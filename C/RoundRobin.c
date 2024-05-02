#include <stdio.h>

typedef struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void roundRobin(Process processes[], int n, int quantum)
{
    int remaining_time[n];
    int current_time = 0;
    int completed = 0;
    int time_quantum = quantum;
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = processes[i].burst_time;
    }
    while (completed < n)
    {
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (remaining_time[i] > 0)
            {
                flag = 1;
                if (remaining_time[i] > time_quantum)
                {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
                else
                {
                    current_time += remaining_time[i];
                    processes[i].completion_time = current_time;
                    remaining_time[i] = 0;
                    completed++;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                }
            }
        }
        if (flag == 0)
        {
            current_time++;
        }
    }
}
void printTable(Process processes[], int n)
{
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrival_time,
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
    int n, quantum, choice;
    printf("enter 1 for Case 1\n");
    printf("enter 2 for Case 2\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        n = 4;
        quantum = 2;
        Process processes[] = {{1, 0, 4}, {2, 1, 5}, {3, 2, 2}, {4, 3, 1}};
        roundRobin(processes, n, quantum);
        printTable(processes, n);
        averageTAT(processes, n);
        averageWT(processes, n);
        schdulingLengthThroughput(processes, n);
        display_gantt_chart(processes, n);
    }
    else if (choice == 2)
    {
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        printf("Enter the time quantum for Round Robin: ");
        scanf("%d", &quantum);
        Process processes[n];
        for (int i = 0; i < n; i++)
        {
            printf("Enter arrival time and burst time for process %d: ", i + 1);
            scanf("%d", &processes[i].arrival_time);
            scanf("%d", &processes[i].burst_time);
            processes[i].pid = i + 1;
        }
        roundRobin(processes, n, quantum);
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