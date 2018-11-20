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

void read_process(const char*, const char*);
void read_file(const char*, char*);
void write_process(const char*);

std::queue<char> write_queue;
std::thread read_threads[3];
std::thread write_thread;
int run_process = 1; // 0 == stop process, 1 == run process

int main(int argc, char** argv)
{
    std::cout << "Press 'q' to exit consumer program..." << std::endl;

    for(int i = 0; i < 3; i++)
        read_threads[i] = std::thread(read_process, filenames[i], mutexnames[i]);

    write_thread = std::thread(write_process, output_filename);

    char in;
    do {
        std::cin >> in;
    }
    while(in != 'q');
    run_process = 0;

    for(int i = 0; i < 3; i++)
        read_threads[i].join();

    write_thread.join();

    return 0;
}

void read_process(const char* filename, const char* mutex_name)
{
    
    sem_t *mutex = sem_open(mutex_name, O_CREAT);

    if(mutex == 0)
    {
        perror("sem_open");
        exit(0);
    }
    
    char lastread = ' ';

    while(run_process)
    {
        sleep(0.5f);
        sem_wait(mutex);
        read_file(filename, &lastread);
        sem_post(mutex);
    }

    sem_close(mutex);
}

void write_process(const char* filename)
{
    while(run_process)
    {
        while(!write_queue.empty())
        {
            char to_write = write_queue.front();
            write_queue.pop();

            std::ofstream outfile(filename, std::ios_base::app);
            outfile << to_write << std::endl;
            outfile.close();
        }
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

int uinput_thread()
{    

}