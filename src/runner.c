#include <stdlib.h>
#include <time.h>
#include "eutil.h"
#include "elevator.h"

enum algo {
	SCAN, MONKEY
};
enum io {
	STD
};

extern ArrayList stdDataInput(int *);
extern void stdUserInHandler(Elevator el, User up);
extern void stdUserOutHandler(Elevator el, User up);
extern State scanStateHandler(Elevator el, State previous);
extern State monkeyStateHandler(Elevator el, State previous);
extern void simulate(int elevator_start, ArrayList user_data, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State), void (*postRunHandler)(Elevator, ArrayList, int));

int main(){
	int elevator_start;
	void (*userInHandler)(Elevator, User);
	void (*userOutHandler)(Elevator, User);
	State (*stateHandler)(Elevator, State);
	ArrayList (*dataInput)(int *);

	switch(SCAN){ // change algorithm here
	case SCAN:
		stateHandler = scanStateHandler;
		break;
	case MONKEY:
		stateHandler = monkeyStateHandler;
		srand((unsigned int) time(0));
		break;
	}
	switch(STD){
	case STD:
		dataInput = stdDataInput;
		userInHandler = stdUserInHandler;
		userOutHandler = stdUserOutHandler;
		break;
	}

	ArrayList user_data = dataInput(&elevator_start);
	simulate(elevator_start, user_data, userInHandler, userOutHandler, stateHandler, NULL);
}
