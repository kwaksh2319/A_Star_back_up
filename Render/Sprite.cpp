#include "stdafx.h"
#include "Sprite.h"


//-----------------------------------------------------------------------------
// Spirte
//-----------------------------------------------------------------------------
Sprite::Sprite(wstring textureFile, wstring shaderFile)
{
	Initialize(textureFile, shaderFile, 0, 0, 0, 0);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float endX, float endY)
{
	Initialize(textureFile, shaderFile, 0, 0, endX, endY);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	Initialize(textureFile, shaderFile, startX, startY, endX, endY);
}

void Sprite::Initialize(wstring spriteFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	D3DXMatrixIdentity(&world); //���� ��Ʈ���� �ʱ�ȭ

	bDrawBound = false;
	bDrawCollision = false;

	textureFile = spriteFile;

	shader = new Shader(shaderFile);
	boundShader = new Shader(Shaders + L"Bounding.fx");
	srv = Sprites::Load(spriteFile);
	shader->AsShaderResource("Map")->SetResource(srv);

	//Default World
	Position(0, 0);
	Scale(1, 1);
	Rotation(0, 0, 0);



	HRESULT hr;
	D3DX11_IMAGE_INFO info;
	hr = D3DX11GetImageInfoFromFile(spriteFile.c_str(), NULL, &info, NULL);
	assert(SUCCEEDED(hr));

	startX = (startX > 0) ? startX / (float)info.Width : 0.0f;
	startY = (startY > 0) ? startY / (float)info.Height : 0.0f;

	endX = (endX > 0) ? endX / (float)info.Width : 1.0f;
	endY = (endY > 0) ? endY / (float)info.Height : 1.0f;

	Vertex vertices[6];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = D3DXVECTOR2(startX, endY);
	vertices[1].Uv = D3DXVECTOR2(startX, startY);
	vertices[2].Uv = D3DXVECTOR2(endX, endY);
	vertices[3].Uv = D3DXVECTOR2(endX, endY);
	vertices[4].Uv = D3DXVECTOR2(startX, startY);
	vertices[5].Uv = D3DXVECTOR2(endX, startY);

	float sizeX = (endX > 0) ? endX * (float)info.Width : (float)info.Width;
	sizeX -= startX * (float)info.Width;

	float sizeY = (endY > 0) ? endY * (float)info.Height : (float)info.Height;
	sizeY -= startY * (float)info.Height;


	
	textureSize = D3DXVECTOR2(sizeX, sizeY); //���� �̹��� ����� �޾ƿ�
	
	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
	CreateBound();
}

void Sprite::CreateBound()
{
	BoundVertex vertices[5];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);


	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(BoundVertex) * 5;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &BoundvertexBuffer);
		assert(SUCCEEDED(hr));
	}
	
}

Sprite::~Sprite()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);

	Sprites::Remove(textureFile);
}


void Sprite::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	boundShader->AsMatrix("View")->SetMatrix(V);
	boundShader->AsMatrix("Projection")->SetMatrix(P);


	D3DXMATRIX  S, R, T;
	D3DXMatrixScaling(&S, scale.x*textureSize.x, scale.y*textureSize.y, 1.0f);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x + scale.x * 0.5f, position.y + scale.y * 0.5f, 0.0f);

	world = S * R * T;

	shader->AsMatrix("World")->SetMatrix(world);

	boundShader->AsMatrix("World")->SetMatrix(world);

}

void Sprite::Render()
{
	

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 6);
	if (bDrawBound == true) {
		UINT stride = sizeof(BoundVertex);
		UINT offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &BoundvertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		//boundShader->Draw(0, 0, 5);
		boundShader->Draw(0, bDrawCollision ? 1 : 0, 5);
	}
}

bool Sprite::Aabb(D3DXVECTOR2 position)
{
   
	return Aabb(this,position);
}

bool Sprite::Aabb(Sprite * b)
{
	return Aabb(this,b);
}

bool Sprite::Obb(Sprite * b)
{

	return Obb(this, b);
}

