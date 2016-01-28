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

 mqd=mq_open("/abc",O_WRONLY ,666,NULL);
 if(mqd!=-1)
{
	puts("create sucess\n");
}

void * ptr=calloc(10,sizeof(char));
mq_send(mqd,ptr,10,0);

 return 0;	
}
