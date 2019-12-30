#include"stdafx.h"
#include"HLDWeapon.h"
#include"HLD/Object/HLDMath.h"

HLDWeapon::HLDWeapon(D3DXVECTOR2 pos, D3DXVECTOR2 size)
:position(pos), scale(size), swordSpeed(600.0f), bCheck(false), bCheckBack(true), angle(0.0f), angleSpeed(10.0f), bCheckUpYaxis(false), bCheckDownYaxis(false), bCheckUpXaxis(false), bCheckDownXaxis(false),bReturnWeapon(false)
{
	wstring textureFile = Textures + L"./HDL/HDLplayerFilter.png";
	wstring shaderFile = Shaders + L"Effect.fx";


	sword = new Sprite(textureFile, shaderFile, 1182, 11436, 1264, 11452);
	math = new HLDMath();
	sword->Position(position);
	sword->Scale(scale);
	sword->DrawBound(true);
	dir = DirectionWeapon::End;
}

HLDWeapon::~HLDWeapon()
{
	SAFE_DELETE(math);
	SAFE_DELETE(sword);
}

void HLDWeapon::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDWeapon::Position(D3DXVECTOR2 val)
{
	position = val;

}

void HLDWeapon::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDWeapon::Scale(D3DXVECTOR2 val)
{
	scale = val;

}

void HLDWeapon::Rotation(float x, float y, float z)
{
	D3DXVECTOR3 input = D3DXVECTOR3(x, y, z);
	Rotation(input);
}

void HLDWeapon::Rotation(D3DXVECTOR3 val)
{
	rotation = val;
}

void HLDWeapon::GetPlayerBool(bool bC)
{
	bCheck = bC;
}

void HLDWeapon::GetCollisionPlayerBool(bool check)
{
	bCheckBack = check;
}

void HLDWeapon::GetDirection(DirectionWeapon d)
{

	dir = d;
	//return Direction();
}

void HLDWeapon::GetPlayerPos(D3DXVECTOR2 pos)
{
	playerPoint = pos;
}




