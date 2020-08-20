#pragma once

#include "cpu.h"

enum insts{
    LS_ADD,
    LS_ADDC,
    LS_SUB,
    LS_SUBC,
    LS_AND,
    LS_ANDC,
    LS_OR,
    LS_ORC,
    LS_XOR,
    LS_XORC,
    LS_LSR,
    LS_LSRC,
    LS_RSH,
    LS_RSHC,

    LS_JMP,
    LS_JPR,
    LS_JPE,
    LS_JPD,
    LS_JPG,
    LS_JPL,

    LS_PSH,
    LS_POP,
    LS_JSR,
    LS_RTS,

    LS_RND,
    LS_SWP,
    LS_SYS,
    LS_HLT
};

#define REGC(rd, rs) (uint8_t)(((rd) << 4) | (rs))

typedef void (*inst_func)();

extern inst_func table[];