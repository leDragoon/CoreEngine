#include "MaterialFile.h"

void MaterialFile::loadMaterial(string path)
{
	load(path);
	vector<string> fileContents = getFileContents();

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i][0] == 'n' && fileContents[i][1] == ' ')
		{
			for (unsigned int j = 2; j < fileContents[i].size(); j++)
			{
				name += fileContents[i][j];
			}
		}

		else if (fileContents[i][0] == 't')
		{
			string tName;

			if (fileContents[i][1] == 'a')
			{
				textureUsages.push_back(1);
			}

			else if (fileContents[i][1] == 'n')
			{
				textureUsages.push_back(2);
			}

			else if (fileContents[i][1] == 'm')
			{
				textureUsages.push_back(3);
			}

			else if (fileContents[i][1] == 'r')
			{
				textureUsages.push_back(4);
			}

			else if (fileContents[i][1] == 'e')
			{
				textureUsages.push_back(6);
			}

			else if (fileContents[i][1] == 'o')
			{
				textureUsages.push_back(5);
			}

			for (unsigned int j = 3; j < fileContents[i].size(); j++)
			{
				tName.push_back(fileContents[i][j]);
			}

			textureNames.push_back(tName);
		}

		else if (fileContents[i][0] == 'v' && fileContents[i][1] == 's')
		{
			string vName;

			for (unsigned int j = 3; j < fileContents[i].size(); j++)
			{
				vName.push_back(fileContents[i][j]);
			}

			vertexShaderNames.push_back(vName);
		}

		else if (fileContents[i][0] == 'p' && fileContents[i][1] == 's')
		{
			string pName;
			
			for (unsigned int j = 3; j < fileContents[i].size(); j++)
			{
				pName.push_back(fileContents[i][j]);
			}

			pixelShaderNames.push_back(pName);
		}
	}
}

vector<int> MaterialFile::getTextureUsages()
{
	return textureUsages;
}

vector<string> MaterialFile::getTextureNames()
{
	return textureNames;
}

vector<string> MaterialFile::getVertexShaderNames()
{
	return vertexShaderNames;
}

vector<string> MaterialFile::getPixelShaderNames()
{
	return pixelShaderNames;
}

MaterialFile::MaterialFile()
{

}

MaterialFile::MaterialFile(string path)
{

}
