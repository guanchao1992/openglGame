#pragma once
#include "../Component.hpp"
#include "Base/Size.h"
#include "Base/Vector2.h"


class Node;

class TrackComponent :public Component
{
public:
	virtual const char* getName() { return "TrackComponent"; }
	virtual ComponentType getType() { return ComponentType::COMPONENT_TRACK; }
	virtual void doBegin();
	virtual void doEnd();
	virtual void update(float time);

public:
	/*
		precision ÿ��ѭ���Ķ�����
		time ÿ��ѭ����ʱ��
		loop ѭ������
	*/
	virtual void resetTracks(int precision, float time, int loop);
	/*
		ִ�дӵ�timeStamp�뿪ʼ��interval���λ�Ʋ���
	*/
	virtual void doTrack(Node* node, float timeStamp, float interval);

protected:
	std::vector<Vector2>* _tracks;
	int _trackNum;
	float _time;
	int _loop;
private:
	float _totalTime;
	int _timerId;
};
