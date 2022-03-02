#pragma once
#include <assert.h>

struct iPoint
{
	int x;
	int y;

	iPoint()
	{
		x = 0;
		y = 0;
	}
	iPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	
	void setRandPos(int minX, int maxX, int minY, int maxY)
	{
		if (maxX < minX || maxY < minY) return;

		int iX = rand() % (maxX - minX + 1) + minX;
		int iY = rand() % (maxY - minY + 1) + minY;
		
		x = iX;
		y = iY;
	}
};

// ��ǥ
struct fPoint
{
	float x;
	float y;

	fPoint()
	{
		x = 0.f;
		y = 0.f;
	}
	fPoint(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	fPoint operator+(fPoint other)
	{
		return fPoint(x + other.x, y + other.y);
	}
	fPoint operator-(fPoint other)
	{
		return fPoint(x - other.x, y - other.y);
	}
	bool operator==(fPoint other)
	{
		return (x == other.x && y == other.y);
	}
	bool operator!=(fPoint other)
	{
		return !(*this == other);
	}

};

// ���⼺
struct fVec2
{
	float x;
	float y;

	fVec2()
	{
		x = 0.f;
		y = 0.f;
	}
	fVec2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	fVec2& normalize()
	{	// sqrt : ������ �Լ�
		float length = (float)sqrt(x * x + y * y);

		assert(0.f != length);

		x = x / length;
		y = y / length;

		return *this;
	}
};

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
	if ((rect.left <= cp.x && cp.x <= rect.right) && (rect.top <= cp.y && cp.y <= rect.bottom))
		return true;

	// ������ �浹 Ȯ�� (Ȯ���� �簢���� �� ������ ��ǥ�� �� �ȿ� �ִ��� Ȯ��)
	else
	{
		if (COLL_PC(fPoint((float)rect.left, (float)rect.top), cp, cr))			return true;
		if (COLL_PC(fPoint((float)rect.right, (float)rect.top), cp, cr))		return true;
		if (COLL_PC(fPoint((float)rect.right, (float)rect.bottom), cp, cr))		return true;
		if (COLL_PC(fPoint((float)rect.left, (float)rect.bottom), cp, cr))		return true;
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