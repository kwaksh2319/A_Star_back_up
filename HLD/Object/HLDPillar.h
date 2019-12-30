#pragma once


class HLDPilar
{
private:
	Animation* 	pilarEffect;
	Sprite*pilar;
	D3DXVECTOR2 position;
	bool bClosed;

public:
	HLDPilar(D3DXVECTOR2 position, D3DXVECTOR2 size = D3DXVECTOR2(1, 1));
	~HLDPilar();

	void Update(D3DXMATRIX V, D3DXMATRIX P);
	void Render();

	Sprite* GetSprite();
	Sprite* GetSpriteAni();

	void Position(D3DXVECTOR2 vec) { position = vec; }
	D3DXVECTOR2 Position() { return position; }


};