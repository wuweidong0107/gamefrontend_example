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

    void addChild(GuiComponent* comp);
    void removeChild(GuiComponent* comp);
    unsigned int getChildCount() { return mChildren.size(); };
    GuiComponent* getChild(unsigned int i) { return mChildren.at(i); };

private:
    std::vector<GuiComponent*> mChildren;
};

#endif