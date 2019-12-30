#pragma once
class HLDMath {
	float alpa;

	D3DXVECTOR2 XPoint;
	D3DXVECTOR2 YPoint;
	float answer;

public:
	HLDMath();
	~HLDMath();
	D3DXVECTOR2 GetAlpa(D3DXVECTOR2 player, D3DXVECTOR2 weapon,float speeds);
	D3DXVECTOR2  Normalize(D3DXVECTOR2 val);

	D3DXVECTOR2 GetPosition(float alp,D3DXVECTOR2 player, D3DXVECTOR2 weapon);
	void Render();
};