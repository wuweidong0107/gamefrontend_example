#include "GuiGameList.h"
#include "Renderer.h"

GuiGameList::GuiGameList(SystemData* system)
{
    mSystem = system;
    mList = new GuiList();
    updateList();
    
    addChild(mList);

    Renderer::registerComponent(this);
    InputManager::registerComponent(this);
}

GuiGameList::~GuiGameList()
{
    Renderer::unregisterComponent(this);
    InputManager::unregisterComponent(this);
}

void GuiGameList::updateList()
{
    mList->clear();

    for (unsigned int i=0; i<mSystem->getGameCount(); i++) {
        GameData* game = mSystem->getGame(i);
        mList->addObject(game->getName(), game);
    }
}

void GuiGameList::onRender()
{
	Renderer::drawRect(0, 0, Renderer::getScreenWidth(), Renderer::getScreenHeight(), 0xFFFFFF);

	Renderer::drawCenteredText(mSystem->getName(), 2, 0x0000FF);
}

void GuiGameList::onInput(InputManager::InputButton button, bool keyDown)
{
    if (button == InputManager::BUTTON1 && keyDown) {
        mSystem->launchGame(mList->getSelection());
    }
}
