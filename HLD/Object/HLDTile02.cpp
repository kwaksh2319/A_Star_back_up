#include"stdafx.h"
#include"HLDTile02.h"

HLDTile02::HLDTile02(D3DXVECTOR2 pos)
	:position(pos)
{
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	tile01 = new Animation;
	{
		Clip*clip;
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 715, 250, 780, 330), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 645, 250, 710, 330), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 580, 250, 645, 330), 1.0f);

		tile01->AddClip(clip);

	}
	//position = pos;
	tile01->Position(pos);
	scale = D3DXVECTOR2(1.0f, 1.0f);
	tile01->Scale(scale);
	//tile01->Position(position);
	tile01->Play(0);

}

HLDTile02::~HLDTile02()
{
	SAFE_DELETE(tile01);
}

void HLDTile02::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDTile02::Position(D3DXVECTOR2 val)
{
	position = val;
}

void HLDTile02::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDTile02::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDTile02::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	tile01->Scale(scale);
	tile01->Position(position);
	tile01->Update(V, P);
}

void HLDTile02::Render()
{
	tile01->Render();
}

Sprite * HLDTile02::GetSpirte()
{
	return tile01->GetSprite();
}
