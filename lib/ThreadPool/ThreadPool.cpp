#include "ThreadPool.h"
#include <Arduino.h>
#include <functional>
#include <pthread.h>
#include <stdlib.h>

ThreadPool::ThreadPool(__uint16_t threads, __uint16_t maxQueueSize) : m_threads(new pthread_t[threads])
{
    Serial.printf("Initializing a ThreadPool with %d threads and a queue size of %d\n", threads, maxQueueSize);

    m_num_threads = threads;
    m_max_queue_size = maxQueueSize;
    m_cur_queue_size = 0;
    m_queue_head = NULL;
    m_queue_tail = NULL;
    m_queue_closed = 0;
    m_shutdown = 0;

    pthread_mutex_init(&(m_queue_lock), NULL);
    pthread_cond_init(&(m_queue_not_empty), NULL);
    pthread_cond_init(&(m_queue_not_full), NULL);
    pthread_cond_init(&(m_queue_empty), NULL);

    typedef void * (*THREADFUNCPTR)(void *);

    for(__uint16_t i = 0; i != threads; i++)
    {
        pthread_create(&(m_threads[i]), NULL, (THREADFUNCPTR)&ThreadPool::execute, this);
    }
}

void* ThreadPool::execute()
{
    tpool_work_t* work;
    while(true)
    {
        pthread_mutex_lock(&m_queue_lock);

        
    }
}