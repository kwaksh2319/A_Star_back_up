#pragma once
#include"HLD/FindPath/NodeHLD.h"



class BFSNodePathHLD :NodeHLD {
private:
	D3DXVECTOR2 playerPos;
	D3DXVECTOR2 monsterPos;
	
	vector<pair<Rect*, tagNode>>savePos;
	vector<D3DXVECTOR2>posCheck;
	vector<pair<Rect*, tagNode>> input;
	vector<pair<Rect*, tagNode>>getPos;
	pair<Rect*, tagNode> nodes[HeightNode][WidthNode];
	D3DXVECTOR2 ptMouse;
	bool bWallCheck;
	int startX, startY;
private:

	void SetStart(D3DXVECTOR2 pos);
	void SetGoal();
	void SetWall();
	void FindPath();
	void SetRoad();

public:
	BFSNodePathHLD(D3DXVECTOR2 position, D3DXVECTOR2 size = D3DXVECTOR2(1, 1), D3DXCOLOR color = D3DXCOLOR(0xff555566));
	~BFSNodePathHLD();
	D3DXVECTOR2  GetPlayerPos(D3DXVECTOR2 pos) { return playerPos= pos; }

	void  GetMonsterPos(D3DXVECTOR2 pos) { monsterPos = pos; }
	void GetMouseCursor(D3DXVECTOR2 pos) { ptMouse = pos; }
    void  SetBFSPosition(vector<pair<Rect*, tagNode>>Pos);
	vector<D3DXVECTOR2>  GetBFSPosition();
	void BFSNode(D3DXVECTOR2 playerPos, D3DXVECTOR2 monsterPos, int indexX, int indexY);
	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();
	vector<D3DXVECTOR2>  ReturnPosition() {return posCheck;}
	void SetWallCheck(bool bCheck) { bWallCheck = bCheck; }
	
};