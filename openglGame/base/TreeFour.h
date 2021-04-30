#ifndef __TreeFour___H__
#define __TreeFour___H__

class TreeFour
{
public:
public:
	TreeFour*_left = nullptr;
	TreeFour*_right = nullptr;
	TreeFour*_top = nullptr;
	TreeFour*_bottom = nullptr;

	int _x;	//分配区域x
	int _y;	//分配区域y
private:
	void *_data;	//用户数据
};

class TreeFourCollective
{
public:
	void insert(TreeFour * tf)
	{
	}
	void remove(TreeFour*tf)
	{
	}
public:
	TreeFour *_root = nullptr;
};

#endif