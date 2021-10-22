#pragma once
#include "TrackComponent.h"


class TrackTestComponent :public TrackComponent
{
public:
	virtual const char* getName() { return "TrackTestComponent"; }
public:
	/*
		precision 每个循环的顶点数
		time 每个循环的时间
		loop 循环次数
	*/
	virtual void resetTracks(int precision, float time, int loop);
};
