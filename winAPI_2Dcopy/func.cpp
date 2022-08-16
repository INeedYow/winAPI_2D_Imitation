#include "framework.h"
#include "func.h"

class CCollider;

// x�� �� �� ĳ���Ͱ� ������ �� �밢�� ������ left�� ������ ���� �̵��� ����
DIR collisionRectToRect(CCollider* coll1, CCollider* coll2)
{	// �̹� �浹�� ���¿���
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size2 = coll2->getOwner()->getSize();

	if (pos2.y - size2.y / 2 <= pos1.y && pos1.y <= pos2.y + size2.y / 2)
	{
		if (pos1.x <= pos2.x - size2.x / 2) return DIR::LEFT;
		if (pos1.x >= pos2.x + size2.x / 2) return DIR::RIGHT;
	}
	else
	{
		if (pos1.y <= pos2.y - size2.y / 2) return DIR::TOP;
		if (pos1.y >= pos2.y + size2.y / 2) return DIR::BOTTOM;
	}
	return DIR::NONE;
}

bool isLeftColl(CCollider* coll1, CCollider* coll2)
{
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();

	if (pos1.x < pos2.x) 
		return true;
	return false;
}

// x�� �� �� ĳ���Ͱ� ������ �� �밢�� ������ left�� ������ ���� �̵��� ����
//DIR collisionRectToRect(CCollider* coll1, CCollider* coll2)
//{	// �̹� �浹�� ���¿���
//	fPoint pos1 = coll1->getPos();
//	fPoint pos2 = coll2->getPos();
//	fPoint size2 = coll2->getOwner()->getSize();
//
//	if (abs(pos2.x - pos1.x) <= abs(pos2.y - pos1.y))	// x �Ÿ��� y �Ÿ����� ª����
//	{	// top or bottom
//		if (pos2.y - size2.y / 2 > pos1.y) return DIR::TOP;
//		if (pos2.y + size2.y / 2 < pos1.y) return DIR::BOTTOM;
//	}
//	else
//	{	// left or right
//		if (pos2.x - size2.x / 2 > pos1.x) return DIR::LEFT;
//		if (pos2.x + size2.x / 2 < pos1.x) return DIR::RIGHT;
//	}
//	return DIR::NONE;
//}

bool isCollisionRectToRect(const fPoint& pos1, const fPoint& size1, const fPoint& pos2, const fPoint& size2)
{	// == ISCOLLRR					// �簢��1 ��ǥ, ������				// �簢��2 ��ǥ, ������
	return ((abs(pos1.x - pos2.x) < (size1.x + size2.x) / 2.f) &&
			(abs(pos1.y - pos2.y) < (size1.y + size2.y) / 2.f));
}

bool isCollisionPointToRect(const fPoint& point, const RECT& rt)
{	// == ISCOLLPR						// ��ǥ		// �簢��
	return ((rt.left <= point.x && point.x <= rt.right) &&
			(rt.top <= point.y && point.y <= rt.bottom));
}	// ��ǥ������ �簢���� ���ԵǴ��� Ȯ��

bool isCollisionPointToCircle(const fPoint& point, const fPoint& cp, int cr)
{	// == ISCOLLPC						// ��ǥ //	�� �߽���ǥ,	 �� ������ ����
	// x, y ����
	float x = point.x - cp.x;
	float y = point.y - cp.y;

	// ��ǥ�� �� �߽ɱ��� �Ÿ�
	float distance = (float)sqrt((double)x * x + (double)y * y);

	// �Ÿ��� ���������� �۰ų� ������ �浹
	return (distance <= cr);
}

bool isCollisionCircleToRect(const fPoint& cp, int cr, const RECT& rt)
{	// == ISCOLLCR				// �� �߽���ǥ, �� ������ ���� // �簢��
	// ���� ������ ��ŭ Ȯ���Ų �簢���� ���� ����
	RECT rect = {
		(int)rt.left - cr,
		(int)rt.top - cr,
		(int)rt.right + cr,
		(int)rt.bottom + cr };

	// Ȯ���� �簢�� �ȿ� ���� �߽��� �ִٸ� �浹 (������ �浹�� ����)
	if ((rect.left <= cp.x && cp.x <= rect.right) && (rt.top <= cp.y && cp.y <= rt.bottom) ||
		(rt.left <= cp.x && cp.x <= rt.right) && (rect.top <= cp.y && cp.y <= rect.bottom))
		return true;

	// ������ �浹 Ȯ�� (�簢���� �� ������ ��ǥ�� �� �ȿ� �ִ��� Ȯ��)
	else
	{
		if (ISCOLLPC(fPoint((float)rt.left, (float)rt.top), cp, cr))			return true;
		if (ISCOLLPC(fPoint((float)rt.right, (float)rt.top), cp, cr))			return true;
		if (ISCOLLPC(fPoint((float)rt.right, (float)rt.bottom), cp, cr))		return true;
		if (ISCOLLPC(fPoint((float)rt.left, (float)rt.bottom), cp, cr))			return true;
	}
	return false;
}

bool isCollisionCircleToCircle(const fPoint& cp1, int cr1, const fPoint& cp2, int cr2)
{	// == ISCOLLCC					// ��1 �߽���ǥ, ������		// ��2 �߽���ǥ, ������
	// �� �߽ɳ��� �Ÿ� ���ؼ� �������� �պ��� ������ �浹
	float x = cp1.x - cp2.x;
	float y = cp1.y - cp2.y;

	float distance = (float)sqrt((double)x * x + (double)y * y);

	return (distance <= cr1 + cr2);
}