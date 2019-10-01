#pragma once
class FileManger {


private:
	static vector<D3DXVECTOR2> markers;//���� ��ü
	static vector<pair<D3DXVECTOR2, D3DXVECTOR2>>markers2;//���ΰ�ü



public:

	//�������� ����
	static bool CompareX(const D3DXVECTOR2& a, const D3DXVECTOR2& b) {

		return a.x < b.x;
	}
	//�������� ����
	static bool CompareX2(const pair<D3DXVECTOR2, D3DXVECTOR2>&a, const pair<D3DXVECTOR2, D3DXVECTOR2>&b) {

		return a.first.x < b.first.x;

	}
	//�������� ����
	static bool CompareY(const D3DXVECTOR2&a, const D3DXVECTOR2&b) {


		return a.y >b.y;
}
	static void Save(wstring filename);
	static void SaveLines();

	static void Load(wstring filename);
	static void LoadLines();

public :
	static void SetMarker(vector<D3DXVECTOR2>&v);
	static void SetMarker2(vector <pair<D3DXVECTOR2, D3DXVECTOR2>>&v);

	static vector<D3DXVECTOR2>GetMarker();
    static vector<pair< D3DXVECTOR2, D3DXVECTOR2>>GetMarker2();
};