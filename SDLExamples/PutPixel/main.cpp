#ifdef WIN32
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <random>

void putPixel(SDL_Renderer *renderer, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

auto main() -> int
{
    constexpr int WindowWidth = 400;
    constexpr int WindowHeight = 400;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;
    std::random_device rd;
    std::mt19937 gen(rd());
    // create a distribution to produce our 2d points
    std::uniform_int_distribution<> width_dist(0, WindowWidth - 1);
    std::uniform_int_distribution<> height_dist(0, WindowHeight - 1);
    // create a distribution to produce our colour range
    // note windows does not allow an unsigned char dist see
    // https://stackoverflow.com/questions/31460733/why-arent-stduniform-int-distributionuint8-t-and-stduniform-int-distri
    std::uniform_int_distribution<unsigned short> colour_dist(0, 255);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WindowWidth, WindowHeight, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Put Pixel");
    // clear to background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    bool quit = false;
    while (!quit)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            // this is the window x being clicked.
            case SDL_QUIT:
                quit = true;
                break;
            // now we look for a keydown event
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                // if it's the escape key quit
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
                } // end of key process
            }     // end of keydown
            break;
            default:
                break;
            } // end of event switch
        }     // end of poll events
        // clear to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        // now draw coloured pixels
        for (i = 0; i < 100000; ++i)
        {
            putPixel(renderer, width_dist(gen), height_dist(gen), colour_dist(gen), colour_dist(gen), colour_dist(gen));
        }
        // flip buffers
        SDL_RenderPresent(renderer);
        // wait 100 ms
        SDL_Delay(100);
    }
    // clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}