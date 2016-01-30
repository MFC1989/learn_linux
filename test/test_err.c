#include <stdio.h> 
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define ERR_EXIT(m) \
	do {\
		perror(m);\
		exit(EXIT_FAILURE);\	
           }while(0)


int main()
{
	int fd=open("log1.txt", O_RDONLY);	
	if(fd==-1)
	{
		ERR_EXIT("open");
	}
	else
	{
		puts("open success");
	}
	
	puts("after open");
	return 0;
}
