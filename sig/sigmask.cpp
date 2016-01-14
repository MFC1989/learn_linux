#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void f_usr1(int pid)
{
	cout<<"SIGUSR1 was captured"<<endl;
}

void f_usr2(int pid)
{
	cout<<"SIGUSR2 was captured"<<endl;
}

bool check_is_block( sigset_t * block_sets,int signo)
{
    if(sigismember(block_sets,signo))
    {
        cout<<"SIGNAL"<<signo<< " is in the block set"<<endl;
        return true;
    }
    else
    {
        cout<<"SIGNAL"<<signo<< " is not in the block set"<<endl;
        return false;
    }
}

int main()
{
	
    signal(SIGUSR1,f_usr1);
	signal(SIGUSR2,f_usr2);
    
    sigset_t sig_sets;
    sigaddset(&sig_sets,SIGUSR1);    
    sigaddset(&sig_sets,SIGUSR2);    

    sigprocmask(SIG_BLOCK,&sig_sets,NULL);    
	raise(SIGUSR1);							
	raise(SIGUSR2);
	
    sigset_t sig_block_sets;
    
    sigpending(&sig_block_sets);
    check_is_block(&sig_block_sets,SIGUSR1);
    check_is_block(&sig_block_sets,SIGUSR2);
    check_is_block(&sig_block_sets,SIGSTOP);
   
  
    sleep(100);
	
	return 0;

}
