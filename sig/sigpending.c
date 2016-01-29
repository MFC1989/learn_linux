#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void sig_quit(int signo);


int main()
{
	sigset_t newmask,oldmask,pendmask;
	printf("current pid = %d\n",getpid());
	sleep(1);	

	if(signal(SIGQUIT,sig_quit)==SIG_ERR)
	{
		puts("can't catch SIGQUIT");
		exit(0);
	}
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
	{
	         puts("SIG_BLOCK error");
         	 exit(0);
	}
	
	sleep(10);
	
	if(sigpending(&pendmask)<0)
	{
    		puts("sigpending error");
                exit(0);
	}
	
	if(sigismember(&pendmask,SIGQUIT))
	{
		puts("SIGQUIT pending ");	
	}	

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
	{
		puts("SIG_SETMASK error");
		exit(0);		
	}
	
	puts("SIGQUIT ubblocked");
	sleep(10);

	return 0;
}

static void sig_quit(int signo)
{
        puts("caught SIGQUIT");
        if(signal(SIGQUIT,SIG_DFL)==SIG_ERR)
        {
                puts("can't reset SIGQUIT");
                exit(0);
        }

}

