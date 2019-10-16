#include "stdafx.h"
#include "Node.h"

#define Inf 2147483648
#define WidthNode 15
#define HeightNode 12

#define Nodes nodes[y][x]

Node::Node(D3DXVECTOR2 position, D3DXVECTOR2 size, D3DXCOLOR color)
	:nodeType(NodeType::None), color(color)
	, startX(0), startY(0), goalX(0), goalY(0)
	, ptMouse(0, 0)
	, startPos(0, 0), goalPos(0, 0), bReadyToMove(false)
{
	wstring shaderFile = Shaders + L"Rect.fx";

	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			float positionX = x * size.x - Width * 0.5f;
			float positionY = y * size.y - Height * 0.5f;

			Nodes.first = new Rect(shaderFile, D3DXVECTOR2(positionX, positionY), size);
			Nodes.second.start = false;
			Nodes.second.goal = false;
			Nodes.second.wall = false;
			Nodes.second.f = Inf;
			Nodes.second.g = Inf;
			Nodes.second.h = Inf;
			Nodes.second.close = false;
			Nodes.second.parent.x = Inf;
			Nodes.second.parent.y = Inf;

		}
	}

}

Node::~Node()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			SAFE_DELETE(Nodes.first);
		}
	}
}

void Node::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			Nodes.first->Update(V, P);
		}
	}

	//���ư : ���� + �� ����, �޹�ư : ��ֹ� ����
	if (bReadyToMove)
	{
		nodeType = NodeType::Start;
		bReadyToMove = false;
		SetStart();
	}
	else if (bReadyToMove == false)
		nodeType = NodeType::None;

	if (Mouse->Down(1))
		nodeType = NodeType::Goal;
	else if (Mouse->Up(1))
		nodeType = NodeType::None;

	if (Mouse->Down(0))
		nodeType = NodeType::Wall;
	else if (Mouse->Up(0))
		nodeType = NodeType::None;

	if (Key->Down(VK_ESCAPE))
		Reset();

	switch (nodeType)
	{
	case NodeType::Start:	SetStart();		break;
	case NodeType::Goal:	SetGoal();		break;
	case NodeType::Wall:	SetWall();		break;
	}

	//��ã�� ����
	if (Key->Down(VK_SPACE))
		FindPath();
}

void Node::Render()
{


	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			//������ : ���
			if (Nodes.second.start == true)
			{
				Nodes.first->Color(1, 1, 0);
			}

			//������ : �ʷ�
			else if (Nodes.second.goal == true)
			{
				Nodes.first->Color(0, 1, 0);
			}

			//�� : ����
			else if (Nodes.second.wall == true)
			{
				Nodes.first->Color(1, 0, 0);
			}

			//���� : �Ķ�
			else if (Nodes.second.close == true)
			{
				Nodes.first->Color(0, 0, 1);
			}
		}
	}

	//�� : �Ͼ��
	for (UINT i = 0; i < way.size(); i++)
	{
		nodes[way[i].y][way[i].x].first->Color(1, 1, 1);
	}

	RenderText();

	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			Nodes.first->Render();
		}
	}

}

UINT Node::FindH(int startY, int startX, int goalY, int goalX)
{
	int Wdistance;
	int Hdistance;
	int distance;

	Wdistance = abs(startX - goalX);
	Hdistance = abs(startY - goalY);

	return (Wdistance + Hdistance) * 10;
}

void Node::Reset()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			Nodes.second.start = false;
			Nodes.second.goal = false;
			Nodes.second.wall = false;
			Nodes.second.f = Inf;
			Nodes.second.g = Inf;
			Nodes.second.h = Inf;
			Nodes.second.close = false;
			Nodes.second.parent.x = Inf;
			Nodes.second.parent.y = Inf;
			Nodes.first->Color(0, 0, 0);
		}
	}

	way.clear();
	nodeType = NodeType::None;

}

