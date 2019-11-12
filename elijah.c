/*

Created: Elijah Luckey
Course: Operating Systems Concepts COP4610
Date: November 12, 2019

Description: A program that uses the pthread API to generate an integer
    array that is populated with the Fibonnaci sequence to the nth
    degree. The largest nth value is managed by [MAX_FIB_N]
    (which is currently [93]).

Building:
    make
    or
    gcc -g -Wall -pthread -o elijah elijah.c

Use:
    ./elijah [positive integer]

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// limits on the calculations
int MAX_FIB_N = 93;
int MIN_FIB_N = 1;

// Functions used
void nline(void);
void *thread_runner(void *arg);
int check_and_return(int arg_count, const char *arg_value);
unsigned long long int *create_int_array(int array_size);
int free_int_array(unsigned long long int *array);
void print_int_array(unsigned long long int *array, int array_size);

// Global value for all threads to use
int fib_num;
unsigned long long int *fib_seq;

int main(int argc, char const *argv[])
{
    // the size of the fibonacci sequence to the nth degre
    fib_num = check_and_return(argc, argv[1]);

    fib_seq = create_int_array(fib_num);

    // populates first two elements of the array
    fib_seq[0] = 0;
    fib_seq[1] = 1;

    // Start threading section:

    // Cread thread instance
    pthread_t thread_x;

    // Call [pthread_create] and check validity
    if (pthread_create(&thread_x, NULL, thread_runner, NULL))
    {
        printf("Could not create thread. Exiting.\n");
        return EXIT_FAILURE;
    }
    // Call [pthread_join] and check validity
    if (pthread_join(thread_x, NULL))
    {
        printf("Could not join thread. Exiting.\n");
        return EXIT_FAILURE;
    }

    print_int_array(fib_seq, fib_num);

    return free_int_array(fib_seq);
}

// Uses [free()] to cleanup allocated memory of integer arrays.
int free_int_array(unsigned long long int *array)
{
    free(array);

    if (array != NULL)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Allocates space for an int array and returns a pointer
unsigned long long int *create_int_array(int array_size)
{
    fib_seq = (unsigned long long int *)malloc(sizeof(unsigned long long int) * (array_size));

    // failed init
    if (fib_seq == NULL)
    {
        printf("Could not create array. Exiting.");
        nline();
        exit(EXIT_FAILURE);
    }

    return fib_seq;
}

// just prints a newline
void nline(void)
{
    printf("\n");
    return;
}

// Checks [argc] and [argv[1]] values and exits on failure
// Returns the integer input of the value at [argv[1]] if there
int check_and_return(int arg_count, const char *arg_value)
{
    if (arg_count < 2 || arg_count > 2)
    {
        printf("USE: ./elijah [number] \n");
        printf("Improper use, exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Conversion to int with [atoi()]
    int int_value = atoi(arg_value);

    // Check use part b
    if (int_value < MIN_FIB_N || int_value > MAX_FIB_N)
    {
        printf("Please use an integer between [%d] and [%d].\n", MIN_FIB_N, MAX_FIB_N);
        exit(EXIT_FAILURE);
    }

    return int_value;
}

// Used for threading. A fibonacci sequence generator on the global
// arry, fib_seq[].
void *thread_runner(void *arg)
{
    int element;
    for (element = 2; element < fib_num; element++)
    {
        fib_seq[element] = fib_seq[element - 2] + fib_seq[element - 1];
    }
    pthread_exit(EXIT_SUCCESS);
}

// Print content of an integer array in a single line.
// Requires a pointer and the size of the array.
void print_int_array(unsigned long long int *array, int array_size)
{
    unsigned long long int i;
    for (i = 0; i < array_size; i++)
    {
        printf("%lld ", array[i]);
    }
    nline();
    return;
}