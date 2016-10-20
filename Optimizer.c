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

int main()
{
	Instruction *head;
	Instruction *ptr;

	head = ReadInstructionList(stdin);
	ptr = head;
	
	if (!head) 
	{
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	
	while (ptr)
	{
		if (ptr -> opcode == 7 || ptr -> opcode == 6)
			ptr -> critical = 'y';
		else
			ptr -> critical = 'n';

		if (ptr -> next)
			ptr = ptr -> next;
		else
			break;
	}
	
	
	trace(ptr -> prev, ptr-> field1);
	
	ptr = head;
	
	while (ptr)
	{
		if (ptr-> critical=='n')
		{
			if (ptr == head)
			{
				ptr = ptr -> next;
				head = ptr;
				free(ptr -> prev);
			}
			else
			{
				Instruction *t = ptr;
				ptr = ptr -> prev;
				ptr -> next = t -> next;
				ptr -> next -> prev = ptr;
				free(t);
			}
		}
		ptr = ptr -> next;
	}
	
	if (head) 
	{
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}
