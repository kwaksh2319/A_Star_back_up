#include"stdafx.h"
#include"HLDgrid.h"


HLDgrid::HLDgrid(wstring shaderFile)
	:position(0, 0), scale(1, 1), color(1, 0, 1, 1)
{



	CreateBuffer(shaderFile);

	Color(color);
}


HLDgrid::HLDgrid(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color)
	: position(position), scale(scale), color(color)
{


	CreateBuffer(shaderFile);

	Color(color);
}

HLDgrid::~HLDgrid()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);
}

void HLDgrid::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	/*
	D3DXMATRIX W;
	D3DXMATRIX S, T;



	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);
	W = S * T;
	*/
	
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	
	//shader->AsVector("Color")->SetFloatVector(color);
	

}

void HLDgrid::Render()
{
	UINT stride = sizeof(Vertex); //보폭
	UINT offset = 0; //시작점
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0); //Todo 08. 인덱스 버퍼 사용
	{
		D3DXMATRIX W;
		D3DXMATRIX S, T;



		D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
		D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);

		W = S * T;
		shader->AsMatrix("World")->SetMatrix(W);
		shader->AsVector("Color")->SetFloatVector(color);
		shader->DrawIndexed(0, 0, indexCount);

	}
	ImGui::SliderFloat("Gridpositionx", (float*)&position.x , -1000.0, 1000.0);
	ImGui::SliderFloat("Gridpositiony", (float*)&position.y, -1000.0, 1000.0);
	ImGui::SliderFloat("Gridscalex", (float*)&scale.x, -1000.0, 1000.0);
	ImGui::SliderFloat("Gridscaley", (float*)&scale.y, -1000.0, 1000.0);
	//shader->Draw(0, 0, 6);

	
}



void HLDgrid::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	//D3DXVECTOR2 input = {x, y};
	Position(input);
}

void HLDgrid::Position(D3DXVECTOR2& vec)
{
	position = vec;

}

void HLDgrid::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDgrid::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;

}

void HLDgrid::Color(float r, float g, float b)
{
	D3DXCOLOR input = D3DXCOLOR(r, g, b, 0.5f);
	Color(input);
}

void HLDgrid::Color(D3DXCOLOR & vec)
{
	color = vec;
	shader->AsVector("Color")->SetFloatVector(color);
}

bool HLDgrid::PtInRect(const HLDgrid * rect, D3DXVECTOR2 ptMouse)
{
	float xScale = rect->scale.x*0.5f;
	float yScale = rect->scale.y*0.5f;

	float left = rect->position.x - xScale;
	float right = rect->position.x + xScale;
	float bottom = rect->position.y - yScale;
	float top = rect->position.y + yScale;

	bool bCheck = true;

	bCheck &= ptMouse.x > left;
	bCheck &= ptMouse.x < right;
	bCheck &= ptMouse.y > bottom;
	bCheck &= ptMouse.y < top;

	return bCheck;
}

void HLDgrid::TransGetPosition(D3DXVECTOR2 pos)
{
	UINT index[4];
	float x = pos.x;
	float z = pos.y;
	index[0] = width * z + x;
	index[1] = width * (z+1) + x;
	index[2] = width * z+x+1;
	index[3] = width * (z+1) + x + 1;

	D3DXVECTOR3 v[4];
	for (int i = 0; i < 4; i++){
		v[index[i]].x = vertices[index[i]].Position.x;
		v[index[i]].y = vertices[index[i]].Position.y;
		v[index[i]].z = vertices[index[i]].Position.z;
	}
}


void HLDgrid::CreateBuffer(wstring shaderFile)
{
	shader = new Shader(shaderFile);
	vertexCount = (width + 1) * (height + 1);
	vertices = new Vertex[vertexCount];
	
	for (UINT z = 0; z <= height; z++)
	{
		for (UINT x = 0; x <= width; x++)
		{
			UINT index = (width + 1) * z + x; //각 rect의 [0] 구하기

			vertices[index].Position.x = (float)x;
			vertices[index].Position.y = (float)z;
			vertices[index].Position.z = 0.0f;

			//Todo 07. y를 0으로, z를 눕혀서 그리면 -> 실행(암것도 안나옴) -> 카메라 y축 움직여보자
			//vertices[index].Position.x = (float)x;
			//vertices[index].Position.y = 0.0f;
			//vertices[index].Position.z = (float)z;
		}
	}
	
	//Create VertexBerffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//	desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;
		//D3D11_SUBRESOURCE_DATA data;
		//ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

		//쉐이더로 넘기면서 값 복사해줌. 원본은 지역변수로 소멸되어도 상관없음
		subResource.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &subResource, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
	
	indexCount = width * height * 6; //전체 인덱스 개수 -> 그리드 한칸당 인덱스는 6개 (칸수 * 6개)
	indices = new UINT[indexCount];

	UINT index = 0;
	for (UINT z = 0; z < height; z++) //칸수니까 작거나 같다x, 작을때까지o(0, 1, 2..인덱스)
	{
		for (UINT x = 0; x < width; x++)
		{
			indices[index + 0] = (width + 1) * z + x; //0 (각 칸의 좌하단 == 인덱스 번호와 동일)
			indices[index + 1] = (width + 1) * (z + 1) + x; //4 (0번 다음에 바로 윗칸)
			indices[index + 2] = (width + 1) * z + (x + 1); //1
			indices[index + 3] = (width + 1) * z + (x + 1); //1
			indices[index + 4] = (width + 1) * (z + 1) + x; //4
			indices[index + 5] = (width + 1) * (z + 1) + (x + 1); //5 (마지막은 둘 다 1씩 더하면 됨)

			index += 6; //6개씩 증가해서 indices 배열을 만듬
		}
	}
	


	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT)* indexCount; //*400
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER; //
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices; //
		HRESULT hr = Device->CreateBuffer(&desc, &subResource, &indexBuffer);
		assert(SUCCEEDED(hr));

	}

}

