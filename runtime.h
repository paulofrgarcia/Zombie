#ifndef RUNTIME_H
#define RUNTIME_H

#include"ir.h"
#include"runtime.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct horde_node
{
	struct ir_node *orc;
	struct horde_node *next;
};


//selects all ALIVE data, adds them to the horde
void run_init_runtime(struct ir_node *i);

//goes through the horde list, evaluates all alive ones
//updates life and death and evaluates
int run_horde();

#endif
