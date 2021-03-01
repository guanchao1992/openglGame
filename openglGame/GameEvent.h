#pragma once


enum EventType : unsigned int
{
	EVENT_NULL = 0,				//占位，无操作事件。
	EVENT_GAME_RESTART = 1,		//复位
	EVENT_KEY = 2,				//键盘消息
};

struct Event 
{
	int _eventId = EventType::EVENT_NULL;
};


struct KeyEvent :public Event
{
	int _key;
	bool _isDown;
};
