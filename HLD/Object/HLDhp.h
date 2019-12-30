#pragma once
class HLDhp {

private:
	Sprite*hp;
	Sprite*hpBar;

	D3DXVECTOR2 hpPoint;
	D3DXVECTOR2 hpScale;

	D3DXVECTOR2 barPoint;
	D3DXVECTOR2 barScale;

	
	


public:

	HLDhp();
	~HLDhp();


	void HpPosition(float x, float y);
	void HpPosition(D3DXVECTOR2 val);
	D3DXVECTOR2 HpPosition() { return hpPoint; }

	void HpBarPosition(float x, float y);
	void HpBarPosition(D3DXVECTOR2 val);
	D3DXVECTOR2 HpBarPosition() { return barPoint; }



	void HpScale(float x, float y);
	void HpScale(D3DXVECTOR2 val);
	D3DXVECTOR2 HpScale() { return hpScale; }

	void HpBarScale(float x, float y);
	void HpBarScale(D3DXVECTOR2 val);
	D3DXVECTOR2 HpBarScale() { return barScale; }

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();


};