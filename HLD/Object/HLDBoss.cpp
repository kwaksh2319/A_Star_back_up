#include"stdafx.h"
#include"./HLD/Object/HLDBoss.h"
#include"./HLD/Object/HLDCastBullet.h"
#include"./HLD/Object/HLDLaser.h"
#include"./HLD/Object/HLDhp.h"

HLDBoss::HLDBoss(D3DXVECTOR2 pos)
	:position(pos), scale(1.0f, 1.0f), bColliCount(0), bCollision(false), moveSpeed(500.0f), reflectSpeed(15.0f), tmpPlayerDir(0.0f, 0.0f), tmpNowPos(0.0f, 0.0f), comDegreeLeft(-1.39626f), comDegreeRight(1.74533f), comDegree(0.0f), bCheckMove(false), readySpeedx(50.0f), readySpeedy(50.0f), bCheckBullet(false), bulletRad(1.0f,0.0f),tmpDeltaX(-0.1f),  tmpDeltaY(0.1f),castCount(0), bCheckCastShot(false), bulletTime(0),castCount2(0),bCheckBullet2(false), laserRad(0.0f), laserRadDelta(5.0f), bCheckCollisionSlash(false), bCheckCollisionSword(false)

{

	wstring textureFile = Textures + L"./HDL/GIF/01_f02judegement_filter01.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	boss = new Animation;
	hp = new HLDhp;
	for(int i=0;i<100;i++){
	bullet.push_back(new HLDCastBullet(D3DXVECTOR2(-50000.0f,-50000.0f)));
	}

	for (int i = 0; i < 100; i++) {
		bullet2.push_back(new HLDCastBullet(D3DXVECTOR2(-50000.0f, -50000.0f)));
	}
	laser = new HLDLaser(D3DXVECTOR2(-50000.0f, -50000.0f));
	Clip*clip;
	{
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 180, 1145, 325, 1378),0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 325, 1145, 466, 1372), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 465, 1145, 608, 1370), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 608, 1145, 749, 1372), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 180, 1385, 325, 1605), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 325, 1385, 465, 1611), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 466, 1385, 607, 1610), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 607, 1385, 750, 1615), 0.3f);


		boss->AddClip(clip);
	}
	{
		clip = new Clip(PlayMode::LoopStop);
		//appear
	clip->AddFrame(new Sprite(textureFile, shaderFile, 220, 223, 230, 250), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 273, 225, 285, 250), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 340, 230, 350, 251), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 390, 235, 405, 255), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 457, 232, 474, 252), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 518, 240, 540, 272), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 590, 228, 611, 265), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 647, 230, 670, 267), 0.1f);


	clip->AddFrame(new Sprite(textureFile, shaderFile, 702, 235, 725, 305), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 766, 240, 793, 305), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 225, 305, 252, 375), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 303, 303, 330, 380), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 380, 300, 380, 405), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 449, 310, 493, 405), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 550, 320, 600, 413), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 645, 303, 695, 413), 0.1f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 905, 315, 960, 425), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 995, 315, 1050, 425), 0.1f);







	//down attack
	clip->AddFrame(new Sprite(textureFile, shaderFile, 220, 408, 300, 560), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 320, 407, 406, 560), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 455, 425, 532, 577), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 575, 440, 650, 590), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 689, 443, 762, 590), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 820, 460, 915, 583), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 964, 462, 1055, 592), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 217, 607, 310, 730), 0.1f);


	clip->AddFrame(new Sprite(textureFile, shaderFile, 345, 610, 435, 735), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 470, 608, 560, 733), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 590, 607, 680, 730), 0.2f);
	
	clip->AddFrame(new Sprite(textureFile, shaderFile, 724, 610, 815, 735), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 868, 607, 960, 730), 0.2f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 370, 765, 485,894), 0.2f);
	
	clip->AddFrame(new Sprite(textureFile, shaderFile, 520, 760, 635, 890), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 706, 765, 826, 893), 0.2f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 877, 752, 998, 904), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1092, 755, 1208, 910), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 200, 935, 323, 1070), 0.2f);

	
	boss->AddClip(clip);

	}

	{//ReadyCollision
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 225, 1720, 340, 1830), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 225, 1720, 340, 1830), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 225, 1720, 340, 1830), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 225, 1720, 340, 1830), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 401, 1715, 525, 1830), 0.2f);
		boss->AddClip(clip);
	}
	{//OnCollision
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 623, 1706, 710, 1836), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 623, 1706, 710, 1836), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 623, 1706, 710, 1836), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 795, 1725, 878, 1840), 0.1f);
		
		boss->AddClip(clip);
	}



	{//offCollision
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1035, 1755, 1200, 1890), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1317, 1750, 1465, 1843), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1525, 1750, 1697, 1856), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1780, 1740, 1955, 1887), 0.1f);


		clip->AddFrame(new Sprite(textureFile, shaderFile, 2035, 1745, 2215, 1890), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2293, 1750, 2485, 1895), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2570, 1750, 2755, 1885), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2857, 1755, 3027, 1875), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 3095, 1765, 3250, 1880), 0.1f);

		boss->AddClip(clip);
	}
	{//endCollision
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 237, 1860, 345, 1972), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 415, 1885, 555, 2020), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 635, 1885, 745, 2025), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 793, 1900, 866, 2030), 0.3f);



		boss->AddClip(clip);
	}
	{//CastShot
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 780, 2135, 883, 2283), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 944, 2106, 1115, 2310), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1200, 2110, 1370, 2310), 1.0f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1462, 2165, 1560, 2310), 1.0f);



		boss->AddClip(clip);
	}
	{//Laser
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 220, 2372, 310, 2515), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 360, 2370, 480, 2527), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 540, 2370, 655, 2527), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 745, 2370, 855, 2580), 0.1f);


		clip->AddFrame(new Sprite(textureFile, shaderFile, 965, 2389, 1065, 2580), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1215, 2408, 1350, 2517), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1460, 2413, 1600, 2523), 0.3f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1680, 2414, 1858, 2530), 0.3f);
	//	clip->AddFrame(new Sprite(textureFile, shaderFile, 2022, 2420, 2142, 2517), 0.1f);

		
		boss->AddClip(clip);
	}
	{
		clip = new Clip(PlayMode::LoopStop);


		clip->AddFrame(new Sprite(textureFile, shaderFile, 995, 315, 1050, 425), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 905, 315, 960, 425), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 645, 303, 695, 413), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 550, 320, 600, 413), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 449, 310, 493, 405), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 380, 300, 380, 405), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 303, 303, 330, 380), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 225, 305, 252, 375), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 766, 240, 793, 305), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 702, 235, 725, 305), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 647, 230, 670, 267), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 590, 228, 611, 265), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 518, 240, 540, 272), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 457, 232, 474, 252), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 390, 235, 405, 255), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 340, 230, 350, 251), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 273, 225, 285, 250), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 220, 223, 230, 250), 0.1f);



	
		

		boss->AddClip(clip);
	}
	//boss->Play((UINT)State::Laser);
	state = State::Appear;
	boss->DrawBound(true);
	boss->Position(position);
	boss->Scale(scale);
	boss->Play((UINT)state);
	

}

