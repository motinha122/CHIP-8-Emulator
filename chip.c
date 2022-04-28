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

    fseek(rom,0,SEEK_END);
    size_t size = ftell(rom);
    chip->rom_size = size;
    fseek(rom,0,SEEK_SET);
    fread(chip->memory,size,1,rom);
    fclose(rom);
}

void CHIP8_Debugger(CHIP8* chip)
{
    for(int i =0 ; i < chip->rom_size ; i++)
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
    }

    printf("\nRom size:%d bytes",chip->rom_size);
    printf("\nCHIP-8 size:%d bytes",sizeof(CHIP8));
}
