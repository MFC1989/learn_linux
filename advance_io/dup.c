#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd=open("log.txt",O_WRONLY);
	if(fd!=-1)
	{
		printf("%d\n",fd);
	}		
	int newfd=dup(fd);
	printf("%d\n",newfd);
	write(newfd,"222",sizeof("222"));
	write(fd,"111",sizeof(111));
	if(close(fd)==-1)
	{
		puts("close error");
	}
	if(close(newfd)==-1)
	{
		  puts("close error");
	}
}