HLDBoss::~HLDBoss()
{
	SAFE_DELETE(hp);
	SAFE_DELETE(laser);

	for (HLDCastBullet*bullets : bullet)
		    SAFE_DELETE(bullets);


	for (HLDCastBullet*bullets2 : bullet2)
		SAFE_DELETE(bullets2);

	SAFE_DELETE(boss);
}

void HLDBoss::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDBoss::Position(D3DXVECTOR2 val)
{
	position = val;
}

void HLDBoss::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDBoss::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDBoss::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	hp->HpBarPosition(hpBarPoint);
	hp->HpBarScale(10.0f, 10.0f);
	hp->Update(V, P);
	bulletTime += Time::Delta();
	
	Pattern();
	

	boss->DrawBoundCollision((bCheckCollisionSlash||bCheckCollisionSword));
	boss->DrawReds((bCheckCollisionSlash || bCheckCollisionSword));
	boss->Position(position);
	boss->Scale(scale);

	laser->Update(V, P);

	for (HLDCastBullet*bullets : bullet)
		bullets->Update(V, P);
	for (HLDCastBullet*bullets2 : bullet2)
		bullets2->Update(V, P);
	boss->Update(V, P);
	
}

void HLDBoss::Render()
{
	hp->Render();
	boss->Render();
	for (HLDCastBullet*bullets : bullet)
		bullets->Render();

	for (HLDCastBullet*bullets2 : bullet2)
		bullets2->Render();

	laser->Render();

	ImGui::LabelText("castCount", "%d", castCount);
	ImGui::LabelText("castCount2", "%d", castCount2);
	ImGui::LabelText(" bulletTime", "%lf", bulletTime);


}

