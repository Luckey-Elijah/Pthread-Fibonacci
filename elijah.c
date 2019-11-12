#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// limits on the calculations
int MAX_FIB_N = 47;
int MIN_FIB_N = 1;

// Functions used
void nline(void);
void *thread_runner(void *arg);
int check_and_return(int arg_count, const char *arg_value);
int *create_int_array(int array_size);
int free_int_array(int *array_pointer);
void start_prompt(int value);
void exit_prompt(int value);
void print_int_array(int *array, int array_size);

// Global value for all threads to use
int fib_num;
int *fib_seq;

int main(int argc, char const *argv[])
{
    // the size of the fibonacci sequence to the nth degre
    fib_num = check_and_return(argc, argv[1]);

    // a simple user prompt
    start_prompt(fib_num);
    fib_seq = create_int_array(fib_num);

    // populates first two elements of the array
    fib_seq[0] = 0;
    fib_seq[1] = 1;

    // Start threading

    pthread_t thread_x;

    if (pthread_create(&thread_x, NULL, thread_runner, NULL))
    {
        printf("Could not create thread. Exiting.\n");
        return EXIT_FAILURE;
    }
    if (pthread_join(thread_x, NULL))
    {
        printf("Could not join thread. Exiting.\n");
        return EXIT_FAILURE;
    }

    print_int_array(fib_seq, fib_num);
    exit_prompt(fib_num);

    return free_int_array(fib_seq);
}

int free_int_array(int *array_pointer)
{
    free(array_pointer);

    if (array_pointer != NULL)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// allocates space for an int array and returns a pointer
int *create_int_array(int array_size)
{
    int *array_pointer;

    array_pointer = (int *)malloc(sizeof(int) * (array_size));

    // failed init
    if (array_pointer == NULL)
    {
        printf("Could not create array. Exiting.");
        nline();
        exit(EXIT_FAILURE);
    }

    return array_pointer;
}

// just prints a newline
void nline(void)
{
    printf("\n");
    return;
}

// Prompt to display on a succesful run.
void exit_prompt(int value)
{
    printf("+---------------------------------------+\n");
    printf("| Thank you. Now exiting.               |\n");
    printf("+---------------------------------------+\n");
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

// Just a simple user prompt.
void start_prompt(int value)
{
    printf("+---------------------------------------+\n");
    printf("| Calcuating fib(%d) with threading.\t|\n", value);
    printf("+---------------------------------------+\n");
    return;
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

// print content of an integer array in a single line.
// requires a pointer and the size of the array.
void print_int_array(int *array, int array_size)
{
    int i;
    for (i = 0; i < array_size; i++)
    {
        printf("%d ", array[i]);
    }
    nline();
    return;
}