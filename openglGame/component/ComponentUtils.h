#pragma once


enum ComponentType
{
	COMPONENT_CUSTOM = 0,		//�Զ���
	COMPONENT_RANDER = 1,		//����
	COMPONENT_MOUSE_KEY = 2,	//��갴��
	COMPONENT_MOUSE_MOVE = 3,	//����ƶ�
	COMPONENT_AREA,				//����
	COMPONENT_OUTLINE,			//����

	COMPONENT_ACTOR_OI,			//������Ա������ӿ�
	COMPONENT_ACTIVE_MOVE,		//�ƶ�����

	COMPONENT_BULLET_MOVE,		//�ӵ��ƶ�����
	COMPONENT_BULLET_MOVE_S,	//�ӵ��ƶ����ƵĿ���
};