void HLDBoss::GetPlayerPoint(D3DXVECTOR2 val)
{
	playerPoint = val;
}

void HLDBoss::GetBackgroundPoint(D3DXVECTOR2 val[])
{
	backgroundPoints[0] = val[0]; //1phase
	backgroundPoints[1] = val[1];//2phase
	backgroundPoints[2] = val[2];//3phase
	backgroundPoints[3] = val[3];//4phase

}

void HLDBoss::GetBackGroundCollision(bool val)
{

	bCollision = val;
}





void HLDBoss::CheckRangeMove()
{
	float tmpRange;
	float min = 999999999;
	int memoryNum=-1;
	for (int i = 0; i < 4; i++) {
		tmpRange = sqrt(pow(position.x - backgroundPoints[i].x, 2) + pow(position.y - backgroundPoints[i].y, 2));
		if (tmpRange < min) {
			memoryNum = i;
			min = tmpRange;
		}
	}
	if (position.x- backgroundPoints[memoryNum].x < 200) {

		position.x = position.x + readySpeedx * Time::Delta();
	}
	if (position.x - backgroundPoints[memoryNum].x>= 200 ) {
		position.x = position.x - readySpeedx * Time::Delta();
	}
	if (position.y- backgroundPoints[memoryNum].y <100 ) {
		position.y = position.y + readySpeedy * Time::Delta();
	}
	if (position.y - backgroundPoints[memoryNum].y >=100 ) {
		position.y = position.y - readySpeedy * Time::Delta();
	}

	if (memoryNum==0|| memoryNum == 4) {
		boss->Rotation(0, 0, 0);
	}
	else if (memoryNum == 2 || memoryNum == 3) {
		boss->Rotation(0, 179, 0);
	}

	if (abs(position.x - backgroundPoints[memoryNum].x) <= 200) {
		readySpeedx = 0.0f;
	}
	if (abs(position.y - backgroundPoints[memoryNum].y) <= 100) {
		readySpeedy = 0.0f;
	}
	if (abs(position.x- backgroundPoints[memoryNum].x)<=200&& abs(position.y - backgroundPoints[memoryNum].y) <=100) {
		
		bCheckMove = true;
	}
	


}

void HLDBoss::GetCollisionSword(bool val)
{
	bCheckCollisionSword = val;
}

void HLDBoss::GetCollisionSlash(bool val)
{
	bCheckCollisionSlash = val;
}

void HLDBoss::GetHpBarPoint(D3DXVECTOR2 val)
{
	hpBarPoint= val;
}


Sprite * HLDBoss::GetSprite()
{
	return boss->GetSprite();
}

