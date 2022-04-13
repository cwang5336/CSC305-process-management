#include <lab4.h>


// This is the main function.
int main (int argc, char *argv[]){

    cout<<"Enter the number of processes: ";
    int numProcesses;
    cin>>numProcesses;
    Process *processes = new Process[numProcesses];
    for(int i=0; i<numProcesses; i++){
        cout << "Enter the process ID, arrival time, priority, and execution time: ";
        cin >> processes[i].pid >> processes[i].arrivalTime >> processes[i].priority >> processes[i].burstTime;
    }

    

    cout << "First Come First Serve" << endl;
    firstComeFirstServe(processes, numProcesses);
    cout << "Shortest Job First" << endl;
    SJN(processes, numProcesses);
    cout << "Priority " << endl;
    priority(processes, numProcesses);
    
}