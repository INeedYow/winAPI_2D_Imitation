#pragma once
#include "CScene.h"
class CScene_Title : public CScene
{
	float	m_fCount;			// 1�� ���� ī��Ʈ��
	bool	m_isChange;			// text��� ���� ������ ����

	unsigned char	m_ucColorR;			// RGB�� ���� ����
	unsigned char	m_ucColorG;
	unsigned char	m_ucColorB;	

public:
	CScene_Title();
	virtual ~CScene_Title();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void enter();
	virtual void exit();

};

