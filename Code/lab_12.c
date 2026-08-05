#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NUM_PHILOSOPHERS 5

HANDLE chopsticks[NUM_PHILOSOPHERS];

DWORD WINAPI philosopherLifeCycle(LPVOID arg)
{
    int id = *(int *)arg;

    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    while (1)
    {
        // Think
        printf("Philosopher %d is thinking...\n", id);
        Sleep(rand() % 3000 + 1000);

        // Pick up left chopstick
        WaitForSingleObject(chopsticks[left_chopstick], INFINITE);

        // Pick up right chopstick
        WaitForSingleObject(chopsticks[right_chopstick], INFINITE);

        // Eat
        printf("Philosopher %d is eating...\n", id);
        Sleep(rand() % 3000 + 1000);

        // Put down chopsticks
        ReleaseMutex(chopsticks[left_chopstick]);
        ReleaseMutex(chopsticks[right_chopstick]);
    }

    return 0;
}

int main()
{
    HANDLE philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Create mutexes (one for each chopstick)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        chopsticks[i] = CreateMutex(NULL, FALSE, NULL);

        if (chopsticks[i] == NULL)
        {
            printf("Failed to create mutex.\n");
            return 1;
        }
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosopher_ids[i] = i;

        philosophers[i] = CreateThread(
            NULL,
            0,
            philosopherLifeCycle,
            &philosopher_ids[i],
            0,
            NULL
        );

        if (philosophers[i] == NULL)
        {
            printf("Failed to create thread.\n");
            return 1;
        }
    }

    // Wait for all philosopher threads (they run forever)
    WaitForMultipleObjects(
        NUM_PHILOSOPHERS,
        philosophers,
        TRUE,
        INFINITE
    );

    // Cleanup
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        CloseHandle(philosophers[i]);
        CloseHandle(chopsticks[i]);
    }

    return 0;
}