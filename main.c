#include<stdio.h>
#include"parser.tab.h"
#include "ast.h"
#include"ir.h"
#include"lin_ast.h"

extern FILE *yyin;
extern struct lin_ast_node *last;


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Error: usage \"hc <file_name>\".\n");
		return 0;
	}
	yyin = fopen(argv[1],"r");
	if(yyin == NULL)
	{
		printf("Error: could not open file %s.\n",argv[1]);
		return 0;
	}	

	//parse program: creates AST
	yyparse();

	//checks AST correctness
	if(ast_typecheck())
	{
		printf("Error: terminating...\n");
		return 0;
	}

	//ast_print_ast(ast, 0);

	//Linearize AST
	lin_gen_last(ast);

	lin_print_last(last);

	//generate IR
	//ir_gen_ir();
	return 0;
}
