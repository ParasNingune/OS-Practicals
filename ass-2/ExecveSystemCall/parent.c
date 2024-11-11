#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

void bubble_asc(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("Array in Ascending Order: \n");
    for(int i=0; i<n; i++)
    {
        printf("\t%d", arr[i]);
    }
}

void intToStrArray(int *arr, int n, char *strArr[])
{
    for(int i=0; i<n; i++)
    {
        strArr[i] = malloc(20*sizeof(char));    //Allocate 20 bytes for each integer string
        sprintf(strArr[i], "%d", arr[i]);   //Typecasts integer to string
    }
    strArr[n] = NULL;
}

int main() 
{
    int n;
    printf("\nEnter no of elements in array: ");
    scanf("%d", &n);

    int arr[n];
    printf("\nEnter the elements: \n");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("\n");
    bubble_asc(arr, n);
    printf("\n");

    pid_t pid = fork();

    if(pid < 0)
    {
        printf("\nFork Failed...\n");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("\nChild Process ID: %d\n", getpid());
        printf("\nParent Process ID: %d\n", getppid());
        char *args[n+2];    //Extra space for program name and NULL terminator
        args[0] = "./child";    //Name of new program

        intToStrArray(arr,n, &args[1]); //Convert intergers to string

        //Execute child program
        if(execve(args[0], args, NULL) == -1)
        {
            printf("\nExecve Failed...\n");
            exit(1);
        }
    }
    else
    {
        //Parent Process
        wait(NULL); //Wait for the child process to complete
    }
}