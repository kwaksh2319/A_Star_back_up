#include "stdafx.h"
#include "NodeHLDCopy.h"
#include"./HLD/FindPath/HLDgrid.h"

#define Inf 2147483648
#define WidthNode 16
#define HeightNode 25

//#define Nodes nodes[y][x]
#define Nodes pointTmps[y][x]
NodeHLDCopy::NodeHLDCopy(D3DXVECTOR2 position, D3DXVECTOR2 rectScale,D3DXVECTOR2 size, D3DXCOLOR color)
	:nodeType(NodeTypes::None), color(color),rectSize(rectScale),positions(position),scales(size)
	, startX(0), startY(0), goalX(0), goalY(0)
	, ptMouse(0, 0)
	, startPos(0, 0), goalPos(0, 0), bReadyToMove(false), bWallCheck(false)
{
	wstring shaderFile = Shaders + L"Rect.fx";
	float positionX = 0 * rectSize.x - Width * 0.25f;
	float positionY = 0* rectSize.y - Height * 0.25f;
	grid=new HLDgrid(shaderFile, positions, D3DXVECTOR2(1.0f,1.0f));//D3DXVECTOR2(positionX, positionY)
	
	rect = new Rect(shaderFile, D3DXVECTOR2(positionX, positionY),rectScale);
	positionX = rect->Position().x;
	positionY = rect->Position().y;
	for (UINT y = 0; y < HeightNode; y++)
	{

		positionX = rect->Position().x;
		positionY = positionY + 80.0f*y;
		//positionY = rect->Position().y;
		for (UINT x = 0; x < WidthNode; x++)
		{
		//	float positionXx = x * rectSize.x - Width * 0.5f; //�簢�� ������ �־������
		//	float positionYy = y * rectSize.y - Height;
			positionX = positionX + 80.0f * x;
			
			Nodes.first=D3DXVECTOR2(positionX, positionY);
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
	/*
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			float positionX = x * size.x - Width*0.5f ;
			float positionY = y * size.y - Height ;

			//Nodes.first = new HLDgrid(shaderFile, D3DXVECTOR2(positionX, positionY), size);
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
	*/
}

NodeHLDCopy::~NodeHLDCopy()
{
	SAFE_DELETE(grid);
}

void NodeHLDCopy::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	

	grid->Update(V, P);
	//grid->Position(positions);
	//grid->Scale(scales);
	
		

	//���ư : ���� + �� ����, �޹�ư : ��ֹ� ����
	

	if (bReadyToMove)
		nodeType = NodeTypes::Goal;
	else if (!bReadyToMove)
		nodeType = NodeTypes::None;

	if (bWallCheck&&Mouse->Down(0))
		nodeType = NodeTypes::Wall;
	else if (Mouse->Up(0))
		nodeType = NodeTypes::None;

	if (Key->Down(VK_ESCAPE))
		Reset();

	
	switch (nodeType)
	{
	case NodeTypes::Start:			break;
	case NodeTypes::Goal:SetStart();	SetGoal();  FindPath(); bReadyToMove = false; break;
	case NodeTypes::Wall:	SetWall();		break;
	//case NodeTypes::None: Reset(); break;
	}
	
	//��ã�� ����
	//if (!bReadyToMove)
		
}

void NodeHLDCopy::Render()
{
	

	grid->Render();
	/*
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
				//Nodes.first->Color(0, 0, 1);
			}
		}
	}*/

	//�� : �Ͼ��
	/*
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
	*/



}

UINT NodeHLDCopy::FindH(int startY, int startX, int goalY, int goalX)
{
	int Wdistance;
	int Hdistance;
	//int distance;

	Wdistance = abs(startX - goalX);
	Hdistance = abs(startY - goalY);

	return (Wdistance + Hdistance) * 10;
}

void NodeHLDCopy::Reset()
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
			//Nodes.first->Color(0, 0, 0);
		}
	}

	way.clear();
	nodeType = NodeTypes::None;

}

D3DXVECTOR2 NodeHLDCopy::Position()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (PtInRect(Nodes.first, ptMouse))
			{
				return Nodes.first;
			}
		}
	}

	return D3DXVECTOR2(1, 1);
}

bool NodeHLDCopy::PtInRect(D3DXVECTOR2 rectPose, D3DXVECTOR2 target)
{
	float xScale = rectSize.x*0.5f;//rect->scale.x*0.5f;
	float yScale = rectSize.y*0.5f;//rect->scale.y*0.5f;

	float left = rectPose.x-xScale;    // rect->position.x - xScale;
	float right = rectPose.x - xScale; //rect->position.x + xScale;
	float bottom = rectPose.y - xScale; //rect->position.y - yScale;
	float top = rectPose.y - xScale; //rect->position.y + yScale;

	bool bCheck = true;

	bCheck &= ptMouse.x > left;
	bCheck &= ptMouse.x < right;
	bCheck &= ptMouse.y > bottom;
	bCheck &= ptMouse.y < top;


	return bCheck;
}

void NodeHLDCopy::GetRectSize(D3DXVECTOR2 size)
{
	rectSize = size;
}



void NodeHLDCopy::RenderText()
{
}

void NodeHLDCopy::SetStart()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (PtInRect(Nodes.first, startPos))
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

void NodeHLDCopy::SetGoal()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (PtInRect(Nodes.first, goalPos))
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

void NodeHLDCopy::SetWall()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (PtInRect(Nodes.first, ptMouse))
			{
				Nodes.second.wall = true;
			}
		}
	}
}

void NodeHLDCopy::FindPath()
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
				RectPosition.push_back(nodes[tempPoint.y][tempPoint.x].first->Position());

			}

			break;
		}

	}
}


