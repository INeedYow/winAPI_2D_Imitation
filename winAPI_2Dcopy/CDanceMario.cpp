#include "framework.h"
#include "CDanceMario.h"

CDanceMario::CDanceMario()
{
	setName(OBJNAME::DANCEMARIO);
	setSize(fPoint((float)P_sizex, (float)P_sizey));
	m_fTimer = 0.f;
	m_ucStep = 0;

	m_pTex = loadTex(KEY_RES::TEX_PLAYER, L"texture\\mario.bmp");

	createAnimator();
	createAnim(L"smDance", m_pTex, fPoint(192.f, 0.f),		fPoint(64.f, 64.f), fPoint(0.f, 64.f), 0.5f, 2);
	createAnim(L"bgDance", m_pTex, fPoint(192.f, 128.f),	fPoint(64.f, 64.f), fPoint(0.f, 64.f), 0.5f, 2);
	createAnim(L"frDance", m_pTex, fPoint(192.f, 256.f),	fPoint(64.f, 64.f), fPoint(0.f, 64.f), 0.5f, 2);

	setRandPos();
	setRandPlay();
}

CDanceMario::~CDanceMario()
{
}

void CDanceMario::update()
{
	m_fTimer += fDT;

	if (m_fTimer > 1.f)
	{
		setRandPos();
		setRandPlay();
		m_fTimer = 0.f;
	}
	getAnimator()->update();
}

void CDanceMario::render(HDC hDC)
{
	componentRender(hDC);
}

void CDanceMario::setRandPos()
{
	int x, y;

	x = rand() % (WINSIZEX - P_SIZEX) + P_SIZEX / 2;
	y = rand() % (WINSIZEY - P_SIZEY) + P_SIZEY / 2;

	setPos(fPoint((float)x, (float)y));
}

void CDanceMario::setRandPlay()
{
	int luck = rand() % 3;

	switch (luck)
	{
	case 0:
		PLAY(L"smDance");
		break;
	case 1:
		PLAY(L"bgDance");
		break;
	case 2:
		PLAY(L"frDance");
		break;
	}
}
