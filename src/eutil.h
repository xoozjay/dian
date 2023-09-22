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
typedef struct userList {
	int length;
	int size; // size >= length >= 0
	bool canExpand;
	User * list;
} *UserList;

User user_new(int, int, int);
bool user_equals(User, User);
User user_clone(User);
void user_destroy(User);
UserList ar_new(int initialSize, bool canExpand);
bool ar_add(UserList, User);
bool ar_deleteByValue(UserList, User);
bool ar_delete(UserList, int);
User ar_get(UserList, int);
int ar_getSize(UserList);
User ar_set(UserList, int, User);
void ar_swap(UserList ar, int a, int b);
bool ar_isEmpty(UserList);
void ar_destroy(UserList, bool);
#endif
