/*
			umain.h

Assignment: UM
Authors: dlee07, alau03

Interface that represents the machine. Reads in clients program
and executes instructed operations 

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef uint32_t** Mem_T;
/*
* Purpose: reads an instruction and performs specific operation
* Arguments: a uint32_t, Seq_T, Seq_T, uint32_t, int*
* Return: an int
*/
int Read_op (uint32_t registers[], Mem_T *mem_storage, Seq_T unmapped_IDs, 
				uint32_t word, int *count);