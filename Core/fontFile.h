#pragma once
#include<FileManager.h>
#include<Texture.h>
#include<Util.h>

class FontFile : public File
{
private:
	vector<int> charCodes;
	vector<int> fontSheets;
	vector<int> xPositions;
	vector<int> yPositions;
	vector<int> widths;
	vector<int> heights;

	void parse();
public:
	void loadFromFile(string path);

	vector<int> getCharCodes();
	vector<int> getFontSheets();
	vector<int> getXPositions();
	vector<int> getYPositions();
	vector<int> getWidths();
	vector<int> getHeights();

	FontFile();
	FontFile(string path);
};