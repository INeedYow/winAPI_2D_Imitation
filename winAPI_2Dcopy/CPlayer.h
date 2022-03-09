#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
	static UINT	s_uiCoin;
	static UINT s_uiScore;
	static UINT s_uiTryCnt;
	static bool	s_bTransform;			// ������ �� �ٸ� ������Ʈ �� ����

	float		m_fSpeedL;				// ���� �ӷ�
	float		m_fSpeedR;				// ������ �ӷ�
	float		m_fSpeedY;				// ���� �ӷ�
	float		m_fGravity;

	float		m_fTransformTimer;		// ���� Ÿ�̸�
	float		m_fInvincibleTimer;		// ���� Ÿ�̸�

	int			m_iBottomCnt;			// ����� �浹 ī��Ʈ

	UINT		m_uiState;				// ����(SUPER,DIR,JUMP���)	// dir 0�� left
	TYPE_MARIO	m_eMario;				// �̴ϸ�����, �򸶸���, �Ҳɸ����� ������ ���̶� ��Ʈ ���꺸�� �̰� ���� �� ����

	CTexture*	m_pTex;
	// ��� ������Ʈ�� ���� �ǵ� CObject�� �������� ���� ��?

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

	static void setCoin(UINT coin);
	static void setScore(UINT score);
	static void setTryCnt(UINT cnt);

	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);

	void drawMario(const wstring& commonName);
	void death();

	void setSmMario();
	void setBgMario();
};


// TODO ����, ��, �� �Ծ��� �� ��� ���߸鼭 �÷��̾� ��� ���ϴ� ������ update()�ǵ��� �ϱ�
// bool ������ true�� �� �ƿ� ������Ʈ �����ϵ��� �ϸ� �� �� ���� ����
// static�̳� ����������?