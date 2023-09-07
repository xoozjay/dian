#include <stdio.h>
#include <stdbool.h>
#include "eutil.h"
#include "elevator.h"
/*
 * input format:
 * <elevator floor>
 * <arrive time> <floor from> <floor to>
 * <arrive time> <floor from> <floor to>
 * ...
 */

ArrayList stdio_man(int * elevator_start){
	scanf("%d", elevator_start);
	int atime, ffloor, tfloor;
	ArrayList ar = ar_newArrayList(6, true);
	while(scanf("%d %d %d", &atime, &ffloor, &tfloor) == 3){
		User up = user_new(atime, ffloor, tfloor);
		ar_add(ar, up);
	}
	return ar;
}

void stdUserInHandler(Elevator el, User up){
	printf("User In  At:%2d Time:%2d Loads:%d\n", el->current_floor, up->wtime + up->atime, el->load_users->length);
}

void stdUserOutHandler(Elevator el, User up){
	printf("User Out At:%2d Time:%2d Loads:%d\n", el->current_floor, up->wtime + up->atime + up->ltime, el->load_users->length);
}
