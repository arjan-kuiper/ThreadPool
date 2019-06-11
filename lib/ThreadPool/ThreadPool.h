#pragma once

#include <pthread.h>
#include <stdint.h>

class ThreadPool
{
    private:
        typedef void * (*THREADFUNCPTR)(void *);

        typedef struct tpool_work {
            void (*routine)(void*);
            void *arg;
            struct tpool_work *next;
        } tpool_work_t;

        __uint16_t m_num_threads;
        __uint16_t m_max_queue_size;
        __uint16_t m_cur_queue_size;
        __uint16_t m_queue_closed;
        __uint16_t m_shutdown;
        pthread_t *m_threads;
        tpool_work_t *m_queue_head;
        tpool_work_t *m_queue_tail;
        pthread_mutex_t m_queue_lock;
        pthread_cond_t m_queue_not_empty;	
        pthread_cond_t m_queue_not_full;	
        pthread_cond_t m_queue_empty;

        void* execute();
        int deallocate(bool awaitWorkers = true);
    
    public:
    ThreadPool(__uint16_t threads, __uint16_t maxQueueSize);
    ~ThreadPool();
    int addWork(void* routine, void* args);
};