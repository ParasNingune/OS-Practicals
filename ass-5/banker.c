// Need = Maximum - Allocation

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocated[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int processes[MAX_PROCESSES];

void initialize();  //Gather all matrix
void calculate_need();  //Calculate need matrix
bool isSafe();  //Checkes whether state is in safe state
bool requestedResources(int processID, int requests[]);

int main()
{
    initialize();
    calculate_need();

    //Display Initial System State:
    printf("\n......Initial State......");
    printf("\nAvailable Resources: ");
    for(int i=0; i<MAX_RESOURCES; i++)
    {
        printf("%d ", available[i]);
    }

    printf("\n\nResource matrix: \n");
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        for(int j=0; j<MAX_RESOURCES; j++)
        {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }

    printf("\nAllocation matrix: \n");
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        for(int j=0; j<MAX_RESOURCES; j++)
        {
            printf("%d ", allocated[i][j]);
        }
        printf("\n");
    }
    printf("\nNeed matrix: \n");
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        for(int j=0; j<MAX_RESOURCES; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    //Check if system is in safe state
    if(isSafe())
    {
        printf("\nThe system already in safe state...\n");
    }
    else
    {
        printf("\nThe system is NOT in safe state...\n");
        exit(1);
    }

    int processID;
    int request[MAX_RESOURCES];

    printf("\nEnter the process ID making request (0-%d): ", MAX_PROCESSES-1);
    scanf("%d", &processID);

    printf("\nEnter request for each resource type:\n");
    for (int i = 0; i < MAX_RESOURCES; i++) 
    {
        scanf("%d", &request[i]);
    }

    if(requestedResources(processID, request))
    {
        printf("Request to process can be granted. System still in safe state...\n\n");
    }
    else
    {
        printf("\nRequest to process can't be granted. This may lead to un-safe state...\n\n");
    }
}

void initialize()
{
    printf("\nEnter no of total available resources per resource type:\n");
    for(int i=0; i<MAX_RESOURCES; i++)
    {
        scanf("%d", &available[i]);
    }

    printf("\n\nEnter Resource Matrix: \n");
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        for(int j=0; j<MAX_RESOURCES; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }
    printf("\n\nEnter the Allocation Matrix: \n");
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        for(int j=0; j<MAX_RESOURCES; j++)
        {
            scanf("%d", &allocated[i][j]);
        }
    }
}

void calculate_need()
{
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        for(int j=0; j<MAX_RESOURCES; j++)
        {
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
    }
}

bool isSafe()
{
    bool finished[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];

    for(int i=0; i<MAX_RESOURCES; i++)
    {
        work[i] = available[i];
    }

    bool foundProcess;
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        foundProcess = false;

        for(int j=0; j<MAX_PROCESSES; j++)
        {
            if(!finished[j])
            {
                bool canAllocate = true;

                for(int k=0; k<MAX_RESOURCES; k++)
                {
                    if(need[j][k] > work[k])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if(canAllocate)
                {
                    for(int l=0; l<MAX_RESOURCES; l++)
                    {
                        work[l] += allocated[j][l];
                    }
                    finished[j] = true;
                    foundProcess = true;
                }
            }
        }
        if(!foundProcess)
        {
            for(int j=0; j<MAX_PROCESSES; j++)
            {
                if(!finished[j])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool requestedResources(int processID, int request[])
{
    //Check if request <= need
    for(int i=0; i<MAX_RESOURCES; i++)
    {
        if(request[i] > need[processID][i])
        {
            printf("\nProcess has exceeded the maximum claim...\n");
            return false;
        }
    }

    //Check if request <= available
    for(int i=0; i<MAX_RESOURCES; i++)
    {
        if(request[i] > available[i])
        {
            printf("\nResources are not availabe...\n");
            return false;
        }
    }

    //Temporarily allocate resources
    for(int i=0; i<MAX_RESOURCES; i++)
    {
        available[i] -= request[i];
        allocated[processID][i] += request[i];
        need[processID][i] -= request[i];
    }

    //Check if  the new state is safe
    if(isSafe())
    {
        return true;
    }
    else
    {
        //Roll back to temporary allocation
        for(int i=0; i<MAX_RESOURCES; i++)
        {
            available[i] += request[i];
            allocated[processID][i] -= request[i];
            need[processID][i] += request[i];
        }
        return false;
    }
}