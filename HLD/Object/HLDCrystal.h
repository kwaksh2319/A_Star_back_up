#pragma once
class HLDCrystal {

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	Sprite*crystal;


public:

	HLDCrystal(D3DXVECTOR2 pos);
	~HLDCrystal();

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