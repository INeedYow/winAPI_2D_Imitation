#pragma once
#include "CObject.h"

class CPlayer : public CObject
{
	static UINT s_uiCoin;

	float	m_fSpeedL;		// ���� �ӷ�
	float	m_fSpeedR;		// ������ �ӷ�
	float	m_fSpeedY;		// ���� �ӷ�
	float	m_fGravity;
	float	m_fTimer;

	UINT	m_uiState;		// ����(SUPER,FIRE,BIG,DIR,JUMP)	// dir 0�� left

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);

	static UINT getCoin();
	static void setCoin(UINT coin);

	void createFireball();

	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);
};


// TODO ����, ��, �� �Ծ��� �� ��� ���߸鼭 �÷��̾� ��� ���ϴ� ������ update()�ǵ��� �ϱ�
// bool ������ true�� �� �ƿ� ������Ʈ �����ϵ��� �ϸ� �� �� ���� ����
// static�̳� ����������?