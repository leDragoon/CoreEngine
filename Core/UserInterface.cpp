#include "UserInterface.h"

void GuiElement::setTexture(Texture *toSet)
{
	guiTexture = toSet;
}

void GuiElement::setHoverTexture(Texture *toSet)
{
	guiHoverTexture = toSet;
}

void GuiElement::setColor(XMFLOAT4 toSet)
{
	guiColour = toSet;
}

void GuiElement::setPosition(XMFLOAT2 toSet)
{
	position = toSet;
}

void GuiElement::setScale(XMFLOAT2 toSet)
{
	size = toSet;
}

void GuiElement::setVisible(bool toSet)
{
	visible = toSet;
}

void GuiElement::setName(string toSet)
{
	name = toSet;
}

void GuiElement::setTextureName(string toSet)
{
	textureName = toSet;
}

void GuiElement::setHoverTextureName(string toSet)
{
	hoverTextureName = toSet;
}

void GuiElement::setNeedToBeLoaded(bool toSet)
{
	needsToBeLoaded = toSet;
}

void GuiElement::setOnHoverCallBack(function<void(void)> toSet)
{
	onHover = toSet;
}

void GuiElement::setOnClickCallBack(function<void(void)> toSet)
{
	onClick = toSet;
}

bool GuiElement::getIsVisible()
{
	return visible;
}

bool GuiElement::getNeedsToBeLoaded()
{
	return needsToBeLoaded;
}

string GuiElement::getName()
{
	return name;
}

string GuiElement::getTextureName()
{
	return textureName;
}

string GuiElement::getHoverTextureName()
{
	return hoverTextureName;
}

Texture *GuiElement::getTexture()
{
	return guiTexture;
}

Texture *GuiElement::getHoverTexture()
{
	return guiHoverTexture;
}

XMFLOAT2 GuiElement::getPosition()
{
	return position;
}

XMFLOAT2 GuiElement::getScale()
{
	return size;
}

void GuiManager::addGuiElement(GuiElement toAdd)
{
	guiElements.push_back(toAdd);
}

void GuiManager::setGuiElementVisible(string name, bool toSet)
{
	for (unsigned int i = 0; i < guiElements.size(); i++)
	{
		if (guiElements[i].getName() == name)
		{
			guiElements[i].setVisible(toSet);
		}
	}
}

unsigned int GuiManager::getNumGuiElements()
{
	return guiElements.size();
}

GuiElement *GuiManager::getGuiElement(string name)
{
	for (unsigned int i = 0; i < guiElements.size(); i++)
	{
		if (guiElements[i].getName() == name)
		{
			return &guiElements[i];
		}
	}

	MessageBoxA(NULL, ("Could not find gui element requested: " + name).c_str(), "Gui System Error", MB_ICONERROR | MB_OK);
	exit(0);
}

GuiElement *GuiManager::getGuiElement(int index)
{
	return &guiElements[index];
}