#ifndef ___Vector4__H__
#define ___Vector4__H__

class Vector4
{
public:
	Vector4()
		:_x(.0f) , _y(.0f) , _z(.0f) , _w(.0f)
		, _r(_x), _g(_y), _b(_z), _l(_w)
	{
	}

	Vector4(float x, float y, float z, float w)
		: _r(_x), _g(_y), _b(_z), _l(_w)
	{
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	Vector4(const Vector4&pos)
		: _r(_x), _g(_y), _b(_z), _l(_w)
	{
		*this = pos;
	}

	~Vector4()
	{
	}

	inline void setVector(float x, float y, float z, float w)
	{
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	inline void setVector(const Vector4&pos)
	{
		*this = pos;
	}

	inline void setX(float x)
	{
		_x = x;
	}

	inline void setY(float y)
	{
		_y = y;
	}

	inline void setZ(float z)
	{
		_z = z;
	}
	inline void setW(float w)
	{
		_w = w;
	}

	inline float getX() const
	{
		return _x;
	}

	inline float getY() const
	{
		return _y;
	}

	inline float getZ() const
	{
		return _z;
	}

	inline float getW() const
	{
		return _w;
	}

	inline Vector4 operator-() const
	{
		return Vector4(-this->_x, -this->_y, -this->_z, -this->_w);
	}

	inline Vector4& operator=(const Vector4& pos)
	{
		this->_x = pos._x;
		this->_y = pos._y;
		this->_z = pos._z;
		this->_w = pos._w;
		return *this;
	}

	inline Vector4 operator+(const Vector4& pos) const
	{
		return Vector4(this->_x + pos._x, this->_y + pos._y, this->_z + pos._z, this->_w + pos._w);
	}

	inline Vector4 operator-(const Vector4& pos) const
	{
		return Vector4(this->_x - pos._x, this->_y - pos._y, this->_z - pos._z, this->_w - pos._w);
	}

	inline bool operator==(const Vector4& pos) const
	{
		return (this->_x == pos._x && this->_y == pos._y&& this->_z == pos._z && this->_w == pos._w);
	}
	
public:

	float _x;
	float _y;
	float _z;
	float _w;

	float &_r;// == _x
	float &_g;// == _y
	float &_b;// == _z
	float &_l;// == _w
};

#endif