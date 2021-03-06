#pragma once
#include"./Viewer/IFollow.h"
class Player: public IFollowing { //플레이어 어케스팅 가능

private:
	float moveSpeed;
	Animation* animation;
	D3DXVECTOR2 focusOffset;

public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();
	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	Sprite* GetSprite();
};