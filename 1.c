
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>



pthread_mutex_t locker;
pthread_cond_t th_cond;
     
int flag = 1;
void * thr_fn(void * arg) 
{
    struct timespec ts;
  long msec = 10000; //10sec, 10000 msec  
   struct timeval tv;
  while (flag){
    printf(".\n");
    //sleep(10);

    gettimeofday(&tv, (struct timezone *) NULL);

    /* what's really funny about this is that I know
       pthread_cond_timedwait just turns around and makes this
       a relative time again */
    ts.tv_sec = tv.tv_sec + (msec / 1000);
    ts.tv_nsec = (tv.tv_usec + (msec % 1000) * 1000L ) * 1000L;
        
    pthread_mutex_lock(&locker);
    
    pthread_cond_timedwait(&th_cond,&locker,&ts);
    pthread_mutex_unlock(&locker);

    
/*
int pthread_cond_timedwait(pthread_cond_t *restrict cond,
       pthread_mutex_t *restrict mutex,
       const struct timespec *restrict abstime);
*/           
  }
  printf("thread exit\n");
}

int fun1()
{
    char source[] = "hello, world! welcome to Taiwan!";
    char delim[] = " ,!";
//    char *s = strdup(source);
    char *s = source;
    char *token;
    for(token = strsep(&s, delim); token != NULL; token = strsep(&s, delim)) 
    {
        printf(token);
        printf("+");
    }
    printf("\n source is %s \n",source);
    printf("\n");
    return 0;

    
}
 

int fun2()
{
    char source[] = "hello, world! welcome to Taiwan!";
    char delim[] = " ,!";
    //char *s = strdup(source);
    char *s = source;
    char *token;
    for(token = strtok(s, delim); token != NULL; token = strtok(NULL, delim)) 
    {
    
        printf(token);
        printf("+");
    }   
    printf("\n source is %s \n",source);
    printf("\n");
    return 0;

    
}

int fun3(char **str)
{
    
    //*str++;
    //*str++;
    (*str)++;
    (*str)++;
    (*str)++;
    
    printf("\n in fun3, str is %s ",*str);
    return 0;
} 

int fun4(char *str)
{
    
    //*str++;
    //*str++;
    (str)++;
    (str)++;
    (str)++;
    
    printf("\n in fun4, str is %s ",str);
    return 0;
} 


 
int fun5(void)
{
    char s[20] = "out of work";
    char t[20] = "future";
     
    //memmove(s, t, 6);
       memcpy(s,t,6);
     
    printf("s is %s\n", s);
    printf("t is %s\n", t);
     
    return 0;   
}


int fun6()
{
    char *cmd=NULL;
    char *t1=NULL;
    printf("\n in fun6");
    asprintf(&cmd,"12345");
    printf("\n cmd is %s \n",cmd);
    free(cmd);
    printf("\n cmd is %s \n",cmd);
    if(cmd==NULL)
        printf("\n cmd is NULL \n");
    else
        printf("\n cmd is NOT NULL \n");
                


    if(t1==NULL)
        printf("\n t1 is NULL \n");
    else
        printf("\n t1 is NOT NULL \n");

    t1 = (char *)malloc(50);    
    
    if(t1==NULL)
        printf("\n t1 is NULL \n");
    else
        printf("\n t1 is NOT NULL \n");

    free(t1);        
    
    if(t1==NULL)
        printf("\n t1 is NULL \n");
    else
        printf("\n t1 is NOT NULL \n");




    return 0;
}

int main() 
{     
    fun6();
/*
    char *tmp=NULL;
    tmp=(char *)malloc(32);
    strcpy(tmp,"1234567890");    
    //return 0;
    //fun3(&tmp);    
    fun4(tmp);    
    printf("\n tmp is %s \n",tmp);
*/

#if 0
  pthread_t thread;
  pthread_mutex_init(&locker, NULL);
  pthread_cond_init(&th_cond, NULL);
    
  if (0 != pthread_create(&thread, NULL, thr_fn, NULL)) {
    printf("error when create pthread,%d\n", errno);
    return 1;
  }
 
  char c ;
  while ((c = getchar()) != 'q');
 
  printf("Now terminate the thread!\n");
  flag = 0;              
  
  pthread_cond_signal(&th_cond);
  
  printf("Wait for thread to exit\n");
  pthread_join(thread, NULL);
  printf("Bye\n");
  return 0;
#endif  
}