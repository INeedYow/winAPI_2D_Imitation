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
	virtual void render(HDC hDC);

	// 화면전환할 때 작업
	virtual void enter() = 0;
	virtual void exit() = 0;

	// 이렇게 하면 안 좋을 것 같은데 어떻게든 되게만 하다보니
public:
	vector<CObject*>* getVecArr();	
	// 그냥 될 것 같아서 시도하다가 오류만 안 나게 하다보니 되기는 한데 되는 이유는 모르겠음
		// 이걸로 exit도 진행했음
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO : (질문) 이거 맞나요 교수님 .. 계속 생각해보는데 머리 너무 아픕니다 하면서도 헷갈려요
// 
// Scene이 갖는 m_arrObj[] 배열의 자료형이 vector<CObject*>이고
// 
// m_arrObj는 배열의 이름이자 시작 주소니까 *(m_arrObj) 가 m_arrObj[0]이고
// 
// 그래서 m_arrObj를 return하는 getVecArr()의 반환 타입이 vector<CObject*>* 여야 하는 것이고
//
// 따라서 getVecArr()를 반환 받아서 쓸 때에는
//
// pVecArr[]가 vector<CObject*>가 되는 것이고 pVecArr[(int)OBJ::ENUMCLASS][i]로 해당 obj들에 접근할 수 있다....? 
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////