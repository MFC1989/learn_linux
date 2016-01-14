 #include <stdio.h>
 #include <signal.h>
 #include <unistd.h>
 
 void show_handler(int sig,siginfo_t *info, void *ctx)
 {
  printf("recv a sig=%d data=%d data=%d\n",
           sig, info->si_value.sival_int, info->si_int);
 }
 
 int main(void)
 {
     int i = 0;
     struct sigaction act;
     act.sa_sigaction = show_handler;
     sigaddset(&act.sa_mask, SIGQUIT); //见注(1)
     act.sa_flags = SA_RESETHAND | SA_NODEFER; //见注(2)
    //act.sa_flags = 0; //见注(3)
 
     sigaction(SIGINT, &act, NULL);
     //raise(SIGINT);
     
     pid_t id=getpid();
     union sigval msg_val;
     msg_val.sival_int=100;
     sigqueue(id,SIGINT,msg_val);
     
     sleep(100);
 }
