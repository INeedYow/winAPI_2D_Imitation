#pragma once
#include "CScene.h"
class CScene_Title : public CScene
{
	float	m_fCount;			// 1�� ���� ī��Ʈ��
	bool	m_isChange;			// text��� ���� ������ ����
	UINT	m_uiColor;			// RGB�� ���� ����

public:
	CScene_Title();
	virtual ~CScene_Title();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();

};

