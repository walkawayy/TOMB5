#pragma once
#include "stdint.h"
#include "vars.h"
#include "math_tbls.h"
#include <stdio.h>
#include <d3d.h>
#include <d3dtypes.h>

#pragma pack(push, 1)
typedef struct 
{
	BYTE opCode;	// must be 0xE9;
	DWORD offset;	// jump offset
} JMP;

#define INJECT(from,to) \
{ \
	((JMP*)(from))->opCode = 0xE9; \
	((JMP*)(from))->offset = (DWORD)(to) - ((DWORD)(from) + sizeof(JMP)); \
}

#ifndef ABS
#define ABS(x) (((x)<0) ? (-(x)) : (x))
#endif // ABS

#ifndef phd_sin
#define phd_sin(x) (4 * rcossin_tbl[((int)(x) >> 3) & 0x1FFE])
#endif // phd_sin

#ifndef phd_cos
#define phd_cos(x) (4 * rcossin_tbl[(((int)(x) >> 3) & 0x1FFE) + 1])
#endif // phd_cos

#ifndef SQUARE
#define SQUARE(x) ((x)*(x))
#endif // SQUARE

#define RGBONLY(r, g, b) ((b & 0xFF) | (((g & 0xFF) | ((r & 0xFF) << 8)) << 8))
#define RGBA(r, g, b, a) (RGBONLY(r, g, b) | ((a) << 24))
#define ARGB(r, g, b, a) (RGBA(b, g, r, a))


enum font_flags
{
	FF_NONE = (0 << 0), // 0x0000
	FF_UNK0 = (1 << 0),	// 0x0001
	FF_UNK1 = (1 << 1),	// 0x0002
	FF_UNK2 = (1 << 2),	// 0x0004
	FF_UNK3 = (1 << 3),	// 0x0008
	FF_UNK4 = (1 << 4),	// 0x0010
	FF_UNK5 = (1 << 5),	// 0x0020
	FF_UNK6 = (1 << 6),	// 0x0040
	FF_UNK7 = (1 << 7),	// 0x0080
	FF_UNK8 = (1 << 8),	// 0x0100
	FF_UNK9 = (1 << 9),	// 0x0200
	FF_UNK10 = (1 << 10),	// 0x0400
	FF_UNK11 = (1 << 11),	// 0x0800
	FF_SMALL = (1 << 12),	// 0x1000
	FF_BLINK = (1 << 13),	// 0x2000
	FF_R_JUSTIFY = (1 << 14),	// 0x4000
	FF_CENTER = (1 << 15),	// 0x8000
};

enum lara_draw_type
{
	LARA_NORMAL = 1,
	LARA_YOUNG = 2,
	LARA_BUNHEAD = 3,
	LARA_CATSUIT = 4,
	LARA_DIVESUIT = 5,
	LARA_INVISIBLE = 7
};

enum lara_mesh
{
	LM_HIPS = 0,
	LM_LTHIGH = 1,
	LM_LSHIN = 2,
	LM_LFOOT = 3,
	LM_RTHIGH = 4,
	LM_RSHIN = 5,
	LM_RFOOT = 6,
	LM_TORSO = 7,
	LM_RINARM = 8,
	LM_ROUTARM = 9,
	LM_RHAND = 10,
	LM_LINARM = 11,
	LM_LOUTARM = 12,
	LM_LHAND = 13,
	LM_HEAD = 14,

	NUM_LARA_MESHES
};

enum item_status
{
	ITEM_INACTIVE = 0,
	ITEM_ACTIVE = 1,
	ITEM_DEACTIVATED = 2,
	ITEM_INVISIBLE = 3
};

enum lara_gun_status
{
	LG_NO_ARMS = 0,
	LG_HANDS_BUSY = 1,
	LG_DRAW_GUNS = 2,
	LG_UNDRAW_GUNS = 3,
	LG_READY = 4,
	LG_FLARE = 5,
};

enum lara_water_status
{
	LW_ABOVE_WATER = 0,
	LW_UNDERWATER = 1,
	LW_SURFACE = 2,
	LW_FLYCHEAT = 3,
	LW_WADE = 4
};

enum item_flags
{
	IFLAG_UNK40 = (1 << 6),		 // 0x0040
	IFLAG_CLEAR_BODY = (1 << 7), // 0x0080
	IFLAG_INVISIBLE = (1 << 8),  // 0x0100
	IFLAG_REVERSE = (1 << 14),	 // 0x4000
	IFLAG_KILLED = (1 << 15),    // 0x8000
	IFLAG_ACTIVATION_MASK = 0x3E00 // bits 9-13
};

enum room_flags
{
	RF_FILL_WATER = (1 << 0),			    // 0x0001
	RF_ALWAYS_SFX = (1 << 1),				// 0x0002
	RF_PITCH_SHIFT = (1 << 2),				// 0x0004
	RF_SKYBOX_VISIBLE = (1 << 3),		    // 0x0008   speeds up rendering if no rendered room has this
	RF_DYNAMIC_LIT = (1 << 4),				// 0x0010
	RF_WIND_BLOWS_PONYTAIL = (1 << 5),	    // 0x0020   also some particles
	RF_INSIDE = (1 << 6),	    		    // 0x0040   used in official levels, no apparent effects
	RF_HIDE_GLOBAL_LENS_FLARE = (1 << 7),   // 0x0080   TRLE "NL"
	RF_CAUSTICS_EFFECT = (1 << 8),		    // 0x0100   TRLE "M"
	RF_WATER_REFLECTIVITY = (1 << 9),	    // 0x0200   TRLE "R"
	RF_UNKNOWN_10 = (1 << 10),			    // 0x0400   NGLE uses it for snow
	RF_TRLE_D = (1 << 11),					// 0x0800   NGLE uses it for rain
	RF_TRLE_P = (1 << 12)					// 0x1000   NGLE uses it for cold rooms
};

enum collision_types
{
	CT_NONE = 0,			   // 0x00
	CT_FRONT = (1 << 0),  // 0x01
	CT_LEFT = (1 << 1),  // 0x02
	CT_RIGHT = (1 << 2),  // 0x04
	CT_TOP = (1 << 3),  // 0x08
	CT_TOP_FRONT = (1 << 4),  // 0x10
	CT_CLAMP = (1 << 5)   // 0x20
};

