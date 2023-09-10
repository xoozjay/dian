#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"

State scanStateHandler(Elevator el, State previous){
	switch(previous){
	case IDLE:
		return UP;
	case UP:
		int highest_floor = el->lowest_floor;
		for(int i = 0; i < el->load_users->length; i++){
			User aload = ar_get(el->load_users, i);
			if(aload->tfloor > highest_floor)
				highest_floor = aload->tfloor;
		}
		for(int i = 0; i < el->waiting_users->length; i++){
			User aload = ar_get(el->waiting_users, i);
			if(aload->ffloor > highest_floor)
				highest_floor = aload->ffloor;
		}
		if(highest_floor > el->current_floor)
			return UP;
		return DOWN;
	case DOWN:
		int lowest_floor = el->highest_floor;
		for(int i = 0; i < el->load_users->length; i++){
			User aload = ar_get(el->load_users, i);
			if(aload->tfloor < lowest_floor)
				lowest_floor = aload->tfloor;
		}
		for(int i = 0; i < el->waiting_users->length; i++){
			User aload = ar_get(el->waiting_users, i);
			if(aload->ffloor < lowest_floor)
				lowest_floor = aload->ffloor;
		}
		if(lowest_floor < el->current_floor)
			return DOWN;
		return UP;
	default:
		return IDLE;
	}
}
