#ifndef DATA_TYPES_H
#define DATA_TYPES_H

//stated definitions
#define UNDEAD	0
#define ALIVE	1
#define DEAD	2

//operations definitions
//Arithmetic
#define ADD 		0
#define SUB 		1
#define MUL		2
#define DIV 		3
#define MOD 		4
//logical
#define EQUALS		5
#define NOTEQUAL	6
#define GREATER		7
#define LESS		8
#define GREATEREQ	9
#define LESSEQ		10
//boolean
#define IF		11
//life and death
#define LIFE		12
#define ZOMBIE		13

//not operations, other types
#define CONS		95
#define INPUT		96
#define OUTPUT		97

struct zombie_datum
{
	char *name; //can be NULL for unnamed data
	int state; //alive, dead, undead
	int operation; //operation, completed term e.g., constant, input or output
	struct zombie_datum *first; //pointer to first operand
	struct zombie_datum *second; //pointer to second operand
};

#endif
