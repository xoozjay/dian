#include <stdbool.h>
#ifndef _EUTIL_H_
#define _EUTIL_H_
typedef struct {
	int atime;
	int wtime;
	int ltime;
	int ffloor;
	int tfloor;
} user, *User;
typedef struct arrayList {
	int length;
	int size; // size >= length >= 0
	bool canExpand;
	User * list;
} *ArrayList;

User user_new(int, int, int);
bool user_equals(User, User);
User user_clone(User);
void user_destroy(User);
ArrayList ar_newArrayList(int initialSize, bool canExpand);
bool ar_add(ArrayList, User);
bool ar_deleteByValue(ArrayList, User);
bool ar_delete(ArrayList, int);
User ar_get(ArrayList, int);
int ar_getSize(ArrayList);
User ar_set(ArrayList, int, User);
void ar_swap(ArrayList ar, int a, int b);
bool ar_isEmpty(ArrayList);
void ar_destroy(ArrayList, bool);
#endif
