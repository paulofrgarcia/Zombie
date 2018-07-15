#include"ir.h"
#include"ast.h"
#include"symtable.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"parser.tab.h"

//List of all program data
//Will be used for interpretation and for compilation
struct ir_node *ir = NULL;

struct ir_node *ir_new_const(char *name, int value)
{
	struct ir_node *i;

	i = (struct ir_node *)malloc(sizeof(struct ir_node));
	i->name = name;
	i->value = value;
	//Completed datum, hence ALIVE
	i->state = ALIVE;

	//No operands
	i->ident = NULL;
	i->first = NULL;
	i->second = NULL;

	//No information on dependents yet
	i->depend_list = NULL;

	i->next = ir;
	ir = i;
	return i;
}


//Adds a new datum that just sources another datum
struct ir_node *ir_new_ident(char *name, char *ident)
{
	struct ir_node *i;

	i = (struct ir_node *)malloc(sizeof(struct ir_node));
	i->name = name;
	i->ident = ident;
	//Not completed datum
	i->state = UNDEAD;
	//Just source
	i->operation = SOURCE;

	//No operands
	i->first = NULL;
	i->second = NULL;

	//No information on dependents yet
	i->depend_list = NULL;

	i->next = ir;
	ir = i;
	return i;
}



//Adds a new complete S_Expression
struct ir_node *ir_new_sexp(char *name, int o, struct ir_node *l, struct ir_node *r)
{
	struct ir_node *i;

	i = (struct ir_node *)malloc(sizeof(struct ir_node));
	
	i->name = name;
	i->first = l;
	i->second = r;
	
	//Not completed datum
	i->state = UNDEAD;
	//Just source
	i->operation = o;

	//No operands
	i->ident = NULL;

	//No information on dependents yet
	i->depend_list = NULL;

	i->next = ir;
	ir = i;
	return i;

		
}



struct ir_node *ir_gen_partial_ir(struct ast_node *a)
{

	struct ir_node *result = NULL;
	if(a != NULL)
	{	
		switch(a->type)
		{
		case AST_DATUM:
		{
			//Is it a constant?
			if(a->s_exp->type == AST_CONST)
			{
				printf("Const %s\n",a->name);
				result = ir_new_const(a->name, a->s_exp->constant);
				
				//move on to next datum
				ir_gen_partial_ir(a->n_datum);
			}
			//Not a constant, S expression or identifier
			else
			{
				//Just depends of another datum?
				if(a->s_exp->type == AST_IDENT)
				{
					printf("IDENT %s\n",a->name);
					result = ir_new_ident(a->name, a->s_exp->identifier);
					
					ir_gen_partial_ir(a->n_datum);
				}
				//Full S_Expression
				else
				{
					printf("FULL Sexp %s\n",a->name); 
					

					result = ir_new_sexp(a->name, a->s_exp->operator, ir_gen_partial_ir(a->s_exp->ls_exp), ir_gen_partial_ir(a->s_exp->rs_exp));
					
					ir_gen_partial_ir(a->n_datum);
				}
			}
		} break;
		case AST_SEXP:
		{
			printf("SEXP Should never be reached\n");
		} break;
		case AST_IDENT:
		{
			printf("IDENT Should never be reached %s\n",a->identifier);
			result = ir_new_ident(a->name, a->identifier);
			
		} break;
		case AST_CONST:
		{
			printf("CONST Should never be reached\n");
		} break;
		default:
		{
			printf("Error: unknown AST type.\n");
			return;
		}		
		}		
	}
	return result;
}




//Adds dependency dep to entry source
void ir_add_dependency(struct ir_node *source,struct ir_node *dep)
{
	struct dependent_node *d;

	if(source == NULL)
		printf("Null dependency\n");

	d = (struct dependent_node *)malloc(sizeof(struct dependent_node));
	d->d_node = dep;
	d->next = source->depend_list;

	source->depend_list = d;
}


//Fixes all dependency pointers in all data
void ir_fix_dependencies(struct ir_node *i)
{
	if(i != NULL)
	{
		//If only sourcing another datum
		if(i->operation == SOURCE)
		{
			printf("Sourcing\n");
			ir_add_dependency(sym_get_ir(i->ident),i);
		}

		//not sourcing another datum, can be CONST (alive) or full S_exp
		//Just fix from S_Exp (const has no deoendencies)
		if(i->state != ALIVE)
		{
			printf("Depend %s\n",i->name);


			ir_add_dependency(i->first,i);
			printf("Depend %s\n",i->name);
			ir_add_dependency(i->second,i);
			printf("Depend %s\n",i->name);
		}
		ir_fix_dependencies(i->next);
	}
}


void ir_gen_ir()
{
	//Generate 1st stage IR from AST
	ir_gen_partial_ir(ast);	
	
	//TODO: backtrack to fix dependencies in each datum
	//ir_fix_dependencies(ir);
}






