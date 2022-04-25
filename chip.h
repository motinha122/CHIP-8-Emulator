#ifndef CHIP_H
#define CHIP_H
#include <stdint.h>
#include <string.h>
#define MEMSIZE 4096


typedef struct
{
    uint16_t pc;
    uint8_t memory[MEMSIZE];
    uint16_t rom_size;
}CHIP8;

CHIP8 *CHIP8_Create();

void CHIP8_Load_Rom(CHIP8 * chip, const char *rom_path);

void CHIP8_Debugger(CHIP8 * chip);

#endif
