#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO1 "/tmp/fifo.1"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


int main()
{
	int writefd;
	if(mkfifo(FIFO1,FILE_MODE)<0 && errno != EEXIST)
	{
		printf("can't create %s\n",FIFO1);
	}	
	
	char * pstr="xxx";	
	writefd=open(FIFO1,O_WRONLY,0);
	write(writefd,pstr,strlen(pstr));	
	unlink(FIFO1);

	return 0;
}
