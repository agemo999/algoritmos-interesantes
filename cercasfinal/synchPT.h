#include <semaphore.h>

class Semaphore {

   public:

      Semaphore( int );
      ~Semaphore();
      int Signal();
      int Wait();

   private:
      sem_t  sem;

// sem_init
// sem_post
// sem_wait

};


class Mutex {

   public:

      Mutex();
      ~Mutex();
      int Lock();
      int Unlock();

   private:
      pthread_mutex_t  mutex;
      
// pthread_mutex_init
// pthread_mutex_lock
// pthread_mutex_unlock
// pthread_mutex_destroy
};


class Lock {
   public:
      Lock();
      ~Lock();
      int Acquire();
      int Release();
      pthread_mutex_t * getMutex() { return &lock; }

   private:
      pthread_mutex_t  lock;

};


class Condition {

   public:
      Condition();
      ~Condition();
      int Wait( Lock * conditionLock );
      int TimedWait( Lock * conditionLock );
      int Signal( Lock * conditionLock );
      int Broadcast( Lock * conditionLock );

   private:
      pthread_cond_t  vc;
// pthread_cond_init
// pthread_cond_wait
// pthread_cond_signal
// pthread_cond_timedwait
// pthread_cond_broadcast
// pthread_cond_destroy
};
