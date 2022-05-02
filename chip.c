#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "chip.h"

CHIP8 *CHIP8_Create()
{   
    CHIP8 *chip = malloc(sizeof(CHIP8));

    chip->pc = 0;
    chip->sp = -1;
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
    printf("\nRom size:%d bytes\n\n" , chip->rom_size);
}

void CHIP8_Fetch(CHIP8 * chip)
{
    chip->opcode = chip->memory[chip->pc] << 8 | chip->memory[chip->pc + 1];
    printf("\nCHIP-8 opcode 0x%X\n",chip->opcode);
    printf("CHIP-8 pc $%X\n",chip->pc);
}

void CHIP8_Decode(CHIP8 * chip)
{
    uint16_t nnn = chip->opcode & 0x0FFF;
    uint16_t n = chip->opcode & 0x000F;
    uint16_t x = chip->opcode & 0x0F00;
    uint16_t y = chip->opcode & 0x00F0;
    uint16_t kk = chip->opcode & 0x00FF;

    printf("NNN:%X,N:%X,X:%X,Y:%X,KK:%X\n",nnn,n,x,y,kk);

    switch (chip->opcode & 0xF000)
    {
    case(0x0000):
        switch (chip->opcode & 0x00FF)
        {
        case(0x00E0): printf("CLS\n");
        chip->pc +=2;
        break;

        case(0x00EE): printf("RET\n");
        chip->pc = chip->stack[chip->sp];
        chip->stack[chip->sp] = 0;
        chip->sp -= 1;
        chip->pc +=2;
        break;

        default : printf("Error\n");
        chip->pc +=2;
        break;
        }
    break;

    case(0x1000): printf("JMP : %X\n", nnn);
    chip->pc = nnn;
    break;

    case(0x2000): printf("CALL : %X\n", nnn);
    chip->sp += 1;
    chip->stack[chip->sp] = chip->pc;
    chip->pc = nnn;
    break;
    
    case(0x3000): printf("SE V[%X], %X\n",x,kk);
    if (chip->registers_v[x] == kk)
    {
        chip->pc +=2;
    }
    chip->pc +=2;
    break;

    case(0x4000): printf("SNE V[%X], %X\n",x,kk);
    if (chip->registers_v[x] != kk)
    {
        chip->pc +=2;
    }
    chip->pc +=2;
    break;

    case(0x5000): printf("SE V[%X], V[%X]\n",x,y);
    if (chip->registers_v[x] == chip->registers_v[y])
    {
        chip->pc +=2;
    }
    chip->pc +=2;
    break;

    case(0x6000): printf("LD V[%X], %X\n",x,kk);
    chip->registers_v[x] = kk;
    chip->pc +=2;
    break;

    case(0x7000): printf("ADD V[%X], %X\n",x,kk);
    chip->registers_v[x] += kk;
    chip->pc +=2; 
    break;

    case(0x8000):
        switch (chip->opcode & 0x000F)
        {
        case(0x0000): 
            chip->pc +=2;break;
        
        case(0x0001): 
            chip->pc +=2;break;

        case(0x0002): 
            chip->pc +=2;break;

        case(0x0003): 
            chip->pc +=2;break;
        
        case(0x0004): 
            chip->pc +=2;break;

        case(0x0005): 
            chip->pc +=2;break;

        case(0x0006): 
            chip->pc +=2;break;
        
        case(0x0007): 
            chip->pc +=2;break;
        
        case(0x000E): 
            chip->pc +=2;break;
        
        default : printf("Error\n");
            chip->pc +=2;break;
        }
    break;

    case(0x9000): 
        chip->pc +=2;break;

    case(0xA000): 
        chip->pc +=2;break;
    
    case(0xB000): 
        chip->pc +=2;break;

    case(0xC000): 
        chip->pc +=2;break;

    case(0xD000): 
        chip->pc +=2;break;

    case(0xE000):
        switch (chip->opcode & 0x00FF)
        {
        case(0x009E): 
            chip->pc +=2;break;
        
        case(0x00A1):
            chip->pc +=2;break; 

        default : printf("Error\n");
            chip->pc +=2;break;
        }
        break;

    case(0xF000):
        switch (chip->opcode & 0x00FF)
        {
        case(0x0007): 
            chip->pc +=2;break;

        case(0x000A): 
            chip->pc +=2;break;

        case(0x0015): 
            chip->pc +=2;break;

        case(0x0018): 
            chip->pc +=2;break;

        case(0x001E): 
            chip->pc +=2;break;
        
        case(0x0029): 
            chip->pc +=2;break;
        
        case(0x0033): 
            chip->pc +=2;break;

        case(0x0055): 
            chip->pc +=2;break;

        case(0x0065): 
            chip->pc +=2;break;

        
        default : printf("Error\n");
            chip->pc +=2;break;
        }
        break;
    default : printf("Error\n");
    chip->pc +=2;break;
    }
}

void CHIP8_Run_Cycle(CHIP8* chip)
{
    for(int i =0 ; i < chip->rom_size ; i++)
    {
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
