#pragma once
class HLDAlter {

private:
	Animation *alter;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
 	int number;


public:
	HLDAlter(D3DXVECTOR2 pos);
	~HLDAlter();


	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position();

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale();

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3 val);
	D3DXVECTOR3 Rotation();

	void GetPlayNum(int num);
	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();





};