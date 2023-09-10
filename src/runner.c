#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"

extern ArrayList stdDataInput(int *);
extern void stdUserInHandler(Elevator el, User up);
extern void stdUserOutHandler(Elevator el, User up);
extern State scanStateHandler(Elevator el, State previous);
extern void simulate(int elevator_start, ArrayList user_data, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State), void (*postRunHandler)(Elevator, ArrayList, int));

int main(){
	int elevator_start;
	ArrayList user_data = stdDataInput(&elevator_start);
	simulate(elevator_start, user_data, stdUserInHandler, stdUserOutHandler, scanStateHandler, NULL);
}

