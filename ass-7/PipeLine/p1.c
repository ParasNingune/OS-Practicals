#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int c = 0;
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";
    char str[256];

    //Grants full read, write & execute permissions to the owner
    if(mkfifo(fifo1, 0777) == -1)
    {
        printf("\nPipe1 not created...\n");
        exit(1);
    }
    printf("\nPipe1 created successfully...");

    if(mkfifo(fifo2, 0777) == -1)
    {
        printf("\nPipe2 not created...\n");
        exit(1);
    }
    printf("\nPipe2 created successfully...");

    //Open Pipes for reading and writing
    int writer = open(fifo1, O_WRONLY);   //Open Pipe for writing
    if (writer == -1)
    {
        printf("\nFailed to open fifo1 for writing...\n");
        exit(1);
    }
    int reader = open(fifo2, O_RDONLY);  // Open fifo2 for reading
    if (reader == -1)
    {
        printf("\nFailed to open fifo2 for reading...\n");
        close(writer); // Close fd1 before exiting
        exit(1);
    }

    printf("\nEnter string: ");
    fgets(str, sizeof(str), stdin); //Get string input

    //Write sentence to pipe1
    write(writer, str, strlen(str)+1);
    printf("\nContents written to pipe...\n");

    //Read sentence from pipe2
    char result[256];
    read(reader, result, sizeof(result));

    //Display the result
    printf("\nReceived from Process 2:\n%s\n", result);

    //Close FIFO's
    close(writer);
    close(reader);
}
