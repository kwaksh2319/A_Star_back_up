#include"stdafx.h"
#include"HLDPlayer.h"
#include"HLD/Object/HLDEffect.h"
#include"HLD/Object/HLDWeapon.h"
#include"HLD/Object/HLDAlter.h"

HLDPlayer::HLDPlayer(D3DXVECTOR2 pos)
	:position(pos),scale(0.6f,0.6f), focusOffset(-410, -400),moveSpeed(100.0f),bCheck(false),swordSpeed(100.0f),bSwordCheck(false),angleSwordSpeed(1.0f),shootWeapon(false),bCheckBackground(false), moveMinSpeed(400.0f), bCheckWall(false), bCheckStage01(false), bCheckBrute(false), bCheckDash(false) 
{//-410, -400
	rt = 0.0f;

	wstring textureFile = Textures + L"./HDL/HDLplayerFilter.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	
	player = new Animation; 
	interval[0] = 10.0f;
	interval[1] = 20.0f;
	interval[2] = 30.0f;
	
	slash = new HLDEffect(D3DXVECTOR2(-5000.0f, -5000.0f), D3DXVECTOR2(0.6f,0.6f));
	sword=new HLDWeapon(D3DXVECTOR2(-5000.0f, -5000.0f), D3DXVECTOR2(0.6f, 0.6f));
	for (int i = 0; i < 3; i++) {
		alter.push_back(new HLDAlter(D3DXVECTOR2(-50000.0f, -50000.0f)));
	}
	Clip*clip;
	//===================================================================================================
	//player
	//===================================================================================================
	{//앞  0
		clip = new Clip(PlayMode::Loop);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 875, 1985, 923, 2070),0.1f );
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1472, 1982, 1528, 2073), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2070, 1980, 2130, 2080), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2675, 1988, 2725, 2070), 0.1f);
		
		clip->AddFrame(new Sprite(textureFile, shaderFile, 275, 2435, 325, 2520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 870, 2435, 928, 2525), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1472, 2430, 1528, 2529), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2075, 2430, 2125, 2520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2675, 2435, 2725, 2520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 272, 2885, 325, 2980), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 870, 2880, 930, 2980), 0.1f);

		player->AddClip(clip);

	}
	{//왼 오른 1
		clip = new Clip(PlayMode::Loop);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 268, 3777, 322, 3869), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 865, 3775, 922, 3870), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1460, 3780, 1530, 3865), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2060, 3780, 2129, 3866), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 2665, 3780, 2722, 3865), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 262, 4230, 325, 4318), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 861, 4228, 925, 4318), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1461, 4225, 1525, 4320), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2065, 4225, 2121, 4320), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2630, 4220, 2730, 4320), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 260, 4680, 330, 4765), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 860, 4680, 933, 4765), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1465, 4680, 1525, 4765), 0.1f);
		player->AddClip(clip);

	} 
	{//뒤2
	clip = new Clip(PlayMode::Loop);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 2680, 4670, 2720, 4765), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 280, 5120, 320, 5215), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 878, 5122, 922, 5212), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1477, 5125, 1524, 5210), 0.1f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 2075, 5120, 2125, 5212), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2680, 5120, 2722, 5215), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 277, 5572, 324, 5661), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 872, 5575, 925, 5660), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1480, 5570, 1520, 5663), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2080, 5570, 2120, 5664), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2678, 5570, 2722, 5662), 0.1f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 278, 6025, 325, 6110), 0.1f);
	
	player->AddClip(clip);

	}
	{//앞idle3

		clip = new Clip(PlayMode::Loop);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 2680, 7825, 2720, 7920), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 280, 8275, 320, 8370), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 880, 8275, 920, 8370), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1480, 8275, 1520, 8370), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 2080, 8275, 2120, 8370), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2680, 8275, 2720, 8370), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 280, 8725, 320, 8820), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 880, 8725, 920, 8820), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1480, 8725, 1520, 8820), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2080, 8725, 2120, 8820), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2680, 8725, 2720, 8820), 0.1f);

	

		player->AddClip(clip);

	}
	{//왼 idle4
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1505, 11425, 1540, 11520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1505, 11425, 1540, 11520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1505, 11425, 1540, 11520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1505, 11425, 1540, 11520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1505, 11425, 1540, 11520), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1870, 11427, 1906, 11525), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1870, 11427, 1906, 11525), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1870, 11427, 1906, 11525), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1870, 11427, 1906, 11525), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1870, 11427, 1906, 11525), 0.1f);

		player->AddClip(clip);
	}
	{//뒤 idle5
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2080, 4670, 2120, 4762), 0.1f);
		

		player->AddClip(clip);
	}

	{//attack 6
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2675, 10487, 2735, 10580), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 290, 10950, 360, 11050), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 885, 10980, 955, 11075), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1465, 10985, 1536, 11078), 0.1f);

		player->AddClip(clip);
	}
	




	
	player->Position(position);
	player->Scale(scale);
	player->Play(3);
	player->DrawBound(true);
	dir = Direction::EndDown;
	aDir = AttackDirection::None;

}