bool Sprite::Aabb(Sprite * sprite, D3DXVECTOR2 position)
{
	//�浹 ������ left,top ,right, bottom
	float xScale = sprite->scale.x * sprite->textureSize.x*0.5f;
	float yScale = sprite->scale.y * sprite->textureSize.y*0.5f;


	//�浹 ����(rect)
	float left = sprite->position.x - xScale;
	float right = sprite->position.x + xScale;
	float top = sprite->position.y + yScale;
	float bottom = sprite->position.y - yScale;

	//�浹 üũ 
	bool bCheck = true;
	bCheck &= position.x >= left;
	bCheck &= position.x <= right;
	bCheck &= position.y >= bottom;
	bCheck &= position.y <= top;
	

	return bCheck;
}

bool Sprite::Aabb(Sprite * a, Sprite * b)
{
	//sprite a �� ���� ���ϱ� 
	float xScale = a->scale.x* a->textureSize.x*0.5f;
	float yScale = a->scale.y* a->textureSize.y*0.5f;
	
	float leftA = a->position.x - xScale;
	float rightA = a->position.x + xScale;
	float bottomA = a->position.y - yScale;
	float topA = a->position.y + yScale;


	//sprtie b�� �������ϱ�

	xScale = b->scale.x* b->textureSize.x*0.5f;
	yScale = b->scale.y* b->textureSize.y*0.5f;

	float leftB = b->position.x - xScale;
	float rightB = b->position.x + xScale;
	float bottomB = b->position.y - yScale;
	float topB = b->position.y + yScale;

	bool bCheck = true;
	bCheck &= leftA < rightB;
	bCheck &= topA > bottomB;
	bCheck &= rightA > leftB;
	bCheck &= bottomA < topB;



	return bCheck;
}

bool Sprite::Obb(Sprite * a, Sprite * b)
{

	ObbDesc obbA, obbB;
	D3DXVECTOR2 lengthA = D3DXVECTOR2(a->world._11,a->world._22)*0.5f;
	CreateObb(&obbA, a->position, a->world, lengthA);
	D3DXVECTOR2 lengthB=D3DXVECTOR2(b->world._11, b->world._22)*0.5f;
	CreateObb(&obbB, b->position, b->world, lengthB);

	return CheckObb(obbA, obbB);
}

void Sprite::CreateObb(OUT ObbDesc * out, D3DXVECTOR2 position, D3DXMATRIX & world, D3DXVECTOR2 & length)
{
	out->Position = position;
	out->Length[0] = length.x;
	out->Length[1] = length.y;
	
	out->Direction[0] =D3DXVECTOR2( world._11, world._12);
	out->Direction[1] = D3DXVECTOR2(world._21, world._22);
	//���Ⱚ�� ����Ҷ� �ڽ��� ũ�⸦ ������� ��-> ������� 1
	//���Ⱚ�� ����ҋ��� �׻� 1�� ����� ���� ����.
	//Normalize�� ���� ���ҿ��� ũ�⸦ �����ش�.
	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);



}

float Sprite::SeperateAxis(D3DXVECTOR2 & seperate, D3DXVECTOR2 & e1, D3DXVECTOR2 & e2)
{
	//�����ڽ��� ������ ������ dot
	float r1 = fabsf(D3DXVec2Dot(&seperate,&e1));
	float r2 = fabsf(D3DXVec2Dot(&seperate, &e2));
	return r1 + r2;
}
float Sprite::lA[4];
float Sprite::lB[4];
float Sprite::l[4];
bool Sprite::lCheck[4];


