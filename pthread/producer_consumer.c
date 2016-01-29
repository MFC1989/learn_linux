#include <stdio.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ERR_EXIT(m)\
        do{\
                perror(m);\
                exit(EXIT_FAILURE);\
          }while(0)

 
pthread_t ptid,ctid1,ctid2;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int n=0;

static void * produce(void * p)
{
	//puts("produce");
	while(1)
	{
		pthread_mutex_lock(&lock);
        	n++;
		printf("%lu produce-->%d\n",pthread_self()%10000,n);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}

//	pthread_mutex_lock(&lock);
//	n++;
//	pthread_mutex_unlock(&lock);
	return NULL;
}


static void * consumer(void * p)
{
        //puts("consumer");
while(1)
{
	pthread_mutex_lock(&lock);
 	while(n==0)
	{
		pthread_cond_wait(&cond,&lock);
	}       

	n--;
//	printf("consume%d\n",n);
	
	printf("%lu consume-->%d\n",pthread_self()%10000,n);
	pthread_mutex_unlock(&lock);
	sleep(1);
}
	return NULL;
}


int main()
{
	
	if(pthread_create(&ptid,NULL,produce,NULL)!=0)
	{
		ERR_EXIT("pthread_create");
	}	

	 if(pthread_create(&ctid1,NULL,consumer,NULL)!=0)
        {
                ERR_EXIT("pthread_create");
        }

	
	 if(pthread_create(&ctid2,NULL,consumer,NULL)!=0)
        {
                ERR_EXIT("pthread_create");
        }
	


	pthread_join(ptid,NULL);
	pthread_join(ctid1,NULL);
	pthread_join(ctid2,NULL);
	return 0;
}
