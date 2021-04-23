#pragma once


enum EventType : unsigned int
{
	EVENT_NULL = 0,				//ռλ���޲����¼���
	EVENT_GAME_RESTART = 1,		//��λ
	EVENT_KEY = 2,				//������Ϣ
	EVENT_MOUSEKEY = 3,			//��갴����Ϣ
	EVENT_MOUSEMOUSE = 4,		//����ƶ�
	EVENT_MOUSEWHEEL = 5,		//�����ֹ���

	EVENT_CUSTOM = 100,			//100�������������Զ�����Ϣ
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
	int _buttons;//��λ����������������״̬
};

struct MouseWheelEvent : public Event
{
	float _x;
	float _y;
	int _tick;
	int _buttons;//��λ����������������״̬
};
