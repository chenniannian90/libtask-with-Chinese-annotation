/* Copyright (c) 2005 Russ Cox, MIT; see COPYRIGHT */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <task.h>

int quiet;
int goal;
int buffer;

#include "taskimpl.h"

void
primetask(void *arg)
{
	Channel *c, *nc;
	int p, i;
	c = arg;

	p = chanrecvul(c);
	printf("task_id:%d rec_p:%d\n", taskrunning->id, p);
	if(p > goal)
		taskexitall(0);
	if(!quiet)
		printf("%d\n", p);
	nc = chancreate(sizeof(unsigned long), buffer);
	taskcreate(primetask, nc, 32768);
	for(;;){
		i = chanrecvul(c);
		printf("task_id:%d rec_i:%d\n", taskrunning->id, i);
		if(i%p){
		    chansendul(nc, i);
		    printf("task_id:%d send_i:%d\n", taskrunning->id, i);
		}

	}
}

void
taskmain(int argc, char **argv)
{
	int i;
	Channel *c;

	if(argc>1)
		goal = atoi(argv[1]);
	else
		goal = 100;
	printf("goal=%d\n", goal);

	c = chancreate(sizeof(unsigned long), buffer);
	taskcreate(primetask, c, 32768);
	for(i=2;; i++)
		chansendul(c, i);
}

void*
emalloc(unsigned long n)
{
	return calloc(n ,1);
}

long
lrand(void)
{
	return rand();
}
