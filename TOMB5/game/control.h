#pragma once
#include "../global/types.h"

void inject_control();
void KlaxonTremor();
int GetRandomControl();
void SeedRandomControl(long seed);
int GetRandomDraw();
void SeedRandomDraw(long seed);
int GetChange(ITEM_INFO* item, ANIM_STRUCT* anim);
int CheckGuardOnTrigger();
void InterpolateAngle(short dest, short* src, short* diff, short speed);
void TranslateItem(ITEM_INFO* item, short x, short y, short z);
void InitCutPlayed();
void SetCutPlayed(int num);
void SetCutNotPlayed(int num);
int CheckCutPlayed(int num);
int is_object_in_room(int roomnumber, int objnumber);
int check_xray_machine_trigger();
void _special1_control();
void _special1_end();
void _special2_control();
void _special2_end();
void _special3_control();
void _special3_end();
void _special4_control();
void _special4_end();
void ResetCutItem(int item_num);
void resetwindowsmash(int item_num);
void triggerwindowsmash(int item_num);

#define	GetTargetOnLOS	( (int(__cdecl*)(GAME_VECTOR*, GAME_VECTOR*, int, int)) 0x0041A170 )
#define ObjectOnLOS2	( (int(__cdecl*)(GAME_VECTOR*, GAME_VECTOR*, PHD_VECTOR*, MESH_INFO**)) 0x00419110 )
#define GetFloor ( (FLOOR_INFO*(__cdecl*)(int, int, int, short*)) 0x00415B20 )
#define GetHeight ( (short(__cdecl*)(FLOOR_INFO*, int, int, int)) 0x00415FB0 )
#define GetCeiling ( (short(__cdecl*)(FLOOR_INFO*, int, int, int)) 0x00417640 )
#define UpdateSky	( (void(__cdecl*)()) 0x00414720 )
#define ClearDynamics	( (void(__cdecl*)()) 0x00431530 )
#define ClearFires	( (void(__cdecl*)()) 0x00481B10 )
#define KillMoveEffects	( (void(__cdecl*)()) 0x004146A0 )
#define KillMoveItems	( (void(__cdecl*)()) 0x00414620 )
#define TestTriggers	( (void(__cdecl*)(short*, int, int)) 0x00416760 )
#define UpdatePulseColour	( (void(__cdecl*)()) 0x00480830 )
#define	CheckNoColFloorTriangle	( (long(__cdecl*)(FLOOR_INFO*, long, long)) 0x00418C80 )
#define	ExplodeItemNode	( (int(__cdecl*)(ITEM_INFO*, int, int, long)) 0x0041ABF0 )
#define	LOS	( (int(__cdecl*)(GAME_VECTOR*, GAME_VECTOR*)) 0x00417CF0 )
#define AnimateItem	( (void(__cdecl*)(ITEM_INFO*)) 0x00415300 )
#define	GetWaterHeight	( (long(__cdecl*)(long, long, long, short)) 0x00415DA0 )
#define TriggerActive	( (int(__cdecl*)(ITEM_INFO*)) 0x004175B0 )
#define	FlipMap	( (void(__cdecl*)(int)) 0x00418910 )
#define FlamingHell	( (void(__cdecl*)(PHD_VECTOR*)) 0x0041C950 )
#define FireTwoGunTitleWeapon	( (void(__cdecl*)(PHD_VECTOR*, PHD_VECTOR*)) 0x0041CB10 )

