#pragma once
#ifndef _UI_DATA_DEFINE_H
#define _UI_DATA_DEFINE_H

// Layer ö��
typedef enum {
	ENUM_LOADING_LAYER,			// ����
	ENUM_LOGIN_LAYER,			// ��¼
	ENUM_HALL_LAYER,			// ����
} ENUM_UI_LAYER;


extern void layerCreateInit(void * mapCreateFun);
#endif