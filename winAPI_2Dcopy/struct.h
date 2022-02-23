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

	// ���� �պ� ���ǿ� ������
	bool operator==(fPoint _pos)
	{
		return (x == _pos.x && y == _pos.y);
	}
	bool operator!=(fPoint _pos)
	{
		return !(*this == _pos);
	}
	// �� �� ���Ƽ�
	fPoint operator-(fPoint pos)
	{
		return fPoint(x - pos.x, y - pos.y);
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
};