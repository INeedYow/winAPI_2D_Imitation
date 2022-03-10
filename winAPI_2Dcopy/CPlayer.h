#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
	static UINT		s_uiCoin;			// 코인 획득
	static UINT		s_uiScore;			// 스코어
	static UINT		s_uiTryCnt;			// 시도 횟수
	static bool		s_bTransform;		// 변신할 때 다른 업데이트 안 돌게
	static float	s_fCamPosX;				

	float		m_fSpeedL;				// 왼쪽 속력
	float		m_fSpeedR;				// 오른쪽 속력
	float		m_fSpeedY;				// 점프 속력
	float		m_fGravity;

	float		m_fTransformTimer;		// 변신 타이머
	float		m_fInvincibleTimer;		// 무적 타이머

	int			m_iBottomCnt;			// 지면과 충돌 카운트

	UINT		m_uiState;				// 상태(SUPER,DIR,AIR등등) // dir 0이 left
	TYPE_MARIO	m_eMario;				// 미니마리오, 빅마리오, 불꽃마리오 종류가 셋이라 비트 연산보다 이게 나을 것 같음

	CTexture*	m_pTex;

	void createFireball();
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);

	static UINT getCoin();
	static UINT getScore();
	static UINT getTryCnt();
	static bool isTransform();
	static float getCamPos();

	static void setCoin(UINT coin);
	static void setScore(UINT score);
	static void setTryCnt(UINT cnt);
	static void setCamPos(float posX);

	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);

	void drawMario(const wstring& commonName);
	void death();

	void setSmMario();
	void setBgMario();
	void getDamage();
};