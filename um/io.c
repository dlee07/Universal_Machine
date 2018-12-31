/*
* 					io.c 
* Authors: dlee07, alau03
* Interface that contains the implementation of output and input
* functions. 
*/

#include "io.h"

void input(uint32_t *rc){
	int temp = getc(stdin);
	if(temp == EOF)
		*rc = ~0;
	else if(temp >= 0 && temp <= 255)
		*rc = (uint32_t)(temp);
	
}

void output(uint32_t val){
	if(val <= 255)
		fprintf(stdout, "%c", val);
}
