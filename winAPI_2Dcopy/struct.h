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
	
	void setRandPos(int minX, int maxX, int minY, int maxY)
	{
		if (maxX < minX || maxY < minY) return;

		int iX = rand() % (maxX - minX + 1) + minX;
		int iY = rand() % (maxY - minY + 1) + minY;
		
		x = iX;
		y = iY;
	}
};

// ÁÂÇ¥
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

	template <typename T>
	fPoint operator*(T num)
	{
		return fPoint(x * num, y * num);
	}

	template <typename T>
	fPoint operator/(T num)
	{
		assert(0 != num);

		return fPoint(x / num, y / num);
	}

};

// ¹æÇâ¼º
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

	bool operator==(fVec2 other)
	{
		return (x == other.x && y == other.y);
	}
	bool operator!=(fVec2 other)
	{
		return !(*this == other);
	}

	fVec2& normalize()
	{	// sqrt : Á¦°ö±Ù ÇÔ¼ö
		float length = (float)sqrt((double)x * x + (double)y * y);

		assert(0.f != length);

		x = x / length;
		y = y / length;

		return *this;
	}
};