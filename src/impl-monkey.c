#include <stdlib.h>
#include "elevator.h"

/*
 * 活跃气氛用
 */
int monkeyStateHandler(Elevator el, Direction previous){
	return (rand() % 2 == 0) ? 1 : -1;
}
