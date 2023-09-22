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

UserList stdDataInput(int * elevator_start){
	scanf("%d", elevator_start);
	int atime, ffloor, tfloor;
	UserList ar = ar_new(6, true);
	while(scanf("%d %d %d", &ffloor, &tfloor, &atime) == 3){
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
