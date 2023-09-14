
/** This file shows how Operating and maintaining a queue works in C using a self referencing struct Node.
       This example includes functions to add to queue: enqueue, remove from queue: dequeue, check if queue
        is empty: isEmpty, and print the queue. The main function is for demonstration only, the majority of main
        will need to be removed for you to use this code as an actual queue in another application.**/

/*Operating and maintaining a queue */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#include "varlib.h"
 

/* function main begins program execution */
 

/* insert a node a queue tail */
void enqueue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char *value )
{
	QueueNodePtr newPtr; /* pointer to new node */
	newPtr = malloc( sizeof( QueueNode ) );

	if ( newPtr != NULL ) { /* is space available */
		newPtr->argStr = value;
		newPtr->nextPtr = NULL;

/* if empty, insert node at head */
		if ( isEmpty( *headPtr ) ) {
			*headPtr = newPtr;
		} /* end if */
		else {
			( *tailPtr )->nextPtr = newPtr;
		} /* end else */
	
		*tailPtr = newPtr;
	} /* end if */
	else {
		printf( "%s not inserted. No memory available.\n", value );
	} /* end else */
} /* end function enqueue */

/* remove node from queue head */
char dequeue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr )
{
	char *value; /* node value */
	QueueNodePtr tempPtr; /* temporary node pointer */
	
	value = ( *headPtr )->argStr;
	tempPtr = *headPtr;
	*headPtr = ( *headPtr )->nextPtr;

	/* if queue is empty */
	if ( *headPtr == NULL ) {
		*tailPtr = NULL;
	} /* end if */

	free( tempPtr );
	return *value;
} /* end function dequeue */

/* Return 1 if the list is empty, 0 otherwise */
int isEmpty( QueueNodePtr headPtr )
{
	return headPtr == NULL;
} /* end function isEmpty */

/* Print the queue */
// void printQueue( QueueNodePtr currentPtr )
// {
// /* if queue is empty */
// 	if ( currentPtr == NULL ) {
// 		printf( "Queue is empty.\n\n" );
// 	} /* end if */
// 	else {
// 		printf( "The queue is:\n" );

// /* while not end of queue */
// 		while ( currentPtr != NULL ) {
// 			printf( "%c --> ", currentPtr->argStr );
// 			currentPtr = currentPtr->nextPtr;
// 		} /* end while */

// 		printf( "NULL\n\n" );
// 	} /* end else */

// } /* end function printQueue */

char * queueSearch(QueueNodePtr currentPtr, char *name)
{
	int i;
	char temp;
	
	printf("%s", currentPtr->argStr);
	return 0;

}

int queueStore(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char *name, char *val) {
	char	*s;
	int	rv = 1;
	int len = strlen(name);

	QueueNodePtr current = *headPtr;

	while (current != NULL) {
		if (strncmp(current->argStr, name, len) == 0) {
			free(current->argStr);
			current->argStr = new_string(name, val);
			rv = 0;
			break;
		}

		current = current->nextPtr;
	}

	if (current->nextPtr == NULL) {
        s = new_string(name, val);
        if (s != NULL) {
            enqueue(headPtr, tailPtr, s);
            rv = 0;
        }
    }
	
	return rv;
}