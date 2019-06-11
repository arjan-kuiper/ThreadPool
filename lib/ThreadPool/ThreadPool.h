#pragma once

#include <pthread.h>
#include <stdint.h>

class ThreadPool
{
    private:
        typedef struct tpool_work {
            void (*routine)();
            void *arg;
            struct tpool_work *next;
        } tpool_work_t;

        typedef struct tpool {
            __uint16_t num_threads;
            __uint16_t max_queue_size;
            __uint16_t cur_queue_size;
            __uint16_t queue_closed;
            __uint16_t shutdown;
            pthread_t *threads;
            tpool_work_t *queue_head;
            tpool_work_t *queue_tail;
            pthread_mutex_t queue_lock;
            pthread_cond_t queue_not_empty;	
            pthread_cond_t queue_not_full;	
            pthread_cond_t queue_empty;     
        } *tpool_t;

        tpool_t currentThreadPool;

        void* execute(tpool_t tpool);
    
    public:
    ThreadPool(__uint16_t threads, __uint16_t maxQueueSize);
};