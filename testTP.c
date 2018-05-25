/**********************************
 *
 * @author      Bianucci Stefano
 *
 **********************************/

#define THREAD 8
#define QUEUE  80

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#include "threadpool.h"

int tasks = 0, done = 0;
pthread_mutex_t lock;


void task(void *arg) {
    
    /* Presentation */
    int me = pthread_self();
    printf("I am the thread: %i \n", me);
    
    /* Work */
    usleep(1000);
    
    /* Update done */
    pthread_mutex_lock(&lock);
    done++;
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv){
    
    printf("TEST STARTED \n");
    
    /* start time */
    clock_t start,end;
    double time;
    start=clock();
    
    /* threadpool pointer */
    threadPool_Thread *pool;
    
    pthread_mutex_init(&lock, NULL);
    
    /* Make new thread pool */
    assert((pool = threadpool_init(THREAD, QUEUE)) != NULL);
    printf("Created threadpool with %d threads and with dimension of queue: %d\n", THREAD, QUEUE);
    
    /* Add work to threadpool */
    while(threadpool_add_task(pool, &task, NULL) == 0){
        pthread_mutex_lock(&lock);
        tasks++;
        pthread_mutex_unlock(&lock);
    }
    
    printf("Added %d tasks\n", tasks);
    
    /* Wait until all task are completed */
    while((tasks ) > done) {
        usleep(1000);
    }
    printf("Completed  %d tasks\n", done);

    /* Destroy threadpool */
    assert(threadpool_destroy(pool) == 0);
    
    /* End time */
    end=clock();
    time=((double)(end-start))/CLOCKS_PER_SEC;
    printf("Total time:  %f seconds\n", time);
    
    return 0;
}
