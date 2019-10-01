#pragma once
class DirectWrite {
private:
	DirectWrite();
	~DirectWrite();

private:
	static DirectWrite* instance;

private:
	ID2D1Factory1*factory;
	static IDWriteFactory* writeFactory;

	ID2D1Device* device;
	static ID2D1DeviceContext* deviceContext;

	static ID2D1Bitmap1* bitmap;
	static IDXGISurface* surface;

	//��Ʈ
	static ID2D1SolidColorBrush* brush;
	static IDWriteTextFormat* format;



public:
	//singleton func
	static void Create();
	static void Delete();

	static DirectWrite* Get();
	static ID2D1DeviceContext* GetDC() { return deviceContext; }
	//2D�� ����� ���� �Լ�
	static void CreateBackBuffer();
	static void DeleteBackBuffer();
	//�������
	static void RenderText(wstring& text, RECT & rect);


};