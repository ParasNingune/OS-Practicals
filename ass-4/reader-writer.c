#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>  
#include<unistd.h>

sem_t mutex;    //Semaphore for read count
sem_t wrt;      //Semaphore for write count
int read_count=1, no_wrt, no_rd;    //No of reader & writer

void *reader_thr(int temp);
void *writer_thr(int temp);

int main() 
{
    pthread_t reader[10], writer[10];   // Thread declaration

    printf("\nEnter no of readers: ");
    scanf("%d", &no_rd);
    printf("\nEnter no of writers: ");
    scanf("%d", &no_wrt);

    sem_init(&mutex, 0, 1);  // Binary semaphore for read count access
    sem_init(&wrt, 0, 1);    // Binary semaphore for writer access

    // Creating Writer Threads
    for(int i=0; i<no_rd; i++)
    {
        pthread_create(&writer[i], NULL, (void *)writer_thr, (int *)i);
        pthread_join(writer[i], NULL);
    }

    // Creating Reader Threads
    for(int i=0; i<no_rd; i++)
    {
        pthread_create(&reader[i], NULL, (void *)reader_thr, (int *)i);
        pthread_join(reader[i], NULL);
    }
}

void *reader_thr(int temp)
{
    printf("\nReader %d is trying to enter the database...", temp);
    sem_wait(&mutex);   //Lock mutex for read
    read_count++;

    if(read_count == 1)
    {
        sem_wait(&wrt); //Block writers
    }
    sem_post(&mutex);

    printf("\nReader %d is now reading from database...", temp);

    sem_wait(&mutex);   //Read complete unlock mutex
    read_count--;

    if(read_count == 0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);

    printf("\nReader %d has left the database...\n", temp);
    sleep(1);
}

void *writer_thr(int temp)
{
    printf("\nWriter %d is trying to enter the databse...", temp);
    sem_wait(&wrt);
    printf("\nWriter %d is writing in the databse...", temp);
    sleep(1);
    printf("\nWriter %d is leaving the database...\n", temp);
    sem_post(&wrt); //Release write semaphore, allowing others to proceed
}