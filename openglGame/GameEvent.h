#pragma once


enum EventType : unsigned int
{
	EVENT_NULL = 0, //占位，无操作事件。
	EVENT_GAME_RESTART = 1,	//复位
};

struct Event 
{
	int _eventId = EventType::EVENT_NULL;
};