void HLDBoss::Pattern()
{
	
	
	switch (state)
	{
	case State::Idle:
		if (playerPoint.x>=position.x) {
			boss->Rotation(0, 0, 0);
		}
		else if (playerPoint.x < position.x) {
			boss->Rotation(0, 179, 0);
		}
		boss->Play((UINT)State::Idle);
		scale = D3DXVECTOR2(1.0f, 1.0f);
		if (!boss->GetClip()->EndFramePattern()) {

			state = State::ReadyCollision;
		}
		break;
	case State::Appear:
		boss->Play((UINT)State::Appear);
		scale = D3DXVECTOR2(1.5f, 1.5f);
		
		if (!boss->GetClip()->EndFramePattern()) {
			//state = State::Appear;
			state = State::Idle;
		}
		break;
	case State::ReadyCollision:
		boss->Play((UINT)State::ReadyCollision);
		if (playerPoint.x >= position.x) {
			boss->Rotation(0, 0, 0);
		}
		else if (playerPoint.x < position.x) {
			boss->Rotation(0, 179, 0);
		}
		scale = D3DXVECTOR2(1.5f, 1.5f);
		//tmpPlayerPoint = playerPoint;
		tmpNowPos= playerPoint- position;
		D3DXVec2Normalize(&tmpPlayerDir, &tmpNowPos); //direction get 
		if (playerPoint.x < position.x) {
			comDegree = atan(tmpNowPos.y / tmpNowPos.x) + comDegreeLeft;
		}
		else if (playerPoint.x >= position.x) {
			comDegree =atan(tmpNowPos.y / tmpNowPos.x) + comDegreeRight;
		}
		if (!boss->GetClip()->EndFramePattern()) {
			state = State::OnCollision;
			bColliCount++;
		}

		break;
	case State::OnCollision:
		boss->Play((UINT)State::OnCollision);
		scale = D3DXVECTOR2(1.5f, 1.5f);
		position.x= position.x+tmpPlayerDir.x* moveSpeed * Time::Delta();
		position.y = position.y + tmpPlayerDir.y * moveSpeed * Time::Delta();
		
		boss->Rotation(0, 0, comDegree);
		


		if (!boss->GetClip()->EndFramePattern()&& bCollision) {
             

			
			state = State::OffCollsion;
		
		}
		break;
	case State::OffCollsion:
		boss->Play((UINT)State::OffCollsion);
		scale = D3DXVECTOR2(1.5f, 1.5f);

		
		position.x = position.x - tmpPlayerDir.x* reflectSpeed* Time::Delta();
		position.y = position.y - tmpPlayerDir.y * reflectSpeed * Time::Delta();

		
		if (!boss->GetClip()->EndFramePattern() && bColliCount > 3) {
			
			state = State::EndCollision;
			bColliCount = 0;
			readySpeedx = 50.0f;
			readySpeedy = 50.0f;
		}
		else if (!boss->GetClip()->EndFramePattern() && bColliCount <= 3) {
			D3DXVec2Normalize(&tmpPlayerDir, &playerPoint); //direction get 
			state = State::ReadyCollision;
		}
		break;
	case State::EndCollision:
		boss->Play((UINT)State::EndCollision);
		boss->RotationDegree(0, 0, 0);
		scale = D3DXVECTOR2(1.5f, 1.5f);

		CheckRangeMove();


		
		if (!boss->GetClip()->EndFramePattern()&& bCheckMove) {
			bCheckMove = false;
			
			Cast();
			castCount = 0;
			bCheckBullet = false;
			castCount2 = 0;
			bCheckBullet2 = false;
			bulletTime = 0.0f;
			state = State::CastShot;
		}
		break;
	case State::CastShot:
		
		boss->Play((UINT)State::CastShot);
		
		//for (HLDCastBullet *bullets:bullet) {
			//bullets->StartMove(true);
		//}
		// *(int)Time::Delta();//castCount + 1 * Time::Delta();
		if(castCount<100){
			
		bullet[castCount]->StartMove(true);
		castCount += 1; //(int)bulletTime;
		
	    
		}
		if(bulletTime>2){
		if (castCount >= 100) {
			bCheckBullet = true;
		}


		if (castCount2 < 100) {

			bullet2[castCount2]->StartMove(true);
			castCount2 += 1;


		}if (castCount2 >= 100) {
			bCheckBullet2 = true;
		}
		}


		scale = D3DXVECTOR2(1.5f, 1.5f);




		if (playerPoint.x >= position.x) {
			boss->Rotation(0, 179, 0);
		}
		else if (playerPoint.x < position.x) {
			boss->Rotation(0, 0, 0);

		}//if (!boss->GetClip()->EndFrame()) {
			//state = State::CastShot;
		//}
		if (!boss->GetClip()->EndFrame()&& bCheckBullet&&bCheckBullet2) {
			laserRad = 0.0f;

			laser->Position(position);
			state = State::Laser;

			if (playerPoint.x >= position.x) {
				boss->Rotation(0, 179, 0);
				laser->Rotation(0, 0, 0);

			}
			if (playerPoint.x < position.x) {
				boss->Rotation(0, 0, 0);
				laser->Rotation(0, 179, 0);
			}
			
		}
		

		break;

	
	case State::Laser:
		boss->Play((UINT)State::Laser);
		scale = D3DXVECTOR2(1.5f, 1.5f);
		if(!boss->GetClip()->EndFramePattern()){
		     LaserDir();
		}
		if (!boss->GetClip()->EndFramePattern()&&!laser->EndLaser()) {
			state = State::Disappear;
			
			laser->Position(-50000.0f, -50000.0f);
			laser->Scale(0.1f, 1.0f);
			laser->StartLaser(false);
		}

		
		break;
	case State::Disappear:

		boss->Play((UINT)State::Disappear);

		if (!boss->GetClip()->EndFramePattern()) {
			state = State::Appear;
			position.x = playerPoint.x;
			position.y = playerPoint.y + 80;
			
		}
		
		break;
	default:
		break;
	}

	
}

