#pragma once

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

	// 몬스터 왕복 조건에 쓰려고
	bool operator==(fPoint _pos)
	{
		return (x == _pos.x && y == _pos.y);
	}
	bool operator!=(fPoint _pos)
	{
		return !(*this == _pos);
	}
	// 될 것 같아서
	fPoint operator-(fPoint pos)
	{
		return fPoint(x - pos.x, y - pos.y);
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
};