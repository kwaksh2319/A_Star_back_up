#pragma once
#include <bitset>
/*
bool type�� ���� �ڷᱸ��
set() : bit�� ��� 1�� ����
reset() : bit�� ��� 0���� ����
set(i, value) : i��° ���� value�� ����
[] �迭 ���·� ���� ���� ex) bit[10] = false;
flip() : bit���� 1<->0
all() : ��� bit�� 1�� �� true ��ȯ
none() : ��� bit 0�� �� true ��ȯ
any() : 1���� 1�̸� true ��ȯ
count() : ���� 1�� ���õ� ��Ʈ�� ���� ��ȯ
*/

#define KEYMAX 256

class Keyboard
{
private:
	//Ű�� ������ �� true, �ȴ����� false
	bitset<KEYMAX> up; // bool up[KEYMAX]
	bitset<KEYMAX> down;

public:
	Keyboard();
	~Keyboard();

	bool Down(int key);
	bool Up(int key);
	bool Press(int key);
	bool Toggle(int key);

};