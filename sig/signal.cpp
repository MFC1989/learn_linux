#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

static void sig_usr(int signo)
{
	if (signo==SIGUSR1)
	{
		cout<<"receive SIGUSR1"<<endl;
	}
	else if (signo==SIGUSR2)
	{
		cout<<"receive SIGUSR2"<<endl;	
	}
	else
	{
		cout<<"receive signal"<< signo<<endl;
	}

}

 int main()
{
	signal(SIGUSR1,sig_usr);
	signal(SIGUSR2,sig_usr);
	while(1)
	{
		;
	}
	return 0;
}

