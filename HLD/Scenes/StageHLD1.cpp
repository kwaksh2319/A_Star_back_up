#include"stdafx.h"
#include"./HLD/Scenes/StageHLD1.h"
#include"./Object/AstarPlayer.h"

#include"./Object/AstarMonster.h"

#include"./HLD/FindPath/NodeHLD.h"
#include"./Viewer/FreeCamera.h"
#include"./Object/Player.h"
#include"./HLD/Object/HLDPillar.h"
#include"./HLD/Object/HLDCrystal.h"
#include"./HLD/Object/HLDStreetLamp.h"
#include"./HLD/Object/HLDTile01.h"
#include"./HLD/Object/HLDTile02.h"
#include"./HLD/Object/HLDRilfMan.h"
#include"./HLD/Object/HLDBrute.h"
#include"./HLD/Object/HLDPlayer.h"
#include "./Viewer/Following.h"
#include"./HLD/FindPath/BFSNodePathHLD.h"
#include"./HLD/FindPath/NodeHLDCopy.h"



#define InPilar position.x < pilar[i]->Position().x+10.0f&& position.x>pilar[i]->Position().x-10.0f&& position.y>pilar[i]->Position().y-10.0f&& position.y < pilar[i]->Position().y +10.0f
#define InCrystal position.x < crystal[i]->Position().x+10.0f&& position.x>crystal[i]->Position().x-10.0f&& position.y>crystal[i]->Position().y-10.0f&& position.y < crystal[i]->Position().y +10.0f
#define InStreetLamp position.x < streetLamp[i]->Position().x+10.0f&& position.x>streetLamp[i]->Position().x-10.0f&& position.y>streetLamp[i]->Position().y-10.0f&& position.y < streetLamp[i]->Position().y +10.0f
#define InTile01 position.x < tile01[i]->Position().x+10.0f&& position.x>tile01[i]->Position().x-10.0f&& position.y>tile01[i]->Position().y-10.0f&& position.y < tile01[i]->Position().y +10.0f
#define InTile02 position.x < tile02[i]->Position().x+10.0f&& position.x>tile02[i]->Position().x-10.0f&& position.y>tile02[i]->Position().y-10.0f&& position.y < tile02[i]->Position().y +10.0f
#define InRilfMan position.x < rilfMan[i]->Position().x+10.0f&& position.x>rilfMan[i]->Position().x-10.0f&& position.y>rilfMan[i]->Position().y-10.0f&& position.y < rilfMan[i]->Position().y +10.0f
#define InBrute position.x < brute[i]->Position().x+10.0f&& position.x>brute[i]->Position().x-10.0f&& position.y>brute[i]->Position().y-10.0f&& position.y < brute[i]->Position().y +10.0f
Stage1HLD::Stage1HLD(SceneValues * values)
	:Scene(values), mouse(0, 0), cameraPos(0, 0), position(0, 0), massSize(0, 0), bMove(false), bButton(false), bButtonCrystal(false), bButtonTile01(false), bButtonTile02(false), bButtonRilfMan(false), bButtonBrute(false),worldTime(0), bFindPathAstar(false) ,bCheckCollisionBrute(false),bCheckCollisionPlayer(false),bCheckCollisionRilfMan(false),bCheckRangeBrute(false),bCheckRangeRilfMan(false), bCheckState(true)  //부모 생성자 초기화 
{

	wstring textureFile = Textures + L"./HDL/HDLbackground_Green.png";
	wstring shaderFile = Shaders + L"./Effect.fx";

	background = new Sprite(textureFile, shaderFile);
	player = new HLDPlayer(D3DXVECTOR2(0.0f, -200));//-10, -150
	monster = new AstarMonster(D3DXVECTOR2(227, 108), D3DXVECTOR2(3, 3));
	
	//HDL_Background_Titan_Parallax
	//HDLbackground_Green
	playerRect = player->GetSprite();
	

	monsterRect = monster->GetSprite();

	//float tempX = monster->Scale().x*monsterRect->TextureSize().x;
	//float tempY = monster->Scale().y*monsterRect->TextureSize().y;


	float tempX = player->Scale().x*playerRect->TextureSize().x;
	float tempY = player->Scale().y*playerRect->TextureSize().y;

	float tempXBack =background->Scale().x*background->TextureSize().x;
	float tempYBack = background->Scale().y*background->TextureSize().y;

	massSize = D3DXVECTOR2(tempX*3, tempY*3/2 );
	massSizeBackground = D3DXVECTOR2(tempXBack, tempYBack);
	//node = new NodeHLD(player->Position(), massSize);
	//background->Position()
	nodeTmp = new NodeHLDCopy(background->Position(),  massSize, massSizeBackground);
	bfs = new BFSNodePathHLD(monster->Position(), massSize);
	//values->MainCamera = new FreeCamera;
	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Following(player);
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		Device,
		(Textures + L"./AStar/tumb_magma.png").c_str(),
		NULL, NULL, &srv, NULL
	);
	assert(SUCCEEDED(hr));
	
	
	background->DrawBound(true);

}

