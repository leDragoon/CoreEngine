#include "SceneFile.h"

void SceneFile::parse()
{
	vector<string> fileContents = getFileContents();
	
	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i][0] == 'n' && fileContents[i][1] == ' ')
		{
			for (unsigned int j = 2; j < fileContents[i].size(); j++)
			{
				sceneName.push_back(fileContents[i][j]);
			}
		}

		else if (fileContents[i][0] == 's' && fileContents[i][1] == 't')
		{
			ObjectInstance instance;
			instance.type = CORE_OBJECTTYPE_SKYMAP;
			vector<string> names = separateIntoSections(fileContents[i]);
			instance.objectName = names[1];
			objectInstances.push_back(instance);
		}

		else if (fileContents[i][0] == 's' && fileContents[i][1] == 'n')
		{
			ObjectInstance instance;
			instance.type = CORE_OBJECTTYPE_SOUND;
			vector<string> names = separateIntoSections(fileContents[i]);
			instance.objectName = names[1];
			objectInstances.push_back(instance);
		}

		else if (fileContents[i][0] == 'l' && fileContents[i][1] == 'p')
		{
			ObjectInstance instance;
			instance.type = CORE_OBJECTTYPE_LIGHTPROBE;
			
			for (int j = i; fileContents[j][0] != 'e'; j++)
			{
				if (fileContents[j][0] == 'n' && fileContents[j][1] == 'm')
				{
					for (unsigned int k = 3; k < fileContents[j].size(); k++)
					{
						instance.objectName.push_back(fileContents[j][k]);
					}
				}

				else if (fileContents[j][0] == 'p')
				{
					string vectorInfo = fileContents[j];
					vectorInfo.erase(vectorInfo.begin(), vectorInfo.begin());
					vector<string> axes = separateIntoSections(vectorInfo);
					instance.position = DirectX::XMFLOAT3(stof(axes[1]), stof(axes[2]), stof(axes[3]));
				}

				else if (fileContents[j][0] == 'r')
				{
					string vectorInfo = fileContents[j];
					vectorInfo.erase(vectorInfo.begin(), vectorInfo.begin());
					vector<string> axes = separateIntoSections(vectorInfo);
					instance.rotation = DirectX::XMFLOAT3(stof(axes[1]), stof(axes[2]), stof(axes[3]));
				}

				else if (fileContents[j][0] == 's')
				{
					string vectorInfo = fileContents[j];
					vectorInfo.erase(vectorInfo.begin(), vectorInfo.begin());
					vector<string> axes = separateIntoSections(vectorInfo);
					instance.scale = DirectX::XMFLOAT3(stof(axes[1]), stof(axes[2]), stof(axes[3]));
				}
			}

			objectInstances.push_back(instance);
		}

		else if (fileContents[i][0] == 'm')
		{
			ObjectInstance instance;
			instance.type = CORE_OBJECTTYPE_MODEL;

			for (int j = i; fileContents[j][0] != 'e'; j++)
			{
				if (fileContents[j][0] == 'n' && fileContents[j][1] == 'm')
				{
					for (unsigned int k = 3; k < fileContents[j].size(); k++)
					{
						instance.objectName.push_back(fileContents[j][k]);
					}
				}

				else if (fileContents[j][0] == 'p')
				{
					string vectorInfo = fileContents[j];
					vectorInfo.erase(vectorInfo.begin(), vectorInfo.begin());
					vector<string> axes = separateIntoSections(vectorInfo);
					instance.position =  DirectX::XMFLOAT3(stof(axes[1]), stof(axes[2]), stof(axes[3]));
				}

				else if (fileContents[j][0] == 'r')
				{
					string vectorInfo = fileContents[j];
					vectorInfo.erase(vectorInfo.begin(), vectorInfo.begin());
					vector<string> axes = separateIntoSections(vectorInfo);
					instance.rotation = DirectX::XMFLOAT3(stof(axes[1]), stof(axes[2]), stof(axes[3]));
				}

				else if (fileContents[j][0] == 's')
				{
					string vectorInfo = fileContents[j];
					vectorInfo.erase(vectorInfo.begin(), vectorInfo.begin());
					vector<string> axes = separateIntoSections(vectorInfo);
					instance.scale = DirectX::XMFLOAT3(stof(axes[1]), stof(axes[2]), stof(axes[3]));
				}

				else if (fileContents[j][0] == 'c')
				{
					string scriptInfo = fileContents[j];
					scriptInfo.erase(scriptInfo.begin(), scriptInfo.begin());
					vector<string> name = separateIntoSections(scriptInfo);
					instance.scripts.push_back(name[1]);
				}
			}

			objectInstances.push_back(instance);
		}

		else if (fileContents[i][0] == 'c' && fileContents[i][1] == 'm')
		{
			ObjectInstance instance;
			instance.type = 10;

			for (int j = i; fileContents[j][0] != 'e'; j++)
			{
				if (fileContents[j][0] == 'n' && fileContents[j][1] == 'm')
				{
					for (unsigned int k = 3; k < fileContents[j].size(); k++)
					{
						instance.objectName.push_back(fileContents[j][k]);
					}
				}

				else if (fileContents[j][0] == 'p')
				{
					string vectorInfo = fileContents[j];
					vectorInfo.erase(vectorInfo.begin(), vectorInfo.begin());
					vector<string> axes = separateIntoSections(vectorInfo);
					instance.position = DirectX::XMFLOAT3(stof(axes[1]), stof(axes[2]), stof(axes[3]));
				}

				else if (fileContents[j][0] == 'r')
				{
					string vectorInfo = fileContents[j];
					vectorInfo.erase(vectorInfo.begin(), vectorInfo.begin());
					vector<string> axes = separateIntoSections(vectorInfo);
					instance.rotation = DirectX::XMFLOAT3(stof(axes[1]), stof(axes[2]), stof(axes[3]));
				}
			}

			objectInstances.push_back(instance);
		}
	}

	assignObjectInstanceIdentifiers();
}

void SceneFile::assignObjectInstanceIdentifiers()
{
	for (unsigned int i = 0; i < objectInstances.size(); i++)
	{
		for (unsigned int j = 0; j < objectInstances.size(); j++)
		{
			if (objectInstances[i].objectName == objectInstances[j].objectName)
			{
				if (objectInstances[i].identifier == objectInstances[j].identifier)
				{
					objectInstances[j].identifier++;
				}
			}
		}
	}
}


void SceneFile::loadFile()
{
	load(getFilePath());
	parse();
}

void SceneFile::loadFile(string path)
{
	load(path);
	parse();
}

vector<ObjectInstance> SceneFile::getObjectInstances()
{
	return objectInstances;
}

string SceneFile::getSceneName()
{
	return sceneName;
}

SceneFile::SceneFile()
{

}

SceneFile::SceneFile(string path)
{
	loadFile(path);
}
