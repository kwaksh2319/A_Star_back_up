#include"stdafx.h"
#include"HLDCastBullet.h"

HLDCastBullet::HLDCastBullet(D3DXVECTOR2 pos)
	:position(pos),scale(2.0f,2.0f),bCheckStart(false),moveSpeed(100.0f)
{
	wstring textureFile = Textures + L"./HDL/GIF/01_f02judegement_filter01.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	bullet = new Sprite(textureFile, shaderFile, 1595, 2175, 1610, 2189);
	bullet->Position(position);
	bullet->Scale(scale);
}

HLDCastBullet::~HLDCastBullet()
{
	SAFE_DELETE(bullet);
}

void HLDCastBullet::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);

}

void HLDCastBullet::Position(D3DXVECTOR2 val)
{
	position = val;
}

void HLDCastBullet::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDCastBullet::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDCastBullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (bCheckStart) {
		position.x += cos(radian.x*D3DX_PI*2)*moveSpeed*Time::Delta();
		position.y += sin(radian.y*D3DX_PI*2)*moveSpeed * Time::Delta();
		
	}

	bullet->Position(position);
	bullet->Update(V, P);

}

void HLDCastBullet::Render()
{
	bullet->Render();
}

void HLDCastBullet::StartMove(bool val )
{

	bCheckStart = val;
}

void HLDCastBullet::GetRaindan(D3DXVECTOR2 rad)
{
	radian = rad;
}

Sprite * HLDCastBullet::GetSprite()
{
	return bullet;
}
