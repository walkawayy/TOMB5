#pragma once
#include "../global/types.h"

#define phd_PutPolygons_train	( (void(__cdecl*)(short*)) 0x004B74A0 )//literally only calls phd_PutPolygons
#define phd_TranslateAbs	( (void(__cdecl*)(long, long, long)) 0x004903F0 )
#define phd_PushMatrix	( (void(__cdecl*)()) 0x0048F9C0 )
#define phd_PushUnitMatrix	( (void(__cdecl*)()) 0x0048FA90 )
#define	phd_RotYXZ	( (void(__cdecl*)(long, long, long)) 0x00490150 )
#define	phd_SetTrans	( (void(__cdecl*)(long, long, long)) 0x0048FA40 )
#define	phd_GetVectorAngles	( (void(__cdecl*)(long, long, long, short*)) 0x004904B0 )
#define phd_GenerateW2V	( (void(__cdecl*)(PHD_3DPOS*)) 0x0048F330 )
#define phd_RotX	( (void(__cdecl*)(long)) 0x0048FBE0 )
#define phd_RotY	( (void(__cdecl*)(long)) 0x0048FCD0 )
#define phd_LookAt	( (void(__cdecl*)(long, long, long, long, long, long, short)) 0x0048F760 )
#define SetD3DViewMatrix	( (void(__cdecl*)()) 0x00497320 )
#define aSetViewMatrix	( (void(__cdecl*)()) 0x00490BE0 )
