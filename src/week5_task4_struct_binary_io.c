// week5_task4_struct_binary_io.c   (BONUS)
// Name: Gamat  Surname: Arabov  Student ID: 251ADB237
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5
// Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student
{
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes required by the autograder
int save_student_binary(const Student *s, const char *filename);
int load_student_binary(const char *filename, Student *out);
long file_size(const char *filename);

int save_student_binary(const Student *s, const char *filename)
{
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        return -1;
    }

    if (fwrite(s, sizeof(Student), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }

    fclose(fp);

    return 0;
}

int load_student_binary(const char *filename, Student *out)
{
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        return -1;
    }

    if (fread(out, sizeof(Student), 1, fp) != 1)
    {
        fclose(fp);
        return -1;
    }

    fclose(fp);

    return 0;
}

long file_size(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    long size;

    if (fp == NULL)
    {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0)
    {
        fclose(fp);
        return -1;
    }

    size = ftell(fp);

    fclose(fp);

    return size;
}

int main(void)
{
    Student s1 = {0};
    Student loaded = {0};

    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    printf("Saving student in binary format...\n");

    if (save_student_binary(&s1, bin_file) != 0)
    {
        printf("Error saving binary file.\n");
        return 1;
    }

    printf("Loading student from binary file...\n");

    if (load_student_binary(bin_file, &loaded) != 0)
    {
        printf("Error loading binary file.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n",
           loaded.name,
           loaded.age,
           loaded.gpa);

    FILE *txt_fp = fopen(txt_file, "w");

    if (txt_fp == NULL)
    {
        printf("Error saving text file.\n");
        return 1;
    }

    fprintf(txt_fp, "%s %d %.2f\n",
            s1.name,
            s1.age,
            s1.gpa);

    fclose(txt_fp);

    long text_size = file_size(txt_file);
    long binary_size = file_size(bin_file);

    if (text_size == -1 || binary_size == -1)
    {
        printf("Error reading file size.\n");
        return 1;
    }

    printf("Text file size: %ld bytes\n", text_size);
    printf("Binary file size: %ld bytes\n", binary_size);

    return 0;
}
