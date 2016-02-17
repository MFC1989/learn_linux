#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>


#define MAX 100
int main(int argc,char **argv)
{

char buff[MAX]={0x00};
if(argc<=1)
{
	puts("please inoput path");
	exit(EXIT_FAILURE);
}

char * path=argv[1];
//printf("path = %s\n",path);
if(-1==readlink(path,buff,MAX))
{
	perror("readlink");
}

printf("real path = %s\n",buff);
return 0;

}
