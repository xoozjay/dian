#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"
/*
 * input format:
 * <elevator floor>
 * <arrive time> <floor from> <floor to>
 * <arrive time> <floor from> <floor to>
 * ...
 */

ArrayList stdmDataInput(){
	int ffloor, tfloor;
	ArrayList ar = ar_newArrayList(6, true);
	while(scanf("%d %d", &ffloor, &tfloor) == 2){
		User up = user_new(0, ffloor, tfloor);
		ar_add(ar, up);
	}
	return ar;
}

void stdmUserInHandler(Elevator el, User up){
	printf("User In  At:%2d Time:%2d Loads:%d\n", el->current_floor, up->wtime + up->atime, el->load_users->length);
}

void stdmUserOutHandler(Elevator el, User up){
	printf("User Out At:%2d Time:%2d Loads:%d\n", el->current_floor, up->wtime + up->atime + up->ltime, el->load_users->length);
}
