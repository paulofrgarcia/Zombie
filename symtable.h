#ifndef SYMTABLE_H
#define SYMTABLE_H

#include"ast.h"

struct sym_node
{
	char *name;
	struct ast_node *ast_entry;
	struct sym_node *next;
};



void sym_add_sym(char *s, struct ast_node *a);
int sym_valid_datum(char *i);

#endif
