#include "UserInterfaceFile.h"

void UserInterfaceFile::parse()
{
	vector<string> fileContents = getFileContents();

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i][0] == 't' && fileContents[i][1] == ' ')
		{
			vector<string> sections = separateIntoSections(fileContents[i]);
			gElement.setTextureName(sections[1]);
		}

		else if (fileContents[i][0] == 't' && fileContents[i][1] == 'h')
		{
			vector<string> sections = separateIntoSections(fileContents[i]);
			gElement.setHoverTextureName(sections[1]);
		}

		else if (fileContents[i][0] == 'p')
		{
			vector<string> sections = separateIntoSections(fileContents[i]);
			gElement.setPosition(XMFLOAT2(stof(sections[1]), stof(sections[2])));
		}

		else if (fileContents[i][0] == 's')
		{
			vector<string> sections = separateIntoSections(fileContents[i]);
			gElement.setScale(XMFLOAT2(stof(sections[1]), stof(sections[2])));
		}

		else if (fileContents[i][0] == 'n')
		{
			vector<string> sections = separateIntoSections(fileContents[i]);
			gElement.setName(sections[1]);
		}
	}
}

GuiElement UserInterfaceFile::loadUserInterfaceElement(string filePath)
{
	load(filePath);
	parse();
	return gElement;
}

GuiElement UserInterfaceFile::getGuiElement()
{
	return gElement;
}

UserInterfaceFile::UserInterfaceFile()
{

}

UserInterfaceFile::UserInterfaceFile(string filePath)
{
	load(filePath);
	parse();
}
