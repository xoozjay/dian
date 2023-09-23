#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"

Elevator el_init(){
	Elevator el = malloc(sizeof(elevator));
	if(el == NULL)
		return NULL;
	UserList waiting_users = ar_new(HIGHEST_FLOOR - LOWEST_FLOOR + 1, true);
	UserList load_users = ar_new(ELEVATOR_LOADS_MAX, false);
	if(el == NULL || waiting_users == NULL || load_users == NULL){
		free(el);
		ar_destroy(waiting_users, true);
		ar_destroy(load_users, true);
		return NULL;
	}
	el->current_floor = LOWEST_FLOOR;
	el->current_time = 0;
	el->relevant_movement = 0;
	el->load_users = load_users;
	el->waiting_users = waiting_users;

	return el;
}

static inline bool el_matchDirection(User aload, Direction direction){
//	if(aload == NULL)
//		return false;
	return (direction == IDLE) ||
			(direction == UP && aload->tfloor > aload->ffloor) ||
			(direction == DOWN && aload->tfloor < aload->ffloor);
}

static inline int el_userIn(Elevator el, void (*userInHandler)(Elevator, User), Direction direction){
	int incount = 0;
	if(el->load_users->length < ELEVATOR_LOADS_RATED)
		for(int i = 0; i < el->waiting_users->length; i++){
			User aload = ar_get(el->waiting_users, i);
//			aload->wtime++;
			aload->wtime = el->current_time - aload->atime; //in case of multi-elevator conflict, use this code
			if(aload->ffloor == el->current_floor && el_matchDirection(aload, direction)){
				if(!ar_add(el->load_users, aload))
					continue;
				aload->ltime = 0;
				ar_delete(el->waiting_users, i--);
				if(userInHandler != NULL)
					userInHandler(el, aload);
				incount++;
			}
		}
	return incount;
}

/*
 * return: lower 16bits indicates users out
 *        higher 16bits indicates users in
 */
int el_update(Elevator el, Direction * directionp, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), int (*stateHandler)(Elevator, Direction), bool forceStateUpdate){
	if(el == NULL)
		return -1;

	int incount = 0, outcount = 0;
//	if elevator is stopped, let waiting users enter
	if(el->relevant_movement == 0)
		incount += el_userIn(el, userInHandler, *directionp);

	//move here
	Direction move_direction = IDLE; //000000XY, Y up, X down
	if(forceStateUpdate || el->relevant_movement == 0){
		el->relevant_movement = stateHandler(el, *directionp);
		//hot fix, this is a bad patch!
		if(el->relevant_movement == 0 && !(ar_isEmpty(el->load_users) && ar_isEmpty(el->waiting_users))){
//			int floor;
			if(*directionp == UP){
				move_direction = DOWN;
//				floor = HIGHEST_FLOOR;
			} else {
				move_direction = UP;
//				floor = LOWEST_FLOOR;
			}
			incount += el_userIn(el, userInHandler, move_direction);
			el->relevant_movement = stateHandler(el, *directionp);

//			for(;;){
//				int rel = el_getNearestDestinationR(el, floor, move_direction);
//				if(rel == 0 || (move_direction == UP
//						? (rel + floor) > el->current_floor
//						: (rel + floor) < el->current_floor)){
//					el->relevant_movement = floor - el->current_floor;
//					break;
//				}
//				floor += rel;
//			}
		}
		//end patch
	}
	if(el->relevant_movement != 0){
		//or rather just throw a error?
		if(el->current_floor == LOWEST_FLOOR && el->relevant_movement < 0)
			el->relevant_movement = 1;
		if(el->current_floor == HIGHEST_FLOOR && el->relevant_movement > 0)
			el->relevant_movement = -1;

		//move up
		if(el->relevant_movement > 0)
			move_direction = UP;
		else //if(el->relevant_movement < 0){
			move_direction = DOWN;
		if(move_direction != *directionp)
			incount += el_userIn(el, userInHandler, move_direction);

		if(el->relevant_movement > 0){
			el->relevant_movement--;
			el->current_floor++;
		} else {
		el->relevant_movement++;
		el->current_floor--;
		}
	}
	el->current_time++;

	for(int i = 0; i < el->load_users->length ; i++){
		User aload = ar_get(el->load_users, i);
		aload->ltime = el->current_time - aload->atime - aload->wtime;
		if(aload->tfloor == el->current_floor){
			ar_delete(el->load_users, i--);
			if(userOutHandler != NULL)
				userOutHandler(el, aload);
//			user_destroy(aload);
			outcount++;
		}
	}

	if(directionp != NULL)
		*directionp = move_direction;
	return incount << 16 | outcount;
}

void el_destroy(Elevator el){
	if(el == NULL)
		return;
	ar_destroy(el->load_users, false);
	ar_destroy(el->waiting_users, false);
	free(el);
}

int el_getNearestDestinationR(Elevator el, int floor, Direction de){
	int dest = floor;
	if(de == IDLE){
		int u, d;
		u = el_getNearestDestinationR(el, floor, UP);
		d = el_getNearestDestinationR(el, floor, DOWN);
		if(u == 0) return d;
		if(d == 0) return u;
		if(u + d > 0) return d;
		return u;
	}
	int dirint = de == UP ? 1 : -1;
	for(;dest >= LOWEST_FLOOR && dest <= HIGHEST_FLOOR; dest += dirint){
		for(int i = 0; i < el->load_users->length; i++){
			User aload = ar_get(el->load_users, i);
			if(aload->tfloor == dest && el_matchDirection(aload, de))
				return dest-floor;
		}
		if(el->load_users->length < ELEVATOR_LOADS_RATED) for(int i = 0; i < el->waiting_users->length ; i++){
			User aload = ar_get(el->waiting_users, i);
			if(aload->ffloor == dest && el_matchDirection(aload, de))
				return dest-floor;
		}
	}
	return 0;
}
