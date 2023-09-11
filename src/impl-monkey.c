#include <stdlib.h>
#include "elevator.h"

/*
 * 活跃气氛用
 */
State monkeyStateHandler(Elevator el, State previous){
	return (rand() % 2 == 0) ? UP : DOWN;
}
