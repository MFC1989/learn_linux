#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>



int main()
{
 
 mqd_t mqd;
 
 mqd=mq_open("/abc",O_RDONLY);
 if(mqd!=-1)
{
	puts("create sucess\n");
}
 struct mq_attr attr;
 int ret=mq_getattr(mqd,&attr);
if(ret==0)
{ 
 	printf("max #msgs = %ld\n,max #bytes/msg=%ld\n,currently on queue =%ld\n",attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);	
}
else
{
	puts("get attr error");
}


 return 0;	
}
