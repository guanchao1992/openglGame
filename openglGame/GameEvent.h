#pragma once


enum EventType : unsigned int
{
	EVENT_NULL = 0, //ռλ���޲����¼���
	EVENT_GAME_RESTART = 1,	//��λ
};

struct Event 
{
	int _eventId = EventType::EVENT_NULL;
};

