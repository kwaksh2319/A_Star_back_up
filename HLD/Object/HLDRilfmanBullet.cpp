#include"stdafx.h"
#include"./HLD/Object/HLDRilfmanBullet.h"

HLDRilfmanBullet::HLDRilfmanBullet(D3DXVECTOR2 pos, D3DXVECTOR2 scl)
	:position(pos),scale(scl),bulletSpeed(5.0f),bCheck(false)
{
	bullet = new Animation;
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	
	Clip*clip; 
	{
	clip= new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 695, 1352, 700, 1357),0.3f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 806, 1340, 812, 1345), 0.3f);
	bullet->AddClip(clip);
	}
	bullet->Play(0);
	bullet->Position(position);
	
	bullet->Scale(scale);
}

HLDRilfmanBullet::~HLDRilfmanBullet()
{
	SAFE_DELETE(bullet);
}

void HLDRilfmanBullet::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);

}

void HLDRilfmanBullet::Position(D3DXVECTOR2 val)
{
	position = val;
}

void HLDRilfmanBullet::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDRilfmanBullet::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDRilfmanBullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	bullet->Play(0);
	bullet->Scale(scale);
	//if(bCheck){
	//position.x = position.x + bulletSpeed * Time::Delta();
	//}
	bullet->Position(position);
	bullet->Update(V, P);

}

void HLDRilfmanBullet::Render()
{
	bullet->Render();
}

Sprite * HLDRilfmanBullet::GetSprite()
{
	return bullet->GetSprite();
}
