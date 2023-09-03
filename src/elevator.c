#include <stdio.h>
#include <stdlib.h>
#define PTEXT "At: %2d, Time: %3d, User: %d\n"

int readFromFile(char *, int *, int *, int *);

int main(){
	int from, to, at, time = 0;
	if(readFromFile("level1.2-data.txt", &from, &to, &at) != 0) {
		puts("ERROR: Read File Failed!");
		return -1;
	}
	printf(PTEXT,   at, time, 0);
	time += abs(at - from);
	printf(PTEXT, from, time, 1);
	time += abs(from - to);
	printf(PTEXT, to, time, 0);
}

int readFromFile(char * filepath, int * from, int * to, int * at){
	FILE * fp = fopen(filepath, "r");
	if(fp == NULL)
		return -1;
	fscanf(fp, "%d %d %d", from, to, at);
	return fclose(fp);
}
