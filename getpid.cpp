// C++ Code to demonstrate getpid()

#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
	int pid = fork();
	if (pid == 0)
		cout << "\nCurrent process id of Process : "<< getpid() << endl;
	return 0;
}
