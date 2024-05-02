#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define BUFFER_SIZE 10
#define ITEM_COUNT 5

int turn = 0;
bool flag[2] = {false, false};

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

// Peterson's lock and unlock functions for mutual exclusion
void peterson_lock(int thread_id)
{
    int other = 1 - thread_id;
    flag[thread_id] = true;
    turn = thread_id;
    while (flag[other] && turn == thread_id)
        ; // Busy-wait until the lock is released
}

void peterson_unlock(int thread_id)
{
    flag[thread_id] = false;
}

void display_buffer()
{
    printf("Buffer: [");
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("]\n");
}

// Producer thread function
void *producer(void *arg)
{
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        while (count == BUFFER_SIZE)
            ;

        peterson_lock(0); // Lock for critical section

        buffer[in] = 100 + i;
        printf("Producer produced: %d\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        display_buffer();

        peterson_unlock(0); // Unlock the critical section
    }

    return NULL;
}

// Consumer thread function
void *consumer(void *arg)
{
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        while (count == 0)
            ;

        peterson_lock(1); // Lock for critical section

        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;
        count--;

        display_buffer();

        peterson_unlock(1); // Unlock the critical section
    }

    return NULL;
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