void HLDWeapon::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{

	sword->DrawCollision(bCheckBack);
	if (bCheck&&!bCheckBack) {
		swordSpeed = 600.0f;
		
		 bCheckUpYaxis = false;
		 bCheckDownYaxis = false;
		 bCheckUpXaxis = false;
		 bCheckDownXaxis = false;
		
		if(dir== DirectionWeapon::EndRight|| dir == DirectionWeapon::Right){
		
			position.x = position.x + swordSpeed *Time::Delta();
		}
		if (dir == DirectionWeapon::EndLeft || dir == DirectionWeapon::Left) {
			position.x = position.x - swordSpeed* Time::Delta();
		}
		if (dir == DirectionWeapon::EndDown || dir == DirectionWeapon::Down) {
			position.y = position.y - swordSpeed* Time::Delta();

		}if (dir == DirectionWeapon::EndUp || dir == DirectionWeapon::Up) {
			position.y = position.y + swordSpeed* Time::Delta();
		}
		if (dir == DirectionWeapon::RightDown) {
			position.x = position.x + swordSpeed* Time::Delta();
			position.y = position.y - swordSpeed* Time::Delta();


		}if (dir==DirectionWeapon::RightUp) {
			position.x = position.x + swordSpeed* Time::Delta();
			position.y = position.y + swordSpeed* Time::Delta();

		}if (dir == DirectionWeapon::LeftDown)
		{
			position.x = position.x - swordSpeed* Time::Delta();
			position.y = position.y - swordSpeed* Time::Delta();

		}if (dir == DirectionWeapon::LeftUp) {
			position.x = position.x - swordSpeed* Time::Delta();
			position.y = position.y + swordSpeed* Time::Delta();
		}
		
	
	
	}
	if (!bCheck&&!bCheckBack) {
		if(bReturnWeapon){
		angle = angle + angleSpeed *Time::Delta();
		if (angle > 360) {
			angle = 0.0f;
		}
		rotation = D3DXVECTOR3(0,0,angle);
		position =math->GetAlpa(playerPoint, position, swordSpeed);
		}
		/*
		if (playerPoint.x < position.x) {

			position.x = position.x - swordSpeed * Time::Delta();
			//position.y = math->GetAlpa(playerPoint, position, swordSpeed);
			if(playerPoint.y-position.y<80.0f){
				bCheckDownYaxis = true;
			  
			}
			if(playerPoint.y - position.y >80.0f) {
				bCheckUpYaxis = true;
			
			}
			if (bCheckDownYaxis && !bCheckUpYaxis) {
				position.y = position.y - swordSpeed * Time::Delta(); //
			}
			if (bCheckDownYaxis && bCheckUpYaxis) {
				position.y = position.y + swordSpeed * Time::Delta();//
			}
			//position.y = math->GetAlpa(D3DXVECTOR2(playerPoint.x, 0.0f), D3DXVECTOR2(position.x, position.y), swordSpeed);
		
		}*/

		/*
		if (playerPoint.x > position.x) {
			position.x = position.x + swordSpeed * Time::Delta();

			if (playerPoint.y - position.y < 100.0f) {
				bCheckDownYaxis = true;

			}
			if (playerPoint.y - position.y > 100.0f) {
				bCheckUpYaxis = true;

			}
			if (bCheckDownYaxis && !bCheckUpYaxis) {
				position.y = position.y - swordSpeed * Time::Delta(); //
			}
			if (bCheckDownYaxis && bCheckUpYaxis) {
				position.y = position.y + swordSpeed * Time::Delta();//
			}

		}*/
		/*
		if (playerPoint.y < position.y) {
			position.y = position.y - swordSpeed * Time::Delta();

			if (playerPoint.x - position.x < 100.0f) {
				bCheckDownXaxis = true;

			}
			if (playerPoint.x - position.x > 100.0f) {
				bCheckUpXaxis = true;

			}
			if (bCheckDownXaxis && !bCheckUpXaxis) {
				position.x = position.x - swordSpeed * Time::Delta(); //
			}
			if (bCheckDownXaxis && bCheckUpXaxis) {
				position.x = position.x + swordSpeed * Time::Delta();//
			}


		}
		if (playerPoint.y > position.y) {
			position.y = position.y + swordSpeed * Time::Delta();


			if (playerPoint.x - position.x < 100.0f) {
				bCheckDownXaxis = true;

			}
			if (playerPoint.x - position.x > 100.0f) {
				bCheckUpXaxis = true;

			}
			if (bCheckDownXaxis && !bCheckUpXaxis) {
				position.x = position.x - swordSpeed * Time::Delta(); //
			}
			if (bCheckDownXaxis && bCheckUpXaxis) {
				position.x = position.x + swordSpeed * Time::Delta();//
			}
		}
		*/

		/*
		if(dir == DirectionWeapon::EndRight || dir == DirectionWeapon::Right){
		position.x = position.x - swordSpeed * Time::Delta();
		}
		if (dir == DirectionWeapon::EndLeft || dir == DirectionWeapon::Left) {
			position.x = position.x + swordSpeed * Time::Delta();
		}
		if (dir == DirectionWeapon::EndDown || dir == DirectionWeapon::Down) {
			position.y = position.y + swordSpeed * Time::Delta();
		}if (dir == DirectionWeapon::EndUp || dir == DirectionWeapon::Up) {
			position.y = position.y - swordSpeed * Time::Delta();
		}
		*/
		
	}
	if (bCheckBack) {
		position.x = -50000.0f;
		position.y = -50000.0f;
		swordSpeed = 0.0f;
		angle = 0.0f;
	}


	sword->Position(position);
	sword->Scale(scale);
	sword->Rotation(rotation);
	sword->Update(V, P);
	if (bCheckBack) {
		swordSpeed = 600.0f;
		bCheckBack = false;
		bReturnWeapon = false;
	}
}

void HLDWeapon::Render()
{
	sword->Render();
}

void HLDWeapon::StartMoveWeapon(bool val)
{
	bReturnWeapon = val;
}

Sprite * HLDWeapon::GetSprite()
{
	return sword;
}
