#pragma once
#include "CObject.h"
class CPlayer : public CObject
{
protected:
	static bool isMode;			// �þ� ���
	static fPoint fpPos;		// ���� ��ǥ

	fPoint	m_fpPrevPos;		// ���� ��ǥ
	fVec2	m_fvDir;			// �Ѿ� ����
	UINT	m_uiBullet;			// �Ѿ� ����
	float	m_fSpeed;			// �̵� �ӵ�

public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);
	
	void setDir(fVec2 vec);

	static bool getMode();
	static fPoint getPlayerPos();
	static void setPlayerPos(fPoint pos);

	void createBullet();

	void setBullet(UINT ea);
	void death();
};

// �ϳ� �ɸ��� ��
// �ٸ� ������Ʈ�鿡�� �÷��̾� ��ǥ�� ������ �����ϱ� ������ �θ��� pos�� �� ����
// static ������� pos�� ���� ���� ��
