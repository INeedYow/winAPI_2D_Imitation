
#include "CObject.h"
class CMonster : public CObject
{
	UCHAR	m_ucState;
	//float	m_fTimer;
public:
	CMonster();
	virtual ~CMonster();

	//void setTimer(float time);

	//float getTimer();

	void setStateTrue(UCHAR state);
	void setStateFalse(UCHAR state);
	bool isState(UCHAR state);

	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};
