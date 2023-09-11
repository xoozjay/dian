#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"

Elevator el_init(){
	Elevator el = malloc(sizeof(elevator));
	if(el == NULL)
		return NULL;
	ArrayList waiting_users = ar_newArrayList(HIGHEST_FLOOR - LOWEST_FLOOR + 1, true);
	ArrayList load_users = ar_newArrayList(ELEVATOR_LOADS_MAX, false);
	int current_floor = LOWEST_FLOOR;
	int highest_floor = HIGHEST_FLOOR;
	int lowest_floor = LOWEST_FLOOR;
	if(el == NULL || waiting_users == NULL || load_users == NULL){
		free(el);
		ar_destroy(waiting_users, true);
		ar_destroy(load_users, true);
		return NULL;
	}
	el->current_floor = current_floor;
	el->highest_floor = highest_floor;
	el->load_users = load_users;
	el->lowest_floor = lowest_floor;
	el->waiting_users = waiting_users;
	return el;
}

/*
 * return: lower 16bits indicates users out
 *        higher 16bits indicates users in
 */
int el_update(Elevator el, State *statep, int current_time, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User),  State (*stateHandler)(Elevator, State)){
	if(el == NULL)
		return -1;

	int incount = 0, outcount = 0;
	for(int i = 0; i < el->waiting_users->length; i++){
		User aload = ar_get(el->waiting_users, i);
		aload->wtime++;
		if(aload->ffloor == el->current_floor){
			if(!ar_add(el->load_users, aload))
				continue;
			aload->ltime = 0;
			ar_delete(el->waiting_users, i--);
			if(userInHandler != NULL)
				userInHandler(el, aload);
			incount++;
		}
	}

	*statep = (ar_isEmpty(el->load_users) && ar_isEmpty(el->waiting_users)) ? IDLE : stateHandler(el, *statep);
	if(*statep != IDLE){
		if(el->current_floor == el->lowest_floor)
			*statep = UP;
		if(el->current_floor == el->highest_floor)
			*statep = DOWN;
	}
	switch(*statep){
		case UP:
			if(el->current_floor < el->highest_floor)
				el->current_floor++;
			else return -1;
			break;
		case DOWN:
			if(el->current_floor > el->lowest_floor)
				el->current_floor--;
			else return -1;
			break;
		case IDLE:
			break;
		default:
			return -1;
	}
	current_time++;

	for(int i = 0; i < el->load_users->length ; i++){
		User aload = ar_get(el->load_users, i);
		aload->ltime++;
		if(aload->tfloor == el->current_floor){
			ar_delete(el->load_users, i--);
			if(userOutHandler != NULL)
				userOutHandler(el, aload);
			user_destroy(aload);
			outcount++;
		}
	}
	return incount << 16 | outcount;
}

void el_destroy(Elevator el){
	if(el == NULL)
		return;
	ar_destroy(el->load_users, true);
	ar_destroy(el->waiting_users, true);
	free(el);
}
