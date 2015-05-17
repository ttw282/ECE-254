/**
 * @file:   os/lab/mqueue/receiver.c
 * @brief:  receive a message from POSIX queue. Typle Ctrl-C to quit 
 * @author: ece254/mte241 lab staff
 * @date:   2012/09/20
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <signal.h>
#include "common.h"
#include "point.h"

#define _XOPEN_SOURCE 600

int ta;
int tb;
int tc;

mqd_t qdes;
struct timeval tv;

char  qname[] = "/mailbox1";

int size;

char* arg_list[] = {
    "consumer",     /* argv[0], the name of the program.  */
    NULL      /* The argument list must end with a NULL.  */
  };
	
	int num = 5;


int spawn (char* program, char** arg_list)
{
  pid_t child_pid;

  /* Duplicate this process.  */
  child_pid = fork ();
  if (child_pid != 0)
    /* This is the parent process.  */
    return child_pid;
  else {
    /* Now execute PROGRAM, searching for it in the path.  */
    execvp (program, arg_list);
    /* The execvp function returns only if an error occurs.  */
    fprintf (stderr, "an error occurred in execvp\n");
    abort ();
  }
}

void producer(int n, int b)
{	
srand(time(NULL));
int i = 0;
size = b;
	gettimeofday(&tv, NULL);
	ta = tv.tv_sec + tv.tv_usec/1000000.0;
	
	spawn(NULL, arg_list);
	qdes  = mq_open(qname, 0);

	gettimeofday(&tv, NULL);
	tb = tv.tv_sec + tv.tv_usec/1000000.0;

	while(i < n)
	{
	int pt = rand();
		if(mq_send(qdes, (char *)pt, sizeof(pt), 0) == -1)
			printf("mq_send() failed\n");
			else
				printf("%d was sent\n", pt);
		i++;
	}
	
	gettimeofday(&tv, NULL);
	tc = tv.tv_sec + tv.tv_usec/1000000.0;

	mq_close(qdes);
}

void consumer()
{
struct point pt;
int i = 0;
	qdes  = mq_open(qname, 0);
	while (i < num) {
		if(mq_receive(qdes, (char *)&pt, sizeof(struct point), 0) == -1)
			printf("mq_timedreceive() failed\n");
			else
			printf("%d is consumed \n", &pt);
			printf("time to initialize system: %d \n", (tb-ta));
			printf("time to transmit data: %d \n", (tc-tb));
			i++;
		} 
}


int main(void)
{
	int i;

	producer(20, size);

	return 0;
}
