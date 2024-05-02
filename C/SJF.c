#include <stdio.h>
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
};
void sjf_schedule(struct Process processes[], int n)
{
    int current_time = 0;
    int completed = 0;
    while (completed < n)
    {
        int shortest_index = -1;
        int shortest_burst = 999999; // A large number
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time &&
                processes[i].is_completed == 0)
            {
                if (processes[i].burst_time < shortest_burst)
                {
                    shortest_burst = processes[i].burst_time;
                    shortest_index = i;
                }
            }
        }
        if (shortest_index != -1)
        {
            processes[shortest_index].completion_time = current_time + processes[shortest_index].burst_time;
            processes[shortest_index].turnaround_time = processes[shortest_index].completion_time - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
            processes[shortest_index].is_completed = 1;
            current_time = processes[shortest_index].completion_time;
            completed++;
        }
        else
        {
            current_time++;
        }
    }
}
void display_processes(struct Process processes[], int n)
{
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id,
               processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time,
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
    int choice;
    printf("Enter 1 for Case 1\nEnter 2 for case 2\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int n = 5;
        printf("Number of processes: %d\n", n);
        struct Process processes[n];

        processes[0].id = 1;
        processes[0].arrival_time = 3;
        processes[0].burst_time = 5;
        processes[0].is_completed = 0;
        processes[1].id = 2;
        processes[1].arrival_time = 2;
        processes[1].burst_time = 6;
        processes[1].is_completed = 0;
        processes[2].id = 3;
        processes[2].arrival_time = 1;
        processes[2].burst_time = 3;
        processes[2].is_completed = 0;
        processes[3].id = 4;
        processes[3].arrival_time = 6;
        processes[3].burst_time = 7;
        processes[3].is_completed = 0;
        processes[4].id = 5;
        processes[4].arrival_time = 4;
        processes[4].burst_time = 3;
        processes[4].is_completed = 0;

        sjf_schedule(processes, n);
        display_processes(processes, n);
        averageTAT(processes, n);
        averageWT(processes, n);
        schdulingLengthThroughput(processes, n);
        display_gantt_chart(processes, n);
    }
    else if (choice == 2)
    {
        int n;
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        struct Process processes[n];
        printf("Enter arrival time and burst time for each process:\n");
        for (int i = 0; i < n; i++)
        {
            processes[i].id = i + 1;
            printf("Process %d: ", i + 1);
            scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
            processes[i].is_completed = 0;
        }
        sjf_schedule(processes, n);
        display_processes(processes, n);
        averageTAT(processes, n);
        averageWT(processes, n);
        schdulingLengthThroughput(processes, n);
        display_gantt_chart(processes, n);
    }
    return 0;
}