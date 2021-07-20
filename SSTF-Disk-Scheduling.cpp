// C++ program to demonstrate
// SSTF Disk Scheduling algorithm

#include <bits/stdc++.h>
using namespace std;

int main()
{

    int i, k, n, m, sum = 0, head;
    cout << "\nEnter the size of disk : ";
    cin >> m;
    cout << "\nEnter number of requests : ";
    cin >> n;
    cout << "\nEnter the requests:\n";

    //creating two arrays, array a will store the input
    //I/O requests and array b will store the output
    vector<int> a(n), b;

    //creating a map to store the count of each element
    //in the array a.
    map<int, int> mp;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
        mp[a[i]]++;
    }

    for (i = 0; i < n; i++)
    {
        if (a[i] > m)
        {
            cout << "Error, Wrong Track No. " << a[i] << "\n";
            return 0;
        }
    }

    cout << "\nEnter the head position : ";
    cin >> head;
    int temp = head;
    int ele;
    b.push_back(head);
    int count = 0;

    while (count < n)
    {

        //initially taking diff to be very large.
        int diff = 999999;

        //traversing in map to find the least difference
        for (auto q : mp)
        {
            if (abs(q.first - temp) < diff)
            {
                ele = q.first;
                diff = abs(q.first - temp);
            }
        }

        //deleting the element that has the least
        //difference from the map

        mp[ele]--;
        if (mp[ele] == 0)
        {
            mp.erase(ele);
        }
        //adding that element to our output array.
        b.push_back(ele);
        temp = ele;
        count++;
    }

    cout << "\nSeek Sequence of tracks is " << endl;
    //printing the output array
    cout << b[0]; //head
    temp = b[0];
    for (i = 1; i < b.size(); i++)
    {
        cout << " -> " << b[i];
        sum += abs(b[i] - temp);
        temp = b[i];
    }
    cout << '\n';
    cout << "\nTotal number of seek operations = " << sum << '\n';
    cout << "Average head movement = " << (float)sum / n << '\n';
    return 0;
}