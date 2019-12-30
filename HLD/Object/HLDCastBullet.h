#pragma once
class HLDCastBullet {

private:

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	Sprite*bullet;
	bool bCheckStart;
	float moveSpeed;
	D3DXVECTOR2 radian;

public:

	HLDCastBullet(D3DXVECTOR2 pos);
	~HLDCastBullet();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }
	void Update(D3DXMATRIX &V,D3DXMATRIX&P);
	void Render();
	void StartMove(bool val);
	void GetRaindan(D3DXVECTOR2 rad);
	
	Sprite*GetSprite();


};