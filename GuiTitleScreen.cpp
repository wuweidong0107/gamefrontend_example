#include "GuiTitleScreen.h"
#include "Renderer.h"

GuiTitleScreen::GuiTitleScreen()
{
    Renderer::registerComponent(this);
}

void GuiTitleScreen::onRender()
{
	Renderer::drawRect(0, 0, Renderer::getScreenWidth(), Renderer::getScreenHeight(), 0xFFFFFF);
	Renderer::drawCenteredText("EmulationStation", 5, 0x00FF00);
}
