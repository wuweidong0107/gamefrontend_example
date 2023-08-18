#ifndef _GUICOMPONENT_H_
#define _GUICOMPONENT_H_

#include <vector>
#include "Renderer.h"

class GuiComponent
{
public:
    void render();
    virtual void onRender() {};
    virtual unsigned int getLayer() { return BIT(0); };    
};

#endif