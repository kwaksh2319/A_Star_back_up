#include"stdafx.h"
#include"BFSNodePathHLD.h"
#define Inf 99999999
#define costStraight 10 
#define costDiagnoal 15

BFSNodePathHLD::BFSNodePathHLD(D3DXVECTOR2 position, D3DXVECTOR2 size, D3DXCOLOR color )
	:NodeHLD(position, size, color),startX(0), startY(0), bWallCheck(false)
{
	NodeHLD(position, size, color);
	monsterPos = position;
	wstring shaderFile = Shaders + L"Rect.fx";
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			float positionX = x * size.x - Width * 0.5f;
			float positionY = y * size.y - Height*0.5;

			nodes[y][x].first = new Rect(shaderFile, D3DXVECTOR2(positionX, positionY), size);
			nodes[y][x].second.start = false;
			nodes[y][x].second.goal = false;
			nodes[y][x].second.wall = false;
			nodes[y][x].second.f = Inf;
			nodes[y][x].second.g = Inf;
			nodes[y][x].second.h = Inf;
			nodes[y][x].second.close = false;
			nodes[y][x].second.parent.x = Inf;
			nodes[y][x].second.parent.y = Inf;

		}
	}
	SetStart(monsterPos);

}

BFSNodePathHLD::~BFSNodePathHLD()
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			SAFE_DELETE(nodes[y][x].first);
		}
	}
}

void BFSNodePathHLD::SetBFSPosition(vector<pair<Rect*, tagNode>> Pos)
{

	for(int i=0;i<Pos.size();i++){
	   posCheck.push_back(Pos[i].first->Position());
	}
	
}

vector<D3DXVECTOR2> BFSNodePathHLD::GetBFSPosition()
{
	vector<D3DXVECTOR2>tmpPos;

	tmpPos = posCheck;
	for (int i = 0; i < posCheck.size(); i++) {
		posCheck.pop_back();
	}
	posCheck.clear();
	return tmpPos;
}

void BFSNodePathHLD::BFSNode(D3DXVECTOR2 playerPos, D3DXVECTOR2 monsterPos, int indexX, int indexY)
{



	srand(time(NULL));
	               if(getPos.size()>0){
	             for (int i = 0; i < getPos.size(); i++) {
			            	getPos.pop_back();
			           }
				   }
			//getPos.clear();
				
				getPos.push_back(nodes[indexX + 1][indexY + 1]);//0

				getPos.push_back(nodes[indexX + 1][indexY]);//1
				if(indexY -1>=0){
			       getPos.push_back(nodes[indexX + 1][indexY - 1]);//2
				
				    getPos.push_back(nodes[indexX][indexY - 1]);//3
				}
				if(indexY - 1 >= 0&& indexX - 1 >= 0){
					getPos.push_back(nodes[indexX - 1][indexY - 1]);//4
				}
					if (indexX - 1 >= 0) {
					getPos.push_back(nodes[indexX - 1][indexY]);//5

					getPos.push_back(nodes[indexX - 1][indexY + 1]);//6
				}
				getPos.push_back(nodes[indexX][indexY + 1]);//7

				
	

				//Wall check
				for (int i = 0; i < getPos.size(); i++) {
					if (getPos[i].second.wall == true)
					{
						getPos.erase(getPos.begin() + i);
					}

				}
			
				//°£°÷ÀÎÁö check
				/*
				for (int i = 0; i < savePos.size(); i++) {
					for (int j = 0; j < getPos.size(); j++) {
						if (getPos[j].first->Position() == savePos[i].first->Position()) {
							//getPos.erase(getPos.begin() + i);
						}
					}
				}*/
				//°¥·Á°íÇÏ´ÂÀå¼Òµé ÀúÀå
				//for (int i = 0; i < getPos.size(); i++) {

				//	savePos.push_back(getPos[i]);
				//}
				//·£´ý
				int rn;
				
				pair<Rect*, tagNode> tmp;
				for (int i = 0; i < getPos.size(); i++) {
					
					    rn = rand() % (getPos.size() - i) + i;
						tmp =getPos[i];
						getPos[i] = getPos[rn];
						getPos[rn] = tmp;
					
				}
				
				SetBFSPosition(getPos);
				for (int i = 0; i < getPos.size(); i++) {
					posCheck.push_back(getPos[i].first->Position());

				}

}

void BFSNodePathHLD::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	
	
	if(bWallCheck&&Mouse->Down(0)){
	     SetWall();
	}
	BFSNode(playerPos, monsterPos,startX, startY);
	


}

void BFSNodePathHLD::Render()
{

	NodeHLD::Render();
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			//½ÃÀÛÁ¡ : ³ë¶û
			if (nodes[y][x].second.start == true)
			{
				nodes[y][x].first->Color(1, 1, 0);
			}

			//¸ñÀûÁö : ÃÊ·Ï
			else if (nodes[y][x].second.goal == true)
			{
				nodes[y][x].first->Color(0, 1, 0);
			}

			//º® : »¡°­
			else if (nodes[y][x].second.wall == true)
			{
				nodes[y][x].first->Color(1, 0, 0);
			}

			//´ÝÈû : ÆÄ¶û
			else if (nodes[y][x].second.close == true)
			{
				nodes[y][x].first->Color(0, 0, 1);
			}
		}
	}

	

	

	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			nodes[y][x].first->Render();
		}
	}

}

void BFSNodePathHLD::SetStart(D3DXVECTOR2 pos)
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (Rect::PtInRect(nodes[y][x].first, pos))
			{
				nodes[y][x].second.start = true;
				nodes[y][x].second.g = 0;
				startX = x;
				startY = y;
			}
			else
			{
				nodes[y][x].second.start = false;
			}
		}
	}
}

void BFSNodePathHLD::SetGoal()
{
}

void BFSNodePathHLD::SetWall()
{
	//ptMouse = ;
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (Rect::PtInRect(nodes[y][x].first, ptMouse))
			{
				nodes[y][x].second.wall = true;
			}
		}
	}

}

void BFSNodePathHLD::FindPath()
{
}

void BFSNodePathHLD::SetRoad()
{


	POINT min;
	int count2 = 0;
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (nodes[y][x].second.f &&
				nodes[y][x].second.wall == false &&
				nodes[y][x].second.close == false)
			{
				min.x = x;
				min.y = y;
				break;
			}
			count2++;
		}
	}

}
