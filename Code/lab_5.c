#include <stdio.h>

struct priority_scheduling
{
    char process_name;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int priority;
};

int main()
{
    int number_of_process;
    int total = 0;
    int ASCII_number = 65;
    int position;

    float average_waiting_time;
    float average_turnaround_time;

    printf("Enter the total number of Processes: ");
    scanf("%d", &number_of_process);

    struct priority_scheduling process[number_of_process];
    struct priority_scheduling temp_process;

    printf("\nPlease Enter the Burst Time and Priority of each process:\n");

    for (int i = 0; i < number_of_process; i++)
    {
        process[i].process_name = (char)ASCII_number;

        printf("\nEnter the details of process %c\n", process[i].process_name);

        printf("Enter the Burst Time: ");
        scanf("%d", &process[i].burst_time);

        printf("Enter the Priority: ");
        scanf("%d", &process[i].priority);

        ASCII_number++;
    }

    // Sort according to priority (Higher number = Higher priority)
    for (int i = 0; i < number_of_process; i++)
    {
        position = i;

        for (int j = i + 1; j < number_of_process; j++)
        {
            if (process[j].priority > process[position].priority)
            {
                position = j;
            }
        }

        temp_process = process[i];
        process[i] = process[position];
        process[position] = temp_process;
    }

    // Calculate Waiting Time
    process[0].waiting_time = 0;

    total = 0;

    for (int i = 1; i < number_of_process; i++)
    {
        process[i].waiting_time = 0;

        for (int j = 0; j < i; j++)
        {
            process[i].waiting_time += process[j].burst_time;
        }

        total += process[i].waiting_time;
    }

    average_waiting_time = (float)total / number_of_process;

    // Calculate Turnaround Time
    total = 0;

    printf("\n\n");
    printf("---------------------------------------------------------------\n");
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < number_of_process; i++)
    {
        process[i].turn_around_time =
            process[i].burst_time + process[i].waiting_time;

        total += process[i].turn_around_time;

        printf("P%c\t%d\t\t%d\t\t%d\t\t%d\n",
               process[i].process_name,
               process[i].burst_time,
               process[i].priority,
               process[i].waiting_time,
               process[i].turn_around_time);
    }

    average_turnaround_time = (float)total / number_of_process;

    printf("---------------------------------------------------------------\n");
    printf("\nAverage Waiting Time    : %.2f", average_waiting_time);
    printf("\nAverage Turnaround Time : %.2f\n", average_turnaround_time);

    return 0;
}