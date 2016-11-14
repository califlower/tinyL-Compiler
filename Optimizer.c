/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2016                              *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

static Instruction *head;

/**********
	Recursively traces out a path through the linked list starting at a WRITE node
	If the next node modifies some variable used by the WRITE node it will be marked critical
**********/

void trace(Instruction *ptr, int field)
{
	
    if (ptr && ptr -> field1 == field)
	{
		ptr -> critical = 'y';
		
		if(ptr -> opcode == 1)
			return;
		
		else if (ptr -> prev)
		{
			trace(ptr -> prev, ptr -> field2);
			trace(ptr -> prev, ptr -> field3);
		}
	}
	else if (ptr -> prev)
	{
		trace(ptr -> prev, field);
	}

}
/**********
	Clean up linked list of any non critical code
	Simply frees the nodes and removes them from the list
**********/

void clean(Instruction *ptr)
{
	while (ptr)
	{
		if (ptr -> prev == NULL && ptr -> critical == 'n')
		{
			ptr = ptr -> next;
			head = ptr;
			free(ptr -> prev);
			ptr -> prev = NULL;
		}
		else if (ptr -> critical == 'n')
		{
			Instruction *t = ptr;
			ptr = ptr -> prev;
			ptr -> next = t -> next;
			ptr -> next -> prev = ptr;
			free(t);
			ptr = ptr -> next;
		}
		else
		{
			ptr = ptr -> next;
		}
			
		
	}	
}
/**********
	Inits all with a char value of 'y' or 'n' marking critical and non critical code
	WRITE, and READ are marked critical automatically
	Calls trace on any WRITE node fixing any case that has more than 1 write output
	instead of automatically assuming that there is only 1 write at the end
**********/

void init(Instruction *ptr)
{
	while (ptr)
	{
		if (ptr -> opcode == 7 && ptr -> prev)
		{
			ptr -> critical = 'y';
			trace(ptr -> prev, ptr-> field1);
		}
		else if (ptr -> opcode == 6)
			ptr -> critical = 'y';
		else
			ptr -> critical = 'n';

		if (ptr -> next)
			ptr = ptr -> next;
		else
			break;
	}
}


int main()
{
	head = ReadInstructionList(stdin);
	
	if (!head) 
	{
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	
	init(head);	
	clean(head);
	
	if (head) 
	{
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}
