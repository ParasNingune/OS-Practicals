// #include<stdio.h>
// #include<stdlib.h>
// #include<sys/shm.h>
// #include<unistd.h>

// #define SIZE 4096

// int main()
// {
//     int shm_id;
//     int *shm_ptr;
//     int data,ret_val;
//     int read_data;
//     int pid;

//     //Create Shared memory
//     shm_id = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);

//     if(shm_id < 0)
//     {
//         printf("\nError creating shared memory...\n");
//         exit(1);
//     }
//     else
//     {
//         printf("\nShared Memory created with ID: %d", shm_id);
//         shm_ptr = (int*) shmat(shm_id, NULL, 0);        // Attach the Shared Memory to process address space

//         if(shm_ptr == (int*)-1)
//         {
//             printf("\nError attaching Shared Memory...\n");
//             exit(1);
//         }
//         else
//         {
//             printf("\nEnter data to be stored on memory: ");
//             scanf("%d", &data);
//             *shm_ptr = data;

//             pid = fork();

//             if(pid == 0)
//             {
//                 printf("\nChild reads data from the Shared Memory: %d", *shm_ptr);
//             }
//             shmdt(shm_ptr);     // Detach the Shared Memory
//             if(pid > 0)
//             {
//                 printf("\nParent detached from Shared Memory...\n");
//             }
//         }
//     }
//     return 0;
// }

#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>

#define SIZE 4096

int main()
{
    int shm_id;
    char *shm_ptr;
    char message[] = "Hello from Server!";

    // Create shared memory segment
    shm_id = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);
    if(shm_id < 0)
    {
        perror("Error creating shared memory");
        exit(1);
    }
    else
    {
        printf("\nShared Memory created with ID: %d\n", shm_id);

        // Attach the shared memory to the process address space
        shm_ptr = (char*) shmat(shm_id, NULL, 0);
        if(shm_ptr == (char*)-1)
        {
            perror("Error attaching shared memory");
            exit(1);
        }

        // Write the message to shared memory
        printf("Server: Writing to shared memory: %s\n", message);
        strcpy(shm_ptr, message);

        // Wait for client to read the message
        printf("Server: Waiting for client to read...\n");
        sleep(5);  // Simulate wait time for client to read the data

        // Detach the shared memory
        shmdt(shm_ptr);
        printf("\nServer: Detached from shared memory\n");

        // Optional: Clean up shared memory (done later by both server and client)
        // shmctl(shm_id, IPC_RMID, NULL);  // Uncomment this to destroy the memory
    }

    return 0;
}
