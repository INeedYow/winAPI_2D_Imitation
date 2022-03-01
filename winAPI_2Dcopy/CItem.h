#pragma once
#include "CObject.h"
class CItem : public CObject
{
	float		fTimer;			// 1�� ī��Ʈ �ؼ� �ٸ� ���鿡 �����ַ���
	UINT		uiDuration;		// ������ ���ӽð� (float���� UINT�� ��� ���� �� ���Ƽ�)
	bool		isFlick;		// ������� �� ������

	LPCWSTR		strName;		// �̹��� ������ �̸��̶�� ����Ϸ���
	
	UCHAR		ucKey;			// ������ ������ȣ(������)
	
public:
	CItem();
	virtual ~CItem();

	void	setTimer(float time);
	void	setDuration(UINT dura);
	void	setIsFlick(bool flick);
	void	setKey(UCHAR key);
	void	setName(LPCWSTR name);

	float	getTimer();
	UINT	getDuration();
	bool	getIsFlick();
	UCHAR	getKey();
	LPCWSTR getName();

	void setRandPos();

	// 2�� ���� �����Լ� �ǳ�
	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};

