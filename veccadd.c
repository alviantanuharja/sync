#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 100

typedef struct {
    int start;
    int end;
    int* vector1;
    int* vector2;
    int* result;
} ThreadData;

void* vectorAddition(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int start = data->start;
    int end = data->end;
    int* vector1 = data->vector1;
    int* vector2 = data->vector2;
    int* result = data->result;

    for (int i = start; i <= end; i++) {
        result[i] = vector1[i] + vector2[i];
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num_threads> <vector_length>\n", argv[0]);
        return 1;
    }

    int numThreads = atoi(argv[1]);
    int vectorLength = atoi(argv[2]);

    if (numThreads <= 0 || numThreads > MAX_THREADS) {
        printf("Invalid number of threads. Please choose a value between 1 and %d.\n", MAX_THREADS);
        return 1;
    }

    if (vectorLength <= 0) {
        printf("Invalid vector length. Please choose a positive value.\n");
        return 1;
    }

    int* vector1 = (int*)malloc(vectorLength * sizeof(int));
    int* vector2 = (int*)malloc(vectorLength * sizeof(int));
    int* result = (int*)malloc(vectorLength * sizeof(int));

    // Initialize vectors with arbitrary values
    for (int i = 0; i < vectorLength; i++) {
        vector1[i] = i + 1;
        vector2[i] = i + 1;
    }

    pthread_t threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];
    struct timeval start_time, end_time;

    gettimeofday(&start_time, NULL);

    int blockSize = vectorLength / numThreads;
    int remainder = vectorLength % numThreads;
    int currentIndex = 0;

    for (int i = 0; i < numThreads; i++) {
        threadData[i].start = currentIndex;
        threadData[i].end = currentIndex + blockSize - 1;

        if (remainder > 0) {
            threadData[i].end++;
            remainder--;
        }

        threadData[i].vector1 = vector1;
        threadData[i].vector2 = vector2;
        threadData[i].result = result;

        pthread_create(&threads[i], NULL, vectorAddition, (void*)&threadData[i]);

        currentIndex = threadData[i].end + 1;
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);

    double executionTime = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    double performance = 1.0 / executionTime;

    // printf("Vector addition completed.\n");
    // printf("Execution time: %.4f seconds\n", executionTime);
    // printf("Performance: %.4f operations per second\n", performance);

    printf("%.4f\n", performance);


    free(vector1);
    free(vector2);
    free(result);

    return 0;
}
