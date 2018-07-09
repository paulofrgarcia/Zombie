#include"ast.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct ast_node *new_ast_datum(char *n, struct ast_node *a, struct ast_node *next)
{
	struct ast_node *node;
	node = (struct ast_node *)malloc(sizeof(struct ast_node));
	node->type = AST_DATUM;
	node->s_exp = a;
	node->n_datum = next;
	//blank
	node->ls_exp = node->rs_exp = NULL;
	node->identifier = NULL;

	return node;
}
struct ast_node *new_ast_sexp(int o, struct ast_node *l, struct ast_node *r)
{
	struct ast_node *node;
	node = (struct ast_node *)malloc(sizeof(struct ast_node));
	node->type = AST_SEXP;
	node->operator = o;
	node->ls_exp = l;
	node->rs_exp = r;
	//blank
	node->s_exp = NULL;
	node->identifier = NULL;
	node->n_datum = NULL;	

	return node;
}

struct ast_node *new_ast_ident(char *i)
{
	struct ast_node *node;
	node = (struct ast_node *)malloc(sizeof(struct ast_node));
	node->type = AST_IDENT;
	node->identifier=i;
	//blank
	node->s_exp = NULL;
	node->ls_exp = node->rs_exp = NULL;
	node->n_datum = NULL;

	return node;
}
struct ast_node *new_ast_cons(int c)
{
	struct ast_node *node;
	node = (struct ast_node *)malloc(sizeof(struct ast_node));
	node->type = AST_CONST;
	node->constant = c;
	//blank
	node->s_exp = NULL;
	node->ls_exp = node->rs_exp = NULL;
	node->n_datum = NULL;

	return node;
}

