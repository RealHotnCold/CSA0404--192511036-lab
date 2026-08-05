#include <stdio.h>
#include <windows.h>

// Shared variable
int counter = 0;

// Mutex handle
HANDLE mutex;

// Function executed by threads
DWORD WINAPI threadFunction(LPVOID arg)
{
    int i;

    for (i = 0; i < 1000000; i++)
    {
        // Lock the mutex
        WaitForSingleObject(mutex, INFINITE);

        // Critical section
        counter++;

        // Unlock the mutex
        ReleaseMutex(mutex);
    }

    return 0;
}

int main()
{
    HANDLE thread1, thread2;

    // Create mutex
    mutex = CreateMutex(NULL, FALSE, NULL);

    if (mutex == NULL)
    {
        printf("Failed to create mutex.\n");
        return 1;
    }

    // Create threads
    thread1 = CreateThread(
        NULL,
        0,
        threadFunction,
        NULL,
        0,
        NULL
    );

    thread2 = CreateThread(
        NULL,
        0,
        threadFunction,
        NULL,
        0,
        NULL
    );

    // Wait for both threads to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Cleanup
    CloseHandle(thread1);
    CloseHandle(thread2);
    CloseHandle(mutex);

    // Print result
    printf("Final Counter Value: %d\n", counter);

    return 0;
}