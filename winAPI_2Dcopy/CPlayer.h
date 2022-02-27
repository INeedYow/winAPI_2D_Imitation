#pragma once
#include "CObject.h"
#include "CBattery.h"

class CPlayer : public CObject
{
protected:
	static bool		isMode;			// �þ� ���
	static bool		isScan;			// ��ĵ ���
	static fPoint	fpPos;			// ���� ��ǥ

	fPoint		m_fpPrevPos;		// ���� ��ǥ
	fVec2		m_fvDir;			// �Ѿ� ����
	UINT		m_uiBullet;			// �Ѿ� ����
	float		m_fSpeed;			// �̵� �ӵ�

	CBattery	m_battery;			// ���͸� (�����̽���)
	
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void update();
	virtual void render(HDC hDC);
	
	void setDir(fVec2 vec);

	static bool getMode();
	static bool getScan();
	static fPoint getPlayerPos();

	static void setMode(bool mode);
	static void setScan(bool scan);
	static void setPlayerPos(fPoint pos);


	void createBullet();

	void setBullet(UINT ea);
	void death();
};

// �ٸ� ������Ʈ�鿡�� �÷��̾� ��ǥ�� ������ �����ϱ� ������ �θ��� pos�� �� ����
// static ������� pos�� ���� ���� ��
// ���� ����� �ƴ� �� ����