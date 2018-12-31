/*
			operations.c

Assignment: UM
Authors: dlee07, alau03

Contains the implementation of the operations interface. Functions
execute specific operations and stores results into registers and
memory. 

*/


#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
#include <bitpack.h>
#include <sys/stat.h> 



uint32_t *initial_registers (){
	uint32_t *registers =  malloc(8 * sizeof(uint32_t));

	for (int i = 0; i < 8; i++) {
		*(registers + i) = 0;
	}
	return registers;
}

void free_register (uint32_t* registers){
	free(registers);
}

/**************************************************************************
*							Operator functions
*
***************************************************************************/ 

void cond_move (uint32_t  *a, uint32_t *b, uint32_t  *c){
	if(*c != 0) {
		*a = *b;
	}
	
}

void add (uint32_t  *a, uint32_t *b, uint32_t  *c){
	*a = *b + *c;
}

void mult (uint32_t  *a, uint32_t *b, uint32_t  *c){
	*a = (*b * *c);
}

void divide (uint32_t  *a, uint32_t *b, uint32_t  *c){
	assert(*c != 0); /*should not divide by zero*/
	
	*a = *b / *c;
}

void bit_nand (uint32_t  *a, uint32_t *b, uint32_t  *c){

	uint32_t result = 0;
	result = *b & *c;
	result = ~result;
	*a = result;
}

int halt(){
	
	return 1;
}

void load_value (uint32_t *ray, uint32_t value){
	int rA = (int)Bitpack_getu((uint64_t)value, 3, 25);
	uint32_t temp = Bitpack_getu((uint64_t)value, 25, 0);
	*(ray + rA) = temp;
	
}






