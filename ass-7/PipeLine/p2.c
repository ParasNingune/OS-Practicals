#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int words=0, lines=0, chars=0, i = 0;
    char sentence[265];

    int reader, writer;
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";

    reader = open(fifo1, O_RDONLY);
    if(reader == -1)
    {
        printf("\nError opening PIPE1 for reading\n");
        exit(1);
    }

    writer = open(fifo2, O_WRONLY);
    if(writer == -1)
    {
        printf("\nError opening PIPE2 for writing\n");
        close(reader);
        exit(1);
    }

    //Read the contents from PIPE1
    read(reader, sentence, sizeof(sentence));

    //Count character, words and lines
    while(sentence[i] != '\0')
    {
        if(sentence[i] == ' ' || sentence[i] == '\n')
        {
            words++;
        }
        else
        {
            chars++;
        }
        if(sentence[i] == '\n')
        {
            lines++;
        }
        i++;
    }
    words++;
    lines++;

    printf("\nCharacters: %d\n", chars);
    printf("\nWords: %d\n", words);
    printf("\nLines: %d\n\n", lines);

    //Write result to Pipe2
    char result[256];
    snprintf(result, sizeof(result), "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
    write(writer, result, strlen(result)+1);

    // Close FIFOs
    close(reader);
    close(writer);
}