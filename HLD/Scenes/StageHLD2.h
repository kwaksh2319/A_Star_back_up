#pragma once
#include"./Scenes/Scene.h"
class StageHLD2 :public Scene{
private:
	class HLDBoss *boss;

private:
	Sprite* background;
	class HLDPlayer *player;
	bool bCheckState;
	bool bNext;
	D3DXVECTOR2 getBackgroundPoint[4];

public:


	StageHLD2(SceneValues* values);
	~StageHLD2();


	void Update() override;
	void Render() override;
	void GetStageState(bool val) { bCheckState = val; }
	bool NextStage() { return bNext; }
	void SetBackgroundPoint();





};
