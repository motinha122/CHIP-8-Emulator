#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "chip.h"

CHIP8 *CHIP8_Create()
{   
    CHIP8 *chip = malloc(sizeof(CHIP8));

    chip->pc = 0;
    chip->sp = 0;
    memset(chip->memory, 0 ,MEMSIZE);
    memset(chip->registers_v,0,NUMREG);
    memset(chip->stack,0,NUMREG);

    printf("\nChip Initialized\n");
    return chip;
}   

void CHIP8_Load_Rom(CHIP8 * chip, const char *rom_path)
{   
    FILE *rom = fopen(rom_path,"rb");

    if(rom == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

    fseek(rom , 0 , SEEK_END);
    size_t size = ftell(rom);
    chip->rom_size = size;
    fseek(rom , 0 , SEEK_SET);
    fread(chip->memory , size , 1 , rom);
    fclose(rom);
    printf("Rom loaded on Ram");
    printf("\nRom size:%d bytes\n" , chip->rom_size);
}

void CHIP8_Fetch(CHIP8 * chip)
{
    chip->opcode = chip->memory[chip->pc] << 8 | chip->memory[chip->pc + 1];
    printf("CHIP-8 opcode : 0x%X\n",chip->opcode);
}

void CHIP8_Decode(CHIP8 * chip)
{
    uint16_t nnn = 0;
    uint8_t n = 0 , x = 0 , y = 0 , kk = 0;

    switch (chip->opcode & 0xF000)
    {
    case(0x0000):
        switch (chip->opcode & 0x00FF)
        {
        case(0x00E0): printf("Clear display");
        break;

        case(0x00EE): 
        break;

        default : printf("Error");
        break;
        }

    case(0x1000): 
    break;

    case(0x2000): 
    break;
    
    case(0x3000): 
    break;

    case(0x4000): 
    break;

    case(0x5000): 
    break;

    case(0x6000): 
    break;

    case(0x7000): 
    break;

    case(0x8000):
        switch (chip->opcode & 0x000F)
        {
        case(0x0000): 
            break;
        
        case(0x0001): 
            break;

        case(0x0002): 
            break;

        case(0x0003): 
            break;
        
        case(0x0004): 
            break;

        case(0x0005): 
            break;

        case(0x0006): 
            break;
        
        case(0x0007): 
            break;
        
        case(0x000E): 
            break;
        
        default : printf("Error");
            break;
        }
    break;

    case(0x9000): 
        break;

    case(0xA000): 
        break;
    
    case(0xB000): 
        break;

    case(0xC000): 
        break;

    case(0xD000): 
        break;

    case(0xE000):
        switch (chip->opcode & 0x00FF)
        {
        case(0x009E): 
            break;
        
        case(0x00A1): 

        default : printf("Error");
            break;
        }
        break;

    case(0xF000):
        switch (chip->opcode & 0x00FF)
        {
        case(0x0007): 
            break;

        case(0x000A): 
            break;

        case(0x0015): 
            break;

        case(0x0018): 
            break;

        case(0x001E): 
            break;
        
        case(0x0029): 
            break;
        
        case(0x0033): 
            break;

        case(0x0055): 
            break;

        case(0x0065): 
            break;

        
        default : printf("Error");
            break;
        }
        break;
    default : printf("Error");
    break;
    }
}

void CHIP8_Run_Cycle(CHIP8* chip)
{
    for (int i = 0; i < chip->rom_size; i+=2)
    {
        chip->pc = i;
        CHIP8_Fetch(chip);
        CHIP8_Decode(chip);
    }
}

void CHIP8_Debugger(CHIP8* chip)
{
    printf("CHIP-8 opcode : 0x%X",chip->opcode);

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
        chip->registers_v[i] = i;
        printf("V%x:0x%X\n",i,chip->registers_v[i]);
    } */
}
