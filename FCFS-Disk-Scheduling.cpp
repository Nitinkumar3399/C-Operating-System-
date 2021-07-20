// C++ program to demonstrate
// FCFS Disk Scheduling algorithm

#include <bits/stdc++.h>
using namespace std;

void FCFS(int *arr, int head , int n)
{
	int seek_count = 0;
	int distance, cur_track ,HEAD = head;

	for (int i = 0; i < n; i++) 
    {
		cur_track = arr[i];

		// calculate absolute distance
        // calculating the difference for the head movement
		distance = abs(cur_track - head);

		// increase the total count
		seek_count += distance;

		// accessed track is now new head
		head = cur_track;
	}

	cout << "Total number of seek operations = "
		<< seek_count << endl<<endl;

	// Seek sequence would be the same
	// as request array sequence
	cout << "Seek Sequence of tracks is " << endl;
    cout<<HEAD;  
	for (int i = 0; i < n; i++) {
		cout <<" -> "<< arr[i];
	}
}


int main()
{
    int n;
    cout<<"\nEnter number of requests : ";
    cin>>n;
    cout<<"\nEnter the requests:\n";
	// request array
	int *arr;
    arr = new int[n];
    for (int i = 0; i < n ; i++)
    {
       cin>>arr[i];
    }

	int head;
    cout<<"\nEnter the head position\n";
    cin>>head;
    cout<<endl;
	FCFS(arr, head , n);

	return 0;
}
