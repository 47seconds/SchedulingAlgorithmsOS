#include <stdio.h>
#include <string.h>

#define N 100

struct Process
{
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int pid;
    int pr;
};

void update_after_ct(struct Process *p)
{
    p->tat = p->ct - p->at;
    p->wt = p->tat - p->bt;
}

void display(struct Process p)
{
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p.pid, p.at, p.bt, p.pr, p.ct, p.tat, p.wt);
}

float average(struct Process P[], int n, char var[])
{
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        if (!strcmp(var, "at"))
            total += P[i].at;
        else if (!strcmp(var, "bt"))
            total += P[i].bt;
        else if (!strcmp(var, "ct"))
            total += P[i].ct;
        else if (!strcmp(var, "tat"))
            total += P[i].tat;
        else if (!strcmp(var, "wt"))
            total += P[i].wt;
        else if (!strcmp(var, "pr"))
            total += P[i].pr;
    }
    return (float)total / n;
}

void priorityScheduling(struct Process processes[], int n)
{
    int current_time = 0;
    int Remaining_time[N];
    int Process_order[N];
    for (int i = 0; i < n; ++i)
    {
        Process_order[i] = i;
        Remaining_time[i] = processes[i].bt;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (processes[Process_order[j]].pr > processes[Process_order[j + 1]].pr)
            {
                int temp = Process_order[j];
                Process_order[j] = Process_order[j + 1];
                Process_order[j + 1] = temp;
            }
        }
    }
    int completed = 0;
    while (completed < n)
    {
        int highest_priority_index = -1;
        int highest_priority = 9999;
        for (int i = 0; i < n; ++i)
        {
            int process_id = Process_order[i];
            if (processes[process_id].at <= current_time && processes[process_id].pr < highest_priority && Remaining_time[i] > 0)
            {
                highest_priority_index = i;
                highest_priority = processes[process_id].pr;
                Remaining_time[highest_priority_index] = 0;
                current_time += processes[process_id].bt;
                completed++;
                processes[process_id].ct = current_time;
                update_after_ct(&processes[process_id]);
            }
        }
        if (highest_priority_index == -1)
        {
            current_time++;
        }
    }
}
void averageTAT(struct Process processes[], int n)
{
    float averageTAT = 0;
    for (int i = 0; i < n; i++)
    {
        averageTAT = processes[i].tat + averageTAT;
    }
    averageTAT = averageTAT / n;
    printf("Average TAT: %f\n", averageTAT);
}
void averageWT(struct Process processes[], int n)
{
    float averageWT = 0;
    for (int i = 0; i < n; i++)
    {
        averageWT = processes[i].wt + averageWT;
    }
    averageWT = averageWT / n;
    printf("Average WT: %f\n", averageWT);
}
void schdulingLengthThroughput(struct Process processes[], int n)
{
    int schedulingLength = processes[n - 1].ct - processes[0].at;
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
        printf("P%d (%d) | ", i, process[i].ct);
    }
    printf("\n");
}
int main()
{
    int choice;
    printf("Enter 1 for Case 1\nEnter 2 for Case 2\n");
    scanf("%d", &choice);
    if (choice == 2)
    {
        int n;
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        struct Process processes[N];
        for (int i = 0; i < n; i++)
        {
            printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
            scanf("%d %d %d", &processes[i].at, &processes[i].bt, &processes[i].pr);
            processes[i].pid = i + 1;
        }
        priorityScheduling(processes, n);
        printf("pid\tat\tbt\tpr\tct\ttat\twt\n");
        for (int i = 0; i < n; i++)
        {
            display(processes[i]);
        }
        printf("Average waiting time: %f\n", average(processes, n, "wt"));
        printf("Average turnaround time: %f\n", average(processes, n, "tat"));
        averageTAT(processes, n);
        averageWT(processes, n);
        schdulingLengthThroughput(processes, n);
        display_gantt_chart(processes, n);
    }
    else if (choice == 1)
    {
        int n = 5;
        printf("Number of processes: 5\n");
        struct Process processes[N];

        processes[0].pid = 1;
        processes[0].at = 1;
        processes[0].bt = 4;
        processes[0].pr = 5;
        processes[1].pid = 2;
        processes[1].at = 2;
        processes[1].bt = 6;
        processes[1].pr = 2;
        processes[2].pid = 3;
        processes[2].at = 6;
        processes[2].bt = 8;
        processes[2].pr = 3;
        processes[3].pid = 4;
        processes[3].at = 5;
        processes[3].bt = 4;
        processes[3].pr = 7;
        processes[4].pid = 5;
        processes[4].at = 3;
        processes[4].bt = 2;
        processes[4].pr = 4;

        priorityScheduling(processes, n);
        printf("pid\tat\tbt\tpr\tct\ttat\twt\n");
        for (int i = 0; i < n; i++)
        {
            display(processes[i]);
        }
        printf("Average waiting time: %f\n", average(processes, n, "wt"));
        printf("Average turnaround time: %f\n", average(processes, n, "tat"));
        averageTAT(processes, n);
        averageWT(processes, n);
        schdulingLengthThroughput(processes, n);
        display_gantt_chart(processes, n);
    }

    return 0;
}