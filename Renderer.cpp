#include "Renderer.h"
#include "GuiComponent.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>

std::vector<GuiComponent*> renderVector;
SDL_Surface* Renderer::screen;
TTF_Font* Renderer::font;

void Renderer::registerComponent(GuiComponent* comp)
{
    renderVector.push_back(comp);
}

void Renderer::unregisterComponent(GuiComponent* comp)
{
    for(unsigned int i=0; i<renderVector.size(); i++) {
        if(renderVector.at(i) == comp) {
            renderVector.erase(renderVector.begin() + i);
            break;
        }
    }
}

void Renderer::render()
{
    for (unsigned int layer=0; layer < LAYER_COUNT; layer++) {
        unsigned int layerBit = BIT(layer);
        for (unsigned int i=0; i < renderVector.size(); i++) {
            if (renderVector.at(i)->getLayer() & layerBit) {
                renderVector.at(i)->render();
            }
        }
    }
}

unsigned int Renderer::getScreenWidth()
{
    return 640;
}

unsigned int Renderer::getScreenHeight()
{
    return 480;
}

void Renderer::drawRect(Sint16 x, Sint16 y, Uint16 h, Uint16 w, int color)
{
    SDL_Rect rect = {x, y, h, w};
    SDL_FillRect(Renderer::screen, &rect, color);
}

void Renderer::drawText(std::string text, Sint16 x, Sint16 y, SDL_Color& color)
{
    if(!font) {
        loadFonts();
    }

    SDL_Surface* textSurf = TTF_RenderText_Blended(font, text.c_str(), color);
    if (textSurf == NULL) {
        std::cerr << "Error - could not render text \"" << text << "\" to surface!\n";
        std::cerr << TTF_GetError() << "\n";
        return;
    }
    SDL_Rect dest = {x, y};
    SDL_BlitSurface(textSurf, NULL, screen, &dest);
    SDL_FreeSurface(textSurf);
}

void Renderer::drawCenteredText(std::string text, Sint16 y, SDL_Color& color)
{
    if(!font) {
        loadFonts();
    }
    int w,h;
    TTF_SizeText(font, text.c_str(), &w, &h);
    int x = (int)getScreenWidth() - w;
    x *= 0.5;
    drawText(text, x, y, color);
}

void Renderer::loadFonts()
{
    font = TTF_OpenFont("LinLibertine_R.ttf", 48);
    if (!font) {
        std::cerr << "Error - could not load font!\n";
        std::cerr << TTF_GetError() << "\n";
        return;
    }
}