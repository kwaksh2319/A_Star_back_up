#include"stdafx.h"
#include"HLDRilfMan.h"
#include"HLD/Object/HLDRilfmanBullet.h"


HLDRilfMan::HLDRilfMan(D3DXVECTOR2 pos)
	:bCheckCollision(false), bCheckRangeCollision(false),bulletSpeed(100.0f), bCheckBulletDirection(false),bCheckStop(false), hitCount(0.0f)
{
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	rilfMan = new Animation;
	
	for(int i=0;i<3;i++){
	  bullet.push_back(new HLDRilfmanBullet(D3DXVECTOR2(-5000.0f, -5000.0f), D3DXVECTOR2(1.5f, 1.5f)));
	  bullet[i]->Position(-50000, -50000);
		//bullet.push_back(new HLDRilfmanBullet(D3DXVECTOR2(moveR, rilfMan->Position().y), D3DXVECTOR2(1.5f, 1.5f)));
	}
	//bullet = new HLDRilfmanBullet(D3DXVECTOR2(-5000.0f,-5000.0f), D3DXVECTOR2(1.0f,1.0f));
	scale = D3DXVECTOR2(1.0f, 1.0f);
	Clip*clip;
	{
	
		clip = new Clip(PlayMode::Loop);//idle
		clip->AddFrame(new Sprite(textureFile, shaderFile, 13, 1642, 53, 1694), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 56, 1642, 97, 1694), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 102, 1642, 143, 1694), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 148, 1642, 189, 1694), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 194, 1642, 235, 1694), 0.3f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 13, 1698, 51, 1750), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 57, 1698, 97, 1750), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 103, 1698, 143, 1750), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 149, 1698, 189, 1750), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 195, 1698, 235, 1750), 0.3f);
		rilfMan->AddClip(clip);
	}
	{
		clip = new Clip(PlayMode::Loop);//walk

		clip->AddFrame(new Sprite(textureFile, shaderFile, 13, 1922, 51, 1974), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 57, 1922, 97, 1974), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 102, 1922, 143, 1974), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 149, 1922, 189, 1974), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 195, 1922, 235, 1974), 0.3f);
		rilfMan->AddClip(clip);
	}
	{
		clip = new Clip(PlayMode::Loop);//attack before

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 1754, 95, 1806), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 98, 1754, 143, 1806), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 145, 1754, 189, 1806), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 190, 1754, 235, 1806), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 13, 1809, 50, 1862), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 52, 1812, 95, 1862), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 99, 1811, 141, 1862), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 145, 1811, 187, 1862), 0.3f);

		rilfMan->AddClip(clip);
	}
	{
		clip = new Clip(PlayMode::Loop);//attack after

		clip->AddFrame(new Sprite(textureFile, shaderFile, 191, 1811, 232, 1862), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 13, 1868, 49, 1918), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 51, 1867, 97, 1918), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 99, 1866, 143, 1918), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 145, 1866, 189, 1918), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 192, 1866, 233, 1918), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 195, 1698, 235, 1750), 0.3f);
		rilfMan->AddClip(clip);
	}
	position = pos;
	rilfMan->Scale(scale);
	rilfMan->Position(position);
	rilfMan->Play(1);
	rilfMan->DrawBound(true);
	rilfMan->DrawBoundRange(true);
	rilfMan->DrawBoundStopRange(true);

	rilfMan->Rotation(0, 0, 0);
	
	//rilfManX = position.x;
	//rilfManY = position.y;
//	rilfManX = rilfMan->Position().x;
	//rilfManY = rilfMan->Position().y;
	rilfManX = position.x;
	rilfManY = position.y;

}

HLDRilfMan::~HLDRilfMan()
{
	for(HLDRilfmanBullet *bullets:bullet)
	     SAFE_DELETE(bullets);

	SAFE_DELETE(rilfMan);


}

void HLDRilfMan::Update(D3DXMATRIX V, D3DXMATRIX P)
{
	static int count = 0;
	static float moveR[3]; //= rilfMan->Position().x - rilfMan->GetSprite()->TextureSize().x*0.5f;// - count * 10.0f;
	static float moveL[3]; //= rilfMan->Position().x + rilfMan->GetSprite()->TextureSize().x*0.5f;//+ count * 10.0f;
	static float moveRy[3]; //= rilfMan->Position().y;// -rilfMan->GetSprite()->TextureSize().y*0.5f;

	static float moveLy[3]; //= rilfMan->Position().y;// +rilfMan->GetSprite()->TextureSize().y*0.5f;
	BulletTime();
	
	
	
	
		for (int i = 0; i < 3; i++) {
			bullet[i]->Update(V, P);
		}
	rilfMan->DrawStop(bCheckStop);
	rilfMan->DrawBoundCollision(bCheckCollision);
	rilfMan->DrawBoundRangeCollision(bCheckRangeCollision);
	rilfMan->DrawReds(bCheckCollision);

	if (hitCount > 2 && !bCheckCollision) {
		Reset();
	}

	if (bCheckCollision) {
		hitCount++;//*Time::Delta();
		bCheckCollision = false;
	}



	

	rilfMan->Scale(scale);
	

	rilfMan->Position(position);
	rilfMan->Update(V, P);
	

}

