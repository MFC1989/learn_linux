#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
// gcc -g -o simple_client simple_client.c
int main(int argc,char *argv[])
{
    char ip[20]={"127.0.0.1"};
    int port=5000;
    int server_fd;
    struct sockaddr_in server_listen_addr;
    bzero(&server_listen_addr,sizeof(server_listen_addr));
    server_listen_addr.sin_family=AF_INET;
    server_listen_addr.sin_port=htons(port);
    inet_pton(AF_INET,"192.168.10.23",(void*)&server_listen_addr.sin_addr);
   // inet_aton(ip,&server_listen_addr.sin_addr);
   // bzero(&(server_listen_addr.sin_zero),8);
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    int ret=connect(server_fd,(const struct sockaddr *)&server_listen_addr,
                    sizeof(struct sockaddr));     
     printf("server_fd=[%d] ret=[%d]\n",server_fd,ret);
     if(ret<0)
     {
      perror("error: socket connect!");       
      exit(1);
     }
     char data[20]={"good luck!\n"};
     int num=send(server_fd,(void*)data,strlen(data),0);
     printf("send bytes[%d][%s]\n",num,data);
     close(server_fd);
    return 1;
}