enum input_buttons
{
	IN_NONE = 0,								// 0x00000000
	IN_FORWARD = (1 << 0),						// 0x00000001
	IN_BACK = (1 << 1),							// 0x00000002
	IN_LEFT = (1 << 2),							// 0x00000004
	IN_RIGHT = (1 << 3),						// 0x00000008
	IN_JUMP = (1 << 4),							// 0x00000010
	IN_DRAW = (1 << 5), // Space / Triangle		// 0x00000020
	IN_ACTION = (1 << 6), // Ctrl / X			// 0x00000040
	IN_WALK = (1 << 7), // Shift / R1			// 0x00000080
	IN_OPTION = (1 << 8),						// 0x00000100
	IN_LOOK = (1 << 9),							// 0x00000200
	IN_LSTEP = (1 << 10),						// 0x00000400
	IN_RSTEP = (1 << 11),						// 0x00000800
	IN_ROLL = (1 << 12), // End / O				// 0x00001000
	IN_PAUSE = (1 << 13),						// 0x00002000
	IN_A = (1 << 14),							// 0x00004000
	IN_B = (1 << 15),							// 0x00008000
	IN_CHEAT = (1 << 16),						// 0x00010000
	IN_D = (1 << 17),							// 0x00020000
	IN_E = (1 << 18),							// 0x00040000
	IN_FLARE = (1 << 19),						// 0x00080000
	IN_SELECT = (1 << 20),						// 0x00100000
	IN_DESELECT = (1 << 21),					// 0x00200000
	IN_SAVE = (1 << 22), // F5					// 0x00400000
	IN_LOAD = (1 << 23),  // F6					// 0x00800000
	IN_STEPSHIFT = (1 << 24),					// 0x01000000
	IN_LOOKLEFT = (1 << 25),					// 0x02000000
	IN_LOOKRIGHT = (1 << 26),					// 0x04000000
	IN_LOOKFORWARD = (1 << 27),					// 0x08000000
	IN_LOOKBACK = (1 << 28),					// 0x10000000
	IN_DUCK = (1 << 29),						// 0x20000000
	IN_SPRINT = (1 << 30),						// 0x40000000
	IN_UNK31 = (1 << 31),						// 0x80000000

	IN_ALL = ~0,								// 0xFFFFFFFF (-1)
};

enum height_types
{
	WALL,
	SMALL_SLOPE,
	BIG_SLOPE,
	DIAGONAL,
	SPLIT_TRI
};

enum floor_types {
	FLOOR_TYPE, DOOR_TYPE, TILT_TYPE, ROOF_TYPE, TRIGGER_TYPE, LAVA_TYPE, CLIMB_TYPE, SPLIT1, SPLIT2, SPLIT3, SPLIT4,
	NOCOLF1T, NOCOLF1B, NOCOLF2T, NOCOLF2B, NOCOLC1T, NOCOLC1B, NOCOLC2T, NOCOLC2B,
	MONKEY_TYPE, TRIGTRIGGER_TYPE, MINER_TYPE
};

enum weapon_type_carried {
	WTYPE_MISSING = 0,
	WTYPE_PRESENT = 1,
	WTYPE_SILENCER = 2,
	WTYPE_LASERSIGHT = 4,
	WTYPE_AMMO_1 = 8,
	WTYPE_AMMO_2 = 16,
	WTYPE_AMMO_3 = 32,

	WTYPE_MASK_AMMO = WTYPE_AMMO_1 | WTYPE_AMMO_2 | WTYPE_AMMO_3
};

enum zone_type
{
	SKELLY_ZONE = 0,
	BASIC_ZONE = 1,
	CROC_ZONE = 2,
	HUMAN_ZONE = 3,
	FLYER_ZONE = 4,
};

enum camera_type
{
	CHASE_CAMERA = 0,
	FIXED_CAMERA = 1,
	LOOK_CAMERA = 2,
	COMBAT_CAMERA = 3,
	CINEMATIC_CAMERA = 4,
	HEAVY_CAMERA = 5,
};

enum mood_type
{
	BORED_MOOD = 0,
	ATTACK_MOOD = 1,
	ESCAPE_MOOD = 2,
	STALK_MOOD = 3,
};

enum weapon_types {
	WEAPON_NONE = 0,
	WEAPON_PISTOLS = 1,
	WEAPON_REVOLVER = 2,
	WEAPON_UZI = 3,
	WEAPON_SHOTGUN = 4,
	WEAPON_HK = 5,
	WEAPON_CROSSBOW = 6,
	WEAPON_FLARE = 7,
	WEAPON_FLARE_2 = 8
};

enum quadrant_names
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum cloth_type
{
	CLOTH_MISSING = 0,
	CLOTH_DRY = 1,
	CLOTH_WET = 2
};

struct OBJECT_VECTOR
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short data; // size=0, offset=12
	short flags; // size=0, offset=14
};

struct bounding_box_f
{
	float minX, minY, minZ;
	float maxX, maxY, maxZ;
};

struct tr5_vertex   // 12 bytes
{
	float x;
	float y;
	float z;
};

struct tr5_room_vertex  // 28 bytes
{
	tr5_vertex Vertex;     // Vertex is now floating-point
	tr5_vertex Normal;
	uint32_t Colour;     // 32-bit colour
};

struct SUBSUIT_INFO
{
	short XRot; // size=0, offset=0
	short dXRot; // size=0, offset=2
	short XRotVel; // size=0, offset=4
	short Vel[2]; // size=4, offset=6
	short YVel; // size=0, offset=10
};

struct ROOMLET   // 56 bytes
{
	short	nVtx;
	short	nWVtx;
	short	nSVtx;
	short	nQuad;
	short	nTri;
	short	nWQuad;
	short	nWTri;
	short	padd;
	float	bBox[6];
	LPDIRECT3DVERTEXBUFFER	pVtx;
	float* pSVtx;
	short* pFac;
	int* pPrelight;
};

struct ROOM_LIGHT   // 88 bytes
{
	float x, y, z;       // Position of light, in world coordinates
	float r, g, b;       // Colour of the light

	uint32_t ShadowIntensity;    // only if LightType == LIGHT_SHADOW

	float In;            // Cosine of the IN value for light / size of IN value
	float Out;           // Cosine of the OUT value for light / size of OUT value
	float RadIn;         // (IN radians) * 2
	float RadOut;        // (OUT radians) * 2
	float Range;         // Range of light

	float dx, dy, dz;    // Direction - used only by sun and spot lights
	int32_t x2, y2, z2;    // Same as position, only in integer.
	int32_t dx2, dy2, dz2; // Same as direction, only in integer.

	uint8_t LightType;

