#pragma once
class Fish {

private:
	Animation *fish;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 start;
	float speed;

	bool bCollision;
	bool bAlive;

	bool bVisible;



public:

	Fish(D3DXVECTOR2 position);
	~Fish();

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();

	Sprite* GetSprite();
	void Collision(bool val) { bCollision = val; }
	bool Collision() { return bCollision; }

	void Alive(bool val) { bAlive = val; }
	bool Alive() { return bAlive; }

	void Visible(bool val) { bVisible = val; }
	bool Visible() { return bVisible; }

	void Position(D3DXVECTOR2 val) { position = val; }
	D3DXVECTOR2 Position() { return position; }


};