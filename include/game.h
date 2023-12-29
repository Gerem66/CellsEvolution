#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL2_framerate.h>
#include <SDL2_gfxPrimitives.h>

typedef struct Map Map;

#include "cell.h"
#include "food.h"

#define CELL_INIT 20
#define CELL_COUNT 1000
#define FOOD_COUNT 10


struct Map
{
    int width;
    int height;
    time_t startTime;
    Cell *cells[CELL_COUNT];
    Food *foods[FOOD_COUNT];
    int cellCount;
    int generation;
    int frames;
    int maxScore;
    bool isRunning;
    bool verticalSync;
    bool renderText;
    bool renderRays;
    bool renderEnabled;
};


bool Game_start(SDL_Renderer *renderer, int w, int h);
void Game_reset(Map *map);
void Game_render(SDL_Renderer *renderer, Map *map);
void Render_Text(SDL_Renderer *renderer, Map *map, SDL_Color color);

#endif // GAME_H
