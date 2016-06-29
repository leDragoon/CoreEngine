#include "UserInterface.h"

void GuiElement::addTexture(string toAdd)
{
	texturesToBeLoaded.push_back(toAdd);
}

void GuiElement::addTexture(Texture *toAdd)
{
	textures.push_back(toAdd);
}

void GuiElement::setCurrentTexture(string toSet)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i]->getName() == toSet)
		{
			currentTextureName = textures[i]->getName();
			currentTexture = i;
		}
	}
}

void GuiElement::setCurrentTexture(int toSet)
{
	currentTexture = toSet;
	currentTextureName = textures[toSet]->getName();
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

void GuiElement::setNeedToBeLoaded(bool toSet)
{
	needsToBeLoaded = toSet;
}

void GuiButton::setOnHoverCallBack(function<void(void)> toSet)
{
	onHover = toSet;
}

void GuiButton::setOnClickCallBack(function<void(void)> toSet)
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

unsigned int GuiElement::getNumberOfTextures()
{
	return textures.size();
}

unsigned int GuiElement::getNumberOfTexturesToBeLoaded()
{
	return texturesToBeLoaded.size();
}

string GuiElement::getName()
{
	return name;
}

Texture *GuiElement::getTexture(int toGet)
{
	return textures[toGet];
}

Texture *GuiElement::getTexture(string toGet)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i]->getName() == toGet)
		{
			return textures[i];
		}
	}

	return textures[0];
}

string GuiElement::getCurrentTextureName()
{
	return currentTextureName;
}

vector<string> GuiElement::getTexturesToBeLoaded()
{
	return texturesToBeLoaded;
}

Texture *GuiElement::getCurrentTexture()
{
	return textures[currentTexture];
}

XMFLOAT2 GuiElement::getPosition()
{
	return position;
}

XMFLOAT2 GuiElement::getScale()
{
	return size;
}

void GuiManager::addGuiLayout(GuiLayout toAdd)
{
	guiLayouts.push_back(toAdd);
}

void GuiManager::setCurrentGuiLayout(int toSet)
{
	currentGuiLayout = toSet;
	currentGuiLayoutName = guiLayouts[toSet].name;
}

void GuiManager::setCurrentGuiLayout(string toSet)
{
	for (unsigned int i = 0; i < guiLayouts.size(); i++)
	{
		if (guiLayouts[i].name == toSet)
		{
			currentGuiLayout = i;
			currentGuiLayoutName = toSet;
		}
	}
}

