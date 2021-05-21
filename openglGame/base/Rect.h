#pragma once

class Rect
{
public:

	Rect()
		: _left(.0f)
		, _bottom(.0f)
		, _right(.0f)
		, _top(.0f)
	{
	}

	Rect(float left, float bottom, float right, float top)
	{
		_left = left;
		_bottom = bottom;
		_right = right;
		_top = top;
	}

	Rect(const Rect&rect)
	{
		*this = rect;
	}

	~Rect()
	{
	}

	inline void setRect(float left, float bottom, float right, float top)
	{
		_left = left;
		_bottom = bottom;
		_right = right;
		_top = top;
	}

	inline void setRect(const Rect&rect)
	{
		*this = rect;
	}

	inline Rect& operator=(const Rect& rect)
	{
		_left = rect._left;
		_bottom = rect._bottom;
		_right = rect._right;
		_top = rect._top;
		return *this;
	}

	inline bool operator==(const Rect& rect) const
	{
		return (this->_left == rect._left &&this->_bottom == rect._bottom &&this->_right == rect._right &&this->_top == rect._top);
	}
public:
	float _left;
	float _bottom;
	float _right;
	float _top;
};

