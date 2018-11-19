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
#define MUTEX_PERM 0777

/**
 * mutex.value == 0 --> locked
 * mutex.value == 1 --> unlocked
 * */
sem_t *mutex;

int main(void)
{
    // Initialize Mutexs
    mutex = sem_open(MUTEX_NAME, O_CREAT | O_EXCL, MUTEX_PERM, 1);

    int i;
    char number;
    FILE *output;
    while (1)
    {
        for (i = 58; i < 127; i++)
        {
            sem_wait(mutex); //START crit section            
            output = fopen("./output3.txt", "w");
            fprintf(output, "%c\n", i);
            fclose(output);
            sem_post(mutex); // END crit section 
            sleep(120);
        }
    }
    return 1;
}