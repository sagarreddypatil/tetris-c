#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

const int PIXELS_PER_GRID = SCREEN_HEIGHT / 72;

const int GRID_START_X = SCREEN_WIDTH - SCREEN_WIDTH / 2 - PIXELS_PER_GRID * GRID_WIDTH / 2;
const int GRID_START_Y = SCREEN_HEIGHT - SCREEN_HEIGHT / 2 - PIXELS_PER_GRID * GRID_HEIGHT / 2;

const int GRID_END_X = GRID_START_X + PIXELS_PER_GRID * GRID_WIDTH;
const int GRID_END_Y = GRID_START_X + PIXELS_PER_GRID * GRID_HEIGHT;

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL initialization error: %s\n", SDL_GetError());
        exit(1);
    }

    if (!SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) == 0)
    {
        printf("SDL Window and Renderer creation error: %s\n", SDL_GetError());
        exit(1);
    }

    // pieces on the game grid are color coded: one letter for each color: roygcbv
    char gameGrid[GRID_HEIGHT][GRID_WIDTH];
    memset(gameGrid, 0, GRID_HEIGHT * GRID_WIDTH * sizeof(char));

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
        SDL_RenderDrawLine(renderer, GRID_START_X, GRID_START_Y, GRID_END_X, GRID_START_Y);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}