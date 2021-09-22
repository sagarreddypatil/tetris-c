#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

const int PIXELS_PER_GRID = 0.9 * SCREEN_HEIGHT / GRID_HEIGHT;

const int GRID_START_X = SCREEN_WIDTH - SCREEN_WIDTH / 2 - PIXELS_PER_GRID * GRID_WIDTH / 2;
const int GRID_START_Y = SCREEN_HEIGHT - SCREEN_HEIGHT / 2 - PIXELS_PER_GRID * GRID_HEIGHT / 2;

const int GRID_END_X = GRID_START_X + PIXELS_PER_GRID * GRID_WIDTH;
const int GRID_END_Y = GRID_START_Y + PIXELS_PER_GRID * GRID_HEIGHT;

typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Color;

// cyan, blue, orange, yellow, green, purple, red, undefined
const Color COLORS[8] = {{0x00, 0xff, 0xff}, {0x00, 0x00, 0xff}, {0xff, 0x7f, 0x00}, {0xff, 0xff, 0x00},
                         {0x00, 0xff, 0x00}, {0xa2, 0x28, 0xff}, {0xff, 0x00, 0x00}, {0x00, 0x00, 0x00}};

const SDL_Point GRID_POINTS[5] = {{GRID_START_X, GRID_START_Y},
                                  {GRID_START_X, GRID_END_Y},
                                  {GRID_END_X, GRID_END_Y},
                                  {GRID_END_X, GRID_START_Y},
                                  {GRID_START_X, GRID_START_Y}};

void drawBox(SDL_Renderer *renderer, int posX, int posY, char color)
{
    SDL_Rect rect = {.x = posX * PIXELS_PER_GRID + GRID_START_X,
                     .y = posY * PIXELS_PER_GRID + GRID_START_Y,
                     .w = PIXELS_PER_GRID,
                     .h = PIXELS_PER_GRID};

    Color boxColor;
    switch (color)
    {
    case 'c':
        boxColor = COLORS[0];
        break;
    case 'b':
        boxColor = COLORS[1];
        break;
    case 'o':
        boxColor = COLORS[2];
        break;
    case 'y':
        boxColor = COLORS[3];
        break;
    case 'g':
        boxColor = COLORS[4];
        break;
    case 'p':
        boxColor = COLORS[5];
        break;
    case 'r':
        boxColor = COLORS[6];
        break;
    default:
        boxColor = COLORS[7];
        break;
    }
    SDL_SetRenderDrawColor(renderer, boxColor.r, boxColor.g, boxColor.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void drawGame(SDL_Renderer *renderer, char gameGrid[GRID_HEIGHT][GRID_WIDTH])
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            drawBox(renderer, x, y, gameGrid[y][x]);
        }
    }
}

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
    SDL_SetWindowTitle(window, "Tetris");

    // pieces on the game grid are color coded: one letter for each color: roygcbv
    char gameGrid[GRID_HEIGHT][GRID_WIDTH];
    memset(gameGrid, 0, GRID_HEIGHT * GRID_WIDTH * sizeof(char));

    for (int col = 0; col < GRID_WIDTH; col++)
    {
        gameGrid[GRID_HEIGHT - 1][col] = 'g';
    }

    for (int col = 0; col < GRID_WIDTH; col++)
    {
        gameGrid[GRID_HEIGHT - 2][col] = 'b';
    }

    for (int col = 0; col < GRID_WIDTH; col++)
    {
        gameGrid[0][col] = 'o';
    }

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
        SDL_RenderClear(renderer);

        drawGame(renderer, gameGrid);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLines(renderer, GRID_POINTS, 5);

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