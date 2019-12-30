#pragma once
class HLDBrute {

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	Animation *brute;
	vector<D3DXVECTOR2> bFSway;
	vector<D3DXVECTOR2> aStarWay;
	bool bColCheck;
	bool bRangeCheck;
	float hitCount;
private:
	void BFSUpdate();
	void AstarUpdate();
	void Reset();
public:
	HLDBrute(D3DXVECTOR2 pos);
	~HLDBrute();

	void Update(D3DXMATRIX V, D3DXMATRIX P);
	void Render();


	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }



	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }
	void BFSGetWay(vector<D3DXVECTOR2> wayVal) { bFSway = wayVal; };
	void AStarGetWay(vector<D3DXVECTOR2> wayVal) { aStarWay = wayVal; };
	Sprite* GetSprite();
	void GetCollision(bool val) { bColCheck = val; }
	void GetRangeCollision(bool val) { bRangeCheck = val; }

};