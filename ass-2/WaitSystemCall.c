#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

void print(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("\t%d",arr[i]);
    }
    printf("\n\n");
}

void bubble_asc(int arr[], int n)
{
    int temp;
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void bubble_dec(int arr[], int n)
{
    int temp;
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(arr[j]<arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() 
{
    printf("\n\n");
    int arr[10],n,i;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter no: ");
        scanf("%d", &arr[i]);
    }

    int pid = fork();   //Fork system call

    if(pid == 0)
    {
        // Orphan State
        printf("\n*******************************ORPHAN STATE*******************************\n");

        printf("\nChild Process PID: %d", getpid());
        printf("\nParent Process PPID: %d", getppid());

        printf("\n\nArray in Ascending Order......\n");
        bubble_asc(arr, n);
        print(arr, n);
    }

    else if (pid > 0)
    {
        // Zombie State
        printf("\n*******************************ZOMBIE STATE*******************************\n");
        int tid = wait(0);

        printf("\nTerminated Child PID: %d", tid);
        printf("\nParent Process PID: %d", getpid());
        printf("\nParent's Parent Process PPID (Bash): %d", getppid());

        printf("\n\nArray in Descending Order......\n");
        bubble_dec(arr, n);
        print(arr, n);
    }

    else
    {
        printf("\nError forking process...");
    }

    return 0;
}