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
#include <sys/wait.h>


double ta;
double tb;
struct timeval tv;

//list to contain n and b to be passed on to receiver program
char* pro_arg_list[] = {
    NULL,     
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
  };
  
char* con_arg_list[] = {
    NULL,
    NULL,
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

int main(int argc, char *argv[])
{
	int i;
	int j;
	int status;
	int k;
		
	//passing n and b and c and p and id to slave program
	pro_arg_list[0] = "./sender.out";
	pro_arg_list[1] = argv[1]; //n
	pro_arg_list[2] = argv[2]; //b
	pro_arg_list[3] = argv[3]; //p
	pro_arg_list[5] = NULL; //null
	
	con_arg_list[0] = "./receiver.out";
	con_arg_list[1] = argv[1]; //n
	con_arg_list[2] = argv[2]; //b
	con_arg_list[3] = argv[4]; //c
	con_arg_list[5] = NULL; //null
	
	
	//calculating and passing ta
	gettimeofday(&tv, NULL);
	ta = tv.tv_sec + tv.tv_usec/1000000.0;
	//char str[15];
	//sprintf(str, "%d", ta);
	//con_arg_list[5] = str;
	
	for(i = 0; i < atoi(argv[3]); i++)
	{
		char str[15];
		sprintf(str, "%d", i);
		pro_arg_list[4] = str; //id of sender
		
		spawn("./sender.out", pro_arg_list);
		//printf("producer %s created\n", str);
	}
	
	for(j = 0; j < atoi(argv[4]); j++)
	{
		char str[15];
		sprintf(str, "%d", j);
		con_arg_list[4] = str; //id of consumer
		
		spawn("./receiver.out", con_arg_list);
		//printf("consumer %s created\n", str);
	}
	
	
	for(k = atoi(argv[3]) + atoi(argv[4]); k > 0; k--)
	{
		wait(&status);
		if(WIFEXITED(status))
		{
			//normal exit
		}
		else
		{
			//abnormal exit
			printf("abnormal exit");
		}	
	}
	
	//calculating and passing tb
	gettimeofday(&tv, NULL);
	tb = tv.tv_sec + tv.tv_usec/1000000.0;
	
	
	printf("System execution time: %.6lf seconds", tb-ta-1);

	
	
	return 0;
}
