#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/*
* 					io.h 
* Authors: dlee07, alau03
* Interface that convert register values into ascii values
*/

/*
* Purpose: takes in a pointer to register and sets the input
* to the dereferenced pointer
* Arguments: uint32_t*
* Return: none
*/
void input(uint32_t *rc);
/*
* Purpose: prints out a value into an ASCII Value
* Argument: uint32_t
* Return: none
*/
void output(uint32_t val);
