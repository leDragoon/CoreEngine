#include "SettingsFile.h"

void SettingsFile::parse()
{
	vector<string> fileContents = getFileContents();

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i][0] == '[')
		{
			SettingsCategory cat;
			string catName;

			for (int j = 1; fileContents[i][j] != ']'; j++)
			{
				catName.push_back(fileContents[i][j]);
			}

			cat.name = catName;
	
			unsigned int j;
			for (j = i + 1; fileContents[j][0] != '[' && j < fileContents.size() - 1; j++)
			{
				if (fileContents[j] != "")
				{
					string varName;
					string varValue;

					unsigned int k;
					for (k = 0; fileContents[j][k] != '=' && k < fileContents[j].size(); k++)
					{
						if (fileContents[j][k] != ' ')
						{
							varName.push_back(fileContents[j][k]);
						}
					}

					if (k < fileContents[j].size())
					{
						 for (k = k + 1; k < fileContents[j].size(); k++)
						 {
							if (fileContents[j][k] != ' ')
							{
								varValue.push_back(fileContents[j][k]);
							}
						 }
					}

					cat.variableNames.push_back(varName);
					cat.variableValues.push_back(varValue);
				}
			}
			categories.push_back(cat);
		}
	}
}

void SettingsFile::loadFile(string path)
{
	load(path);
	parse();
}

SettingsCategory SettingsFile::getCategory(string catName)
{
	for (unsigned int i = 0; i < categories.size(); i++)
	{
		if (categories[i].name == catName)
		{
			return categories[i];
		}
	}

	return SettingsCategory();
}

string SettingsFile::getVariable(string catName, string varName)
{
	SettingsCategory cat = getCategory(catName);

	for (unsigned int i = 0; i < cat.variableNames.size(); i++)
	{
		if (cat.variableNames[i] == varName)
		{
			return cat.variableValues[i];
		}
	}

	return "Error";
}

bool SettingsFile::getBool(string catName, string varName)
{
	string varValue = getVariable(catName, varName);

	if (varValue == "true" || varValue == "True" || varValue == "1")
	{
		return true;
	}

	else
	{
		return false;
	}
}

int SettingsFile::getInt(string catName, string varName)
{
	string varValue = getVariable(catName, varName);
	return stoi(varValue);
}

char SettingsFile::getChar(string catName, string varName)
{
	string varValue = getVariable(catName, varName);
	return varValue[0];
}

float SettingsFile::getFloat(string catName, string varName)
{
	string varValue = getVariable(catName, varName);
	return stof(varValue);
}

string SettingsFile::getString(string catName, string varName)
{
	return getVariable(catName, varName);
}

string SettingsCategory::getVariable(string varName)
{
	for (unsigned int i = 0; i < variableNames.size(); i++)
	{
		if (variableNames[i] == varName)
		{
			return variableValues[i];
		}
	}

	return "Error";
}

bool SettingsCategory::getBool(string varName)
{
	string varValue = getVariable(varName);

	if (varValue == "true" || varValue == "True" || varValue == "1")
	{
		return true;
	}

	else
	{
		return false;
	}
}

int SettingsCategory::getInt(string varName)
{
	string varValue = getVariable(varName);
	return stoi(varValue);
}

char SettingsCategory::getChar(string varName)
{
	string varValue = getVariable(varName);
	return varValue[0];
}

float SettingsCategory::getFloat(string varName)
{
	string varValue = getVariable(varName);
	return stof(varValue);
}

string SettingsCategory::getString(string varName)
{
	return getVariable(varName);
}

SettingsFile::SettingsFile()
{

}

SettingsFile::SettingsFile(string path)
{
	loadFile(path);
}
