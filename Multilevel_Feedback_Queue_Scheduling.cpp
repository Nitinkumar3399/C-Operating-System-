// C++ implementaion of 'Multilevel Feedback Queue' CPU Scheduling Algorithm.

#include<stdio.h> 
#define N 10 
 
typedef struct 
{ 
      int process_id, arrival_time, burst_time, priority;
      int q, ready; 
}process_structure; 
 
int Queue(int t1) 
{ 
      if(t1 == 0 || t1 == 1 || t1 == 2 || t1 == 3) 
      { 
            return 1; 
      } 
      else
      {
            return 2; 
      }
} 
 
int main() 
{ 
      int limit, i, temp_process, time, j, y; 
      process_structure temp; 

      printf("\n\nEnter Total Number of Processes:\t"); 
      scanf("%d", &limit);  

      process_structure process[limit]; 

      for(i = 0; i < limit; i++) 
      { 
            printf("\nProcess ID:\t"); 
            scanf("%d", &process[i].process_id);

            printf("Arrival Time:\t"); 
            scanf("%d", &process[i].arrival_time); 

            printf("Burst Time:\t"); 
            scanf("%d", &process[i].burst_time); 

            printf("Process Priority:\t"); 
            scanf("%d", &process[i].priority);

            temp_process = process[i].priority; 
            process[i].q = Queue(temp_process);
            process[i].ready = 0; 
      }

      time = process[0].burst_time; 

      for(y = 0; y < limit; y++) 
      { 
            // Do ready all the processes from "y" which has arrival time less than burst time of first process.
            for(i = y; i < limit; i++) 
            { 
                  if(process[i].arrival_time < time) 
                  {
                        process[i].ready = 1; 
                  } 
            } 
         
            for(i = y; i < limit - 1; i++) 
            {
                  for(j = i + 1; j < limit; j++) 
                  { 
                        if(process[i].ready == 1 && process[j].ready == 1) 
                        { 
                              if(process[i].q == 2 && process[j].q == 1) 
                              { 
                                    // swapping...
                                    temp = process[i]; 
                                    process[i] = process[j]; 
                                    process[j] = temp; 
                              } 
                        } 
                  } 
            } 

            for(i = y; i < limit - 1; i++) 
            { 
                  for(j = i + 1; j < limit; j++) 
                  {
                        if(process[i].ready == 1 && process[j].ready == 1) 
                        { 
                              if(process[i].q == 1 && process[j].q == 1) 
                              { 
                                    if(process[i].burst_time > process[j].burst_time) 
                                    { 
                                          // swapping...
                                          temp = process[i]; 
                                          process[i] = process[j]; 
                                          process[j] = temp; 
                                    } 
                                    else 
                                    { 
                                          break; 
                                    } 
                              } 
                        } 
                  } 
            } 
            
            printf("\nProcess[%d]:\tTime:\t%d To %d\n", process[y].process_id, time, time + process[y].burst_time); 
            time = time + process[y].burst_time;

            for(i = y; i < limit; i++) 
            { 
                  if(process[i].ready == 1) 
                  { 
                        process[i].ready = 0; 
                  } 
            }

      } 

      return 0; 
}