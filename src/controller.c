#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"

int callUpdate(State* statep, Elevator el, int current_time, bool isListChanged, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State));
void sortList(ArrayList ar, int start, int end);

void simulate(ArrayList user_data, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State), void (*postRunHandler)(Elevator, ArrayList, int)){
	Elevator el = el_init();
	int current_time = 0;

	sortList(user_data, 0, user_data->length - 1);

	int index = 0;
	State state = IDLE;
	while(index < user_data->length){
		User aload = ar_get(user_data, index);
		bool isListChanged = false;
		if(aload->atime == current_time){
			isListChanged = true;
			ar_add(el->waiting_users, aload);
			index ++;
			continue;
		}

		callUpdate(&state, el, current_time, isListChanged, userInHandler, userOutHandler, stateHandler);
		current_time++;
	}
	while(!(state == IDLE || (ar_isEmpty(el->waiting_users) && ar_isEmpty(el->load_users)))){
		callUpdate(&state, el, current_time, false, userInHandler, userOutHandler, stateHandler);
		current_time++;
	}

	current_time--;
	postRunHandler(el, user_data, current_time);
	el_destroy(el);
	ar_destroy(user_data, true);
}

int callUpdate(State* statep, Elevator el, int current_time, bool isListChanged, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State)){
	if(isListChanged || !(*statep == STILL_DOWN || *statep == STILL_UP))
		*statep = stateHandler(el, *statep);
	int res = el_update(el, *statep, current_time, userInHandler, userOutHandler);
	if(res != 0 && (*statep == STILL_DOWN || *statep == STILL_UP))
		*statep = NUL;
	return res;
}

void sortList(ArrayList ar, int start, int end){
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

