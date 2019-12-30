#pragma once
class HLDRilfMan {

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 positionPlayer;
	D3DXVECTOR2 rilfManPos;
	Animation *rilfMan;
	bool bCheckCollision;
	bool bCheckRangeCollision;
	vector < D3DXVECTOR2 >bFSway;
	vector < D3DXVECTOR2 >aStarWay;
	vector<class HLDRilfmanBullet*>bullet;
	float bulletSpeed;
	float rilfManX;
	float rilfManY;
	float hitCount;
	
	bool bCheckBulletDirection;
	bool tmpbCheck;
	bool bStop;
   
	bool bCheckStop;
private:
	void BFSUpdate();
	void AstarUpdate();
public:
	HLDRilfMan(D3DXVECTOR2 pos);
	~HLDRilfMan();

	void Update(D3DXMATRIX V, D3DXMATRIX P);
	void Render();

	
	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }



	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void BFSGetWay(vector<D3DXVECTOR2> wayVal) { bFSway = wayVal; };

	void AStarGetWay(vector<D3DXVECTOR2> wayVal) { aStarWay = wayVal; };
	
	Sprite* GetSprite();
	void GetCollision(bool val) { bCheckCollision = val; }
	void GetRangeCollision(bool val) { bCheckRangeCollision = val; }
	void GetStop(bool val) { bCheckStop = val; }
	void GetPlayerPosition(D3DXVECTOR2 val) { positionPlayer = val; }
	void BulletTime();
	void BulletDirection(float moveR, float moveL);
	void Reset();
	Sprite* GetBulletSprite(int i);


};