HLDPlayer::~HLDPlayer()
{
	for (HLDAlter*alters:alter) {
		SAFE_DELETE(alters);
	}

	SAFE_DELETE(sword);
	SAFE_DELETE(slash);
	
	SAFE_DELETE(player);
}

void HLDPlayer::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
}

void HLDPlayer::Position(D3DXVECTOR2 val)
{
	position = val;
}

void HLDPlayer::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
}

void HLDPlayer::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDPlayer::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	
	KeyDirection();


	if(bCheckDash){
	for (int i = 0; i < 3;i++) {
		alter[i]->Position(alterPosition[i]);
		alter[i]->Update(V, P);
	}
	}

	sword->Update(V, P);
	player->DrawBoundCollision(bCheck);
	player->DrawReds(bCheck||bCheckBrute);
	slash->Update(V, P);
	

	
	player->Position(position);
	player->Scale(scale);
	player->Update(V, P);
}

void HLDPlayer::Render()
{
	ImGui::SliderFloat("rotation", (float*)&rt, -179.9, 179.9);
	ImGui::LabelText("alterPositon0", "%f,%f", alterPosition[0].x, alterPosition[0].y);
	ImGui::LabelText("alterPositon1", "%f,%f", alterPosition[1].x, alterPosition[1].y);
	ImGui::LabelText("alterPositon2", "%f,%f", alterPosition[2].x, alterPosition[2].y);


	//if(ImGui::LabelText(&rt,))

	slash->Render();
	if (bCheckDash) {
		for (int i = 0; i < 3; i++) {
			alter[i]->Render();
		}
	}

	
	
	player->Render();
	
	sword->Render();
}

