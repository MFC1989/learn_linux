#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <stddef.h>		/* for offsetof */
#include <string.h>		/* for convenience */
#include <unistd.h>		/* for convenience */
#include <signal.h>		/* for SIG_ERR */

using namespace std;

char buf[50000];

void set_fl(int fd, int flags) 
{
	int	val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
	puts("fcntl F_GETFL error");

	val |= flags;		

	if (fcntl(fd, F_SETFL, val) < 0){;}
		puts("fcntl F_SETFL error");
}

void clr_fl(int fd, int flags)
{
	int	val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		puts("fcntl F_GETFL error");

	val &= ~flags;		/* turn flags off */

	if (fcntl(fd, F_SETFL, val) < 0)
		puts("fcntl F_SETFL error");
}


int main(int argc, char const *argv[])
{
	int ntowrite,nwrite;
	char *ptr;

	ntowrite=read(STDIN_FILENO,buf,sizeof(buf));
	cout<<"read "<<ntowrite<<" bytes";
	set_f1(STDOUT_FILENO,O_NONBLOCK);
	ptr=buf;

	while(ntowrite>0)
	{
		int errno=0;
		nwrite=write(STDOUT_FILENO,ptr,ntowrite);
		cout<<"nwrite = "<<nwrite<<" errno = "<<errno<<endl;

		if (nwrite>0)
		{
			ptr+=nwrite;
			ntowrite-=nwrite;
		}
	}

	clr_fl(STDOUT_FILENO,O_NONBLOCK);

	return 0;
}