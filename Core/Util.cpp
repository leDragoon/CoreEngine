#include<Util.h>

vector<string> separateIntoSections(string in)
{
	unsigned int onSection = 1;
	vector<string> toReturn;

	for (unsigned int i = 0; i < in.size(); i++)
	{
		if (in[i] == ' ')
		{
			onSection++;
		}

		else
		{
			if (onSection > toReturn.size())
			{
				toReturn.push_back("");
			}

			toReturn[onSection - 1].push_back(in[i]);
		}
	}

	return toReturn;
}