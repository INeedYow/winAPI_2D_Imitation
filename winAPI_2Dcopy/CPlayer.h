#pragma once
#include "CObject.h"

class CPlayer : public CObject
{
	static UINT s_uiCoin;

	float	m_fSpeed;
	float	m_fAccel;
	float	m_fTimer;

	UCHAR	m_ucState;		// ����(SUPER,FIRE,BIG,DIR,JUMP)

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);

	static UINT getCoin();
	static void setCoin(UINT coin);

	void createFireball();
};

UINT    CPlayer::s_uiCoin = 0;

// TODO ����, ��, �� �Ծ��� �� ��� ���߸鼭 �÷��̾� ��� ���ϴ� ������ update()�ǵ��� �ϱ�
// bool ������ true�� �� �ƿ� ������Ʈ �����ϵ��� �ϸ� �� �� ���� ����
// static�̳� ����������?