#include "FileManager.h"

void File::load()
{
	fstream file;
	file.open(filePath, ios::in);

	if (!file.is_open())
	{
		MessageBox(NULL, ("Could not open file: " + filePath).c_str(), "File loading error", MB_ICONERROR | MB_OK);
		exit(0);
	}

	while (file.good())
	{
		string str;
		getline(file, str);
		fileContents.push_back(str);
	}

	file.close();
}

void File::load(string path)
{
	filePath = path;
	load();
}

void File::write()
{
	fstream file;
	file.open(filePath, ios::out | ios::trunc);

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		file << fileContents[i] + "\n";
	}

	file.close();
}

void File::write(vector<string> toWrite)
{
	fileContents = toWrite;
	write();
}

void File::setFilePath(string path)
{
	filePath = path;
}

string File::getFilePath()
{
	return filePath;
}

vector<string> File::getFileContents()
{
	return fileContents;
}

File::File()
{
	filePath = "";
}

File::File(string path)
{
	load(path);
}
