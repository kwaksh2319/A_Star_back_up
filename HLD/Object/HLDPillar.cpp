#include "stdafx.h"
#include "HLDPillar.h"

#define MAX_LIMIT_Y 150.0f
#define SPEED 0.5f

HLDPilar::HLDPilar(D3DXVECTOR2 position, D3DXVECTOR2 size)
	:position(position), bClosed(true)
{
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	pilar = new Sprite(textureFile, shaderFile, 0, 0, 130, 240);
	pilarEffect = new Animation;
	Clip* clip;

	//Magma1
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 135, 5, 260, 205), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 265, 5, 395, 205), 1.0f);
		//clip->AddFrame(new Sprite(textureFile, shaderFile, 517, 620, 560, 664), 0.1f);
		//clip->AddFrame(new Sprite(textureFile, shaderFile, 567, 620, 610, 664), 0.1f);
		pilarEffect->AddClip(clip);
	}

	pilarEffect->Position(position);
	pilarEffect->Play(0);

	//tile->DrawBound(true);

}

HLDPilar::~HLDPilar()
{
	SAFE_DELETE(pilar);
	SAFE_DELETE(pilarEffect);
}

void HLDPilar::Update(D3DXMATRIX V, D3DXMATRIX P)
{
	pilar->Position(position);
	pilarEffect->Position(D3DXVECTOR2(position.x, position.y+16));
	pilar->Update(V, P);
	pilarEffect->Update(V, P);
}

void HLDPilar::Render()
{
	pilar->Render();
	pilarEffect->Render();
}

Sprite * HLDPilar::GetSprite()
{
	return pilar;
}

Sprite * HLDPilar::GetSpriteAni()
{
	return pilarEffect->GetSprite();
}
