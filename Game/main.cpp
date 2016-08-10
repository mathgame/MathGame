#include <iostream>
#include "UniStream/UniStream.h"
#include "libs.h"
#include <SDL2/SDL.h>

using namespace std;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Math Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool runWindow = true;

    while ( runWindow )
    {
        SDL_Event event;
        while( SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                runWindow = false;
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        // Up until now everything was drawn behind the scenes.
        // This will show the new, red contents of the window.
        SDL_RenderPresent(renderer);

        SDL_UpdateWindowSurface( window );
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}
