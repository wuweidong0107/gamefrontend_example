#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Renderer.h"
#include "GuiTitleScreen.h"
#include "InputManager.h"
#include "SystemData.h"
#include "GuiGameList.h"


int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error - could not initialize SDL!\n";
        std::cerr << "	" << SDL_GetError() << "\n";
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "Error - could not initialize SDL_ttf\n";
        std::cerr << "	" << TTF_GetError() << "\n";
    }

    Renderer::screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    if (Renderer::screen == NULL) {
        std::cerr << "Error - could not set video mode!\n";
        return 1;
    }

    SDL_ShowCursor(false);
    SDL_EnableKeyRepeat(500, 100);
    
    SystemData* testSystem = SystemData::loadConfig("./systems.cfg").at(0);
    GuiGameList* testGui = new GuiGameList(testSystem);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    InputManager::processEvent(&event);
                    break;
                case SDL_KEYUP:
                    InputManager::processEvent(&event);
                    break;
                case SDL_QUIT:
                    std::cerr<<"quiting..."<<std::endl;
                    running = false;
                    break;
            }
        }
        Renderer::render();
        SDL_Flip(Renderer::screen);
    }

    delete testGui;
    delete testSystem;
    TTF_Quit();
    SDL_Quit();
    return 0;
}