void HLDRilfMan::Render()
{
	rilfMan->Render();
	ImGui::LabelText("HitCount", "%lf", hitCount);
	if(bCheckStop){
	for (HLDRilfmanBullet *bullets : bullet)
		  bullets->Render();
	}
}

void HLDRilfMan::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDRilfMan::Position(D3DXVECTOR2 val)
{
	position = val;
}

void HLDRilfMan::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDRilfMan::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

Sprite * HLDRilfMan::GetSprite()
{
	return rilfMan->GetSprite();
}

void HLDRilfMan::BulletTime()
{
	static D3DXVECTOR2 playPosTmp;
	
	
	if (!bCheckRangeCollision) {
		BFSUpdate();
		rilfMan->Play(1);
		for (int i = 0; i < 3; i++) {
			bullet[i]->Position(-50000, -50000);
		}
		if (bStop) {
			//rilfManX = position.x;
			//rilfManY = position.y;
			bStop = false;
		}
	}
	if (bCheckRangeCollision && !bCheckStop) {
		AstarUpdate();
		rilfMan->Play(1);
		for(int i=0;i<3;i++){
		bullet[i]->Position(position.x, position.y);
		}
		rilfManX = position.x;
		rilfManY = position.y;
		playPosTmp = positionPlayer;
		bStop = true;

	}
	if (bCheckStop) {
		rilfMan->Play(2);
		for (int i = 0; i < 3; i++) {
			bullet[i]->Position(rilfManX, rilfManY);
			if (rilfManX - positionPlayer.x <20 &&rilfManY < positionPlayer.y) {
				rilfManX = rilfManX + bulletSpeed * Time::Delta();
				rilfManY = rilfManY + bulletSpeed * Time::Delta();
				
			}
			if (rilfManX - positionPlayer.x <20 &&rilfManY >= playPosTmp.y) {
				rilfManX = rilfManX + bulletSpeed * Time::Delta();
				rilfManY = rilfManY - bulletSpeed * Time::Delta();
				
			}

			if (rilfManX >= positionPlayer.x&&rilfManY < positionPlayer.y) {
				rilfManX = rilfManX - bulletSpeed * Time::Delta();
				rilfManY = rilfManY + bulletSpeed * Time::Delta();
				
			}
			if (rilfManX >= positionPlayer.x&&rilfManY >= positionPlayer.y) {
				rilfManX = rilfManX - bulletSpeed * Time::Delta();
				rilfManY = rilfManY - bulletSpeed * Time::Delta();
				
			}
			
		}




	}



}

void HLDRilfMan::Reset()
{
	position = D3DXVECTOR2(-50000.0f, -50000.0f);
	for (int i = 0; i < 3; i++) {
		bullet[i]->Position(-50000.0f, -50000.0f);
	}
	bCheckCollision = false;
	bCheckRangeCollision = false;
	bCheckStop = false;
	bulletSpeed = 0.0f;
	hitCount = 0;
}

Sprite* HLDRilfMan::GetBulletSprite(int i)
{
	
	

	return bullet[i]->GetSprite();
}




void HLDRilfMan::BFSUpdate()
{
	float worldTime = Time::Delta();
	static float MoveMonster = 100;
	static int countNum = 1;
	static bool bCheckM = false;
	static bool bCheckS = false;
	static bool bCheckK = false;
	static bool bCheckB = false;
	if (bFSway.size()< countNum) {
		countNum = 1;
	}
	if (bFSway.size() > 0) {
		if (bFSway[bFSway.size() - countNum].x < position.x) {
			rilfMan->Rotation(0,0,0);
			//bCheckBulletDirection = true;
			position.x -= MoveMonster * Time::Delta();
			
			bCheckM = true;
		}
		if (bFSway[bFSway.size() - countNum].x > position.x) {
			rilfMan->Rotation(0, 179, 0);
			//bCheckBulletDirection = false;
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

		if (bCheckM&&bCheckS&&bCheckK&&bCheckB){
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

void HLDRilfMan::AstarUpdate()
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
			rilfMan->Rotation(0, 0, 0);
			
			position.x -= MoveMonster * Time::Delta();
			bCheckM = true;
		}
		if (aStarWay[aStarWay.size() - countNum].x > position.x) {
			rilfMan->Rotation(0, 179, 0);
			
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
