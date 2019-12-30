#pragma once

#define WidthNode 16
#define HeightNode 25

enum class NodeType { None, Start, Goal, Wall };

struct tagNode
{
	//node type
	bool start;
	bool goal;
	bool wall;

	//비용 계산
	float f;
	float g;
	float h;

	//검사
	bool close;
	D3DXVECTOR2 parent;
};

class NodeHLD
{
private:
	NodeType nodeType;
    class HLDgrid*grid;
	Rect* rect;
	bool bWallCheck;
	

	//pair<class HLDgrid*, tagNode> nodes[HeightNode][WidthNode];
	pair<Rect*, tagNode> nodes[HeightNode][WidthNode];
	D3DXCOLOR color;

	int startX, startY;
	int goalX, goalY;

	vector<POINT> way;
	vector<D3DXVECTOR2> RectPosition;
	//마우스
	D3DXVECTOR2 ptMouse;

	//플레이어, 몬스터 위치
	D3DXVECTOR2 startPos;
	D3DXVECTOR2 goalPos;

	//
	bool bReadyToMove;

private:
	void RenderText();

	void SetStart();
	void SetGoal();
	void SetWall();

	void FindPath();


public:
	NodeHLD(D3DXVECTOR2 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXCOLOR color = D3DXCOLOR(0xff555566));
	~NodeHLD();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	UINT FindH(int startY, int startX, int goalY, int goalX);
	void Reset();

	void GetMouseCursor(D3DXVECTOR2 ptMouse) { this->ptMouse = ptMouse; }

	void GetStartPos(D3DXVECTOR2 start) { startPos = start; }
	void GetGoalPos(D3DXVECTOR2 goal) { goalPos = goal; }

	void ReadyToStart(bool val) { bReadyToMove = val; }
	bool ReadyToStart() { return bReadyToMove; }
	vector<D3DXVECTOR2> SetWay() { return RectPosition; }

	D3DXVECTOR2 Position();
	D3DXVECTOR2 SendToPtMoust() { return ptMouse; }
	void SetWallCheck(bool bCheck) { bWallCheck = bCheck; }

};