void HLDPlayer::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{

	
	//defaultCameraPoint = focusOffset;
	//temp.x -= (float)Width*0.5f;
    //	temp.y -= (float)Height*0.5f;
	if(!bCheckStage01){
	if (backgroundSize.x/2 - (float)Width * 0.5f-9.0f> player->Position().x-backgroundPoint.x&&backgroundSize.x / 2 - (float)Width * 0.5f+13.0f > backgroundPoint.x-player->Position().x  ) {
	defaultCameraPoint.x = player->Position().x - focusOffset.x;
	}
	if(backgroundSize.y / 2 - (float)Height * 0.5f+104.0f  > backgroundPoint.y- player->Position().y&& backgroundSize.y / 2 - (float)Height * 0.5f - 95.0f > player->Position().y - backgroundPoint.y){//backgroundSize.y/2- Height * 0.5f-95.0f > player->Position().y - backgroundPoint.y
	defaultCameraPoint.y = player->Position().y - focusOffset.y;//&& backgroundSize.y / 2 - Height * 0.5f - 95.0f > player->Position().y - backgroundPoint.y
	
	}
	}
	if (bCheckStage01) {
		if (backgroundSize.x / 2 - (float)Width *0.285 > player->Position().x - backgroundPoint.x&&backgroundSize.x / 2 - (float)Width *0.26 > backgroundPoint.x - player->Position().x) {
			defaultCameraPoint.x = player->Position().x - focusOffset.x;
		}
		if (backgroundSize.y / 2 - (float)Height  *0.09 > backgroundPoint.y - player->Position().y&& backgroundSize.y / 2 - (float)Height*0.42 > player->Position().y - backgroundPoint.y) {//backgroundSize.y/2- Height * 0.5f-95.0f > player->Position().y - backgroundPoint.y
			defaultCameraPoint.y = player->Position().y - focusOffset.y;//&& backgroundSize.y / 2 - Height * 0.5f - 95.0f > player->Position().y - backgroundPoint.y

		}
	}



	*position = defaultCameraPoint;
	//cameraPosHp(*position);
	
	*size = D3DXVECTOR2(1, 1);
}

void HLDPlayer::GetBackgroundCollision(bool val)
{
	bCheckBackground = val;
}

Sprite * HLDPlayer::GetSprite()
{
	return player->GetSprite();
}

Sprite* HLDPlayer::GetSlash()
{
	return slash->GetSprite();
}

Sprite * HLDPlayer::GetSword()
{
	return sword->GetSprite();
}

void HLDPlayer::GetCollision(bool val)
{
	bCheck = val;

}

void HLDPlayer::GetBruteCollision(bool val)
{
	bCheckBrute = val;
}

void HLDPlayer::GetBackgroundData(D3DXVECTOR2 size, D3DXVECTOR2 backPoint)
{
	backgroundSize = size;
	backgroundPoint= backPoint;
}

void HLDPlayer::GetWallCollision(bool val)
{
	//bCheckWalls.push_back(val);
	bCheckWall = val;
}

void HLDPlayer::SetWallCollision(bool val,int count)
{
	bCheckWalls[count] = val;
}

Direction HLDPlayer::AttackDir(Direction dir, bool bCheckDown, bool bCheckLeft, bool bCheckRight, bool bCheckUp)
{
	if (Key->Press('A')) {
		dir = Direction::Attack;
		slash->Position(player->Position());

		//player->Play(6);
	}

	if (Key->Press('A') && Key->Press(VK_UP)) {
		slash->Rotation(179, 0, 0);//Rotation(179);
		dir = Direction::AttackUp;
	}
	if (Key->Press('A') && Key->Press(VK_DOWN)) {
		slash->Rotation(0, 0, 0);
		dir = Direction::AttackDown;
	}
	if (Key->Press('A') && Key->Press(VK_LEFT)) {
		slash->Rotation(0, 0, 275);//Rotation(179);
		dir = Direction::AttackLeft;
	}
	if (Key->Press('A') && Key->Press(VK_RIGHT)) {
		slash->Rotation(0, 0, 90);//Rotation(179);
		dir = Direction::AttackRight;
	}

	if (Key->Up('A')) {
		slash->Position(D3DXVECTOR2(-50000, -50000));
		if (bCheckDown) {
			slash->Rotation(0, 0, 0);
			dir = Direction::EndDown;
		}
		if (bCheckLeft) {
			slash->Rotation(0, 0, 275);//Rotation(179);
			dir = Direction::EndLeft;
		}
		if (bCheckRight) {
			slash->Rotation(0, 0, 90);//Rotation(179);
			dir = Direction::EndRight;
		}
		if (bCheckUp) {
			slash->Rotation(179, 0, 0);//Rotation(179);
			dir = Direction::EndUp;
		}

	}
	return dir;
}

void HLDPlayer::GetStageBool(bool val)
{
	bCheckStage01 = val;
}

