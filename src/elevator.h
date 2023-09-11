#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "eutil.h"

#define ELEVATOR_LOADS_MAX 4
#define ELEVATOR_LOADS_RATED 4
#define LOWEST_FLOOR 1
#define HIGHEST_FLOOR 10

typedef struct {
	volatile ArrayList waiting_users;
	ArrayList load_users;
	int current_floor;
	int highest_floor;
	int lowest_floor;
} elevator, *Elevator;

typedef enum el_state {
	UP, DOWN, IDLE
} State;

Elevator el_init();
int el_update(Elevator el, State* statep, int current_time, void (*userInHandler)(Elevator, User), void (*userOutHandler)(Elevator, User), State (*stateHandler)(Elevator, State));
void el_destroy(Elevator);
#endif
