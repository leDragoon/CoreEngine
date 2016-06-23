#pragma once
#include<Texture.h>
#include<DirectXMath.h>
#include<functional>

using namespace DirectX;
using namespace std;

class GuiElement
{
private:
	string name;
	string textureName;
	string hoverTextureName;
	Texture *guiTexture;
	Texture *guiHoverTexture;
	XMFLOAT4 guiColour;
	XMFLOAT2 position;
	XMFLOAT2 size;
	function<void(void)> onHover;
	function<void(void)> onClick;
	GuiElement *parent;
	bool visible = true;
	bool needsToBeLoaded = true;
public:
	void setTexture(Texture *toSet);
	void setHoverTexture(Texture *toSet);
	void setColor(DirectX::XMFLOAT4 toSet);
	void setPosition(XMFLOAT2 toSet);
	void setScale(XMFLOAT2 toSet);
	void setVisible(bool toSet);
	void setName(string toSet);
	void setTextureName(string toSet);
	void setHoverTextureName(string toSet);
	void setNeedToBeLoaded(bool toSet);
	void setOnHoverCallBack(function<void(void)> toSet);
	void setOnClickCallBack(function<void(void)> toSet);

	bool getIsVisible();
	bool getNeedsToBeLoaded();
	string getName();
	string getTextureName();
	string getHoverTextureName();
	Texture *getTexture();
	Texture *getHoverTexture();
	XMFLOAT2 getPosition();
	XMFLOAT2 getScale();
};

class HUDElement : public GuiElement
{

};

class GuiManager
{
private:
	vector<GuiElement> guiElements;
public:
	void addGuiElement(GuiElement toAdd);
	void setGuiElementVisible(string name, bool toSet);

	unsigned int getNumGuiElements();
	GuiElement *getGuiElement(string name);
	GuiElement *getGuiElement(int index);
};