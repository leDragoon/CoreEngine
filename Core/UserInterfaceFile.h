#pragma once
#include<FileManager.h>
#include<UserInterface.h>
#include<Util.h>
#include<string>

using namespace std;

class UserInterfaceFile : public File
{
private:
	void parse();
	GuiElement gElement;
public:
	GuiElement loadUserInterfaceElement(string filePath);
	GuiElement getGuiElement();
	UserInterfaceFile();
	UserInterfaceFile(string filePath);
};
