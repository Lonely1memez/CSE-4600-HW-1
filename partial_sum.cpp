// partial_sum.cpp
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define SIZE 48
#define NUM_PROCESSES 4


int array[SIZE];


int partial_sum(int start, int end) 
{
    int sum = 0;
    for (int i = start; i < end; i++) 
    {
        sum += array[i];
    }
    return sum;
}


int main() 
{
    // Fill the array with numbers from 1 to 20.
    for (int i = 0; i < SIZE; i++) 
    {
        array[i] = i + 1;
    }


    int segment_size = SIZE / NUM_PROCESSES;
    int total_sum = 0;
    int pipes[NUM_PROCESSES][2];



    for(int i = 0; i < NUM_PROCESSES; i++)
    {
        if(pipe(pipes[i]) == -1)
        {
            perror("Pipe Failed");
            return 1;
        }
    }


    for (int i = 0; i < NUM_PROCESSES; i++) 
    {
        pid_t pid = fork();


        if (pid < 0) 
        {
            perror("Fork failed");
            return 1;
        } 
        else if (pid == 0) 
        {  // Child process
            close(pipes[i][0]);

            int start = i * segment_size;
            int end = start + segment_size;
            int part = partial_sum(start, end);

            printf("Partial sum is: %d\n", part);

            write(pipes[i][1], &part, sizeof(part));

            close(pipes[i][1]);
            return 0;  // Return the result or 255 if it exceeds the range.

        }
    }
    // Parent waits for all children and collects results.
    for (int i = 0; i < NUM_PROCESSES; i++) 
    {
        close(pipes[i][1]);

        int part = 0;
        read(pipes[i][0], &part, sizeof(part));
        total_sum += part;
        
        close(pipes[i][0]);
    }


     //waits for all children
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        wait(NULL);
    }

    printf("Total sum: %d\n", total_sum);
    return 0;
}
