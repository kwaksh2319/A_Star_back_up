#include"stdafx.h"
#include"HLDMath.h"

HLDMath::HLDMath()
	:alpa(1.0f), XPoint(0.0f,0.0f), YPoint(0.0f, 0.0f)
{
	//alpa = 0.0f;
}

HLDMath::~HLDMath()
{
}
//(x-x1)(x-x2)+(y-y1)(y-y2)=0
D3DXVECTOR2 HLDMath::GetAlpa(D3DXVECTOR2 player, D3DXVECTOR2 weapon,float speeds)
{
	//speeds

	speeds = 600.0f;
	//this->setPosition(pos); // 이동한 위치 저장

	float pi2 = D3DX_PI * 2; //파이
	static float Rad=1.0f;
	//D3DXVec2Normalize(&Rad, &weapon);
	float diff = atan2f(player.y - weapon.y, player.x - weapon.x)-Rad;
	static float vrad = 0.05f;//0.08f;

	while (diff < -D3DX_PI) diff += pi2;
	while (diff >= D3DX_PI) diff -= pi2;//* Time::Delta();

	if (abs(diff) < vrad){
		Rad += diff;// *Time::Delta();
	}
	else {
		Rad += (diff < 0 ? -vrad : vrad);
	}

	weapon.x += cos(Rad)*speeds *Time::Delta();
	weapon.y += sin(Rad)*speeds*Time::Delta();
	
	return weapon;
}

D3DXVECTOR2 HLDMath::Normalize(D3DXVECTOR2 val)
{
	
	float vector=pow(val.x, 2) + pow(val.y, 2);
	float normValue = abs(sqrt(vector));

	D3DXVECTOR2 input = D3DXVECTOR2(val.x / normValue, val.y / normValue);


	return input;
}

D3DXVECTOR2 HLDMath::GetPosition(float alp, D3DXVECTOR2 player, D3DXVECTOR2 weapon)
{
	return D3DXVECTOR2();
}

void HLDMath::Render()
{
	//ImGui::LabelText();
}
