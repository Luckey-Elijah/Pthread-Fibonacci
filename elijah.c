#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int MAX_FIB_N = 29;
int MIN_FIB_N = 1;

// Functions used
void *thread_runner(void *arg);
int fib(int n);
int check_and_return(int arg_count, const char *arg_value);
void enter_prompt(int value);
void exit_prompt(int value);

// Global value for all threads to use
int sum;

int main(int argc, char const *argv[])
{
    int fib_num = check_and_return(argc, argv[1]);
    enter_prompt(fib_num);

    // Threading starts up
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    int i;
    for (i = 0; i < fib_num; i++)
    {
        pthread_t thread_id;
        // TODO: correct behaviour of thread
        pthread_create(&thread_id, &thread_attr, thread_runner, &fib_num);
        pthread_join(thread_id, NULL);
    }

    exit_prompt(sum);

    return 0;
}

void exit_prompt(int value)
{
    printf("+---------------------------------------+\n");
    printf("| Goodbye.                              |\n");
    printf("+---------------------------------------+\n");
    return;
}

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

void enter_prompt(int value)
{
    printf("+---------------------------------------+\n");
    printf("| Calcuating fib(%d) with Threading\t|\n", value);
    printf("+---------------------------------------+\n");
    return;
}

// [thread_runner] is used for threaded operations
void *thread_runner(void *arg)
{
    sum = fib(atoi(arg));
    pthread_exit(0);
}

int fib(int x)
{
    if (x < 2)
    {
        return x;
    }
    // printf("%d ", x);
    return fib(x - 1) + fib(x - 2);
}
