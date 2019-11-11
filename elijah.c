#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Functions used
void *thread_runner(void *arg);
int fib(int n);
void main_prompt(int num);

// Global value for all threads to use
int sum;

int main(int argc, char const *argv[])
{
    // Check use part a
    if (argc <= 1)
    {
        printf("USE: .\\elijah [number] \n");
        printf("Improper use, exiting.\n");
        exit(0);
    }

    // Conversion to int with [atoi()]
    int fib_num = atoi(argv[1]);

    // Check use part b
    if (fib_num < 1 || fib_num > 29)
    {
        printf("Please use an integer between 0 and 30.\n");
        exit(0);
    }

    // prompt after checks
    main_prompt(fib_num);

    // Program starts here:

    int *fib_sequence;
    fib_sequence = (int *)malloc(fib_num * sizeof(int));

    // thread identifier
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    int i;
    for (i = 0; i < fib_num; i++)
    {
        pthread_t thread_id;
        // TODO: correct behaviour of thread
        pthread_create(&thread_id, &thread_attr, thread_runner, &fib_sequence[i]);
        pthread_join(thread_id, NULL);
    }
    printf("done:\t%d\n", sum);

    return 0;
}

void main_prompt(int num)
{
    printf("Welcome!\n");
    printf("calculating fib_n = %d\n", num);

    printf("+-------------------------------+\n");
    printf("| Calcuating %d with Threading\t|\n", num);
    printf("+-------------------------------+\n");
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
