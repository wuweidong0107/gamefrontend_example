#ifndef _RENDERER_H_
#define _RENDERER_H_

#define LAYER_COUNT 3

#define BIT(x) (1 << (x))

#include <vector>
#include <SDL/SDL.h>

class GuiComponent;

namespace Renderer
{
    void registerComponent(GuiComponent* comp);
    void unregisterComponent(GuiComponent* comp);
    void render();
    extern SDL_Surface* screen;

    void drawRect(Sint16 x, Sint16 y, Uint16 h, Uint16 w, int color);
}

#endif