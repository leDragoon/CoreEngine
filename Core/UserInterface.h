#pragma once
#include<Texture.h>
#include<DirectXMath.h>
#include<functional>
#include<fontFile.h>
#include<Model.h>
#include<d3d11.h>

using namespace DirectX;
using namespace std;

struct perObjectVertexData
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX WorldViewProjection;
};

class GuiElement
{
private:
	string name;
	string currentTextureName;
	vector<Texture*> textures;
	vector<string> texturesToBeLoaded;
	XMFLOAT4 guiColour;
	XMFLOAT2 position;
	XMFLOAT2 size;
	GuiElement *parent;
	int currentTexture = 0;
	bool visible = true;
	bool needsToBeLoaded = true;
public:
	void addTexture(string toAdd);
	void addTexture(Texture *toAdd);
	void setCurrentTexture(string toSet);
	void setCurrentTexture(int toSet);
	void setColor(DirectX::XMFLOAT4 toSet);
	void setPosition(XMFLOAT2 toSet);
	void setScale(XMFLOAT2 toSet);
	void setVisible(bool toSet);
	void setName(string toSet);
	void setNeedToBeLoaded(bool toSet);

	bool getIsVisible();
	bool getNeedsToBeLoaded();
	unsigned int getNumberOfTextures();
	unsigned int getNumberOfTexturesToBeLoaded();
	string getName();
	string getCurrentTextureName();
	vector<string> getTexturesToBeLoaded();
	Texture *getTexture(int toGet);
	Texture *getTexture(string toGet);
	Texture *getCurrentTexture();
	XMFLOAT2 getPosition();
	XMFLOAT2 getScale();
};

class GuiHudElement : public GuiElement
{

};

class GuiButton : public GuiElement
{
private:
	function<void(void)> onHover;
	function<void(void)> onClick;
public:
	void setOnHoverCallBack(function<void(void)> toSet);
	void setOnClickCallBack(function<void(void)> toSet);
};

class GuiSlider : public GuiElement
{

};

class GuiTextInput : public GuiElement
{

};

class GuiMenuBar : public GuiElement
{

};

class GuiProgressBar : public GuiElement
{

};

class GuiCheckBox : public GuiElement
{

};

class GuiRadioButton : public GuiElement
{

};

struct GuiTextCharacter
{
	int charCode;
	int fontSheet;
	int xPos;
	int yPos;
	int width;
	int height;
};

class GuiFont
{
private:
	string name;
	vector<string> fontSheetsToLoad;
	vector<Texture> fontSheets;
	vector<GuiTextCharacter> characters;
public:
	void loadFromFile(string path);
	void addFontSheet(Texture toAdd);
	void addFontSheet(string toAdd);
	void setName(string toSet);

	string getName();
	vector<string> getFontSheetsToLoad();
	Texture* getFontSheet(int toGet);
	GuiTextCharacter getCharacter(char toGet);
};

class GuiTextElement : public GuiElement
{
private:
	string text;
	string fontName;
	GuiFont font;
public:
	void setText(string toSet);
	void setFont(GuiFont toSet);
	void setFont(string toSet);

	string getText();
	string getFontName();
	GuiFont *getFont();
};

struct WindowStyle
{
	Texture topLeftCorner;
	Texture verticalEdge;
	int textureSize;
};

class GuiWindow : public GuiElement
{
private:
	WindowStyle style;
	vector<GuiWindow> windows;
	vector<GuiHudElement> HUDelements;
	vector<GuiButton> buttons;
	vector<GuiSlider> sliders;
	vector<GuiTextInput> textInputs;
	vector<GuiMenuBar> menuBars;
	vector<GuiProgressBar> progressBars;
	vector<GuiCheckBox> checkBoxes;
	vector<GuiRadioButton> radioButtons;
	vector<GuiTextElement> textElements;
public:
	void add(GuiWindow toAdd);
	void add(GuiHudElement toAdd);
	void add(GuiButton toAdd);
	void add(GuiSlider toAdd);
	void add(GuiTextInput toAdd);
	void add(GuiMenuBar toAdd);
	void add(GuiProgressBar toAdd);
	void add(GuiCheckBox toAdd);
	void add(GuiRadioButton toAdd);
	void add(GuiTextElement toAdd);
	void setWindowStyle(WindowStyle toSet);

	unsigned int getNumberOfHudElements();
	unsigned int getNumberOfButtons();
	unsigned int getNumberOfSliders();
	unsigned int getNumberOfTextInputs();
	unsigned int getNumberOfMenuBars();
	unsigned int getNumberOfProgressBars();
	unsigned int getNumberOfCheckBoxes();
	unsigned int getNumberOfRadioButtons();
	unsigned int getNumberOfTextElements();
	unsigned int getNumberOfWindows();

	WindowStyle *getWindowStyle();
	GuiWindow *getWindow(int toGet);
	GuiWindow *getWindow(string toGet);
	GuiHudElement *getHudElement(int toGet);
	GuiHudElement *getHudElement(string toGet);
	GuiButton *getButton(int toGet);
	GuiButton *getButton(string toGet);
	GuiSlider *getSlider(int toGet);
	GuiSlider *getSlider(string toGet);
	GuiTextInput *getTextInput(int toGet);
	GuiTextInput *getTextInput(string toGet);
	GuiMenuBar *getMenuBar(int toGet);
	GuiMenuBar *getMenuBar(string toGet);
	GuiProgressBar *getProgressBar(int toGet);
	GuiProgressBar *getProgressBar(string toGet);
	GuiCheckBox *getCheckBox(int toGet);
	GuiCheckBox *getCheckBox(string toGet);
	GuiRadioButton *getRadioButton(int toGet);
	GuiRadioButton *getRadioButton(string toGet);
	GuiTextElement *getTextElement(int toGet);
	GuiTextElement *getTextElement(string toGet);
};

struct GuiLayout
{
	string name;
	vector<GuiFont> fonts;
	vector<GuiWindow> windows;
};

class GuiManager
{
private:
	int currentGuiLayout = 0;
	string currentGuiLayoutName;
	vector<GuiLayout> guiLayouts;
public:
	void addGuiLayout(GuiLayout toAdd);
	void setCurrentGuiLayout(int toSet);
	void setCurrentGuiLayout(string toSet);

	void render(Model *quadModel, ID3D11DeviceContext *devCon, int outputWidth, int outputHeight, ID3D11ShaderResourceView *renderTexture, perObjectVertexData *perObjectVertexDataToBeSent, ID3D11Buffer **perObjectVertexDataConstantBuffer);
	unsigned int getNumberOfGuiLayouts();
	string getCurrentGuiLayoutName();
	GuiLayout *getCurrentGuiLayout();
	GuiLayout *getGuiLayout(string name);
	GuiLayout *getGuiLayout(int index);
};