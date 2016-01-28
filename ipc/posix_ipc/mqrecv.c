#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>


int main()
{
 
 mqd_t mqd;
 struct mq_attr attr;	

 mqd=mq_open("/abc",O_RDONLY ,666,NULL);
 if(mqd!=-1)
{
	puts("open sucess\n");
}

mq_getattr(mqd,&attr);
void * buff=malloc(attr.mq_msgsize);
int n=mq_receive(mqd,buff,attr.mq_msgsize,NULL);
printf("reveive %ld bytes.\n",(long)n);

 return 0;	
}
