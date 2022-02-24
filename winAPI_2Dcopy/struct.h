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

	// 몬스터 왕복 조건에 쓰려고 했는데 못 씀
	/*bool operator==(fPoint _pos)
	{
		return (x == _pos.x && y == _pos.y);
	}
	bool operator!=(fPoint _pos)
	{
		return !(*this == _pos);
	}

	fPoint operator-(fPoint pos)
	{
		return fPoint(x - pos.x, y - pos.y);
	}*/
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