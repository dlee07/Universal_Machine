#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <seq.h>
#include "segment.h"

/*
			operations.h

Assignment: UM
Authors: dlee07, alau03

Interface that represents our arithmetic and logical unit. It
will use registers to manipulate values and perform specific 
instructions from the client. Then it will pass the results
to memory.  

*/


/*
* Purpose: Initialises an array of 8 of uint32_t words and returns
* a pointer to the array
* Paramters: none
* Returns: uint32_t*
*/
uint32_t *initial_registers ();

/*
* Purpose: Executes a switch statement that calls a switch statement 
  on the respective op_code and executes the respective function on the 
  three registers passed in
* Paramters: uint32_t
* Returns: none
*/
// void Read_op (Seq_T mem_storage, Seq_T unmapped_IDs, uint32_t word);

/*
* Purpose: Frees the register
* Paramters: Seq_T
* Returns: none
*/
void free_register (uint32_t* registers);

/**************************************************************************
*							Operator functions
*
***************************************************************************/ 

/*
* Purpose: Conditional Move if $r[C] ̸= 0 then $r[A] := $r[B] 
* Arguments: uint32_t*, uint32_t*, uint32_t*
* Return: none
*/
void cond_move (uint32_t *a, uint32_t *b, uint32_t  *c);

/*
* Purpose: Add, $r[A] := ($r[B] + $r[C]) mod 232
* Arguments: uint32_t*, uint32_t*, uint32_t*
* Return: none
*/
void add (uint32_t  *a, uint32_t *b, uint32_t  *c);


/*
* Purpose: Multiplies, $r[A] := ($r[B] × $r[C]) mod 232
* Arguments: uint32_t*, uint32_t*, uint32_t*
* Return: none
*/
void mult (uint32_t  *a, uint32_t *b, uint32_t  *c);

/*
* Purpose: Division, $r[A] := ⌊$r[B] ÷ $r[C]⌋
* Arguments: uint32_t*, uint32_t*, uint32_t*
* Return: none
*/
void divide (uint32_t  *a, uint32_t *b, uint32_t  *c);

/*
* Purpose: Bitwise NAND, $r[A] := ¬($r[B] ∧ $r[C])
* Arguments: uint32_t*, uint32_t*, uint32_t*
* Return: none
*/
void bit_nand (uint32_t  *a, uint32_t *b, uint32_t  *c);

/*
* Purpose: Halts the program by returning 1
* Arguments: none
* Return: int, which is 1. 
*/
int halt();

/*
* Purpose: Takes in the input from the I/O steam and puts it into register C 
* Arguments: uint32_t*
* Return: none
*/
void input (uint32_t *c);

/*
* Purpose: Sets a to the value of the remaining 25 bits that are an 
* unsigned binary value 
* Arguments: uint32_t*, uint32_t
* Return: None
*/
void load_value (uint32_t *ray, uint32_t value);








