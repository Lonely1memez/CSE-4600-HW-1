/*
pthreads_demo.cpp
 A very simple example demonstrating the usage of pthreads.
 Compile: g++ -o pthreads_demo pthreads_demo.cpp -lpthread
 Execute: ./pthreads_demo
 Antonio Mora
*/




#include <iostream>
#include <pthread.h>


int N = 10;
pthread_mutex_t lock; // Mutex to protect printing


void* numbers_sum(void* arg) {
   int sum = 0;
   for (int i = 1; i <= N; i++) sum += i;


   pthread_mutex_lock(&lock);
   std::cout << "Sum of the numbers from 1 to " << N << ": " << sum << std::endl;
   pthread_mutex_unlock(&lock);


   pthread_exit(0);
   return NULL;
}


void* numbers_product(void* arg) {
   int product = 1;
   for (int i = 1; i <= N; i++) product *= i;


   pthread_mutex_lock(&lock);
   std::cout << "Product of the numbers from 1 to " << N << ": " << product << std::endl;
   pthread_mutex_unlock(&lock);


   pthread_exit(0);
   return NULL;
}


void* numbers_average(void* arg) {
   double sum = 0;
   for (int i = 1; i <= N; i++) sum += i;
   double average = sum / N;


   pthread_mutex_lock(&lock);
   std::cout << "Average of the numbers from 1 to " << N << ": " << average << std::endl;
   pthread_mutex_unlock(&lock);


   pthread_exit(0);
   return NULL;
}


int main() {
   pthread_t id1, id2, id3;
   pthread_attr_t attr1, attr2, attr3;


   pthread_mutex_init(&lock, NULL);


   pthread_attr_init(&attr1);
   pthread_attr_init(&attr2);
   pthread_attr_init(&attr3);


   pthread_create(&id1, &attr1, numbers_sum, NULL);
   pthread_create(&id2, &attr2, numbers_product, NULL);
   pthread_create(&id3, &attr3, numbers_average, NULL);


   pthread_join(id1, NULL);
   pthread_join(id2, NULL);
   pthread_join(id3, NULL);


   pthread_mutex_destroy(&lock);
   return 0;
}
