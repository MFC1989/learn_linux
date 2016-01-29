#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX_BUF 1024
#define MAXEPOLLSIZE 10000

static setnonblocking(int sockfd)
{
	if(fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFD,0)|O_NONBLOCK)==-1)
	{
		return -1;
	}
	
	return 0;
}

static int  handle_message(int newfd)
{
	char buff[MAX_BUF]={0x00};
	int len;
	memset(buff,0,MAX_BUF);		
	len=recv(newfd,buff,MAX_BUF,0);
	if(len>0)
	{
		puts(buff);
		send(newfd,buff,sizeof(buff),0);
	}
	else
	{
		puts("recv error");
		close(newfd);
		return -1;
	}

	return len;

}




int main()
{
	int listener,new_fd,kdpfd,nfds,n,ret,curfds;
	socklen_t len;
	struct sockaddr_in my_addr,their_addr;
	unsigned int myport,lisnum;
	struct epoll_event ev;
	struct epoll_event events[MAXEPOLLSIZE];
	struct rlimit rt;
	myport=5000;
	lisnum=2;
	rt.rlim_max=rt.rlim_cur=MAXEPOLLSIZE;
	//if(setrlimit(RLIMIT_NOFILE,&rt)==-1)
	{
	//	puts("set limit error");
	}
	
	if((listener=socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		puts("create socket error");		
	}
		
 	setnonblocking(listener);
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(myport);
	my_addr.sin_addr.s_addr=INADDR_ANY;

	 if( bind(listener,(struct sockaddr *)&my_addr,sizeof(my_addr)) == -1)
        {
                puts("bind error");
        }
	
	if(listen(listener,lisnum)==-1)
	{
                puts("bind error");
	}
	
	kdpfd=epoll_create(MAXEPOLLSIZE);
	ev.events=EPOLLIN|EPOLLET;
	ev.data.fd=listener;	
	if(epoll_ctl(kdpfd,EPOLL_CTL_ADD,listener,&ev)<0)
	{
		puts("add listener to epoll error");
	}
	
	curfds=1;
	
	while(1)
	{
		nfds=epoll_wait(kdpfd,events,curfds,-1);
		if(nfds == -1)
			puts("epoll wait error");
		
		for(n=0;n<nfds;n++)
		{
			if(events[n].data.fd==listener)
			{
				new_fd=accept(listener,(struct sockaddr *)&their_addr,&len);
			
				if(new_fd<0)
				{
					puts("accept error");
				}	
				else
				{
					printf("%s : %d",inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port));
					setnonblocking(new_fd);
					ev.events=EPOLLIN|EPOLLET;
					ev.data.fd=new_fd;
					if(epoll_ctl(kdpfd,EPOLL_CTL_ADD,new_fd,&ev)<0)
					{
						puts("add new socket into epoll error");
						return -1;
					}
					curfds++;
				}
					
			}
			else
			{
				ret=handle_message(events[n].data.fd);
				if(ret<1&&errno!=11)
				{
					epoll_ctl(kdpfd,EPOLL_CTL_DEL,events[n].data.fd,&ev);
					curfds--;
				}
			


			}	
			

		}

	}
	
close(listener);

return 0;
}

