#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "chip.h"

int main(int argc, char* argv[])
{
    CHIP8 *chip_chip = CHIP8_Create();
    CHIP8_Load_Rom(chip_chip,"./logo.ch8");
    CHIP8_Load_Font(chip_chip);
    CHIP8_Run_Cycle(chip_chip);
    SDL_Window * window;
    SDL_Renderer * renderer;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Game Window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,0);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 112 , 112, 255 , 255);
    SDL_Delay(2000);
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    //CHIP8_Debugger(chip_chip);
    return 0;
}

