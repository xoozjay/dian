#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"

//int callUpdate(State* statep, Elevator el, int current_time, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State));
void sortList(UserList ar, int start, int end);


void simulate(int elevator_start, UserList user_data, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), int (*stateHandler)(Elevator, Direction), void (*postRunHandler)(Elevator, UserList, int)){
	Elevator el = el_init();
	el->current_floor = elevator_start;
	int current_time = 0;

	sortList(user_data, 0, user_data->length - 1);

	int index = 0;
	Direction state = IDLE;
	while(index < user_data->length){
		// when user_data is not empty
		// which means a new user presses button
		User aload = ar_get(user_data, index);
		if(aload->atime == current_time){
			//add user
			ar_add(el->waiting_users, aload);
			index ++;
			if(index < user_data->length)
				continue;
		}

		//or simulate one step
		el_update(el, &state, userInHandler, userOutHandler, stateHandler, true);
		current_time++;
	}
	while(!(ar_isEmpty(el->waiting_users) && ar_isEmpty(el->load_users))){
		el_update(el, &state, userInHandler, userOutHandler, stateHandler, false);
		current_time++;
	}

	current_time--;
	if(postRunHandler != NULL)
		postRunHandler(el, user_data, current_time);
	el_destroy(el);
	ar_destroy(user_data, false);
}

//int callUpdate(State* statep, Elevator el, int current_time, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State)){
//	int res = el_update(el, *statep, current_time, userInHandler, userOutHandler);
////	if(res != 0 && (*statep == STILL_DOWN || *statep == STILL_UP))
////		*statep = NUL;
//	return res;
//}

void sortList(UserList ar, int start, int end){
	if(start >= end)
		return;

	int pivot = ar_get(ar, start)->atime, pivor_index = start;
	int index = start + 1;
	for(int i = index; i <= end; i++){
		if(ar_get(ar, i)->atime < pivot){
			ar_swap(ar, i, index++);
		}
	}
	index--;
	ar_swap(ar, pivor_index, index);

	sortList(ar, start, index - 1);
	sortList(ar, index + 1, end);
}
