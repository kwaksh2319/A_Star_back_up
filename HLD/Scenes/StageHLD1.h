#pragma once
#include"./Scenes/Scene.h"
class Stage1HLD :public Scene
{


private:
	/*이미지 버튼*/
	vector<class TileMagma*> magmas;
	vector<D3DXVECTOR2> magmaPoint;
	Sprite*background;
	
	class AstarMonster* monster;
	class HLDPlayer *player;


	vector<class HLDPilar*> pilar;
	vector<class HLDCrystal*> crystal;
	vector<class HLDStreetLamp*>streetLamp;
	vector<class HLDTile01*>tile01;
	vector<class HLDTile02*>tile02;
	vector<class HLDRilfMan*> rilfMan;
	vector<class HLDBrute*> brute;
	vector<class BFSNodePathHLD*> bfsNode;//RilfMan
	vector<class BFSNodePathHLD*> bfsNodeBrute;//brute
	//vector<class NodeHLD*> astarRilfMan;
	vector<class NodeHLDCopy*> astarRilfMan;
	vector<class NodeHLDCopy*> astarBrute;
	vector<D3DXVECTOR2> pilarPoint;
	vector<D3DXVECTOR2> crystalPoint;
	vector<D3DXVECTOR2> streetLampPoint;
	vector<D3DXVECTOR2> tile01Point;
	vector<D3DXVECTOR2> tile02Point;
	vector<D3DXVECTOR2> rilfManPoint;
	vector<D3DXVECTOR2> brutePoint;
	vector<bool>bRangeRilfMan;
	vector<bool>bStopRilfMan;
	vector<bool>bCollisionRilfMan;
	vector<bool>bRangeBrute;
	vector<bool>bCollisionPilar;
	vector<bool>bCollisionCrystal;
	vector<bool>bCollisionStreetLamp;
	//class Player*metalSlug;

	Sprite*playerRect;
	Sprite*monsterRect;
	Sprite*backgroundRect;
	//class NodeHLD* node;
	class BFSNodePathHLD* bfs;
	class NodeHLDCopy*nodeTmp;
	D3DXVECTOR2 massSize;
	D3DXVECTOR2 massSizeBackground;

	D3DXVECTOR2 mouse;
	D3DXVECTOR2 cameraPos;
	D3DXVECTOR2 position;

	ID3D11ShaderResourceView*srv;
	bool bButton;
	bool bMove;
	bool bButtonCrystal;
	bool bButtonstreetLamp;
	bool bButtonTile01;
	bool bButtonTile02;
	bool bButtonRilfMan;
	bool bButtonBrute;
	bool bFindPathAstar;

	bool bCheckCollisionRilfMan;
	bool bCheckCollisionBrute;
	bool bCheckRangeRilfMan;
	bool bCheckRangeBrute;
	bool bCheckCollisionPlayer;
	bool bCheckState;

	float worldTime;
	bool bNext;

private:
	void EditPilar();
	void EditCrystal();
	void EditstreetLamp();
	void EditTile01();
	void EditTile02();
	void EditRilfMan();
	void EditBrute();


	void RenderImGui();
	void RenderDebbuging();

	void RenderImGuiSaveLoad();
	void RenderImGuiCrystal();
	void RenderImGuiPilar();
	void RenderImGuistreetLamp();
	void RenderImGuiTile01();
	void RenderImGuiTile02();
	void RenderImGuiRilfMan();
	void RenderImGuiBrute();
	void RenderImGuiBFS();
	void RenderImGuIAstar();
	void RenderImGuiWall();
	

	void RenderSaveLoadImGuiPilar();
	void RenderSaveLoadImGuiCrystal();
	void RenderSaveLoadImGuiStreetLamp();
	void RenderSaveLoadImGuiTile01();
	void RenderSaveLoadImGuiTile02();
	void RenderSaveLoadImGuiRilfMan();
	void RenderSaveLoadImGuiBrute();

	void RilfManCreateBFS();
	void BruteCreateBFS();
	void RilfManCreateAstar();
	void BruteCreateAstar();
	void RilfManWall();
	void BruteWall();

	void CheckRilfManCollision();
	void CheckBruteManCollision();
	void CheckSlashRilfMan();
	void CheckSlashBrute();
	void CheckPlayerBrute();
	void CheckPlayerBullet();
	

public:
	Stage1HLD(SceneValues* values);
	~Stage1HLD();


	void Update() override;
	void Render() override;
	void BFSupdate(D3DXMATRIX &V, D3DXMATRIX &P);
	void AstarUpdate(D3DXMATRIX &V, D3DXMATRIX &P);
	void UpdateWall();
	void GetStageState(bool val) { bCheckState = val; };
	bool NextStage() { return bNext; }
	void CreatePotal();
	void CollisionWall();
	void CheckTile01();
};