bool Sprite::CheckObb(ObbDesc & obbA, ObbDesc & obbB)
{

	//nea : ����(�븻������� 1�� ��ȯ�� ��), ea : ����*����(1�� ���� ������ ���Ѱ�)
	D3DXVECTOR2 nea1 = obbA.Direction[0], ea1 = nea1 * obbA.Length[0];//x����
	D3DXVECTOR2 nea2 = obbA.Direction[1], ea2 = nea2 * obbA.Length[1];//y����
	
	D3DXVECTOR2 neb1 = obbB.Direction[0], eb1 = neb1 * obbB.Length[0];//x����
	D3DXVECTOR2 neb2 = obbB.Direction[1], eb2 = neb2 * obbB.Length[1];//y����

	//���� ��� :obbA��ġ -obbB��ġ (���� ������ �ִ� �Ÿ��̱⵵��)
	D3DXVECTOR2 direction = obbA.Position - obbB.Position;//Distance �������� �Ÿ�
	//lengthA �浹üA lengthB �浹ü B length �Ÿ� 
	float lengthA = 0.0f, lengthB=0.0f,length=0.0f;
	
	//�������(A)

	lengthA = D3DXVec2Length(&ea1);
	lengthB = SeperateAxis(nea1, eb1, eb2);
	length = fabsf(D3DXVec2Dot(&direction, &nea1));

	lA[0] = lengthA;
	lB[0] = lengthB;
	l[0] = length;
	lCheck[0] = length > lengthA + lengthB;

	if (length > lengthA + lengthB)
		return false;

	//��������(A)
	lengthA = D3DXVec2Length(&ea2);
	lengthB = SeperateAxis(nea2, eb1, eb2);
	length = fabsf(D3DXVec2Dot(&direction, &nea2));

	lA[1] = lengthA;
	lB[1] = lengthB;
	l[1] = length;
	lCheck[1] = length > lengthA + lengthB;

	if (length > lengthA + lengthB)
		return false;
	//�������(B)
	lengthA = SeperateAxis(neb1, ea1, ea2);
	lengthB = D3DXVec2Length(&eb1);
	length = fabsf(D3DXVec2Dot(&direction, &neb1));

	lA[2] = lengthA;
	lB[2] = lengthB;
	l[2] = length;
	lCheck[2] = length > lengthA + lengthB;

	if (length > lengthA + lengthB)
		return false;

	//��������(B)
	lengthA = SeperateAxis(neb2, ea1, ea2);
	lengthB = D3DXVec2Length(&eb2);
	length = fabsf(D3DXVec2Dot(&direction, &neb2));

	lA[3] = lengthA;
	lB[3] = lengthB;
	l[3] = length;
	lCheck[3] = length > lengthA + lengthB;

	if (length > lengthA + lengthB)
		return false;


	return true;
}

void Sprite::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void Sprite::Position(D3DXVECTOR2 & vec)
{
	position = vec;


}

void Sprite::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);

}

void Sprite::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;

	
}

void Sprite::Rotation(float x, float y, float z)
{
	D3DXVECTOR3 input = D3DXVECTOR3(x, y, z);
	Rotation(input);
}

void Sprite::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;
	//UpdateWorld();

}

void Sprite::RotationDegree(float x, float y, float z)
{
	D3DXVECTOR3 input = D3DXVECTOR3(x, y, z);
	RotationDegree(input);
}

void Sprite::RotationDegree(D3DXVECTOR3 & vec)
{
	vec.x = Math::ToRadian(vec.x);
	vec.y = Math::ToRadian(vec.y);
	vec.z = Math::ToRadian(vec.z);

	Rotation(vec);
}

D3DXVECTOR3 Sprite::RotationDegree()
{
	D3DXVECTOR3 vec = Rotation();
	vec.x = Math::ToDegree(rotation.x);
	vec.y = Math::ToDegree(rotation.y);
	vec.z = Math::ToDegree(rotation.z);

	return vec;

}




//-----------------------------------------------------------------------------
// Spirtes
//-----------------------------------------------------------------------------

map<wstring, Sprites::SpriteDesc> Sprites::spriteMap;

ID3D11ShaderResourceView * Sprites::Load(wstring file)
{
	//�̹� ������ SRV�� ����
	if (spriteMap.count(file) > 0)
	{
		spriteMap[file].RefCount++;
		return spriteMap[file].SRV;
	}

	//���� SRV ����
	HRESULT hr;
	ID3D11ShaderResourceView* srv;
	hr = D3DX11CreateShaderResourceViewFromFile(Device, file.c_str(), NULL, NULL, &srv, NULL);
	assert(SUCCEEDED(hr));

	///�ʿ� ����
	SpriteDesc desc;
	desc.RefCount++;
	desc.SRV = srv;
	spriteMap[file] = desc;

	return desc.SRV;
}

void Sprites::Remove(wstring file)
{
	UINT count = spriteMap.count(file);
	assert(count > 0); //�ش� ������ ������ ���� �ɷ��� ����

	spriteMap[file].RefCount--;

	if (spriteMap[file].RefCount < 1)
	{
		SAFE_RELEASE(spriteMap[file].SRV);
		spriteMap.erase(file);
	}
}