Stage1HLD::~Stage1HLD()
{
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(background);
	SAFE_DELETE(player);
	SAFE_DELETE(monster);
	SAFE_DELETE(bfs);
	SAFE_DELETE(nodeTmp);
	//SAFE_DELETE(node);
	for (HLDPilar*pilars : pilar)
		SAFE_DELETE(pilars);

	for (HLDCrystal*crystals : crystal)
		SAFE_DELETE(crystals);

	for (HLDStreetLamp*streetLamps : streetLamp)
		SAFE_DELETE(streetLamps);

	for (HLDTile01*tile01s : tile01)
		SAFE_DELETE(tile01s);
	for (HLDTile02*tile02s : tile02)
		SAFE_DELETE(tile02s);


	for (HLDRilfMan*rilfMans : rilfMan)
		SAFE_DELETE(rilfMans);

	for (HLDBrute*brutes : brute)
		SAFE_DELETE(brutes);

	for (BFSNodePathHLD*bfsNodes : bfsNode)
		SAFE_DELETE(bfsNodes);

	for (BFSNodePathHLD*bfsNodeBrutes : bfsNodeBrute)
		SAFE_DELETE(bfsNodeBrutes);

	//for(NodeHLD *astarRilfMans: astarRilfMan)
	//	SAFE_DELETE(astarRilfMans);
	for (NodeHLDCopy *astarRilfMans : astarRilfMan)
		SAFE_DELETE(astarRilfMans);
	for (NodeHLDCopy *astarBrutes : astarBrute)
		SAFE_DELETE(astarBrutes);

	SAFE_RELEASE(srv);

}

void Stage1HLD::Update()
{
	if (!bCheckState) {
		D3DXMATRIX V = values->MainCamera->View();
		D3DXMATRIX P = values->Projection;
		vector<D3DXVECTOR2> ways;

		//몬스터 마그마 충돌 검사

		for (HLDPilar*pilars : pilar) {
			if (Sprite::Aabb(monster->GetSprite(), pilars->GetSprite())) {
				monster->Collision(true);
				break;
			}
			else
				monster->Collision(false);
		}


		mouse = Mouse->Position();
		mouse.x = mouse.x - (float)Width*0.5f;
		mouse.y = (mouse.y - (float)Height*0.5f)*-1.0f;
		cameraPos = values->MainCamera->Position();
		position = mouse + cameraPos;
		{
			/*		node->GetMouseCursor(position);
		

		bMove = monster->Move();

		
		node->ReadyToStart(bMove == false && Mouse->Down(1));
		node->GetStartPos(monster->Position());
		node->GetGoalPos(player->Position());
		node->Update(V, P);
		*/


		}

		nodeTmp->GetMouseCursor(position);
		nodeTmp->ReadyToStart(bMove == false && Mouse->Down(1));
		//nodeTmp->GetStartPos(monster->Position());
		//nodeTmp->GetGoalPos(player->Position());
		nodeTmp->Update(V, P);


		CollisionWall();
		CreatePotal();
		CheckRilfManCollision();
		CheckBruteManCollision();
		CheckSlashBrute();
		CheckPlayerBrute();
		CheckSlashRilfMan();
		CheckPlayerBullet();
		CheckTile01();

		//=bfs->GetBFSPosition();

		background->Update(V, P);

		for (HLDPilar* pilars : pilar)
			pilars->Update(V, P);

		for (HLDCrystal*crystals : crystal)
			crystals->Update(V, P);

		for (HLDStreetLamp*streetLamps : streetLamp)
			streetLamps->Update(V, P);

		for (HLDTile01*tile01s : tile01)
			tile01s->Update(V, P);

		for (HLDTile02*tile02s : tile02)
			tile02s->Update(V, P);

		for (HLDRilfMan*rilfMans : rilfMan) {

			rilfMans->Update(V, P);
		}
		for (HLDBrute*brutes : brute)
			brutes->Update(V, P);

		player->GetBackgroundData(background->TextureSize(), background->Position());
		player->GetBackgroundCollision(Sprite::AabbBackgroundRange(background, player->GetSprite()));





		player->Position(-10, -150);
		player->Update(V, P);

		//monster->GetWay(node->SetWay());

		//monster->GetWay(bfs->GetBFSPosition());



		monster->Update(V, P);

		//node->Update(V, P);
		for (NodeHLDCopy*astarRilfManes : astarRilfMan) {
			astarRilfManes->Update(V, P);

		}
		for (NodeHLDCopy*astarBrutes : astarBrute) {
			astarBrutes->Update(V, P);
		}
		BFSupdate(V, P);
		AstarUpdate(V, P);
		UpdateWall();
	}
}

