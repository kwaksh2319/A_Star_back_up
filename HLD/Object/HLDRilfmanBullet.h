#pragma once

class HLDRilfmanBullet {

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	Animation *bullet;
	float bulletSpeed;
	bool bCheck;


public:
	HLDRilfmanBullet(D3DXVECTOR2 pos, D3DXVECTOR2 scl);
	~HLDRilfmanBullet();


	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }
   
	
	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();
	void GetCheckRange(bool val) { bCheck = val; }
	
	Sprite*GetSprite();





};
