#include <lab4.h>


// This is the main function.
int main (int argc, char *argv[]){

    cout<<"Enter the number of processes: ";
    int numProcesses;
    cin>>numProcesses;
    Process *processes = new Process[numProcesses];
    for(int i=0; i<numProcesses; i++){
        cout<<"Enter the pid, burst time, arrival time, and priority for process "<<i+1<<": ";
        cin>>processes[i].pid>>processes[i].burstTime>>processes[i].arrivalTime>>processes[i].priority;
        processes[i].executionTime = 0;
        processes[i].startTime = 0;
        processes[i].completionTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].averageTurnaroundTime = 0;
    }

    cout << "First Come First Serve" << endl;
    firstComeFirstServe(processes, numProcesses);
    cout << "Shortest Job First" << endl;
    shortestJobFirst(processes, numProcesses);
    cout << "Priority Scheduling" << endl;
    priorityScheduling(processes, numProcesses);
    
}