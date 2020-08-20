#include <stdlib.h>
#include <stdio.h>
#include "insts.h"

#define reg_ds(v) (((v) >> 4) & 0xF)
#define reg_sc(v) ((v) & 0xF)

/*
    R-TYPE (no not the game)
*/

static void func_ls_add()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG)
        printf("ADD: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    
    cpu->regs[reg_ds(regs)] += cpu->regs[reg_sc(regs)];
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_addc()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("ADDC: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("WORD: %02x\n", word);
    }

    cpu->regs[reg_ds(regs)] += cpu->regs[reg_sc(regs)] + word;
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_sub()
{
    uint8_t regs = ls_fetchb();
    if(cpu->flags & DEBUG)
        printf("SUB: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    

    cpu->regs[reg_ds(regs)] -= cpu->regs[reg_sc(regs)];
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_subc()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("SUBC: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("WORD: %02x\n", word);
    }
    
    cpu->regs[reg_ds(regs)] -= cpu->regs[reg_sc(regs)] + word;
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_and()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG)
        printf("AND: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    
    
    cpu->regs[reg_ds(regs)] &= cpu->regs[reg_sc(regs)];
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_andc()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("ANDC: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("WORD: %02x\n", word);
    }
    
    cpu->regs[reg_ds(regs)] &= cpu->regs[reg_sc(regs)] + word;
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_or()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG)
        printf("OR: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    
    
    cpu->regs[reg_ds(regs)] |= cpu->regs[reg_sc(regs)];
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_orc()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("ORC: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("WORD: %02x\n", word);
    }
    
    cpu->regs[reg_ds(regs)] |= cpu->regs[reg_sc(regs)] + word;
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_xor()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG)
        printf("XOR: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    
    
    cpu->regs[reg_ds(regs)] ^= cpu->regs[reg_sc(regs)];
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_xorc()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("XORC: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("WORD: %02x\n", word);
    }
    
    cpu->regs[reg_ds(regs)] ^= cpu->regs[reg_sc(regs)] + word;
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_lsr()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG)
        printf("LSR: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    
    cpu->regs[reg_ds(regs)] <<= cpu->regs[reg_sc(regs)];
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_lsrc()
{
    uint8_t regs = ls_fetchb();
    uint8_t byte = ls_fetchb();

    if(cpu->flags & DEBUG){
        printf("LSRC: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("BYTE: %02x\n", byte);
    }
    
    cpu->regs[reg_ds(regs)] <<= cpu->regs[reg_sc(regs)] + byte;
    if(cpu->flags & DEBUG)
        printf("RES = %02x\n", cpu->regs[reg_ds(regs)]);
}

static void func_ls_rsh()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG)
        printf("RSH: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    
    cpu->regs[reg_ds(regs)] >>= cpu->regs[reg_sc(regs)];
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

static void func_ls_rshc()
{
    uint8_t regs = ls_fetchb();
    uint8_t byte = ls_fetchb();

    if(cpu->flags & DEBUG){
        printf("RSHC: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("BYTE: %02x\n", byte);
    }
    
    cpu->regs[reg_ds(regs)] >>= cpu->regs[reg_sc(regs)] + byte;
    if(cpu->flags & DEBUG)
        printf("r%01x = %02x\n", reg_ds(regs), cpu->regs[reg_ds(regs)]);
}

/*
    J-TYPE
*/

static void func_ls_jmp()
{
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("JMP: PC = %02X\n", cpu->pc);
        printf("RES = %02x\n", word);
    }

    cpu->pc = word;
}

static void func_ls_jpr()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG){
        printf("JPR: PC = %02X\n", cpu->pc);
        printf("RES = %02x\n", cpu->regs[reg_ds(regs)]);
    }

    cpu->pc = cpu->regs[reg_ds(regs)];

}

static void func_ls_jpe()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("JPE: PC = %02X\n", cpu->pc);
        printf("REGS: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("POSSIBLE RES = %02x\n", word);
    }
    
    if(cpu->regs[reg_ds(regs)] == cpu->regs[reg_sc(regs)]){
        cpu->pc = word;
        if(cpu->flags & DEBUG)
            printf("WENT THROUGH.\n");
    }
}

static void func_ls_jpd()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("JPd: PC = %02X\n", cpu->pc);
        printf("REGS: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("POSSIBLE RES = %02x\n", word);
    }
    
    if(cpu->regs[reg_ds(regs)] != cpu->regs[reg_sc(regs)]){
        cpu->pc = word;
        if(cpu->flags & DEBUG)
            printf("WENT THROUGH.\n");
    }
}

static void func_ls_jpg()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("JPG: PC = %02X\n", cpu->pc);
        printf("REGS: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("POSSIBLE RES = %02x\n", word);
    }
    
    if(cpu->regs[reg_ds(regs)] >= cpu->regs[reg_sc(regs)]){
        cpu->pc = word;
        if(cpu->flags & DEBUG)
            printf("WENT THROUGH.\n");
    }
}

