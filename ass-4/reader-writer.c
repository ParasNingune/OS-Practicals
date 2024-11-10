#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>  
#include<unistd.h>

sem_t mutex;
sem_t wrt;
int read_count=1, no_wrt, no_rd;

void *reader_thr(int temp);
void *writer_thr(int temp);

int main() 
{
    pthread_t reader[10], writer[10];
    printf("\nEnter no of readers: ");
    scanf("%d", &no_rd);
    printf("\nEnter no of writers: ");
    scanf("%d", &no_wrt);

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
    sem_wait(&mutex);
    read_count++;

    if(read_count == 1)
    {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    printf("\nReader %d is now reading from database...", temp);

    sem_wait(&mutex);
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
    sem_post(&wrt);
}