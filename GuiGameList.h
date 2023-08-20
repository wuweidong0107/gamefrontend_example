#ifndef _GUIGAMELIST_H_
#define _GUIGAMELIST_H_

#include "GuiComponent.h"
#include "GUIList.h"
#include "SystemData.h"
#include "GameData.h"
#include <string>

class GuiGameList : GuiComponent
{
public:
    GuiGameList(SystemData* system);
    ~GuiGameList();

    void updateList();
    void onRender();
    void onInput(InputManager::InputButton button, bool keyDown);

private:
    SystemData* mSystem;
    GuiList* mList;
};

#endif