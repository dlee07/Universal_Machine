/*
            test_segment.c

Assignment: UM
Authors: dlee07, alau03
 
This file contains unit-test functions and also a 
implementation of a test program. 

*/


#include "segment.h"
#include <stdio.h>
#include <stdlib.h>


void check_mapped (Seq_T mem, unsigned seg_id);

void check_size (Seq_T mem, unsigned seg_id);

void test_m0stored (Seq_T mem); 

void halt();

/*int main(int argc, char *argv[])
{
    FILE *fp;
    if(argc == 1)
        fp = stdin;
    else if(argc == 2)
        fp = fopen((argv[1]),"r");

    //creates a random series of segmentIDs
    int instructions[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
    
    creates a memory sequene and a sequence for unmapped IDs
    Seq_T memory = initial_mem(fp);
    Seq_T unmapped = initial_stack();
    
    for(int i = 0; i < 5; i++){
        
        unsigned ID = new_seg(memory, instructions[i]);
        check_size(memory, ID); check that segment stored is 
                                    within the bounds of the memory segment 
    }
    choose a random segment to unmap
    unsigned remov = 2; 
    unsigned new_id;
    //unmap the random segment
    free_seg(memory, remov, unmapped);
    
    //TEST1: tests to make sure a segment ID for the 6th instruction would be
     // equal to the recently unmapped segment ID.
      
    
    new_id = new_seg(memory, instructions[6]);
    
    if (new_id != remov) {
        fprintf(stderr, "Failed to map\n");
        exit(EXIT_FAILURE);
    }

    //TEST2: make sure a new value is not put to an unmapped segment ID. 
    
    new_id = new_seg(memory, instructions[7]);
    
    if (new_id == remov) {
        fprintf(stderr, "Next map will be to unmapped mem! \n");
        exit(EXIT_FAILURE);
    }

    
    //TEST3: makes sure store and access use the same value.
    
    unsigned offset = 0;
    uint32_t value = 2181038081;
    uint32_t return_value;
    seg_store(memory, new_id, offset, value);

    return_value = seg_access(memory, new_id, offset);

    if (value != return_value) {
        fprintf(stderr, "Failed to store and retrieve! \n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

Seq_T initial_mem (FILE *input){
    (void)input;
    Seq_T mem = Seq_new(0); 
    Seq_T instructions = Seq_new(0);
    Seq_put(mem, 0, (void*)instructions);
    return mem;

}*/

/*************************************************************************
*   Segment interface's unit tests
*************************************************************************/

/*
* Purpose: iterates through the stack of unsegmented IDs and tries to find
* seg_id in the stack. If it is in the stack, the seg_id refers to an unmapped
* ID. 
* Arguments: Seq_T, unsigned 
* Return: none
*/
void check_mapped(Seq_T stack, unsigned seg_id){
    int i = 0;
    while(!Seq_length(stack)){
        if((uint32_t)(uintptr_t)Seq_get(stack, i) == seg_id)
            fprintf(stderr, "Can't use unmapped");
    }
}

/*
* Purpose: if the segmented ID is greated than the size of the memory sequence,
* call halt to throw an error. 
* Arguments: Seq_T, unsigned
* Return: none
*/
void check_size(Seq_T mem, unsigned seg_id){
    if(seg_id > (uint32_t)Seq_length(mem))
        halt();
}

/*
* Purpose: if Segment 0 is empty, then call halt. 
* Arguments: Seq_T
* Return: none
*/
void test_m0stored(Seq_T mem){
    if(Seq_get(mem, 0) == NULL)
        halt();
}

/*
* Purpose: prints an error statement
* Arguments: none
* Return: none
*/
void halt(){
    fprintf(stderr, "HALT");
    exit(EXIT_FAILURE);
}