	uint8_t Filler[3];     // Dummy values = 3 x 0xCD
};

struct SPHERE
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	long r; // size=0, offset=12
};


struct GAME_VECTOR
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short room_number; // size=0, offset=12
	short box_number; // size=0, offset=14
};

struct PHD_VECTOR
{
	long x;
	long y;
	long z;
};

struct PHD_3DPOS
{
	long x_pos; // off 0 [64]
	long y_pos; // off 4 [68]
	long z_pos; // off 8 [72]
	short x_rot; // off 12 [76]
	short y_rot; // off 14 [78]
	short z_rot; // off 16 [80]
};

struct SVECTOR
{        /* short word type 3D vector */
	short vx, vy;
	short vz, pad;
};

struct CVECTOR
{        /* color type vector */
	union
	{
		struct
		{
			unsigned char b, g, r, cd;
		};
		uint32_t rgbcd{};
	};

	CVECTOR() = default;

	CVECTOR(BYTE r, BYTE g, BYTE b)
		: b(b), g(g), r(r), cd(0)
	{
	}

	CVECTOR(BYTE r, BYTE g, BYTE b, BYTE cd)
		: b(b), g(g), r(r), cd(cd)
	{
	}
};

struct CHANGE_STRUCT
{
	short goal_anim_state; // size=0, offset=0
	short number_ranges; // size=0, offset=2
	short range_index; // size=0, offset=4
};

struct HAIR_STRUCT
{
	PHD_3DPOS pos; // size=20, offset=0
	PHD_VECTOR vel; // size=12, offset=20
	float	fx, fy, fz;
};

struct DISPLAYPU
{
	short life; // size=0, offset=0
	short object_number; // size=0, offset=2
};

struct RANGE_STRUCT
{
	short start_frame; // size=0, offset=0
	short end_frame; // size=0, offset=2
	short link_anim_num; // size=0, offset=4
	short link_frame_num; // size=0, offset=6
};

struct WEAPON_INFO
{
	short lock_angles[4]; // size=8, offset=0
	short left_angles[4]; // size=8, offset=8
	short right_angles[4]; // size=8, offset=16
	short aim_speed; // size=0, offset=24
	short shot_accuracy; // size=0, offset=26
	short gun_height; // size=0, offset=28
	short target_dist; // size=0, offset=30
	char damage; // size=0, offset=32
	char recoil_frame; // size=0, offset=33
	char flash_time; // size=0, offset=34
	char draw_frame; // size=0, offset=35
	short sample_num; // size=0, offset=36
};

struct GAMEFLOW
{
	unsigned int CheatEnabled : 1; // offset=0.0
		unsigned int LoadSaveEnabled : 1; // offset=0.1
		unsigned int TitleEnabled : 1; // offset=0.2
		unsigned int PlayAnyLevel : 1; // offset=0.3
		unsigned int Language : 3; // offset=0.4
		unsigned int DemoDisc : 1; // offset=0.7
		unsigned int Unused : 24; // offset=1.0
	unsigned int InputTimeout; // size=0, offset=4
	unsigned char SecurityTag; // size=0, offset=8
	unsigned char nLevels; // size=0, offset=9
	unsigned char nFileNames; // size=0, offset=10
	unsigned char Pad; // size=0, offset=11
	unsigned short FileNameLen; // size=0, offset=12
	unsigned short ScriptLen; // size=0, offset=14
};

struct FLOOR_INFO
{
	unsigned short index; // size=0, offset=0
	unsigned short fx : 4; // offset=2.0
		unsigned short box : 11; // offset=2.4
		unsigned short stopper : 1; // offset=3.7
	unsigned char pit_room; // size=0, offset=4
	char floor; // size=0, offset=5
	unsigned char sky_room; // size=0, offset=6
	char ceiling; // size=0, offset=7
};

struct ANIM_STRUCT
{
	short* frame_ptr; // size=0, offset=0
	short interpolation; // size=0, offset=4
	short current_anim_state; // size=0, offset=6
	long velocity; // size=0, offset=8
	long acceleration; // size=0, offset=12
	long Xvelocity; // size=0, offset=16
	long Xacceleration; // size=0, offset=20
	short frame_base; // size=0, offset=24
	short frame_end; // size=0, offset=26
	short jump_anim_num; // size=0, offset=28
	short jump_frame_num; // size=0, offset=30
	short number_changes; // size=0, offset=32
	short change_index; // size=0, offset=34
	short number_commands; // size=0, offset=36
	short command_index; // size=0, offset=38
};

struct PCLIGHT//evil bitch
{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	long shadow;
	float Inner;
	float Outer;
	float InnerAngle;
	float OuterAngle;
	float Cutoff;
	float nx;
	float ny;
	float nz;
	long ix;
	long iy;
	long iz;
	long inx;
	long iny;
	long inz;
	float tr;
	float tg;
	float tb;
	float rs;
	float gs;
	float bs;
	long fcnt;
	unsigned char Type;
	unsigned char Active;
	PHD_VECTOR rlp;
	long Range;
};

struct ITEM_LIGHT
{
	long r;
	long g;
	long b;
	long ambient;
	long rs;
	long gs;
	long bs;
	long fcnt;
	PCLIGHT	CurrentLights[21];
	PCLIGHT	PrevLights[21];
	int nCurrentLights;
	int nPrevLights;
	int	room_number;
	int RoomChange;
	PHD_VECTOR item_pos;
	void* pCurrentLights;
	void* pPrevLights;
};

struct SAMPLE_INFO
{
	short number; // size=0, offset=0
	unsigned char volume; // size=0, offset=2
	char radius; // size=0, offset=3
	char randomness; // size=0, offset=4
	char pitch; // size=0, offset=5
	short flags; // size=0, offset=6
};

struct SoundSlot
{
	int OrigVolume; // size=0, offset=0
	int nVolume; // size=0, offset=4
	int nPan; // size=0, offset=8
	int nPitch; // size=0, offset=12
	int nSampleInfo; // size=0, offset=16
	unsigned long distance; // size=0, offset=20
	PHD_VECTOR pos; // size=12, offset=24
};

struct box_node
{
	short exit_box; // size=0, offset=0
	unsigned short search_number; // size=0, offset=2
	short next_expansion; // size=0, offset=4
	short box_number; // size=0, offset=6
};

struct LIGHTINFO
{
	long x;
	long y;
	long z;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char Type;
	short Intensity;
	float Inner;
	float Outer;
	short Length;
	short Cutoff;
	float nx;
	float ny;
	float nz;
};

