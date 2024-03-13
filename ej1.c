#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *process1(void *arg) {
    while (1) {
        printf("Process 1: Attempting to acquire Resource 1\n");
        pthread_mutex_lock(&mutex1);
        sleep(1); 
        printf("Process 1: Acquired Resource 1\n");
        
        printf("Process 1: Attempting to acquire Resource 2\n");
        pthread_mutex_lock(&mutex2);
        printf("Process 1: Acquired Resource 2\n");
        
        sleep(2);
        
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

void *process2(void *arg) {
    while (1) {
        printf("Process 2: Attempting to acquire Resource 2\n");
        pthread_mutex_lock(&mutex2);
        sleep(1);
        printf("Process 2: Acquired Resource 2\n");
        
        printf("Process 2: Attempting to acquire Resource 1\n");
        pthread_mutex_lock(&mutex1);
        printf("Process 2: Acquired Resource 1\n");
        
        sleep(2);
        
        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    
    pthread_create(&tid1, NULL, process1, NULL);
    pthread_create(&tid2, NULL, process2, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    return 0;
}
