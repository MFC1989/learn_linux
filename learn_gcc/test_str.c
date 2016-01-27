#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
char * s="abcd";
char * p=strstr(s,"b");
if(p!=NULL)
{
	puts(p);
}

char * q= strchr(s,'c');

if(q!=NULL)
{
        puts(q);
}



}
