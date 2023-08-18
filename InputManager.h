#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <vector>
#include <SDL/SDL.h>

namespace InputManager {
    enum InputButton { UP, DOWN, LEFT, RIGHT, BUTTON1, BUTTON2};
    void processEvent(SDL_Event* event);
}

#endif