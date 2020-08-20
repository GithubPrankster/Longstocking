#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "insts.h"
#include "up_utils.h"

static size_t cycles = 0;

ls_cpu* cpu;
uint8_t* program;
uint16_t stack[256];

void ls_cpu_init(void)
{
    srand((unsigned int)time(NULL));
    cpu = malloc(sizeof *cpu);
    if(!cpu){
        puts("[LS] ERROR: Could not allocate CPU.");
        return;
    }
    memset(cpu->regs, 0, sizeof cpu->regs);
    cpu->pc = 0x0000;
    cpu->stack_ptr = 0x00;
    cpu->flags = 0b00000000;
    memset(stack, 0, sizeof stack);
}

void ls_cpu_cycle(void)
{
    if(!program){
        puts("[LS] ERROR: No program found.");
        cpu->flags ^= 0b10000000;
        return;
    }

    cpu->regs[0] = 0; /* Hardwire */
    uint8_t op = ls_fetchb();
    if(cpu->flags & DEBUG)
        printf("Current Cycle: %llu\n OP Fetched: %01x\n", cycles++, op);
    table[op]();
}

void ls_cpu_destroy(void)
{
    free(cpu);
}

void ls_prog_load(const char* file)
{
    program = up_file_bin(file);
    if(!program){
        puts("[LS] ERROR: Could not allocate program.");
    }
}

void ls_prog_destroy(void)
{
    free(program);
}