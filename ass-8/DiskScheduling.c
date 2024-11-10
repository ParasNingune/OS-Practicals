#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void sstf(int reqs[], int visited[], int head_pos, int n);
int find_min(int reqs[], int visited[], int head_pos, int n);
void scan(int reqs[], int head_pos, int n, int head_dir, int size);
void clook(int reqs[], int head_pos, int n, int head_dir);

int main()
{
    int n, head, head_dir, size_disk;

    printf("\n\nEnter Size of Disk: ");
    scanf("%d", &size_disk);

    printf("\nEnter no of requests: ");
    scanf("%d", &n);
    printf("\n");

    int reqs[n], visited[n];
    printf("\nEnter the requests...\n");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &reqs[i]);
        visited[i] = 0;
    }

    printf("\n\nEnter head position: ");
    scanf("%d", &head);

    printf("\nSSTF Scheduling Result....");
    sstf(reqs, visited, head, n);

    printf("\nEnter the direction of traversal (0:Lower, 1:Upper): ");
    scanf("%d", &head_dir);
    printf("\nScan Scheduling Result....");
    scan(reqs, head, n, head_dir, size_disk);

    printf("\n\nCLOOK Scheduling Result....");
    clook(reqs, head, n, head_dir);
}

int find_min(int reqs[], int visited[], int head_pos, int n)
{
    int min_dis = INT_MAX;
    int min_index = -1;

    for(int i=0; i<n; i++)
    {
        int distance = abs(head_pos - reqs[i]);
        if(!visited[i] && distance < min_dis)
        {
            min_dis = distance;
            min_index = i;
        }
    }

    return min_index;
}

void sstf(int reqs[], int visited[], int head_pos, int n)
{
    int total_mov = 0;
    printf("\n\nHead Movement Sequence: \n");

    for(int i=0; i<n;i++)
    {
        int min_index = find_min(reqs, visited, head_pos, n);
        visited[min_index] = 1;

        total_mov += abs(head_pos-reqs[min_index]);
        head_pos = reqs[min_index];
        printf("%d ", head_pos);
    }
    printf("\n\nTotal Head movements: %d\n\n", total_mov);
}

void scan(int reqs[], int head_pos, int n, int head_dir, int size)
{
    int total_mov=0;
    // Sort the request queue
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(reqs[j] > reqs[j+1])
            {
                int temp = reqs[j];
                reqs[j] = reqs[j+1];
                reqs[j+1] = temp;
            }
        }
    }

    // Find index where requests greater than initial head pos
    int index=0;
    while(index < n && reqs[index] < head_pos)
    {
        index++;
    }

    printf("\nHead position....\n");
    if(head_dir == 1)
    {
        for(int i=index; i<n; i++)
        {
            total_mov += abs(head_pos - reqs[i]);
            head_pos = reqs[i];
            printf("%d ", head_pos);
        }

        // Jump to end of disk
        total_mov += abs(size - 1 - head_pos);
        head_pos = size - 1;
        printf("%d ", head_pos);

        for(int i=index-1; i>=0; i--)
        {
            total_mov += abs(head_pos - reqs[i]);
            head_pos = reqs[i];
            printf("%d ", head_pos);
        }
    }
    else
    {
        for(int i=index-1; i>=0; i--)
        {
            total_mov += abs(head_pos - reqs[i]);
            head_pos = reqs[i];
            printf("%d ", head_pos);
        }

        // Jump to end of disk
        total_mov += abs(head_pos - 0);
        head_pos=0;
        printf("%d ", head_pos);

        for(int i=index; i<n; i++)
        {
            total_mov += abs(head_pos - reqs[i]);
            head_pos = reqs[i];
            printf("%d ", head_pos);
        }
    }
    printf("\n\nTotal Head movements: %d\n", total_mov);
}

void clook(int reqs[], int head_pos, int n, int head_dir)
{
    int total_mov=0;
    // Sort the request queue
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(reqs[j] > reqs[j+1])
            {
                int temp = reqs[j];
                reqs[j] = reqs[j+1];
                reqs[j+1] = temp;
            }
        }
    }

    // Find index where requests greater than initial head pos
    int index=0;
    while(index < n && reqs[index] < head_pos)
    {
        index++;
    }

    printf("\nHead position....\n");
    if(head_dir == 1)
    {
        for(int i=index; i<n; i++)
        {
            total_mov += abs(head_pos - reqs[i]);
            head_pos = reqs[i];
            printf("%d ", head_pos);
        }

        // Jump to lowest request 
        if(index > 0)
        {
            total_mov += abs(head_pos - reqs[0]);
            head_pos = reqs[0];
            printf("%d ", head_pos);

            for(int i=index-1; i>=0; i--)
            {
                total_mov += abs(head_pos - reqs[i]);
                head_pos = reqs[i];
                printf("%d ", head_pos);
            }
        }
    }
    else
    {
        for(int i=index-1; i>=0; i--)
        {
            total_mov += abs(head_pos - reqs[i]);
            head_pos = reqs[i];
            printf("%d ", head_pos);
        }

        // Jump to highest request
        if(index < n)
        {
            total_mov += abs(head_pos - reqs[n-1]);
            head_pos=reqs[n-1];
            printf("%d ", head_pos);

            for(int i=index; i<n; i++)
            {
                total_mov += abs(head_pos - reqs[i]);
                head_pos = reqs[i];
                printf("%d ", head_pos);
            }
        }
    }
    printf("\n\nTotal Head movements: %d\n\n", total_mov);
}

