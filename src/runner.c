#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"

extern ArrayList stdmDataInput();
extern void stdmUserInHandler(Elevator el, User up);
extern void stdmUserOutHandler(Elevator el, User up);
extern State scanStateHandler(Elevator el, State previous);
extern void simulate(int elevator_start, ArrayList user_data, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State), void (*postRunHandler)(Elevator, ArrayList, int));

int main(){
	ArrayList user_data = stdmDataInput();
	simulate(LOWEST_FLOOR, user_data, stdmUserInHandler, stdmUserOutHandler, scanStateHandler, NULL);
}

