#pragma once
#include "CObject.h"
#include "CBattery.h"

class CPlayer : public CObject
{
protected:
	static bool		isMode;			// �þ� ���
	static bool		isScan;			// ��ĳ�� ���
	static float	scanTimer;		// ��ĳ�� ���ӽð�
	static fPoint	fpPos;			// ���� ��ǥ
	static UINT		uiBullet;		// �Ѿ� ����

	fPoint		m_fpPrevPos;		// ���� ��ǥ
	fVec2		m_fvDir;			// �Ѿ� ����
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
	static float getScanTimer();
	static fPoint getPlayerPos();
	static UINT getBullet();

	static void setScanTimer(float time);
	static void setMode(bool mode);
	static void setPlayerPos(fPoint pos);
	static void setBullet(UINT bullet);


	void createBullet();

	void death();
};

// �ٸ� ������Ʈ�鿡�� �÷��̾� ��ǥ�� ������ �����ϱ� ������ �θ��� pos�� �� ����
// static ������� pos�� ���� ���� ��
// ���� ����� �ƴ� �� ����