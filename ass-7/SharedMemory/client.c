#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>

#define SIZE 100

int main()
{
    int shm_id;
    int *shm_ptr;

    //Get shared Memory ID
    printf("\nEnter ID of shared memory: ");
    scanf("%d", &shm_id);

    //Attach shared Memory
    shm_ptr = shmat(shm_id, NULL, 0);
    if(shm_ptr == (int*)-1)
    {
        printf("\nError attaching Shared Memory...\n");
        exit(1);
    }
    printf("\nClient: Accessing Shared Memory with ID: %d\n", shm_id);

    //Read the data from the shared memory
    printf("\nClient: Reading data from the memory: %d\n", *shm_ptr);

    //Detach from shared Memory
    shmdt(shm_ptr);
    printf("\nClient: Detached from Shared memory...\n\n");
}