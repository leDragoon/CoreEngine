#pragma once
#include<vector>
#include<fstream>
#include<string>
#include<Windows.h>

using std::vector;
using std::string;
using std::fstream;
using std::ios;
using std::getline;

class File
{
private:
	string filePath;
	vector<string> fileContents;
public:
	void load();
	void load(string path);
	void write();
	void write(vector<string> toWrite);
	void setFilePath(string path);
	string getFilePath();
	vector<string> getFileContents();

	File();
	File(string path);
};