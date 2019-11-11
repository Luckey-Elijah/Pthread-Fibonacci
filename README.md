# Fibonacci Sequence with Pthreading

A small C program that uses threading to calculate the Fibonacci sequence.

## Up & Running

```shell
git clone https://github.com/Luckey-Elijah/pthread_fibonacci.git
cd pthread_fibonacci
# build the program
make
./elijah 10
# cleanup the program
make clean
```

The `make` basically runs `gcc -g -Wall -pthread -o elijah elijah.c` in the command line. The `-pthread` flag is necessary for *NIX systems to build with consistency with threads. You also will need a `gcc` compiler.

## Pthread API Use

This program was challenging for me since I have never *really* used function pointers before (some very cool stuff!). Threading in C gets really interesting because of this.
