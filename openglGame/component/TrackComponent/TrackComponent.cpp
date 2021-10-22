#include "TrackComponent.h"
#include <GameApp.h>
#include <math.h>
#include "../../2d/Node.h"
#include "../../base/Vector2.h"


void TrackComponent::doBegin()
{
	__super::doBegin();

	_tracks = new std::vector<Vector2>();
	_totalTime = 0;

	_timerId = TimerController::getInstance()->addTimer(0, -1, std::bind(&TrackComponent::update, this, std::placeholders::_1));
}

void TrackComponent::doEnd()
{
	__super::doEnd();

	TimerController::getInstance()->killTimer(_timerId);

	delete _tracks;
	_tracks = nullptr;
}

void TrackComponent::update(float time)
{
	doTrack(dynamic_cast<Node*>(this->_object), _totalTime, time);
	_totalTime += time;
	return;
}

void TrackComponent::resetTracks(int precision, float time, int loop)
{
	_trackNum = precision + 1;
	_time = time;
	_loop = loop;
	_tracks->resize(_trackNum);

	/*
	速度默认设定为1
	向前行驶的直线路径
	*/
	for (int i = 0; i < _trackNum; i++) {
		_tracks->at(i).setVector(i * (_trackNum - 1), 0);
	}
}

void twoone(const Vector2& leftPos, const Vector2& rightPos, float pro, Vector2* outPos) {
	outPos->setVector(leftPos._x + (rightPos._x - leftPos._x) * pro, leftPos._y + (rightPos._y - leftPos._y) * pro);
}

void TrackComponent::doTrack(Node* node, float timeStamp, float interval)
{
	Vector2 nowPos;
	Vector2 nextPos;

	int round = floor(timeStamp / _time);
	float roundStamp = timeStamp - _time * round;
	float nowIndexf = roundStamp / _time * (_trackNum - 1);
	int leftIndex = floor(nowIndexf);
	float offIndexf = nowIndexf - floor(nowIndexf);
	twoone(_tracks->at(leftIndex), _tracks->at(leftIndex + 1), offIndexf, &nowPos);

	int round2 = floor((timeStamp + interval) / _time);
	roundStamp = timeStamp + interval - _time * round2;
	nowIndexf = roundStamp / _time * (_trackNum - 1);
	leftIndex = floor(nowIndexf);
	offIndexf = nowIndexf - leftIndex;
	twoone(_tracks->at(leftIndex), _tracks->at(leftIndex + 1), offIndexf, &nextPos);
	if (round2 != round) {
		nextPos.setVector(nextPos._x + (round2 - round) * (_tracks->at(_trackNum - 1)._x - _tracks->at(0)._x), nextPos._y + (round2 - round) * (_tracks->at(_trackNum - 1)._y - _tracks->at(0)._y));
	}

	Vector3 oldNodePos = node->getPosition();
	node->setPosition(oldNodePos._x + nextPos._x - nowPos._x, oldNodePos._y + nextPos._y - nowPos._y);
}
