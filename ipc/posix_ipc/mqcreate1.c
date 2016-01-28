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

 mqd=mq_open("/abc",O_RDWR | O_CREAT,666,NULL);
 if(mqd!=-1)
{
	puts("create sucess\n");
}

 return 0;	
}
