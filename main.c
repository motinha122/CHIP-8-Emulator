#include <stdio.h>
#include <stdlib.h>
#include "chip.h"

int main()
{
    CHIP8 *chip_chip = CHIP8_Create();
    CHIP8_Load_Rom(chip_chip,"./logo.ch8");
    CHIP8_Debugger(chip_chip);
    
    return 0;
}

//Bit placement 
    //0000 0001 = 0x1
    //0000 0010 = 0x2
    //0000 0100 = 0x4
    //0000 1000 = 0x8
    //0001 0000 = 0x10
    //0010 0000 = 0x20
    //0100 0000 = 0x40
    //1000 0000 = 0x80
    