#pragma once

using namespace FMOD;

class SoundManager
{
private:
	System* system;	//Device
	Sound** sound;	//Resource
	Channel** channel;	//��� ä��

	UINT buffer; //���� ����(Default + Extra)

	map<string, Sound**> sounds; //���� ����
	map<string, Sound**>::iterator iter;

	float volume;

public:
	SoundManager();
	~SoundManager();
	
	void AddSound(string name, string soundFile, bool loop = false);
	void Play(string name, float volume = 1.0f);
	void Stop(string name);
	void Pause(string name);
	void Resume(string name);

	bool Playing(string key);
	bool Paused(string key);

	void Update();
	
	void Volume(string name, float volume);
	float Volume() { return volume; }

};