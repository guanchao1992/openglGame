#include "TrackTestComponent.h"
#include <GameApp.h>
#include <math.h>


void TrackTestComponent::resetTracks(int precision, float time, int loop)
{
	_trackNum = precision + 1;
	_time = time;
	_loop = loop;
	_tracks->resize(_trackNum);

	for (int i = 0; i < _trackNum; i++) {
		_tracks->at(i).setVector(50 * sin(i * 2 * PI / (_trackNum - 1)) + i * 10, 50 * cos(i * 2 * PI / (_trackNum - 1)));
	}
}
