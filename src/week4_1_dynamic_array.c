#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;

    // Read the number of elements from the user
    printf("Enter number of elements: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    // Allocate memory dynamically for the integer array
    int *array = malloc(n * sizeof(int));

    // Check if memory allocation was successful
    if (array == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);

    long long sum = 0;

    // Read all integers and calculate their sum
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &array[i]) != 1)
        {
            printf("Invalid input.\n");
            free(array);
            return 1;
        }

        sum += array[i];
    }

    // Calculate the average using floating-point division
    double average = (double)sum / n;

    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    // Free dynamically allocated memory
    free(array);

    return 0;
}
