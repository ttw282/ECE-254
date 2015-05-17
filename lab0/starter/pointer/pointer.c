/**
 * @file:  pointer.c
 * @brief: Lab0-A, to demonstrate C structure and pointer usage
 * @author:yqhuang@uwaterloo.ca
 * @date:  2013/05/05
 */
#include <stdio.h>
#include <stdlib.h>

/* To model a point in 2D terminal screen*/
struct point {
	int x;	/* x coordinate */
	int y;	/* y coordinate */
};


int main(void)
{
	/* The memory of a_point is allocated on the process stack at run time */
	struct point a_point;

	/* The ptr contains the address of a_point variable */
	struct point *ptr = &a_point;


	/* First method: set the value of a point structure through a struct variable*/
	a_point.x = 0;
	a_point.y = 0;
	/* Use debugger: we can see the following are true: 
	   a_point.x == 0;
	   ptr->x    == 0;

	   a_point.y == 0; 
	   ptr->y    == 0.
	*/


	/* Second method: set the value of a point structure through a pointer */
	ptr->x = 3;
	ptr->y = 3;
	/* Use debugger: we can see the following are true: 
	   a_point.x == 3;
	   ptr->x    == 3;

	   a_point.y == 3; 
	   ptr->y    == 3.
	*/

	/* Third method: set the value of a point structure by deferencing a pointer */
	(*ptr).x = 5;
	(*ptr).y = 5;

	/* Use debugger: we can see the following are true: 
	 * a_point.x == 5;
	 * ptr->x    == 5;
	 *
	 * a_point.y == 5; 
	 * ptr->y    == 5.
	*/

	/* Switch the ptr to memory dynamically allocated from heap */
	ptr = (struct point *)malloc(sizeof(struct point));


	/* 
	 *  Assign new value to the new point 
	 *  NOTE that ptr no longer points to a_point!
	 */
	ptr->x = 10;
	ptr->y = 10;

	/* 
	 * Use debugger: we can see the following are true: 
	 * a_point.x == 5 ;
	 * ptr->x    == 10;
	 *
	 * a_point.y == 5 ;
	 * ptr->y    == 10.
	 */

	free(ptr);

	return(0);
}