void GuiManager::render(Model *quadModel, ID3D11DeviceContext *devCon, int outputWidth, int outputHeight, ID3D11ShaderResourceView *renderTexture, perObjectVertexData *perObjectVertexDataToBeSent1, ID3D11Buffer **perObjectVertexDataConstantBuffer)
{
	perObjectVertexData perObjectVertexDataToBeSent;

	for (unsigned int i = 0; i < getCurrentGuiLayout()->windows.size(); i++)
	{
		GuiWindow window = getCurrentGuiLayout()->windows[i];

		if (window.getIsVisible())
		{
			if (window.getCurrentTexture()->getResource() == NULL)
			{
				ID3D11ShaderResourceView* const v = renderTexture;
				devCon->PSSetShaderResources(0, 1, &v);
			}

			else
			{
				ID3D11ShaderResourceView* const v = window.getCurrentTexture()->getResource();
				devCon->PSSetShaderResources(0, 1, &v);
			}

			XMFLOAT2 pos = window.getPosition();
			XMFLOAT2 scl = window.getScale();
			quadModel->setPosition(XMFLOAT3(pos.x, pos.y - scl.y, 1.0f));
			quadModel->setScale(XMFLOAT3(scl.x, scl.y, 1.0f));
			perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
			devCon->UpdateSubresource(*perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
			devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);

			for (int j = 0; j < 4; j++)
			{
				quadModel->setRotation(XMFLOAT3(0.0f, 0.0f, 90.0f * j));

				if (j == 0)
				{
					ID3D11ShaderResourceView* const v = window.getWindowStyle()->verticalEdge.getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					quadModel->setScale(XMFLOAT3(1.0f, 0.02f, 1.0f));
					quadModel->setPosition(XMFLOAT3(0.0f, 1.0f - 0.02f, 1.0f));
					//perObjectVertexDataToBeSent->world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMMatrixScaling(0.0f, 0.0f, 0.0f));
					devCon->UpdateSubresource(*perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}

				else if (j == 1)
				{
					ID3D11ShaderResourceView* const v = window.getWindowStyle()->verticalEdge.getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					quadModel->setScale(XMFLOAT3(1.0f, 0.02f * ((float)outputHeight / outputWidth), 1.0f));
					quadModel->setPosition(XMFLOAT3(-1.0f + 0.01f, 0.0f, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(*perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					//devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}

				else if (j == 2)
				{
					ID3D11ShaderResourceView* const v = window.getWindowStyle()->verticalEdge.getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					quadModel->setScale(XMFLOAT3(1.0f, 0.02f, 1.0f));
					quadModel->setPosition(XMFLOAT3(0.0f, -1.0f + 0.02f, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(*perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					//devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}

				else
				{
					ID3D11ShaderResourceView* const v = window.getWindowStyle()->verticalEdge.getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					quadModel->setScale(XMFLOAT3(1.0f, 0.02f * ((float)outputHeight / outputWidth), 1.0f));
					quadModel->setPosition(XMFLOAT3(1.0f - 0.01f, 0.0f, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(*perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					//devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}
			}

			quadModel->setRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));

			for (unsigned int j = 0; j < window.getNumberOfHudElements(); j++)
			{
				if (window.getHudElement(j)->getIsVisible() == true)
				{
					ID3D11ShaderResourceView* const v = window.getHudElement(j)->getCurrentTexture()->getResource();
					devCon->PSSetShaderResources(0, 1, &v);
					XMFLOAT2 pos = window.getHudElement(j)->getPosition();
					XMFLOAT2 scl = window.getHudElement(j)->getScale();
					quadModel->setPosition(XMFLOAT3(pos.x, pos.y, 1.0f));
					quadModel->setScale(XMFLOAT3(scl.x, scl.y, 1.0f));
					perObjectVertexDataToBeSent.world = XMMatrixTranspose(XMLoadFloat4x4(&quadModel->getWorldMatrix()));
					devCon->UpdateSubresource(*perObjectVertexDataConstantBuffer, NULL, NULL, &perObjectVertexDataToBeSent, NULL, NULL);
					//devCon->DrawIndexed(quadModel->getNumberOfIndices(), 0, 0);
				}
			}
		}
	}
}

unsigned int GuiManager::getNumberOfGuiLayouts()
{
	return guiLayouts.size();
}

string GuiManager::getCurrentGuiLayoutName()
{
	return currentGuiLayoutName;
}

GuiLayout *GuiManager::getCurrentGuiLayout()
{
	return &guiLayouts[currentGuiLayout];
}

GuiLayout *GuiManager::getGuiLayout(string name)
{
	for (unsigned int i = 0; i < guiLayouts.size(); i++)
	{
		if (guiLayouts[i].name == name)
		{
			return &guiLayouts[i];
		}
	}

	return &guiLayouts[0];
}

GuiLayout *GuiManager::getGuiLayout(int index)
{
	return &guiLayouts[index];
}

void GuiWindow::add(GuiWindow toAdd)
{
	windows.push_back(toAdd);
}

void GuiWindow::add(GuiHudElement toAdd)
{
	HUDelements.push_back(toAdd);
}

void GuiWindow::add(GuiButton toAdd)
{
	buttons.push_back(toAdd);
}

void GuiWindow::add(GuiSlider toAdd)
{
	sliders.push_back(toAdd);
}

void GuiWindow::add(GuiTextInput toAdd)
{
	textInputs.push_back(toAdd);
}

void GuiWindow::add(GuiMenuBar toAdd)
{
	menuBars.push_back(toAdd);
}

void GuiWindow::add(GuiProgressBar toAdd)
{
	progressBars.push_back(toAdd);
}

void GuiWindow::add(GuiCheckBox toAdd)
{
	checkBoxes.push_back(toAdd);
}

void GuiWindow::add(GuiRadioButton toAdd)
{
	radioButtons.push_back(toAdd);
}

void GuiWindow::add(GuiTextElement toAdd)
{
	textElements.push_back(toAdd);
}

void GuiWindow::setWindowStyle(WindowStyle toSet)
{
	style = toSet;
}

unsigned int GuiWindow::getNumberOfHudElements()
{
	return HUDelements.size();
}

unsigned int GuiWindow::getNumberOfButtons()
{
	return buttons.size();
}

unsigned int GuiWindow::getNumberOfSliders()
{
	return sliders.size();
}

unsigned int GuiWindow::getNumberOfTextInputs()
{
	return textInputs.size();
}

unsigned int GuiWindow::getNumberOfMenuBars()
{
	return menuBars.size();
}

unsigned int GuiWindow::getNumberOfProgressBars()
{
	return progressBars.size();
}

unsigned int GuiWindow::getNumberOfCheckBoxes()
{
	return checkBoxes.size();
}

unsigned int GuiWindow::getNumberOfRadioButtons()
{
	return radioButtons.size();
}

unsigned int GuiWindow::getNumberOfTextElements()
{
	return textElements.size();
}

unsigned int GuiWindow::getNumberOfWindows()
{
	return windows.size();
}

WindowStyle *GuiWindow::getWindowStyle()
{
	return &style;
}

GuiWindow *GuiWindow::getWindow(int toGet)
{
	return nullptr;
}

GuiWindow *GuiWindow::getWindow(string toGet)
{
	return nullptr;
}

GuiHudElement *GuiWindow::getHudElement(int toGet)
{
	return &HUDelements[toGet];
}

GuiHudElement *GuiWindow::getHudElement(string toGet)
{
	for (unsigned int i = 0; i < HUDelements.size(); i++)
	{
		if (HUDelements[i].getName() == toGet)
		{
			return &HUDelements[i];
		}
	}

	return &HUDelements[0];
}

GuiButton *GuiWindow::getButton(int toGet)
{
	return &buttons[toGet];
}

GuiButton *GuiWindow::getButton(string toGet)
{
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].getName() == toGet)
		{
			return &buttons[i];
		}
	}

	return &buttons[0];
}

GuiSlider *GuiWindow::getSlider(int toGet)
{
	return &sliders[toGet];
}

GuiSlider *GuiWindow::getSlider(string toGet)
{
	for (unsigned int i = 0; i < sliders.size(); i++)
	{
		if (sliders[i].getName() == toGet)
		{
			return &sliders[i];
		}
	}

	return &sliders[0];
}

GuiTextInput *GuiWindow::getTextInput(int toGet)
{
	return &textInputs[toGet];
}

GuiTextInput *GuiWindow::getTextInput(string toGet)
{
	for (unsigned int i = 0; i < textInputs.size(); i++)
	{
		if (textInputs[i].getName() == toGet)
		{
			return &textInputs[i];
		}
	}

	return &textInputs[0];;
}

GuiMenuBar *GuiWindow::getMenuBar(int toGet)
{
	return &menuBars[toGet];
}

GuiMenuBar *GuiWindow::getMenuBar(string toGet)
{
	for (unsigned int i = 0; i < menuBars.size(); i++)
	{
		if (menuBars[i].getName() == toGet)
		{
			return &menuBars[i];
		}
	}

	return &menuBars[0];
}

GuiProgressBar *GuiWindow::getProgressBar(int toGet)
{
	return &progressBars[toGet];
}

GuiProgressBar *GuiWindow::getProgressBar(string toGet)
{
	for (unsigned int i = 0; i < progressBars.size(); i++)
	{
		if (progressBars[i].getName() == toGet)
		{
			return &progressBars[i];
		}
	}

	return &progressBars[0];
}

GuiCheckBox *GuiWindow::getCheckBox(int toGet)
{
	return &checkBoxes[toGet];
}

GuiCheckBox *GuiWindow::getCheckBox(string toGet)
{
	for (unsigned int i = 0; i < checkBoxes.size(); i++)
	{
		if (checkBoxes[i].getName() == toGet)
		{
			return &checkBoxes[i];
		}
	}

	return &checkBoxes[0];
}

GuiRadioButton *GuiWindow::getRadioButton(int toGet)
{
	return &radioButtons[toGet];
}

GuiRadioButton *GuiWindow::getRadioButton(string toGet)
{
	for (unsigned int i = 0; i < radioButtons.size(); i++)
	{
		if (radioButtons[i].getName() == toGet)
		{
			return &radioButtons[i];
		}
	}

	return &radioButtons[0];
}

GuiTextElement *GuiWindow::getTextElement(int toGet)
{
	return &textElements[toGet];
}

GuiTextElement *GuiWindow::getTextElement(string toGet)
{
	for (unsigned int i = 0; i < textElements.size(); i++)
	{
		if (textElements[i].getName() == toGet)
		{
			return &textElements[i];
		}
	}

	return &textElements[0];
}

void GuiFont::loadFromFile(string path)
{
	FontFile file(path);

	for (unsigned int i = 0; i < file.getCharCodes().size(); i++)
	{
		GuiTextCharacter ch;
		ch.charCode = file.getCharCodes()[i];
		ch.fontSheet = file.getFontSheets()[i];
		ch.height = file.getHeights()[i];
		ch.width = file.getWidths()[i];
		ch.xPos = file.getXPositions()[i];
		ch.yPos = file.getYPositions()[i];
		characters.push_back(ch);
	}
}

void GuiFont::addFontSheet(Texture toAdd)
{
	fontSheets.push_back(toAdd);
}

void GuiFont::addFontSheet(string toAdd)
{
	fontSheetsToLoad.push_back(toAdd);
}

void GuiFont::setName(string toSet)
{
	name = toSet;
}

string GuiFont::getName()
{
	return name;
}

vector<string> GuiFont::getFontSheetsToLoad()
{
	return fontSheetsToLoad;
}

Texture *GuiFont::getFontSheet(int toGet)
{
	return &fontSheets[toGet];
}

GuiTextCharacter GuiFont::getCharacter(char toGet)
{
	for (unsigned int i = 0; i < characters.size(); i++)
	{
		if (characters[i].charCode == toGet)
		{
			return characters[i];
		}
	}

	return GuiTextCharacter();
}

void GuiTextElement::setText(string toSet)
{
	text = toSet;
}

void GuiTextElement::setFont(GuiFont toSet)
{
	font = toSet;
}

void GuiTextElement::setFont(string toSet)
{
	fontName = toSet;
}

string GuiTextElement::getText()
{
	return text;
}

string GuiTextElement::getFontName()
{
	return fontName;
}

GuiFont *GuiTextElement::getFont()
{
	return &font;
}