struct MESH_INFO
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short y_rot; // size=0, offset=12
	short shade; // size=0, offset=14
	short Flags; // size=0, offset=16
	short static_number; // size=0, offset=18
};

struct ITEM_INFO
{
	long floor; // size=0, offset=0
	unsigned long touch_bits; // size=0, offset=4
	unsigned long mesh_bits; // size=0, offset=8
	short object_number; // size=0, offset=12
	short current_anim_state; // size=0, offset=14
	short goal_anim_state; // size=0, offset=16
	short required_anim_state; // size=0, offset=18
	short anim_number; // size=0, offset=20
	short frame_number; // size=0, offset=22
	short room_number; // size=0, offset=24
	short next_item; // size=0, offset=26
	short next_active; // size=0, offset=28
	short speed; // size=0, offset=30
	short fallspeed; // size=0, offset=32
	short hit_points; // size=0, offset=34
	unsigned short box_number; // size=0, offset=36
	short timer; // size=0, offset=38
	short flags; // size=0, offset=40
	short shade; // size=0, offset=42
	short trigger_flags; // size=0, offset=44
	short carried_item; // size=0, offset=46
	short after_death; // size=0, offset=48
	unsigned short fired_weapon; // size=0, offset=50
	short item_flags[4]; // size=8, offset=52
	void* data; // size=0, offset=60
	PHD_3DPOS pos; // size=20, offset=64
	ITEM_LIGHT il; // size=48, offset=84
	unsigned long active : 1; // offset=132.0 OFF=5610
	unsigned long status : 2; // offset=132.1
	unsigned long gravity_status : 1; // offset=132.3
	unsigned long hit_status : 1; // offset=132.4
	unsigned long collidable : 1; // offset=132.5
	unsigned long looked_at : 1; // offset=132.6
	unsigned long dynamic_light : 1; // offset=132.7
	unsigned long poisoned : 1; // offset=133.0
	unsigned long ai_bits : 5; // offset=133.1
	unsigned long really_active : 1; // offset=133.6
	unsigned long InDrawRoom : 1; // offset=133.7
	unsigned long meshswap_meshbits; // size=0, offset=136 OFF=132
	short draw_room; // size=0, offset=140 OFF=136
	short TOSSPAD; // size=0, offset=142 OFF=138
};

struct lara_arm
{
	short* frame_base; // size=0, offset=0
	short frame_number; // size=0, offset=4
	short anim_number; // size=0, offset=6
	short lock; // size=0, offset=8
	short y_rot; // size=0, offset=10
	short x_rot; // size=0, offset=12
	short z_rot; // size=0, offset=14
	short flash_gun; // size=0, offset=16
};

struct FX_INFO
{
	PHD_3DPOS pos; // size=20, offset=0
	short room_number; // size=0, offset=20
	short object_number; // size=0, offset=22
	short next_fx; // size=0, offset=24
	short next_active; // size=0, offset=26
	short speed; // size=0, offset=28
	short fallspeed; // size=0, offset=30
	short frame_number; // size=0, offset=32
	short counter; // size=0, offset=34
	short shade; // size=0, offset=36
	short flag1; // size=0, offset=38
	short flag2; // size=0, offset=40
};

struct lot_info
{
	box_node* node; // size=8, offset=0
	short head; // size=0, offset=4
	short tail; // size=0, offset=6
	unsigned short search_number; // size=0, offset=8
	unsigned short block_mask; // size=0, offset=10
	short step; // size=0, offset=12
	short drop; // size=0, offset=14
	short zone_count; // size=0, offset=16
	short target_box; // size=0, offset=18
	short required_box; // size=0, offset=20
	short fly; // size=0, offset=22
	unsigned short can_jump : 1; // offset=24.0
	unsigned short can_monkey : 1; // offset=24.1
	unsigned short is_amphibious : 1; // offset=24.2
	unsigned short is_jumping : 1; // offset=24.3
	unsigned short is_monkeying : 1; // offset=24.4
	PHD_VECTOR target; // size=12, offset=28
	zone_type zone; // size=4, offset=40
};

struct FOOTPRINT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short YRot; // size=0, offset=12
	short Active; // size=0, offset=14
};

struct creature_info
{
	short joint_rotation[4]; // size=8, offset=0
	short maximum_turn; // size=0, offset=8
	short flags; // size=0, offset=10
	unsigned short alerted : 1; // offset=12.0
	unsigned short head_left : 1; // offset=12.1
	unsigned short head_right : 1; // offset=12.2
	unsigned short reached_goal : 1; // offset=12.3
	unsigned short hurt_by_lara : 1; // offset=12.4
	unsigned short patrol2 : 1; // offset=12.5
	unsigned short jump_ahead : 1; // offset=12.6
	unsigned short monkey_ahead : 1; // offset=12.7
	mood_type mood; // size=4, offset=14
	ITEM_INFO* enemy; // size=144, offset=18
	ITEM_INFO ai_target; // size=144, offset=22
	short pad;
	short item_num; // size=0, offset=5646
	PHD_VECTOR target; // size=12, offset=5648
	lot_info LOT; // size=44, offset=5660
};

struct COLL_INFO
{
	long mid_floor; // size=0, offset=0
	long mid_ceiling; // size=0, offset=4
	long mid_type; // size=0, offset=8
	long front_floor; // size=0, offset=12
	long front_ceiling; // size=0, offset=16
	long front_type; // size=0, offset=20
	long left_floor; // size=0, offset=24
	long left_ceiling; // size=0, offset=28
	long left_type; // size=0, offset=32
	long right_floor; // size=0, offset=36
	long right_ceiling; // size=0, offset=40
	long right_type; // size=0, offset=44
	long left_floor2; // size=0, offset=48
	long left_ceiling2; // size=0, offset=52
	long left_type2; // size=0, offset=56
	long right_floor2; // size=0, offset=60
	long right_ceiling2; // size=0, offset=64
	long right_type2; // size=0, offset=68
	long radius; // size=0, offset=72
	long bad_pos; // size=0, offset=76
	long bad_neg; // size=0, offset=80
	long bad_ceiling; // size=0, offset=84
	PHD_VECTOR shift; // size=12, offset=88
	PHD_VECTOR old; // size=12, offset=100
	short old_anim_state; // size=0, offset=112
	short old_anim_number; // size=0, offset=114
	short old_frame_number; // size=0, offset=116
	short facing; // size=0, offset=118
	short quadrant; // size=0, offset=120
	short coll_type; // size=0, offset=122 USE ENUM CT_*
	short* trigger; // size=0, offset=124
	char tilt_x; // size=0, offset=128
	char tilt_z; // size=0, offset=129
	char hit_by_baddie; // size=0, offset=130
	char hit_static; // size=0, offset=131
	unsigned short slopes_are_walls : 2; // offset=132.0
	unsigned short slopes_are_pits : 1; // offset=132.2
	unsigned short lava_is_pit : 1; // offset=132.3
	unsigned short enable_baddie_push : 1; // offset=132.4
	unsigned short enable_spaz : 1; // offset=132.5
	unsigned short hit_ceiling : 1; // offset=132.6
};

