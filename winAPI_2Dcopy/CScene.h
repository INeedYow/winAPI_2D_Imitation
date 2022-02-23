#pragma once

class CObject;		// ������ ������ ����� �� ���漱������ ����ϴ�. (#include ������ �ϴ� �� ����, ������ �ӵ� ���)

class CScene
{
	vector<CObject*> m_arrObj[(int)OBJ::SIZE];		// [] �����ŭ vector����
	wstring m_strName;

public:
	CScene();
	virtual ~CScene();

	void setName(const wstring& strName);
	wstring getName();

	void addObject(CObject* pObj, OBJ objType);

	void update();
	void render(HDC hDC);

	// ȭ����ȯ�� �� �۾�
	virtual void enter() = 0;
	virtual void exit() = 0;
};