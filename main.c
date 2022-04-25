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