#pragma once
#include "TrackComponent.h"


class TrackTestComponent :public TrackComponent
{
public:
	virtual const char* getName() { return "TrackTestComponent"; }
public:
	/*
		precision ÿ��ѭ���Ķ�����
		time ÿ��ѭ����ʱ��
		loop ѭ������
	*/
	virtual void resetTracks(int precision, float time, int loop);
};
