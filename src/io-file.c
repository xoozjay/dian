#include <stdlib.h>
#include <stdio.h>
#include "eutil.h"
#include "elevator.h"
/*
 * input format:
 * <elevator floor>
 * <floor from> <floor to> <time>
 * <floor from> <floor to> <time>
 * ...
 */

FILE *data, *out;

int finit(char datafile[], char outfile[]){
	int res = 0;
	data = fopen(datafile, "r");
	out = fopen(outfile, "a");
	if(data == 0)
		res |= 1;
	if(out == 0)
		res |= 2;
	return res;
}

ArrayList fdataInput(int * elevator_start){
	scanf("%d", elevator_start);
	int atime, ffloor, tfloor;
	ArrayList ar = ar_newArrayList(6, true);
	while(scanf("%d %d %d", &ffloor, &tfloor, &atime) == 3){
		User up = user_new(atime, ffloor, tfloor);
		ar_add(ar, up);
	}
	return ar;
}

void fuserInHandler(Elevator el, User up){
	fprintf(out, "User In  At:%2d Time:%2d Loads:%d\n", el->current_floor, up->wtime + up->atime, el->load_users->length);
}

void fuserOutHandler(Elevator el, User up){
	fprintf(out, "User Out At:%2d Time:%2d Loads:%d\n", el->current_floor, up->wtime + up->atime + up->ltime, el->load_users->length);
}
