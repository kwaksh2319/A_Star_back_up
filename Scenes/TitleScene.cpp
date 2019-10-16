#include"stdafx.h"
#include"TitleScene.h"





TitleScene::TitleScene(SceneValues * values)
	:Scene(values)   //�θ� ������ �ʱ�ȭ 
{
	wstring textureFile = Textures + L"./Sonic/TitleScreen.png";
	wstring shaderFile = Shaders+L"./Effect.fx";
	
	sky = new Sprite(textureFile, shaderFile, 13, 193, 332, 195);
	sky->Scale(2.6f, 300.0f);
	sky->Position(0, -110);

	island = new Sprite(textureFile, shaderFile, 13, 195, 332, 241);
	island->Scale(2.6f, 2.8f);
	island->Position(0, -230);

	badge = new Sprite(textureFile, shaderFile, 180, 0, 370, 117);
	badge->Scale(2.6f, 2.8f);
	badge->Position(0, -80);
	//Sonic
	{
		sonic = new Clip(PlayMode::END);
		sonic->AddFrame(new Sprite(textureFile, shaderFile, 0, 56, 54, 111), 0.0f);
		sonic->AddFrame(new Sprite(textureFile, shaderFile, 0, 112, 56, 166), 0.3f);
		sonic->AddFrame(new Sprite(textureFile, shaderFile, 0, 0, 56, 53), 0.3f);
		sonic->AddFrame(new Sprite(textureFile, shaderFile, 56, 0, 114, 56), 0.3f);
		sonic->AddFrame(new Sprite(textureFile, shaderFile, 0, 56, 54, 111), 0.3f);
		sonic->Play();
		sonic->Position(50, -5);
		sonic->Scale(2.2f, 2.2f);
	}
	//tales
	{
		tales = new Clip(PlayMode::END);
		tales->AddFrame(new Sprite(textureFile, shaderFile, 114, 0, 154, 44), 0.2f);
		tales->AddFrame(new Sprite(textureFile, shaderFile, 0, 0, 1, 1), 1.5f);
		tales->AddFrame(new Sprite(textureFile, shaderFile, 54, 103, 99, 148), 0.2f);
		tales->AddFrame(new Sprite(textureFile, shaderFile, 113, 46, 157, 85), 0.2f);
		tales->AddFrame(new Sprite(textureFile, shaderFile, 54, 57, 102, 102), 0.2f);
		tales->AddFrame(new Sprite(textureFile, shaderFile, 133, 122, 173, 166), 0.2f);
		tales->AddFrame(new Sprite(textureFile, shaderFile, 114, 0, 154, 44), 0.2f);
		tales->Play();
		tales->Position(-50, -15);
		tales->Scale(2.2f, 2.2f);

	}


}

TitleScene::~TitleScene()
{
	SAFE_DELETE(island);
	SAFE_DELETE(sky);
	SAFE_DELETE(badge);
	SAFE_DELETE(sonic);
	SAFE_DELETE(tales);
	

}

void TitleScene::Update()
{
	D3DXMATRIX V;
	D3DXMatrixIdentity(&V);
	D3DXMATRIX P=values->Projection;

	sky->Update(V, P);
	island->Update(V, P);
	badge->Update(V, P);
	sonic->Update(V, P);
	tales->Update(V, P);

	
}

void TitleScene::Render()
{
	sky->Render();
	island->Render();
	badge->Render();
	sonic->Render();
	tales->Render();
	
}
