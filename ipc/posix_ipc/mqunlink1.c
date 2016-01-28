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
 
int res=mq_unlink("/abc");	
if(res==0)
{
	puts("unlink success");
}	

 return 0;	
}
