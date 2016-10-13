#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum 
{
	semi_c,
	epsilon,
	ques,
	not,
	plus,
	minus,
	mult,
	var,
	digit
} Symbol;

typdef enum
{
	LOADI,
	LOAD,
	STORE,
	ADD,
	SUB,
	MUL,
	READ,
	WRITE
} OpCode;


Symbol sym;
char look_ahead;

static int digit()
{
	
}
static int variable()
{
	
}
static int expr()
{
	
}
static int print()
{
	
}
static int read()
{
	
}
static int assign()
{
	
}
static int stmt()
{
	
}
static int morestmts()
{
	
}
static void stmt_list()
{
	stmt();
	morestmts();
}
static int prgrm()
{
	
}

static void write_op()
{
	case LOADI:
	case LOAd
	case STORE:
	case ADD:
	case SUB:
	case MUL:
	case READ:
	case WRITE:
}







