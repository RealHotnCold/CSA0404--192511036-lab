#include <stdio.h>
#include <windows.h>
#include <string.h>

#define SHM_SIZE 1024

int main()
{
    HANDLE hMapFile;
    char *pBuf;

    // Create a named shared memory object
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // Use system paging file
        NULL,                   // Default security
        PAGE_READWRITE,         // Read/Write access
        0,
        SHM_SIZE,
        "MySharedMemory"        // Name of shared memory
    );

    if (hMapFile == NULL)
    {
        printf("Could not create file mapping (%lu)\n", GetLastError());
        return 1;
    }

    // Map the shared memory into the process address space
    pBuf = (char *)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        SHM_SIZE
    );

    if (pBuf == NULL)
    {
        printf("Could not map view (%lu)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write data
    strcpy(pBuf, "Hello, shared memory!");

    printf("Data written to shared memory: %s\n", pBuf);

    // Cleanup
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}