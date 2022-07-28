#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include "chip.h"

CHIP8 *CHIP8_Create()
{
    CHIP8 *chip = malloc(sizeof(CHIP8));

    chip->pc = 0x200;
    chip->sp = -1;
    memset(chip->memory, 0, sizeof(chip->memory));
    memset(chip->reg_v, 0, sizeof(chip->reg_v));
    memset(chip->stack, 0, sizeof(chip->stack));
    chip->drawFlag = false;
    printf("\nChip Initialized\n");

    return chip;
}

void CHIP8_Load_Rom(CHIP8 *chip, const char *rom_path)
{
    FILE *rom = fopen(rom_path, "rb");

    if (rom == NULL)
    {
        printf("Error!");
        printf("Press Any Key to Continue\n");  
        getchar();   
        exit(1);
    }

    fseek(rom, 0, SEEK_END);
    size_t size = ftell(rom);
    chip->rom_size = size;
    fseek(rom, 0, SEEK_SET);
    fread(chip->memory + 0x200, size, 1, rom);
    fclose(rom);
    printf("Rom loaded on Ram");
    printf("\nRom size:%d bytes\n", chip->rom_size);
}

void CHIP8_Load_Font(CHIP8 *chip)
{
    uint8_t font[80] =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0  
            0x20, 0x60, 0x20, 0x20, 0x70, // 1  
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2  
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3  
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4  
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5  
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6  
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7  
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8  
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9  
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A  
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B  
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C  
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D  
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E  
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F 
        };
    
    for (size_t i = 0; i < 80; i++)
    {
        chip->memory[i] = font[i];
    }
    printf("Font loaded on Ram\n");
}

void CHIP8_Fetch(CHIP8 *chip)
{
    chip->opcode = chip->memory[chip->pc] << 8 | chip->memory[chip->pc + 1];
    printf("\nCHIP-8 opcode 0x%X\n", chip->opcode);
    printf("CHIP-8 pc $%X\n", chip->pc);
}

void CHIP8_Decode(CHIP8 *chip)
{
    uint16_t nnn = chip->opcode & 0x0FFF;
    uint16_t n = chip->opcode & 0x000F; 
    uint16_t x = (chip->opcode & 0x0F00) >> 8; 
    uint16_t y = (chip->opcode & 0x00F0) >> 4; 
    uint16_t kk = chip->opcode & 0x00FF;
    uint16_t pixel;

    chip->pc += 2;

    printf("NNN:%X,N:%X,X:%X,Y:%X,KK:%X\n", nnn, n, x, y, kk);

    switch (chip->opcode & 0xF000)
    {
    case (0x0000):

        switch (chip->opcode & 0x00FF)
        {
        case (0x00E0):
            printf("CLS\n");
            break;

        case (0x00EE):
            printf("RET\n");
            break;

        default:
            printf("Error\n");
            break;
        }
        break;

    case (0x1000):
        printf("JMP : %X\n", nnn);
        break;

    case (0x2000):
        printf("CALL : %X\n", nnn);
        break;

    case (0x3000):
        printf("SE V[%X], %X\n", chip->reg_v[x], kk);
        break;

    case (0x4000):
        printf("SNE V[%X], %X\n", chip->reg_v[x], kk);
        break;

    case (0x5000):
        printf("SE V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
        break;

    case (0x6000):
        printf("LD V[%X], %X\n", chip->reg_v[x], kk);
        break;

    case (0x7000):
        printf("ADD V[%X], %X\n", chip->reg_v[x], kk);
        break;

    case (0x8000):
        switch (chip->opcode & 0x000F)
        {
        case (0x0000):
            printf("LD V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        case (0x0001):
            printf("OR V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        case (0x0002):
            printf("AND V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        case (0x0003):
            printf("XOR V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        case (0x0004):
            printf("ADD V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        case (0x0005):
            printf("SUB V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        case (0x0006):
            printf("SHR V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        case (0x0007):
            printf("SUBN V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        case (0x000E):
            printf("SHL V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
            break;

        default:
            printf("Error\n");
            break;
        }
        break;

    case (0x9000):
        printf("SNE V[%X], V[%X]\n", chip->reg_v[x], chip->reg_v[y]);
        break;

    case (0xA000):
        printf("LD I = %X\n", nnn);
        break;

    case (0xB000):
        printf("JP V[0], %X\n", nnn + chip->reg_v[0]);
        break;

    case (0xC000):
        printf("RND V[%X], %X\n", chip->reg_v[x], kk);
        break;

    case (0xD000):
        printf("DRW V[%X], V[%X], %X\n", chip->reg_v[x], chip->reg_v[y], n);
        chip->reg_v[0xF] = 0;
        for (int yline = 0; yline < n; yline++)
        {
            pixel = chip->memory[chip->i + yline];
            for(int xline = 0; xline < 8; xline++)
            {
                if((pixel & (0x80 >> xline)) != 0)
                {
                    if(chip->graphic_buffer[chip->reg_v[x] + xline + ((chip->reg_v[y] + yline) * 64)] == 1)
                    {
                        chip->reg_v[0xF] = 1;
                        chip->graphic_buffer[chip->reg_v[x] + xline + ((chip->reg_v[y] + yline) * 64)] ^= 1;
                    }    
                }
            }
        }
        chip->drawFlag = true;

        break;

    case (0xE000):
        switch (chip->opcode & 0x00FF)
        {
        case (0x009E):
            printf("SKP V[%X]\n", chip->reg_v[x]);
            break;

        case (0x00A1):
            printf("SKNP V[%X]\n", chip->reg_v[x]);
            break;

        default:
            printf("Error\n");
            break;
        }
        break;

    case (0xF000):
        switch (chip->opcode & 0x00FF)
        {
        case (0x0007):
            printf("LD V[%X], DT\n", chip->reg_v[x]);
            break;

        case (0x000A):
            printf("LD V[%X], K\n", chip->reg_v[x]);
            break;

        case (0x0015):
            printf("LD DT, V[%X]\n", chip->reg_v[x]);
            break;

        case (0x0018):
            printf("LD ST, V[%X]\n", chip->reg_v[x]);
            break;

        case (0x001E):
            printf("ADD %X, V[%X]\n", chip->i, chip->reg_v[x]);
            break;

        case (0x0029):
            printf("LD F, V[%X]\n", chip->reg_v[x]);
            break;

        case (0x0033):
            printf("LD B, V[%X]\n", chip->reg_v[x]);
            break;

        case (0x0055):
            printf("LD [%X], V[%X]\n", chip->i, chip->reg_v[x]);
            break;

        case (0x0065):
            printf("LD V[%X], [%X]\n", chip->reg_v[x], chip->i);
            break;

        default:
            printf("Error\n");
            break;
        }
        break;
    default:
        printf("Error\n");
        break;
    }
}

void CHIP8_Run_Cycle(CHIP8 *chip) // run cycle disassembly
{
    CHIP8_Fetch(chip);
    CHIP8_Decode(chip);
}

void CHIP8_Debugger(CHIP8 *chip)
{
    for (size_t i = 0; i < 80; i++)
    {
        printf("Font 0x%X\n",chip->memory[i]);
    }
    
    /* for(int i =0 ; i < chip->rom_size ; i++)
    {
        if (i % 2 != 0)
        {
            printf("%02X \n",chip->memory[i]);
        }
        else
        {
            printf("HEX: %02X ",chip->memory[i]);
        }
    }

    for(int i = 0; i < 16 ; i++)
    {
        chip->reg_v[i] = i;
        printf("V%x:0x%X\n",i,chip->reg_v[i]);
    } */
}
