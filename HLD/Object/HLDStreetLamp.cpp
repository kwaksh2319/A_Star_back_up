#include"stdafx.h"
#include"HLDStreetLamp.h"

HLDStreetLamp::HLDStreetLamp(D3DXVECTOR2 pos)
{
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	streetLamp = new Sprite(textureFile, shaderFile, 780, 250, 799, 319);
	scale = D3DXVECTOR2(1.0f, 1.0f);
	position = pos;
}

HLDStreetLamp::~HLDStreetLamp()
{
	SAFE_DELETE(streetLamp);
}

void HLDStreetLamp::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDStreetLamp::Position(D3DXVECTOR2 val)
{

	position = val;
}

void HLDStreetLamp::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDStreetLamp::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDStreetLamp::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{

	streetLamp->Position(position);
	streetLamp->Scale(scale);
	streetLamp->Update(V, P);
}

void HLDStreetLamp::Render()
{
	streetLamp->Render();
}

Sprite * HLDStreetLamp::GetSprite()
{
	return streetLamp;
}
