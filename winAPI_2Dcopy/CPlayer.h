#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
	static UINT	s_uiCoin;
	static bool	s_bTransform;			// ������ �� �ٸ� ������Ʈ �� ���� �� ����

	float		m_fSpeedL;				// ���� �ӷ�
	float		m_fSpeedR;				// ������ �ӷ�
	float		m_fSpeedY;				// ���� �ӷ�
	float		m_fGravity;
	float		m_fTransformTimer;		// ���� Ÿ�̸�

	UINT		m_uiBottomCnt;			// �Ʒ� �浹 ī��Ʈ

	UINT		m_uiState;				// ����(SUPER,DIR,JUMP)	// dir 0�� left
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
	static void setCoin(UINT coin);
	static bool getTransformMode();

	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);

	void drawMario(const wstring& commonName);

	void setSmMario();
	void setBgMario();
};


// TODO ����, ��, �� �Ծ��� �� ��� ���߸鼭 �÷��̾� ��� ���ϴ� ������ update()�ǵ��� �ϱ�
// bool ������ true�� �� �ƿ� ������Ʈ �����ϵ��� �ϸ� �� �� ���� ����
// static�̳� ����������?