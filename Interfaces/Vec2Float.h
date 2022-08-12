#pragma once

class Vec2Float
{
public:

	Vec2Float() : X(0), Y(0)
	{

	}

	Vec2Float(float x, float y) : X(x), Y(y)
	{
	}

	float X;
	float Y;

	inline Vec2Float operator+ (Vec2Float const& b) const
	{
		return Vec2Float(X + b.X, Y + b.Y);
	}

	inline Vec2Float operator- (Vec2Float const& b) const
	{
		return Vec2Float(X - b.X, Y - b.Y);
	}

	inline bool operator == (Vec2Float const& b) const
	{
		return X == b.X && Y == b.Y;
	}

	inline Vec2Float operator / (float const& b) const
	{
		return Vec2Float(X / b, Y / b);
	}

	inline Vec2Float operator / (Vec2Float const& b) const
	{
		return Vec2Float(X / b.X, Y / b.Y);
	}
};