#include "stdafx.h"
#include "NodeHLD.h"
#include"./HLD/FindPath/HLDgrid.h"

#define Inf 2147483648
#define WidthNode 16
#define HeightNode 25

#define Nodes nodes[y][x]

NodeHLD::NodeHLD(D3DXVECTOR2 position, D3DXVECTOR2 size, D3DXCOLOR color)
	:nodeType(NodeType::None), color(color)
	, startX(0), startY(0), goalX(0), goalY(0)
	, ptMouse(0, 0)
	, startPos(0, 0), goalPos(0, 0), bReadyToMove(false), bWallCheck(false)
{
	wstring shaderFile = Shaders + L"Rect.fx";

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

}

NodeHLD::~NodeHLD()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			SAFE_DELETE(Nodes.first);
		}
	}
}

void NodeHLD::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			Nodes.first->Update(V, P);
		}
	}
	
	//우버튼 : 시작 + 골 세팅, 왼버튼 : 장애물 세팅
	

	if (bReadyToMove)
		nodeType = NodeType::Goal;
	else if (!bReadyToMove)
		nodeType = NodeType::None;

	if (bWallCheck&&Mouse->Down(0))
		nodeType = NodeType::Wall;
	else if (Mouse->Up(0))
		nodeType = NodeType::None;

	if (Key->Down(VK_ESCAPE))
		Reset();

	
	switch (nodeType)
	{
	case NodeType::Start:			break;
	case NodeType::Goal:SetStart();	SetGoal();  FindPath(); bReadyToMove = false; break;
	case NodeType::Wall:	SetWall();		break;
	//case NodeType::None: Reset(); break;
	}
	
	//길찾기 시작
	//if (!bReadyToMove)
		
}

void NodeHLD::Render()
{


	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			//시작점 : 노랑
			if (Nodes.second.start == true)
			{
				Nodes.first->Color(1, 1, 0);
			}

			//목적지 : 초록
			else if (Nodes.second.goal == true)
			{
				Nodes.first->Color(0, 1, 0);
			}

			//벽 : 빨강
			else if (Nodes.second.wall == true)
			{
				Nodes.first->Color(1, 0, 0);
			}

			//닫힘 : 파랑
			else if (Nodes.second.close == true)
			{
				//Nodes.first->Color(0, 0, 1);
			}
		}
	}

	//길 : 하얀색
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

UINT NodeHLD::FindH(int startY, int startX, int goalY, int goalX)
{
	int Wdistance;
	int Hdistance;
	//int distance;

	Wdistance = abs(startX - goalX);
	Hdistance = abs(startY - goalY);

	return (Wdistance + Hdistance) * 10;
}

void NodeHLD::Reset()
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

D3DXVECTOR2 NodeHLD::Position()
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



void NodeHLD::RenderText()
{
}

void NodeHLD::SetStart()
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

void NodeHLD::SetGoal()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (Rect::PtInRect(Nodes.first, goalPos))
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

void NodeHLD::SetWall()
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

void NodeHLD::FindPath()
{
	int count = 0;

	//예상 비용 H
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			Nodes.second.h = FindH(y, x, goalY, goalX);
		}
	}

	//최소값 검사 시작 minF
	while (true)
	{
		//검사 회수가 전체 대상보다 같으면 반복문 탈출
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

		//검사 대상 선별 -> 인덱스 저장
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

		//전체의 State를 너무 많이 검색하면 반복문 종료
		if (count2 == WidthNode * HeightNode)
		{
			break;
		}

		//minF 를 계산
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

		///주변 노드의 g값 계산

		//왼쪽
		if (min.x != 0)
		{
			if (nodes[min.y][min.x - 1].second.g > 10 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y][min.x - 1].second.g = 10 + nodes[min.y][min.x].second.g;
				nodes[min.y][min.x - 1].second.parent.x = min.x;
				nodes[min.y][min.x - 1].second.parent.y = min.y;
			}
		}

		//오른쪽
		if (min.x != WidthNode - 1)
		{
			if (nodes[min.y][min.x + 1].second.g > 10 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y][min.x + 1].second.g = 10 + nodes[min.y][min.x].second.g;
				nodes[min.y][min.x + 1].second.parent.x = min.x;
				nodes[min.y][min.x + 1].second.parent.y = min.y;
			}
		}

		//위
		if (min.y != 0)
		{
			if (nodes[min.y - 1][min.x].second.g > 10 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y - 1][min.x].second.g = 10 + nodes[min.y][min.x].second.g;
				nodes[min.y - 1][min.x].second.parent.x = min.x;
				nodes[min.y - 1][min.x].second.parent.y = min.y;
			}
		}

		//아래
		if (min.y != HeightNode - 1)
		{
			if (nodes[min.y + 1][min.x].second.g > 10 + nodes[min.y][min.x].second.g)
			{
				nodes[min.y + 1][min.x].second.g = 10 + nodes[min.y][min.x].second.g;
				nodes[min.y + 1][min.x].second.parent.x = min.x;
				nodes[min.y + 1][min.x].second.parent.y = min.y;
			}
		}

		//좌상
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

		//좌하
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

		//우상
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

		//우하
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

		//minF 더이상 검사하지 마라
		nodes[min.y][min.x].second.close = true;

		//길 만들기
		if (nodes[min.y][min.x].second.goal == true)
		{
			//검사를 수행한 노드의 위치를 저장
			POINT tempPoint;
			tempPoint.y = min.y;
			tempPoint.x = min.x;

			//부모 노드의 위치를 저장(1)
			POINT tempPoint2;

			while (true)
			{
				//부모 노드의 위치를 저장(2)
				tempPoint2.y = nodes[tempPoint.y][tempPoint.x].second.parent.y;
				tempPoint2.x = nodes[tempPoint.y][tempPoint.x].second.parent.x;
				
				//검사 대상이었던 노드를 부모로 변경
				tempPoint.y = tempPoint2.y;
				tempPoint.x = tempPoint2.x;
				
				way.push_back(tempPoint);
				

				//시작점 검사 대상에서 제외
				if (nodes[tempPoint.y][tempPoint.x].second.start == true)
					break;

				
				//부모의 값이 이상할 때
				if (tempPoint.y == Inf)
				{
					Reset();
					break;
				}

				//벡터가 한없이 커질 때
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


