#pragma once
#include "CEnemy.h"
class CEnemy_Worms :   public CEnemy
{
	bool	isNotice;
	float	fAttention;

	bool	isFinish;		// �� ���� �̵� �ֱ� ��������
	bool	isWiggle;		// �þ�� ������
	bool	isMoveX;		// �����̴� ��
	float	fAccel;			// ����

	float	fPosVariance;	// ��ǥ ��ȭ��
	float	fSizeVariance;	// ũ�� ��ȭ��


public:
	CEnemy_Worms();
	virtual ~CEnemy_Worms();

	virtual void setRandDir();

	virtual void update();
	virtual void render(HDC hDC);
};

