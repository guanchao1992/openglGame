#pragma once


enum ComponentType
{
	COMPONENT_CUSTOM = 0,		//�Զ���
	COMPONENT_RANDER = 1,		//����
	COMPONENT_MOUSE_KEY = 2,	//��갴��
	COMPONENT_MOUSE_MOVE = 3,	//����ƶ�
	COMPONENT_AREA,				//����
	COMPONENT_OUTLINE,			//����

	COMPONENT_ACTOR_STATE,		//��Ա״̬���
	COMPONENT_ACTOR_OI,			//������Ա������ӿ�
	COMPONENT_ACTOR_MOVE,		//�ƶ�����
	COMPONENT_ACTOR_SKILL,		//ʹ�ü���
	COMPONENT_ACTOR_AI,			//AI�����������Ա�ƶ�

	COMPONENT_BULLET_STATE,		//�ӵ�״̬���
	COMPONENT_BULLET_MOVE,		//�ӵ��ƶ�����
	COMPONENT_BULLET_MOVE_CHANGE,//�ӵ��ƶ����ƵĿ���

	COMPONENT_COLLISION,	//��ײ���

};