void Stage1HLD::Render()
{

	RenderImGui();
	RenderDebbuging();
	RenderImGuiSaveLoad();


	background->Render();
	//node->Render();
	nodeTmp->Render();
	for (NodeHLDCopy*astarRilfManes : astarRilfMan) {
		astarRilfManes->Render();

	}
	for (NodeHLDCopy*astarBrutes : astarBrute) {
		astarBrutes->Render();
	}
	

	for (HLDPilar* pilars : pilar)
		pilars->Render();

	

	

	for (HLDTile01*tile01s : tile01)
		  tile01s->Render();

	for (HLDTile02*tile02s : tile02)
		tile02s->Render();

	for (HLDCrystal*crystals : crystal)
		crystals->Render();

	for (HLDStreetLamp*streetLamps : streetLamp)
		streetLamps->Render();

	for (HLDRilfMan*rilfMans : rilfMan)
		rilfMans->Render();

	for (HLDBrute*brutes : brute)
		brutes->Render();

	player->Render();
	monster->Render();




}

void Stage1HLD::BFSupdate(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (bfsNode.size() > 0 && rilfMan.size() > 0) {


		for (int i = 0; i < bfsNode.size(); i++) {
			bfsNode[i]->GetMonsterPos(rilfMan[i]->Position());
			bfsNode[i]->Update(V, P);
			rilfMan[i]->BFSGetWay(bfsNode[i]->ReturnPosition());
		}


	}
	if (bfsNodeBrute.size() > 0 && brute.size() > 0) {
		for (int i = 0; i < bfsNodeBrute.size(); i++) {
			bfsNodeBrute[i]->GetMonsterPos(brute[i]->Position());
			bfsNodeBrute[i]->Update(V, P);
			brute[i]->BFSGetWay(bfsNodeBrute[i]->ReturnPosition());
		}
	}
}

void Stage1HLD::AstarUpdate(D3DXMATRIX & V, D3DXMATRIX & P)
{

	//node->GetMouseCursor(position);
	
	if(astarRilfMan.size()>0){

	for (int i = 0; i < astarRilfMan.size();i++) {
		//bFindPathAstar = bCheckRangeRilfMan;
		
		astarRilfMan[i]->ReadyToStart(bRangeRilfMan[i]);
		astarRilfMan[i]->GetStartPos(rilfMan[i]->Position());
		astarRilfMan[i]->GetGoalPos(player->Position());
		astarRilfMan[i]->Update(V, P);
		rilfMan[i]->AStarGetWay(astarRilfMan[i]->SetWay());
	}

	}

	if (astarBrute.size() > 0) {

		for (int i = 0; i < astarBrute.size(); i++) {
			astarBrute[i]->ReadyToStart(bRangeBrute[i]);
			astarBrute[i]->GetStartPos(brute[i]->Position());
			astarBrute[i]->GetGoalPos(player->Position());
			astarBrute[i]->Update(V, P);
			brute[i]->AStarGetWay(astarBrute[i]->SetWay());
		}

	}

	

}

void Stage1HLD::UpdateWall()
{
	RilfManWall();
	 BruteWall();
}

void Stage1HLD::CreatePotal()
{
	if (tile02.size() > 0) {
		for (HLDTile02* tile02s : tile02) {
			if (Sprite::Aabb(tile02s->GetSpirte(), player->GetSprite())) {

				bNext = true;
				
				
			}


		}



	
	}
}

void Stage1HLD::CollisionWall()
{
	bool bCheckWall=false;
	if (pilar.size() > 0) {
		for (int i = 0; i < pilar.size();i++) {
			
		
			
			bCheckWall|= Sprite::Aabb(pilar[i]->GetSprite(), player->GetSprite());
		
			
			
		}
		
	}if (crystal.size()>0) {
		for (int i = 0; i < crystal.size(); i++) {
			
			
			bCheckWall |= Sprite::Aabb(crystal[i]->GetSprite(), player->GetSprite());
		}

	}if (streetLamp.size()>0) {
		for (int i = 0; i < streetLamp.size(); i++) {
			
			
			bCheckWall |= Sprite::Aabb(streetLamp[i]->GetSprite(), player->GetSprite());
		}
	}

	player->GetWallCollision(bCheckWall);
}

