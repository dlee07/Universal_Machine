/*/*
			Segment.h

Assignment: UM
Authors: dlee07, alau03

Interface that represents our memory storage. The memory storage 
will be in the form of a squence of sequences. Each of the public
members modifies the status of the memory storage by allocating,
freeing, or adding values into the sequence of sequences. 

*/
#include <seq.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <bitpack.h>

/*
* Function purpose: reads in a program stored in a file, stores it
* into an array, and intializes an another array. At this array[0],
* the array of the program is stored.
* Arguments: FILE
* Return Type: a pointer to Sequence of Seq_T
*/
Seq_T initial_mem (FILE *input, unsigned size);

/*
* Function purpose: creates a new Sequence for unmapped segmented IDs
* Arguments: none
* Return Type: a pointer to sequence of Seq_T
*/
Seq_T initial_stack();

/*
* Function purpose: frees the memory storage
* Arguments: Seq_T
* Return Type: none
*/
void free_mem (Seq_T mem);

/*
* Function purpose: frees the sequence of unmapped IDs
* Arguments: Seq_T
* Return Type: none
*/
void free_stack (Seq_T stack);

/*
* Function purpose: takes in a value and creates a Segment ID
* Arguments: Seq_T, int, Seq_T
* Return Type: int value, which is the segment number
*/
int new_seg (Seq_T mem, int num_words, Seq_T stack); 

/*
* Function purpose: accesses the memory structure and retrieves the 
* uint32_t value at Memory[seg_id][offset].
* Arguments: Seq_T, uint32_t *, int, int
* Return none
*/
void seg_load (Seq_T mem, uint32_t *rA, int seg_id, int offset);

/*
* Function purpose: stores a value into Memory[segnum][offset] 
* Arguments: Seq_T, int, int, uint32_t 
* Return Type: none
*/
void seg_store (Seq_T mem, int seg_id, int offset, uint32_t value); 

/*
* Function purpose: Set the Seq_T mem at the seg_id to NULL and 
* add the number of the seq_id to the Stack
* Arguments: Seq_T, uint32_t*, Seq_T
* Return Type: none
*/
void free_seg (Seq_T mem, uint32_t *seg_id, Seq_T stack);

/*
* Function purpose: gets the next segment_id, checks the stack for u
* nmapped segments, if there are previous unmapped segments, return 
* that value, get the Sequence length and increment it to get the next 
* seg_id.
* Arguments: Seq_T, Seq_T
* Return Type: none
*/
uint32_t get_id (Seq_T mem, Seq_T stack);

/*
* Function purpose: a valid mapped segment is duplicated and a
* deep copy is performed. Then this copied segment is placed into
* segment 0.
* Arguments: Seq_T, uint32_t,
* Return Type: none
*/

void load_prog(Seq_T mem, uint32_t rB);


