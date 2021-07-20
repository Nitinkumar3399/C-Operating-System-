// C++ program to demonstrate
// LOOK Disk Scheduling algorithm

#include <bits/stdc++.h>
using namespace std;

void LOOK(int arr[], int head, string direction, int n)
{
	int seek_count = 0;
	int distance, cur_track, HEAD = head;
	vector<int> left, right;
	vector<int> seek_sequence;

	// appending values which are
	// currently at left and right
	// direction from the head.
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < head)
			left.push_back(arr[i]);
		if (arr[i] > head)
			right.push_back(arr[i]);
	}

	// sorting left and right vectors
	// for servicing tracks in the
	// correct sequence.
	sort(left.begin(), left.end());
	sort(right.begin(), right.end());

	// run the while loop two times.
	// one by one scanning right
	// and left side of the head
	int run = 2;
	while (run--)
	{
		if (direction == "left")
		{
			for (int i = left.size() - 1; i >= 0; i--)
			{
				cur_track = left[i];

				// appending current track to seek sequence
				seek_sequence.push_back(cur_track);

				// calculate absolute distance
				distance = abs(cur_track - head);

				// increase the total count
				seek_count += distance;

				// accessed track is now the new head
				head = cur_track;
			}
			// reversing the direction
			direction = "right";
		}
		else if (direction == "right")
		{
			for (int i = 0; i < right.size(); i++)
			{
				cur_track = right[i];
				// appending current track to seek sequence
				seek_sequence.push_back(cur_track);

				// calculate absolute distance
				distance = abs(cur_track - head);

				// increase the total count
				seek_count += distance;

				// accessed track is now new head
				head = cur_track;
			}
			// reversing the direction
			direction = "left";
		}
	}

	cout << "\nTotal number of seek operations = "
		 << seek_count << endl;

	cout << "\nSeek Sequence is" << endl;
	cout << HEAD;
	for (int i = 0; i < seek_sequence.size(); i++)
	{
		cout << " -> " << seek_sequence[i];
	}
}

int main()
{
	int n;
	char ch;
	cout << "\nEnter number of requests : ";
	cin >> n;
	cout << "\nEnter the requests:\n";
	// request array
	int *arr;
	arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	int head;
	cout << "\nEnter the head position : ";
	cin >> head;
	string direction;
	cout << "Enter the direction Left or Right [L/R] : ";
	cin >> ch;
	if (ch == 'L' || ch == 'l')
	{
		direction = "left";
	}
	else
	{
		direction = "right";
	}

	LOOK(arr, head, direction, n);

	return 0;
}
