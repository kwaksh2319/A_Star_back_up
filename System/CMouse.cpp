#include "stdafx.h"
#include "CMouse.h"

CMouse::CMouse(HWND handle)
	:handle(handle), position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	ZeroMemory(buttonStatus, sizeof(short) * 8);
	ZeroMemory(buttonPrevStatus, sizeof(short) * 8);
	ZeroMemory(buttonMap, sizeof(Button) * 8);

	ZeroMemory(buttonCount, sizeof(int) * 8); //��� ���ȳ�.


	doubleClickTime = GetDoubleClickTime(); //OS�� ������ ����Ŭ�� Ÿ���� �о���� �Լ�
	startDoubleClickTime[0] = GetTickCount(); //OS�� ���õǰ� ������� �ð��� ms������ ���

	for (int i = 1; i < 8; i++)//0���� �־����ϱ� ����
		startDoubleClickTime[i] = startDoubleClickTime[0]; //GetTickCount�� ��� ����
}

CMouse::~CMouse()
{
}

void CMouse::WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (iMessage == WM_MOUSEMOVE)
	{
		position.x = (float)LOWORD(lParam);
		position.y = (float)HIWORD(lParam);
	}

	if (iMessage == WM_MOUSEWHEEL)
	{
		short temp = (short)HIWORD(wParam); //wparam!

		wheelPrevValue = wheelValue; //���� 0 + 0
		wheelValue += (float)temp; //wParam ��ŭ ����->��ũ�� ��ŭ ����
	}
}

void CMouse::Update()
{
	memcpy(buttonPrevStatus, buttonStatus, sizeof(byte) * 8); //������ ��ư ����[8](��,�ٿ�,������ ��) �迭�� ��°�� ���� ���·� ����

	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);

	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;	//��� �� �ܿ� ��ư�� �� ������..

	for (UINT i = 0; i < 8; i++) //��ư�� 8��
	{
		short prevStatus = buttonPrevStatus[i]; //��ư�� ���� ����(��,�ٿ�..)�� ���� ������ ��Ƽ�
		short currentStatus = buttonStatus[i]; //���� ���� ��ư�� current�� ����

		if (prevStatus == 0 && currentStatus == 1)
			buttonMap[i] = Button::Down;
		else if (prevStatus == 1 && currentStatus == 0)
			buttonMap[i] = Button::Up;
		else if (prevStatus == 1 && currentStatus == 1)
			buttonMap[i] = Button::Press;
		else
			buttonMap[i] = Button::None;
	}

	//����Ŭ��
	UINT buttonStatus = GetTickCount();
	for (UINT i = 0; i < 8; i++)
	{
		if (buttonMap[i] == Button::Down) //(3)Ư�� ��ư�� �������� �ִٸ�
		{
			if (buttonCount[i] == 1) //1�� ���� ���
			{
				//����Ŭ�� �ȵ�(�� �ʰ� ������) : �ؼ� - �ι�° ���� Ÿ�ӽ����� - ù��° ���� Ÿ�� ����Ʈ > ����Ŭ�� ���ð� 
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0; //���� ȸ���� 0���� �ٽ� �ʱ�ȭ
			}

			buttonCount[i]++; //(1)���� �ٿ� ���±� ������ 1�� ���� ���·� ���������ش�.

			if (buttonCount[i] == 1)
				startDoubleClickTime[i] = buttonStatus; //(2)���� ��ư�� ���� �ð��� ����
		}

		if (buttonMap[i] == Button::Up)
		{
			//���� �� �ٽ� Ȯ��(���� Ŭ���� dowon->up->down �����̹Ƿ� up������ �˻� ����)
			if (buttonCount[i] == 1)
			{
				//����Ŭ�� ����(�ð� �ʰ�)
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
			}
			//up�ð� ����
			else if (buttonCount[i] == 2) //�ι� ��������
			{

				if (buttonStatus - startDoubleClickTime[i] <= doubleClickTime)//����Ŭ�� ����
					buttonMap[i] = Button::DoubleClick;

				buttonCount[i] = 0; //�ٽ� ���� ȸ���� 0����
			}
		}
	}

	POINT point;
	GetCursorPos(&point);//���콺�� ��ġ(OS����..)
	ScreenToClient(handle, &point);//�츮 ȭ�鿡 �ݿ�

	wheelPrevValue = wheelValue;
	wheelMoveValue = wheelValue - wheelPrevValue;
}
