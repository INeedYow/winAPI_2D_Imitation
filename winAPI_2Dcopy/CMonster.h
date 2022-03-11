
#include "CObject.h"
class CMonster : public CObject
{
	UCHAR	m_ucState;

public:
	CMonster();
	virtual ~CMonster();

	UCHAR getState();

	void setStateTrue(UCHAR state);
	void setStateFalse(UCHAR state);
	bool isState(UCHAR state);

	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};
