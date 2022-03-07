#pragma once

class CAnimation;

class CAnimator
{
	friend class CObject;

	map<wstring, CAnimation*>	m_mapAni;		// 키값으로 애니메이션 저장
	CAnimation*					m_pCurAni;
	CObject*					m_pOwner;

public:
	CAnimator();
	~CAnimator();

	CObject* getOwner();

	void update();
	void render(HDC hDC);

	void createAnimation(const wstring& strName, CTexture* pTex, fPoint leftTop, fPoint slice,
		fPoint step, float dura, UINT frmCnt);
	CAnimation* findAnimation(const wstring& strName);
	void play(const wstring& strName);
};

