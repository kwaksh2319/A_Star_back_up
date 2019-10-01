#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
	:system(NULL), channel(NULL), sound(NULL), buffer(15), volume(1.0f)
{
	//�ý��� ����
	System_Create(&system);	
	system->init(buffer, FMOD_INIT_NORMAL, NULL);

	//ä�� ����
	sound = new Sound*[buffer]; 
	channel = new Channel*[buffer];

	//����, ä�� �迭 NULL �ʱ�ȭ
	memset(sound, NULL, sizeof(Sound*) * buffer);
	memset(channel, NULL, sizeof(Channel*) * buffer);
	//ZeroMemory(sound, sizeof(Sound*) * buffer);

}

SoundManager::~SoundManager()
{
	//ä�� Ȥ�� ���尡 ��� ���� ���¶��
	if (channel != NULL || sound != NULL)
	{
		for (UINT i = 0; i < buffer; i++)
		{
			if (channel != NULL)
			{
				if (channel[i]) channel[i]->stop();
			}

			if (sound != NULL)
			{
				if (sound[i]) sound[i]->release();
			}

		}
	}

	SAFE_DELETE(channel);
	SAFE_DELETE(sound);

	//�ý��� �ݱ�
	if (system != NULL)
	{
		system->release();
		system->close();
	}

	sounds.clear();
}

void SoundManager::AddSound(string name, string soundFile, bool loop)
{
	if (loop == true)
	{
		system->createStream
		(
			soundFile.c_str(),
			FMOD_LOOP_NORMAL, //����
			NULL,
			&sound[sounds.size()]
		);
	}
	else
	{
		system->createStream
		(
			soundFile.c_str(),
			FMOD_DEFAULT,
			NULL,
			&sound[sounds.size()]
		);
	}

	//name + sound resource�� �ʿ� ����(pair)
	sounds.insert(make_pair(name, &sound[sounds.size()]));

}

void SoundManager::Play(string name, float volume)
{
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			//�ش� ���� �÷���
			system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &channel[count]);

			//����
			channel[count]->setVolume(volume);
		}
	}

}

void SoundManager::Stop(string name)
{
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			//�ش� ä�� ����
			channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string name)
{
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			//�ش� ä�� pause
			channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string name)
{
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			//�ش� ä�� pause
			channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::Playing(string key)
{
	bool bPlay = false;
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		//��� ä�� �˻�, �ϳ��� �÷��� ���ΰ� �ִ���
		if (key == iter->first)
		{
			channel[count]->isPlaying(&bPlay);
			break;
		}
	}

	return bPlay;
}

bool SoundManager::Paused(string key)
{
	bool bPause = false;
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		//��� ä�� �˻�, �ϳ��� �÷��� ���ΰ� �ִ���
		if (key == iter->first)
		{
			channel[count]->getPaused(&bPause);
			break;
		}
	}

	return bPause;
}

void SoundManager::Update()
{
	system->update();
}

void SoundManager::Volume(string name, float volume)
{
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			channel[count]->setVolume(volume);
		}
	}
}
