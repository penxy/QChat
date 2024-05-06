#ifndef __POOL_H
#define __POOL_H

#include <pthread.h>
#include <queue>
#include <semaphore.h>
#include <thread>
#include "ClientRecv.h"

class ThreadPool : ClientRecv{
public:
    static ThreadPool* Init_pool();    
    static void Destroy_pool();
    void Add_Task(void *data);
private:
    static void* worker(void* arg);
private:
    ThreadPool() = default;
    ~ThreadPool() = default;
    ThreadPool(const ThreadPool& );
    ThreadPool& operator = (const ThreadPool&);
private:
    struct Task{
        void* data;   
        Task(void* data) : data(data){}
    };
private:
    static std::queue<Task>task_queue;
    static pthread_t* threads;
    static pthread_mutex_t pool_mutex;
    static pthread_cond_t queue_not_empty_cond;
private:
    static const int MAX_THREADS = 6;
    static bool non_stop;
    static sem_t sem_all_lock_unuse;
    static int cnt;
};



#endif
