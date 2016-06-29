#include "fontFile.h"

void FontFile::parse()
{
	vector<string> fileContents = getFileContents();

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		vector<string> sections = separateIntoSections(fileContents[i]);

		for (unsigned int j = 0; j < sections.size(); j++)
		{
			if (sections[j][0] == 'i' && sections[j][1] == 'd' && sections[0][0] == 'c' && sections[0][1] == 'h')
			{
				string id = sections[j];
				id.erase(id.begin(), id.begin() + 3);
				charCodes.push_back(stoi(id));
			}

			else if (sections[j][0] == 'x' && sections[j][1] == '=' && sections[0][0] == 'c' && sections[0][1] == 'h')
			{
				string x = sections[j];
				x.erase(x.begin(), x.begin() + 2);
				xPositions.push_back(stoi(x));
			}

			else if (sections[j][0] == 'y' && sections[j][1] == '=' && sections[0][0] == 'c' && sections[0][1] == 'h')
			{
				string x = sections[j];
				x.erase(x.begin(), x.begin() + 2);
				yPositions.push_back(stoi(x));
			}

			else if (sections[j][0] == 'w' && sections[j][1] == 'i' && sections[0][0] == 'c' && sections[0][1] == 'h')
			{
				string x = sections[j];
				x.erase(x.begin(), x.begin() + 6);
				widths.push_back(stoi(x));
			}

			else if (sections[j][0] == 'h' && sections[j][1] == 'e' && sections[0][0] == 'c' && sections[0][1] == 'h')
			{
				string x = sections[j];
				x.erase(x.begin(), x.begin() + 7);
				heights.push_back(stoi(x));
			}

			else if (sections[j][0] == 'p' && sections[j][1] == 'a' && sections[0][0] == 'c' && sections[0][1] == 'h')
			{
				string x = sections[j];
				x.erase(x.begin(), x.begin() + 5);
				fontSheets.push_back(stoi(x));
			}
		}
	}
}

void FontFile::loadFromFile(string path)
{
	load(path);
	parse();
}

vector<int> FontFile::getCharCodes()
{
	return charCodes;
}

vector<int> FontFile::getFontSheets()
{
	return fontSheets;
}

vector<int> FontFile::getXPositions()
{
	return xPositions;
}

vector<int> FontFile::getYPositions()
{
	return yPositions;
}

vector<int> FontFile::getWidths()
{
	return widths;
}

vector<int> FontFile::getHeights()
{
	return heights;
}

FontFile::FontFile()
{
}

FontFile::FontFile(string path)
{
	loadFromFile(path);
}
