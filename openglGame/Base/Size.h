#pragma once

class Size
{
public:

	Size()
		:_width(.0f)
		, _height(.0f)
	{
	}

	Size(float width, float height)
	{
		_width = width;
		_height = height;
	}

	Size(const Size&size)
	{
		*this = size;
	}

	~Size()
	{
	}

	inline void setSize(float width, float height)
	{
		_width = width;
		_height = height;
	}

	inline void setSize(const Size&size)
	{
		*this = size;
	}

	inline void setWidth(float width)
	{
		_width = width;
	}

	inline void setHeight(float height)
	{
		_height = height;
	}

	inline float getWidth() const
	{
		return _width;
	}

	inline float getHeight() const
	{
		return _height;
	}

	inline Size operator-() const
	{
		return Size(-this->_width, -this->_height);
	}

	inline Size& operator=(const Size& size)
	{
		this->_width = size._width;
		this->_height = size._height;
		return *this;
	}

	inline Size operator+(const Size& size) const
	{
		return Size(this->_width + size._width, this->_height + size._height);
	}

	inline Size operator-(const Size& size) const
	{
		return Size(this->_width - size._width, this->_height - size._height);
	}

	inline bool operator==(const Size& size) const
	{
		return (this->_width == size._width && this->_height == size._height);
	}
public:
	float _width;
	float _height;
};

