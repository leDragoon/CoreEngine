#pragma once
#include<FileManager.h>

using std::stoi;
using std::stof;

class SettingsCategory
{
public:
	string name;
	vector<string> variableNames;
	vector<string> variableValues;
	string getVariable(string varName);
	bool getBool(string varName);
	int getInt(string varName);
	char getChar(string varName);
	float getFloat(string varName);
	string getString(string varName);
};

class SettingsFile : public File
{
private:
	vector<SettingsCategory> categories;
	void parse();
public:
	void loadFile(string path);
	SettingsCategory getCategory(string catName);
	string getVariable(string catName, string varName);
	bool getBool(string catName, string varName);
	int getInt(string catName, string varName);
	char getChar(string catName, string varName);
	float getFloat(string catName, string varName);
	string getString(string catName, string varName);

	SettingsFile();
	SettingsFile(string path);
};