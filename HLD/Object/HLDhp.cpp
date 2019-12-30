#include"stdafx.h"
#include"HLDhp.h"

HLDhp::HLDhp()
{
	wstring textureFile = Textures + L"./HDL/HpBar.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	hp = new Sprite(textureFile, shaderFile, 40, 38, 45, 105);
	hpBar = new Sprite(textureFile, shaderFile, 32, 50, 114, 60);

}

HLDhp::~HLDhp()
{
	SAFE_DELETE(hpBar);
	SAFE_DELETE(hp);
	
}

void HLDhp::HpPosition(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	HpPosition(input);
}

void HLDhp::HpPosition(D3DXVECTOR2 val)
{
	hpPoint = val;

}

void HLDhp::HpBarPosition(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	HpBarPosition(input);
}

void HLDhp::HpBarPosition(D3DXVECTOR2 val)
{
	barPoint = val;
}

void HLDhp::HpScale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	HpScale(input);
}

void HLDhp::HpScale(D3DXVECTOR2 val)
{
	hpScale = val;
}


void HLDhp::HpBarScale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	HpBarScale(input);
}

void HLDhp::HpBarScale(D3DXVECTOR2 val)
{
	barScale = val;
}


void HLDhp::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	hp->Position(hpPoint);
	hp->Scale(hpScale);

	hpBar->Position(barPoint);
	hpBar->Scale(barScale);

	hp->Update(V, P);
	hpBar->Update(V, P);
}

void HLDhp::Render()
{
	hp->Render();
	hpBar->Render();
}
