/************************************************/
/* Produces a character once every 120 seconds. */
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MUTEX_NAME "/out3mutex"
#define FLAG_NAME "/out3flag"
#define MUTEX_PERM S_IRWXG

void mutex_init();
void lock();
void unlock();

/**
 * mutex.value == 0 --> locked
 * mutex.value == 1 --> unlocked
 * flag.value == 0 --> old value
 * flag.value == 1 --> new value
 * */
sem_t *mutex, *flag;

int main(void)
{
    // Initialize Mutexs
    mutex_init();

    int i;
    char number;
    FILE *output;
    while (1)
    {
        for (i = 58; i < 127; i++)
        {
            lock(); //START crit section            
            output = fopen("./output3.txt", "w");
            fprintf(output, "%c\n", i);
            fclose(output);
            unlock(); // END crit section 
            sleep(120);
        }
    }
    return 1;
}

void mutex_init()
{
    mutex = sem_open(MUTEX_NAME, O_CREAT, MUTEX_PERM, 1);
    flag = sem_open(FLAG_NAME, O_CREAT, MUTEX_PERM, 0);
}

void lock()
{
    sem_wait(mutex);
}

void unlock()
{
    sem_post(mutex);
    sem_post(flag);
}