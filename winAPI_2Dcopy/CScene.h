#pragma once

class CObject;		// ������ ������ ����� �� ���漱������ ����ϴ�. (#include ������ �ϴ� �� ����, ������ �ӵ� ���)

class CScene
{
	vector<CObject*> m_arrObj[(int)OBJ::SIZE];		// [] �����ŭ vector����
	wstring m_strName;

public:
	CScene();
	~CScene();

	void setName(const wstring& strName);
	wstring getName();

	void addObject(CObject* pObj, OBJ objType);
};