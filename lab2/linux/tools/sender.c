/**
 * @file:   os/lab1/mqueue/sender.c
 * @brief:  send random points to a POSIX queue. Type 'q' to terminate. 
 * @author: ece254/mte241 lab staff 
 * @date:   2012/09/20
 * NOTES: 
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
//#include "common.h"
//#include "point.h"


double ta;
double tb;
double tc;
struct timeval tv;


char* arg_list[] = {
    NULL,     
    NULL,
    NULL,
    NULL
  };

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


void producer(int n,int b)
{
	mqd_t qdes;
	const char  qname[] = "/mailbox2";	//queue name must start with '/'. man mq_overview
	mode_t mode = S_IRUSR | S_IWUSR;
	struct mq_attr attr;

	int pt;
	
	attr.mq_msgsize = 4;
	attr.mq_maxmsg  = b;
	
	attr.mq_flags   = 0;		// blocking queue 

	gettimeofday(&tv, NULL);
	ta = tv.tv_sec + tv.tv_usec/1000000.0;
	
	spawn("./receiver.out", arg_list);
	
	
	
	qdes  = mq_open(qname, O_RDWR | O_CREAT, mode, &attr);
	if (qdes == -1 ) {
		perror("mq_open() failed");
		exit(1);
	}
	
	gettimeofday(&tv, NULL);
	tb = tv.tv_sec + tv.tv_usec/1000000.0;

	srand(time(0));

	int i;
	for(i=0; i<n; i++)
	 {
		pt = rand() % n;
		
		if (mq_send(qdes, (char *)&pt, 4, 0) == -1) {
			perror("mq_send() failed");
		}
		//printf("random char %d\n", pt);
	}
	gettimeofday(&tv, NULL);
	tc = tv.tv_sec + tv.tv_usec/1000000.0;
		
	if (mq_close(qdes) == -1) {
		perror("mq_close() failed\n");
		exit(2);
	}

	if (mq_unlink(qname) != 0) {
		perror("mq_unlink() failed\n");
		exit(3);
	}
	
	printf("time to initialize system: %.6lf seconds\n", tb-ta);
	printf("time to transmit data: %.6lf seconds\n", tc-tb);
	
}


int main(int argc, char *argv[])
{
	arg_list[0] = "receiver";
	arg_list[1] = argv[1];
	arg_list[2] = argv[2];
	arg_list[3] = NULL;

	producer(atoi(argv[1]),atoi(argv[2]));
	
	return 0;
}