struct CAMERA_INFO
{
	GAME_VECTOR pos; // size=16, offset=0
	GAME_VECTOR target; // size=16, offset=16
	camera_type type; // size=4, offset=32
	camera_type old_type; // size=4, offset=36
	long shift; // size=0, offset=40
	long flags; // size=0, offset=44
	long fixed_camera; // size=0, offset=48
	long number_frames; // size=0, offset=52
	long bounce; // size=0, offset=56
	long underwater; // size=0, offset=60
	long target_distance; // size=0, offset=64
	short target_angle; // size=0, offset=68
	short target_elevation; // size=0, offset=70
	short actual_elevation; // size=0, offset=72
	short actual_angle; // size=0, offset=74
	short lara_node; // size=0, offset=76
	short box; // size=0, offset=78
	short number; // size=0, offset=80
	short last; // size=0, offset=82
	short timer; // size=0, offset=84
	short speed; // size=0, offset=86
	short targetspeed; // size=0, offset=88
	ITEM_INFO* item; // size=144, offset=92
	ITEM_INFO* last_item; // size=144, offset=96
	OBJECT_VECTOR* fixed; // size=16, offset=100
	int mike_at_lara; // size=0, offset=104
	PHD_VECTOR mike_pos; // size=12, offset=108
};

struct OBJECT_INFO
{
	short nmeshes; // size=0, offset=0
	short mesh_index; // size=0, offset=2
	long bone_index; // size=0, offset=4
	short* frame_base; // size=0, offset=8
	void (*initialise)(short item_number); // size=0, offset=12
	void (*control)(short item_number); // size=0, offset=16
	void (*floor)(ITEM_INFO* item, int x, int y, int z, int* height); // size=0, offset=20
	void (*ceiling)(ITEM_INFO* item, int x, int y, int z, int* height); // size=0, offset=24
	void (*draw_routine)(ITEM_INFO* item); // size=0, offset=28
	void (*collision)(short item_num, ITEM_INFO* laraitem, COLL_INFO* coll); // size=0, offset=32
	short object_mip; // size=0, offset=36
	short anim_index; // size=0, offset=38
	short hit_points; // size=0, offset=40
	short pivot_length; // size=0, offset=42
	short radius; // size=0, offset=44
	short shadow_size; // size=0, offset=46
	unsigned short bite_offset; // size=0, offset=48
	unsigned short loaded : 1; // offset=50.0
	unsigned short intelligent : 1; // offset=50.1
	unsigned short non_lot : 1; // offset=50.2
	unsigned short save_position : 1; // offset=50.3
	unsigned short save_hitpoints : 1; // offset=50.4
	unsigned short save_flags : 1; // offset=50.5
	unsigned short save_anim : 1; // offset=50.6
	unsigned short semi_transparent : 1; // offset=50.7
	unsigned short water_creature : 1; // offset=51.0
	unsigned short using_drawanimating_item : 1; // offset=51.1
	unsigned short HitEffect : 2; // offset=51.2
	unsigned short undead : 1; // offset=51.4
	unsigned short save_mesh : 1; // offset=51.5
	void (*draw_routine_extra)(ITEM_INFO* item); // size=0, offset=52
	unsigned long explodable_meshbits; // size=0, offset=56
	unsigned long padfuck; // size=0, offset=60
};

struct FOGBULB
{
	float px;
	float py;
	float pz;
	float rad;
	float sqrad;
	float den;
	float r; 
	float g;
	float b;
};

struct PCLIGHT_INFO
{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	long shadow;
	float Inner;
	float Outer;
	float InnerAngle;
	float OuterAngle;
	float Cutoff;
	float nx;
	float ny;
	float nz;
	long ix;
	long iy;
	long iz;
	long inx;
	long iny;
	long inz;
	unsigned char Type;
	unsigned char Pad;
	short	fuckpad;
};

struct room_info
{
	short* data; // size=0, offset=0
	short* door; // size=0, offset=4
	FLOOR_INFO* floor; // size=8, offset=8
	LIGHTINFO* light; // size=32, offset=12
	MESH_INFO* mesh; // size=20, offset=16
	long x; // size=0, offset=20
	long y; // size=0, offset=24
	long z; // size=0, offset=28
	long minfloor; // size=0, offset=32
	long maxceiling; // size=0, offset=36
	short x_size; // size=0, offset=40
	short y_size; // size=0, offset=42
	CVECTOR ambient; // size=4, offset=44
	short num_lights; // size=0, offset=48
	short num_meshes; // size=0, offset=50
	unsigned char ReverbType; // size=0, offset=52
	unsigned char FlipNumber; // size=0, offset=53
	char MeshEffect; // size=0, offset=54
	char bound_active; // size=0, offset=55
	short left; // size=0, offset=56
	short right; // size=0, offset=58
	short top; // size=0, offset=60
	short bottom; // size=0, offset=62
	short test_left; // size=0, offset=64
	short test_right; // size=0, offset=66
	short test_top; // size=0, offset=68
	short test_bottom; // size=0, offset=70
	short item_number; // size=0, offset=72
	short fx_number; // size=0, offset=74
	short flipped_room; // size=0, offset=76
	unsigned short flags; // size=0, offset=78
	int nVerts;
	int nWaterVerts;
	int nShoreVerts;
	LPDIRECT3DVERTEXBUFFER SourceVB;
	short* FaceData;
	float posx;
	float posy;
	float posz;
	D3DVECTOR* vnormals;
	D3DVECTOR* fnormals;
	long* prelight;
	long* prelightwater;
	int	watercalc;
	D3DVECTOR* verts;
	int gt3cnt;
	int gt4cnt;
	PCLIGHT_INFO* pclight;
	FOGBULB* fogbulb;
	int nPCLight;
	int nFogBulbs;
	float cy0;
	float cy1;
	int nRoomlets;
	ROOMLET* pRoomlets;
	float* pRmVtx;		// Roomlet vertex dump
	short* pRmFace;
	int* pRmPrelight;
	int	vDumpSz;		// Vertex dump size
	float fLeft;
	float fRight;
	float fTop;
	float fBottom;
};

