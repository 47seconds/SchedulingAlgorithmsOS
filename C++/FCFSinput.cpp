#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

void calculateCompletionTime(vector<Process> &processes)
{
    int currentTime = 0;
    for (auto &process : processes)
    {
        currentTime = max(currentTime, process.arrivalTime);
        process.completionTime = currentTime + process.burstTime;
        currentTime = process.completionTime;
    }
}

void calculateWaitingTurnaroundTime(vector<Process> &processes)
{
    for (auto &process : processes)
    {
        process.turnaroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.burstTime;
    }
}

void printTable(const vector<Process> &processes)
{
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes)
    {
        cout << process.id << "\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t"
             << process.completionTime << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << endl;
    }
}

void printStatistics(const vector<Process> &processes)
{
    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    double totalThroughput = processes.back().completionTime;
    cout << "\nThroughput: " << processes.size() / totalThroughput << " processes per unit time.\n";
    cout << "Scheduling Length: " << totalThroughput << " units of time.\n";
    for (const auto &process : processes)
    {
        avgWaitingTime += process.waitingTime;
        avgTurnaroundTime += process.turnaroundTime;
    }
    avgWaitingTime /= processes.size();
    avgTurnaroundTime /= processes.size();
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

void printGanttChart(const vector<Process> &processes)
{
    cout << "\nGantt Chart:\n";
    cout << "|";
    for (const auto &process : processes)
    {
        cout << " P" << process.id << " |";
    }
    cout << endl;
    int currentTime = 0;
    for (const auto &process : processes)
    {
        cout << currentTime << "   ";
        currentTime = process.completionTime;
    }
    cout << currentTime << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    // Calculate completion time
    calculateCompletionTime(processes);

    // Calculate waiting and turnaround time
    calculateWaitingTurnaroundTime(processes);

    // Print table
    printTable(processes);

    // Print statistics
    printStatistics(processes);

    // Print Gantt Chart
    printGanttChart(processes);

    return 0;
}
