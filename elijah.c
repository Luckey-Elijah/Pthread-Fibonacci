#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int MAX_FIB_N = 29;
int MIN_FIB_N = 1;

// Functions used
void nline(void);
void *thread_runner(void *arg);
int fib(int n);
int check_and_return(int arg_count, const char *arg_value);
int *create_int_array(int array_size);
void start_prompt(int value);
void exit_prompt(int value);
void print_int_array(int *array, int array_size);

// Global value for all threads to use
int sum;

int main(int argc, char const *argv[])
{
    // the size of the fibonacci sequence to the nth degre
    int fib_num = check_and_return(argc, argv[1]);

    // a simple user prompt
    start_prompt(fib_num);

    // allocated a space for an array
    int *fib_seq = create_int_array(fib_num);

    // populates first two elements of the array
    fib_seq[0] = 0;
    fib_seq[1] = 1;

    int i;
    for (i = 2; i < fib_num; i++)
    {
        fib_seq[i] = fib_seq[i - 2] + fib_seq[i - 1];
    }

    nline();
    print_int_array(fib_seq, fib_num);
    nline();

    exit_prompt(sum);

    return 0;
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
        exit(0);
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
        exit(0);
    }

    // Conversion to int with [atoi()]
    int int_value = atoi(arg_value);

    // Check use part b
    if (int_value < MIN_FIB_N || int_value > MAX_FIB_N)
    {
        printf("Please use an integer between [%d] and [%d].\n", MIN_FIB_N, MAX_FIB_N);
        exit(0);
    }

    return int_value;
}

// after running [check_and_return], this is called
void start_prompt(int value)
{
    printf("+---------------------------------------+\n");
    printf("| Calcuating fib(%d) with threading.\t|\n", value);
    printf("+---------------------------------------+\n");
    return;
}

// TODO: [thread_runner]
void *thread_runner(void *arg)
{
    pthread_exit(0);
}

// a reusable recursive use for calculatin a fibonacci sequence.
int fib(int x)
{
    if (x < 2)
    {
        return x;
    }
    return fib(x - 1) + fib(x - 2);
}

// print content of an integer array in a single line.
// requires a point and the size of the array.
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