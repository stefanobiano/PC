/**********************************
 *
 * @author      Bianucci Stefano
 *
 **********************************/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include "threadpool.h"

/* ========================== STRUCTURES ============================ */

/* Task */
typedef struct {
    void (*function)(void *);   /* function pointer */
    void *argument;             /* function argument */
} task;

/* Threadpool */
struct threadPool {
    
    int threadNum;          /* Thread number */
    int queueSize;          /* Queue of task to do */
    task *queue;            /* Array containing the task queue */
    
    /* FIFO queued job */
    int head;               /* Index of the first element */
    int tail;               /* Index of the last element */
    int count;              /* Number of pending tasks */
    
    int started;            /* Number of started threads */
    
    int shutdown;           /* Flag indicating if the pool is shutting down */
    
    pthread_mutex_t lock;   /* Condition variable to lock worker threads */
    pthread_cond_t notify;  /* Condition variable to notify worker threads */
    pthread_t *threads;     /* Array containing worker threads ID */
    
    
};

/* ========================== PROTOTYPES ============================ */

/**
 * @brief Takes off work from task queue
 *
 * Takes off an action and its argument from the task queue.
 *
 *
 * @param pool thread pool to which take off the task
 * @return anything
 */
static void *threadpool_thread(void *threadpool);

/* ========================== THREADPOOL ============================ */

/* Initialise thread pool */
threadPool_Thread *threadpool_init(unsigned int numThread, unsigned int queueSize){
    
    /* Make new thread pool */
    threadPool_Thread *pool;
    /* Allocate memory for thread pool */
    if((pool = (threadPool_Thread *)malloc(sizeof(threadPool_Thread))) == NULL) {
        err("threadpool_init(): Could not allocate memory for thread pool\n");
        return NULL;
    }
    
    /* Initialise thread pool value */
    pool->threadNum = 0;
    pool->queueSize = queueSize;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;
    
    /* Allocate memory for threads and queue */
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * numThread);//alloco lo spazio
    pool->queue = (task *)malloc(sizeof(task) * queueSize);
    if ((pool->threads == NULL) || (pool->queue == NULL)){
        err("threadpool_init(): Could not allocate memory for threads or queue\n");
        free(pool);
        return NULL;
    }
    
    /* Initialise mutex and cond */
    pthread_mutex_init(&(pool->lock), NULL);
    pthread_cond_init(&(pool->notify), NULL);
    
    /* Make threads in pool */
    for(int i = 0; i < numThread; i++) {
        if(pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void*)pool) != 0) {
            threadpool_destroy(pool);
            return NULL;
        }
        pool->threadNum++;
        pool->started++;
    }
    
    return pool;
}

int threadpool_add_task(threadPool_Thread *pool, void (*function)(void *), void *argument){
    int err = 0;
    int next;
    
    /* Check pool, function and lock */
    if(pool == NULL || function == NULL || (pthread_mutex_lock(&(pool->lock)) != 0)) { //caso in cui il threadpool o la funzione da runnare non sono definiti
        return -1;
    }
    
    next = (pool->tail + 1) % pool->queueSize;
    
    /* Infinite loop */
    do {
        /* Check is there a full queue or if system is in shutting down mode*/
        if(pool->count == pool->queueSize || (pool->shutdown)) {
            err = -1;
            break;
        }
        
        
        /* Add task to queue */
        pool->queue[pool->tail].function = function; /* Add FIFO mode */
        pool->queue[pool->tail].argument = argument;
        pool->tail = next; /* Update free position */
        pool->count += 1; /* Update counter */
        
        /* Check cond lock */
        if(pthread_cond_signal(&(pool->notify)) != 0) {
            err = -1;
            break;
        }
    } while(0);
    
    /* Check mutex lock */
    if(pthread_mutex_unlock(&pool->lock) != 0) {
        err = -1;
    }
    
    return err;
}

int threadpool_destroy(threadPool_Thread *pool){
    
    int error = 0;
    
    /* Check if pool and function are defined and if the lock is open */
    if(pool == NULL || (pthread_mutex_lock(&(pool->lock)) != 0)) {
        err("pool not defined or locked\n");
        return -1;
    }
    
    /* Endless loop */
    do {
        /* Thread pool is already in shutdown mode */
        if(pool->shutdown) {
            err("shutdown\n");
            error = -1;
            break;
        }
        
        pool->shutdown = 1;
        
        /* Check locks */
        if((pthread_cond_broadcast(&(pool->notify)) != 0) || (pthread_mutex_unlock(&(pool->lock)) != 0)) {
            err("locked\n");
            error = -1;
            break;
        }
        
        /* Join all thread worker */
        for(int i = 0; i < pool->threadNum; i++) {
            if(pthread_join(pool->threads[i], NULL) != 0) {
                err("failed\n");
                error = -1;
            }
        }
    } while(0);
    
    /* Memory released in error case */
    if(!error) {
        if(pool) {
            free(pool->threads);
            free(pool->queue);
            free(pool);
        }
    }
    return error;
}

static void *threadpool_thread(void *threadpool) {

    /* Make a threadpool pointer */
    threadPool_Thread *pool = (threadPool_Thread *) threadpool;
    /* Make task */
    task task;
    
    /* Endless loop */
    for (;;) {
        /* Take lock */
        pthread_mutex_lock(&(pool->lock));
        
        /* Wait cond */
        while ((pool->count == 0) && (!pool->shutdown)) {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }
        
        if ((pool->shutdown == 1) && (pool->count == 0)) {
            break;
        }
        /* Update the task */
        task.function = pool->queue[pool->head].function;
        task.argument = pool->queue[pool->head].argument;
        
        /* Update the threadpool */
        pool->head = (pool->head + 1) % pool->queueSize;
        pool->count -= 1;
        
        /* Release lock */
        pthread_mutex_unlock(&(pool->lock));
        
        /* Start task */
        (*(task.function))(task.argument);
    }

    /* Update the threadpool */
    pool->started--;
    
    /* Release lock in case of break */
    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
    return (NULL);
}
