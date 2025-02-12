#include "game.h"

void Game_update(Map *map)
{
    if (!map->isRunning)
        return;

    map->frames++;

    // Update cells
    for (int i = 0; i < map->cellCount; ++i)
        if (map->cells[i] != NULL)
            Cell_update(map->cells[i], map);

    // Check generation
    bool allDead = true;
    for (int i = 0; i < map->cellCount; ++i)
    {
        if (map->cells[i] != NULL && map->cells[i]->isAlive)
        {
            allDead = false;
            break;
        }
    }

    // Next generation
    if (allDead)
        Game_reset(map, false);

    // Update best cell
    int bestCellIndex = 0;
    for (int i = 0; i < map->cellCount; ++i)
    {
        if (map->cells[i] == NULL || map->cells[bestCellIndex] == NULL)
            continue;
        if (map->cells[i]->score > map->cells[bestCellIndex]->score)
            bestCellIndex = i;
    }
    map->currentBestCellIndex = bestCellIndex;

    if (map->cells[bestCellIndex]->score > map->bestCellEver->score)
    {
        NeuralNetwork *bestNN = NeuralNetwork_Copy(map->cells[bestCellIndex]->nn);
        if (bestNN != NULL)
        {
            freeNeuralNetwork(map->bestCellEver->nn);
            map->bestCellEver->nn = bestNN;
        }

        map->bestCellEver->score = map->cells[bestCellIndex]->score;
        map->bestCellEver->generation = map->generation;
    }

    // Update oldest cell
    Cell *oldestCell = map->cells[0];
    for (int i = 0; i < map->cellCount; ++i)
        if (map->cells[i] != NULL && map->cells[i]->generation > oldestCell->generation)
            oldestCell = map->cells[i];
    if (oldestCell->generation > map->maxGeneration)
        map->maxGeneration = oldestCell->generation;
}
