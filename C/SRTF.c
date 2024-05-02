#include <stdio.h>

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};
void SRTF(struct Process processes[], int n)
{
    int remaining_time[n];
    int smallest, time = 0, completed = 0, min = 9999;
    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].burst_time;
    while (completed != n)
    {
        smallest = -1;
        min = 9999;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && remaining_time[i] < min && remaining_time[i] > 0)
            {
                min = remaining_time[i];
                smallest = i;
            }
        }
        if (smallest == -1)
        {
            time++;
            continue;
        }
        remaining_time[smallest]--;
        time++;
        if (remaining_time[smallest] == 0)
        {
            completed++;
            processes[smallest].completion_time = time;
            processes[smallest].turnaround_time = processes[smallest].completion_time - processes[smallest].arrival_time;
            processes[smallest].waiting_time = processes[smallest].turnaround_time - processes[smallest].burst_time;
        }
    }
}
void printTable(struct Process processes[], int n)
{
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
    }
}
void averageTAT(struct Process processes[], int n)
{
    float averageTAT = 0;
    for (int i = 0; i < n; i++)
    {
        averageTAT = processes[i].turnaround_time + averageTAT;
    }
    averageTAT = averageTAT / n;
    printf("Average TAT: %f\n", averageTAT);
}
void averageWT(struct Process processes[], int n)
{
    float averageWT = 0;
    for (int i = 0; i < n; i++)
    {
        averageWT = processes[i].waiting_time + averageWT;
    }
    averageWT = averageWT / n;
    printf("Average WT: %f\n", averageWT);
}
void schdulingLengthThroughput(struct Process processes[], int n)
{
    int schedulingLength = processes[n - 1].completion_time - processes[0].arrival_time;
    printf("Scheduling Length: %f\n", schedulingLength);
    float throughput;
    throughput = n / schedulingLength;
    printf("Throughput: %f\n", throughput);
}
void display_gantt_chart(struct Process process[], int n)
{
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d (%d) | ", i, process[i].completion_time);
    }
    printf("\n");
}
int main()
{
    int n, choice;
    printf("enter 1 for Case 1\n");
    printf("enter 2 for Case 2\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        n = 4;
        struct Process processes[] = {{1, 0, 5}, {2, 1, 3}, {3, 2, 8}, {4, 3, 6}};
        SRTF(processes, n);
        printTable(processes, n);
        averageTAT(processes, n);
        averageWT(processes, n);
        schdulingLengthThroughput(processes, n);
        display_gantt_chart(processes, n);
    }
    else if (choice == 2)
    {
        printf("Enter number of processes: ");
        scanf("%d", &n);
        struct Process processes[n];
        for (int i = 0; i < n; i++)
        {
            processes[i].pid = i + 1;
            printf("Enter arrival time and burst time for process %d: ", i + 1);
            scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        }
        SRTF(processes, n);
        printTable(processes, n);
        averageTAT(processes, n);
        averageWT(processes, n);
        schdulingLengthThroughput(processes, n);
        display_gantt_chart(processes, n);
    }
    else
    {
        printf("Invalid choice.\n");
    }
    return 0;
}