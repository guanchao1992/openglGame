#pragma once


enum ComponentType
{
	COMPONENT_CUSTOM = 0,		//自定义
	COMPONENT_RANDER = 1,		//绘制
	COMPONENT_MOUSE_KEY = 2,	//鼠标按键
	COMPONENT_MOUSE_MOVE = 3,	//鼠标移动
	COMPONENT_AREA,				//区块
	COMPONENT_OUTLINE,			//描线

	COMPONENT_ACTOR_OI,			//控制演员的输入接口
	COMPONENT_ACTIVE_MOVE,		//移动控制

	COMPONENT_BULLET_MOVE,		//子弹移动控制
	COMPONENT_BULLET_MOVE_S,	//子弹移动控制的控制
};

