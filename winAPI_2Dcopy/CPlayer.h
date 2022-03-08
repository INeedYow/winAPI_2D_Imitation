#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
	static UINT	s_uiCoin;
	static bool	s_bTransform;			// 변신할 때 다른 업데이트 안 돌게 할 생각

	float		m_fSpeedL;				// 왼쪽 속력
	float		m_fSpeedR;				// 오른쪽 속력
	float		m_fSpeedY;				// 점프 속력
	float		m_fGravity;
	float		m_fTransformTimer;		// 변신 타이머

	UINT		m_uiBottomCnt;			// 아래 충돌 카운트

	UINT		m_uiState;				// 상태(SUPER,DIR,JUMP)	// dir 0이 left
	TYPE_MARIO	m_eMario;				// 미니마리오, 빅마리오, 불꽃마리오 종류가 셋이라 비트 연산보다 이게 나을 것 같음

	CTexture*	m_pTex;
	// 모든 오브젝트가 가질 건데 CObject에 공통으로 묶는 게?

	void createFireball();
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);

	static UINT getCoin();
	static void setCoin(UINT coin);
	static bool getTransformMode();

	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);

	void drawMario(const wstring& commonName);

	void setSmMario();
	void setBgMario();
};


// TODO 버섯, 꽃, 별 먹었을 때 잠시 멈추면서 플레이어 모습 변하는 과정만 update()되도록 하기
// bool 변수로 true일 때 아예 업데이트 생략하도록 하면 될 것 같은 느낌
// static이나 전역변수로?