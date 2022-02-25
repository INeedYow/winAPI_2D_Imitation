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
	bool isCollisionRectToRectSameSize(const RECT& rt1, const RECT& rt2)
	{								// �簢��1		// �簢��2
		if (COLL_PR(fPoint(rt1.left,  rt1.top),		rt2)) return true;
		if (COLL_PR(fPoint(rt1.right, rt1.top),		rt2)) return true;
		if (COLL_PR(fPoint(rt1.right, rt1.bottom),	rt2)) return true;
		if (COLL_PR(fPoint(rt1.left,  rt1.bottom),	rt2)) return true;
		
		return false;
	}

	bool isCollisionPointToRect(const fPoint& point, const RECT& rt)
	{									// ��ǥ		// �簢��
		return ((rt.left <= point.x && point.x <= rt.right) &&
				(rt.top  <= point.y && point.y <= rt.bottom ));
	}	// ��ǥ������ �簢���� ���ԵǴ��� Ȯ��

	bool isCollisionPointToCircle(const fPoint& point, const fPoint& cp, int cr)
	{										// ��ǥ //	�� �߽���ǥ,	 �� ������ ����
		// x, y ����
		float x = point.x - cp.x;
		float y = point.y - cp.y;

		// ��ǥ�� �� �߽ɱ��� �Ÿ�
		float distance = sqrt(x * x + y * y);

		// �Ÿ��� ���������� �۰ų� ������ �浹
		return (distance <= cr);
	}

	bool isCollisionCircleToRect(const fPoint& cp, int cr, const RECT& rt)
	{							// �� �߽���ǥ, �� ������ ���� // �簢��
		// ���� ������ ��ŭ Ȯ���Ų �簢���� ���� ����
		RECT rect = {
			rt.left		- cr,
			rt.top		- cr,
			rt.right	+ cr,
			rt.bottom	+ cr };

		// Ȯ���� �簢�� �ȿ� ���� �߽��� �ִٸ� �浹 (������ �浹�� ����)
		if ((rt.left < cp.x && cp.x < rt.right) && (rt.top < cp.y && cp.y < rt.bottom))
			return true;
		
		// ������ �浹 Ȯ��
		else
		{
			// �� ������ ��ǥ�� �� �ȿ� �ִ��� Ȯ��
			if (COLL_PC(fPoint(rt.left, rt.top), cp, cr))		return true;
			if (COLL_PC(fPoint(rt.right, rt.top), cp, cr))		return true;
			if (COLL_PC(fPoint(rt.right, rt.bottom), cp, cr))	return true;
			if (COLL_PC(fPoint(rt.left, rt.bottom), cp, cr))	return true;
		}
		return false;
	}

	bool isCollisionCircleToCircle(const fPoint& cp1, int cr1, const fPoint& cp2, int cr2)
	{								// ��1 �߽���ǥ, ������			// ��2 �߽���ǥ, ������
		// �� �߽ɳ��� �Ÿ� ���ؼ� �������� �պ��� ������ �浹
		float x = cp1.x - cp2.x;
		float y = cp1.y - cp2.y;

		float distance = sqrt(x * x + y * y);
		
		return (distance <= cr1 + cr2);
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