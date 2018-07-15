#ifndef IR_H
#define IR_H

#include"ast.h"

//state definitions
#define UNDEAD	0
#define ALIVE	1
#define DEAD	2


struct ir_node;

//Used to implement a list of ir_nodes that depend on us (this datum)
//Will be implemnented as static memory in compilation
struct dependent_node
{
	struct ir_node *d_node;
	struct dependent_node *next;
};

struct ir_node
{
	char *name; //can be NULL for unnamed data
	int state; //alive, dead, undead
	int operation; //atomic operation to perform
	int value; //resolve value, e.g., constant or result of calculation
	struct dependent_node *depend_list; //List of dependent nodes
	char *ident; //If only one operand (identifier)
	struct ir_node *first; //pointer to first S_exp operand. 
	struct ir_node *second; //pointer to second S_exp operand
	//Pointer to next IR node
	struct ir_node *next;
};

//Adds a new constant datum
struct ir_node *ir_new_const(char *name, int value);

//Adds a new datum that just sources another datum
struct ir_node *ir_new_ident(char *name, char *ident);

//Adds a new complete S_Expression
struct ir_node *ir_new_sexp(char *name, int o, struct ir_node *l, struct ir_node *r);

//Generates the partial IR from the AST
struct ir_node *ir_gen_partial_ir(struct ast_node *a);

//Fixes all dependency pointers in all data
void ir_fix_dependencies(struct ir_node *i);

//Adds dependency dep to entry source
void ir_add_dependency(struct ir_node *source,struct ir_node *dep);

void ir_gen_ir();

#endif
