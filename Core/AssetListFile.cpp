#include "AssetListFile.h"

void AssetListFile::parse()
{
	vector<string> fileContents = getFileContents();

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i] != "")
		{
			if (fileContents[i][0] == 'm' && fileContents[i][1] == ' ')
			{
				vector<string> sections = separateIntoSections(fileContents[i]);
				assets.modelNames.push_back(sections[1]);
				assets.modelPaths.push_back(sections[2]);
			}

			else if (fileContents[i][0] == 'c' && fileContents[i][1] == 'm')
			{
				string sectionsMinusType = fileContents[i];
				sectionsMinusType.erase(sectionsMinusType.begin(), sectionsMinusType.begin() + 3);
				assets.cameraNames.push_back(sectionsMinusType);
			}

			else if (fileContents[i][0] == 'v' && fileContents[i][1] == 's')
			{
				vector<string> sections = separateIntoSections(fileContents[i]);
				assets.vertexShaderNames.push_back(sections[1]);
				assets.vertexShaderPaths.push_back(sections[2]);
			}

			else if (fileContents[i][0] == 'p' && fileContents[i][1] == 's')
			{
				vector<string> sections = separateIntoSections(fileContents[i]);
				assets.pixelShaderNames.push_back(sections[1]);
				assets.pixelShaderPaths.push_back(sections[2]);
			}

			else if (fileContents[i][0] == 'l')
			{
				vector<string> sections = separateIntoSections(fileContents[i]);
				assets.lightNames.push_back(sections[1]);
				assets.lightPaths.push_back(sections[2]);
			}

			else if (fileContents[i][0] == 't')
			{
				vector<string> sections = separateIntoSections(fileContents[i]);
				assets.textureNames.push_back(sections[1]);
				assets.texturePaths.push_back(sections[2]);
			}

			else if (fileContents[i][0] == 'm' && fileContents[i][1] == 't')
			{
				vector<string> sections = separateIntoSections(fileContents[i]);
				assets.materialNames.push_back(sections[1]);
				assets.materialPaths.push_back(sections[2]);
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

vector<string> AssetListFile::getCameraNames()
{
	return assets.cameraNames;
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

vector<string> AssetListFile::getLightNames()
{
	return assets.lightNames;
}

vector<string> AssetListFile::getLightPaths()
{
	return assets.lightPaths;
}

vector<string> AssetListFile::getTextureNames()
{
	return assets.textureNames;
}

vector<string> AssetListFile::getTexturePaths()
{
	return assets.texturePaths;
}

vector<string> AssetListFile::getMaterialNames()
{
	return assets.materialNames;
}

vector<string> AssetListFile::getMaterialPaths()
{
	return assets.materialPaths;
}

AssetListFile::AssetListFile()
{
}

AssetListFile::AssetListFile(string path)
{
	loadFile(path);
}
