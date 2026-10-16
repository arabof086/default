// week5_task3_student_management_system.c
// Name: Gamat  Surname: Arabov  Student ID: 251ADB237
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
//
// Build: make lab5
// Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student
{
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int read_line(const char *prompt, char *buf, size_t size);

static int parse_int(const char *text, int *value)
{
    char extra;

    if (sscanf(text, " %d %c", value, &extra) != 1)
    {
        return 0;
    }

    return 1;
}

static int parse_float(const char *text, float *value)
{
    char extra;

    if (sscanf(text, " %f %c", value, &extra) != 1)
    {
        return 0;
    }

    return 1;
}

int read_line(const char *prompt, char *buf, size_t size)
{
    size_t len;
    int ch;

    if (prompt != NULL)
    {
        printf("%s", prompt);
    }

    if (fgets(buf, size, stdin) == NULL)
    {
        return 0;
    }

    len = strlen(buf);

    if (len > 0 && buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
    }
    else
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }

    return 1;
}

int load_students(Student arr[], int max)
{
    FILE *fp = fopen(DATA_FILE, "r");
    char line[LINE_LEN];
    int count = 0;

    if (fp == NULL)
    {
        return 0;
    }

    while (count < max && fgets(line, sizeof(line), fp) != NULL)
    {
        Student temp;

        if (sscanf(line, "%49[^,],%d,%f",
                   temp.name,
                   &temp.id,
                   &temp.gpa) == 3)
        {
            arr[count] = temp;
            count++;
        }
    }

    fclose(fp);

    return count;
}

int save_students(const Student arr[], int count)
{
    FILE *fp = fopen(DATA_FILE, "w");

    if (fp == NULL)
    {
        return -1;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s,%d,%.2f\n",
                arr[i].name,
                arr[i].id,
                arr[i].gpa);
    }

    fclose(fp);

    return 0;
}

void add_student(Student arr[], int *count)
{
    char name[NAME_LEN];
    char input[LINE_LEN];
    int id;
    float gpa;

    if (*count >= MAX_STUDENTS)
    {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    if (!read_line("Enter name: ", name, sizeof(name)))
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    if (name[0] == '\0' || strchr(name, ',') != NULL)
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    if (!read_line("Enter ID: ", input, sizeof(input)) ||
        !parse_int(input, &id))
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    if (!read_line("Enter GPA: ", input, sizeof(input)) ||
        !parse_float(input, &gpa) ||
        gpa < 0.0f ||
        gpa > 4.0f)
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    snprintf(arr[*count].name, NAME_LEN, "%s", name);
    arr[*count].id = id;
    arr[*count].gpa = gpa;

    (*count)++;

    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count)
{
    if (count == 0)
    {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");

    for (int i = 0; i < count; i++)
    {
        printf("%-5d %-20s %.2f\n",
               arr[i].id,
               arr[i].name,
               arr[i].gpa);
    }
}

int main(void)
{
    Student students[MAX_STUDENTS];
    int count;
    char input[LINE_LEN];
    int option;
    int running = 1;

    count = load_students(students, MAX_STUDENTS);

    printf("Loaded %d student(s) from students.txt\n", count);

    while (running)
    {
        printf("\n");
        printf("=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        if (!read_line("Select an option: ", input, sizeof(input)))
        {
            if (save_students(students, count) != 0)
            {
                printf("Error saving data.\n");
                return 1;
            }

            printf("Data saved. Goodbye!\n");
            break;
        }

        if (!parse_int(input, &option))
        {
            printf("Invalid option.\n");
            continue;
        }

        switch (option)
        {
            case 1:
                list_students(students, count);
                break;

            case 2:
                add_student(students, &count);
                break;

            case 3:
                if (save_students(students, count) != 0)
                {
                    printf("Error saving data.\n");
                    return 1;
                }

                printf("Data saved. Goodbye!\n");
                running = 0;
                break;

            default:
                printf("Invalid option.\n");
                break;
        }
    }

    return 0;
}
