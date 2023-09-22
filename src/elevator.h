#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "eutil.h"

#define ELEVATOR_LOADS_MAX 7
#define ELEVATOR_LOADS_RATED 4
#define LOWEST_FLOOR 1
#define HIGHEST_FLOOR 10

typedef struct {
	volatile UserList waiting_users;
	UserList load_users;
	int current_floor;
	int current_time;
	int relevant_movement;
} elevator, *Elevator;

typedef enum {
	IDLE, UP, DOWN
} Direction;

Elevator el_init();
int el_update(Elevator el, Direction *, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), int (*stateHandler)(Elevator, Direction), bool forceStateUpdate);
void el_destroy(Elevator);
int el_getNearestDestinationR(Elevator, int, Direction);
#endif
