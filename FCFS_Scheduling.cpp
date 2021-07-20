// C++ implementaion of FCFS CPU Scheduling Algorithm.
#include <iostream>
#include<vector>
#include <algorithm> 
#include <iomanip>
 
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;  // Time at which process gets CPU first Time.
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compareArrival(process p1, process p2) 
{ 
    return p1.arrival_time < p2.arrival_time;
}

bool compareID(process p1, process p2) 
{  
    return p1.pid < p2.pid;
}

int main() {

    int n;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;

    //order of processes in which they are executing.
    vector<int>Order_Of_Execution;
    cout << setprecision(2) << fixed;

    cout<<"\n\nEnter the number of processes: ";
    cin>>n;
    cout<<endl<<endl;
    for(int i = 0; i < n; i++) {
        cout<<"Enter ARRIVAL time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter BURST time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;
    }

    sort(p,p+n,compareArrival);

    for(int i = 0; i < n; i++) 
    {
 
        if(i == 0){

          p[i].start_time = p[i].arrival_time;
        }
        else{

          p[i].start_time = max(p[i-1].completion_time , p[i].arrival_time);  
        }

        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
        //order of processes in which they are executing.
        Order_Of_Execution.push_back(p[i].pid);

        if(i == 0){
           
           total_idle_time += p[i].arrival_time;
        }
        else{
           
           total_idle_time += p[i].start_time - p[i-1].completion_time;
        }
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((p[n-1].completion_time - total_idle_time) / (float) p[n-1].completion_time)*100;
    throughput = float(n) / (p[n-1].completion_time - p[0].arrival_time);

    sort(p,p+n,compareID); 
    
    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) 
    {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    cout<<endl;
    cout<<"**********************************************************"<<endl;
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].response_time<<"\t"<<"\n"<<endl;
    }

     
    // Gantt chart... 
    cout<<"\n";
    cout<<"Gantt Chart:\n"<<"-----------"<<"\n\n\n";
    for (int i=0; i<n; i++){
        cout <<"|   "<<Order_Of_Execution[i] << "   "; 
    }
    cout<<"|";

    cout<<"\n";
    int k , j;
    for ( k = 0; k < n; k++)
    {
        // start time according to order of execution.
        for (int j = 0; j < n ; j++)
        {
            if(Order_Of_Execution[k] == p[j].pid)
            {
               cout << p[j].start_time<< "\t";
            }
        }    
    } 

    //
    cout<<max_completion_time<<endl<<endl;


    cout<<"\nAverage Turnaround Time = "<<avg_turnaround_time<<endl<<endl;
    cout<<"\nAverage Waiting Time = "<<avg_waiting_time<<endl<<endl;
    cout<<"\nAverage Response Time = "<<avg_response_time<<endl<<endl;
    cout<<"\nCPU Utilization = "<<cpu_utilisation<<"%"<<endl<<endl;
    cout<<"\nThroughput = "<<throughput<<" process/unit time"<<endl<<endl;
    cout<<"**********************************************************"<<endl;
  
    return 0;
}