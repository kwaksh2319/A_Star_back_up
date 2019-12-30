#pragma once
class HLDLaser {

private:

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
 	float radian;
	float laserScale;
	float laserPosDelta;
	float laserYDelta;
	Animation* laser;
	bool bCheckStart;
	bool bCheckEnd;
	float delta;


public:

	HLDLaser(D3DXVECTOR2 pos);
	~HLDLaser();

	void Position(float x,float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; };

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x, float y,float z);
	void Rotation(D3DXVECTOR3 val);
	D3DXVECTOR3 Rotation() { return rotation; }

	void Update(D3DXMATRIX&V, D3DXMATRIX&P);
	void Render();
	bool EndLaser();

	void StartLaser(bool val);
	void GetRaindan(float rad);
	Sprite *GetSprite();
};