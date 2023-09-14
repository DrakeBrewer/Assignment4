/* varlib.c
 *
 * a simple storage system to store name=value pairs
 * with facility to mark items as part of the environment
 *
 * interface:
 *     VLstore( name, value )    returns 1 for 0k, 0 for no
 *     VLlookup( name )          returns string or NULL if not there
 *     VLlist()			 prints out current table
 *
 * environment-related functions
 *     VLexport( name )		 adds name to list of env vars
 *     VLtable2environ()	 copy from table to environ
 *     VLenviron2table()         copy from environ to table
 *
 * details:
 *	the table is stored as an array of structs that
 *	contain a flag for `global' and a single string of
 *	the form name=value.  This allows EZ addition to the
 *	environment.  It makes searching pretty easy, as
 *	long as you search for "name=" 
 *
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	"varlib.h"
#include	"queue.h"
#include	<string.h>

#define	MAXVARS	200		/* a linked list would be nicer */

struct var {
		char *str;		/* name=val string	*/
		int  global;		/* a boolean		*/
	};

static struct var tab[MAXVARS];			/* the table	*/

QueueNodePtr headPtr = NULL; /* initialize headPtr */
QueueNodePtr tailPtr = NULL; /* initialize tailPtr */

char *new_string( char *, char *);	/* private methods	*/
QueueNodePtr find_item(char *, int);

int VLstore( char *name, char *val )
/*
 * traverse list, if found, replace it, else add at end
 * since there is no delete, a blank one is a free one
 * return 1 if trouble, 0 if ok (like a command)
 */
{

	int	rv = 1;

	if (queueStore(&headPtr, &tailPtr, name, val))
		rv = 0;

	return rv;
}

char * new_string( char *name, char *val )
/*
 * returns new string of form name=value or NULL on error
 */
{
	char	*retval;

	retval = malloc( strlen(name) + strlen(val) + 2 );
	if ( retval != NULL )
		sprintf(retval, "%s=%s", name, val );
	return retval;
}

char * VLlookup( char *name )
/*
 * returns value of var or empty string if not there
 */
{
	QueueNodePtr currentPtr;

	while (currentPtr != NULL)
	{
		if ( (currentPtr = find_item(name,0)) != NULL )
			return currentPtr->argStr + 1 + strlen(name);
	}
	

	return "";
}

int VLexport( char *name )
/*
 * marks a var for export, adds it if not there
 * returns 1 for no, 0 for ok
 */
{
	QueueNodePtr currentPtr;
	int	rv = 1;

	if ( (currentPtr = find_item(name,0)) != NULL ){
		currentPtr->global = 1;
		rv = 0;
	}
	else if ( queueStore(&headPtr, &tailPtr, name, "") == 1 )
		rv = VLexport(name);
	return rv;
}

QueueNodePtr find_item( char *name , int first_blank )
/*
 * searches list for an item
 * returns ptr to struct or NULL if not found
 * OR if (first_blank) then ptr to first blank one
 */
{
	int	i;
	int	len = strlen(name);
	char	*s;
	QueueNodePtr currentPtr = headPtr;

	// for( i = 0 ; i<MAXVARS && tab[i].str != NULL ; i++ )
	while(currentPtr->nextPtr != NULL)
	{
		s = currentPtr->argStr;
		if ( strncmp(s,name,len) == 0 && s[len] == '=' ){
			return currentPtr;
		}

		currentPtr = currentPtr->nextPtr;
	}
	if ( currentPtr->nextPtr != NULL && first_blank )
		return currentPtr;
	return NULL;
}


void VLlist()
/*
 * performs the shell's  `set'  command
 * Lists the contents of the variable table, marking each
 * exported variable with the symbol  '*' 
 */
{
	QueueNodePtr currentPtr = headPtr;
	if (isEmpty(headPtr)) {
		printf("No env variables detected");
	} else {
		while(currentPtr != NULL)
		{
			if ( currentPtr->global )
				printf("  * %s\n", currentPtr->argStr);
			else
				printf("    %s\n", currentPtr->argStr);
			currentPtr = currentPtr->nextPtr;
		}
	}
}

int VLenviron2table(char *env[])
/*
 * initialize the variable list by loading array of strings
 * return 1 for ok, 0 for not ok
 */
{
	int     i;
	for (i = 0; env[i] != NULL; i++) {
		if (i == MAXVARS) {
			return 0;
		}
		enqueue(&headPtr, &tailPtr, env[i]);
	}
	printf("test");
	return 1;
}

char ** VLtable2environ()
/*
 * build a list of pointers suitable for making a new environment
 * note, you need to free() this when done to avoid memory leaks
 */
{
	int i, j;
	int n = 0;
    char **envtab;

    // Count the number of variables in the linked list
    QueueNodePtr currentPtr = &headPtr;
    while (currentPtr != NULL) {
		if (currentPtr->global == 1)
        	n++;
        currentPtr = currentPtr->nextPtr;
    }

    // Allocate space for the array of pointers
    envtab = (char **)malloc((n + 1) * sizeof(char *));
    if (envtab == NULL)
        return NULL;

    // Load the array with pointers
    currentPtr = &headPtr;
    while (currentPtr != NULL) {
        envtab[i] = currentPtr->argStr;
        currentPtr = currentPtr->nextPtr;
    }
    envtab[n] = NULL;
    return envtab;
}
