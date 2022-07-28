#ifndef CHIP_H
#define CHIP_H
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    uint8_t memory[4096]; //Ram 4096bytes            
    uint16_t rom_size;  //Rom Size                                  
    uint16_t pc; //16-bit Program Counter                    
    uint16_t sp; // 16-bit Stack Pointer
    uint16_t opcode; // 16-bit Opcode
    uint8_t reg_v[16];  //8-bit V Registers
    uint16_t i; // 16-bit I Register                                            
    uint16_t stack[16]; // 16-bit Stack 
    uint8_t graphic_buffer[64 * 32]; // Graphical Buffer 2048 pixels 
    bool drawFlag; // DRAW FLAG                  
}CHIP8;

CHIP8 *CHIP8_Create();

void CHIP8_Load_Rom(CHIP8 * chip, const char *rom_path);

void CHIP8_Load_Font(CHIP8 * chip);
 
void CHIP8_Fetch(CHIP8 * chip);

void CHIP8_Decode(CHIP8 * chip);

void CHIP8_Run_Cycle(CHIP8 * chip);

void CHIP8_Debugger(CHIP8 * chip);

#endif