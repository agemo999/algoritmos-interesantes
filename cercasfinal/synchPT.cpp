
#include "synchPT.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <pthread.h>

using namespace std;



Semaphore::Semaphore( int i) {//crea un semáforo en un número especifico
    
    sem_init(&sem,0,i);
    
}

int Semaphore::Wait() {//hace que se espere al reducir el sem.op en uno, basicamente detiene el funcionamiento si el semaforo esta en 0 o menos
    
    return sem_wait(&sem);
    
}

int Semaphore::Signal() {// aumenta el sem.op en uno, esto activa los procesos que esten en wait() para que continuen su funcionamiento
    
    return sem_post(&sem);
}

Semaphore::~Semaphore() {//destruye el semáforo
    sem_destroy(&sem);
}

Mutex::Mutex(){
    
    pthread_mutex_init ( &mutex, NULL );
}

int Mutex::Lock(){
    return pthread_mutex_lock(&mutex);
}

int Mutex::Unlock(){
    
    return pthread_mutex_unlock(&mutex);
}


Mutex::~Mutex() {//destruye el semáforo
    pthread_mutex_destroy(&mutex);
}


Lock::Lock(){
    pthread_mutex_init(&lock,NULL);
}

int Lock::Acquire(){
    return pthread_mutex_lock(&lock);
}

int Lock::Release(){
    
    return pthread_mutex_unlock(&lock);
}

Lock::~Lock(){
    pthread_mutex_destroy(&lock);
}

Condition::Condition(){
    
    vc = PTHREAD_COND_INITIALIZER;
}



int Condition::Wait( Lock * conditionLock ){
    return pthread_cond_wait(&vc,conditionLock->getMutex());
    
}

int Condition::TimedWait( Lock * conditionLock ){
    struct timespec max_wait = {0, 10};
    return pthread_cond_timedwait(&vc,conditionLock->getMutex(),&max_wait);
    
}
int Condition::Signal( Lock * conditionLock ){
    
    return pthread_cond_signal(&vc);
}

int Condition::Broadcast( Lock * conditionLock ){
    
    return pthread_cond_broadcast(&vc);
    
}

Condition::~Condition(){
    
    pthread_cond_destroy(&vc);
}