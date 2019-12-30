#include"stdafx.h"
#include"HLDAlter.h"

HLDAlter::HLDAlter(D3DXVECTOR2 pos)
	:position(pos),scale(0.6f,0.6f)
{
	alter = new Animation;
	wstring textureFile = Textures + L"./HDL/HDLplayerFilter.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	Clip*clip;
	//===================================================================================================
	//alter
	//===================================================================================================

	{//¾Õ  0
		clip = new Clip(PlayMode::Loop);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 875, 1985, 923, 2070), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1472, 1982, 1528, 2073), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2070, 1980, 2130, 2080), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2675, 1988, 2725, 2070), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 275, 2435, 325, 2520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 870, 2435, 928, 2525), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1472, 2430, 1528, 2529), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2075, 2430, 2125, 2520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2675, 2435, 2725, 2520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 272, 2885, 325, 2980), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 870, 2880, 930, 2980), 0.1f);
	
			alter->AddClip(clip);
	

	}
	{//¿Ş ¿À¸¥ 1
		clip = new Clip(PlayMode::Loop);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 268, 3777, 322, 3869), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 865, 3775, 922, 3870), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1460, 3780, 1530, 3865), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2060, 3780, 2129, 3866), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 2665, 3780, 2722, 3865), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 262, 4230, 325, 4318), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 861, 4228, 925, 4318), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1461, 4225, 1525, 4320), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2065, 4225, 2121, 4320), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2630, 4220, 2730, 4320), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 260, 4680, 330, 4765), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 860, 4680, 933, 4765), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1465, 4680, 1525, 4765), 0.1f);
		
			alter->AddClip(clip);
		

	}
	{//µÚ2
		clip = new Clip(PlayMode::Loop);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 2680, 4670, 2720, 4765), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 280, 5120, 320, 5215), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 878, 5122, 922, 5212), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1477, 5125, 1524, 5210), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 2075, 5120, 2125, 5212), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2680, 5120, 2722, 5215), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 277, 5572, 324, 5661), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 872, 5575, 925, 5660), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1480, 5570, 1520, 5663), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2080, 5570, 2120, 5664), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2678, 5570, 2722, 5662), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 278, 6025, 325, 6110), 0.1f);

			alter->AddClip(clip);
		

	}
	
}

HLDAlter::~HLDAlter()
{
	SAFE_DELETE(alter);
}

void HLDAlter::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDAlter::Position(D3DXVECTOR2 val)
{
	position = val;
}

D3DXVECTOR2 HLDAlter::Position()
{
	return position;
}

void HLDAlter::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDAlter::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

D3DXVECTOR2 HLDAlter::Scale()
{
	return scale;
}

void HLDAlter::Rotation(float x, float y, float z)
{
	D3DXVECTOR3 input = D3DXVECTOR3(x,y,z);
	    Rotation(input);
}

void HLDAlter::Rotation(D3DXVECTOR3 val)
{
	rotation = val;
}

D3DXVECTOR3 HLDAlter::Rotation()
{
	return rotation;
}

void HLDAlter::GetPlayNum(int num)
{
	number = num;
}

void HLDAlter::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	alter->DrawViolet(true);
	alter->Rotation(rotation);
	alter->Play(number);
	alter->Position(position);
	alter->Scale(scale);
	alter->Update(V, P);
}

void HLDAlter::Render()
{
	alter->Render();
}
