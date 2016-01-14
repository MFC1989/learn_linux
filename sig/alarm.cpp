#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <ctime>
#include <chrono>

using namespace std;

void display_time()
{
   
   time_t now = time(0);
  
   char* dt = ctime(&now);

   cout << "time-->" << dt << endl;

	
}

static void f1(int signo)
{
	if (signo==SIGALRM)
	{
		cout<<"capture SIGALRM from self "<<endl;
		display_time();		
	}

}

 int main()
{

	
	
	pid_t id=getpid();
	cout<<"current process ID is "<<id<<endl;
	signal(SIGALRM,f1);
	while(1)
	{
		alarm(2);
		sleep(2);
	}

	return 0;
}