void HLDPlayer::KeyDirection()
{
	static bool bCheckUp = false;
	static bool bCheckDown = true;
	static bool bCheckRight = false;
	static bool bCheckLeft = false;
	if (Key->Press('Z')&& dir !=Direction::Attack && dir != Direction::EndDown&& dir != Direction::EndUp&& dir != Direction::EndRight&& dir != Direction::EndLeft) {
		moveSpeed = 500.0f;
		moveMinSpeed = 3000.0f;
		if(bCheckUp|| bCheckDown|| bCheckRight|| bCheckLeft){
		        bCheckDash = true;
		}
	}
	if (Key->Up('Z')) {
		moveSpeed = 100.0f;
		moveMinSpeed = 400.0f;
		bCheckDash = false;
	}

	if (Key->Press(VK_UP)) {

		dir = Direction::Up;
	}if (Key->Up(VK_UP)) {
		slash->Rotation(179, 0, 0);//Rotation(179);
		bCheckUp = true;
		bCheckDown = false;
		bCheckRight = false;
		bCheckLeft = false;
		//player->Play(5);
		dir = Direction::EndUp;
	}
	if (Key->Press(VK_DOWN)) {

		dir = Direction::Down;
	}if (Key->Up(VK_DOWN)) {
		slash->Rotation(0, 0, 0);
		bCheckUp = false;
		bCheckDown = true;
		bCheckRight = false;
		bCheckLeft = false;
		//player->Play(3);
		dir = Direction::EndDown;
	}
	if (Key->Press(VK_LEFT)) {

		dir = Direction::Left;
	}if (Key->Up(VK_LEFT)) {
		//player->Play(4);
		slash->Rotation(0, 0, 275);//Rotation(179);
		bCheckUp = false;
		bCheckDown = false;
		bCheckRight = false;
		bCheckLeft = true;
		dir = Direction::EndLeft;
	}

	if (Key->Press(VK_RIGHT)) {
		
		dir = Direction::Right;
	}if (Key->Up(VK_RIGHT)) {
		slash->Rotation(0, 0, 90);//Rotation(179);
		//player->Play(4);
		bCheckUp = false;
		bCheckDown = false;
		bCheckRight = true;
		bCheckLeft = false;
		dir = Direction::EndRight;
	}

	if (Key->Press(VK_RIGHT) && Key->Press(VK_UP)) {
		dir = Direction::RightUp;
	}
	if (Key->Press(VK_RIGHT) && Key->Press(VK_DOWN)) {
		dir = Direction::RightDown;
	}
	if (Key->Press(VK_LEFT) && Key->Press(VK_UP)) {
		dir = Direction::LeftUp;
	}
	if (Key->Press(VK_LEFT) && Key->Press(VK_DOWN)) {
		dir = Direction::LeftDown;
	}

	dir=AttackDir(dir, bCheckDown,  bCheckLeft,  bCheckRight, bCheckUp);
	sword->GetPlayerPos(player->Position());
	if (Key->Press('S')) {

		RotationWeapon(); 
		
	}

	if (abs(player->Position().x-sword->Position().x)+ abs(player->Position().y - sword->Position().y) >350) {
		
		sword->GetPlayerBool(false); //직선 날라오기
	
	}
	if (abs(player->Position().x - sword->Position().x) + abs(player->Position().y - sword->Position().y) < 50.0f) {
		
		sword->GetCollisionPlayerBool(true); //다시 되돌아오기
		bSwordCheck = false;
	}

	switch (dir)
	{
	case Direction::Up:
		
		position.y += moveSpeed * Time::Delta();
		if (bCheckBackground||bCheckWall) {
			position.y -= moveMinSpeed * Time::Delta();
		}
		player->Play(2);
		if (bCheckDash) {
			for (int i = 0; i < 3;i++) {
				
				
			alter[i]->GetPlayNum(2);
			alterPosition[i].x = position.x;
			alterPosition[i].y = position.y - interval[i]; //moveSpeed * Time::Delta();
			}
		}
		
		break;
	case Direction::Down:
		
		player->Play(0);
	
		position.y -= moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.y += moveMinSpeed * Time::Delta();
		}
		if (bCheckDash) {
			for (int i = 0; i < 3; i++) {
				
			alter[i]->GetPlayNum(0);
			alterPosition[i].x = position.x;
			alterPosition[i].y = position.y + interval[i];//moveSpeed  * Time::Delta();
			}

		}
		
		break;
	case Direction::Left:
		position.x -= moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.x += moveMinSpeed * Time::Delta();
		}
		player->Play(1);
		if (bCheckDash) {
			for (int i = 0; i < 3; i++) {
				alter[i]->Rotation(0, 0, 0);
				alter[i]->GetPlayNum(1);
				alterPosition[i].x = position.x + interval[i];//+ moveSpeed * Time::Delta();
				alterPosition[i].y = position.y;
			}

		}
		
		
		player->Rotation(0, 0, 0);
		break;
	case Direction::Right:
		position.x += moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.x -= moveMinSpeed * Time::Delta();

			
		}

		player->Play(1);
		
		player->Rotation(0, 179, 0);
		if (bCheckDash) {
			for (int i = 0; i < 3; i++) {
				

				alter[i]->GetPlayNum(1);
				alter[i]->Rotation(0, 179, 0);
				alterPosition[i].x = position.x - interval[i];//- moveSpeed * Time::Delta();
				alterPosition[i].y = position.y;
			}
		}

		break;
	case Direction::LeftDown:
		position.x -= moveSpeed * Time::Delta();
		position.y -= moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.x += moveMinSpeed * Time::Delta();
			position.y += moveMinSpeed * Time::Delta();
		}
		player->Play(1);
		player->Rotation(0, 0, 0);
		if (bCheckDash) {
			for (int i = 0; i < 3; i++) {
				alter[i]->GetPlayNum(1);
				alter[i]->Rotation(0, 0, 0);

				alterPosition[i].x = position.x + interval[i];// moveSpeed  * Time::Delta();
				alterPosition[i].y = position.y + interval[i]; //moveSpeed  * Time::Delta();
			}

		}
		break;
	case Direction::LeftUp:
		position.x -= moveSpeed * Time::Delta();
		position.y += moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.x += moveMinSpeed * Time::Delta();
			position.y -= moveMinSpeed * Time::Delta();
		}
		player->Play(1);
		player->Rotation(0, 0, 0);
		if (bCheckDash) {
			for (int i = 0; i < 3; i++) {
				
				alter[i]->GetPlayNum(1);
				alter[i]->Rotation(0, 0, 0);

				alterPosition[i].x = position.x + interval[i];//moveSpeed  * Time::Delta();
				alterPosition[i].y = position.y - interval[i];//moveSpeed  * Time::Delta();
			}

		}
		break;
	case Direction::RightUp:
		position.x += moveSpeed * Time::Delta();
		position.y += moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.x -= moveMinSpeed * Time::Delta();
			position.y -= moveMinSpeed * Time::Delta();
		}
		player->Play(1);
		player->Rotation(0, 179, 0);
		if (bCheckDash) {
			for (int i = 0; i < 3; i++) {
				
				alter[i]->GetPlayNum(1);
				alter[i]->Rotation(0, 179, 0);
				alterPosition[i].x = position.x - interval[i];// moveSpeed  * Time::Delta();
				alterPosition[i].y = position.y - interval[i]; //moveSpeed  * Time::Delta();
			}
		}
		break;
	case Direction::RightDown:
		position.x += moveSpeed * Time::Delta();
		position.y -= moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.x -= moveMinSpeed * Time::Delta();
			position.y += moveMinSpeed * Time::Delta();
		}
		player->Play(1);
		player->Rotation(0, 179, 0);
		if (bCheckDash) {
			for (int i = 0; i < 3; i++) {
				alter[i]->GetPlayNum(1);
				alter[i]->Rotation(0, 179, 0);

				alterPosition[i].x = position.x - interval[i]; //moveSpeed  * Time::Delta();
				alterPosition[i].y = position.y + interval[i];//moveSpeed * Time::Delta();
			}
		}
		break;
	case Direction::EndUp:
		if (bCheckBackground || bCheckWall) {
			position.y -= moveMinSpeed * Time::Delta();
		}
		player->Play(5);
		break;
	case Direction::EndDown:
		if (bCheckBackground || bCheckWall) {
			position.y += moveMinSpeed * Time::Delta();
		}
		player->Play(3);
		break;
	case Direction::EndRight:
		if (bCheckBackground || bCheckWall) {
			position.x -= moveMinSpeed * Time::Delta();
		}
		player->Play(4);
		break;
	case Direction::EndLeft:
		if (bCheckBackground || bCheckWall) {
			position.x += moveMinSpeed * Time::Delta();
		}
		player->Play(4);
		break;
	case Direction::Attack:
		player->Play(6);
		break;
	case Direction::AttackUp:
		position.y += moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.y -= moveMinSpeed * Time::Delta();
			
		}
		player->Play(6);
		break;
	case Direction::AttackDown:
		position.y -= moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.y += moveMinSpeed * Time::Delta();

		}
		player->Play(6);
		break;
	case Direction::AttackLeft:
		position.x -= moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.x += moveMinSpeed * Time::Delta();

		}
		player->Play(6);
		break;
	case Direction::AttackRight:
		position.x += moveSpeed * Time::Delta();
		if (bCheckBackground || bCheckWall) {
			position.x -= moveMinSpeed * Time::Delta();

		}
		player->Play(6);
		break;

	default:
		
		break;
	}

	
}

