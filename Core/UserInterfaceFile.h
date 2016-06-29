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
	GuiLayout gLayout;
public:
	GuiLayout loadUserInterfaceLayout(string filePath);
	GuiLayout getGuiLayout();
	UserInterfaceFile();
	UserInterfaceFile(string filePath);
};
