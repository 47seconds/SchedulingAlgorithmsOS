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
        return pid; // corrected this line
    }

    void update_after_ct()
    {
        tat = ct - at;
        wt = tat - bt;
    }

    void display()
    {
        cout << pid << "\t" << at << "\t" << bt << "\t" << ct << "\t" << tat << "\t" << wt << endl;
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
    int max_ct = numeric_limits<int>::min();
    int min_at = numeric_limits<int>::max();
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
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < gantt.size(); i++)
    {
        if (i == 0 || gantt[i].first > gantt[i - 1].second)
        {
            cout << "|" << gantt[i].first;
        }
        cout << "|P" << i + 1 << "|" << gantt[i].second;
    }
    cout << "|\n";
}

void roundRobin(vector<Process> &processes, int quantum)
{
    int current_time = 0;
    int n = processes.size();
    queue<int> ready_queue;
    vector<int> Remaining_time(n);
    vector<int> Process_order(n);
    iota(Process_order.begin(), Process_order.end(), 0);
    // Removed sorting of processes based on arrival time

    for (int i = 0; i < n; ++i)
    {
        Remaining_time[i] = processes[i]["bt"];
    }
    int completed = 0;
    while (completed < n)
    {
        for (int i = 0; i < n; ++i)
        {
            int process_id = Process_order[i];
            if (processes[process_id]["at"] <= current_time && Remaining_time[process_id] > 0)
            {
                ready_queue.push(process_id);
            }
        }
        if (ready_queue.empty())
        {
            current_time++;
            continue;
        }
        int process_id = ready_queue.front();
        ready_queue.pop();
        int remaining = Remaining_time[process_id];
        if (remaining >= quantum)
        {
            current_time += quantum;
            Remaining_time[process_id] -= quantum;
            if (Remaining_time[process_id] == 0)
            {
                completed++;
                processes[process_id]["ct"] = current_time;
                processes[process_id].update_after_ct();
            }
            else
            {
                ready_queue.push(process_id);
            }
        }
        else
        {
            current_time += remaining;
            Remaining_time[process_id] = 0;
            completed++;
            processes[process_id]["ct"] = current_time;
            processes[process_id].update_after_ct();
        }
    }
}

int main()
{
    int n, quantum;
    cin >> n >> quantum;
    int counter = 0;
    vector<Process> P(n);
    for (Process &temp : P)
    {
        temp["pid"] = counter++;
        cin >> temp["at"] >> temp["bt"];
    }
    roundRobin(P, quantum);
    cout << "pid\tat\tbt\tct\ttat\twt\n";
    for (int i = 0; i < n; i++)
    {
        P[i].display();
    }
    cout << "Average waiting time : " << average(P, "wt") << endl;
    cout << "Average turnaround time : " << average(P, "tat") << endl;
    cout << "Throughput time : " << throughput(P, "ct", n) << endl;
    cout << "Scheduling length : " << scheduling_length(P) << endl;
    vector<pair<int, int>> gantt;
    gantt.push_back({P[0]["at"], P[0]["ct"]});
    for (int i = 1; i < P.size(); i++)
    {
        gantt.push_back({P[i]["at"], P[i]["ct"]});
    }
    printGanttChart(gantt);
    return 0;
}
