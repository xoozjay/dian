#include <stdlib.h>
#include <time.h>
#include "eutil.h"
#include "elevator.h"

enum algo {
	SCAN, MONKEY
};
enum io {
	STD, FILE
};

extern UserList stdDataInput(int *);
extern void stdUserInHandler(Elevator el, User up);
extern void stdUserOutHandler(Elevator el, User up);
extern int scanStateHandler(Elevator el, Direction previous);
extern int monkeyStateHandler(Elevator el, Direction previous);
extern int finit(char datafile[], char outfile[]);
extern UserList fdataInput(int * elevator_start);
extern void fuserInHandler(Elevator el, User up);
extern void fuserOutHandler(Elevator el, User up);
extern void simulate(int elevator_start, UserList user_data, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), int (*stateHandler)(Elevator, Direction), void (*postRunHandler)(Elevator, UserList, int));

int main(){
	int elevator_start;
	void (*userInHandler)(Elevator, User);
	void (*userOutHandler)(Elevator, User);
	int (*stateHandler)(Elevator, Direction);
	UserList (*dataInput)(int *);

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
	case FILE:
		dataInput = fdataInput;
		userInHandler = fuserInHandler;
		userOutHandler = fuserOutHandler;
		finit("data.txt", "output.log");
	}

	UserList user_data = dataInput(&elevator_start);
	simulate(elevator_start, user_data, userInHandler, userOutHandler, stateHandler, NULL);
}
