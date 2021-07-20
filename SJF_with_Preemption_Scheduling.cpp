// C++ implementaion of SJF(Preemptive) CPU Scheduling Algorithm.
// This algorithm is also known as SRTF(Shortest Remaining Time First).
#include <iostream>
#include<vector>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time; // Time at which process gets CPU first time. 
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

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
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));
    
    //order of processes in which they are executing.
    vector<int>Order_Of_Execution; 
    vector<int>Time;    

    cout << setprecision(2) << fixed;

    cout<<"\nEnter the number of processes: ";
    cin>>n;
    cout<<endl;

    for(int i = 0; i < n; i++) {
        cout<<"Enter ARRIVAL time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter BURST time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        //initially update burst_remaining time with total burst time.
        burst_remaining[i] = p[i].burst_time;
        cout<<endl;
    }

    int current_time = 0 , prev_time = 0;
    int completed = 0;
    int prev = 0 , Prev_idx = -1;

    while(completed != n) 
    {
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) 
        {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) 
            {
                // compute least burst time
                if(burst_remaining[i] < mn) 
                {
                    mn = burst_remaining[i];
                    idx = i;
                }

                // compare arrival time when 'least burst time' will be same for two process
                if(burst_remaining[i] == mn) 
                {
                    if(p[i].arrival_time < p[idx].arrival_time) 
                    {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) 
        {
            // To check same process is coming again Or 
            // Another new process with burst_remaining time exactly equal to burst_time is coming after context Switching.
            if(burst_remaining[idx] == p[idx].burst_time) 
            {
                p[idx].start_time = current_time;
                prev_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }

            // always proceed with 1 unit of time to check preemption.
            burst_remaining[idx] -= 1;

            
            if(Prev_idx != idx)
            {
               if(find(Order_Of_Execution.begin(),Order_Of_Execution.end(),p[idx].pid) != Order_Of_Execution.end())
               { 
                   // Agar same process ek ya ek se jyada baar pahle aa chuka hai toh yeh hoga 
                   // but only for first Unit of time. 
                   prev_time = current_time;
               } 
               Order_Of_Execution.push_back(p[idx].pid);
               Time.push_back(prev_time);
            }
            Prev_idx = idx;
            prev_time = current_time; // 3
            current_time++; // 4
            prev = current_time; 
            
            // If any process will have burst time zero then it has been finished.
            if(burst_remaining[idx] == 0) 
            {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                // Mark one process gets completed  
                is_completed[idx] = 1;
                completed++;
            }
        }
        else 
        { 
            // To skip ideal time for CPU if it comes... 
            current_time++;
        }  
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    
    for(int i = 0; i < n; i++) 
    {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    // Final completion time
    Time.push_back(max_completion_time);

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float) max_completion_time )*100;
    throughput = float(n) / (max_completion_time - min_arrival_time);

    cout<<endl<<endl;
    
    cout<<"**********************************************************"<<endl;
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) 
    {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].response_time<<"\t"<<"\n"<<endl;
    }
     
    // Gantt chart...
    cout<<"\n";
    cout<<"Gantt Chart:\n"<<"-----------"<<"\n\n\n";
    for (int i=0; i<Order_Of_Execution.size(); i++)
    {
        cout <<"|   "<<Order_Of_Execution[i]<< "   "; 
    }
    cout<<"|";

    cout<<"\n";
    
    for (int i = 0; i < Time.size() ; i++)
    {
          cout <<Time[i]<< "\t";
    }

    cout<<"\n\nAverage Turnaround Time = "<<avg_turnaround_time<<endl<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl<<endl;
    cout<<"Average Response Time = "<<avg_response_time<<endl<<endl;
    cout<<"CPU Utilization = "<<cpu_utilisation<<"%"<<endl<<endl;
    cout<<"Throughput = "<<throughput<<" process/unit time"<<endl<<endl;
    cout<<"**********************************************************"<<endl;
 
  return 0;
}