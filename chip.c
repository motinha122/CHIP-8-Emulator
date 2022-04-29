#include <stdlib.h>
#include <stdio.h>
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
    chip->ir = chip->opcode;

    switch (chip->ir & 0xF000)
    {
    case(0x0000):
        switch (chip->ir & 0x00FF)
        {
        case(0x00E0): printf("00E0 : Clear Screen\n");break;

        case(0x00EE): printf("00EE : Return from subroutine\n");break;

        default: printf("Error\n");break;
        }

    case(0x1000): printf("1nnn : Jump to location\n");break;

    case(0x2000): printf("2nnn : Call subroutine\n");break;
    
    case(0x3000): printf("3xkk : Skip next if Vx = kk\n");break;

    default: printf("Error\n");break;
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
