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

// 좌표
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

	// 가로 세로 크기가 다른 사각형이라면 가로 기준, 세로 기준 두 번 비교해야 할 듯
			// (가로 또는 세로가) 작은 사각형 기준으로 각 꼭지점이 큰 사각형에 포함되는지 확인
	// -> 현재 구상 중인 게임의 경우 두 사각형 크기가 같으므로 한 사각형의 꼭지점이 다른 사각형에 포함되는지 확인하는 방식으로 작성
	bool isCollisionRectToRectSameSize(const RECT& rt1, const RECT& rt2)
	{								// 사각형1		// 사각형2
		if (COLL_PR(fPoint(rt1.left,  rt1.top),		rt2)) return true;
		if (COLL_PR(fPoint(rt1.right, rt1.top),		rt2)) return true;
		if (COLL_PR(fPoint(rt1.right, rt1.bottom),	rt2)) return true;
		if (COLL_PR(fPoint(rt1.left,  rt1.bottom),	rt2)) return true;
		
		return false;
	}

	bool isCollisionPointToRect(const fPoint& point, const RECT& rt)
	{									// 좌표		// 사각형
		return ((rt.left <= point.x && point.x <= rt.right) &&
				(rt.top  <= point.y && point.y <= rt.bottom ));
	}	// 좌표범위가 사각형에 포함되는지 확인

	bool isCollisionPointToCircle(const fPoint& point, const fPoint& cp, int cr)
	{										// 좌표 //	원 중심좌표,	 원 반지름 길이
		// x, y 길이
		float x = point.x - cp.x;
		float y = point.y - cp.y;

		// 좌표와 원 중심까지 거리
		float distance = sqrt(x * x + y * y);

		// 거리가 반지름보다 작거나 같으면 충돌
		return (distance <= cr);
	}

	bool isCollisionCircleToRect(const fPoint& cp, int cr, const RECT& rt)
	{							// 원 중심좌표, 원 반지름 길이 // 사각형
		// 원의 반지름 만큼 확장시킨 사각형을 새로 만듦
		RECT rect = {
			rt.left		- cr,
			rt.top		- cr,
			rt.right	+ cr,
			rt.bottom	+ cr };

		// 확장한 사각형 안에 원의 중심이 있다면 충돌 (꼭지점 충돌은 제외)
		if ((rt.left < cp.x && cp.x < rt.right) && (rt.top < cp.y && cp.y < rt.bottom))
			return true;
		
		// 꼭지점 충돌 확인
		else
		{
			// 각 꼭지점 좌표가 원 안에 있는지 확인
			if (COLL_PC(fPoint(rt.left, rt.top), cp, cr))		return true;
			if (COLL_PC(fPoint(rt.right, rt.top), cp, cr))		return true;
			if (COLL_PC(fPoint(rt.right, rt.bottom), cp, cr))	return true;
			if (COLL_PC(fPoint(rt.left, rt.bottom), cp, cr))	return true;
		}
		return false;
	}

	bool isCollisionCircleToCircle(const fPoint& cp1, int cr1, const fPoint& cp2, int cr2)
	{								// 원1 중심좌표, 반지름			// 원2 중심좌표, 반지름
		// 원 중심끼리 거리 구해서 반지름의 합보다 작으면 충돌
		float x = cp1.x - cp2.x;
		float y = cp1.y - cp2.y;

		float distance = sqrt(x * x + y * y);
		
		return (distance <= cr1 + cr2);
	}
};

// 방향성
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
	{	// sqrt : 제곱근 함수
		float length = (float)sqrt(x * x + y * y);

		assert(0.f != length);

		x = x / length;
		y = y / length;

		return *this;
	}
};