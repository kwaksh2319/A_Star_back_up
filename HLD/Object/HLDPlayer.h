#pragma once
#include "./Viewer/IFollow.h"
enum class Direction
{
	End,Up,Down,Left,Right,LeftUp,LeftDown,RightUp,RightDown,EndUp,EndDown,EndLeft,EndRight, Attack,AttackUp,AttackDown,AttackRight,AttackLeft
};
enum class AttackDirection {
	None,North,South,East,west
};
class HLDPlayer : public IFollowing {



private:

	D3DXVECTOR2 position;
	D3DXVECTOR2 alterPosition[3];
	D3DXVECTOR2 scale;
	D3DXVECTOR2 focusOffset;
	D3DXVECTOR2 backgroundSize;
	D3DXVECTOR2 backgroundPoint;
	D3DXVECTOR2 defaultCameraPoint;
	Animation *player;

	
		
	class HLDEffect *slash;
	class HLDWeapon *sword;
	vector<class HLDAlter*>alter;
	float moveSpeed;
	float interval[3];
	float intervalDelta[3];
	float moveMinSpeed;
	float swordSpeed;
	Direction dir;
	AttackDirection aDir;
	float rt;
	bool bCheck;
	bool bSwordCheck;
	float angleSwordSpeed;
	bool shootWeapon;
	bool bCheckBackground;
	bool bCheckWall;
	bool bCheckStage01;
	bool bCheckBrute;
	bool bCheckDash;
	vector<bool>bCheckWalls;
	//bool bCheckSlash;
	
private:
	void KeyDirection();
	void RotationWeapon();
public:

	HLDPlayer(D3DXVECTOR2 pos);
	~HLDPlayer();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }
	
	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();

	void Focus(D3DXVECTOR2 *position, D3DXVECTOR2 *size);
	void GetBackgroundCollision(bool val);
	Sprite*GetSprite();

	Sprite*GetSlash();
	Sprite*GetSword();
	void GetCollision(bool val);
	void GetBruteCollision(bool val);
	void GetBackgroundData(D3DXVECTOR2 size, D3DXVECTOR2 backPoint);
	void GetWallCollision(bool val);
	void SetWallCollision(bool val,int count);
	Direction AttackDir(Direction dir, bool bCheckDown, bool bCheckLeft, bool bCheckRight, bool bCheckUp);
	
	//D3DXVECTOR2 cameraPosHp(D3DXVECTOR2 val) { return defaultCameraPoint= val; }
	void GetStageBool(bool val);
	//	void GetSlashBool(bool val);
	





};