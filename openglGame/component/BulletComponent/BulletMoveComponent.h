#pragma once
#include "../Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"
#include "BMCComponent.h"
#include <list>


class BulletMoveComponent :public Component
{
public:
	virtual const char* getName() { return "BulletMoveComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_BULLET_MOVE; }
	virtual void doBegin();
	virtual void doEnd(); 
	void update(float time);
	bool collision();

	void setSpeedOriginal(const Vector2&speed);	//设置初始速度，会将当前速度重置
	void setSpeedOriginal(float speed);			//设置初始速度，会将当前速度重置
	void setDirOriginal(const Vector2&dir);		//设置初始方向，会将当前方向重置
	void setDirOriginal(float radian);			//设置初始方向，会将当前方向重置

	void setSpeedIncrement(const Vector2&speed);	//增量
	void setSpeedIncrement(float speed);			//增量
	void setDirIncrement(const Vector2&dir);		//增量
	void setDirIncrement(float radian);				//增量

	inline float getSpeedIncrement() { return _speedIncrement; }
	inline float getRadianIncrement() { return _radianIncrement; }
	inline float getSpeedOriginal() { return _speedOriginal; }
	inline float getRadianOriginal() { return _radianOriginal; }

	void insert(BMCComponent*bmcc);
	void erase(BMCComponent*bmcc);
private:
	std::list<BMCComponent*> _bmcComponents;
	int _timerId;
	float _totalTime = 3.f;
	float _leftTime = 3.f;
	float _radianOriginal = 0.f;	//初始弧度
	float _speedOriginal = 0.f;		//初始速度
	float _radianIncrement = 0.f;	//弧度增量
	float _speedIncrement = 0.f;	//速度增量
};
