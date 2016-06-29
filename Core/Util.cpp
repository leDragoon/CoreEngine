#include<Util.h>

vector<string> separateIntoSections(string in)
{
	unsigned int onSection = 1;
	vector<string> toReturn;

	for (unsigned int i = 0; i < in.size(); i++)
	{
		if (in[i] == ' ' && in[i - 1] != ' ')
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

	vector<string> returnable;

	for (unsigned int i = 0; i < toReturn.size(); i++)
	{
		string toPush;
		for (unsigned int j = 0; j < toReturn[i].size(); j++)
		{
			if (toReturn[i][j] != ' ')
			{
				toPush.push_back(toReturn[i][j]);
			}
		}
		returnable.push_back(toPush);
	}

	return returnable;
}

bool startsWith(string in, string toCheck)
{
	vector<string> sections = separateIntoSections(in);

	if (sections[0] == toCheck)
	{
		return true;
	}

	return false;
}
