// partial_sum_threads.cpp
#include <stdio.h>
#include <pthread.h>

#define SIZE 48
#define NUM_THREADS 4

int array[SIZE];
int partial_sums[NUM_THREADS]; 

typedef struct {
    int start;
    int end;
    int index;  // Which thread this is
} ThreadData;

void* partial_sum_thread(void* arg) 
{
    ThreadData* data = (ThreadData*) arg;
    int sum = 0;
    for (int i = data->start; i < data->end; i++) 
    {
        sum += array[i];
    }
    printf("Partial sum is: %d\n", sum);
    partial_sums[data->index] = sum;
    return NULL;
}

int main() {
    // Fill the array with numbers from 1 to SIZE
    for (int i = 0; i < SIZE; i++)
     {
        array[i] = i + 1;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int segment_size = SIZE / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        thread_data[i].start = i * segment_size;
        thread_data[i].end = (i + 1) * segment_size;
        thread_data[i].index = i;
        pthread_create(&threads[i], NULL, partial_sum_thread, &thread_data[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    // Sum up partial sums
    int total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        total_sum += partial_sums[i];
    }

    printf("Total sum: %d\n", total_sum);
    return 0;
}

