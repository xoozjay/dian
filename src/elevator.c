#include <stdio.h>
#include <stdlib.h>
#define PTEXT "At: %2d, Time: %3d, User: %d\n"

int main(){
	int from, to, at, time = 0;
	scanf("%d %d %d", &from, &to, &at);
	printf(PTEXT,   at, time, 0);
	time += abs(at - from);
	printf(PTEXT, from, time, 1);
	time += abs(from - to);
	printf(PTEXT, to, time, 0);
}
