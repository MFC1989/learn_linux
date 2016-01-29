#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 100

void Pipe(int pipefd[2])
{
	int res=pipe(pipefd);
	if(res!=0)
	{
		puts("create pipe error");
	}	
}

void server(int readfd,int writefd)
{
	char server_buff[MAX];
	int n=read(readfd,server_buff,MAX);	
	
	int i;
	
	if(n>0)
	{
		puts(server_buff);
		
		for(i=0;i<strlen(server_buff);i++)
        	{
                	server_buff[i]+=1;
        	}
		
		write(writefd,server_buff,n);
	}
	
}

void client(int readfd,int writefd)
{
        write(writefd,"xxx",sizeof("xxx"));
	char client_buff[MAX];
	int n=read(readfd,client_buff,MAX);
	if(n>0)
	{
		//printf("%d\n",n);
		puts(client_buff);
	}
}


int main()
{
	
	pid_t childpid;	
	int pipe1[2],pipe2[2];
	Pipe(pipe1);
	Pipe(pipe2);
	

	if((childpid=fork())==0)
	{
		close(pipe1[1]);		
		close(pipe2[0]);	
		server(pipe1[0],pipe2[1]);			
	}
	
	close(pipe1[0]);
	close(pipe2[1]);
	
	client(pipe2[0],pipe1[1]);	
	waitpid(childpid,NULL,0);
	return 0;
}
