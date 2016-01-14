#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <ctime>
#include <chrono>

using namespace std;



static void f1(int signo)
{
	if (signo==SIGALRM)
	{
		cout<<"capture SIGALRM from self "<<endl;	
	}

}

 int main()
{

	pid_t id=getpid();
	cout<<"current process ID is "<<id<<endl;
	signal(SIGALRM,f1);
	alarm(3);
	pause();	//pause function waiting a signal.without pause,the process will directly exit.	

	return 0;
}

