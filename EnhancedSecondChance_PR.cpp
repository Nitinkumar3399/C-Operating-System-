// C++ implementation of 'Enhanced - Second chance Page Replacement' Algorithm
#include <bits/stdc++.h>
using namespace std;

struct page
{
    int page_no;
    int modified_bit;
    int use_bit = 0;
};

int main()
{
    int pages, frames, pf = 0;
    cout << "\nEnter the total number of pages : ";
    cin >> pages;
    cout << "\nEnter number of frames : ";
    cin >> frames;

    struct page reference_string[pages];
    // Create a array to hold page numbers
    struct page arr[frames];

    for (int i = 0; i < frames; i++)
    {
        arr[i].page_no = -1;
    }

    cout << "Enter Page no. and their Modified bit :\n\n";

    for (int i = 0; i < pages; i++)
    {
        cout << "Enter Page : ";
        cin >> reference_string[i].page_no;
        cout << "Modified Bit : ";
        cin >> reference_string[i].modified_bit;
        cout << endl;
    }

    // for first page..
    pf = 1;
    reference_string[0].use_bit = 1;
    arr[0].page_no = reference_string[0].page_no;
    arr[0].use_bit = 1;
    arr[0].modified_bit = reference_string[0].modified_bit;

    int k = 1;
    for (int i = 1; i < pages; i++)
    {
        int j;
        for (j = 0; j < frames; j++)
        {
            if (arr[j].page_no == reference_string[i].page_no)
            {
                // page hit..
                arr[j].modified_bit = reference_string[i].modified_bit;
                reference_string[i].use_bit = 1;
                arr[j].use_bit = 1;
                break;
            }
        }

        if (j == frames && k <= frames - 1)
        {
            // if space left in frames..
            arr[k].page_no = reference_string[i].page_no;
            arr[k].modified_bit = reference_string[i].modified_bit;
            arr[k].use_bit = 1;
            reference_string[i].use_bit = 1;
            k++;
            pf++;
        }
        else if (j == frames && k > frames - 1)
        {
            // page fault occur..
            // so replacement is necessary here.

            while (reference_string[i].use_bit != 1)
            {
                int flag1 = 0, flag2 = 0, idx_1 = -1, idx_2 = -1;

                // Checking for class (0,0)
                for (int count = 0; count < frames; count++)
                {
                    if (arr[count].modified_bit == 0 && arr[count].use_bit == 0)
                    {
                        flag1 = 1;
                        idx_1 = count;
                        break;
                    }
                }

                // Checking for class (0,1)
                for (int count = 0; count < frames; count++)
                {
                    if (arr[count].use_bit == 0 && arr[count].modified_bit == 1)
                    {
                        flag2 = 1;
                        idx_2 = count;
                        break;
                    }
                }

                if (flag1 == 1 && flag2 == 0)
                {
                    arr[idx_1].page_no = reference_string[i].page_no;
                    arr[idx_1].modified_bit = reference_string[i].modified_bit;
                    arr[idx_1].use_bit = 1;
                    reference_string[i].use_bit = 1;
                }
                else if (flag1 == 0 && flag2 == 1)
                {
                    arr[idx_2].page_no = reference_string[i].page_no;
                    arr[idx_2].modified_bit = reference_string[i].modified_bit;
                    arr[idx_2].use_bit = 1;
                    reference_string[i].use_bit = 1;
                }
                else if (flag1 == 1 && flag2 == 1)
                {
                    if (idx_1 < idx_2)
                    {
                        arr[idx_1].page_no = reference_string[i].page_no;
                        arr[idx_1].modified_bit = reference_string[i].modified_bit;
                        arr[idx_1].use_bit = 1;
                        reference_string[i].use_bit = 1;
                    }
                    else
                    {
                        arr[idx_2].page_no = reference_string[i].page_no;
                        arr[idx_2].modified_bit = reference_string[i].modified_bit;
                        arr[idx_2].use_bit = 1;
                        reference_string[i].use_bit = 1;
                    }
                }
                else if (flag1 == 0 && flag2 == 0)
                {
                    for (int count = 0; count < frames; count++)
                    {
                        arr[count].use_bit = 0;
                    }
                }
            }

            pf++;
        }
    }

    cout<<"Total Page faults : "<<pf<<endl;

    return 0;
}
