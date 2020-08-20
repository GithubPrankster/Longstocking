#pragma once

#include <stdint.h>

typedef struct{
    uint16_t regs[16];
    uint16_t pc;
    uint8_t stack_ptr, flags;
}ls_cpu;

enum CPU_FLAGS{
    RUN = 0b10000000,
    DEBUG = 0b01000000
};

extern ls_cpu* cpu;
extern uint8_t* program;
extern uint16_t stack[256];

static inline uint8_t ls_fetchb(void)
{
    return program[cpu->pc++];
}

static inline uint16_t ls_fetchw(void)
{
    return (ls_fetchb() << 8) | ls_fetchb(); 
}

void ls_cpu_init(void);
void ls_cpu_cycle(void);
void ls_cpu_destroy(void);

void ls_prog_load(const char* file);
void ls_prog_destroy(void);