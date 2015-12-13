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

string File::getFileExtension()
{
	string fileExtension = "Error";

	for (unsigned int i = 0; i < filePath.size(); i++)
	{
		if (filePath[i] == '.')
		{
			fileExtension = "";
			for (unsigned int j = i + 1; j < filePath.size(); j++)
			{
				fileExtension.push_back(filePath[j]);
			}
			break;
		}
	}

	for (unsigned int i = 0; i < fileExtension.size(); i++)
	{
		fileExtension[i] = toupper(fileExtension[i]);
	}

	return fileExtension;
}

string getFileExtension(string filePath)
{
	string fileExtension = "Error";

	for (unsigned int i = 0; i < filePath.size(); i++)
	{
		if (filePath[i] == '.')
		{
			fileExtension = "";
			for (unsigned int j = i + 1; j < filePath.size(); j++)
			{
				fileExtension.push_back(filePath[j]);
			}
			break;
		}
	}

	for (unsigned int i = 0; i < fileExtension.size(); i++)
	{
		fileExtension[i] = toupper(fileExtension[i]);
	}

	return fileExtension;
}

File::File()
{
	filePath = "";
}

File::File(string path)
{
	load(path);
}
