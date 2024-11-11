#include<stdio.h>
#include<limits.h>

void fifo(int pages[], int frameSize);
void lru(int pages[], int frameSize);
void optimal(int pages[], int frameSize);

int main()
{
    int frameSize = 3;

    int pages[10] = {7,0,1,2,3,0,1,2,0,3};  //Initializing the pages with random values
    printf("\nEnter no of frames(Greater than or Equal to 3): ");
    scanf("%d", &frameSize);
    printf("\nEnter 10 pages...\n");

    for(int i=0; i<10; i++)
    {
        printf("Enter %d no: ", i+1);
        scanf("%d", &pages[i]);
    }

    printf("\nPrinting Pages....\n");
    for(int i=0; i<10; i++)
    {
        printf("%d\t", pages[i]);
    }
    printf("\n\n");
    printf("\nFIFO...");
    fifo(pages, frameSize);
    printf("\n\n\n\n");
    printf("\nLRU...");
    lru(pages, frameSize);
    printf("\n\n\n\n");
    printf("\nOptimal...");
    optimal(pages, frameSize);
}

void fifo(int pages[], int frameSize)
{
    int faults=0, front=0, end=0;

    int frame[frameSize];

    printf("\n\nPages\tFrames\tPage Fault\n");
    printf("==========================\n");

    for(int i=0; i<10; i++)
    {
        int found=0;

        //Check if page already in frame
        for(int j=0; j<end; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;  //Page found
                break;
            }
        }

        //If page not found replace
        if(!found)
        {
            faults++;
            if(end<frameSize)
            {
                frame[end++] = pages[i];    //Add page in frame if space available
            }
            else
            {
                frame[front] = pages[i];    //Replace the oldest page
                front = (front+1)%frameSize;
            }

            printf("%d\t", pages[i]);
            for(int k=0; k<end;k++)
            {
                printf("%d ", frame[k]);
            }
            printf("\tY\n");
        }
        else
        {
            printf("%d\t", pages[i]);
            for(int k=0; k<end;k++)
            {
                printf("%d ", frame[k]);
            }
            printf("\tN\n");
        }
    }

    printf("\n\nTotal Page Faults: %d", faults);
}

void lru(int pages[], int frameSize)
{
    int faults=0, end=0;

    int frame[frameSize];   
    int recent[frameSize];

    printf("\nPage\tFrames\tPage Fault\n");
    printf("==========================\n");
    for(int i=0; i<10;i++)
    {
        int found=0, min=0;

        // Check if page is in frame and update its recent usage
        for(int j=0; j<end; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                recent[j] = i;  // Update recent usage of the page
                break;  
            }
        }

        // Page not found in frame
        if(!found) 
        {
            faults++;
            if(end<frameSize)
            {
                frame[end] = pages[i];  //Insert page if space available
                recent[end++] = i;
            }
            else
            {
                for(int j=1;j<end;j++)
                {
                    if(recent[j] < recent[min])
                    {
                        min = j;
                    }
                }
                frame[min] = pages[i];  //Replace least recently used page
                recent[min] = i;
            }
            printf("%d\t", pages[i]);

            for(int k=0; k<end; k++)
            {
                printf("%d ", frame[k]);
            }
            printf("\tY\n");
        }
        else
        {
            printf("%d\t", pages[i]);
            for(int k=0; k<end; k++)
            {
                printf("%d ", frame[k]);
            }
            printf("\tN\n");
        }
    }
    printf("\nTotal Page Faults: %d\n", faults);
}

void optimal(int pages[], int frameSize)
{
    int faults=0, end=0;

    int frame[frameSize];

    printf("\nPage\tFrames\tPage Fault\n");
    printf("==========================\n");

    for(int i=0;i<10;i++)
    {
        int found=0;

        for(int j=0;j<end;j++)
        {
            if(frame[j] == pages[i])
            {
                found=1;
                break;
            }
        }

        if(!found)
        {
            faults++;
            if(end<frameSize)
            {
                frame[end++] = pages[i];    //Insert page if space available
            }
            else
            {  
                //Find the page that will not be used for long time
                int replace=-1, far=i;
                for(int j=0;j<end;j++)
                {
                    int k;
                    for(k=i+1; k<10; k++)
                    {
                        if(frame[j] == pages[k])
                        {
                            break;
                        }
                    }
                    if(k > far)
                    {
                        far = k;
                        replace = j;
                    }
                }
                frame[replace] = pages[i];  //Replace optimal 
            }    
            printf("%d\t", pages[i]);

            for(int k=0; k<end; k++)
            {
                printf("%d ", frame[k]);
            }
            printf("\tY\n");
        }
        else
        {
            printf("%d\t", pages[i]);
            for(int k=0; k<end; k++)
            {
                printf("%d ", frame[k]);
            }
            printf("\tN\n");
        }
    }
    printf("\nTotal Page Faults: %d\n", faults);
}
