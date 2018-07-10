#include"symtable.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct sym_node *sym_table = NULL;

void sym_add_sym(char *s, struct ast_node *a)
{
	struct sym_node *n;
	n = (struct sym_node *)malloc(sizeof(struct sym_node));
	n->name = s;
	n-> ast_entry = a;
	if(sym_table == NULL)
	{
		sym_table = n;
		sym_table->next = NULL;
	}
	else
	{
		n->next = sym_table;
		sym_table = n;
	}
}

//returns 0 if symbol exists: 1 otherwise
int sym_valid_datum(char *i)
{
	struct sym_node *s;
	s = sym_table;

	while(s != NULL)
	{
		if(strcmp(s->name, i)==0)
			return 0;
		s = s->next;
	}
	printf("Error: Symbol %s is not a defined datum.\n",i);
	return 1;
}
