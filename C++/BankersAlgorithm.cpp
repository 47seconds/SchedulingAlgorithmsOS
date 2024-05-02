#include <iostream>
#include <vector>
using namespace std;

class Process
{
public:
    int id;
    int num_of_resources;
    int *resources_assigned, *resources_max_need;
    Process(int id, int a, int b, int c, int d) : id(id)
    {
        resources_assigned = new int[2];
        resources_max_need = new int[2];
        resources_assigned[0] = a;
        resources_assigned[1] = b;
        resources_max_need[0] = c;
        resources_max_need[1] = d;
    }
    Process(int id, int num_of_resources) : id(id), num_of_resources(num_of_resources)
    {
        resources_assigned = new int[num_of_resources];
        resources_max_need = new int[num_of_resources];
        for (int i = 0; i < num_of_resources; i++)
        {
            cout << "Enter assigned R" << i << " for process P" << id << " : ";
            cin >> resources_assigned[i];
        }
        for (int i = 0; i < num_of_resources; i++)
        {
            cout << "Enter max needed R" << i << " for process P" << id << " : ";
            cin >> resources_max_need[i];
        }
    }
};

bool enough_resources(vector<int> &available_resources, Process process)
{
    for (int i = 0; i < available_resources.size(); i++)
    {
        if (available_resources[i] + process.resources_assigned[i] < process.resources_max_need[i])
            return false;
    }
    return true;
}

void execute_process(Process &process, int to_execute, vector<int> &available_resources, vector<bool> &executed, int &count_executed, vector<int> &sequence)
{
    for (int i = 0; i < available_resources.size(); i++)
    {
        available_resources[i] += process.resources_assigned[i];
    }
    executed[to_execute] = true;
    count_executed++;
    sequence.push_back(to_execute);
}

void print_sequence(vector<int> &sequence, vector<int> &available_resources, vector<Process> &processes)
{
    for (int i = 0; i < sequence.size(); i++)
    {
        cout << "Available : ";
        for (int j = 0; j < available_resources.size(); j++)
        {
            cout << available_resources[j] << " ";
        }
        cout << "\nP" << sequence[i] << " released : ";
        for (int j = 0; j < available_resources.size(); j++)
        {
            available_resources[j] += processes[sequence[i]].resources_assigned[j];
            cout << processes[sequence[i]].resources_assigned[j] << " ";
        }
        cout << endl;
    }
    cout << "Available : ";
    for (int i = 0; i < available_resources.size(); i++)
    {
        cout << available_resources[i] << " ";
    }
    cout << endl
         << endl;
}

void print_table(vector<Process> &processes, vector<int> &available)
{
    cout << "\n---------------------------------------------------------------------\n";
    cout << "Process "
         << "Allocated "
         << "Max "
         << "Need ";
    cout << "\n---------------------------------------------------------------------\n";
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "P" << i << " ";
        for (int j = 0; j < available.size(); j++)
        {
            cout << processes[i].resources_assigned[j] << " ";
        }
        cout << " ";
        for (int j = 0; j < available.size(); j++)
        {
            cout << processes[i].resources_max_need[j] << " ";
        }
        cout << " ";
        for (int j = 0; j < available.size(); j++)
        {
            cout << processes[i].resources_max_need[j] - processes[i].resources_assigned[j] << " ";
        }
        cout << "\n---------------------------------------------------------------------\n";
    }
}

void bankers_algorithm(vector<Process> &processes, int num_of_resources, vector<int> &available_resources)
{
    int n = processes.size();
    int count_executed = 0;
    vector<bool> executed(n, false);
    vector<int> copy_av_res = available_resources;
    vector<int> sequence;
    while (count_executed < n)
    {
        int to_execute = -1;
        for (int i = 0; i < n; i++)
        {
            if (!executed[i] && enough_resources(available_resources, processes[i]))
            {
                to_execute = i;
                break;
            }
        }
        if (to_execute == -1)
        {
            // Condition of Deadlock
            cout << "!!!!!!!! Deadlock !!!!!!!!";
            return;
        }
        execute_process(processes[to_execute], to_execute, available_resources, executed, count_executed, sequence);
    }
    print_table(processes, available_resources);
    print_sequence(sequence, copy_av_res, processes);
}

int main()
{
    // CASE 1 :
    vector<Process> p = {Process(0, 0, 1, 2, 2),
                         Process(1, 1, 0, 2, 1),
                         Process(2, 1, 1, 2, 3)};
    vector<int> avl = {2, 2};
    bankers_algorithm(p, 2, avl);
    // CASE 2 :
    int n;
    cout << "Enter number of processes : ";
    cin >> n;
    int num_of_resources;
    cout << "Enter number of resources : ";
    cin >> num_of_resources;
    vector<Process> processes;
    for (int i = 0; i < n; i++)
    {
        cout << "Process P" << i << " details : \n";
        Process new_p(i, num_of_resources);
        processes.push_back(new_p);
    }
    vector<int> available_resources(num_of_resources);
    for (int i = 0; i < num_of_resources; i++)
    {
        cout << "Enter number of available instaces for R" << i << " : ";
        cin >> available_resources[i];
    }
    bankers_algorithm(processes, num_of_resources, available_resources);
    return 0;
}
