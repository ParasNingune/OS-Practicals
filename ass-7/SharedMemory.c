#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>

#define SIZE 4096

int main()
{
    int shm_id;
    int *shm_ptr;
    int data,ret_val;
    int read_data;
    int pid;

    shm_id = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);

    if(shm_id < 0)
    {
        printf("\nError creating shared memory...\n");
        exit(1);
    }
    else
    {
        printf("\nShared Memory created with ID: %d", shm_id);
        shm_ptr = (int*) shmat(shm_id, NULL, 0);        // Attach the Shared Memory

        if(shm_ptr == (int*)-1)
        {
            printf("\nError attaching Shared Memory...\n");
            exit(1);
        }
        else
        {
            printf("\nEnter data to be stored on memory: ");
            scanf("%d", &data);
            *shm_ptr = data;

            pid = fork();

            if(pid == 0)
            {
                printf("\nChild reads data from the Shared Memory: %d", *shm_ptr);
            }
            shmdt(shm_ptr);     // Detach the Shared Memory
            if(pid > 0)
            {
                printf("\nParent detached from Shared Memory...\n");
            }
        }
    }
    return 0;
}