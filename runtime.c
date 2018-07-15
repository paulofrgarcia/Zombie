#include"ir.h"
#include"runtime.h"
#include"parser.tab.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct horde_node *horde = NULL;

//selects all ALIVE data, adds them to the horde
void run_init_runtime(struct ir_node *i)
{
	int liveones = 0;

	while(i != NULL)
	{
		if(i->state == ALIVE)
		{
			struct horde_node *h=(struct horde_node *)malloc(sizeof(struct horde_node));
			h->orc = i;
			h->next = horde;
			liveones++;
		}
		i = i->next;
	}
	printf("Horde initialized: found %d live ones.\n",liveones);
}

//propagates datum life to other data, kills datum, removes from horde, adds alive ones to horde
void run_prop_life(struct horde_node *h)
{
	
}



//goes through the horde list, evaluates all alive ones
//updates life and death and evaluates
int run_horde()
{
	
}
