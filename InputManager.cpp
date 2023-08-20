#include "InputManager.h"
#include "GuiComponent.h"
#include <iostream>

std::vector<GuiComponent*> InputManager::inputVector;

void InputManager::registerComponent(GuiComponent* comp)
{
    inputVector.push_back(comp);
}

void InputManager::unregisterComponent(GuiComponent* comp)
{
    for (unsigned int i=0; i<inputVector.size(); i++) {
        if (inputVector.at(i) == comp) {
            inputVector.erase(inputVector.begin() + i);
        }
    }
}


void InputManager::processEvent(SDL_Event* event)
{
    bool keyDown = false;
    if (event->key.state == SDL_PRESSED)
        keyDown = true;

    InputButton button;
    switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            button = LEFT;
            break;
        case SDLK_RIGHT:
            button = RIGHT;
            break;
        case SDLK_UP:
            button = UP;
            break;
        case SDLK_DOWN:
            button = DOWN;
            break;
        case SDLK_RETURN:
            button = BUTTON1;
            break;
        default:
            return;
    }
    
    std::cout << "Processing keyboard event: " << button << "\n";
    if (event->key.keysym.sym == SDLK_F4) {
        SDL_Event* quit = new SDL_Event();
        quit->type = SDL_QUIT;
        SDL_PushEvent(quit);
        std::cout << "Pushing quit event\n";
    }

    for (unsigned int i = 0; i< inputVector.size(); i++) {
        inputVector.at(i)->onInput(button, keyDown);
    }
}