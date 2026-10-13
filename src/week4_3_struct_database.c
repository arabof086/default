#include <stdio.h>
#include <stdlib.h>

// Define the Student structure
struct Student
{
    char name[50];
    int id;
    float grade;
};

int main(void)
{
    int n;

    // Read the number of students
    printf("Enter number of students: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number.\n");
        return 1;
    }

    // Allocate memory for an array of Student records
    struct Student *students =
        malloc(n * sizeof(struct Student));

    // Check if memory allocation was successful
    if (students == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read data for each student
    for (int i = 0; i < n; i++)
    {
        printf("Enter data for student %d: ", i + 1);

        if (scanf("%49s %d %f",
                  students[i].name,
                  &students[i].id,
                  &students[i].grade) != 3)
        {
            printf("Invalid input.\n");
            free(students);
            return 1;
        }
    }

    printf("\n");

    // Print the table header and student records
    printf("%-6s %-11s %s\n", "ID", "Name", "Grade");

    for (int i = 0; i < n; i++)
    {
        printf("%-6d %-11s %.1f\n",
               students[i].id,
               students[i].name,
               students[i].grade);
    }

    // Free dynamically allocated memory
    free(students);

    return 0;
}
