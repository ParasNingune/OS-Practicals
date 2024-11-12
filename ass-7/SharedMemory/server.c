#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>

#define SIZE 100

int main()
{
    int shm_id;
    int *shm_ptr;
    int data;

    printf("\nEnter data to be written on shared memory: ");
    scanf("%d", &data);

    //Create shared memory
    shm_id = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);   //0666 -> Read write permisions

    if(shm_id < 0)
    {
        printf("\nError creating shared memory...\n");
        exit(1);
    }
    else
    {
        printf("\nCreated Shared Memory with ID: %d\n", shm_id);

        //Attach the shared memory to the process address space
        shm_ptr = (int*) shmat(shm_id, NULL, 0);

        if(shm_ptr == (int*)-1)
        {
            printf("\nError Attaching to shared Memory...\n");
            exit(1);
        }

        //Write message to Shared Memory
        printf("\nServer: Writing to the Shared Memory: %d\n", data);
        *shm_ptr = data;  // Copies the content for data to the shared memory

        //Wait for client to read
        printf("\nServer: Waiting for the client to read...\n");
        sleep(5);

        //Detach fro the Shared Memory
        shmdt(shm_ptr);
        printf("\nServer: Shared Memory Detached...\n\n");
    }
}