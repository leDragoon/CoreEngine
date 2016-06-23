#include "LightFile.h"

void LightFile::parse()
{
	vector<string> fileContents = getFileContents();

	for (unsigned int i = 0; i < fileContents.size(); i++)
	{
		if (fileContents[i][0] == 'n')
		{
			vector<string> sep = separateIntoSections(fileContents[i]);
			light.setName(sep[1]);
		}
		
		else if (fileContents[i][0] == 't')
		{
			vector<string> sep = separateIntoSections(fileContents[i]);

			if (sep[1] == "p")
			{
				light.setLightType(CORE_LIGHTTYPE_POINT);
			}

			else if (sep[1] == "s")
			{
				light.setLightType(CORE_LIGHTTYPE_SPOT);
			}

			else if (sep[1] == "d")
			{
				light.setLightType(CORE_LIGHTTYPE_DISC);
			}

			else if (sep[1] == "sp")
			{
				light.setLightType(CORE_LIGHTTYPE_SPHERE);
			}

			else if (sep[1] == "t")
			{
				light.setLightType(CORE_LIGHTTYPE_TUBE);
			}
		}

		else if (fileContents[i][0] == 'i')
		{
			vector<string> sep = separateIntoSections(fileContents[i]);
			light.setLightIntensity(stof(sep[1]));
		}

		else if (fileContents[i][0] == 'a')
		{
			vector<string> sep = separateIntoSections(fileContents[i]);
			light.setLightAttenuationRange(stof(sep[1]));
		}

		else if (fileContents[i][0] == 't' && fileContents[i][1] == 'm')
		{
			vector<string> sep = separateIntoSections(fileContents[i]);
			light.setLightTemperature(stof(sep[1]));
		}

		else if (fileContents[i][0] == 'c')
		{
			vector<string> sep = separateIntoSections(fileContents[i]);
			light.setLightColor(XMFLOAT3(stof(sep[1]), stof(sep[2]), stof(sep[3])));
		}

		else if (fileContents[i][0] == 'd')
		{
			vector<string> sep = separateIntoSections(fileContents[i]);
			light.setLightDirection(XMFLOAT3(stof(sep[1]), stof(sep[2]), stof(sep[3])));
		}

		else if (fileContents[i][0] == 'p')
		{
			vector<string> sep = separateIntoSections(fileContents[i]);
			light.setLightPosition(XMFLOAT3(stof(sep[1]), stof(sep[2]), stof(sep[3])));
		}
	}
}

Light LightFile::getLight()
{
	return light;
}

Light LightFile::loadLightFile(string path)
{
	load(path);
	parse();
	return light;
}

LightFile::LightFile()
{

}

LightFile::LightFile(string path)
{
	loadLightFile(path);
}
