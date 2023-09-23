#include <stdlib.h>
#include "eutil.h"
#include "elevator.h"

int scanStateHandler_(Elevator el, Direction previous){
	switch(previous){
	case IDLE:
		return el_getNearestDestinationR(el, el->current_floor, IDLE);
	case UP:
		int highest_floor = LOWEST_FLOOR;
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
			return el_getNearestDestinationR(el, el->current_floor, UP);
		return el_getNearestDestinationR(el, el->current_floor, DOWN);
	case DOWN:
		int lowest_floor = HIGHEST_FLOOR;
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
			return el_getNearestDestinationR(el, el->current_floor, DOWN);
		return el_getNearestDestinationR(el, el->current_floor, UP);
	}
	return 114514;
}

int scanStateHandler(Elevator el, Direction previous){
	int rel = scanStateHandler_(el, previous);
	if(previous == IDLE || rel != 0)
		return rel;
	if(previous == UP)
		return el_getNearestDestinationR(el, HIGHEST_FLOOR, DOWN) + HIGHEST_FLOOR - el->current_floor;
	else
		return el_getNearestDestinationR(el, LOWEST_FLOOR, UP) + LOWEST_FLOOR - el->current_floor;
}
