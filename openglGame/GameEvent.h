#pragma once


enum EventType : unsigned int
{
	EVENT_NULL = 0,				//占位，无操作事件。
	EVENT_GAME_RESTART = 1,		//复位
	EVENT_KEY = 2,				//键盘消息
	EVENT_MOUSEKEY = 3,			//鼠标按键消息
	EVENT_MOUSEMOUSE = 4,		//鼠标移动
	EVENT_MOUSEWHEEL = 5,		//鼠标滚轮滚动

	EVENT_CUSTOM = 100,			//100以上是其他的自定义消息
};

struct Event 
{
	unsigned int _eventId = EventType::EVENT_NULL;
};


struct KeyEvent :public Event
{
	int _key;
	bool _isDown;
};

struct MouseKeyEvent :public Event
{
	float _x;
	float _y;
	/*
		*1 Left mouse button.
		* 2 Middle mouse button.
		* 4 Right mouse button.
	*/
	int button;
	bool _isDown;
};

struct MouseMoveEvent :public Event
{
	float _x;
	float _y;
	int _buttons;//按位返回鼠标各个按键的状态
};

struct MouseWheelEvent : public Event
{
	float _x;
	float _y;
	int _tick;
	int _buttons;//按位返回鼠标各个按键的状态
};
