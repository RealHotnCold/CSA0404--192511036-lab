#include <stdio.h>
#include <windows.h>

HANDLE mutex, writeBlock;

int data = 0;
int readersCount = 0;

DWORD WINAPI reader(LPVOID arg)
{
    int i = 0;

    while (i < 10)
    {
        // Entry Section
        WaitForSingleObject(mutex, INFINITE);

        readersCount++;

        if (readersCount == 1)
        {
            WaitForSingleObject(writeBlock, INFINITE);
        }

        ReleaseSemaphore(mutex, 1, NULL);

        // Reading
        printf("Reader reads data: %d\n", data);

        // Exit Section
        WaitForSingleObject(mutex, INFINITE);

        readersCount--;

        if (readersCount == 0)
        {
            ReleaseSemaphore(writeBlock, 1, NULL);
        }

        ReleaseSemaphore(mutex, 1, NULL);

        Sleep(500);

        i++;
    }

    return 0;
}

DWORD WINAPI writer(LPVOID arg)
{
    int i = 0;

    while (i < 10)
    {
        WaitForSingleObject(writeBlock, INFINITE);

        // Writing
        data++;

        printf("Writer writes data: %d\n", data);

        ReleaseSemaphore(writeBlock, 1, NULL);

        Sleep(1000);

        i++;
    }

    return 0;
}

int main()
{
    HANDLE readerThread;
    HANDLE writerThread;

    // Create semaphores
    mutex = CreateSemaphore(NULL, 1, 1, NULL);
    writeBlock = CreateSemaphore(NULL, 1, 1, NULL);

    if (mutex == NULL || writeBlock == NULL)
    {
        printf("Failed to create semaphores.\n");
        return 1;
    }

    // Create threads
    readerThread = CreateThread(
        NULL,
        0,
        reader,
        NULL,
        0,
        NULL
    );

    writerThread = CreateThread(
        NULL,
        0,
        writer,
        NULL,
        0,
        NULL
    );

    // Wait for threads
    WaitForSingleObject(readerThread, INFINITE);
    WaitForSingleObject(writerThread, INFINITE);

    // Cleanup
    CloseHandle(readerThread);
    CloseHandle(writerThread);
    CloseHandle(mutex);
    CloseHandle(writeBlock);

    return 0;
}