#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "game.h"

// Define screen dimensions
#define SCREEN_WIDTH    1200
#define SCREEN_HEIGHT   800
#define GAME_WIDTH    1200
#define GAME_HEIGHT   800

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not be initialized!\n"
                        "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    // Create window
    SDL_Window *window = SDL_CreateWindow("Cells Evolution - SDL",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        fprintf(stderr, "Window could not be created!\n"
                        "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            fprintf(stderr, "Renderer could not be created!\n"
                            "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

            // Start the game
            Game_start(renderer, GAME_WIDTH, GAME_HEIGHT);

            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }

    // Quit SDL
    SDL_Quit();

    return 0;
}
