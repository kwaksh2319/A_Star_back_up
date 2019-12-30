#include"stdafx.h"
#include"HLDCrystal.h"

HLDCrystal::HLDCrystal(D3DXVECTOR2 pos)
{
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	crystal = new Sprite(textureFile,shaderFile, 925, 0, 1005, 105);
	scale = D3DXVECTOR2(1.0f, 1.0f);
	position = pos;

}

HLDCrystal::~HLDCrystal()
{
	SAFE_DELETE(crystal);
}

void HLDCrystal::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDCrystal::Position(D3DXVECTOR2 val)
{

	position = val;
}

void HLDCrystal::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDCrystal::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDCrystal::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	crystal->Position(position);
	crystal->Scale(scale);
	crystal->Update(V, P);
}

void HLDCrystal::Render()
{
	crystal->Render();
}

Sprite * HLDCrystal::GetSprite()
{
	return crystal;
}
