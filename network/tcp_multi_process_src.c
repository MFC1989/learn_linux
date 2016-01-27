#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

void process(int sockfd)
{
	while(1)
	{
		char recv_buff[1024]={0x00};
        	int n=recv(sockfd,recv_buff,1024,0);
      		printf(" reve %d bytes\n",n);
		puts(recv_buff);      
	
	if(strchr(recv_buff,'q')!=NULL)
	{
		close(sockfd);
        	return;
	}


 	n=send(sockfd,recv_buff,1024,0);
        memset(recv_buff,0,1024);
        printf(" send %d bytes\n",n);
        
	}
}


int main()
{
	
	int res;	
	int listenfd=socket(AF_INET, SOCK_STREAM,0);
	

	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr= htonl(INADDR_ANY);
	local.sin_port=htons(5000);

	res=bind(listenfd,(struct sockaddr *)&local,sizeof(local));
	printf("bind code%d\n",res);
	char recv_buff[260];
	res=listen(listenfd,3);

	printf("listen code %d\n",res);
	
 	struct sockaddr_in cli; 
	int cli_addr_len;	
	
	while(1)
	{ 	
			
		int connfd=accept(listenfd,(struct sockaddr *)&cli,&cli_addr_len);
		
		int childpid=fork();
		if(childpid==0)
		{
			close(listenfd);
			process(connfd);
			exit(0);			
		}
		close(connfd);
	}
	close(listenfd);
	return 0;
}
