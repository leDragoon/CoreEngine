#include "Audio.h"

void AudioHandler::init()
{
	YSE::System().init();
}

void AudioHandler::update()
{
	YSE::System().update();
}

void AudioHandler::addSound(string path, string name)
{
	YSE::sound snd;
	snd.create(path.c_str());

	if (!snd.isValid())
	{
		MessageBox(NULL, ("Could not load sound: " + path).c_str(), "Sound Load Error", MB_ICONERROR | MB_OK);
		exit(0);
	}
}

void AudioHandler::addSound(string path, string name, YSE::channel channel)
{
	YSE::sound snd;
	snd.create(path.c_str(), &channel);

	if (!snd.isValid())
	{
		MessageBox(NULL, ("Could not load sound: " + path).c_str(), "Sound Load Error", MB_ICONERROR | MB_OK);
		exit(0);
	}
}

void AudioHandler::playSound(string name)
{
	for (unsigned int i = 0; i < soundNames.size(); i++)
	{
		if (soundNames[i] == name)
		{
			sounds[i].play();
		}
	}
}

void AudioHandler::pauseSound(string name)
{
	for (unsigned int i = 0; i < soundNames.size(); i++)
	{
		if (soundNames[i] == name)
		{
			sounds[i].pause();
		}
	}
}

void AudioHandler::stopSound(string name)
{
	for (unsigned int i = 0; i < soundNames.size(); i++)
	{
		if (soundNames[i] == name)
		{
			sounds[i].stop();
		}
	}
}

void AudioHandler::setSoundLooping(string name, bool loop)
{
	for (unsigned int i = 0; i < soundNames.size(); i++)
	{
		if (soundNames[i] == name)
		{
			sounds[i].setLooping(loop);
		}
	}
}

void AudioHandler::setSoundVolume(string name, float volume)
{
	for (unsigned int i = 0; i < soundNames.size(); i++)
	{
		if (soundNames[i] == name)
		{
			sounds[i].setVolume(volume);
		}
	}
}

void AudioHandler::setSoundPosition(string name, DirectX::XMFLOAT3 position)
{
	for (unsigned int i = 0; i < soundNames.size(); i++)
	{
		if (soundNames[i] == name)
		{
			sounds[i].setPosition(YSE::Vec(position.x, position.y, position.z));
		}
	}
}

void AudioHandler::close()
{
	YSE::System().close();
}

AudioHandler::AudioHandler()
{
	init();
}
