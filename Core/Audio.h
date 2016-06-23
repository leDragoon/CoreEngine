#pragma once
#include<string>
#include<vector>
#include<DirectXMath.h>
#include<C:\Resources\yse_binary_release_windows\include\yse.hpp>
#include<Windows.h>

#pragma comment(lib, "C://Resources//yse_binary_release_windows//lib//dll//libyse32.lib")

using std::string;
using std::vector;

class AudioHandler
{
private:
	vector<string> soundNames;
	vector<YSE::sound> sounds;
public:
	void init();
	void update();
	void addSound(string path, string name);
	void addSound(string path, string name, YSE::channel channel);
	void playSound(string name);
	void pauseSound(string name);
	void stopSound(string name);
	void setSoundLooping(string name, bool loop);
	void setSoundVolume(string name, float volume);
	void setSoundPosition(string name, DirectX::XMFLOAT3 position);
	void close();
	AudioHandler();
};