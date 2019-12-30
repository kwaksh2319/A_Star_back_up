#include"stdafx.h"
#include"HLDBrute.h"



HLDBrute::HLDBrute(D3DXVECTOR2 pos)
	:bColCheck(false), bRangeCheck(false)
{
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	brute = new Animation;
	Clip*clip;
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile,shaderFile, 331, 1801, 413, 1907),0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 425, 1805, 511, 1907), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 512, 1809, 614, 1907), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 620, 1806, 708, 1907), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 716, 1804, 802, 1907), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 336, 1925, 414, 2025), 0.3f);
		brute->AddClip(clip);
	}
	position = pos;
	scale = D3DXVECTOR2(1.0f, 1.0f);
	brute->Position(position);
	brute->Scale(scale);
	brute->Play(0);
	brute->DrawBound(true);
	brute->DrawBoundRange(true);

}

HLDBrute::~HLDBrute()
{
	SAFE_DELETE(brute);
}

void HLDBrute::Update(D3DXMATRIX V, D3DXMATRIX P)
{
	
	if(bRangeCheck==false)
	     BFSUpdate();

	if(bRangeCheck==true)
	   AstarUpdate();
	
	brute->DrawReds(bColCheck);
	brute->DrawBoundCollision(bColCheck);
	brute->DrawBoundRangeCollision(bRangeCheck);

	if (!bColCheck&&hitCount>2.0f) {

		Reset();
	}
	if (bColCheck) {
		hitCount++;
		bColCheck = false;
	}
	
	brute->Scale(scale);
	brute->Position(position);
	brute->Update(V, P);
}

void HLDBrute::Render()
{
	brute->Render();
}

void HLDBrute::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDBrute::Position(D3DXVECTOR2 val)
{
	position = val;
}

void HLDBrute::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDBrute::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

Sprite * HLDBrute::GetSprite()
{
	return brute->GetSprite();
}
void HLDBrute::BFSUpdate()
{
	float worldTime = Time::Delta();
	static float MoveMonster = 100;
	static int countNum = 1;
	static bool bCheckM = false;
	static bool bCheckS = false;
	static bool bCheckK = false;
	static bool bCheckB = false;
	if (bFSway.size() < countNum) {
		countNum = 1;
	}
	if (bFSway.size() > 0) {
		if (bFSway[bFSway.size() - countNum].x < position.x) {
			brute->Rotation(0, 179, 0);
			position.x -= MoveMonster * Time::Delta();
			bCheckM = true;
		}
		if (bFSway[bFSway.size() - countNum].x > position.x) {
			brute->Rotation(0, 0, 0);
			position.x += MoveMonster * Time::Delta();
			bCheckS = true;
		}

		if (bFSway[bFSway.size() - countNum].y < position.y) {

			position.y -= MoveMonster * Time::Delta();
			bCheckK = true;
		}
		if (bFSway[bFSway.size() - countNum].y > position.y) {

			position.y += MoveMonster * Time::Delta();
			bCheckB = true;
		}

		if (bCheckM&&bCheckS&&bCheckK&& bCheckB) {
			if (countNum < bFSway.size()) {
				countNum++;
			}

			bCheckM = false;
			bCheckS = false;
			bCheckK = false;
			bCheckB = false;

		}

	}
}

void HLDBrute::AstarUpdate()
{

	float worldTime = Time::Delta();
	static float MoveMonster = 100;
	static int countNum = 1;
	static bool bCheckM = false;
	static bool bCheckS = false;
	static bool bCheckK = false;
	static bool bCheckB = false;
	if (aStarWay.size() < countNum) {
		countNum = 1;
	}
	if (aStarWay.size() > 0) {
		if (aStarWay[aStarWay.size() - countNum].x < position.x) {
			brute->Rotation(0, 179, 0);
			position.x -= MoveMonster * Time::Delta();
			bCheckM = true;
		}
		if (aStarWay[aStarWay.size() - countNum].x > position.x) {
			brute->Rotation(0, 0, 0);
			position.x += MoveMonster * Time::Delta();
			bCheckS = true;
		}

		if (aStarWay[aStarWay.size() - countNum].y < position.y) {

			position.y -= MoveMonster * Time::Delta();
			bCheckK = true;
		}
		if (aStarWay[aStarWay.size() - countNum].y > position.y) {

			position.y += MoveMonster * Time::Delta();
			bCheckB = true;
		}

		if (bCheckM&&bCheckS&&bCheckK&& bCheckB) {
			if (countNum < aStarWay.size()) {
				countNum++;
			}

			bCheckM = false;
			bCheckS = false;
			bCheckK = false;
			bCheckB = false;

		}

	}
}

void HLDBrute::Reset()
{
	position = D3DXVECTOR2(-50000.0f, -50000.0f);
	bColCheck = false;
	bRangeCheck = false;
	hitCount = 0.0f;

	//bCheckStop = false;
	//bulletSpeed = 0.0f;

}