void HLDPlayer::RotationWeapon()
{

	shootWeapon = true;

	if (!bSwordCheck) {
		sword->GetDirection((DirectionWeapon)dir);
		bSwordCheck = true;
		if (dir == Direction::Right || dir == Direction::EndRight) {
			sword->Position(player->Position().x + 55.0f, player->Position().y);
			sword->Rotation(0, 0, 0);
		}
		if (dir == Direction::Left || dir == Direction::EndLeft) {
			sword->Position(player->Position().x - 55.0f, player->Position().y);
			sword->Rotation(0, 179, 0);
		}
		if (dir == Direction::Up || dir == Direction::EndUp) {
			sword->Position(player->Position().x, player->Position().y + 55.0f);
			sword->Rotation(0, 0, 108.4f);
		}
		if (dir == Direction::Down || dir == Direction::EndDown) {
			sword->Position(player->Position().x, player->Position().y - 55.0f);
			sword->Rotation(0, 0, -108.4f);
		}if (dir == Direction::RightDown) {
			sword->Position(player->Position().x + 55.0f, player->Position().y - 55.0f);
			sword->Rotation(0, 0, 100.1f);
		}
		if (dir == Direction::RightUp) {
			sword->Position(player->Position().x + 55.0f, player->Position().y + 55.0f);
			sword->Rotation(0, 0, -100.1f);
		}
		if (dir == Direction::LeftDown) {
			sword->Position(player->Position().x - 55.0f, player->Position().y - 55.0f);
			sword->Rotation(0, 179, 100.1f);
		}
		if (dir == Direction::LeftUp) {
			sword->Position(player->Position().x - 55.0f, player->Position().y + 55.0f);
			sword->Rotation(0, 179, -100.1f);
		}
		//	sword->Rotation(0, 0, rt);
		sword->GetPlayerBool(true);
		sword->StartMoveWeapon(shootWeapon);
		//sword->Rotation(0, 0, 0);
	}
	
}
