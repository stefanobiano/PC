/**********************************
 *
 * @author      Bianucci Stefano
 *
 **********************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
int done = 0;

void *task(void *arg) {
    
    /* Presentation */
    int me = pthread_self();
    printf("I am the thread: %i \n", me);
    
    /* Work */
    usleep(1000);

    pthread_exit (NULL);
}
  
int main(){

    printf("TEST STARTED \n");
    /* start time */
    clock_t start,end;
    double time;
    start=clock();

    pthread_t threads[80];
    for (int i=0; i<80; i++){
        pthread_create(&threads[i], NULL, task, NULL);
    }
    
    /* End time */
    end=clock();
    time=((double)(end-start))/CLOCKS_PER_SEC;
    printf("Total time:  %f seconds\n", time);

    exit(0);
}
