// C++ implementation of LRU(Least Recently Used) page replacement
// in Operating Systems.
#include<bits/stdc++.h>
using namespace std;

// Function to find page faults using indexes
int pageFaults(int *pages, int n, int capacity)
{
	// To represent set of current pages. We use
	// an unordered_set so that we quickly check
	// if a page is present in set or not
	unordered_set<int> s;

	// To store least recently used indexes
	// of pages.
	unordered_map<int, int> indexes;

	// Start from initial page
	int page_faults = 0;
	for (int i=0; i<n; i++)
	{
		// Check if the set can hold more pages
		if (s.size() < capacity)
		{
			// Insert it into set if not present
			// already which represents page fault
			if (s.find(pages[i])==s.end())
			{
				s.insert(pages[i]);

				// increment page fault
				page_faults++;
			}

			// Store the recently used index of
			// each page
			indexes[pages[i]] = i;
		}

		// If the set is full then need to perform lru
		// i.e. remove the least recently used page
		// and insert the current page
		else
		{
			// Check if current page is not already
			// present in the set
			if (s.find(pages[i]) == s.end())
			{
				// Find the least recently used pages
				// that is present in the set
				int lru = INT_MAX, val;
				for (auto it=s.begin(); it!=s.end(); it++)
				{
					if (indexes[*it] < lru)
					{
						lru = indexes[*it];
						val = *it;
					}
				}

				// Remove the indexes page
				s.erase(val);

				// insert the current page
				s.insert(pages[i]);

				// Increment page faults
				page_faults++;
			}

			// Update the current page index
			indexes[pages[i]] = i;
		}
	}

	return page_faults;
}




int main()
{
    int pages , frames;
    cout<<"\n*********************************";
    cout<<"\nEnter Total Number of pages :  ";
    cin>>pages;
    cout<<"\nEnter Total Number of frames : ";
    cin>>frames;

	int *reference_string;
    reference_string = new int[pages];
    cout<<"\nEnter values of Reference String:\n";
    for (int i = 0; i < pages ; i++)
    {
        cout<<"Value No. "<<"["<<i+1<<"]:\t";
        cin>>reference_string[i];   
    }
    
    int faults = pageFaults(reference_string, pages, frames);
    cout <<"\nTotal Page Hits:\t"<<(pages - faults);
	cout <<"\nTotal Page Faults:\t"<<faults;
	return 0;
}
