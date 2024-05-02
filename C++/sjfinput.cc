#include <bits/stdc++.h>
using namespace std;

class Process
{
private:
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int pid;

public:
    int &operator[](string var)
    {
        if (var == "at")
            return at;
        if (var == "bt")
            return bt;
        if (var == "ct")
            return ct;
        if (var == "tat")
            return tat;
        if (var == "wt")
            return wt;
        return pid;
    }
    void update_after_ct()
    {
        tat = ct - at;
        wt = tat - bt;
    }
    void display()
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid, at, bt, ct, tat, wt);
    }
};

float average(vector<Process> P, string var)
{
    int total = 0;
    for (auto temp : P)
        total += temp[var];
    return (float)total / P.size();
}

float scheduling_length(vector<Process> P);

float throughput(vector<Process> P, string var, int n)
{
    return (float)n / scheduling_length(P);
}

float scheduling_length(vector<Process> P)
{
    int max_ct = INT_MIN;
    int min_at = INT_MAX;
    for (auto temp : P)
    {
        if (temp["ct"] > max_ct)
            max_ct = temp["ct"];
        if (temp["at"] < min_at)
            min_at = temp["at"];
    }
    return max_ct - min_at;
}

void printGanttChart(const vector<pair<int, int>> &gantt)
{
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gantt.size(); i++)
    {
        if (i == 0 || gantt[i].first > gantt[i - 1].second)
            printf("|%d", gantt[i].first);
        printf("|P%d|", i + 1, gantt[i].second);
        printf("%d", gantt[i].second);
    }
    printf("|\n");
}

void SJF(vector<Process> &processes)
{
    int current_time = 0;
    int n = processes.size();
    vector<int> Remaining_time(n);
    vector<int> Process_order(n);
    iota(Process_order.begin(), Process_order.end(), 0);
    sort(Process_order.begin(), Process_order.end(), [&](int a, int b)
         { return processes[a]["bt"] < processes[b]["bt"]; });
    for (int i = 0; i < n; ++i)
        Remaining_time[i] = processes[Process_order[i]]["bt"];
    int completed = 0;
    while (completed < n)
    {
        int shortest_index = -1;
        int shortest_burst = INT_MAX;
        for (int i = 0; i < n; ++i)
        {
            int process_id = Process_order[i];
            if (processes[process_id]["at"] <= current_time && Remaining_time[i] < shortest_burst && Remaining_time[i] > 0)
            {
                shortest_index = i;
                shortest_burst = Remaining_time[i];
            }
        }
        if (shortest_index == -1)
        {
            current_time++;
            continue;
        }
        int process_id = Process_order[shortest_index];
        Remaining_time[shortest_index] = 0;
        current_time += processes[process_id]["bt"];
        if (Remaining_time[shortest_index] == 0)
        {
            completed++;
            processes[process_id]["ct"] = current_time;
            processes[process_id].update_after_ct();
        }
    }
}

int main()
{
    int n = 3; // Number of processes
    vector<Process> P(n);

    // Manually insert the processes with their arrival and burst times
    P[0]["at"] = 0;
    P[0]["bt"] = 5;

    P[1]["at"] = 1;
    P[1]["bt"] = 3;

    P[2]["at"] = 2;
    P[2]["bt"] = 8;

    SJF(P);

    printf("pid\tat\tbt\tct\ttat\twt\n");
    for (int i = 0; i < n; i++)
        P[i].display();
    printf("Average waiting time : %f\n", average(P, "wt"));
    printf("Average turnaround time : %f\n", average(P, "tat"));
    printf("Throughput time : %f\n", throughput(P, "ct", n));
    printf("Scheduling length : %f\n", scheduling_length(P));

    vector<pair<int, int>> gantt;
    gantt.push_back({P[0]["at"], P[0]["ct"]});
    for (int i = 1; i < P.size(); i++)
    {
        gantt.push_back({P[i]["at"], P[i]["ct"]});
    }
    printGanttChart(gantt);

    return 0;
}
