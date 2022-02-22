#pragma once

class CObject;		// 포인터 변수를 사용할 때 전방선언으로 충분하다. (#include 여러번 하는 것 방지, 컴파일 속도 향상)

class CScene
{
	vector<CObject*> m_arrObj[(int)OBJ::SIZE];		// [] 사이즈만큼 vector생성
	wstring m_strName;

public:
	CScene();
	~CScene();

	void setName(const wstring& strName);
	wstring getName();

	void addObject(CObject* pObj, OBJ objType);
};