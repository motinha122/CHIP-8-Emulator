#ifndef CHIP_H
#define CHIP_H
#include <stdint.h>
#include <string.h>
#define MEMSIZE 4096
#define NUMREG 16

typedef struct
{
    uint8_t memory[MEMSIZE]; //Ram 4096bytes
    uint16_t rom_size;  //Rom Size
    uint16_t pc; //16-bit Program Counter
    uint8_t sp; // 8-bit Stack Pointer
    uint16_t opcode; // 16-bit Opcode
    uint8_t registers_v[NUMREG];  //8-bit V Registers
    uint16_t register_i; // 16-bit I Register
    uint16_t stack[NUMREG]; // 16-bit Stack
}CHIP8;

CHIP8 *CHIP8_Create();

void CHIP8_Load_Rom(CHIP8 * chip, const char *rom_path);

void CHIP8_Fetch(CHIP8 * chip);

void CHIP8_Run_Cycle(CHIP8 * chip);

//void CHIP8_Debugger(CHIP8 * chip);

#endif
