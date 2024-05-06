#include "pool.h"

std::queue<ThreadPool::Task> ThreadPool::task_queue;
pthread_t* ThreadPool::threads;
pthread_mutex_t ThreadPool::pool_mutex;
pthread_cond_t ThreadPool::queue_not_empty_cond;
bool ThreadPool::non_stop = true;
sem_t ThreadPool::sem_all_lock_unuse;
int ThreadPool::cnt = MAX_THREADS;

void* ThreadPool::worker(void* arg){
    ThreadPool *pool = (ThreadPool*)arg;
    while (pool->non_stop) {
        pthread_mutex_lock(&pool->pool_mutex);
        while (non_stop && pool->task_queue.empty()) {
            pthread_cond_wait(&pool->queue_not_empty_cond, &pool->pool_mutex);
        }

        /* if Server Stop */
        if(!non_stop){
            pthread_mutex_unlock(&pool->pool_mutex);
            if((--cnt) == 0)sem_post(&sem_all_lock_unuse);
            pthread_exit((void*)0);
        }
        /* if not Stop */
        Task task = pool->task_queue.front();
        pool->task_queue.pop();
        Recv(task.data); 
        pthread_mutex_unlock(&pool->pool_mutex);
    }
    pthread_exit((void*)0);
};

ThreadPool* ThreadPool::Init_pool(){
    static ThreadPool pool;
    pthread_mutex_init(&pool.pool_mutex, NULL);
    pthread_cond_init(&pool.queue_not_empty_cond, NULL);
    sem_init(&sem_all_lock_unuse, 0, 0);
    pool.threads = new pthread_t[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&pool.threads[i], NULL, worker, (void*)&pool);
    }

    return &pool;
}
void ThreadPool::Destroy_pool(){
    std::this_thread::sleep_for(std::chrono::milliseconds(200));//avoid Init_pool() and the next sentence is Destroy_pool();
    non_stop = false;
    pthread_cond_broadcast(&queue_not_empty_cond);
    
    if(cnt != 0)sem_wait(&sem_all_lock_unuse);

    int ret = pthread_mutex_destroy(&pool_mutex);
    ret = pthread_cond_destroy(&queue_not_empty_cond);
    delete[] threads;
    sem_destroy(&sem_all_lock_unuse);
}
void ThreadPool::Add_Task(void *data){
    pthread_mutex_lock(&pool_mutex);
    task_queue.push(Task(data));
    pthread_cond_signal(&queue_not_empty_cond);
    pthread_mutex_unlock(&pool_mutex);
}
