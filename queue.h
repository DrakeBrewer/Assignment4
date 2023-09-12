/* self-referential structure  Be sure to change to proper data type needed for queue*/
struct queueNode {
	char *argStr; /* define data as a char */
	struct queueNode *nextPtr; 
	int global;/* queueNode pointer */
}; /* end structure queueNode */

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr; 

/* function prototypes */
void printQueue( QueueNodePtr currentPtr );
int isEmpty( QueueNodePtr headPtr );
char dequeue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr );
void enqueue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char *value );
void instructions( void );