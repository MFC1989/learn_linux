#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/* port we're listening on */
#define PORT 5000

int main(int argc, char *argv[])
{
	 int ret;
	 int listenfd=socket(AF_INET, SOCK_STREAM ,0);
	 struct  sockaddr_in local_addr,peer_addr;
	 local_addr.sin_family= AF_INET;
	 local_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	 local_addr.sin_port=htons(PORT);
	 ret=bind(listenfd,(struct sockaddr *)&local_addr,sizeof(local_addr));
	 if(ret!=0)
	{
			puts("bind error");
	}

	listen(listenfd,3);

	fd_set fdread,fdall;
	FD_ZERO(&fdall);
	FD_SET(listenfd,&fdall);

	int i;

	int maxfd=listenfd;

	while(1)
	{
		fdread=fdall;
		ret=select(maxfd+1,&fdread,NULL,NULL,NULL);
		if(ret<0)
		{
			puts("select error");
		}

		for(i=0;i<=maxfd;i++)
		{

			if(FD_ISSET(i,&fdread))
			{
				if(i==listenfd)
				{
					
				int peer_addr_size=sizeof(peer_addr);
				int conn=accept(listenfd, (struct sockaddr *)(&peer_addr),&peer_addr_size);

				if(conn<0)
				{
					puts("accept error");
				}
				else
				{
					puts("accept ok");
												
                                 	if(maxfd<conn)
					{
						maxfd=conn;
					}
					FD_SET(conn,&fdall);
					
					printf("%s : %d was accept ",inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
				}			
				
			}
			else
			{
				
				char buff[1000]={0x00};	
				ret=recv(i,buff,sizeof(buff),0);
				
				if(ret<=0)
				{
					close(i);
					printf("%s : %d was closed ");
				}	
				printf("%s : %d ---> ",inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
				puts(buff);
				send(i,buff,sizeof(buff),0);
			}

		}

	}
}

	return 0;
}
