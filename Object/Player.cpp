#include"stdafx.h"
#include"Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f) ,focusOffset(180,140)//ī�޶� ��ǥ

{
	animation = new Animation;
	wstring spriteFile = Textures + L"metalslug.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	Clip* clip;
	//Idle:clip[0]
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 2, 34, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 2, 64, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 64, 2, 94, 40), 0.3f);
		animation->AddClip(clip);
	}
	//run clip[1]
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 600, 64, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 65, 600, 96, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 97, 600, 124, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 125, 600, 154, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 158, 600, 188, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 191, 600, 222, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 224, 599, 258, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 259, 600, 294, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 295, 600, 326, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 329, 600, 360, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 362, 600, 393, 640), 0.1f);
		animation->AddClip(clip);


	}
	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	animation->DrawBound(true);//box

}

Player::~Player()
{
	SAFE_DELETE(animation);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{

	//�̵�
	D3DXVECTOR2 position = animation->Position();
	D3DXVECTOR3 rotation = animation->RotationDegree();

	if (Key->Press('A')) {
		
		position.x -= moveSpeed * Time::Delta();
		animation->Position(position);
		rotation.y -= 20.0f*Time::Delta();
		//animation->RotationDegree(rotation); 
		//animation->Rotation(0.0f, 1.0f*Math::PI, 0.0f);
		animation->RotationDegree(0,180,0);
		animation->Play(1);

	}
	else if (Key->Press('D')) {
		
		position.x += moveSpeed * Time::Delta();
		animation->Position(position);
		rotation.y += 20.0f*Time::Delta();
		//animation->RotationDegree(rotation);
		//animation->Rotation(0.0f,0.0f*Math::PI, 0.0f);
		animation->RotationDegree(0, 0 ,0);
		animation->Play(1);
	
	}
	else {
		animation->Play(0);
	}
	
	animation->Update(V, P);
}

void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);
	animation->Render();
}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{

	*position = animation->Position() + focusOffset;

	D3DXVECTOR2 textureSize = animation->TextureSize();
	D3DXVECTOR2 scale = animation->Scale();

	//(*size).x = textureSize.x*scale.x;

	//(*size).y = textureSize.y*scale.y;

	(*size) = D3DXVECTOR2(1, 1);

}

Sprite * Player::GetSprite()
{
	return animation->GetSprite();
}
