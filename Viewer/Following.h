#pragma once
#include"IFollow.h"
#include"Camera.h"
class Following :public Camera {

private:
	IFollowing* focus;

public:

	Following(IFollowing* focus=NULL);//NULL�� ���������� ���������� ũ��.

	~Following();

	void Change(IFollowing* focus);//event appear move focus camera
	void Update() override;

};