struct STATS 
{
	unsigned long Timer; // size=0, offset=0
	unsigned long Distance; // size=0, offset=4
	unsigned long AmmoUsed; // size=0, offset=8
	unsigned long AmmoHits; // size=0, offset=12
	unsigned short Kills; // size=0, offset=16
	unsigned char Secrets; // size=0, offset=18
	unsigned char HealthUsed; // size=0, offset=19
};

struct BLOOD_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short Xvel; // size=0, offset=12
	short Yvel; // size=0, offset=14
	short Zvel; // size=0, offset=16
	short Gravity; // size=0, offset=18
	short RotAng; // size=0, offset=20
	unsigned char sSize; // size=0, offset=22
	unsigned char dSize; // size=0, offset=23
	unsigned char Size; // size=0, offset=24
	unsigned char Friction; // size=0, offset=25
	char RotAdd; // size=0, offset=26
	unsigned char On; // size=0, offset=27
	unsigned char sShade; // size=0, offset=28
	unsigned char dShade; // size=0, offset=29
	unsigned char Shade; // size=0, offset=30
	unsigned char ColFadeSpeed; // size=0, offset=31
	unsigned char FadeToBlack; // size=0, offset=32
	char sLife; // size=0, offset=33
	char Life; // size=0, offset=34
	char Pad; // size=0, offset=35
};

typedef struct lara_info
{
	short item_number; // size=0, offset=0
	short gun_status; // size=0, offset=2
	short gun_type; // size=0, offset=4
	short request_gun_type; // size=0, offset=6
	short last_gun_type; // size=0, offset=8
	short calc_fallspeed; // size=0, offset=10
	short water_status; // size=0, offset=12
	short climb_status; // size=0, offset=14
	short pose_count; // size=0, offset=16
	short hit_frame; // size=0, offset=18
	short hit_direction; // size=0, offset=20
	short air; // size=0, offset=22
	short dive_count; // size=0, offset=24
	short death_count; // size=0, offset=26
	short current_active; // size=0, offset=28
	short current_xvel; // size=0, offset=30
	short current_yvel; // size=0, offset=32
	short current_zvel; // size=0, offset=34
	short spaz_effect_count; // size=0, offset=36
	short flare_age; // size=0, offset=38
	short BurnCount; // size=0, offset=40
	short weapon_item; // size=0, offset=42
	short back_gun; // size=0, offset=44
	short flare_frame; // size=0, offset=46
	short poisoned; // size=0, offset=48
	short dpoisoned; // size=0, offset=50
	unsigned char Anxiety; // size=0, offset=52
	unsigned char wet[15]; // size=15, offset=53
	unsigned short flare_control_left : 1; // offset=68.0 - 0x0001
	unsigned short Unused1 : 1; // offset=68.1 - 0x0002
	unsigned short look : 1; // offset=68.2 - 0x0004
	unsigned short burn : 1; // offset=68.3 - 0x0008
	unsigned short keep_ducked : 1; // offset=68.4 - 0x0010
	unsigned short IsMoving : 1; // offset=68.5 - 0x0020
	unsigned short CanMonkeySwing : 1; // offset=68.6 - 0x0040
	unsigned short BurnBlue : 2; // offset=68.7 - 0x0080 | 0x0100
	unsigned short Gassed : 1; // offset=69.1 - 0x0200
	unsigned short BurnSmoke : 1; // offset=69.2 - 0x0400
	unsigned short IsDucked : 1; // offset=69.3 - 0x0800
	unsigned short has_fired : 1; // offset=69.4 - 0x1000
	unsigned short Busy : 1; // offset=69.5 - 0x2000
	unsigned short LitTorch : 1; // offset=69.6 - 0x4000
	unsigned short IsClimbing : 1; // offset=69.7 - 0x8000
	unsigned short Fired : 1; // offset=70.0 - 0x0001
	long water_surface_dist; // size=0, offset=72
	PHD_VECTOR last_pos; // size=12, offset=76
	FX_INFO* spaz_effect; // size=44, offset=88
	int mesh_effects; // size=0, offset=92
	short* mesh_ptrs[15]; // size=60, offset=96
	ITEM_INFO* target; // size=144, offset=156
	short target_angles[2]; // size=4, offset=160
	short turn_rate; // size=0, offset=164
	short move_angle; // size=0, offset=166
	short head_y_rot; // size=0, offset=168
	short head_x_rot; // size=0, offset=170
	short head_z_rot; // size=0, offset=172
	short torso_y_rot; // size=0, offset=174
	short torso_x_rot; // size=0, offset=176
	short torso_z_rot; // size=0, offset=178
	lara_arm left_arm; // size=20, offset=180
	lara_arm right_arm; // size=20, offset=200
	unsigned short holster; // size=0, offset=220
	creature_info* creature; // size=228, offset=224
	long CornerX; // size=0, offset=228
	long CornerZ; // size=0, offset=232
	char RopeSegment; // size=0, offset=236
	char RopeDirection; // size=0, offset=237
	short RopeArcFront; // size=0, offset=238
	short RopeArcBack; // size=0, offset=240
	short RopeLastX; // size=0, offset=242
	short RopeMaxXForward; // size=0, offset=244
	short RopeMaxXBackward; // size=0, offset=246
	long RopeDFrame; // size=0, offset=248
	long RopeFrame; // size=0, offset=252
	unsigned short RopeFrameRate; // size=0, offset=256
	unsigned short RopeY; // size=0, offset=258
	long RopePtr; // size=0, offset=260
	void* GeneralPtr; // size=0, offset=264
	int RopeOffset; // size=0, offset=268
	unsigned long RopeDownVel; // size=0, offset=272
	char RopeFlag; // size=0, offset=276
	char MoveCount; // size=0, offset=277
	int RopeCount; // size=0, offset=280
	char skelebob; // size=0, offset=284
	char pistols_type_carried; // size=0, offset=285
	char uzis_type_carried; // size=0, offset=286
	char shotgun_type_carried; // size=0, offset=287
	char crossbow_type_carried; // size=0, offset=288
	char hk_type_carried; // size=0, offset=289
	char sixshooter_type_carried; // size=0, offset=290
	char lasersight; // size=0, offset=291
	char silencer; // size=0, offset=292
	char binoculars; // size=0, offset=293
	char crowbar; // size=0, offset=294
	char examine1; // size=0, offset=295
	char examine2; // size=0, offset=296
	char examine3; // size=0, offset=297
	char wetcloth; // size=0, offset=298
	char bottle; // size=0, offset=299
	char puzzleitems[12]; // size=12, offset=300
	unsigned short puzzleitemscombo; // size=0, offset=312
	unsigned short keyitems; // size=0, offset=314
	unsigned short keyitemscombo; // size=0, offset=316
	unsigned short pickupitems; // size=0, offset=318
	unsigned short pickupitemscombo; // size=0, offset=320
	short num_small_medipack; // size=0, offset=322
	short num_large_medipack; // size=0, offset=324
	short num_flares; // size=0, offset=326
	short num_pistols_ammo; // size=0, offset=328
	short num_uzi_ammo; // size=0, offset=330
	short num_revolver_ammo; // size=0, offset=332
	short num_shotgun_ammo1; // size=0, offset=334
	short num_shotgun_ammo2; // size=0, offset=336
	short num_hk_ammo1; // size=0, offset=338
	short num_crossbow_ammo1; // size=0, offset=340
	short num_crossbow_ammo2; // size=0, offset=342
	char location; // size=0, offset=344
	char highest_location; // size=0, offset=345
	char locationPad; // size=0, offset=346
	unsigned char TightRopeOnCount; // size=0, offset=347
	unsigned char TightRopeOff; // size=0, offset=348
	unsigned char TightRopeFall; // size=0, offset=349
	unsigned char ChaffTimer; // size=0, offset=350
} LARA_INFO;

