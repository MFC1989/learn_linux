 #include <stdio.h>
#include <stdlib.h>



#define MAX 1024
int main()
{
FILE * fp;
char * command="sudo cat /etc/shadow";
char buff[MAX]={0x00};



fp=popen(command,"r");	
while(fgets(buff,MAX,fp)!=NULL)
{
	puts(buff);
}
pclose(fp);

return 0;	
}
