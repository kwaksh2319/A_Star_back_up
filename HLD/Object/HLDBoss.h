#pragma once
enum class State{ Idle ,Appear, ReadyCollision, OnCollision,OffCollsion,EndCollision,CastShot,Laser,Disappear
};
class HLDBoss {
	
private:
	
	Animation*boss;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 playerPoint;
	State state;
	int bColliCount;
	bool bCollision;
	float moveSpeed;
	float reflectSpeed;
	float readySpeedx;
	float readySpeedy;
	D3DXVECTOR2 tmpPlayerDir;
	D3DXVECTOR2 tmpNowPos;
	float comDegreeLeft;
	float comDegreeRight;
	float comDegree;
	bool bCheckMove;
	bool bCheckBullet;
	D3DXVECTOR2 backgroundPoints[4];
	float tmpDeltaX;
	float tmpDeltaY;
	D3DXVECTOR2 tmpDir;
	D3DXVECTOR2 bulletRad;
	float laserRad;
	float laserRadDelta;
	vector<class HLDCastBullet*> bullet;
	vector<class HLDCastBullet*> bullet2;
	class HLDhp*hp;
	class HLDLaser *laser;
	int castCount;
	bool bCheckCastShot;

	int castCount2;
	bool bCheckBullet2;
	float bulletTime;
	bool bCheckCollisionSword;
	bool bCheckCollisionSlash;
	D3DXVECTOR2 hpBarPoint;
	Sprite*tmpBackg;
public:

	HLDBoss(D3DXVECTOR2 pos);
	~HLDBoss();
	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();


	void GetPlayerPoint(D3DXVECTOR2 val);
	void GetBackgroundPoint(D3DXVECTOR2 val[]);
	void GetBackGroundCollision(bool val);
	
	void CheckRangeMove();

	void GetCollisionSword(bool val);
	void GetCollisionSlash(bool val);
	void GetHpBarPoint(D3DXVECTOR2 val);
	Sprite*GetSprite();
	
	void Pattern();
	void Cast();
	void LaserDir();

	
};