#pragma once
#include "CScene.h"
class CScene_Result :  public CScene
{
	UINT		uiCount;			// ī��Ʈ
	float		fTimer;				// �ð�
	LPCWSTR		szTextArr[6];		// ��� ����� �ؽ�Ʈ��
	UINT		uiTotalScore;		// ����

public:
	CScene_Result();
	virtual ~CScene_Result();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();
};