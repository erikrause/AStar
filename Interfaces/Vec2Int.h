#pragma once

class Vec2Int
{
public:

	Vec2Int() : X(0), Y(0)
	{

	}

	Vec2Int(int x, int y) : X(x), Y(y)
	{
	}

	int X;
	int Y;

	inline Vec2Int operator+ (Vec2Int const& b) const
	{
		return Vec2Int(X + b.X, Y + b.Y);
	}

	inline Vec2Int operator- (Vec2Int const& b) const
	{
		return Vec2Int(X - b.X, Y - b.Y);
	}

	inline bool operator == (Vec2Int const& b) const
	{
		return X == b.X && Y == b.Y;
	}
};