void Stage1HLD::CheckRilfManCollision() //riflman 충돌 및 총알 충돌처리 
{
	static bool bColCheck = false;
	static bool bRangeCheck = false;
	//static bool bBulletToPlayer[3] = { false,false,false };
	//static bool bBulletToRangeOut[3] = { false,false,false };
	
	for(int i=0;i< rilfMan.size();i++){
		bColCheck = Sprite::Aabb(player->GetSprite(), rilfMan[i]->GetSprite()); //탐지 범위 

		bStopRilfMan[i] = Sprite::AabbStopBox(player->GetSprite(), rilfMan[i]->GetSprite());
		bRangeRilfMan[i] = Sprite::AabbRangeBox(player->GetSprite(), rilfMan[i]->GetSprite());

		rilfMan[i]->GetCollision(bColCheck);
		rilfMan[i]->GetRangeCollision(bRangeRilfMan[i]);
		//for(int j=0;j<3;j++){


		
		 
		

		if (bStopRilfMan[i]) {

			rilfMan[i]->GetStop(true);
		}

		if (Sprite::Aabb(player->GetSprite(), rilfMan[i]->GetBulletSprite(0))) {//총알 플레이어 충돌 처리
			rilfMan[i]->GetStop(false);
			bStopRilfMan[i] = false;
		}

		if (!(Sprite::AabbStopBox(rilfMan[i]->GetSprite(), rilfMan[i]->GetBulletSprite(0)))) { //총알의 날아가는 범위
			rilfMan[i]->GetStop(false);
			bStopRilfMan[i] = false;
			
		}

		rilfMan[i]->GetPlayerPosition(player->Position());
		
		//}
																										  //if(bStopRilfMan[i]==){
			//bStopRilfMan[i] = true;
		//}
		//총알에 대한 구현 
		
		//rilfMan[i]->GetStop(bStopRilfMan[i]);
		//if(bStopRilfMan[i]){
		
		 //bStopRilfMan[i] = false;
		//}
		
		
	}
		
	

	
}

void Stage1HLD::CheckBruteManCollision()  //brute 충돌처리 
{
	static bool bColCheck = false;

	for (int i = 0; i < brute.size(); i++) {
		bColCheck = Sprite::Aabb(player->GetSprite(), brute[i]->GetSprite()); //탐지 범위 

		bRangeBrute[i] = Sprite::AabbRangeBox(player->GetSprite(), brute[i]->GetSprite());

		brute[i]->GetCollision(bColCheck);
		brute[i]->GetRangeCollision(bRangeBrute[i]);


	}
	
}

void Stage1HLD::CheckSlashRilfMan() //riflman 충돌처리 
{
	
	
	for (HLDRilfMan*rilfMans : rilfMan) {
		rilfMans->GetCollision(Sprite::Aabb(player->GetSword(), rilfMans->GetSprite())||Sprite::Aabb(player->GetSlash(), rilfMans->GetSprite()));

	}

}

void Stage1HLD::CheckSlashBrute()
{
	//for (HLDBrute*brutes:brute) {
		//brutes->GetCollision(Sprite::Aabb(player->GetSlash(), brutes->GetSprite()));

	//}

	for (HLDBrute*brutes : brute) {
		brutes->GetCollision(Sprite::Aabb(player->GetSword(), brutes->GetSprite())|| Sprite::Aabb(player->GetSlash(), brutes->GetSprite()));

	}
}

void Stage1HLD::CheckPlayerBrute()
{
	for (HLDBrute*brutes : brute) {
		player->GetBruteCollision(Sprite::Aabb(player->GetSprite(), brutes->GetSprite()));

	}
}

void Stage1HLD::CheckPlayerBullet()
{
	for (HLDRilfMan*rilfMans : rilfMan) {
		//rilfMans->GetCollision(Sprite::Aabb(player->GetSlash(), rilfMans->GetSprite()));
		player->GetCollision((Sprite::Aabb(player->GetSprite(), rilfMans->GetSprite())||Sprite::Aabb(player->GetSprite(), rilfMans->GetBulletSprite(0))));
	//	player->GetCollision(Sprite::Aabb(player->GetSprite(), rilfMans->GetBulletSprite(0)));
		
	}

}

void Stage1HLD::CheckTile01()
{

	if (tile01.size() > 0) {
		for (HLDTile01*tile01s : tile01) {
			
			
			tile01s->GetSearchRange(Sprite::AabbStopBox(tile01s->GetSprite(), player->GetSprite()));


		}



	}

}



void Stage1HLD::EditPilar()
{
	if (Mouse->Down(0)) {
		D3DXVECTOR2 temp = nodeTmp->Position();//node->Position();
		pilar.push_back(new HLDPilar(temp));
		bCollisionPilar.push_back(false);
		pilarPoint.push_back(temp);
		//player->GetWallCollision(false);

	}
	if (Key->Down(VK_DELETE)) {
		for (size_t i = 0; i < pilar.size(); i++) {
			if (InPilar) {

				pilar.erase(pilar.begin() + i);
				pilarPoint.erase(pilarPoint.begin() + i);
			}
		}
	}
}

