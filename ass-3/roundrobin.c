#include<stdio.h>
#include<stdbool.h>

struct Process {
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
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

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

    int currentTime = 0, completed=0;
    int queue[n];
    int front = 0, rear = 0;
    bool inQueue[n];

    //Initially entire queue is empty
    for(int i=0; i<n; i++)
    {
        inQueue[i] = false;
    }

    //Initializing the queue with the first arrived process
    currentTime = ps[0].arrivalTime;
    queue[rear++] = 0;
    inQueue[0] = true;

    while (completed != n)
    {
        int process = queue[front++];

        //Circular Queue
        if(front == n)
        {
            front = 0;
        }

        //Check if the process is still waiting for exectution
        if(ps[process].remainingTime > 0)
        {
            //If process can finish in this time quantum
            if(ps[process].remainingTime <= quantum)
            {
                currentTime += ps[process].remainingTime;
                ps[process].remainingTime = 0;

                //Process completion
                ps[process].completionTime = currentTime;
                ps[process].turnaroundTime = ps[process].completionTime - ps[process].arrivalTime;
                ps[process].waitingTime = ps[process].turnaroundTime - ps[process].burstTime;
                completed++;
            }
            else
            {
                //Process runs for full time quantum
                ps[process].remainingTime -= quantum;
                currentTime += quantum;
            }

            //For newly arrived processes in queue
            for(int i=0; i<n; i++)
            {
                if(i != process && ps[i].arrivalTime <= currentTime && ps[i].remainingTime > 0 && !inQueue[i])
                {
                    queue[rear++] = i;
                    
                    //Circular queue
                    if(rear == n)
                    {
                        rear = 0;
                    }
                    inQueue[i] = true;
                }
            }

            //Re-add current process to end of queue if not completed
            if(ps[process].remainingTime > 0)
            {
                queue[rear++] = process;
                
                //Circular Queue
                if(rear == n)
                {
                    rear = 0;
                }
            }
        }
    }

    printf("\nRound Robin Scheduling Results: \n");
    printf("PID\tArrival\t\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for(int i=0; i<n; i++)
    {
        printf("%d \t %d \t\t %d \t   %d \t\t %d \t\t %d \n\n", ps[i].pid, ps[i].arrivalTime, ps[i].burstTime,
         ps[i].completionTime, ps[i].turnaroundTime, ps[i].waitingTime);
    }

    float averageWT, averageTT;
    int temp1=0, temp2=0;

    for(int i=0; i<n; i++)
    {
        temp1 += ps[i].waitingTime;
        temp2 += ps[i].turnaroundTime;
    }

    averageWT = (float)temp1 / n;
    averageTT = (float)temp2 / n;

    printf("\n\nAverage Waiting Time: %0.2f", averageWT);
    printf("\nAverage TurnAround Time: %0.2f\n", averageTT);
}