#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "insts.h"

int main(void)
{
    printf("Longstocking VM ver. 0.06\nby Uneven Prankster @ 2020\n");

    program = malloc(5);
    program[0] = LS_ADDC;
    program[1] = REGC(2, 0);
    program[2] = 0xff;
    program[3] = 0x0;
    program[4] = LS_HLT;

    ls_cpu_init();
    cpu->flags |= DEBUG;

    while(!(cpu->flags & RUN))
        ls_cpu_cycle();
    ls_cpu_destroy();
    ls_prog_destroy();
    return 0;
}