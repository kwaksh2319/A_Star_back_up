#pragma once
class HLDTile01{

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	Animation *tile01;
	bool bCheckSearch;

public:
	HLDTile01(D3DXVECTOR2 pos);
	~HLDTile01();

	void Position(float x,float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }


	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();
	void GetSearchRange(bool val);
	Sprite*GetSprite();


};