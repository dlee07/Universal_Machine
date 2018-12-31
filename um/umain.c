/*
            um.c

Assignment: UM
Authors: dlee07, alau03

Interface that represents the machine. Creates memory storage for program,
reads in clients program, executes instructed operations 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "seq.h"
#include "segment.h"
#include "operations.h"
#include "umain.h"
#include "io.h"
#include <sys/stat.h>
#include <uarray.h>

int main(int argc, char *argv[]) 
{
    
    uint32_t pcount;
    uint32_t *pptr;

    if (argc < 1) {
        exit(EXIT_FAILURE);
    } else if (argc == 1) {
        fprintf(stderr, "Put filename! \n");
    } else if (argc == 2) {

        FILE *fp = fopen(argv[1], "r");
        
        /* get number of instructions */
        struct stat um;
        stat(argv[1], &um);
        unsigned temp = um.st_size/4;

        /* initialize instructions */
        uint32_t *reg = initial_registers();
        Mem_T mem = initial_mem(fp, temp);
        Seq_T unmap = initial_stack();

        /* set program counter and read first instruction */
        int count = 0;
        UArray_T prog = (UArray_T)Seq_get(mem, 0);
        pptr = (uint32_t*)(uintptr_t)Seq_get(prog, 0);
        pcount = *pptr;
        int a = Read_op(reg, &mem, unmap, pcount, &count);

        uint32_t op = 0;
        uint32_t rA, rB, rC;

        while(a != 7) /* checks for halt */
        {
            
            count++;
            pptr = (uint32_t*)UArray_at(prog, count);
            pcount = *pptr;

            op = (uint64_t)pcount;
            rA = (uint64_t)pcount;
            rB = (uint64_t)pcount;
            rC = (uint64_t)pcount;

            unsigned hi = 4 + 28;
            unsigned left = 64 - hi;
            unsigned right = 64 - 4;
            
            assert(hi <= 64);
            
            assert(left <= 64);
            
            if (left == 64){
                op = 0;
            } else{
                op = op << left; 
            }
            

            assert(right <= 64);
            
            if (right == 64){
                op = 0;
            } else{
                op = op >> right;
            }
            
            // (uint32_t)op;

            hi = 3 + 6;
            left = 64 - hi;
            right = 64 - 3;
            
            assert(hi <= 64);
            
            assert(left <= 64);
            
            if (left == 64){
                rA = 0;
            } else{
                rA = rA << left; 
            }   

            assert(right <= 64);
            
            if (right == 64){
                rA = 0;
            } else{
                rA = rA >> right;
            }
            // (uint32_t)rA;

            hi = 3 + 3;
            left = 64 - hi;
            right = 64 - 3;
            
            assert(hi <= 64);
            
            assert(left <= 64);
            
            if (left == 64){
                rB = 0;
            } else{
                rB = rB << left; 
            }
            
            assert(right <= 64);
            
            if (right == 64){
                rB = 0;
            } else{
                rB = rB >> right;
            }
            // (uint32_t)rB;
            
            hi = 3 + 0;
            left = 64 - hi;
            right = 64 - 3;
            
            assert(hi <= 64);
            
            assert(left <= 64);
            
            if (left == 64){
                rC = 0;
            } else{
                rC = rC << left; 
            }

            assert(right <= 64);
            
            if (right == 64){
                rC = 0;
            } else{
                rC = rC >> right;
            }


            if (a == 12) { /* resets program to the new program */
                prog = (UArray_T)UArray_at(mem, 0);
            }
        
        }

        free_mem(mem);
        free_stack(unmap);
        fclose(fp);
        free(reg);
    }

    return 0;
}

/* Does: Reads the op code, calls a switch statement that calls the 
    appropriate 

*/
int Read_op (uint32_t *ray, Mem_T *mem_storage, Seq_T unmapped_IDs, 
                    uint32_t pcount, int *count){

    uint32_t op = 0;
    uint32_t rA, rB, rC;
    
    op = (uint32_t)Bitpack_getu((uint64_t)pcount, 4, 28);
    rA = (uint32_t)Bitpack_getu((uint64_t)pcount, 3, 6);
    rB = (uint32_t)Bitpack_getu((uint64_t)pcount, 3, 3);
    rC = (uint32_t)Bitpack_getu((uint64_t)pcount, 3, 0);

    /* switch statement to carry out instruction based on op code */
    switch(op){
        case 0 : 
            cond_move((ray + rA), (ray + rB), (ray + rC)); 
            break;
        case 1 :
            seg_load(mem_storage, (ray + rA), *(ray + rB), *(ray + rC));
            break;
        case 2 : 
            seg_store(mem_storage, *(ray + rA), *(ray + rB), *(ray + rC)); 
            break;
        case 3 :
            add((ray + rA), (ray + rB), (ray + rC)); break;
        case 4 : 
            mult((ray + rA), (ray + rB), (ray + rC)); break;
        case 5 :
            divide((ray + rA), (ray + rB), (ray + rC));
            break;
        case 6 :
            bit_nand((ray + rA), (ray + rB), (ray + rC));
            break;
        case 7 :
            return 7; break; /* returns 7 to indicate halt */
        case 8 :
            *(ray + rB) = new_seg (mem_storage, (int)(*(ray +rC)), 
                                    unmapped_IDs); break;
        case 9 :
            free_seg (mem_storage, (ray + rC), unmapped_IDs); break;
        case 10 :
            output(*(ray + rC)); break;
        case 11 :
            input(ray + rC); break;
        case 12 :
            load_prog(mem_storage, *(ray + rB)); 
            *count = (*(ray + rC) - 1); /* change the count to reset program 
                                                                    counter */
            return 12; break;
        case 13 :
            load_value(ray, pcount); break;
        default: 
            break;
    }

    return 0;
}




