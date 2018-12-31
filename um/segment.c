/*
			Segment.c

Assignment: UM
Authors: dlee07, alau03

Interface that updates the memory storage. 

*/

#include "segment.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

void print(Seq_T ray1);

uint32_t extract(FILE *fp);

Seq_T initial_mem (FILE *input, unsigned size)
{
	uint32_t word = 0;
	
	Seq_T mem = Seq_new(0);
	Seq_T prog = Seq_new(0);
	Seq_addhi(mem, prog); /*adds a sequence of words to segment 0*/
	/*extract reads it big-endian order*/
	for(unsigned i = 0; i < size; i++){
		word = extract(input);
		Seq_addhi(prog, (void*)(uintptr_t)word);

	}

	return mem;
}

Seq_T initial_stack(){
	Seq_T Unmap = Seq_new(0);
	Seq_addhi(Unmap, (uint32_t *)1);
	Seq_remlo(Unmap);
	return Unmap;
}

void free_mem (Seq_T mem){
	for(int i = 0; i < Seq_length(mem); i++){
		Seq_T temp = (Seq_T)Seq_get(mem, i);
		if(temp != NULL)
			Seq_free(&temp);
	}

	Seq_free(&mem);
}

void free_stack(Seq_T stack){
	Seq_free(&stack);
}

int new_seg (Seq_T mem, int num_words, Seq_T stack){
	/*get an unmapped ID*/
	uint32_t index = get_id(mem, stack); 
	/*initialize a new sequence to put in segment #index*/
	Seq_T value = Seq_new(num_words);
	for(int i = 0; i < num_words; i++){
		Seq_addhi(value, NULL);
	}
	assert(value != NULL);
	/*inserts the array*/
	Seq_put(mem, index, value);
	return index;
}

uint32_t get_id (Seq_T mem, Seq_T stack){
	int temp2 = Seq_length(stack);
	/*if stack size is empty current memory is segmented*/
	if(temp2 == 0){
		Seq_addhi(mem, NULL);
		int size = (Seq_length(mem) - 1);
		return size;
	}
	/*there is at least 1 unmapped segment in current memory*/
	else{
		 uint32_t index = (uint32_t)(uintptr_t)Seq_remlo(stack); 
		 return index;
	}
}

void seg_load (Seq_T mem, uint32_t *rA, int seg_id, int offset){
		
		int size = Seq_length(mem);
		/*makes sure segID is within the region of memory*/
		assert(seg_id < size);

		/*get the sequence at that ID*/
		Seq_T temp = (Seq_T)Seq_get(mem, seg_id);
		int seg_length = Seq_length(temp);
		/*makes sure address is within bounds of segment*/
		assert(offset < seg_length);

		/*retrieves the value*/
		uint32_t value = (uint32_t)(uintptr_t)Seq_get(temp, offset);
		*rA = value;
}

void seg_store (Seq_T mem, int seg_id, int offset, uint32_t value){

		int size = Seq_length(mem);

		assert(seg_id < size);
		/*finds the location in memory segment*/
		Seq_T temp = (Seq_T)Seq_get(mem, seg_id);
		int seg_length = Seq_length(temp);
		assert(offset < seg_length);
		/*stores the value*/
		Seq_put(temp, offset, (void*)(uintptr_t)value);
} 

void free_seg (Seq_T mem, uint32_t *seg_id, Seq_T stack){
	assert(*seg_id != 0);
	/*gets the desired memory segment and unmaps it */
	Seq_T temp = (Seq_T)Seq_get(mem, *seg_id);
	assert(temp != NULL);
	Seq_free(&temp);

	/*makes sure segment pointer points to NULL*/
	Seq_put(mem, *seg_id, NULL);
	Seq_addhi(stack, (void *)(uintptr_t)*seg_id);
}

void load_prog(Seq_T mem, uint32_t rB){
	
	Seq_T temp = (Seq_T)Seq_get(mem, rB);

	int original = Seq_length(temp);
	/*segment ID is not 0, perform copy of the sequence in segment[rB] */ 
	if (rB != 0) {

			Seq_T temp1 = (Seq_T)Seq_get(mem, 0);
			Seq_free(&temp1);
			Seq_T temp_new = Seq_new(0);
			assert(temp_new != NULL);
			Seq_put(mem, 0, temp_new);
			temp1 = (Seq_T)Seq_get(mem, 0);
			for(int i = 0; i < original; i++){
				uint32_t val = (uint32_t)(uintptr_t)
							Seq_get(temp, i);
				Seq_addhi(temp1, (void*)(uintptr_t)val);
			}

	}
	/*if segment ID is zero then makes sure program counter points
	to it.*/
}
/***********************************************************************

					Test functions

***********************************************************************/

/*
Purpose: prints values in a segment
Arguments: Seq_T
Return: none
*/
void print(Seq_T ray1){

	Seq_T program = (Seq_T)Seq_get(ray1, 0);
	for(int i = 0; i < Seq_length(program); i++){
		printf("%x\n", (uint32_t)((uintptr_t)Seq_get(program, i)));
	}

}
/*
* Purpose: reads content of file in big-endian order and packs
* 4 characters into an instruction
* Arguments: FILE
* Return: a uint32_t
*/
uint32_t extract(FILE *fp){
	
	int a = fgetc(fp);
	int b = fgetc(fp);
	int c = fgetc(fp);
	int d = fgetc(fp);

	uint64_t word = 0;
	
	word = Bitpack_newu(word, 8, 24, (uint64_t)a);
	word = Bitpack_newu(word, 8, 16, (uint64_t)b);
	word = Bitpack_newu(word, 8, 8, (uint64_t)c);
	word = Bitpack_newu(word, 8, 0, (uint64_t)d);

	return word;

}
