#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main (void)
{
  char IPdotdec[20]; 
  struct in_addr s;  
  inet_pton(AF_INET, "127.0.0.1", (void *)&s);
  printf("inet_pton: 0x%x\n", s.s_addr);
   
  char addr_str[16]={0x00};	
  inet_ntop(AF_INET, (void *)&s, addr_str, 16);
  printf("inet_ntop: %s\n", addr_str);
  return 0;	
}