void Stage1HLD::EditCrystal()
{
	if (Mouse->Down(0)) {
		D3DXVECTOR2 temp = nodeTmp->Position();//node->Position();
		crystal.push_back(new HLDCrystal(temp));
		crystalPoint.push_back(temp);
		bCollisionCrystal.push_back(false);

	}if (Key->Down(VK_DELETE)) {
		for (size_t i = 0; i < crystal.size(); i++) {
			if (InCrystal) {

				crystal.erase(crystal.begin() + i);
				crystalPoint.erase(crystalPoint.begin() + i);
			}
		}
	}

}

void Stage1HLD::EditstreetLamp()
{
	if (Mouse->Down(0)) {
		D3DXVECTOR2 temp = nodeTmp->Position();//node->Position();
		streetLamp.push_back(new HLDStreetLamp(temp));
		streetLampPoint.push_back(temp);
		bCollisionStreetLamp.push_back(false);

	}if (Key->Down(VK_DELETE)) {
		for (size_t i = 0; i < streetLamp.size(); i++) {
			if (InStreetLamp) {

				streetLamp.erase(streetLamp.begin() + i);
				streetLampPoint.erase(streetLampPoint.begin() + i);
			}
		}
	}
}

void Stage1HLD::EditTile01()
{
	if (Mouse->Down(0)) {
		D3DXVECTOR2 temp = nodeTmp->Position();//node->Position();
		tile01.push_back(new HLDTile01(temp));
		tile01Point.push_back(temp);


	}if (Key->Down(VK_DELETE)) {
		for (size_t i = 0; i < tile01.size(); i++) {
			if (InTile01) {

				tile01.erase(tile01.begin() + i);
				tile01Point.erase(tile01Point.begin() + i);
			}
		}
	}



}

void Stage1HLD::EditTile02()
{
	if(Mouse->Down(0)) {
		D3DXVECTOR2 temp = nodeTmp->Position();//node->Position();
		tile02.push_back(new HLDTile02(temp));
		tile02Point.push_back(temp);


	}if (Key->Down(VK_DELETE)) {
		for (size_t i = 0; i < tile02.size(); i++) {
			if (InTile02) {

				tile02.erase(tile02.begin() + i);
				tile02Point.erase(tile02Point.begin() + i);
			}
		}
	}
}

void Stage1HLD::EditRilfMan()
{
	
	if (Mouse->Down(0)) {
		
		D3DXVECTOR2 temp;
		temp = Mouse->Position();
		temp.x = temp.x - (float)Width*0.5f;
		temp.y = (temp.y - (float)Height*0.5f)*-1.0f;
		D3DXVECTOR2 cameraPos = values->MainCamera->Position();
		
		temp = cameraPos + temp;
		
		rilfMan.push_back(new HLDRilfMan(temp));
		rilfManPoint.push_back(temp);
		bRangeRilfMan.push_back(false);
		bStopRilfMan.push_back(false);

		
		
		
		
		

	}if (Key->Down(VK_DELETE)) {
		for (size_t i = 0; i < rilfMan.size(); i++) {
			if (InRilfMan) {

				rilfMan.erase(rilfMan.begin() + i);
				rilfManPoint.erase(rilfManPoint.begin() + i);
			}
		}
		for (size_t i = 0; i < bfsNode.size(); i++) {
			if (InRilfMan) {
				bfsNode.erase(bfsNode.begin() + i);
			}
		}
	}



}

void Stage1HLD::EditBrute()
{
	if (Mouse->Down(0)) {
		nodeTmp->GetStartPos(position);
		nodeTmp->GetGoalPos(player->Position());
		nodeTmp->GetMouseCursor(position);
		D3DXVECTOR2 temp = nodeTmp->Position(); //node->Position();
		
		brute.push_back(new HLDBrute(temp));
		brutePoint.push_back(temp);
		bRangeBrute.push_back(false);
	}
	if (Key->Down(VK_DELETE)) {
		for (size_t i = 0; i < brute.size(); i++) {
			if (InBrute) {

				brute.erase(brute.begin() + i);
				brutePoint.erase(brutePoint.begin() + i);
			}
		}
	}
}

