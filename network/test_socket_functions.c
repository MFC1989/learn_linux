#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdlib.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
	int listenfd=socket(AF_INET, SOCK_STREAM ,0);
	//printf("%d\n",listenfd);  
	struct sockaddr_in serv_addr,cli_addr;
	serv_addr.sin_family=AF_INET;
	//serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);
	serv_addr.sin_port=htons(5000);

	socklen_t serv_addr_len=sizeof(struct sockaddr_in);
	int nret=bind(listenfd,(struct sockaddr *)&serv_addr,serv_addr_len);
	
	if(nret!=0)
	{
		puts("bind error");
	}	

	listen(listenfd,3);
	
	int clientfd=accept(listenfd,NULL,NULL);
	
	socklen_t cli_addr_len=sizeof(cli_addr);
	char buff[1024]={0x00};	
	if(clientfd>0)
	{
		puts("accept ok");
		nret=getpeername(clientfd,(struct sockaddr *)&cli_addr,&cli_addr_len);
		   if(nret!=0)
        	   {
               		 puts("getpeername error");
        	   }  
			puts(inet_ntoa(cli_addr.sin_addr));
			printf("%d\n" ,htons(cli_addr.sin_port));
	}
	
	
	struct hostent * baidu;
	baidu=gethostbyname("www.baidu.com");
	if(baidu!=NULL)
	{
		printf("%s",baidu->h_name);
	}
	else
	{
		puts("gethostbyname error");
	}


	close(clientfd);
	close(listenfd);

	return 0;
}



