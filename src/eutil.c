#include <stdlib.h>
#include "eutil.h"

UserList ar_new(int initialSize, bool canExpand){
	if(initialSize < 1)
		return NULL;
	UserList ar = malloc(sizeof(struct userList));
	if(ar == NULL)
		return NULL;
	User * list = malloc(sizeof(User) * initialSize);
	if(list == NULL){
		free(ar);
		return NULL;
	}
	for(int i = 0; i < initialSize; i++)
		*(list + i) = NULL;
	ar->canExpand = canExpand;
	ar->size = initialSize;
	ar->length = 0;
	ar->list = list;
	return ar;
}

static bool ar_expand(UserList ar){
	if(!ar->canExpand)
		return false;
	User * new_list = realloc(ar->list, sizeof(User) * (ar->size + ar->size / 2));
	if(new_list == NULL)
		return false;
	ar->list = new_list;
	return true;

}

bool ar_add(UserList ar, User up){
	if(ar == NULL || up == NULL)
		return false;
	if(ar->length == ar->size && !ar_expand(ar))
		return false;
	*(ar->list + ar->length++) = up;
	return true;
}

User user_new(int atime, int ffloor, int tfloor){
	if(atime < 0 || ffloor == tfloor)
		return NULL;
	User up = malloc(sizeof(user));
	if(up == NULL)
		return NULL;
	up->atime = atime;
	up->ffloor = ffloor;
	up->tfloor = tfloor;
	up->ltime = -1;
	up->wtime = -1;
	return up;
}

bool user_equals(User a, User b){
	if(a == NULL && b == NULL)
		return true;
	if(a == NULL || b == NULL)
		return false;
	return a == b ||
			(  a->atime == b->atime
			&& a->ffloor == b->ffloor
			&& a->ltime == b->ltime
			&& a->tfloor == b->tfloor
			&& a->wtime == b->wtime
			);
}

User user_clone(User up){
	if(up == NULL)
		return NULL;
	User clone = malloc(sizeof(user));
	if(clone == NULL)
		return NULL;
	clone->atime = up->atime;
	clone->ffloor = up->ffloor;
	clone->ltime = up->ltime;
	clone->tfloor = up->tfloor;
	clone->wtime = up->wtime;
	return clone;
}

void user_destroy(User up){
	free(up);
}

bool ar_deleteByValue(UserList ar, User up){
	if(ar == NULL)
		return false;
	for(int i = 0; i < ar->length; i++){
		if(user_equals(*(ar->list + i), up)){
			return ar_delete(ar, i);
		}
	}
	return false;
}

bool ar_delete(UserList ar, int index){
	if(ar == NULL || index >= ar->length || index < 0)
		return false;
	ar->length--;
	for(; index < ar->length; index++){
		*(ar->list + index) = *(ar->list + index + 1);
	}
	return true;
}

User ar_get(UserList ar, int index){
	if(ar == NULL || index >= ar->length || index < 0)
		return NULL;
	return *(ar->list + index);
}

int ar_getSize(UserList ar){
	if(ar == NULL)
		return -1;
	return ar->size;
}

User ar_set(UserList ar, int index, User up){
	if(ar == NULL || index >= ar->length)
		return NULL;
	User old = ar_get(ar, index);
	*(ar->list + index) = up;
	return old;
}

void ar_swap(UserList ar, int a, int b){
	if(ar == NULL || a == b || a >= ar->length || b >= ar->length || a < 0 || b < 0)
		return;
	ar_set(ar, b,
			ar_set(ar, a, ar_get(ar, b)));
}

bool ar_isEmpty(UserList ar){
	return ar->length == 0;
}

void ar_destroy(UserList ar, bool destroy_entry){
	if(ar == NULL)
		return;
	if(destroy_entry)
		for(int i = 0; i < ar->length; i++)
			user_destroy(*(ar->list + i));
	free(ar->list);
	free(ar);
}
