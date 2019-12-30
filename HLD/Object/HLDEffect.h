#pragma once
class HLDEffect {

private:
	Animation*effect;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	D3DXVECTOR3 rotation;




public:

	HLDEffect(D3DXVECTOR2 pos,D3DXVECTOR2 size);
	~HLDEffect();
	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x,float y,float z);
	void Rotation(D3DXVECTOR3 rota);
	
	

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();

	Sprite* GetSprite();








};