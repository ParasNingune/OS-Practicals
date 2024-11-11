#include<stdio.h>
#include<stdbool.h>

struct Process
{   
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

int main()
{
    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    struct Process ps[n];

    printf("\nEnter process details: \n");
    for(int i=0; i<n; i++)
    {
        printf("\nEnter %d process details: \n", i+1);
        ps[i].pid = i+1;

        printf("Enter arrival time: ");
        scanf("%d", &ps[i].arrivalTime);

        printf("Enter burst time: ");
        scanf("%d", &ps[i].burstTime);

        ps[i].remainingTime = ps[i].burstTime;
    }

    printf("\n=======================================\n");
    printf("PID\tArrival\t\tBurst");
    for(int i=0; i<n; i++)
    {
        printf("\n%d \t %d \t\t %d \n", ps[i].pid, ps[i].arrivalTime, ps[i].burstTime);
    }
    printf("\n=======================================\n");

    // Input Done

    int completed=0;
    int currentTime=0;

    while(completed != n)
    {
        int shortest=-1;
        int remainingTime;

        //Find the process with shortest remaining time
        for(int i=0; i<n; i++)
        {
            if(ps[i].arrivalTime <= currentTime && ps[i].remainingTime > 0)
            {
                if(shortest == -1 || ps[i].remainingTime < remainingTime)
                {
                    shortest = i;
                    remainingTime = ps[i].remainingTime;
                }
            }
        }

        if(shortest == -1)
        {
            currentTime++;  //No process to execute so increase current time
            continue;
        }

        ps[shortest].remainingTime--;   //Execute the process for 1 unit time
        currentTime++;

        //If process is completed
        if(ps[shortest].remainingTime == 0)
        {
            ps[shortest].completionTime = currentTime;
            ps[shortest].turnaroundTime = ps[shortest].completionTime - ps[shortest].arrivalTime;
            ps[shortest].waitingTime = ps[shortest].turnaroundTime - ps[shortest].burstTime;
            completed++;
        }
    }
    printf("\nSJF Scheduling Results: \n");
    printf("PID\tArrival\t\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for(int i=0; i<n; i++)
    {
        printf("%d \t %d \t\t %d \t   %d \t\t %d \t\t %d \n\n", ps[i].pid, ps[i].arrivalTime, ps[i].burstTime,
         ps[i].completionTime, ps[i].turnaroundTime, ps[i].waitingTime);
    }
}