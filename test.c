#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	char filename[20];
	strcpy(filename,argv[1]);

	FILE * file;
	file = fopen( filename , "r");

	if (file){
		printf("got the file called: %s \n",filename);
	}

	return 0;
}

