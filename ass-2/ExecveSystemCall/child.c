#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No array passed\n");
        exit(1);
    }
    printf("\nProgram ID: %d\n", getpid());
    printf("\nArray in reverse order...\n");
    for(int i=argc-1; i>=1; i--)
    {
        printf("%s\t", argv[i]);
    }
    printf("\n");
}