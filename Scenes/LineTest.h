#pragma once
#include "Scene.h"

class LineTest : public Scene
{
private:
	vector<class Line*> lines;
	vector<pair<D3DXVECTOR2, D3DXVECTOR2>> linePoints;
	vector<class Ring*> rings;
	vector<D3DXVECTOR2> ringPoints;
	vector<class Fish*> fishes;
	vector<D3DXVECTOR2> fishPoints;

	Sprite* background;

	D3DXVECTOR2 mouse;
	D3DXVECTOR2 cameraPos;
	D3DXVECTOR2 position; //최종 마우스 포지션(WinAPI -> DX)

	D3DXVECTOR2 lastPosition;

private:
	void EditLine();
	void EditRing();
	void EditFish();
	void RenderImGui();

public:
	LineTest(SceneValues* values);
	~LineTest();

	void Update() override;
	void Render() override;

};