void Stage1HLD::RenderImGui()
{
	worldTime += Time::Delta();
	ImGui::Begin("Tools");
	{
		ImGui::LabelText("World Time", "%f", worldTime);
		ImGui::LabelText("Mouse", "%0.2f,%0.2f", position.x, position.y);


		static int combo_item = 0;
		bool valueChanged = ImGui::Combo("item", &combo_item, "None\0Pilar\0Crystal\0StreetLamp\0Tile01\0Tile02\0RilfMan\0Brute\0BFS\0Astar\0Wall\0\0");
		if (combo_item == 1) {
			RenderImGuiPilar();
		}
		else if (combo_item == 2) {
			RenderImGuiCrystal();
		}
		else if (combo_item == 3) {
			RenderImGuistreetLamp();
		}
		else if (combo_item == 4) {
			RenderImGuiTile01();
		}
		else if (combo_item == 5) {
			RenderImGuiTile02();
		}
		else if (combo_item == 6) {
			RenderImGuiRilfMan();
		}
		else if (combo_item == 7) {
			RenderImGuiBrute();
		}
		else if (combo_item == 8) {
			RenderImGuiBFS();
			
		}
		else if (combo_item == 9) {
			RenderImGuIAstar();
		}
		else if (combo_item == 10) {
			RenderImGuiWall();
		}
		//이미지 버튼

		//ImTextureID id = static_cast<ImTextureID>(srv);
		//if (ImGui::ImageButton(id, ImVec2(40, 40), ImVec2(40, 40), ImVec2(1, 1), 1) == true) {
	

		
	}
	ImGui::End();
}

void Stage1HLD::RenderDebbuging()
{
	ImGui::Begin("Debbuging");
	{
		ImGui::LabelText("Collision", "%d", monster->Collision() ? 1 : 0);
		ImGui::LabelText("Img Button", "%d", bButton ? 1 : 0);


	}
	ImGui::End();

}

void Stage1HLD::RenderImGuiSaveLoad()
{
	
	
	RenderSaveLoadImGuiPilar();
	RenderSaveLoadImGuiCrystal();
	RenderSaveLoadImGuiStreetLamp();
	RenderSaveLoadImGuiTile01();
	RenderSaveLoadImGuiTile02();
	RenderSaveLoadImGuiRilfMan();
	RenderSaveLoadImGuiBrute();
	

}

void Stage1HLD::RenderImGuiCrystal()
{
	bool hovering = ImGui::GetIO().WantCaptureMouse;
	if (ImGui::Button("create Crystal")) {

		bButtonCrystal = !bButtonCrystal;
		bButton = false;
		bButtonstreetLamp = false;
		bButtonTile01 = false;
		bButtonTile02 = false;
		bButtonRilfMan = false;
	}
	if (bButtonCrystal&& hovering == false) {
		EditCrystal();

	}

}

void Stage1HLD::RenderImGuiPilar()
{
	bool hovering = ImGui::GetIO().WantCaptureMouse;
	if (ImGui::Button("create Pilar")) {
		bButton = !bButton;
		bButtonCrystal = false;
		bButtonstreetLamp = false;
		bButtonTile01 = false;
		bButtonTile02 = false;
		bButtonRilfMan = false;
		bButtonBrute = false;

	}
	if (bButton && hovering == false) {
		EditPilar();
	}//save 버튼 load 버튼 
}

void Stage1HLD::RenderImGuistreetLamp()
{
	bool hovering = ImGui::GetIO().WantCaptureMouse;

	if (ImGui::Button("create StreetLamp")) {
		bButtonstreetLamp = !bButtonstreetLamp;
		bButtonCrystal = false;
		bButton = false;
		bButtonTile01 = false;
		bButtonTile02 = false;
		bButtonRilfMan = false;
		bButtonBrute = false;
	}
	if (bButtonstreetLamp && hovering == false) {
		EditstreetLamp();
	}//save 버튼 load 버튼 

}

void Stage1HLD::RenderImGuiTile01()
{
	bool hovering = ImGui::GetIO().WantCaptureMouse;

	if (ImGui::Button("create Tile01")) {

		bButtonTile01 = !bButtonTile01;
		bButtonstreetLamp = false;
		bButtonCrystal = false;
		bButton = false;
		bButtonTile02 = false;
		bButtonRilfMan = false;
		bButtonBrute = false;

	}
	if (bButtonTile01==true&& hovering == false) {
		EditTile01();
	}//save 버튼 load 버튼 
}

void Stage1HLD::RenderImGuiTile02()
{
	bool hovering = ImGui::GetIO().WantCaptureMouse;

	if (ImGui::Button("create Tile02")) {

		bButtonTile02 = !bButtonTile02;
		bButtonTile01 = false;
		bButtonstreetLamp = false;
		bButtonCrystal = false;
		bButton = false;
		bButtonRilfMan = false;
		bButtonBrute = false;

	}
	if (bButtonTile02 == true && hovering == false) {
		EditTile02();
	}//save 버튼 load 버튼 

}

