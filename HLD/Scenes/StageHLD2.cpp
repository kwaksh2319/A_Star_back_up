#include"stdafx.h"
#include"./HLD/Scenes/StageHLD2.h"
#include "./Viewer/Following.h"
#include"./HLD/Object/HLDPlayer.h"
#include"./Viewer/FreeCamera.h"
#include"./HLD/Object/HLDBoss.h"

StageHLD2::StageHLD2(SceneValues * values)
	:Scene(values), bCheckState(false)
{

	wstring textureFile = Textures + L"./HDL/HDL_Background_Titan_Parallax.png";
	//HDL_Background_Titan_Parallax
	//HDLbackground_Green
	wstring shaderFile = Shaders + L"./Effect.fx";
	
	background = new Sprite(textureFile, shaderFile);
	
	player = new HLDPlayer(D3DXVECTOR2(0.0f, -200));//-10, -150
	boss = new HLDBoss(D3DXVECTOR2(100.0f, 0.0f));
   //values->MainCamera = new FreeCamera;
	values->MainCamera = new Following(player);
	//background->Scale(2.0f, 2.0f);
	background->DrawBound(true);
}

StageHLD2::~StageHLD2()
{
	
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(boss);
	SAFE_DELETE(player);
	SAFE_DELETE(background);
}

void StageHLD2::Update()
{
	if (bCheckState) {
	
	//values->MainCamera = new Following(player);
	//bCheckState = false;
	
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	
	
	SetBackgroundPoint();
	player->GetStageBool(bCheckState);
	//player->GetBackgroundData(background->TextureSize(),background->Position());

	player->GetBackgroundData(background->TextureSize(), background->Position());
	player->GetBackgroundCollision(Sprite::AabbBackgroundRange(background, player->GetSprite()));
	player->GetCollision(Sprite::Aabb(player->GetSprite(),boss->GetSprite()));
	//boss->GetHpBarPoint(player->cameraPosHp());
	boss->GetCollisionSword(Sprite::Aabb(boss->GetSprite(),player->GetSword()));
	boss->GetCollisionSlash(Sprite::Aabb(boss->GetSprite(), player->GetSlash()));
	boss->GetPlayerPoint(player->Position());
	boss->GetBackgroundPoint(getBackgroundPoint);
	
	//boss->GetSprite();
	boss->GetBackGroundCollision(Sprite::AabbBackgroundRange(background, boss->GetSprite()));
	
	background->Scale(1.5f, 1.5f);
	background->Update(V, P);
	boss->Update(V, P);
	player->Update(V, P);
	
	}
}

void StageHLD2::Render()
{
	background->Render();
	boss->Render();
	player->Render();
	ImGui::LabelText("cameraPos", "%f,%f",values->MainCamera->Position().x, values->MainCamera->Position().y);

}

void StageHLD2::SetBackgroundPoint()
{
	getBackgroundPoint[0].x = background->Position().x + background->TextureSize().x / 2;
	getBackgroundPoint[0].y = background->Position().y + background->TextureSize().y / 2; //1 phase

	getBackgroundPoint[1].x = background->Position().x - background->TextureSize().x / 2;
	getBackgroundPoint[1].y = background->Position().y + background->TextureSize().y / 2; //2 phase

	getBackgroundPoint[2].x = background->Position().x - background->TextureSize().x / 2;
	getBackgroundPoint[2].y = background->Position().y - background->TextureSize().y / 2; //3 phase

	getBackgroundPoint[3].x = background->Position().x + background->TextureSize().x / 2;
	getBackgroundPoint[3].y = background->Position().y - background->TextureSize().y / 2; //4 phase
}
