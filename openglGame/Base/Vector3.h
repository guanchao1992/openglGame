#ifndef ___Vector3__H__
#define ___Vector3__H__

class Vector3
{
public:
	Vector3()
		:_x(.0f) , _y(.0f) , _z(.0f)
		, _r(_x), _g(_y), _b(_z)
	{
	}

	Vector3(float x, float y, float z)
		: _r(_x), _g(_y), _b(_z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	Vector3(const Vector3&pos)
		: _r(_x), _g(_y), _b(_z)
	{
		*this = pos;
	}

	~Vector3()
	{
	}

	inline void setVector(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	inline void setVector(const Vector3&pos)
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

	inline Vector3 operator-() const
	{
		return Vector3(-this->_x, -this->_y, -this->_z);
	}

	inline Vector3& operator=(const Vector3& pos)
	{
		this->_x = pos._x;
		this->_y = pos._y;
		this->_z = pos._z;
		return *this;
	}

	inline Vector3 operator+(const Vector3& pos) const
	{
		return Vector3(this->_x + pos._x, this->_y + pos._y, this->_z + pos._z);
	}

	inline Vector3 operator-(const Vector3& pos) const
	{
		return Vector3(this->_x - pos._x, this->_y - pos._y, this->_z - pos._z);
	}

	inline bool operator==(const Vector3& pos) const
	{
		return (this->_x == pos._x && this->_y == pos._y&& this->_z == pos._z);
	}
	
public:
	float _x;
	float _y;
	float _z;

	float &_r;// == _x
	float &_g;// == _y
	float &_b;// == _z
};

#endif