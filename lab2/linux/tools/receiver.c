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


int main(int argc, char *argv[])
{
	int pt;
	mqd_t qdes;
	const char  qname[] = "/mailbox2";
	mode_t mode = S_IRUSR | S_IWUSR;
	struct mq_attr attr;

	attr.mq_maxmsg  = atoi(argv[2]);
	attr.mq_msgsize = 32;
	attr.mq_flags   = 0;	// blocking queue 
	
	double ta;
	double tb;
	double tc;

	sleep(1);
	qdes  = mq_open(qname, O_RDONLY, mode, &attr);
	if (qdes == -1 ) {
		perror("mq_open()");
		exit(1);
	}

	int i;
	for(i=0; i<atoi(argv[1]); i++) {
		// only block for a limited time if queue is empty
		if (mq_receive(qdes, (char *) &pt, 32, 0) == -1) {
			perror("mq_timedreceive() failed\n");
			//printf("Type Ctrl-C and wait for 5 seconds to terminate.\n");
			
		} else {
			printf("%d is consumed\n", pt);
		}
	}


	if (mq_close(qdes) == -1) {
		perror("mq_close() failed");
		exit(2);
	}

	return 0;
}
