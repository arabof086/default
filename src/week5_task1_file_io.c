// week5_task1_file_io.c
// Name: Gamat  Surname: Arabov  Student ID: 251ADB237
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
//
// Build: make lab5
// Run: ./bin/week5_task1_file_io

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(void)
{
    FILE *fp;
    const char *filename = DEFAULT_FILENAME;
    char line[LINE_LEN];

    // Open the file for writing
    printf("Writing lines to %s...\n", filename);

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        perror(filename);
        return 1;
    }

    // Write two lines to the file
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");

    // Close the file after writing
    fclose(fp);

    // Open the same file for reading
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror(filename);
        return 1;
    }

    // Read and print the file contents
    printf("Reading contents:\n");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    // Close the file after reading
    fclose(fp);

    return 0;
}
