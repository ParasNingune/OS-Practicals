#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];    //Shared Buffer
int in=0;   //Consumer index    
int out=0;  //Producer index

sem_t empty;    //Count empty slots in buffer
sem_t full;     //Counts filled slots in buffer
pthread_mutex_t mutex;  //Creating Mutex

void *producer()
{
    for(int i=0; i<MAX_ITEMS; i++)
    {
        int item;
        item = rand()%100;  //Produce random item

        sem_wait(&empty);   //Wait for empty slot
        pthread_mutex_lock(&mutex); //Lock mutex

        buffer[in] = item;
        printf("\nProducer produced: %d\n", item);
        in = (in+1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);   //Unlock mutex
        sem_post(&full);    //Signal item added

        sleep(1);
    }
}

void *consumer()
{
    for(int i=0; i<MAX_ITEMS; i++)
    {
        int item;
        sem_wait(&full);    //Wait for a filled slot
        pthread_mutex_lock(&mutex); //Lock mutex

        //Remove item from buffer
        item = buffer[out];
        printf("\nConsumer consumed: %d\n", item);
        out = (out+1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);      //Signal that item was removed

        sleep(1);
    }
}

int main() 
{
    pthread_t tid_producer, tid_consumer;

    sem_init(&empty, 0, BUFFER_SIZE);   //Initially all buffer slots are empty
    sem_init(&full, 0, 0);  //Initially no items in buffer
    pthread_mutex_init(&mutex, NULL);   //Initialize mutex

    // Create producer and consumer threads
    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    // Wait for the threads to complete
    pthread_join(tid_producer, NULL),
    pthread_join(tid_consumer, NULL);

    //Destroy everything after use
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}