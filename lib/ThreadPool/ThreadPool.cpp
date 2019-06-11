#include "ThreadPool.h"
#include <Arduino.h>
#include <functional>
#include <pthread.h>
#include <stdlib.h>

ThreadPool::ThreadPool(__uint16_t threads, __uint16_t maxQueueSize)
{
    Serial.printf("Initializing a ThreadPool with %d threads and a queue size of %d\n", threads, maxQueueSize);

    tpool_t tpool;
    if ((tpool = (tpool_t )malloc(sizeof(struct tpool))) == NULL)
    {
        Serial.println("[ERROR] Could not allocate sufficient memory for the threadpool");
    }

    tpool->num_threads = threads;
    tpool->max_queue_size = maxQueueSize;
    if ((tpool->threads = (pthread_t*)malloc(sizeof(pthread_t) * threads)) == NULL)
    {
        Serial.println("[ERROR] Could not allocate sufficient memory for threads");
    }
    tpool->cur_queue_size = 0;
    tpool->queue_head = NULL;
    tpool->queue_tail = NULL;
    tpool->queue_closed = 0;
    tpool->shutdown = 0;

    pthread_mutex_init(&(tpool->queue_lock), NULL);
    pthread_cond_init(&(tpool->queue_not_empty), NULL);
    pthread_cond_init(&(tpool->queue_not_full), NULL);
    pthread_cond_init(&(tpool->queue_empty), NULL);

    typedef void * (*THREADFUNCPTR)(void *);

    for(__uint16_t i = 0; i != threads; i++)
    {
        pthread_create( &(tpool->threads[i]), NULL, (THREADFUNCPTR)&ThreadPool::execute, (void*) tpool);
    }

    currentThreadPool = tpool;
}

void* ThreadPool::execute(tpool_t tpool)
{
    
}