static void func_ls_jpl()
{
    uint8_t regs = ls_fetchb();
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("JPL: PC = %02X\n", cpu->pc);
        printf("REGS: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("POSSIBLE RES = %02x\n", word);
    }
    
    if(cpu->regs[reg_ds(regs)] <= cpu->regs[reg_sc(regs)]){
        cpu->pc = word;
        if(cpu->flags & DEBUG)
            printf("WENT THROUGH.\n");
    }
}

/*
    S-TYPE
*/

static void func_ls_psh()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG){
        printf("PSH: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("stk_ptr @ %01x: %02X\n", cpu->stack_ptr, stack[cpu->stack_ptr]);                                  
    }

    stack[cpu->stack_ptr++] = cpu->regs[reg_ds(regs)];

    if(reg_sc(regs))
        stack[cpu->stack_ptr++] = cpu->regs[reg_sc(regs)];
    
    if(cpu->flags & DEBUG)
        printf("stk_ptr now @ %01x: %02X\n", cpu->stack_ptr, stack[cpu->stack_ptr]);
}

static void func_ls_pop()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG){
        printf("POP: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("stk_ptr @ %01x: %02X\n", cpu->stack_ptr, stack[cpu->stack_ptr]);                                  
    }
    
    cpu->regs[reg_sc(regs)] = stack[--cpu->stack_ptr];

    if(reg_ds(regs))
        cpu->regs[reg_ds(regs)] = stack[--cpu->stack_ptr];

    if(cpu->flags & DEBUG){
        printf("stk_ptr now @ %01x: %02X\n", cpu->stack_ptr, stack[cpu->stack_ptr]);
        printf("RES: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    }
}

static void func_ls_jsr()
{
    uint16_t word = ls_fetchw();

    if(cpu->flags & DEBUG){
        printf("JMP: PC = %02X\n", cpu->pc);
        printf("RES = %02x\n", word);
    }

    stack[cpu->stack_ptr++] = cpu->pc;
    cpu->pc = word;
    if(cpu->flags & DEBUG)
        printf("stk_ptr now @ %01x: %02X\n", cpu->stack_ptr, stack[cpu->stack_ptr]);
}

static void func_ls_rts()
{
    if(cpu->flags & DEBUG){
        printf("JMP: PC = %02X\n", cpu->pc);
        printf("RES = %02x\n", stack[cpu->stack_ptr - 1]);
    }

    cpu->pc = stack[--cpu->stack_ptr];
    if(cpu->flags & DEBUG)
        printf("stk_ptr now @ %01x: %02X\n", cpu->stack_ptr, stack[cpu->stack_ptr]);
}

/*
    X-TYPE
*/

static void func_ls_rnd()
{
    uint8_t regs = ls_fetchb();
    uint32_t rnd = rand();

    if(cpu->flags & DEBUG){
        printf("RND: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
        printf("RAND: %04x\n", rnd);                                
    }
    
    cpu->regs[reg_ds(regs)] = (rnd >> 16) & 0xFFFF;
    cpu->regs[reg_sc(regs)] = rnd & 0xFFFF;
    if(cpu->flags & DEBUG)
        printf("RES: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
}

static void func_ls_swp()
{
    uint8_t regs = ls_fetchb();

    if(cpu->flags & DEBUG)
        printf("SWP: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
    
    uint16_t temp = cpu->regs[reg_ds(regs)];
    cpu->regs[reg_ds(regs)] = cpu->regs[reg_sc(regs)];
    cpu->regs[reg_sc(regs)] = temp;
    if(cpu->flags & DEBUG)
        printf("RES: r%01x = %02X, r%01x = %02X\n", reg_ds(regs), cpu->regs[reg_ds(regs)], 
                                                     reg_sc(regs), cpu->regs[reg_sc(regs)]);
}

static void func_ls_sys()
{
    uint8_t idx = ls_fetchb();
    if(cpu->flags & DEBUG)
            printf("SYS: Calling system function %01x.\n", idx);
}

static void func_ls_hlt()
{
    cpu->flags ^= 0b10000000;
    if(cpu->flags & DEBUG)
            printf("HLT: Halting!\n");
}

inst_func table[] = {
    func_ls_add, func_ls_addc, func_ls_sub, func_ls_subc, 
    func_ls_and, func_ls_andc, func_ls_or, func_ls_orc, func_ls_xor, func_ls_xorc,
    func_ls_lsr, func_ls_lsrc, func_ls_rsh, func_ls_rshc,
    func_ls_jmp, func_ls_jpr, func_ls_jpe, func_ls_jpd, func_ls_jpg, func_ls_jpl,
    func_ls_psh, func_ls_pop, func_ls_jsr, func_ls_rts,
    func_ls_rnd, func_ls_swp, func_ls_sys, func_ls_hlt
};