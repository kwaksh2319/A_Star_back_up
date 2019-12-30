#pragma once

enum class DirectionWeapon
{
	End, Up, Down, Left, Right, LeftUp, LeftDown, RightUp, RightDown, EndUp, EndDown, EndLeft, EndRight, Attack, AttackUp, AttackDown, AttackRight, AttackLeft
};

class HLDWeapon {

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 playerPoint;
	Sprite *sword;
	class HLDMath* math;
	float swordSpeed;
	float angle;
	float angleSpeed;
	bool bCheck;
	bool bCheckBack;

	bool bCheckUpYaxis;
	bool bCheckDownYaxis;
	bool bCheckUpXaxis;
	bool bCheckDownXaxis;


	bool bCheckUp;
	bool bCheckDown;
	bool bCheckLeft;
	bool bCheckRight;
	bool bReturnWeapon;
	DirectionWeapon dir;

public:
	HLDWeapon(D3DXVECTOR2 pos,D3DXVECTOR2 size);
	~HLDWeapon();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3 val);
	D3DXVECTOR3 Rotation() { return rotation; }
	void GetPlayerBool(bool bC);
	void GetCollisionPlayerBool(bool check);
	void GetDirection(DirectionWeapon d);
	void GetPlayerPos(D3DXVECTOR2 pos);

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();
	void StartMoveWeapon(bool val);

	Sprite*GetSprite();

	



};