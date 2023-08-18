#include "InputManager.h"
#include <iostream>

void InputManager::processEvent(SDL_Event* event)
{
    bool keyDown = false;
    if (event->key.state == SDL_PRESSED)
        keyDown = true;
    
    std::cout << "Processing keyboard event\n";

    InputButton button;
    switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            button = LEFT;
            break;
        case SDLK_RIGHT:
            button = RIGHT;
            break;
        case SDLK_DOWN:
            button = DOWN;
        case SDLK_SPACE:
            button = BUTTON1;
            break;
        default:
            break;
    }
    if (event->key.keysym.sym == SDLK_F4) {
        SDL_Event* quit = new SDL_Event();
        quit->type = SDL_QUIT;
        SDL_PushEvent(quit);
        std::cout << "Pushing quit event\n";
    }
}