#include"stdafx.h"
#include"HLDEffect.h"

HLDEffect::HLDEffect(D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:position(pos),scale(size), rotation(0.0f,0.0f,0.0f)
{

	wstring textureFile = Textures + L"./HDL/HDLplayerFilter.png";
	wstring shaderFile = Shaders + L"Effect.fx";  
	effect = new Animation;
	Clip*clip;
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2665, 11360, 2840, 11535), 0.13f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2410, 11365, 2585, 11515), 0.13f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2245, 11365, 2265, 11380), 0.13f);
		//clip->AddFrame(new Sprite(textureFile, shaderFile, 1465, 10985, 1536, 11078), 0.1f);

		effect->AddClip(clip);
	}
	effect->Position(position);
	effect->Scale(scale);
	effect->DrawBound(true);

	effect->Play(0);



}

HLDEffect::~HLDEffect()
{
	SAFE_DELETE(effect);
}

void HLDEffect::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDEffect::Position(D3DXVECTOR2 val)
{
	position = val;

}

void HLDEffect::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDEffect::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDEffect::Rotation(float x, float y, float z)
{
	D3DXVECTOR3 input = D3DXVECTOR3(x, y, z);

	Rotation(input);

}

void HLDEffect::Rotation(D3DXVECTOR3 rota)
{
	rotation=rota;
}





void HLDEffect::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	effect->Position(position);
	effect->Scale(scale);
	effect->Rotation(rotation);
	effect->Update(V, P);
}

void HLDEffect::Render()
{
	effect->Render();

}

Sprite * HLDEffect::GetSprite()
{
	return effect->GetSprite();
}
