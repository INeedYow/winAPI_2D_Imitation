
#include "CObject.h"
class CMonster : public CObject
{
public:
	CMonster();
	virtual ~CMonster();

	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;
};
