#pragma once
class HLDStreetLamp {

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	Sprite*streetLamp;


public:

	HLDStreetLamp(D3DXVECTOR2 pos);
	~HLDStreetLamp();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }



	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();

	Sprite*GetSprite();






};