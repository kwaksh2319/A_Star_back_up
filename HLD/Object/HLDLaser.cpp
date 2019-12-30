#include"stdafx.h"
#include"HLDLaser.h"

HLDLaser::HLDLaser(D3DXVECTOR2 pos)
	:position(pos),scale(0.1f,0.1f), bCheckStart(false),bCheckEnd(true),laserScale(3.4f),laserPosDelta(600.0f),laserYDelta(10.0f)
{
	laser = new Animation;
	wstring textureFile = Textures + L"./HDL/GIF/01_f02judegement_filter01.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	Clip*clip;
	{//laser
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 240, 2635, 305, 2695),0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 379, 2622, 485, 2706), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 535, 2605, 720, 2707), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 780, 2593, 955, 2720), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1023, 2578, 1190, 2733), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1238, 2579, 1423, 2733), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1498, 2592, 1698, 2732), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1770, 2600, 2020, 2730), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2134, 2590, 2380, 2720), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2485, 2565, 2780, 2707), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2880, 2547, 3175, 2695), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 3302, 2529, 3624, 2682), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 3302, 2529, 3624, 2682), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 210, 2820, 550, 2965), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 652, 2808, 1023, 2960), 0.5f);
		laser->AddClip(clip);
	}
	{//laser last
		clip = new Clip(PlayMode::LoopStop);
		
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1596, 2765, 1952, 2930), 0.5f);
		laser->AddClip(clip);
	}
	scale = D3DXVECTOR2(0.1f, 1.0f);
	//laser->Play(0);
}

HLDLaser::~HLDLaser()
{
	SAFE_DELETE(laser);
}

void HLDLaser::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);

}

void HLDLaser::Position(D3DXVECTOR2 val)
{
	position = val;

}

void HLDLaser::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDLaser::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDLaser::Rotation(float x, float y, float z)
{
	D3DXVECTOR3 input = D3DXVECTOR3(x, y,z);
	Rotation(input);
}

void HLDLaser::Rotation(D3DXVECTOR3 val)
{
	rotation = val;
}

void HLDLaser::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	
	if(bCheckStart){
		laser->Play(1);
		bCheckEnd=laser->GetClip()->EndFramePattern();
		if(rotation.y==0){
		position.x = position.x +laserPosDelta * Time::Delta();
		
		scale.x = scale.x + laserScale * Time::Delta();
		}
		else if (rotation.y == 179) {
		position.x = position.x -laserPosDelta * Time::Delta();
		
		scale.x = scale.x + laserScale * Time::Delta();
		}
		position.y = position.y + sin(radian*D3DX_PI*2)*laserYDelta * Time::Delta();
	}
	else {
	    laser->Play(0);
		bCheckEnd = true;
	}
	
	
	
	
	laser->Rotation(rotation);
	laser->Scale(scale);
	laser->Position(position);
	laser->Update(V, P);
}

void HLDLaser::Render()
{
	if (bCheckStart) {
		laser->Render();
	}
}

bool HLDLaser::EndLaser()
{
	return bCheckEnd;
}


void HLDLaser::StartLaser(bool val)
{
	bCheckStart = val;
}

void HLDLaser::GetRaindan(float rad)
{
	radian = rad;

}

Sprite * HLDLaser::GetSprite()
{
	return laser->GetSprite();
}
