#include <iostream>

using namespace std;

class Process
{
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    string order;
};

void resetProcess(Process *process, int numProcesses)
{
    for (int i = 0; i < numProcesses; i++)
    {
        process[i].startTime = 0;
        process[i].completionTime = 0;
        process[i].turnaroundTime = 0;
        process[i].waitingTime = 0;
        process[i].responseTime = 0;
        process[i].order = "";
    }
}

void printProcess(Process *process, int numProcesses)
{
    double totalTurnaroundTime = 0;
    cout << "Process ID\tStart Time\tCompletion Time\tTurnaround Time" << endl;
    for (int i = 0; i < numProcesses; i++)
    {
        cout << process[i].pid << "\t\t" << process[i].startTime << "\t\t" << process[i].completionTime << "\t\t" << process[i].turnaroundTime << endl;
        totalTurnaroundTime += process[i].turnaroundTime;
    }
    cout << "Average Turnaround Time: " << (double)(totalTurnaroundTime / numProcesses) << endl;

    cout << "Order: ";
    
        cout << process[1].order << endl;

}

void firstComeFirstServe(Process *process, int numProcesses)
{
    int totalTurnaroundTime = 0;

    for (int i = 0; i < numProcesses; i++)
    {
        process[i].startTime = (i == 0) ? process[i].arrivalTime : max(process[i - 1].completionTime, process[i].arrivalTime);
        process[i].completionTime = process[i].startTime + process[i].burstTime;
        process[i].turnaroundTime = process[i].completionTime - process[i].arrivalTime;
        process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime;
        process[i].responseTime = process[i].startTime - process[i].arrivalTime;
        totalTurnaroundTime += process[i].turnaroundTime;

        process[1].order += to_string(process[i].pid) + " ";
    }

    printProcess(process, numProcesses);
    resetProcess(process, numProcesses);
}


bool isCompleted(Process *process, int numProcesses)
{
    int completed = true;
    for (int i = 0; i < numProcesses; i++)
    {
        if (process[i].burstTime > 0)
        {
            completed = false;
            break;
        }
    }
    return completed;
}

void SJN(Process *process, int numProcesses)
{
    int time = 0;
    int idx = 0;
    bool completed = !isCompleted(process, numProcesses);
    int initShortestJob = 999;


    while(completed){
        int shortest = initShortestJob;
        
        for(int i=0; i<numProcesses; i++){
            if(process[i].burstTime >0 && process[i].arrivalTime <= time && process[i].completionTime == 0){
                if(process[i].burstTime < shortest){
                    shortest = process[i].burstTime;
                    idx = i;
                }
            }
        }


        if(shortest != initShortestJob){
            if(process[idx].burstTime > 0){
                process[idx].startTime = time;
                time += process[idx].burstTime;
                process[idx].completionTime = time;
                process[idx].burstTime = 0;
                process[1].order += to_string(process[idx].pid) + " ";
            }
        }else{
            time++;
        }
        if(isCompleted(process, numProcesses)){
            break;
        }
    }
    for(int i=0; i<numProcesses; i++){
        process[i].turnaroundTime = process[i].completionTime - process[i].arrivalTime;
        process[i].waitingTime = process[i].turnaroundTime - process[i].burstTime;
        process[i].responseTime = process[i].startTime - process[i].arrivalTime;
    }

    printProcess(process, numProcesses);
    resetProcess(process, numProcesses);
}

void priority(Process *process, int numProcesses)
{
    int currentTime = 0;
    int completed = 0;
    int prev = 0;
    int is_completed[100];
    int burst_remaining[100];
    int total_idle_time = 0;
    int total_turnaroundTime = 0;
    int total_waitTime = 0;
    int total_responseTime = 0;
    memset(is_completed, 0, sizeof(is_completed));

    for (int i = 0; i < numProcesses; i++)
    {
        // process[i].startTime = currentTime;
        // process[i].responseTime = process[i].startTime - process[i].arrivalTime;
        burst_remaining[i] = process[i].burstTime;
    }
    while (completed != numProcesses)
    {
        int idx = -1;
        int max = 100;
        for (int i = 0; i < numProcesses; i++)
        {
            if (process[i].arrivalTime <= currentTime && is_completed[i] == 0)
            {
                if (process[i].priority < max)
                {
                    max = process[i].priority;
                    idx = i;
                }
                if (process[i].priority == max)
                {
                    if (process[i].arrivalTime < process[idx].arrivalTime)
                    {
                        max = process[i].priority;
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1)
        {
            if (burst_remaining[idx] == process[idx].burstTime)
            {
                process[idx].startTime = currentTime;
                total_idle_time += process[idx].startTime - prev;
            }
            burst_remaining[idx] -= 1;
            currentTime++;
            prev = currentTime;

            if (burst_remaining[idx] == 0)
            {
                process[idx].completionTime = currentTime;
                process[idx].turnaroundTime = process[idx].completionTime - process[idx].arrivalTime;
                process[idx].waitingTime = process[idx].turnaroundTime - process[idx].burstTime;
                process[idx].responseTime = process[idx].startTime + process[idx].arrivalTime;

                total_turnaroundTime += process[idx].turnaroundTime;
                total_waitTime += process[idx].waitingTime;
                total_responseTime += process[idx].responseTime;


                process[1].order += to_string(process[idx].pid) + " ";

                is_completed[idx] = 1;
                completed++;
            }
        }
        else
        {
            currentTime++;
        }
    }

    printProcess(process, numProcesses);
    resetProcess(process, numProcesses);
}