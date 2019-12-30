#include"stdafx.h"
#include"HLDTile01.h"

HLDTile01::HLDTile01(D3DXVECTOR2 pos)
	:position(pos),bCheckSearch(false)
{
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	tile01 = new Animation;
	{
		Clip*clip;
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile,270, 215, 335, 295),1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 200, 215, 265, 295), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 135, 215, 200, 295), 1.0f);
		
		tile01->AddClip(clip);
		
	}
	{
		Clip*clip;
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 270, 215, 335, 295), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 200, 215, 265, 295), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 135, 215, 200, 295), 1.0f);

		tile01->AddClip(clip);

	}
	//position = pos;
	tile01->Position(pos);
	scale = D3DXVECTOR2(1.0f, 1.0f);
	tile01->Scale(scale);
	//tile01->Position(position);
	tile01->Play(0);
	tile01->DrawBoundStopRange(true);
}

HLDTile01::~HLDTile01()
{
	SAFE_DELETE(tile01);
}

void HLDTile01::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDTile01::Position(D3DXVECTOR2 val)
{
	position = val;
}

void HLDTile01::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDTile01::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDTile01::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{

	if (bCheckSearch) {
		tile01->Play(0);
	}
	else if (!bCheckSearch) {
		tile01->Play(1);
	}
	tile01->Scale(scale);
	tile01->Position(position);
	tile01->Update(V, P);


}

void HLDTile01::Render()
{
	if (bCheckSearch) {
		tile01->Render();
	}
}

void HLDTile01::GetSearchRange(bool val)
{
	bCheckSearch = val;
}

Sprite * HLDTile01::GetSprite()
{
	return tile01->GetSprite();
}
