#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "chip.h"
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char* argv[])
{
    CHIP8 *chip_chip = CHIP8_Create();
    CHIP8_Load_Rom(chip_chip,"./logo.ch8");
    CHIP8_Load_Font(chip_chip);
  
    if(SDL_Init(SDL_INIT_VIDEO) <0 ){
        printf("Fail");
        return -1;
    }

    SDL_Window * window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480,SDL_WINDOW_SHOWN);

    if(!window){
        printf("Fail");
        return -1;
    }

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        printf("Fail");
        return -1;
    }

    SDL_RenderSetLogicalSize(renderer, 680, 480);

    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);

    while (true) {
        
        CHIP8_Run_Cycle(chip_chip);

        SDL_Event e;
        while(SDL_PollEvent(&e)){
            
            if (e.type == SDL_QUIT) {exit(0);}
            
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {exit(0);}
            }
        }

    }

    // SDL_RenderClear(renderer);

    // SDL_RenderCopy(renderer, texture, NULL, NULL);

    // SDL_RenderPresent(renderer);

    // SDL_Delay(2000);

    //CHIP8_Debugger(chip_chip);
    
    return 0;
}