D3DXVECTOR2 Node::Position()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (Rect::PtInRect(Nodes.first, ptMouse))
			{
				return Nodes.first->Position();
			}
		}
	}

	return D3DXVECTOR2(1, 1);
}



void Node::RenderText()
{
}

void Node::SetStart()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (Rect::PtInRect(Nodes.first, startPos))
			{
				Nodes.second.start = true;
				Nodes.second.g = 0;
				startX = x;
				startY = y;
			}
			else
			{
				Nodes.second.start = false;
			}
		}
	}
}

void Node::SetGoal()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (Rect::PtInRect(Nodes.first, ptMouse))
			{
				Nodes.second.goal = true;
				goalX = x;
				goalY = y;
			}
			else
			{
				Nodes.second.goal = false;
			}
		}
	}
}

void Node::SetWall()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (Rect::PtInRect(Nodes.first, ptMouse))
			{
				Nodes.second.wall = true;
			}
		}
	}
}

void Node::FindPath()
{
	int count = 0;

	//���� ��� H
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			Nodes.second.h = FindH(y, x, goalY, goalX);
		}
	}

	//�ּҰ� �˻� ���� minF
	while (true)
	{
		//�˻� ȸ���� ��ü ��󺸴� ������ �ݺ��� Ż��
		if (count == HeightNode * WidthNode)
		{
			break;
		}

		count++;

		//F  = G + H
		for (UINT y = 0; y < HeightNode; y++)
		{
			for (UINT x = 0; x < WidthNode; x++)
			{
				if (Nodes.second.g != Inf)
				{
					Nodes.second.f = Nodes.second.h + Nodes.second.g;
				}
			}
		}

		//�˻� ��� ���� -> �ε��� ����
		POINT min;
		int count2 = 0;
		for (UINT y = 0; y < HeightNode; y++)
		{
			for (UINT x = 0; x < WidthNode; x++)
			{
				if (Nodes.second.f &&
					Nodes.second.wall == false &&
					Nodes.second.close == false)
				{
					min.x = x;
					min.y = y;
					break;
				}
				count2++;
			}
		}

		//��ü�� State�� �ʹ� ���� �˻��ϸ� �ݺ��� ����
		if (count2 == WidthNode * HeightNode)
		{
			break;
		}

		//minF �� ���
		for (UINT y = 0; y < HeightNode; y++)
		{
			for (UINT x = 0; x < WidthNode; x++)
			{
				if (nodes[min.y][min.x].second.f >= Nodes.second.f &&
					Nodes.second.wall == false &&
					Nodes.second.close == false)
				{
					min.y = y;
					min.x = x;
				}
			}
		}

		///�ֺ� ����� g�� ���

		//����
		if (min.x != 0)
		{
			if (nodes[min.y][min.x - 1].second.g > 10 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y][min.x - 1].second.g = 10 + nodes[min.y][min.x].second.g;
				nodes[min.y][min.x - 1].second.parent.x = min.x;
				nodes[min.y][min.x - 1].second.parent.y = min.y;
			}
		}

		//������
		if (min.x != WidthNode - 1)
		{
			if (nodes[min.y][min.x + 1].second.g > 10 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y][min.x + 1].second.g = 10 + nodes[min.y][min.x].second.g;
				nodes[min.y][min.x + 1].second.parent.x = min.x;
				nodes[min.y][min.x + 1].second.parent.y = min.y;
			}
		}

		//��
		if (min.y != 0)
		{
			if (nodes[min.y - 1][min.x].second.g > 10 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y - 1][min.x].second.g = 10 + nodes[min.y][min.x].second.g;
				nodes[min.y - 1][min.x].second.parent.x = min.x;
				nodes[min.y - 1][min.x].second.parent.y = min.y;
			}
		}

		//�Ʒ�
		if (min.y != HeightNode - 1)
		{
			if (nodes[min.y + 1][min.x].second.g > 10 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y + 1][min.x].second.g = 10 + nodes[min.y][min.x].second.g;
				nodes[min.y + 1][min.x].second.parent.x = min.x;
				nodes[min.y + 1][min.x].second.parent.y = min.y;
			}
		}

		//�»�
		if (min.x != 0 && min.y != 0)
		{
			if (nodes[min.y - 1][min.x].second.wall == true &&
				nodes[min.y][min.x - 1].second.wall == true)
			{
				//
			}
			else if (nodes[min.y - 1][min.x - 1].second.g > 14 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y - 1][min.x - 1].second.g = 14 + nodes[min.y][min.x].second.g;
				nodes[min.y - 1][min.x - 1].second.parent.x = min.x;
				nodes[min.y - 1][min.x - 1].second.parent.y = min.y;
			}
		}

		//����
		if (min.x != 0 && min.y != HeightNode - 1)
		{
			if (nodes[min.y + 1][min.x].second.wall == true &&
				nodes[min.y][min.x - 1].second.wall == true)
			{
				//
			}
			else if (nodes[min.y + 1][min.x - 1].second.g > 14 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y + 1][min.x - 1].second.g = 14 + nodes[min.y][min.x].second.g;
				nodes[min.y + 1][min.x - 1].second.parent.x = min.x;
				nodes[min.y + 1][min.x - 1].second.parent.y = min.y;
			}
		}

		//���
		if (min.x != WidthNode - 1 && min.y != 0)
		{
			if (nodes[min.y - 1][min.x].second.wall == true &&
				nodes[min.y][min.x + 1].second.wall == true)
			{
				//
			}
			else if (nodes[min.y - 1][min.x + 1].second.g > 14 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y - 1][min.x + 1].second.g = 14 + nodes[min.y][min.x].second.g;
				nodes[min.y - 1][min.x + 1].second.parent.x = min.x;
				nodes[min.y - 1][min.x + 1].second.parent.y = min.y;
			}
		}

		//����
		if (min.x != WidthNode - 1 && min.y != HeightNode - 1)
		{
			if (nodes[min.y + 1][min.x].second.wall == true &&
				nodes[min.y][min.x + 1].second.wall == true)
			{
				//
			}
			else if (nodes[min.y + 1][min.x + 1].second.g > 14 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y + 1][min.x + 1].second.g = 14 + nodes[min.y][min.x].second.g;
				nodes[min.y + 1][min.x + 1].second.parent.x = min.x;
				nodes[min.y + 1][min.x + 1].second.parent.y = min.y;
			}
		}

		//minF ���̻� �˻����� ����
		nodes[min.y][min.x].second.close = true;

		//�� �����
		if (nodes[min.y][min.x].second.goal == true)
		{
			//�˻縦 ������ ����� ��ġ�� ����
			POINT tempPoint;
			tempPoint.y = min.y;
			tempPoint.x = min.x;

			//�θ� ����� ��ġ�� ����(1)
			POINT tempPoint2;

			while (true)
			{
				//�θ� ����� ��ġ�� ����(2)
				tempPoint2.y = nodes[tempPoint.y][tempPoint.x].second.parent.y;
				tempPoint2.x = nodes[tempPoint.y][tempPoint.x].second.parent.x;

				//�˻� ����̾��� ��带 �θ�� ����
				tempPoint.y = tempPoint2.y;
				tempPoint.x = tempPoint2.x;

				way.push_back(tempPoint);

				//������ �˻� ��󿡼� ����
				if (nodes[tempPoint.y][tempPoint.x].second.start == true)
					break;

				//�θ��� ���� �̻��� ��
				if (tempPoint.y == Inf)
				{
					Reset();
					break;
				}

				//���Ͱ� �Ѿ��� Ŀ�� ��
				if (way.size() == WidthNode * HeightNode)
				{
					Reset();
					break;
				}

			}

			break;
		}

	}
}