void Stage1HLD::RenderImGuiRilfMan()
{
	bool hovering = ImGui::GetIO().WantCaptureMouse;

	if (ImGui::Button("create RilfMan")) {
		bButtonRilfMan = !bButtonRilfMan;
		bButtonTile02 = false;
		bButtonTile01 = false;
		bButtonstreetLamp = false;
		bButtonCrystal = false;
		bButton = false;
		bButtonBrute = false;

	}
	if (bButtonRilfMan == true && hovering == false) {
		EditRilfMan();
	}//save 버튼 load 버튼 
}

void Stage1HLD::RenderImGuiBrute()
{
	bool hovering = ImGui::GetIO().WantCaptureMouse;

	if (ImGui::Button("create Brute")) {
		bButtonBrute = !bButtonBrute;
		bButtonRilfMan = false;
		bButtonTile02 = false;
		bButtonTile01 = false;
		bButtonstreetLamp = false;
		bButtonCrystal = false;
		bButton = false;

	}

	if (bButtonBrute == true && hovering == false) {
		EditBrute();
	}//save 버튼 load 버튼 

}

void Stage1HLD::RenderImGuiBFS()
{
	if (ImGui::Button("create BFS")) {

	RilfManCreateBFS();
	BruteCreateBFS();
	}
}

void Stage1HLD::RenderImGuIAstar()
{
//	static bool checked = true;
	ImGui::Checkbox("AstarFindPath", &bFindPathAstar);
		
	
	if (ImGui::Button("create Astar")) {

		
		RilfManCreateAstar();
		BruteCreateAstar();
	}
}

void Stage1HLD::RenderImGuiWall()
{
	if (ImGui::Button("create Wall")) {
		
	    
		
		
	}


}

void Stage1HLD::RenderSaveLoadImGuiPilar()
{
	
	if (ImGui::Button("Save Pilar") == true&& pilarPoint.size()>0) {
		
		FileManger::SetMarker(pilarPoint);
		FileManger::Save(L"pilarPoint.bin");
		
	}
	ImGui::SameLine();

	if (ImGui::Button("Load Pilar") == true) {
		for (size_t i = 0; i < pilar.size(); i++)
			SAFE_DELETE(pilar[i]);

		pilar.clear();
		pilarPoint.clear();

		FileManger::Load(L"pilarPoint.bin");
		pilarPoint = FileManger::GetMarker();

		for (size_t i = 0; i < pilarPoint.size(); i++)
			pilar.push_back(new HLDPilar(pilarPoint[i]));

	}

}

void Stage1HLD::RenderSaveLoadImGuiCrystal()
{
	if (ImGui::Button("Save Crystal") == true&& crystalPoint.size()>0) {
		FileManger::SetMarker(crystalPoint);
		FileManger::Save(L"crystalPoint.bin");
	}
	ImGui::SameLine();

	if (ImGui::Button("Load Crystal") == true) {
		for (size_t i = 0; i < crystal.size(); i++)
			SAFE_DELETE(crystal[i]);

		crystal.clear();
		crystalPoint.clear();

		FileManger::Load(L"crystalPoint.bin");
		crystalPoint = FileManger::GetMarker();

		for (size_t i = 0; i < crystalPoint.size(); i++)
			crystal.push_back(new HLDCrystal(crystalPoint[i]));

	}

}

void Stage1HLD::RenderSaveLoadImGuiStreetLamp()
{
	if (ImGui::Button("Save StreetLamp") == true&& streetLampPoint.size()>0) {
		FileManger::SetMarker(streetLampPoint);
		FileManger::Save(L"streetLampPoint.bin");
	}
	ImGui::SameLine();

	if (ImGui::Button("Load StreetLamp") == true) {
		for (size_t i = 0; i < streetLamp.size(); i++)
			SAFE_DELETE(streetLamp[i]);

		streetLamp.clear();
		streetLampPoint.clear();

		FileManger::Load(L"streetLampPoint.bin");
		streetLampPoint = FileManger::GetMarker();

		for (size_t i = 0; i < streetLampPoint.size(); i++)
			streetLamp.push_back(new HLDStreetLamp(streetLampPoint[i]));

	}
}

void Stage1HLD::RenderSaveLoadImGuiTile01()
{
	if (ImGui::Button("Save Tile01") == true && tile01Point.size() > 0) {
		FileManger::SetMarker(tile01Point);
		FileManger::Save(L"tile01Point.bin");
	}
	ImGui::SameLine();

	if (ImGui::Button("Load  Tile01") == true) {
		for (size_t i = 0; i < tile01.size(); i++)
			SAFE_DELETE(tile01[i]);

		tile01.clear();
		tile01Point.clear();

		FileManger::Load(L"tile01Point.bin");
		tile01Point = FileManger::GetMarker();

		for (size_t i = 0; i < tile01Point.size(); i++)
			tile01.push_back(new HLDTile01(tile01Point[i]));

	}
}