void HLDBoss::Cast()
{
	
	
	
	for (HLDCastBullet*bullets : bullet){
		
		if (bulletRad.x >= 1.0) {
			tmpDeltaX = -0.01;
		}if (bulletRad.x <= -1.0) {
			tmpDeltaX = 0.01;
	    }
		if (bulletRad.y >= 1.0) {
			tmpDeltaY = -0.01;
		}if (bulletRad.y <= -1.0) {
			tmpDeltaY = 0.01;
		}
		bulletRad.x = bulletRad.x + tmpDeltaX;
		bulletRad.y = bulletRad.y + tmpDeltaY;
		
		bullets->Position(position.x, position.y+40);
		
		bullets->StartMove(false);
		
		bullets->GetRaindan(bulletRad);
		
	}



	for (HLDCastBullet*bullets2 : bullet2) {

		if (bulletRad.x >= 1.0) {
			tmpDeltaX = -0.01;
		}if (bulletRad.x <= -1.0) {
			tmpDeltaX = 0.01;
		}
		if (bulletRad.y >= 1.0) {
			tmpDeltaY = -0.01;
		}if (bulletRad.y <= -1.0) {
			tmpDeltaY = 0.01;
		}
		bulletRad.x = bulletRad.x + tmpDeltaX;
		bulletRad.y = bulletRad.y + tmpDeltaY;
		bullets2->StartMove(false);
		bullets2->Position(position.x, position.y + 40);



		bullets2->GetRaindan(bulletRad);

	}

}

void HLDBoss::LaserDir()
{

	if (laserRad>=1.0) {
		laserRadDelta = -0.01;
	}
	if (laserRad <= 0.0) {
		laserRadDelta = 0.01;
	}


	laserRad = laserRad + laserRadDelta*Time::Delta();
	laser->GetRaindan(laserRad);
	
	laser->StartLaser(true);
	
}
