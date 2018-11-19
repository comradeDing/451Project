// Erich Dingeldein
#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

const char* filenames[] = {
    "./output1.txt",
    "./output2.txt",
    "./output3.txt"
};

const char* output_filename = "./output4.txt";

const char* mutexnames[] = {
    "/out1mutex",
    "/out2mutex",
    "/out3mutex"
};

void read_thread(const char*, const char*);
void read_file(const char*, char*);
void lock(sem_t*);
void unlock(sem_t*);

std::queue<char> write_queue;
std::thread read_threads[3];

int main(int argc, char** argv)
{
    for(int i = 0; i < 3; i++)
        read_threads[i] = std::thread(read_thread, filenames[i], mutexnames[i]);

    while(1)
    {
        while(!write_queue.empty())
        {
            char to_write = write_queue.front();
            write_queue.pop();

            std::ofstream outfile(output_filename, std::ios_base::app);
            outfile << to_write << std::endl;
            outfile.close();
        }
    }

    for(int i = 0; i < 3; i++)
        read_threads[i].join();

    return 0;
}

void read_thread(const char* filename, const char* mutex_name)
{
    
    sem_t *mutex = sem_open(mutex_name, O_CREAT);

    if(mutex == 0)
    {
        perror("sem_open");
        exit(0);
    }
    
    char lastread = ' ';

    while(1)
    {
        sleep(0.5f);
        sem_wait(mutex);
        read_file(filename, &lastread);
        sem_post(mutex);
    }
}

void read_file(const char* filename, char *lastread)
{
    char temp;
    std::ifstream infile(filename, std::ios_base::in);
    infile >> temp;
    if(temp == *lastread)
        return;
    std::cout << filename << ": " << temp << std::endl;

    write_queue.push(temp);
    *lastread = temp;
}