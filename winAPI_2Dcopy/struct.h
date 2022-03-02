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


	// ���� ���� ũ�Ⱑ �ٸ� �簢���̶�� ���� ����, ���� ���� �� �� ���ؾ� �� ��
			// (���� �Ǵ� ���ΰ�) ���� �簢�� �������� �� �������� ū �簢���� ���ԵǴ��� Ȯ��
	// -> ���� ���� ���� ������ ��� �� �簢�� ũ�Ⱑ �����Ƿ� �� �簢���� �������� �ٸ� �簢���� ���ԵǴ��� Ȯ���ϴ� ������� �ۼ�
	// �߰��ϴٺ��� ����� �޶������� ���� �׸� �����Ƿ� ����
	bool isCollisionRectToRectSameSize(const RECT& rt1, const RECT& rt2)					// == COLL_RRS
	{								// �簢��1		// �簢��2
		if (COLL_PR(fPoint((float)rt1.left,  (float)rt1.top),		rt2)) return true;
		if (COLL_PR(fPoint((float)rt1.right, (float)rt1.top),		rt2)) return true;
		if (COLL_PR(fPoint((float)rt1.right, (float)rt1.bottom),	rt2)) return true;
		if (COLL_PR(fPoint((float)rt1.left,  (float)rt1.bottom),	rt2)) return true;
		
		return false;
	}

	bool isCollisionPointToRect(const fPoint& point, const RECT& rt)						// == COLL_PR
	{									// ��ǥ		// �簢��
		return ((rt.left <= point.x && point.x <= rt.right) &&
				(rt.top  <= point.y && point.y <= rt.bottom ));
	}	// ��ǥ������ �簢���� ���ԵǴ��� Ȯ��

	bool isCollisionPointToCircle(const fPoint& point, const fPoint& cp, int cr)			// == COLL_PC
	{										// ��ǥ //	�� �߽���ǥ,	 �� ������ ����
		// x, y ����
		float x = point.x - cp.x;
		float y = point.y - cp.y;

		// ��ǥ�� �� �߽ɱ��� �Ÿ�
		float distance = (float)sqrt((double)x * x + (double)y * y);

		// �Ÿ��� ���������� �۰ų� ������ �浹
		return (distance <= cr);
	}

	bool isCollisionCircleToRect(const fPoint& cp, int cr, const RECT& rt)					// == COLL_CR
	{							// �� �߽���ǥ, �� ������ ���� // �簢��
		// ���� ������ ��ŭ Ȯ���Ų �簢���� ���� ����
		RECT rect = {
			(int)rt.left	- cr,
			(int)rt.top		- cr,
			(int)rt.right	+ cr,
			(int)rt.bottom	+ cr };

		// Ȯ���� �簢�� �ȿ� ���� �߽��� �ִٸ� �浹 (������ �浹�� ����)
		if ((rect.left <= cp.x && cp.x <= rect.right) && (rect.top <= cp.y && cp.y <= rect.bottom))
			return true;
		
		// ������ �浹 Ȯ�� (Ȯ���� �簢���� �� ������ ��ǥ�� �� �ȿ� �ִ��� Ȯ��)
		else
		{
			if (COLL_PC(fPoint((float)rect.left,  (float)rect.top),		cp, cr))		return true;
			if (COLL_PC(fPoint((float)rect.right, (float)rect.top),		cp, cr))		return true;
			if (COLL_PC(fPoint((float)rect.right, (float)rect.bottom),	cp, cr))		return true;
			if (COLL_PC(fPoint((float)rect.left,  (float)rect.bottom),	cp, cr))		return true;
		}
		return false;
	}

	bool isCollisionCircleToCircle(const fPoint& cp1, int cr1, const fPoint& cp2, int cr2)	// == COLL_CC
	{								// ��1 �߽���ǥ, ������			// ��2 �߽���ǥ, ������
		// �� �߽ɳ��� �Ÿ� ���ؼ� �������� �պ��� ������ �浹
		float x = cp1.x - cp2.x;
		float y = cp1.y - cp2.y;

		float distance = (float)sqrt((double)x * x + (double)y * y);
		
		return (distance <= cr1 + cr2);
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