#include"stdafx.h"
#include"Bullet.h"


Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
	:scale(1,1),rotation(0,0,0)
{
	wstring textureFile = Textures + L"bullet.png";
	clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(textureFile,shaderFile,37,1,55,18),0.3f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 117, 7, 55, 10), 0.3f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 37, 116, 53, 133), 0.3f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 204, 100, 220, 126), 0.3f);

	position = start;
	clip->Position(position);
	clip->Play();


}

Bullet::~Bullet()
{
	SAFE_DELETE(clip);

}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (Key->Press('I'))
		position.y += 200.0f*Time::Delta();
	else if(Key->Press('K'))
		position.y -= 200.0f*Time::Delta();
	else if (Key->Press('L'))
		position.x += 200.0f*Time::Delta();
	else if (Key->Press('J'))
		position.x -= 200.0f*Time::Delta();

	clip->Position(position);
	clip->Update(V,P);
}

void Bullet::Render()
{
	
	ImGui::Separator();
	ImGui::SliderFloat2("Bullet Scale", (float*)&scale, 1, 5);
	ImGui::SliderFloat3("Bullet rotation", (float*)&rotation, -179.9, 179.9);

	clip->Scale(scale);
	clip->Rotation(rotation);

	clip->Render();

	clip->DrawBound(true);

}
