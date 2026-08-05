#include <stdio.h>

// Descending Sort
void rsort(int a[], int n)
{
    int i, j, t;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i] < a[j])
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

// Ascending Sort
void sort(int a[], int n)
{
    int i, j, t;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

// Best Fit Allocation
void bestfit(int mp[], int p[], int m, int n)
{
    int j = 0;

    for (int i = 0; i < n && j < m; i++)
    {
        if (mp[i] >= p[j])
        {
            printf("\nProcess %d fits in Memory Partition %d",
                   p[j], mp[i]);

            mp[i] -= p[j];
            j++;
            i--;
        }
    }

    for (int i = j; i < m; i++)
    {
        printf("\nProcess %d must wait.", p[i]);
    }
}

// First Fit
void firstfit(int mp[], int p[], int m, int n)
{
    bestfit(mp, p, m, n);
}

// Worst Fit
void worstfit(int mp[], int p[], int m, int n)
{
    rsort(mp, n);
    sort(p, m);
    bestfit(mp, p, m, n);
}

int main()
{
    int m, n;
    int mp[20], p[20];
    int ch;

    printf("Number of Memory Partitions: ");
    scanf("%d", &n);

    printf("Number of Processes: ");
    scanf("%d", &m);

    printf("\nEnter the Memory Partition Sizes:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &mp[i]);
    }

    printf("\nEnter the Process Sizes:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &p[i]);
    }

    printf("\n1. First Fit");
    printf("\n2. Best Fit");
    printf("\n3. Worst Fit");
    printf("\nEnter your Choice: ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        firstfit(mp, p, m, n);
        break;

    case 2:
        sort(mp, n);
        sort(p, m);
        bestfit(mp, p, m, n);
        break;

    case 3:
        worstfit(mp, p, m, n);
        break;

    default:
        printf("Invalid Choice!");
    }

    return 0;
}