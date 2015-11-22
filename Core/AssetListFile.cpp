#include "AssetListFile.h"

void AssetListFile::parse()
{
	vector<string> fileContents = getFileContents();

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i] != "")
		{
			if (fileContents[i][0] == 'm')
			{
				string sectionsMinusType = fileContents[i];
				sectionsMinusType.erase(sectionsMinusType.begin(), sectionsMinusType.begin() + 2);
				vector<string> sections = separateIntoSections(sectionsMinusType);
				assets.modelNames.push_back(sections[0]);
				assets.modelPaths.push_back(sections[1]);
			}

			else if (fileContents[i][0] == 'v' && fileContents[i][1] == 's')
			{
				string sectionsMinusType = fileContents[i];
				sectionsMinusType.erase(sectionsMinusType.begin(), sectionsMinusType.begin() + 3);
				vector<string> sections = separateIntoSections(sectionsMinusType);
				assets.vertexShaderNames.push_back(sections[0]);
				assets.vertexShaderPaths.push_back(sections[1]);
			}

			else if (fileContents[i][0] == 'p' && fileContents[i][1] == 's')
			{
				string sectionsMinusType = fileContents[i];
				sectionsMinusType.erase(sectionsMinusType.begin(), sectionsMinusType.begin() + 3);
				vector<string> sections = separateIntoSections(sectionsMinusType);
				assets.pixelShaderNames.push_back(sections[0]);
				assets.pixelShaderPaths.push_back(sections[1]);
			}
		}
	}
}


void AssetListFile::loadFile(string path)
{
	load(path);
	parse();
}

AssetList AssetListFile::getAssetList()
{
	return assets;
}

vector<string> AssetListFile::getModelNames()
{
	return assets.modelNames;
}

vector<string> AssetListFile::getModelPaths()
{
	return assets.modelPaths;
}

vector<string> AssetListFile::getVertexShaderNames()
{
	return assets.vertexShaderNames;
}

vector<string> AssetListFile::getVertexShaderPaths()
{
	return assets.vertexShaderPaths;
}

vector<string> AssetListFile::getPixelShaderNames()
{
	return assets.pixelShaderNames;
}

vector<string> AssetListFile::getPixelShaderPaths()
{
	return assets.pixelShaderPaths;
}

AssetListFile::AssetListFile()
{
}

AssetListFile::AssetListFile(string path)
{
	loadFile(path);
}