void Stage1HLD::RenderSaveLoadImGuiTile02()
{
	if (ImGui::Button("Save Tile02") == true && tile02Point.size() > 0) {
		FileManger::SetMarker(tile02Point);
		FileManger::Save(L"tile02Point.bin");
	}
	ImGui::SameLine();

	if (ImGui::Button("Load  Tile02") == true) {
		for (size_t i = 0; i < tile02.size(); i++)
			SAFE_DELETE(tile02[i]);

		tile02.clear();
		tile02Point.clear();

		FileManger::Load(L"tile02Point.bin");
		tile02Point = FileManger::GetMarker();

		for (size_t i = 0; i < tile02Point.size(); i++)
			tile02.push_back(new HLDTile02(tile02Point[i]));

	}

}

void Stage1HLD::RenderSaveLoadImGuiRilfMan()
{
	if (ImGui::Button("Save RilfMan") == true && rilfManPoint.size() > 0) {
		FileManger::SetMarker(rilfManPoint);
		FileManger::Save(L"rilfManPoint.bin");
	}
	ImGui::SameLine();

	if (ImGui::Button("Load RilfMan") == true) {
		

		for (size_t i = 0; i < rilfMan.size(); i++)
			SAFE_DELETE(rilfMan[i]);

		rilfMan.clear();
		rilfManPoint.clear();

		FileManger::Load(L"rilfManPoint.bin");
		rilfManPoint = FileManger::GetMarker();

		for (size_t i = 0; i < rilfManPoint.size(); i++)
			rilfMan.push_back(new HLDRilfMan(rilfManPoint[i]));

	}
}

void Stage1HLD::RenderSaveLoadImGuiBrute()
{
	if (ImGui::Button("Save Brute") == true && brutePoint.size() > 0) {
		FileManger::SetMarker(brutePoint);
		FileManger::Save(L" brutePoint.bin");
	}
	ImGui::SameLine();

	if (ImGui::Button("Load Brute") == true) {
		for (size_t i = 0; i < bfsNodeBrute.size(); i++)
			SAFE_DELETE(bfsNodeBrute[i]);

		for (size_t i = 0; i < brute.size(); i++)
			SAFE_DELETE(brute[i]);

		brute.clear();
		brutePoint.clear();

		FileManger::Load(L" brutePoint.bin");
		brutePoint = FileManger::GetMarker();

		for (size_t i = 0; i < brutePoint.size(); i++)
			brute.push_back(new HLDBrute(brutePoint[i]));



	}
}

void Stage1HLD::RilfManCreateBFS()
{
	if(rilfMan.size()>0){


	for (HLDRilfMan*rilfMans : rilfMan) {
		bfsNode.push_back(new BFSNodePathHLD(rilfMans->Position(), massSize));
	}
	}
}

void Stage1HLD::BruteCreateBFS()
{
	if (brute.size() > 0) {
		
		for (HLDBrute*brutes : brute) {
			bfsNodeBrute.push_back(new BFSNodePathHLD(brutes->Position(), massSize));
		}
	}
}

void Stage1HLD::RilfManCreateAstar()
{
	if (rilfMan.size() > 0) {


		for (HLDRilfMan*rilfMans : rilfMan) {
			astarRilfMan.push_back(new NodeHLDCopy(background->Position(), massSize, massSizeBackground));//new NodeHLDCopy(rilfMans->Position(), massSize));
				//nodeTmp = new NodeHLDCopy(background->Position(), massSizeBackground, massSize);
		}
	}
}

void Stage1HLD::BruteCreateAstar()
{
	if (brute.size() > 0) {

		for (HLDBrute*brutes : brute) {
			astarBrute.push_back(new NodeHLDCopy(background->Position(), massSize, massSizeBackground));
			//astarBrute.push_back(new NodeHLD(brutes->Position(), massSize));
		}
	}

}

void Stage1HLD::RilfManWall()
{
	if (astarRilfMan.size() > 0) {
		
		for (NodeHLDCopy*astarRilfManes : astarRilfMan) {
			//node->SetWallCheck(true);

			
			astarRilfManes->SetWallCheck(true);
			astarRilfManes->GetMouseCursor(position);
			
			
		}
		
		
	}
	if (bfsNode.size()>0) {
		for (BFSNodePathHLD* bfsNodes : bfsNode) {
			//node->SetWallCheck(true);


			bfsNodes->SetWallCheck(true);
			bfsNodes->GetMouseCursor(position);


		}
	}
}

void Stage1HLD::BruteWall()
{
	if (astarBrute.size() > 0) {
		for (NodeHLDCopy*astarBrutes : astarBrute) {
			astarBrutes->SetWallCheck(true);
			astarBrutes->GetMouseCursor(position);

		}
	}

}