struct savegame_info
{
	short Checksum; // size=0, offset=0
	unsigned short VolumeCD; // size=0, offset=2
	unsigned short VolumeFX; // size=0, offset=4
	short ScreenX; // size=0, offset=6
	short ScreenY; // size=0, offset=8
	unsigned char ControlOption; // size=0, offset=10
	unsigned char VibrateOn; // size=0, offset=11
	char pad[3];
	unsigned char AutoTarget; // size=0, offset=12
	LARA_INFO Lara; // size=352, offset=16
	STATS Level; // size=20, offset=368
	STATS Game; // size=20, offset=388
	short WeaponObject; // size=0, offset=408
	short WeaponAnim; // size=0, offset=410
	short WeaponFrame; // size=0, offset=412
	short WeaponCurrent; // size=0, offset=414
	short WeaponGoal; // size=0, offset=416
	unsigned long CutSceneTriggered1; // size=0, offset=420
	unsigned long CutSceneTriggered2; // size=0, offset=424
	char GameComplete; // size=0, offset=428
	unsigned char CurrentLevel; // size=0, offset=429
	unsigned char CampaignSecrets[4]; // size=4, offset=430
	unsigned char TLCount; // size=0, offset=434
};


struct OBJECT_TEXTURE_VERT
{
	float x;
	float y;
};

struct OBJECT_TEXTURE
{
	uint16_t attribute;
	uint16_t tile_and_flag;
	union
	{
		uint16_t new_flags;
		struct
		{
			uint16_t mapping_corr : 3; // 0..2
			uint16_t : 8;
			uint16_t bump_level : 2; // 11..12
			uint16_t : 2;
			uint16_t is_room_geom : 1; // 15
		};
	};
	struct OBJECT_TEXTURE_VERT vertices[4];
};

struct DYNAMIC
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	unsigned char on; // size=0, offset=12
	unsigned char r; // size=0, offset=13
	unsigned char g; // size=0, offset=14
	unsigned char b; // size=0, offset=15
	unsigned short falloff; // size=0, offset=16
	unsigned char used; // size=0, offset=18
	unsigned char pad1[1]; // size=1, offset=19
	long FalloffScale; // size=0, offset=20
};

struct SMOKE_SPARKS
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short Xvel; // size=0, offset=12
	short Yvel; // size=0, offset=14
	short Zvel; // size=0, offset=16
	short Gravity; // size=0, offset=18
	short RotAng; // size=0, offset=20
	short Flags; // size=0, offset=22
	unsigned char sSize; // size=0, offset=24
	unsigned char dSize; // size=0, offset=25
	unsigned char Size; // size=0, offset=26
	unsigned char Friction; // size=0, offset=27
	unsigned char Scalar; // size=0, offset=28
	unsigned char Def; // size=0, offset=29
	char RotAdd; // size=0, offset=30
	char MaxYvel; // size=0, offset=31
	unsigned char On; // size=0, offset=32
	unsigned char sShade; // size=0, offset=33
	unsigned char dShade; // size=0, offset=34
	unsigned char Shade; // size=0, offset=35
	unsigned char ColFadeSpeed; // size=0, offset=36
	unsigned char FadeToBlack; // size=0, offset=37
	char sLife; // size=0, offset=38
	char Life; // size=0, offset=39
	unsigned char TransType; // size=0, offset=40
	unsigned char FxObj; // size=0, offset=41
	unsigned char NodeNumber; // size=0, offset=42
	unsigned char mirror; // size=0, offset=43
};

struct OBJLIST
{
	short invitem; // size=0, offset=0
	unsigned short yrot; // size=0, offset=2
	unsigned short bright; // size=0, offset=4
};

struct RINGME
{
	OBJLIST current_object_list[100]; // size=600, offset=0
	int ringactive; // size=0, offset=600
	int objlistmovement; // size=0, offset=604
	int curobjinlist; // size=0, offset=608
	int numobjectsinlist; // size=0, offset=612
};

struct COMBINELIST
{
	void(*combine_routine)(int flag); // size=0, offset=0
	short item1; // size=0, offset=4
	short item2; // size=0, offset=6
	short combined_item; // size=0, offset=8
};

struct DOORPOS_DATA
{
	FLOOR_INFO* floor; // size=8, offset=0
	FLOOR_INFO data; // size=8, offset=4
	short block; // size=0, offset=12
};

struct DOOR_DATA
{
	DOORPOS_DATA d1; // size=16, offset=0
	DOORPOS_DATA d1flip; // size=14, offset=14
	DOORPOS_DATA d2; // size=14, offset=28
	DOORPOS_DATA d2flip; // size=14, offset=42
	short Opened; // size=0, offset=56
	short* dptr1; // size=0, offset=58
	short* dptr2; // size=0, offset=62
	short* dptr3; // size=0, offset=66
	short* dptr4; // size=0, offset=70
	char dn1; // size=0, offset=74
	char dn2; // size=0, offset=75
	char dn3; // size=0, offset=76
	char dn4; // size=0, offset=77
	ITEM_INFO* item; // size=144, offset=78
};

