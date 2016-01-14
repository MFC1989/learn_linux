#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

using namespace std;

static void f1(int signo)
{
	if (signo==SIGUSR1)
	{
		cout<<"capture SIGUSR1 from self "<<endl;
	}
}

 int main()
{
	signal(SIGUSR1,f1);
	
	
	pid_t id=getpid();
	cout<<"current process ID is "<<id<<endl;
	while(1)
	{
		sleep(1);
		raise (SIGUSR1);
	}
	return 0;
}

