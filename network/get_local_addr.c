#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <pwd.h>
#include <shadow.h>
#include <crypt.h>
#include <dirent.h>
#include <netdb.h>
#include <sys/stat.h>
#include <time.h>

int getlocalip2()
{
  char host[100] = {0};
  if (gethostname(host, sizeof(host)) < 0)
		return -1;

  struct addrinfo hints,*res,*res_free;

  hints.ai_family=AF_INET;
  hints.ai_socktype=SOCK_STREAM;
  getaddrinfo(host,NULL,&hints,&res);
 
  res_free=res;
 
 do {
    char buff[16]={0x00};
    struct in_addr in_a = ((struct sockaddr_in*)res->ai_addr)->sin_addr;
    inet_ntop(AF_INET,&in_a,buff,16);
    puts(buff);
  } while(res=res->ai_next);
	
  free(res_free);	  
  return 0;
}


int main()
{
	getlocalip2();	
	return 0;
} 
