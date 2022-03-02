#pragma once

class CObject;		// 포인터 변수를 사용할 때 전방선언으로 충분하다. (#include 여러번 하는 것 방지, 컴파일 속도 향상)

class CScene
{
	vector<CObject*> m_arrObj[(int)OBJ::SIZE];		// [] 사이즈만큼 vector생성
	wstring m_strName;

public:
	CScene();
	virtual ~CScene();

	void setName(const wstring& strName);
	wstring getName();

	void addObject(CObject* pObj, OBJ objType);

	virtual void update();
	virtual void finalUpdate();
	virtual void render(HDC hDC);

	// 화면전환할 때 작업
	virtual void enter() = 0;
	virtual void exit() = 0;

	// const 원본, 해당 OBJ의 배열.
	const vector<CObject*>& getGroupObject(OBJ type);

public:
	vector<CObject*>* getVecArr();	
};
