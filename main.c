#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "chip.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char* argv[])
{
    CHIP8 *chip_chip = CHIP8_Create();
    CHIP8_Load_Rom(chip_chip,"./logo.ch8");
    CHIP8_Load_Font(chip_chip);
    CHIP8_Run_Cycle(chip_chip);
  
    //CHIP8_Debugger(chip_chip);

    }  
    return 0;
}

