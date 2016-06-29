#include "UserInterfaceFile.h"

void UserInterfaceFile::parse()
{
	vector<string> fileContents = getFileContents();

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i][0] == 'w')
		{
			GuiWindow window;
			WindowStyle ws;
			int j = i + 1;

			for (j; fileContents[j][0] != 'e'; j++)
			{
				if (fileContents[j][0] == 'h' && fileContents[j][1] == 'e')
				{
					GuiHudElement hudElement;
					int k = j + 1;

					for (k; fileContents[k][0] != 'e'; k++)
					{
						if (fileContents[k][0] == 't')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							hudElement.addTexture(sections[1]);
						}

						else if (fileContents[k][0] == 'p')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							hudElement.setPosition(XMFLOAT2(stof(sections[1]), stof(sections[2])));
						}

						else if (fileContents[k][0] == 's')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							hudElement.setScale(XMFLOAT2(stof(sections[1]), stof(sections[2])));
						}

						else if (fileContents[k][0] == 'n')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							hudElement.setName(sections[1]);
						}
					}

					window.add(hudElement);
					j = k;
				}

				else if (fileContents[j][0] == 't' && fileContents[j][1] == 'e')
				{
					GuiTextElement textElement;
					int k = j + 1;

					for (k; fileContents[k][0] != 'e'; k++)
					{
						if (fileContents[k][0] == 't')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							textElement.setText(sections[1]);
						}

						else if (fileContents[k][0] == 'p')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							textElement.setPosition(XMFLOAT2(stof(sections[1]), stof(sections[2])));
						}

						else if (fileContents[k][0] == 's')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							textElement.setScale(XMFLOAT2(stof(sections[1]), stof(sections[2])));
						}

						else if (fileContents[k][0] == 'n')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							textElement.setName(sections[1]);
						}

						else if (fileContents[k][0] == 'f')
						{
							vector<string> sections = separateIntoSections(fileContents[k]);
							textElement.setFont(sections[1]);
						}
					}

					window.add(textElement);
					j = k;
				}

				else if (fileContents[j][0] == 't' && fileContents[j][1] == 'w')
				{
					vector<string> sections = separateIntoSections(fileContents[j]);
				}

				else if (fileContents[j][0] == 's' && fileContents[j][1] == 't' && fileContents[j][2] == 'w')
				{
					vector<string> sections = separateIntoSections(fileContents[j]);
					Texture topLeftCorner, verticalEdge;
					ws.textureSize = stoi(sections[1]);
					topLeftCorner.setName(sections[2]);
					verticalEdge.setName(sections[3]);
					ws.topLeftCorner = topLeftCorner;
					ws.verticalEdge = verticalEdge;
				}

				else if (fileContents[j][0] == 'n' && fileContents[j][1] == 'w')
				{
					vector<string> sections = separateIntoSections(fileContents[j]);
					window.setName(sections[1]);
				}

				else if (fileContents[j][0] == 'p' && fileContents[j][1] == 'w')
				{
					vector<string> sections = separateIntoSections(fileContents[j]);
					window.setPosition(XMFLOAT2(stof(sections[1]), stof(sections[2])));
				}

				else if (fileContents[j][0] == 's' && fileContents[j][1] == 'w')
				{
					vector<string> sections = separateIntoSections(fileContents[j]);
					window.setScale(XMFLOAT2(stof(sections[1]), stof(sections[2])));
				}
			}

			window.setWindowStyle(ws);
			gLayout.windows.push_back(window);
			i = j;
		}

		else if (fileContents[i][0] == 'n')
		{
			vector<string> sections = separateIntoSections(fileContents[i]);
			gLayout.name = sections[1];
		}
	}
}

GuiLayout UserInterfaceFile::loadUserInterfaceLayout(string filePath)
{
	load(filePath);
	parse();
	return gLayout;
}

GuiLayout UserInterfaceFile::getGuiLayout()
{
	return gLayout;
}

UserInterfaceFile::UserInterfaceFile()
{

}

UserInterfaceFile::UserInterfaceFile(string filePath)
{
	load(filePath);
	parse();
}
