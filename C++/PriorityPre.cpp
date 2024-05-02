#include <bits/stdc++.h>
using namespace std;

class Process
{
private:
    int at;
    int bt;
    int ct;
    int tat, wt;
    int pid;
    int pr;

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
        if (var == "pr")
            return pr;
        return pid;
    }

    void update_after_ct()
    {
        tat = ct - at;
        wt = tat - bt;
    }

    void display()
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid, at, bt, pr, ct, tat, wt);
    }
};

float average(vector<Process> P, string var)
{
    int total = 0;
    for (auto temp : P)
    {
        total += temp[var];
    }
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
        {
            max_ct = temp["ct"];
        }
        if (temp["at"] < min_at)
        {
            min_at = temp["at"];
        }
    }
    return max_ct - min_at;
}

void printGanttChart(const vector<pair<int, int>> &gantt)
{
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gantt.size(); i++)
    {
        if (i == 0 || gantt[i].first > gantt[i - 1].second)
        {
            printf("|%d", gantt[i].first);
        }
        printf("|P%d|%d", i + 1, gantt[i].second);
    }
    printf("|\n");
}

void priorityScheduling(vector<Process> &processes)
{
    int current_time = 0;
    int n = processes.size();
    vector<int> Remaining_time(n);
    vector<int> Process_order(n);
    iota(Process_order.begin(), Process_order.end(), 0);
    sort(Process_order.begin(), Process_order.end(), [&](int a, int b)
         { return processes[a]["pr"] < processes[b]["pr"]; });
    for (int i = 0; i < n; ++i)
    {
        Remaining_time[i] = processes[Process_order[i]]["bt"];
    }
    int completed = 0;
    while (completed < n)
    {
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;
        for (int i = 0; i < n; ++i)
        {
            int process_id = Process_order[i];
            if (processes[process_id]["at"] <= current_time && processes[process_id]["pr"] < highest_priority && Remaining_time[i] > 0)
            {
                highest_priority_index = i;
                highest_priority = processes[process_id]["pr"];
            }
        }
        if (highest_priority_index != -1)
        {
            int process_id = Process_order[highest_priority_index];
            Remaining_time[highest_priority_index] = 0;
            current_time += processes[process_id]["bt"];
            completed++;
            processes[process_id]["ct"] = current_time;
            processes[process_id].update_after_ct();
        }
        else
        {
            current_time++;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int counter = 0;
    vector<Process> P(n);
    for (Process &temp : P)
    {
        temp["pid"] = counter++;
        cin >> temp["at"] >> temp["bt"] >> temp["pr"];
    }
    priorityScheduling(P);
    printf("pid\tat\tbt\tpr\tct\ttat\twt\n");
    for (int i = 0; i < n; i++)
    {
        P[i].display();
    }
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