struct box_info
{
	unsigned char left; // size=0, offset=0
	unsigned char right; // size=0, offset=1
	unsigned char top; // size=0, offset=2
	unsigned char bottom; // size=0, offset=3
	short height; // size=0, offset=4
	short overlap_index; // size=0, offset=6
};

struct SPARKS
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short Xvel; // size=0, offset=12
	short Yvel; // size=0, offset=14
	short Zvel; // size=0, offset=16
	short Gravity; // size=0, offset=18
	short RotAng; // size=0, offset=20
	short Flags; // size=0, offset=22
	unsigned char sSize; // size=0, offset=24
	unsigned char dSize; // size=0, offset=25
	unsigned char Size; // size=0, offset=26
	unsigned char Friction; // size=0, offset=27
	unsigned char Scalar; // size=0, offset=28
	unsigned char Def; // size=0, offset=29
	char RotAdd; // size=0, offset=30
	char MaxYvel; // size=0, offset=31
	unsigned char On; // size=0, offset=32
	unsigned char sR; // size=0, offset=33
	unsigned char sG; // size=0, offset=34
	unsigned char sB; // size=0, offset=35
	unsigned char dR; // size=0, offset=36
	unsigned char dG; // size=0, offset=37
	unsigned char dB; // size=0, offset=38
	unsigned char R; // size=0, offset=39
	unsigned char G; // size=0, offset=40
	unsigned char B; // size=0, offset=41
	unsigned char ColFadeSpeed; // size=0, offset=42
	unsigned char FadeToBlack; // size=0, offset=43
	unsigned char sLife; // size=0, offset=44
	unsigned char Life; // size=0, offset=45
	unsigned char TransType; // size=0, offset=46
	unsigned char extras; // size=0, offset=47
	char Dynamic; // size=0, offset=48
	unsigned char FxObj; // size=0, offset=49
	unsigned char RoomNumber; // size=0, offset=50
	unsigned char NodeNumber; // size=0, offset=51
};

struct SHATTER_ITEM
{
	SPHERE Sphere; // size=16, offset=0
	ITEM_LIGHT* il; // size=48, offset=16
	short* meshp; // size=0, offset=20
	long Bit; // size=0, offset=24
	short YRot; // size=0, offset=28
	short Flags; // size=0, offset=30
};

struct CUTSEQ_ROUTINES
{
	void(*init_func)(); // size=0, offset=0
	void(*control_func)(); // size=0, offset=4
	void(*end_func)(); // size=0, offset=8
};

struct ACTORME
{
	int offset; // size=0, offset=0
	short objslot; // size=0, offset=4
	short nodes; // size=0, offset=6
};

struct NEW_CUTSCENE
{
	short numactors; // size=0, offset=0
	short numframes; // size=0, offset=2
	int orgx; // size=0, offset=4
	int orgy; // size=0, offset=8
	int orgz; // size=0, offset=12
	int audio_track; // size=0, offset=16
	int camera_offset; // size=0, offset=20
	ACTORME actor_data[10]; // size=80, offset=24
};

struct INVOBJ
{
	short object_number; // size=0, offset=0
	short yoff; // size=0, offset=2
	short scale1; // size=0, offset=4
	short yrot; // size=0, offset=6
	short xrot; // size=0, offset=8
	short zrot; // size=0, offset=10
	short flags; // size=0, offset=12
	short objname; // size=0, offset=14
	unsigned long meshbits; // size=0, offset=16
};

struct BITE_INFO
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	long mesh_num; // size=0, offset=12
};

struct TWOGUN_INFO
{
	PHD_3DPOS pos; // size=20, offset=0
	short life; // size=0, offset=20
	short coil; // size=0, offset=22
	short spin; // size=0, offset=24
	short spinadd; // size=0, offset=26
	short length; // size=0, offset=28
	short dlength; // size=0, offset=30
	short size; // size=0, offset=32
	char r; // size=0, offset=34
	char g; // size=0, offset=35
	char b; // size=0, offset=36
	char fadein; // size=0, offset=37
};

struct AMMOLIST
{
	short invitem; // size=0, offset=0
	short amount; // size=0, offset=2
	unsigned short yrot; // size=0, offset=4
};

struct MENUTHANG
{
	int type; // size=0, offset=0
	char* text; // size=0, offset=4
};

struct VECTOR
{
	long vx;
	long vy;
	long vz;
	long pad;
};

struct AI_info
{
	short zone_number; // size=0, offset=0
	short enemy_zone; // size=0, offset=2
	long distance; // size=0, offset=4
	long ahead; // size=0, offset=8
	long bite; // size=0, offset=12
	short angle; // size=0, offset=16
	short x_angle; // size=0, offset=18
	short enemy_facing; // size=0, offset=20
};

struct RTDECODE
{
	unsigned long length; // size=0, offset=0
	unsigned long off; // size=0, offset=4
	unsigned short counter; // size=0, offset=8
	unsigned short data; // size=0, offset=10
	unsigned char decodetype; // size=0, offset=12
	unsigned char packmethod; // size=0, offset=13
	unsigned short padfuck; // size=0, offset=14
};

struct PACKNODE
{
	short xrot_run; // size=0, offset=0
	short yrot_run; // size=0, offset=2
	short zrot_run; // size=0, offset=4
	short xkey; // size=0, offset=6
	short ykey; // size=0, offset=8
	short zkey; // size=0, offset=10
	RTDECODE decode_x; // size=16, offset=12
	RTDECODE decode_y; // size=16, offset=28
	RTDECODE decode_z; // size=16, offset=44
	unsigned long xlength; // size=0, offset=60
	unsigned long ylength; // size=0, offset=64
	unsigned long zlength; // size=0, offset=68
	char* xpacked; // size=0, offset=72
	char* ypacked; // size=0, offset=76
	char* zpacked; // size=0, offset=80
};

struct NODELOADHEADER
{
	short xkey; // size=0, offset=0
	short ykey; // size=0, offset=2
	short zkey; // size=0, offset=4
	short packmethod; // size=0, offset=6
	short xlength; // size=0, offset=8
	short ylength; // size=0, offset=10
	short zlength; // size=0, offset=12
};
#pragma pack(pop)
