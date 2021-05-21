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

	void setSpeedOriginal(const Vector2&speed);	//���ó�ʼ�ٶȣ��Ὣ��ǰ�ٶ�����
	void setSpeedOriginal(float speed);			//���ó�ʼ�ٶȣ��Ὣ��ǰ�ٶ�����
	void setDirOriginal(const Vector2&dir);		//���ó�ʼ���򣬻Ὣ��ǰ��������
	void setDirOriginal(float radian);			//���ó�ʼ���򣬻Ὣ��ǰ��������

	void setSpeedIncrement(const Vector2&speed);	//����
	void setSpeedIncrement(float speed);			//����
	void setDirIncrement(const Vector2&dir);		//����
	void setDirIncrement(float radian);				//����

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
	float _radianOriginal = 0.f;	//��ʼ����
	float _speedOriginal = 0.f;		//��ʼ�ٶ�
	float _radianIncrement = 0.f;	//��������
	float _speedIncrement = 0.f;	//�ٶ�����
};
