/**********************************
 *
 * @author      Bianucci Stefano
 *
 **********************************/

/* Define new type: threadPool_Thread */
typedef struct threadPool threadPool_Thread;

/**
 * @brief  Initialize threadpool
 *
 * Initializes a threadpool. This function will not return untill all
 * threads have initialized successfully.
 *
 *
 * @param  numThread   number of threads to be created in the threadpool
 * @param  queueSize    size of the queue
 * @return threadpool    created threadpool on success,
 *                       NULL on error
 */
threadPool_Thread *threadpool_init(unsigned int numThread, unsigned int queueSize);

/**
 * @brief Add work to the task queue
 *
 * Takes an action and its argument and adds it to the threadpool's task queue.
 *
 *
 * @param pool      thread pool to which add the task
 * @param function  pointer to the function that will perform the task
 * @param argument  argument to be passed to the function
 * @return 0 if all goes well, negative values in case of error
 */
int threadpool_add_task(threadPool_Thread *pool, void (*function)(void *), void *argument);

/**
 * @brief Cancel all queued tasks and destroy the pool.
 *
 * @param pool  thread pool to destroy.
 * @return 0 if all goes well, negative values in case of error
 */
int threadpool_destroy(threadPool_Thread *pool);
