#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fib_thread(void *arg);
int fib(int n);
int sum;

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        printf("USE: .\\elijah [number] \n");
        printf("Improper use, exiting.\n");
        exit(0);
    }

    int fib_num = atoi(argv[1]);

    if (fib_num < 1)
    {
        printf("Please use an integer greater than 0.\n");
        exit(0);
    }

    printf("Welcome!\n");
    printf("calculating fib_n = %d\n", fib_num);

    // Program starts here:

    int *fib_sequence;
    fib_sequence = (int *)malloc(fib_num * sizeof(int));

    // thread identifier
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    int fib_index;
    for (fib_index = 0; fib_index < fib_num; fib_index++)
    {
        pthread_t thread_id;
        // TODO: correct behaviour of thread
        if (pthread_create(&thread_id, &thread_attr, fib_thread, &fib_sequence[fib_index]))
        {
            // error handling
            printf("Could not create thread, exiting.\n");
            exit(0);
        }
        else if (pthread_join(thread_id, NULL))
        {
            // error handling
            printf("Could not join thread, exiting.\n");
            exit(0);
        }
    }
    printf("done:\t%d\n", sum);

    return 0;
}

// [fib_thread] is used for threaded operations
void *fib_thread(void *arg)
{
    sum = fib(atoi(arg));
    printf("sum:\t%d\n", sum);
    pthread_exit(0);
    // return NULL;
}

int fib(int x)
{
    if (x < 2)
    {
        return 1;
    }
    return fib(x - 1) + fib(x - 2);
}
