#ifndef ___Vector2__H__
#define ___Vector2__H__

class Vector2
{
public:
	Vector2()
		:_x(.0f)
		, _y(.0f)
	{
	}

	Vector2(float x, float y)
	{
		_x = x;
		_y = y;
	}

	Vector2(const Vector2&pos)
	{
		*this = pos;
	}

	~Vector2()
	{
	}

	inline void setVector(float x, float y)
	{
		_x = x;
		_y = y;
	}

	inline void setVector(const Vector2&pos)
	{
		*this = pos;
	}

	inline void setVectorX(float x)
	{
		_x = x;
	}

	inline void setVectorY(float y)
	{
		_y = y;
	}

	inline float getX() const
	{
		return _x;
	}

	inline float getY() const
	{
		return _y;
	}

	inline Vector2 operator-() const
	{
		return Vector2(-this->_x, -this->_y);
	}

	inline Vector2& operator=(const Vector2& pos)
	{
		this->_x = pos._x;
		this->_y = pos._y;
		return *this;
	}

	inline Vector2 operator+(const Vector2& pos) const
	{
		return Vector2(this->_x + pos._x, this->_y + pos._y);
	}

	inline Vector2 operator*(float s) const
	{
		return Vector2(this->_x * s, this->_y * s);
	}
	inline Vector2 operator/(float s) const
	{
		return Vector2(this->_x / s, this->_y / s);
	}

	inline Vector2 operator-(const Vector2& pos) const
	{
		return Vector2(this->_x - pos._x, this->_y - pos._y);
	}

	inline bool operator==(const Vector2& pos) const
	{
		return (this->_x == pos._x && this->_y == pos._y);
	}

public:
	float _x;
	float _y;
};

#endif