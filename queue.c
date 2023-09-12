
/** This file shows how Operating and maintaining a queue works in C using a self referencing struct Node.
       This example includes functions to add to queue: enqueue, remove from queue: dequeue, check if queue
        is empty: isEmpty, and print the queue. The main function is for demonstration only, the majority of main
        will need to be removed for you to use this code as an actual queue in another application.**/

/*Operating and maintaining a queue */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
 

/* function main begins program execution */
int main( void )
{
	QueueNodePtr headPtr = NULL; /* initialize headPtr */
	QueueNodePtr tailPtr = NULL; /* initialize tailPtr */

	char temp1;
	int choice; /* user's menu choice */
	char item; /* char input by user */
	instructions(); /* display the menu */
	printf( "? " );
	scanf( "%d", &choice );

/* while user does not enter 3 */
	while ( choice != 3 ) {
		switch( choice ) {

/* enqueue value */
			case 1:
				printf( "Enter a character: " );
				scanf( "\n%c", &item );
				enqueue( &headPtr, &tailPtr, item );
				printQueue( headPtr );
			break;
	
	/* dequeue value */
			case 2:
	/* if queue is not empty */
				if ( !isEmpty( headPtr ) ) {
					item = dequeue( &headPtr, &tailPtr );
				printf( "%c has been dequeued.\n", item );
				} /* end if */
				printQueue( headPtr );
			break;
			
			case 3:
				temp1 = queueSearch(&headPtr, "ass");
			break;
			
			default:
				printf( "Invalid choice.\n\n" );
				instructions();
			break;
		} /* end switch */

		printf( "? " );
		scanf( "%d", &choice );
	} /* end while */

	printf( "End of run.\n" );
	return 0; /* indicates successful termination */
} /* end main */

/* display program instructions to user */
void instructions( void )
{
	printf ( "Enter your choice:\n"
	" 1 to add an item to the queue\n"
	" 2 to remove an item from the queue\n"
	" 3 to end\n" );
} /* end function instructions */

 

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
		printf( "%c not inserted. No memory available.\n", value );
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
	return value;
} /* end function dequeue */

/* Return 1 if the list is empty, 0 otherwise */
int isEmpty( QueueNodePtr headPtr )
{
	return headPtr == NULL;
} /* end function isEmpty */

/* Print the queue */
void printQueue( QueueNodePtr currentPtr )
{
/* if queue is empty */
	if ( currentPtr == NULL ) {
		printf( "Queue is empty.\n\n" );
	} /* end if */
	else {
		printf( "The queue is:\n" );

/* while not end of queue */
		while ( currentPtr != NULL ) {
			printf( "%c --> ", currentPtr->argStr );
			currentPtr = currentPtr->nextPtr;
		} /* end while */

		printf( "NULL\n\n" );
	} /* end else */

} /* end function printQueue */

char * queueSearch(QueueNodePtr currentPtr, char *name)
{
	int i;
	char temp;
	
	printf("%s", currentPtr->argStr);
	return 0;

}