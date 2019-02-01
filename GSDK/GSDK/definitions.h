// idk what happened I store a bunch of shit in here now lol.

#define DECLARE_CLASS( className, baseClassName ) \
		typedef baseClassName BaseClass; \
		typedef className ThisClass;

#define DECLARE_CLASS_GAMEROOT( className, baseClassName )	DECLARE_CLASS( className, baseClassName )
#define DECLARE_CLASS_NOFRIEND( className, baseClassName )	DECLARE_CLASS( className, baseClassName )

#define DECLARE_HANDLE_16BIT(name)	typedef CIntHandle16< struct name##__handle * > name;
#define DECLARE_HANDLE_32BIT(name)	typedef CIntHandle32< struct name##__handle * > name;

#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#define FORWARD_DECLARE_HANDLE(name) typedef struct name##__ *name

#define DECLARE_CLASS_NOBASE( className ) typedef className ThisClass;

// How many bits to use to encode an edict.
#define	MAX_EDICT_BITS				11			// # of bits needed to represent max edicts
// Max # of edicts in a level
#define	MAX_EDICTS					(1<<MAX_EDICT_BITS)

// Used for networking ehandles.
#define NUM_ENT_ENTRY_BITS		(MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES			(1 << NUM_ENT_ENTRY_BITS)
#define ENT_ENTRY_MASK			(NUM_ENT_ENTRIES - 1)
#define INVALID_EHANDLE_INDEX	0xFFFFFFFF

#define NUM_SERIAL_NUM_BITS		(32 - NUM_ENT_ENTRY_BITS)

#define Q_stricmp	_stricmp
// Networked ehandles use less bits to encode the serial number.
#define NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS	10
#define NUM_NETWORKED_EHANDLE_BITS					(MAX_EDICT_BITS + NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS)
#define INVALID_NETWORKED_EHANDLE_VALUE	((1 << NUM_NETWORKED_EHANDLE_BITS) - 1)
#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2
#define VALVE_RAND_MAX 0x7FFF

#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<9)	// In water

// NOTE if you move things up, make sure to change this value
#define PLAYER_FLAG_BITS		10

#define	FL_FLY					(1<<10)	// Changes the SV_Movestep() behavior to not need to be on ground
#define	FL_SWIM					(1<<11)	// Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
#define	FL_CONVEYOR				(1<<12)
#define	FL_NPC					(1<<13)
#define	FL_GODMODE				(1<<14)
#define	FL_NOTARGET				(1<<15)
#define	FL_AIMTARGET			(1<<16)	// set if the crosshair needs to aim onto the entity
#define	FL_PARTIALGROUND		(1<<17)	// not all corners are valid
#define FL_STATICPROP			(1<<18)	// Eetsa static prop!		
#define FL_GRAPHED				(1<<19) // worldgraph has this ent listed as something that blocks a connection
#define FL_GRENADE				(1<<20)
#define FL_STEPMOVEMENT			(1<<21)	// Changes the SV_Movestep() behavior to not do any processing
#define FL_DONTTOUCH			(1<<22)	// Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set
#define FL_BASEVELOCITY			(1<<23)	// Base velocity has been applied this frame (used to convert base velocity into momentum)
#define FL_WORLDBRUSH			(1<<24)	// Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
#define FL_OBJECT				(1<<25) // Terrible name. This is an object that NPCs should see. Missiles, for example.
#define FL_KILLME				(1<<26)	// This entity is marked for death -- will be freed by game DLL
#define FL_ONFIRE				(1<<27)	// You know...
#define FL_DISSOLVING			(1<<28) // We're dissolving!
#define FL_TRANSRAGDOLL			(1<<29) // In the process of turning into a client side ragdoll.
#define FL_UNBLOCKABLE_BY_PLAYER (1<<30) // pusher that can't be blocked by the player


#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_ATTACK3	(1 << 25)

#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT		0x00000200	// bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK	0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0	0x00000400	// bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1	0x00000800	
#define BONE_USED_BY_VERTEX_LOD2	0x00001000  
#define BONE_USED_BY_VERTEX_LOD3	0x00002000
#define BONE_USED_BY_VERTEX_LOD4	0x00004000
#define BONE_USED_BY_VERTEX_LOD5	0x00008000
#define BONE_USED_BY_VERTEX_LOD6	0x00010000
#define BONE_USED_BY_VERTEX_LOD7	0x00020000
#define BONE_USED_BY_BONE_MERGE		0x00040000	// bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_AREA_STATE_BYTES		32
#define MAX_AREA_PORTAL_STATE_BYTES 24
#define PRINTF_FORMAT_STRING _Printf_format_string_
#define SCANF_FORMAT_STRING _Scanf_format_string_impl_

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace


// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define	SURF_LIGHT		0x0001		// value will hold the light strength
#define	SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define	SURF_SKY		0x0004		// don't draw, but add to skybox
#define	SURF_WARP		0x0008		// turbulent water warp
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define	SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	SURF_NODRAW		0x0080	// don't bother referencing the texture

#define	SURF_HINT		0x0100	// make a primary bsp splitter

#define	SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface 
#define SURF_HITBOX		0x8000	// surface is part of a hitbox



// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)


#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS	"Morph Targets"

#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)


// OVERALL Coordinate Size Limits used in COMMON.C MSG_*BitCoord() Routines (and someday the HUD)
#define	COORD_INTEGER_BITS			14
#define COORD_FRACTIONAL_BITS		5
#define COORD_DENOMINATOR			(1<<(COORD_FRACTIONAL_BITS))
#define COORD_RESOLUTION			(1.0/(COORD_DENOMINATOR))

// Special threshold for networking multiplayer origins
#define COORD_INTEGER_BITS_MP		11
#define COORD_FRACTIONAL_BITS_MP_LOWPRECISION 3
#define COORD_DENOMINATOR_LOWPRECISION			(1<<(COORD_FRACTIONAL_BITS_MP_LOWPRECISION))
#define COORD_RESOLUTION_LOWPRECISION			(1.0/(COORD_DENOMINATOR_LOWPRECISION))

#define NORMAL_FRACTIONAL_BITS		11
#define NORMAL_DENOMINATOR			( (1<<(NORMAL_FRACTIONAL_BITS)) - 1 )
#define NORMAL_RESOLUTION			(1.0/(NORMAL_DENOMINATOR))

// this is limited by the network fractional bits used for coords
// because net coords will be only be accurate to 5 bits fractional
// Standard collision test epsilon
// 1/32nd inch collision epsilon
#define DIST_EPSILON (0.03125)

///////////////////////////////////////////////////////////////////////////////////////////////////////
// The following are Bit Packing Diagrams for client/server Coordinate BitField Messages
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//							"Coordinates" = +/-16384.9375	(21 Bits Max)
//
// | IntegerFlagBit:1 | FractionFlagBit:1 | SignBit:1 | IntegerField:14 | FractionPart:4 |		Total		
// --------------------------------------------------------------------------------------------------
//			0					0				-				-				-				2
//			0					1				x				-				xxxx			7
//			1					0				x		xxxxxxxxxxxxx			-				17
//			1					1				x		xxxxxxxxxxxxx			xxxx			21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//							"Vec3Coordinate" = Up to 3 Coordinates (66 Bits Max)
//
// | NonZeroX:1 | NonZeroY:1 | NonZeroZ:1 |  0..3 "Coordinates"	|	BitField Total
// -------------------------------------------------------------------------------
//			0			0				0			-					3
//			0			0				1			7..21 Bits			10..24
//			0			1				0			7..21 Bits			10..24
//			1			0				0			7..21 Bits			10..24
//			0			1				1			14..42 Bits			17..45
//			1			1				0			14..42 Bits			17..45
//			1			0				1			14..42 Bits			17..45
//			1			1				1			21..63 Bits			24..66
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
// The following are Bit Packing Diagrams for client/server Normal BitField Messages
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//							"Normals" = +/-1.0	(12 Bits Total)
//
// The only gotcha here is that normalization occurs so that 
// 011111111111 = +1.0 and 1111111111111 = -1.0
//
// | SignBit:1 | FractionPart:11 |		Total		
// --------------------------------------------------------------------------------------------------
//			1		xxxxxxxxxxx			12
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//							"Vec3Normal" = Up to 3 Coordinates (27 Bits Max)
//
// | NonZeroX:1 | NonZeroY:1 |  0..2 "Coordinates"	| Z Sign Bit |	BitField Total
// -------------------------------------------------------------------------------
//			0			0				-					x			3
//			0			1			12 Bits					x			14
//			1			0			12 Bits					x			14
//			1			1			24 Bits					x			27
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline T WordSwapC(T w)
{
	UINT16 temp;

	temp = ((*((UINT16 *)&w) & 0xff00) >> 8);
	temp |= ((*((UINT16 *)&w) & 0x00ff) << 8);

	return *((T*)&temp);
}

template <typename T>
inline T DWordSwapC(T dw)
{
	UINT32 temp;

	temp = *((UINT32 *)&dw) >> 24;
	temp |= ((*((UINT32 *)&dw) & 0x00FF0000) >> 8);
	temp |= ((*((UINT32 *)&dw) & 0x0000FF00) << 8);
	temp |= ((*((UINT32 *)&dw) & 0x000000FF) << 24);

	return *((T*)&temp);
}

template <typename T>
inline T QWordSwapC(T dw)
{
	// Assert sizes passed to this are already correct, otherwise
	// the cast to uint64 * below is unsafe and may have wrong results 
	// or even crash.

	UINT64 temp;

	temp = *((UINT64 *)&dw) >> 56;
	temp |= ((*((UINT64 *)&dw) & 0x00FF000000000000ull) >> 40);
	temp |= ((*((UINT64 *)&dw) & 0x0000FF0000000000ull) >> 24);
	temp |= ((*((UINT64 *)&dw) & 0x000000FF00000000ull) >> 8);
	temp |= ((*((UINT64 *)&dw) & 0x00000000FF000000ull) << 8);
	temp |= ((*((UINT64 *)&dw) & 0x0000000000FF0000ull) << 24);
	temp |= ((*((UINT64 *)&dw) & 0x000000000000FF00ull) << 40);
	temp |= ((*((UINT64 *)&dw) & 0x00000000000000FFull) << 56);

	return *((T*)&temp);
}
#define BITBUF_INLINE FORCEINLINE

#define WordSwap  WordSwapC
#define DWordSwap DWordSwapC
#define QWordSwap QWordSwapC
#define SafeSwapFloat( pOut, pIn ) (*((UINT*)pOut) = DWordSwap( *((UINT*)pIn) ))
inline short BigShort(short val) { int test = 1; return (*(char *)&test == 1) ? WordSwap(val) : val; }
inline UINT16 BigWord(UINT16 val) { int test = 1; return (*(char *)&test == 1) ? WordSwap(val) : val; }
inline long BigLong(long val) { int test = 1; return (*(char *)&test == 1) ? DWordSwap(val) : val; }
inline UINT32 BigDWord(UINT32 val) { int test = 1; return (*(char *)&test == 1) ? DWordSwap(val) : val; }
inline short LittleShort(short val) { int test = 1; return (*(char *)&test == 1) ? val : WordSwap(val); }
inline UINT16 LittleWord(UINT16 val) { int test = 1; return (*(char *)&test == 1) ? val : WordSwap(val); }
inline long LittleLong(long val) { int test = 1; return (*(char *)&test == 1) ? val : DWordSwap(val); }
inline UINT32 LittleDWord(UINT32 val) { int test = 1; return (*(char *)&test == 1) ? val : DWordSwap(val); }
inline UINT64 LittleQWord(UINT64 val) { int test = 1; return (*(char *)&test == 1) ? val : QWordSwap(val); }
inline short SwapShort(short val) { return WordSwap(val); }
inline UINT16 SwapWord(UINT16 val) { return WordSwap(val); }
inline long SwapLong(long val) { return DWordSwap(val); }
inline UINT32 SwapDWord(UINT32 val) { return DWordSwap(val); }

// Pass floats by pointer for swapping to avoid truncation in the fpu
inline void BigFloat(float *pOut, const float *pIn) { int test = 1; (*(char *)&test == 1) ? SafeSwapFloat(pOut, pIn) : (*pOut = *pIn); }
inline void LittleFloat(float *pOut, const float *pIn) { int test = 1; (*(char *)&test == 1) ? (*pOut = *pIn) : SafeSwapFloat(pOut, pIn); }
inline void SwapFloat(float *pOut, const float *pIn) { SafeSwapFloat(pOut, pIn); }

FORCEINLINE unsigned long LoadLittleDWord(const unsigned long *base, unsigned int dwordIndex)
{
	return LittleDWord(base[dwordIndex]);
}

FORCEINLINE void StoreLittleDWord(unsigned long *base, unsigned int dwordIndex, unsigned long dword)
{
	base[dwordIndex] = LittleDWord(dword);
}

#define  STDCALL				__stdcall
#define  FASTCALL				__fastcall
#define  FORCEINLINE			__forceinline
// GCC 3.4.1 has a bug in supporting forced inline of templated functions
// this macro lets us not force inlining in that case
#define FORCEINLINE_TEMPLATE	__forceinline
#define Plat_FastMemset memset
#define Plat_FastMemcpy memcpy
#define MAX_INCOMING_MESSAGES		250
// Size of command send buffer
#define MAX_CMD_BUFFER				4000


enum UpdateType
{
	EnterPVS = 0,	// Entity came back into pvs, create new entity if one doesn't exist

	LeavePVS,		// Entity left pvs

	DeltaEnt,		// There is a delta for this entity.
	PreserveEnt,	// Entity stays alive but no delta ( could be LOD, or just unchanged )

	Finished,		// finished parsing entities successfully
	Failed,			// parsing error occured while reading entities
};

// Flags for delta encoding header
enum
{
	FHDR_ZERO = 0x0000,
	FHDR_LEAVEPVS = 0x0001,
	FHDR_DELETE = 0x0002,
	FHDR_ENTERPVS = 0x0004,
};



#define INSTANCE_BASELINE_TABLENAME	"instancebaseline"
#define LIGHT_STYLES_TABLENAME		"lightstyles"
#define USER_INFO_TABLENAME			"userinfo"
#define SERVER_STARTUP_DATA_TABLENAME	"server_query_info"	// the name is a remnant...


//#define CURRENT_PROTOCOL    1


#define DELTA_OFFSET_BITS 5
#define DELTA_OFFSET_MAX ( ( 1 << DELTA_OFFSET_BITS ) - 1 )

#define DELTASIZE_BITS		20	// must be: 2^DELTASIZE_BITS > (NET_MAX_PAYLOAD * 8)

// Largest # of commands to send in a packet
#define NUM_NEW_COMMAND_BITS		4
#define MAX_NEW_COMMANDS			((1 << NUM_NEW_COMMAND_BITS)-1)

// Max number of history commands to send ( 2 by default ) in case of dropped packets
#define NUM_BACKUP_COMMAND_BITS		3
#define MAX_BACKUP_COMMANDS			((1 << NUM_BACKUP_COMMAND_BITS)-1)


#define PROTOCOL_AUTHCERTIFICATE 0x01   // Connection from client is using a WON authenticated certificate
#define PROTOCOL_HASHEDCDKEY     0x02	// Connection from client is using hashed CD key because WON comm. channel was unreachable
#define PROTOCOL_STEAM			 0x03	// Steam certificates
#define PROTOCOL_LASTVALID       0x03    // Last valid protocol

#define CONNECTIONLESS_HEADER			0xFFFFFFFF	// all OOB packet start with this sequence
#define STEAM_KEYSIZE				2048  // max size needed to contain a steam authentication key (both server and client)

// each channel packet has 1 byte of FLAG bits
#define PACKET_FLAG_RELIABLE			(1<<0)	// packet contains subchannel stream data
#define PACKET_FLAG_COMPRESSED			(1<<1)	// packet is compressed
#define PACKET_FLAG_ENCRYPTED			(1<<2)  // packet is encrypted
#define PACKET_FLAG_SPLIT				(1<<3)  // packet is split
#define PACKET_FLAG_CHOKED				(1<<4)  // packet was choked by sender

// NOTE:  Bits 5, 6, and 7 are used to specify the # of padding bits at the end of the packet!!!
#define ENCODE_PAD_BITS( x ) ( ( x << 5 ) & 0xff )
#define DECODE_PAD_BITS( x ) ( ( x >> 5 ) & 0xff )

// shared commands used by all streams, handled by stream layer, TODO

#define	net_NOP 		0			// nop command used for padding
#define net_Disconnect	1			// disconnect, last message in connection
#define net_File		2			// file transmission message request/deny

#define net_Tick		3			// send last world tick
#define net_StringCmd	4			// a string command
#define net_SetConVar	5			// sends one/multiple convar settings
#define	net_SignonState	6			// signals current signon state

//
// server to client
//

#define	svc_Print			7		// print text to console
#define	svc_ServerInfo		8		// first message from server about game, map etc
#define svc_SendTable		9		// sends a sendtable description for a game class
#define svc_ClassInfo		10		// Info about classes (first byte is a CLASSINFO_ define).							
#define	svc_SetPause		11		// tells client if server paused or unpaused


#define	svc_CreateStringTable	12	// inits shared string tables
#define	svc_UpdateStringTable	13	// updates a string table

#define svc_VoiceInit		14		// inits used voice codecs & quality
#define svc_VoiceData		15		// Voicestream data from the server

// #define svc_HLTV			16		// HLTV control messages

#define	svc_Sounds			17		// starts playing sound

#define	svc_SetView			18		// sets entity as point of view
#define	svc_FixAngle		19		// sets/corrects players viewangle
#define	svc_CrosshairAngle	20		// adjusts crosshair in auto aim mode to lock on traget

#define	svc_BSPDecal		21		// add a static decal to the worl BSP
// NOTE: This is now unused!
//#define	svc_TerrainMod		22		// modification to the terrain/displacement

// Message from server side to client side entity
#define svc_UserMessage		23	// a game specific message 
#define svc_EntityMessage	24	// a message for an entity
#define	svc_GameEvent		25	// global game event fired

#define	svc_PacketEntities	26  // non-delta compressed entities

#define	svc_TempEntities	27	// non-reliable event object

#define svc_Prefetch		28	// only sound indices for now

#define svc_Menu			29	// display a menu from a plugin

#define svc_GameEventList	30	// list of known games events and fields

#define svc_GetCvarValue	31	// Server wants to know the value of a cvar on the client.

#define SVC_LASTMSG			31	// last known server messages

//
// client to server
//

#define clc_ClientInfo			8		// client info (table CRC etc)
#define	clc_Move				9		// [CUserCmd]
#define clc_VoiceData			10      // Voicestream data from a client
#define clc_BaselineAck			11		// client acknowledges a new baseline seqnr
#define clc_ListenEvents		12		// client acknowledges a new baseline seqnr
#define clc_RespondCvarValue	13		// client is responding to a svc_GetCvarValue message.
#define clc_FileCRCCheck		14		// client is sending a file's CRC to the server to be verified.

#define CLC_LASTMSG			14		//	last known client message

#define RES_FATALIFMISSING	(1<<0)   // Disconnect if we can't get this file.
#define RES_PRELOAD			(1<<1)  // Load on client rather than just reserving name

#define SIGNONSTATE_NONE		0	// no state yet, about to connect
#define SIGNONSTATE_CHALLENGE	1	// client challenging server, all OOB packets
#define SIGNONSTATE_CONNECTED	2	// client is connected to server, netchans ready
#define SIGNONSTATE_NEW			3	// just got serverinfo and string tables
#define SIGNONSTATE_PRESPAWN	4	// received signon buffers
#define SIGNONSTATE_SPAWN		5	// ready to receive entity packets
#define SIGNONSTATE_FULL		6	// we are fully connected, first non-delta packet received
#define SIGNONSTATE_CHANGELEVEL	7	// server is changing level, please wait

#define	LIFE_ALIVE				0 // alive
#define	LIFE_DYING				1 // playing death animation or still falling off of a ledge waiting to hit ground
#define	LIFE_DEAD				2 // dead. lying still.
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY	4


enum PLAYER_ANIM
{
	PLAYER_IDLE,
	PLAYER_WALK,
	PLAYER_JUMP,
	PLAYER_SUPERJUMP,
	PLAYER_DIE,
	PLAYER_ATTACK1,
	PLAYER_IN_VEHICLE,

	// TF Player animations
	PLAYER_RELOAD,
	PLAYER_START_AIMING,
	PLAYER_LEAVE_AIMING,
};
enum stepsoundtimes_t
{
	STEPSOUNDTIME_NORMAL = 0,
	STEPSOUNDTIME_ON_LADDER,
	STEPSOUNDTIME_WATER_KNEE,
	STEPSOUNDTIME_WATER_FOOT,
};
enum soundlevel_t
{
	SNDLVL_NONE = 0,

	SNDLVL_20dB = 20,			// rustling leaves
	SNDLVL_25dB = 25,			// whispering
	SNDLVL_30dB = 30,			// library
	SNDLVL_35dB = 35,
	SNDLVL_40dB = 40,
	SNDLVL_45dB = 45,			// refrigerator

	SNDLVL_50dB = 50,	// 3.9	// average home
	SNDLVL_55dB = 55,	// 3.0

	SNDLVL_IDLE = 60,	// 2.0	
	SNDLVL_60dB = 60,	// 2.0	// normal conversation, clothes dryer

	SNDLVL_65dB = 65,	// 1.5	// washing machine, dishwasher
	SNDLVL_STATIC = 66,	// 1.25

	SNDLVL_70dB = 70,	// 1.0	// car, vacuum cleaner, mixer, electric sewing machine

	SNDLVL_NORM = 75,
	SNDLVL_75dB = 75,	// 0.8	// busy traffic

	SNDLVL_80dB = 80,	// 0.7	// mini-bike, alarm clock, noisy restaurant, office tabulator, outboard motor, passing snowmobile
	SNDLVL_TALKING = 80,	// 0.7
	SNDLVL_85dB = 85,	// 0.6	// average factory, electric shaver
	SNDLVL_90dB = 90,	// 0.5	// screaming child, passing motorcycle, convertible ride on frw
	SNDLVL_95dB = 95,
	SNDLVL_100dB = 100,	// 0.4	// subway train, diesel truck, woodworking shop, pneumatic drill, boiler shop, jackhammer
	SNDLVL_105dB = 105,			// helicopter, power mower
	SNDLVL_110dB = 110,			// snowmobile drvrs seat, inboard motorboat, sandblasting
	SNDLVL_120dB = 120,			// auto horn, propeller aircraft
	SNDLVL_130dB = 130,			// air raid siren

	SNDLVL_GUNFIRE = 140,	// 0.27	// THRESHOLD OF PAIN, gunshot, jet engine
	SNDLVL_140dB = 140,	// 0.2

	SNDLVL_150dB = 150,	// 0.2

	SNDLVL_180dB = 180,			// rocket launching

	// NOTE: Valid soundlevel_t values are 0-255.
	//       256-511 are reserved for sounds using goldsrc compatibility attenuation.
};
enum
{
	CHAN_REPLACE = -1,
	CHAN_AUTO = 0,
	CHAN_WEAPON = 1,
	CHAN_VOICE = 2,
	CHAN_ITEM = 3,
	CHAN_BODY = 4,
	CHAN_STREAM = 5,		// allocate stream channel from the static or dynamic area
	CHAN_STATIC = 6,		// allocate channel from the static area 
	CHAN_VOICE2 = 7,
	CHAN_VOICE_BASE = 8,		// allocate channel for network voice data
	CHAN_USER_BASE = (CHAN_VOICE_BASE + 128)		// Anything >= this number is allocated to game code.
};
#define VOL_NORM	1.0f
#define	PITCH_NORM		100			// non-pitch shifted
#define PITCH_LOW		95			// other values are possible - 0-255, where 255 is very high
#define PITCH_HIGH		120

struct CSoundParameters
{
	CSoundParameters()
	{
		channel = CHAN_AUTO; // 0
		volume = VOL_NORM;  // 1.0f
		pitch = PITCH_NORM; // 100

		pitchlow = PITCH_NORM;
		pitchhigh = PITCH_NORM;

		soundlevel = SNDLVL_NORM; // 75dB
		soundname[0] = 0;
		play_to_owner_only = false;
		count = 0;

		delay_msec = 0;
	}

	int				channel;
	float			volume;
	int				pitch;
	int				pitchlow, pitchhigh;
	soundlevel_t	soundlevel;
	// For weapon sounds...
	bool			play_to_owner_only;
	int				count;
	char 			soundname[128];
	int				delay_msec;
};


struct surfacephysicsparams_t
{
	// vphysics physical properties
	float			friction;
	float			elasticity;				// collision elasticity - used to compute coefficient of restitution
	float			density;				// physical density (in kg / m^3)
	float			thickness;				// material thickness if not solid (sheet materials) in inches
	float			dampening;
};
struct surfaceaudioparams_t
{
	// sounds / audio data
	float			reflectivity;		// like elasticity, but how much sound should be reflected by this surface
	float			hardnessFactor;	// like elasticity, but only affects impact sound choices
	float			roughnessFactor;	// like friction, but only affects scrape sound choices

// audio thresholds
	float			roughThreshold;	// surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float			hardThreshold;	// surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float			hardVelocityThreshold;	// collision velocity > this causes "hard" impacts, < this causes "soft" impacts
									// NOTE: Hard impacts must meet both hardnessFactor AND velocity thresholds
};
struct surfacesoundnames_t
{
	unsigned short	stepleft;
	unsigned short	stepright;

	unsigned short	impactSoft;
	unsigned short	impactHard;

	unsigned short	scrapeSmooth;
	unsigned short	scrapeRough;

	unsigned short	bulletImpact;
	unsigned short	rolling;

	unsigned short	breakSound;
	unsigned short	strainSound;
};

struct surfacegameprops_t
{
	// game movement data
	float			maxSpeedFactor;			// Modulates player max speed when walking on this surface
	float			jumpFactor;				// Indicates how much higher the player should jump when on the surface
// Game-specific data
	unsigned short	material;
	// Indicates whether or not the player is on a ladder.
	unsigned char	climbable;
	unsigned char	pad;
};
struct surfacedata_t
{
	surfacephysicsparams_t	physics;	// physics parameters
	surfaceaudioparams_t	audio;		// audio parameters
	surfacesoundnames_t		sounds;		// names of linked sounds
	surfacegameprops_t		game;		// Game data / properties


};
enum HDRType_t
{
	HDR_TYPE_NONE,
	HDR_TYPE_INTEGER,
	HDR_TYPE_FLOAT,
};
enum CompiledVtfFlags
{
	// flags from the *.txt config file
	TEXTUREFLAGS_POINTSAMPLE = 0x00000001,
	TEXTUREFLAGS_TRILINEAR = 0x00000002,
	TEXTUREFLAGS_CLAMPS = 0x00000004,
	TEXTUREFLAGS_CLAMPT = 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC = 0x00000010,
	TEXTUREFLAGS_HINT_DXT5 = 0x00000020,
	TEXTUREFLAGS_SRGB = 0x00000040,
	TEXTUREFLAGS_NORMAL = 0x00000080,
	TEXTUREFLAGS_NOMIP = 0x00000100,
	TEXTUREFLAGS_NOLOD = 0x00000200,
	TEXTUREFLAGS_ALL_MIPS = 0x00000400,
	TEXTUREFLAGS_PROCEDURAL = 0x00000800,

	// These are automatically generated by vtex from the texture data.
	TEXTUREFLAGS_ONEBITALPHA = 0x00001000,
	TEXTUREFLAGS_EIGHTBITALPHA = 0x00002000,

	// newer flags from the *.txt config file
	TEXTUREFLAGS_ENVMAP = 0x00004000,
	TEXTUREFLAGS_RENDERTARGET = 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET = 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE = 0x00020000,
	TEXTUREFLAGS_SINGLECOPY = 0x00040000,

	TEXTUREFLAGS_UNUSED_00080000 = 0x00080000,
	TEXTUREFLAGS_UNUSED_00100000 = 0x00100000,
	TEXTUREFLAGS_UNUSED_00200000 = 0x00200000,
	TEXTUREFLAGS_UNUSED_00400000 = 0x00400000,

	TEXTUREFLAGS_NODEPTHBUFFER = 0x00800000,

	TEXTUREFLAGS_UNUSED_01000000 = 0x01000000,

	TEXTUREFLAGS_CLAMPU = 0x02000000,

	TEXTUREFLAGS_VERTEXTEXTURE = 0x04000000,					// Useable as a vertex texture

	TEXTUREFLAGS_SSBUMP = 0x08000000,

	TEXTUREFLAGS_UNUSED_10000000 = 0x10000000,

	// Clamp to border color on all texture coordinates
	TEXTUREFLAGS_BORDER = 0x20000000,

	TEXTUREFLAGS_UNUSED_40000000 = 0x40000000,
	TEXTUREFLAGS_UNUSED_80000000 = 0x80000000,
};
enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};
typedef struct player_info_s
{
	char			name[32];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[32 + 1];
	// friends identification number
	long			friendsID;
	// friends name
	char			friendsName[32];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	int				customFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
} player_info_t;
enum VGuiPanel_t
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};
// In-game panels are cropped to the current engine viewport size
enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};
enum PaintMode_t
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2), // software cursor, if appropriate
};
struct model_t;
enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};
struct IntRect
{
	int x0;
	int y0;
	int x1;
	int y1;
};
enum PlayerAnimEvent_t
{
	PLAYERANIMEVENT_ATTACK_PRIMARY,
	PLAYERANIMEVENT_ATTACK_SECONDARY,
	PLAYERANIMEVENT_ATTACK_GRENADE,
	PLAYERANIMEVENT_RELOAD,
	PLAYERANIMEVENT_RELOAD_LOOP,
	PLAYERANIMEVENT_RELOAD_END,
	PLAYERANIMEVENT_JUMP,
	PLAYERANIMEVENT_SWIM,
	PLAYERANIMEVENT_DIE,
	PLAYERANIMEVENT_FLINCH_CHEST,
	PLAYERANIMEVENT_FLINCH_HEAD,
	PLAYERANIMEVENT_FLINCH_LEFTARM,
	PLAYERANIMEVENT_FLINCH_RIGHTARM,
	PLAYERANIMEVENT_FLINCH_LEFTLEG,
	PLAYERANIMEVENT_FLINCH_RIGHTLEG,
	PLAYERANIMEVENT_DOUBLEJUMP,

	// Cancel.
	PLAYERANIMEVENT_CANCEL,
	PLAYERANIMEVENT_SPAWN,

	// Snap to current yaw exactly
	PLAYERANIMEVENT_SNAP_YAW,

	PLAYERANIMEVENT_CUSTOM,				// Used to play specific activities
	PLAYERANIMEVENT_CUSTOM_GESTURE,
	PLAYERANIMEVENT_CUSTOM_SEQUENCE,	// Used to play specific sequences
	PLAYERANIMEVENT_CUSTOM_GESTURE_SEQUENCE,

	// TF Specific. Here until there's a derived game solution to this.
	PLAYERANIMEVENT_ATTACK_PRE,
	PLAYERANIMEVENT_ATTACK_POST,
	PLAYERANIMEVENT_GRENADE1_DRAW,
	PLAYERANIMEVENT_GRENADE2_DRAW,
	PLAYERANIMEVENT_GRENADE1_THROW,
	PLAYERANIMEVENT_GRENADE2_THROW,
	PLAYERANIMEVENT_VOICE_COMMAND_GESTURE,

	PLAYERANIMEVENT_COUNT
};
typedef enum
{
	ACT_INVALID = -1,			// So we have something more succint to check for than '-1'
	ACT_RESET = 0,				// Set m_Activity to this invalid value to force a reset to m_IdealActivity
	ACT_IDLE,
	ACT_TRANSITION,
	ACT_COVER,					// FIXME: obsolete? redundant with ACT_COVER_LOW?
	ACT_COVER_MED,				// FIXME: unsupported?
	ACT_COVER_LOW,				// FIXME: rename ACT_IDLE_CROUCH?
	ACT_WALK,
	ACT_WALK_AIM,
	ACT_WALK_CROUCH,
	ACT_WALK_CROUCH_AIM,
	ACT_RUN,
	ACT_RUN_AIM,
	ACT_RUN_CROUCH,
	ACT_RUN_CROUCH_AIM,
	ACT_RUN_PROTECTED,
	ACT_SCRIPT_CUSTOM_MOVE,
	ACT_RANGE_ATTACK1,
	ACT_RANGE_ATTACK2,
	ACT_RANGE_ATTACK1_LOW,		// FIXME: not used yet, crouched versions of the range attack
	ACT_RANGE_ATTACK2_LOW,		// FIXME: not used yet, crouched versions of the range attack
	ACT_DIESIMPLE,
	ACT_DIEBACKWARD,
	ACT_DIEFORWARD,
	ACT_DIEVIOLENT,
	ACT_DIERAGDOLL,
	ACT_FLY,				// Fly (and flap if appropriate)
	ACT_HOVER,
	ACT_GLIDE,
	ACT_SWIM,
	ACT_JUMP,
	ACT_HOP,				// vertical jump
	ACT_LEAP,				// long forward jump
	ACT_LAND,
	ACT_CLIMB_UP,
	ACT_CLIMB_DOWN,
	ACT_CLIMB_DISMOUNT,
	ACT_SHIPLADDER_UP,
	ACT_SHIPLADDER_DOWN,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_ROLL_LEFT,			// tuck and roll, left
	ACT_ROLL_RIGHT,			// tuck and roll, right
	ACT_TURN_LEFT,			// turn quickly left (stationary)
	ACT_TURN_RIGHT,			// turn quickly right (stationary)
	ACT_CROUCH,				// FIXME: obsolete? only used be soldier (the act of crouching down from a standing position)
	ACT_CROUCHIDLE,			// FIXME: obsolete? only used be soldier (holding body in crouched position (loops))
	ACT_STAND,				// FIXME: obsolete? should be transition (the act of standing from a crouched position)
	ACT_USE,
	ACT_SIGNAL1,
	ACT_SIGNAL2,
	ACT_SIGNAL3,

	ACT_SIGNAL_ADVANCE,		// Squad handsignals, specific.
	ACT_SIGNAL_FORWARD,
	ACT_SIGNAL_GROUP,
	ACT_SIGNAL_HALT,
	ACT_SIGNAL_LEFT,
	ACT_SIGNAL_RIGHT,
	ACT_SIGNAL_TAKECOVER,

	ACT_LOOKBACK_RIGHT,		// look back over shoulder without turning around.
	ACT_LOOKBACK_LEFT,
	ACT_COWER,				// FIXME: unused, should be more extreme version of crouching
	ACT_SMALL_FLINCH,		// FIXME: needed? shouldn't flinching be down with overlays?
	ACT_BIG_FLINCH,
	ACT_MELEE_ATTACK1,
	ACT_MELEE_ATTACK2,
	ACT_RELOAD,
	ACT_RELOAD_START,
	ACT_RELOAD_FINISH,
	ACT_RELOAD_LOW,
	ACT_ARM,				// pull out gun, for instance
	ACT_DISARM,				// reholster gun
	ACT_DROP_WEAPON,
	ACT_DROP_WEAPON_SHOTGUN,
	ACT_PICKUP_GROUND,		// pick up something in front of you on the ground
	ACT_PICKUP_RACK,		// pick up something from a rack or shelf in front of you.
	ACT_IDLE_ANGRY,			// FIXME: being used as an combat ready idle?  alternate idle animation in which the monster is clearly agitated. (loop)

	ACT_IDLE_RELAXED,
	ACT_IDLE_STIMULATED,
	ACT_IDLE_AGITATED,
	ACT_IDLE_STEALTH,
	ACT_IDLE_HURT,

	ACT_WALK_RELAXED,
	ACT_WALK_STIMULATED,
	ACT_WALK_AGITATED,
	ACT_WALK_STEALTH,

	ACT_RUN_RELAXED,
	ACT_RUN_STIMULATED,
	ACT_RUN_AGITATED,
	ACT_RUN_STEALTH,

	ACT_IDLE_AIM_RELAXED,
	ACT_IDLE_AIM_STIMULATED,
	ACT_IDLE_AIM_AGITATED,
	ACT_IDLE_AIM_STEALTH,

	ACT_WALK_AIM_RELAXED,
	ACT_WALK_AIM_STIMULATED,
	ACT_WALK_AIM_AGITATED,
	ACT_WALK_AIM_STEALTH,

	ACT_RUN_AIM_RELAXED,
	ACT_RUN_AIM_STIMULATED,
	ACT_RUN_AIM_AGITATED,
	ACT_RUN_AIM_STEALTH,

	ACT_CROUCHIDLE_STIMULATED,
	ACT_CROUCHIDLE_AIM_STIMULATED,
	ACT_CROUCHIDLE_AGITATED,

	ACT_WALK_HURT,			// limp  (loop)
	ACT_RUN_HURT,			// limp  (loop)
	ACT_SPECIAL_ATTACK1,	// very monster specific special attacks.
	ACT_SPECIAL_ATTACK2,
	ACT_COMBAT_IDLE,		// FIXME: unused?  agitated idle.
	ACT_WALK_SCARED,
	ACT_RUN_SCARED,
	ACT_VICTORY_DANCE,		// killed a player, do a victory dance.
	ACT_DIE_HEADSHOT,		// die, hit in head. 
	ACT_DIE_CHESTSHOT,		// die, hit in chest
	ACT_DIE_GUTSHOT,		// die, hit in gut
	ACT_DIE_BACKSHOT,		// die, hit in back
	ACT_FLINCH_HEAD,
	ACT_FLINCH_CHEST,
	ACT_FLINCH_STOMACH,
	ACT_FLINCH_LEFTARM,
	ACT_FLINCH_RIGHTARM,
	ACT_FLINCH_LEFTLEG,
	ACT_FLINCH_RIGHTLEG,
	ACT_FLINCH_PHYSICS,

	ACT_IDLE_ON_FIRE,		// ON FIRE animations
	ACT_WALK_ON_FIRE,
	ACT_RUN_ON_FIRE,

	ACT_RAPPEL_LOOP,		// Rappel down a rope!

	ACT_180_LEFT,			// 180 degree left turn
	ACT_180_RIGHT,

	ACT_90_LEFT,			// 90 degree turns
	ACT_90_RIGHT,

	ACT_STEP_LEFT,			// Single steps
	ACT_STEP_RIGHT,
	ACT_STEP_BACK,
	ACT_STEP_FORE,

	ACT_GESTURE_RANGE_ATTACK1,
	ACT_GESTURE_RANGE_ATTACK2,
	ACT_GESTURE_MELEE_ATTACK1,
	ACT_GESTURE_MELEE_ATTACK2,
	ACT_GESTURE_RANGE_ATTACK1_LOW,	// FIXME: not used yet, crouched versions of the range attack
	ACT_GESTURE_RANGE_ATTACK2_LOW,	// FIXME: not used yet, crouched versions of the range attack

	ACT_MELEE_ATTACK_SWING_GESTURE,

	ACT_GESTURE_SMALL_FLINCH,
	ACT_GESTURE_BIG_FLINCH,
	ACT_GESTURE_FLINCH_BLAST,			// Startled by an explosion
	ACT_GESTURE_FLINCH_BLAST_SHOTGUN,
	ACT_GESTURE_FLINCH_BLAST_DAMAGED,	// Damaged by an explosion
	ACT_GESTURE_FLINCH_BLAST_DAMAGED_SHOTGUN,
	ACT_GESTURE_FLINCH_HEAD,
	ACT_GESTURE_FLINCH_CHEST,
	ACT_GESTURE_FLINCH_STOMACH,
	ACT_GESTURE_FLINCH_LEFTARM,
	ACT_GESTURE_FLINCH_RIGHTARM,
	ACT_GESTURE_FLINCH_LEFTLEG,
	ACT_GESTURE_FLINCH_RIGHTLEG,

	ACT_GESTURE_TURN_LEFT,
	ACT_GESTURE_TURN_RIGHT,
	ACT_GESTURE_TURN_LEFT45,
	ACT_GESTURE_TURN_RIGHT45,
	ACT_GESTURE_TURN_LEFT90,
	ACT_GESTURE_TURN_RIGHT90,
	ACT_GESTURE_TURN_LEFT45_FLAT,
	ACT_GESTURE_TURN_RIGHT45_FLAT,
	ACT_GESTURE_TURN_LEFT90_FLAT,
	ACT_GESTURE_TURN_RIGHT90_FLAT,

	// HALF-LIFE 1 compatability stuff goes here. Temporary!
	ACT_BARNACLE_HIT,		// barnacle tongue hits a monster
	ACT_BARNACLE_PULL,		// barnacle is lifting the monster ( loop )
	ACT_BARNACLE_CHOMP,		// barnacle latches on to the monster
	ACT_BARNACLE_CHEW,		// barnacle is holding the monster in its mouth ( loop )

	// Sometimes, you just want to set an NPC's sequence to a sequence that doesn't actually
	// have an activity. The AI will reset the NPC's sequence to whatever its IDEAL activity
	// is, though. So if you set ideal activity to DO_NOT_DISTURB, the AI will not interfere
	// with the NPC's current sequence. (SJB)
	ACT_DO_NOT_DISTURB,

	// viewmodel (weapon) activities
	// FIXME: move these to the specific viewmodels, no need to make global
	ACT_VM_DRAW,
	ACT_VM_HOLSTER,
	ACT_VM_IDLE,
	ACT_VM_FIDGET,
	ACT_VM_PULLBACK,
	ACT_VM_PULLBACK_HIGH,
	ACT_VM_PULLBACK_LOW,
	ACT_VM_THROW,
	ACT_VM_PULLPIN,
	ACT_VM_PRIMARYATTACK,		// fire
	ACT_VM_SECONDARYATTACK,		// alt. fire
	ACT_VM_RELOAD,
	ACT_VM_DRYFIRE,				// fire with no ammo loaded.
	ACT_VM_HITLEFT,				// bludgeon, swing to left - hit (primary attk)
	ACT_VM_HITLEFT2,			// bludgeon, swing to left - hit (secondary attk)
	ACT_VM_HITRIGHT,			// bludgeon, swing to right - hit (primary attk)
	ACT_VM_HITRIGHT2,			// bludgeon, swing to right - hit (secondary attk)
	ACT_VM_HITCENTER,			// bludgeon, swing center - hit (primary attk)
	ACT_VM_HITCENTER2,			// bludgeon, swing center - hit (secondary attk)
	ACT_VM_MISSLEFT,			// bludgeon, swing to left - miss (primary attk)
	ACT_VM_MISSLEFT2,			// bludgeon, swing to left - miss (secondary attk)
	ACT_VM_MISSRIGHT,			// bludgeon, swing to right - miss (primary attk)
	ACT_VM_MISSRIGHT2,			// bludgeon, swing to right - miss (secondary attk)
	ACT_VM_MISSCENTER,			// bludgeon, swing center - miss (primary attk)
	ACT_VM_MISSCENTER2,			// bludgeon, swing center - miss (secondary attk)
	ACT_VM_HAULBACK,			// bludgeon, haul the weapon back for a hard strike (secondary attk)
	ACT_VM_SWINGHARD,			// bludgeon, release the hard strike (secondary attk)
	ACT_VM_SWINGMISS,
	ACT_VM_SWINGHIT,
	ACT_VM_IDLE_TO_LOWERED,
	ACT_VM_IDLE_LOWERED,
	ACT_VM_LOWERED_TO_IDLE,
	ACT_VM_RECOIL1,
	ACT_VM_RECOIL2,
	ACT_VM_RECOIL3,
	ACT_VM_PICKUP,
	ACT_VM_RELEASE,

	ACT_VM_ATTACH_SILENCER,
	ACT_VM_DETACH_SILENCER,

	//===========================
	// HL2 Specific Activities
	//===========================
		// SLAM	Specialty Activities
		ACT_SLAM_STICKWALL_IDLE,
		ACT_SLAM_STICKWALL_ND_IDLE,
		ACT_SLAM_STICKWALL_ATTACH,
		ACT_SLAM_STICKWALL_ATTACH2,
		ACT_SLAM_STICKWALL_ND_ATTACH,
		ACT_SLAM_STICKWALL_ND_ATTACH2,
		ACT_SLAM_STICKWALL_DETONATE,
		ACT_SLAM_STICKWALL_DETONATOR_HOLSTER,
		ACT_SLAM_STICKWALL_DRAW,
		ACT_SLAM_STICKWALL_ND_DRAW,
		ACT_SLAM_STICKWALL_TO_THROW,
		ACT_SLAM_STICKWALL_TO_THROW_ND,
		ACT_SLAM_STICKWALL_TO_TRIPMINE_ND,
		ACT_SLAM_THROW_IDLE,
		ACT_SLAM_THROW_ND_IDLE,
		ACT_SLAM_THROW_THROW,
		ACT_SLAM_THROW_THROW2,
		ACT_SLAM_THROW_THROW_ND,
		ACT_SLAM_THROW_THROW_ND2,
		ACT_SLAM_THROW_DRAW,
		ACT_SLAM_THROW_ND_DRAW,
		ACT_SLAM_THROW_TO_STICKWALL,
		ACT_SLAM_THROW_TO_STICKWALL_ND,
		ACT_SLAM_THROW_DETONATE,
		ACT_SLAM_THROW_DETONATOR_HOLSTER,
		ACT_SLAM_THROW_TO_TRIPMINE_ND,
		ACT_SLAM_TRIPMINE_IDLE,
		ACT_SLAM_TRIPMINE_DRAW,
		ACT_SLAM_TRIPMINE_ATTACH,
		ACT_SLAM_TRIPMINE_ATTACH2,
		ACT_SLAM_TRIPMINE_TO_STICKWALL_ND,
		ACT_SLAM_TRIPMINE_TO_THROW_ND,
		ACT_SLAM_DETONATOR_IDLE,
		ACT_SLAM_DETONATOR_DRAW,
		ACT_SLAM_DETONATOR_DETONATE,
		ACT_SLAM_DETONATOR_HOLSTER,
		ACT_SLAM_DETONATOR_STICKWALL_DRAW,
		ACT_SLAM_DETONATOR_THROW_DRAW,

		// Shotgun Specialty Activities
		ACT_SHOTGUN_RELOAD_START,
		ACT_SHOTGUN_RELOAD_FINISH,
		ACT_SHOTGUN_PUMP,

		// SMG2 special activities
		ACT_SMG2_IDLE2,
		ACT_SMG2_FIRE2,
		ACT_SMG2_DRAW2,
		ACT_SMG2_RELOAD2,
		ACT_SMG2_DRYFIRE2,
		ACT_SMG2_TOAUTO,
		ACT_SMG2_TOBURST,

		// Physcannon special activities
		ACT_PHYSCANNON_UPGRADE,

		// weapon override activities
		ACT_RANGE_ATTACK_AR1,
		ACT_RANGE_ATTACK_AR2,
		ACT_RANGE_ATTACK_AR2_LOW,
		ACT_RANGE_ATTACK_AR2_GRENADE,
		ACT_RANGE_ATTACK_HMG1,
		ACT_RANGE_ATTACK_ML,
		ACT_RANGE_ATTACK_SMG1,
		ACT_RANGE_ATTACK_SMG1_LOW,
		ACT_RANGE_ATTACK_SMG2,
		ACT_RANGE_ATTACK_SHOTGUN,
		ACT_RANGE_ATTACK_SHOTGUN_LOW,
		ACT_RANGE_ATTACK_PISTOL,
		ACT_RANGE_ATTACK_PISTOL_LOW,
		ACT_RANGE_ATTACK_SLAM,
		ACT_RANGE_ATTACK_TRIPWIRE,
		ACT_RANGE_ATTACK_THROW,
		ACT_RANGE_ATTACK_SNIPER_RIFLE,
		ACT_RANGE_ATTACK_RPG,
		ACT_MELEE_ATTACK_SWING,

		ACT_RANGE_AIM_LOW,
		ACT_RANGE_AIM_SMG1_LOW,
		ACT_RANGE_AIM_PISTOL_LOW,
		ACT_RANGE_AIM_AR2_LOW,

		ACT_COVER_PISTOL_LOW,
		ACT_COVER_SMG1_LOW,

		// weapon override activities
		ACT_GESTURE_RANGE_ATTACK_AR1,
		ACT_GESTURE_RANGE_ATTACK_AR2,
		ACT_GESTURE_RANGE_ATTACK_AR2_GRENADE,
		ACT_GESTURE_RANGE_ATTACK_HMG1,
		ACT_GESTURE_RANGE_ATTACK_ML,
		ACT_GESTURE_RANGE_ATTACK_SMG1,
		ACT_GESTURE_RANGE_ATTACK_SMG1_LOW,
		ACT_GESTURE_RANGE_ATTACK_SMG2,
		ACT_GESTURE_RANGE_ATTACK_SHOTGUN,
		ACT_GESTURE_RANGE_ATTACK_PISTOL,
		ACT_GESTURE_RANGE_ATTACK_PISTOL_LOW,
		ACT_GESTURE_RANGE_ATTACK_SLAM,
		ACT_GESTURE_RANGE_ATTACK_TRIPWIRE,
		ACT_GESTURE_RANGE_ATTACK_THROW,
		ACT_GESTURE_RANGE_ATTACK_SNIPER_RIFLE,
		ACT_GESTURE_MELEE_ATTACK_SWING,

		ACT_IDLE_RIFLE,
		ACT_IDLE_SMG1,
		ACT_IDLE_ANGRY_SMG1,
		ACT_IDLE_PISTOL,
		ACT_IDLE_ANGRY_PISTOL,
		ACT_IDLE_ANGRY_SHOTGUN,
		ACT_IDLE_STEALTH_PISTOL,

		ACT_IDLE_PACKAGE,
		ACT_WALK_PACKAGE,
		ACT_IDLE_SUITCASE,
		ACT_WALK_SUITCASE,

		ACT_IDLE_SMG1_RELAXED,
		ACT_IDLE_SMG1_STIMULATED,
		ACT_WALK_RIFLE_RELAXED,
		ACT_RUN_RIFLE_RELAXED,
		ACT_WALK_RIFLE_STIMULATED,
		ACT_RUN_RIFLE_STIMULATED,

		ACT_IDLE_AIM_RIFLE_STIMULATED,
		ACT_WALK_AIM_RIFLE_STIMULATED,
		ACT_RUN_AIM_RIFLE_STIMULATED,

		ACT_IDLE_SHOTGUN_RELAXED,
		ACT_IDLE_SHOTGUN_STIMULATED,
		ACT_IDLE_SHOTGUN_AGITATED,

		// Policing activities
		ACT_WALK_ANGRY,
		ACT_POLICE_HARASS1,
		ACT_POLICE_HARASS2,

		// Manned guns
		ACT_IDLE_MANNEDGUN,

		// Melee weapon
		ACT_IDLE_MELEE,
		ACT_IDLE_ANGRY_MELEE,

		// RPG activities
		ACT_IDLE_RPG_RELAXED,
		ACT_IDLE_RPG,
		ACT_IDLE_ANGRY_RPG,
		ACT_COVER_LOW_RPG,
		ACT_WALK_RPG,
		ACT_RUN_RPG,
		ACT_WALK_CROUCH_RPG,
		ACT_RUN_CROUCH_RPG,
		ACT_WALK_RPG_RELAXED,
		ACT_RUN_RPG_RELAXED,

		ACT_WALK_RIFLE,
		ACT_WALK_AIM_RIFLE,
		ACT_WALK_CROUCH_RIFLE,
		ACT_WALK_CROUCH_AIM_RIFLE,
		ACT_RUN_RIFLE,
		ACT_RUN_AIM_RIFLE,
		ACT_RUN_CROUCH_RIFLE,
		ACT_RUN_CROUCH_AIM_RIFLE,
		ACT_RUN_STEALTH_PISTOL,

		ACT_WALK_AIM_SHOTGUN,
		ACT_RUN_AIM_SHOTGUN,

		ACT_WALK_PISTOL,
		ACT_RUN_PISTOL,
		ACT_WALK_AIM_PISTOL,
		ACT_RUN_AIM_PISTOL,
		ACT_WALK_STEALTH_PISTOL,
		ACT_WALK_AIM_STEALTH_PISTOL,
		ACT_RUN_AIM_STEALTH_PISTOL,

		// Reloads
		ACT_RELOAD_PISTOL,
		ACT_RELOAD_PISTOL_LOW,
		ACT_RELOAD_SMG1,
		ACT_RELOAD_SMG1_LOW,
		ACT_RELOAD_SHOTGUN,
		ACT_RELOAD_SHOTGUN_LOW,

		ACT_GESTURE_RELOAD,
		ACT_GESTURE_RELOAD_PISTOL,
		ACT_GESTURE_RELOAD_SMG1,
		ACT_GESTURE_RELOAD_SHOTGUN,

		// Busy animations
		ACT_BUSY_LEAN_LEFT,
		ACT_BUSY_LEAN_LEFT_ENTRY,
		ACT_BUSY_LEAN_LEFT_EXIT,
		ACT_BUSY_LEAN_BACK,
		ACT_BUSY_LEAN_BACK_ENTRY,
		ACT_BUSY_LEAN_BACK_EXIT,
		ACT_BUSY_SIT_GROUND,
		ACT_BUSY_SIT_GROUND_ENTRY,
		ACT_BUSY_SIT_GROUND_EXIT,
		ACT_BUSY_SIT_CHAIR,
		ACT_BUSY_SIT_CHAIR_ENTRY,
		ACT_BUSY_SIT_CHAIR_EXIT,
		ACT_BUSY_STAND,
		ACT_BUSY_QUEUE,

		// Dodge animations
		ACT_DUCK_DODGE,

		// For NPCs being lifted/eaten by barnacles:
		// being swallowed by a barnacle
		ACT_DIE_BARNACLE_SWALLOW,
		// being lifted by a barnacle
		ACT_GESTURE_BARNACLE_STRANGLE,

		ACT_PHYSCANNON_DETACH,	// An activity to be played if we're picking this up with the physcannon
		ACT_PHYSCANNON_ANIMATE, // An activity to be played by an object being picked up with the physcannon, but has different behavior to DETACH
		ACT_PHYSCANNON_ANIMATE_PRE,	// An activity to be played by an object being picked up with the physcannon, before playing the ACT_PHYSCANNON_ANIMATE
		ACT_PHYSCANNON_ANIMATE_POST,// An activity to be played by an object being picked up with the physcannon, after playing the ACT_PHYSCANNON_ANIMATE

		ACT_DIE_FRONTSIDE,
		ACT_DIE_RIGHTSIDE,
		ACT_DIE_BACKSIDE,
		ACT_DIE_LEFTSIDE,

		ACT_OPEN_DOOR,

		// Dynamic interactions
		ACT_DI_ALYX_ZOMBIE_MELEE,
		ACT_DI_ALYX_ZOMBIE_TORSO_MELEE,
		ACT_DI_ALYX_HEADCRAB_MELEE,
		ACT_DI_ALYX_ANTLION,

		ACT_DI_ALYX_ZOMBIE_SHOTGUN64,
		ACT_DI_ALYX_ZOMBIE_SHOTGUN26,

		ACT_READINESS_RELAXED_TO_STIMULATED,
		ACT_READINESS_RELAXED_TO_STIMULATED_WALK,
		ACT_READINESS_AGITATED_TO_STIMULATED,
		ACT_READINESS_STIMULATED_TO_RELAXED,

		ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED,
		ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED_WALK,
		ACT_READINESS_PISTOL_AGITATED_TO_STIMULATED,
		ACT_READINESS_PISTOL_STIMULATED_TO_RELAXED,

		ACT_IDLE_CARRY,
		ACT_WALK_CARRY,

		//===========================
		// TF2 Specific Activities
		//===========================
		ACT_STARTDYING,
		ACT_DYINGLOOP,
		ACT_DYINGTODEAD,

		ACT_RIDE_MANNED_GUN,

		// All viewmodels
		ACT_VM_SPRINT_ENTER,
		ACT_VM_SPRINT_IDLE,
		ACT_VM_SPRINT_LEAVE,

		// Looping weapon firing
		ACT_FIRE_START,
		ACT_FIRE_LOOP,
		ACT_FIRE_END,

		ACT_CROUCHING_GRENADEIDLE,
		ACT_CROUCHING_GRENADEREADY,
		ACT_CROUCHING_PRIMARYATTACK,
		ACT_OVERLAY_GRENADEIDLE,
		ACT_OVERLAY_GRENADEREADY,
		ACT_OVERLAY_PRIMARYATTACK,
		ACT_OVERLAY_SHIELD_UP,
		ACT_OVERLAY_SHIELD_DOWN,
		ACT_OVERLAY_SHIELD_UP_IDLE,
		ACT_OVERLAY_SHIELD_ATTACK,
		ACT_OVERLAY_SHIELD_KNOCKBACK,
		ACT_SHIELD_UP,
		ACT_SHIELD_DOWN,
		ACT_SHIELD_UP_IDLE,
		ACT_SHIELD_ATTACK,
		ACT_SHIELD_KNOCKBACK,
		ACT_CROUCHING_SHIELD_UP,
		ACT_CROUCHING_SHIELD_DOWN,
		ACT_CROUCHING_SHIELD_UP_IDLE,
		ACT_CROUCHING_SHIELD_ATTACK,
		ACT_CROUCHING_SHIELD_KNOCKBACK,

		// turning in place
		ACT_TURNRIGHT45,
		ACT_TURNLEFT45,

		ACT_TURN,

		ACT_OBJ_ASSEMBLING,
		ACT_OBJ_DISMANTLING,
		ACT_OBJ_STARTUP,
		ACT_OBJ_RUNNING,
		ACT_OBJ_IDLE,
		ACT_OBJ_PLACING,
		ACT_OBJ_DETERIORATING,
		ACT_OBJ_UPGRADING,

		// Deploy
		ACT_DEPLOY,
		ACT_DEPLOY_IDLE,
		ACT_UNDEPLOY,

		//===========================
		// HL1 Specific Activities
		//===========================
			// Grenades
			ACT_GRENADE_ROLL,
			ACT_GRENADE_TOSS,

			// Hand grenade
			ACT_HANDGRENADE_THROW1,
			ACT_HANDGRENADE_THROW2,
			ACT_HANDGRENADE_THROW3,

			// Shotgun
			ACT_SHOTGUN_IDLE_DEEP,
			ACT_SHOTGUN_IDLE4,

			// Glock
			ACT_GLOCK_SHOOTEMPTY,
			ACT_GLOCK_SHOOT_RELOAD,

			// RPG
			ACT_RPG_DRAW_UNLOADED,
			ACT_RPG_HOLSTER_UNLOADED,
			ACT_RPG_IDLE_UNLOADED,
			ACT_RPG_FIDGET_UNLOADED,

			// Crossbow
			ACT_CROSSBOW_DRAW_UNLOADED,
			ACT_CROSSBOW_IDLE_UNLOADED,
			ACT_CROSSBOW_FIDGET_UNLOADED,

			// Gauss
			ACT_GAUSS_SPINUP,
			ACT_GAUSS_SPINCYCLE,

			// Tripmine
			ACT_TRIPMINE_GROUND,
			ACT_TRIPMINE_WORLD,

			//===========================
			// CSPort Specific Activities
			//===========================

			ACT_VM_PRIMARYATTACK_SILENCED,		// fire
			ACT_VM_RELOAD_SILENCED,
			ACT_VM_DRYFIRE_SILENCED,				// fire with no ammo loaded.
			ACT_VM_IDLE_SILENCED,
			ACT_VM_DRAW_SILENCED,
			ACT_VM_IDLE_EMPTY_LEFT,
			ACT_VM_DRYFIRE_LEFT,

			ACT_PLAYER_IDLE_FIRE,
			ACT_PLAYER_CROUCH_FIRE,
			ACT_PLAYER_CROUCH_WALK_FIRE,
			ACT_PLAYER_WALK_FIRE,
			ACT_PLAYER_RUN_FIRE,

			ACT_IDLETORUN,
			ACT_RUNTOIDLE,


			//===========================
			// DoD Specific Activities
			//===========================
			ACT_SPRINT,

			ACT_GET_DOWN_STAND,
			ACT_GET_UP_STAND,
			ACT_GET_DOWN_CROUCH,
			ACT_GET_UP_CROUCH,
			ACT_PRONE_FORWARD,
			ACT_PRONE_IDLE,

			ACT_DEEPIDLE1,
			ACT_DEEPIDLE2,
			ACT_DEEPIDLE3,
			ACT_DEEPIDLE4,

			ACT_VM_RELOAD_DEPLOYED,
			ACT_VM_RELOAD_IDLE,

			ACT_VM_DRAW_DEPLOYED,

			//Weapon is empty activities
			ACT_VM_DRAW_EMPTY,
			ACT_VM_PRIMARYATTACK_EMPTY,
			ACT_VM_RELOAD_EMPTY,
			ACT_VM_IDLE_EMPTY,
			ACT_VM_IDLE_DEPLOYED_EMPTY,

			ACT_VM_IDLE_8,
			ACT_VM_IDLE_7,
			ACT_VM_IDLE_6,
			ACT_VM_IDLE_5,
			ACT_VM_IDLE_4,
			ACT_VM_IDLE_3,
			ACT_VM_IDLE_2,
			ACT_VM_IDLE_1,

			ACT_VM_IDLE_DEPLOYED,
			ACT_VM_IDLE_DEPLOYED_8,
			ACT_VM_IDLE_DEPLOYED_7,
			ACT_VM_IDLE_DEPLOYED_6,
			ACT_VM_IDLE_DEPLOYED_5,
			ACT_VM_IDLE_DEPLOYED_4,
			ACT_VM_IDLE_DEPLOYED_3,
			ACT_VM_IDLE_DEPLOYED_2,
			ACT_VM_IDLE_DEPLOYED_1,

			// Animation from prone idle to standing/crouch idle. Number designates bullets left
			ACT_VM_UNDEPLOY,
			ACT_VM_UNDEPLOY_8,
			ACT_VM_UNDEPLOY_7,
			ACT_VM_UNDEPLOY_6,
			ACT_VM_UNDEPLOY_5,
			ACT_VM_UNDEPLOY_4,
			ACT_VM_UNDEPLOY_3,
			ACT_VM_UNDEPLOY_2,
			ACT_VM_UNDEPLOY_1,
			ACT_VM_UNDEPLOY_EMPTY,

			// Animation from standing/crouch idle to prone idle. Number designates bullets left
			ACT_VM_DEPLOY,
			ACT_VM_DEPLOY_8,
			ACT_VM_DEPLOY_7,
			ACT_VM_DEPLOY_6,
			ACT_VM_DEPLOY_5,
			ACT_VM_DEPLOY_4,
			ACT_VM_DEPLOY_3,
			ACT_VM_DEPLOY_2,
			ACT_VM_DEPLOY_1,
			ACT_VM_DEPLOY_EMPTY,

			// Shooting animations for standing/crouch position.  Number designates bullets left at START of animation
			ACT_VM_PRIMARYATTACK_8,
			ACT_VM_PRIMARYATTACK_7,
			ACT_VM_PRIMARYATTACK_6,
			ACT_VM_PRIMARYATTACK_5,
			ACT_VM_PRIMARYATTACK_4,
			ACT_VM_PRIMARYATTACK_3,
			ACT_VM_PRIMARYATTACK_2,
			ACT_VM_PRIMARYATTACK_1,

			// Shooting animations for prone position. Number designates bullets left at START of animation
			ACT_VM_PRIMARYATTACK_DEPLOYED,
			ACT_VM_PRIMARYATTACK_DEPLOYED_8,
			ACT_VM_PRIMARYATTACK_DEPLOYED_7,
			ACT_VM_PRIMARYATTACK_DEPLOYED_6,
			ACT_VM_PRIMARYATTACK_DEPLOYED_5,
			ACT_VM_PRIMARYATTACK_DEPLOYED_4,
			ACT_VM_PRIMARYATTACK_DEPLOYED_3,
			ACT_VM_PRIMARYATTACK_DEPLOYED_2,
			ACT_VM_PRIMARYATTACK_DEPLOYED_1,
			ACT_VM_PRIMARYATTACK_DEPLOYED_EMPTY,

			// Player anim ACTs
			ACT_DOD_DEPLOYED,
			ACT_DOD_PRONE_DEPLOYED,
			ACT_DOD_IDLE_ZOOMED,
			ACT_DOD_WALK_ZOOMED,
			ACT_DOD_CROUCH_ZOOMED,
			ACT_DOD_CROUCHWALK_ZOOMED,
			ACT_DOD_PRONE_ZOOMED,
			ACT_DOD_PRONE_FORWARD_ZOOMED,
			ACT_DOD_PRIMARYATTACK_DEPLOYED,
			ACT_DOD_PRIMARYATTACK_PRONE_DEPLOYED,
			ACT_DOD_RELOAD_DEPLOYED,
			ACT_DOD_RELOAD_PRONE_DEPLOYED,
			ACT_DOD_PRIMARYATTACK_PRONE,
			ACT_DOD_SECONDARYATTACK_PRONE,
			ACT_DOD_RELOAD_CROUCH,
			ACT_DOD_RELOAD_PRONE,
			ACT_DOD_STAND_IDLE,
			ACT_DOD_STAND_AIM,
			ACT_DOD_CROUCH_IDLE,
			ACT_DOD_CROUCH_AIM,
			ACT_DOD_CROUCHWALK_IDLE,
			ACT_DOD_CROUCHWALK_AIM,
			ACT_DOD_WALK_IDLE,
			ACT_DOD_WALK_AIM,
			ACT_DOD_RUN_IDLE,
			ACT_DOD_RUN_AIM,

			// Positions
			ACT_DOD_STAND_AIM_PISTOL,
			ACT_DOD_CROUCH_AIM_PISTOL,
			ACT_DOD_CROUCHWALK_AIM_PISTOL,
			ACT_DOD_WALK_AIM_PISTOL,
			ACT_DOD_RUN_AIM_PISTOL,
			ACT_DOD_PRONE_AIM_PISTOL,
			ACT_DOD_STAND_IDLE_PISTOL,
			ACT_DOD_CROUCH_IDLE_PISTOL,
			ACT_DOD_CROUCHWALK_IDLE_PISTOL,
			ACT_DOD_WALK_IDLE_PISTOL,
			ACT_DOD_RUN_IDLE_PISTOL,
			ACT_DOD_SPRINT_IDLE_PISTOL,
			ACT_DOD_PRONEWALK_IDLE_PISTOL,

			ACT_DOD_STAND_AIM_C96,
			ACT_DOD_CROUCH_AIM_C96,
			ACT_DOD_CROUCHWALK_AIM_C96,
			ACT_DOD_WALK_AIM_C96,
			ACT_DOD_RUN_AIM_C96,
			ACT_DOD_PRONE_AIM_C96,
			ACT_DOD_STAND_IDLE_C96,
			ACT_DOD_CROUCH_IDLE_C96,
			ACT_DOD_CROUCHWALK_IDLE_C96,
			ACT_DOD_WALK_IDLE_C96,
			ACT_DOD_RUN_IDLE_C96,
			ACT_DOD_SPRINT_IDLE_C96,
			ACT_DOD_PRONEWALK_IDLE_C96,

			ACT_DOD_STAND_AIM_RIFLE,
			ACT_DOD_CROUCH_AIM_RIFLE,
			ACT_DOD_CROUCHWALK_AIM_RIFLE,
			ACT_DOD_WALK_AIM_RIFLE,
			ACT_DOD_RUN_AIM_RIFLE,
			ACT_DOD_PRONE_AIM_RIFLE,
			ACT_DOD_STAND_IDLE_RIFLE,
			ACT_DOD_CROUCH_IDLE_RIFLE,
			ACT_DOD_CROUCHWALK_IDLE_RIFLE,
			ACT_DOD_WALK_IDLE_RIFLE,
			ACT_DOD_RUN_IDLE_RIFLE,
			ACT_DOD_SPRINT_IDLE_RIFLE,
			ACT_DOD_PRONEWALK_IDLE_RIFLE,

			ACT_DOD_STAND_AIM_BOLT,
			ACT_DOD_CROUCH_AIM_BOLT,
			ACT_DOD_CROUCHWALK_AIM_BOLT,
			ACT_DOD_WALK_AIM_BOLT,
			ACT_DOD_RUN_AIM_BOLT,
			ACT_DOD_PRONE_AIM_BOLT,
			ACT_DOD_STAND_IDLE_BOLT,
			ACT_DOD_CROUCH_IDLE_BOLT,
			ACT_DOD_CROUCHWALK_IDLE_BOLT,
			ACT_DOD_WALK_IDLE_BOLT,
			ACT_DOD_RUN_IDLE_BOLT,
			ACT_DOD_SPRINT_IDLE_BOLT,
			ACT_DOD_PRONEWALK_IDLE_BOLT,

			ACT_DOD_STAND_AIM_TOMMY,
			ACT_DOD_CROUCH_AIM_TOMMY,
			ACT_DOD_CROUCHWALK_AIM_TOMMY,
			ACT_DOD_WALK_AIM_TOMMY,
			ACT_DOD_RUN_AIM_TOMMY,
			ACT_DOD_PRONE_AIM_TOMMY,
			ACT_DOD_STAND_IDLE_TOMMY,
			ACT_DOD_CROUCH_IDLE_TOMMY,
			ACT_DOD_CROUCHWALK_IDLE_TOMMY,
			ACT_DOD_WALK_IDLE_TOMMY,
			ACT_DOD_RUN_IDLE_TOMMY,
			ACT_DOD_SPRINT_IDLE_TOMMY,
			ACT_DOD_PRONEWALK_IDLE_TOMMY,

			ACT_DOD_STAND_AIM_MP40,
			ACT_DOD_CROUCH_AIM_MP40,
			ACT_DOD_CROUCHWALK_AIM_MP40,
			ACT_DOD_WALK_AIM_MP40,
			ACT_DOD_RUN_AIM_MP40,
			ACT_DOD_PRONE_AIM_MP40,
			ACT_DOD_STAND_IDLE_MP40,
			ACT_DOD_CROUCH_IDLE_MP40,
			ACT_DOD_CROUCHWALK_IDLE_MP40,
			ACT_DOD_WALK_IDLE_MP40,
			ACT_DOD_RUN_IDLE_MP40,
			ACT_DOD_SPRINT_IDLE_MP40,
			ACT_DOD_PRONEWALK_IDLE_MP40,

			ACT_DOD_STAND_AIM_MP44,
			ACT_DOD_CROUCH_AIM_MP44,
			ACT_DOD_CROUCHWALK_AIM_MP44,
			ACT_DOD_WALK_AIM_MP44,
			ACT_DOD_RUN_AIM_MP44,
			ACT_DOD_PRONE_AIM_MP44,
			ACT_DOD_STAND_IDLE_MP44,
			ACT_DOD_CROUCH_IDLE_MP44,
			ACT_DOD_CROUCHWALK_IDLE_MP44,
			ACT_DOD_WALK_IDLE_MP44,
			ACT_DOD_RUN_IDLE_MP44,
			ACT_DOD_SPRINT_IDLE_MP44,
			ACT_DOD_PRONEWALK_IDLE_MP44,

			ACT_DOD_STAND_AIM_GREASE,
			ACT_DOD_CROUCH_AIM_GREASE,
			ACT_DOD_CROUCHWALK_AIM_GREASE,
			ACT_DOD_WALK_AIM_GREASE,
			ACT_DOD_RUN_AIM_GREASE,
			ACT_DOD_PRONE_AIM_GREASE,
			ACT_DOD_STAND_IDLE_GREASE,
			ACT_DOD_CROUCH_IDLE_GREASE,
			ACT_DOD_CROUCHWALK_IDLE_GREASE,
			ACT_DOD_WALK_IDLE_GREASE,
			ACT_DOD_RUN_IDLE_GREASE,
			ACT_DOD_SPRINT_IDLE_GREASE,
			ACT_DOD_PRONEWALK_IDLE_GREASE,

			ACT_DOD_STAND_AIM_MG,
			ACT_DOD_CROUCH_AIM_MG,
			ACT_DOD_CROUCHWALK_AIM_MG,
			ACT_DOD_WALK_AIM_MG,
			ACT_DOD_RUN_AIM_MG,
			ACT_DOD_PRONE_AIM_MG,
			ACT_DOD_STAND_IDLE_MG,
			ACT_DOD_CROUCH_IDLE_MG,
			ACT_DOD_CROUCHWALK_IDLE_MG,
			ACT_DOD_WALK_IDLE_MG,
			ACT_DOD_RUN_IDLE_MG,
			ACT_DOD_SPRINT_IDLE_MG,
			ACT_DOD_PRONEWALK_IDLE_MG,

			ACT_DOD_STAND_AIM_30CAL,
			ACT_DOD_CROUCH_AIM_30CAL,
			ACT_DOD_CROUCHWALK_AIM_30CAL,
			ACT_DOD_WALK_AIM_30CAL,
			ACT_DOD_RUN_AIM_30CAL,
			ACT_DOD_PRONE_AIM_30CAL,
			ACT_DOD_STAND_IDLE_30CAL,
			ACT_DOD_CROUCH_IDLE_30CAL,
			ACT_DOD_CROUCHWALK_IDLE_30CAL,
			ACT_DOD_WALK_IDLE_30CAL,
			ACT_DOD_RUN_IDLE_30CAL,
			ACT_DOD_SPRINT_IDLE_30CAL,
			ACT_DOD_PRONEWALK_IDLE_30CAL,

			ACT_DOD_STAND_AIM_GREN_FRAG,
			ACT_DOD_CROUCH_AIM_GREN_FRAG,
			ACT_DOD_CROUCHWALK_AIM_GREN_FRAG,
			ACT_DOD_WALK_AIM_GREN_FRAG,
			ACT_DOD_RUN_AIM_GREN_FRAG,
			ACT_DOD_PRONE_AIM_GREN_FRAG,
			ACT_DOD_SPRINT_AIM_GREN_FRAG,
			ACT_DOD_PRONEWALK_AIM_GREN_FRAG,
			ACT_DOD_STAND_AIM_GREN_STICK,
			ACT_DOD_CROUCH_AIM_GREN_STICK,
			ACT_DOD_CROUCHWALK_AIM_GREN_STICK,
			ACT_DOD_WALK_AIM_GREN_STICK,
			ACT_DOD_RUN_AIM_GREN_STICK,
			ACT_DOD_PRONE_AIM_GREN_STICK,
			ACT_DOD_SPRINT_AIM_GREN_STICK,
			ACT_DOD_PRONEWALK_AIM_GREN_STICK,

			ACT_DOD_STAND_AIM_KNIFE,
			ACT_DOD_CROUCH_AIM_KNIFE,
			ACT_DOD_CROUCHWALK_AIM_KNIFE,
			ACT_DOD_WALK_AIM_KNIFE,
			ACT_DOD_RUN_AIM_KNIFE,
			ACT_DOD_PRONE_AIM_KNIFE,
			ACT_DOD_SPRINT_AIM_KNIFE,
			ACT_DOD_PRONEWALK_AIM_KNIFE,

			ACT_DOD_STAND_AIM_SPADE,
			ACT_DOD_CROUCH_AIM_SPADE,
			ACT_DOD_CROUCHWALK_AIM_SPADE,
			ACT_DOD_WALK_AIM_SPADE,
			ACT_DOD_RUN_AIM_SPADE,
			ACT_DOD_PRONE_AIM_SPADE,
			ACT_DOD_SPRINT_AIM_SPADE,
			ACT_DOD_PRONEWALK_AIM_SPADE,

			ACT_DOD_STAND_AIM_BAZOOKA,
			ACT_DOD_CROUCH_AIM_BAZOOKA,
			ACT_DOD_CROUCHWALK_AIM_BAZOOKA,
			ACT_DOD_WALK_AIM_BAZOOKA,
			ACT_DOD_RUN_AIM_BAZOOKA,
			ACT_DOD_PRONE_AIM_BAZOOKA,
			ACT_DOD_STAND_IDLE_BAZOOKA,
			ACT_DOD_CROUCH_IDLE_BAZOOKA,
			ACT_DOD_CROUCHWALK_IDLE_BAZOOKA,
			ACT_DOD_WALK_IDLE_BAZOOKA,
			ACT_DOD_RUN_IDLE_BAZOOKA,
			ACT_DOD_SPRINT_IDLE_BAZOOKA,
			ACT_DOD_PRONEWALK_IDLE_BAZOOKA,

			ACT_DOD_STAND_AIM_PSCHRECK,
			ACT_DOD_CROUCH_AIM_PSCHRECK,
			ACT_DOD_CROUCHWALK_AIM_PSCHRECK,
			ACT_DOD_WALK_AIM_PSCHRECK,
			ACT_DOD_RUN_AIM_PSCHRECK,
			ACT_DOD_PRONE_AIM_PSCHRECK,
			ACT_DOD_STAND_IDLE_PSCHRECK,
			ACT_DOD_CROUCH_IDLE_PSCHRECK,
			ACT_DOD_CROUCHWALK_IDLE_PSCHRECK,
			ACT_DOD_WALK_IDLE_PSCHRECK,
			ACT_DOD_RUN_IDLE_PSCHRECK,
			ACT_DOD_SPRINT_IDLE_PSCHRECK,
			ACT_DOD_PRONEWALK_IDLE_PSCHRECK,

			ACT_DOD_STAND_AIM_BAR,
			ACT_DOD_CROUCH_AIM_BAR,
			ACT_DOD_CROUCHWALK_AIM_BAR,
			ACT_DOD_WALK_AIM_BAR,
			ACT_DOD_RUN_AIM_BAR,
			ACT_DOD_PRONE_AIM_BAR,
			ACT_DOD_STAND_IDLE_BAR,
			ACT_DOD_CROUCH_IDLE_BAR,
			ACT_DOD_CROUCHWALK_IDLE_BAR,
			ACT_DOD_WALK_IDLE_BAR,
			ACT_DOD_RUN_IDLE_BAR,
			ACT_DOD_SPRINT_IDLE_BAR,
			ACT_DOD_PRONEWALK_IDLE_BAR,

			// Zoomed aims
			ACT_DOD_STAND_ZOOM_RIFLE,
			ACT_DOD_CROUCH_ZOOM_RIFLE,
			ACT_DOD_CROUCHWALK_ZOOM_RIFLE,
			ACT_DOD_WALK_ZOOM_RIFLE,
			ACT_DOD_RUN_ZOOM_RIFLE,
			ACT_DOD_PRONE_ZOOM_RIFLE,

			ACT_DOD_STAND_ZOOM_BOLT,
			ACT_DOD_CROUCH_ZOOM_BOLT,
			ACT_DOD_CROUCHWALK_ZOOM_BOLT,
			ACT_DOD_WALK_ZOOM_BOLT,
			ACT_DOD_RUN_ZOOM_BOLT,
			ACT_DOD_PRONE_ZOOM_BOLT,

			ACT_DOD_STAND_ZOOM_BAZOOKA,
			ACT_DOD_CROUCH_ZOOM_BAZOOKA,
			ACT_DOD_CROUCHWALK_ZOOM_BAZOOKA,
			ACT_DOD_WALK_ZOOM_BAZOOKA,
			ACT_DOD_RUN_ZOOM_BAZOOKA,
			ACT_DOD_PRONE_ZOOM_BAZOOKA,

			ACT_DOD_STAND_ZOOM_PSCHRECK,
			ACT_DOD_CROUCH_ZOOM_PSCHRECK,
			ACT_DOD_CROUCHWALK_ZOOM_PSCHRECK,
			ACT_DOD_WALK_ZOOM_PSCHRECK,
			ACT_DOD_RUN_ZOOM_PSCHRECK,
			ACT_DOD_PRONE_ZOOM_PSCHRECK,

			// Deployed Aim
			ACT_DOD_DEPLOY_RIFLE,
			ACT_DOD_DEPLOY_TOMMY,
			ACT_DOD_DEPLOY_MG,
			ACT_DOD_DEPLOY_30CAL,

			// Prone Deployed Aim
			ACT_DOD_PRONE_DEPLOY_RIFLE,
			ACT_DOD_PRONE_DEPLOY_TOMMY,
			ACT_DOD_PRONE_DEPLOY_MG,
			ACT_DOD_PRONE_DEPLOY_30CAL,

			// Attacks

			// Rifle
			ACT_DOD_PRIMARYATTACK_RIFLE,
			ACT_DOD_SECONDARYATTACK_RIFLE,
			ACT_DOD_PRIMARYATTACK_PRONE_RIFLE,
			ACT_DOD_SECONDARYATTACK_PRONE_RIFLE,
			ACT_DOD_PRIMARYATTACK_PRONE_DEPLOYED_RIFLE,
			ACT_DOD_PRIMARYATTACK_DEPLOYED_RIFLE,

			// Bolt
			ACT_DOD_PRIMARYATTACK_BOLT,
			ACT_DOD_SECONDARYATTACK_BOLT,
			ACT_DOD_PRIMARYATTACK_PRONE_BOLT,
			ACT_DOD_SECONDARYATTACK_PRONE_BOLT,

			// Tommy
			ACT_DOD_PRIMARYATTACK_TOMMY,
			ACT_DOD_PRIMARYATTACK_PRONE_TOMMY,
			ACT_DOD_SECONDARYATTACK_TOMMY,
			ACT_DOD_SECONDARYATTACK_PRONE_TOMMY,

			// MP40
			ACT_DOD_PRIMARYATTACK_MP40,
			ACT_DOD_PRIMARYATTACK_PRONE_MP40,
			ACT_DOD_SECONDARYATTACK_MP40,
			ACT_DOD_SECONDARYATTACK_PRONE_MP40,

			// MP44
			ACT_DOD_PRIMARYATTACK_MP44,
			ACT_DOD_PRIMARYATTACK_PRONE_MP44,

			// Greasegun
			ACT_DOD_PRIMARYATTACK_GREASE,
			ACT_DOD_PRIMARYATTACK_PRONE_GREASE,

			// Pistols (Colt, Luger)
			ACT_DOD_PRIMARYATTACK_PISTOL,
			ACT_DOD_PRIMARYATTACK_PRONE_PISTOL,
			ACT_DOD_PRIMARYATTACK_C96,
			ACT_DOD_PRIMARYATTACK_PRONE_C96,

			// Mgs (mg42, mg34)
			ACT_DOD_PRIMARYATTACK_MG,
			ACT_DOD_PRIMARYATTACK_PRONE_MG,
			ACT_DOD_PRIMARYATTACK_PRONE_DEPLOYED_MG,
			ACT_DOD_PRIMARYATTACK_DEPLOYED_MG,

			// 30cal
			ACT_DOD_PRIMARYATTACK_30CAL,
			ACT_DOD_PRIMARYATTACK_PRONE_30CAL,
			ACT_DOD_PRIMARYATTACK_DEPLOYED_30CAL,
			ACT_DOD_PRIMARYATTACK_PRONE_DEPLOYED_30CAL,

			// Grenades
			ACT_DOD_PRIMARYATTACK_GREN_FRAG,
			ACT_DOD_PRIMARYATTACK_PRONE_GREN_FRAG,
			ACT_DOD_PRIMARYATTACK_GREN_STICK,
			ACT_DOD_PRIMARYATTACK_PRONE_GREN_STICK,

			// Knife
			ACT_DOD_PRIMARYATTACK_KNIFE,
			ACT_DOD_PRIMARYATTACK_PRONE_KNIFE,

			// Spade
			ACT_DOD_PRIMARYATTACK_SPADE,
			ACT_DOD_PRIMARYATTACK_PRONE_SPADE,

			// Bazooka
			ACT_DOD_PRIMARYATTACK_BAZOOKA,
			ACT_DOD_PRIMARYATTACK_PRONE_BAZOOKA,

			// Pschreck
			ACT_DOD_PRIMARYATTACK_PSCHRECK,
			ACT_DOD_PRIMARYATTACK_PRONE_PSCHRECK,

			// Bar
			ACT_DOD_PRIMARYATTACK_BAR,
			ACT_DOD_PRIMARYATTACK_PRONE_BAR,

			// Reloads
			ACT_DOD_RELOAD_GARAND,
			ACT_DOD_RELOAD_K43,
			ACT_DOD_RELOAD_BAR,
			ACT_DOD_RELOAD_MP40,
			ACT_DOD_RELOAD_MP44,
			ACT_DOD_RELOAD_BOLT,
			ACT_DOD_RELOAD_M1CARBINE,
			ACT_DOD_RELOAD_TOMMY,
			ACT_DOD_RELOAD_GREASEGUN,
			ACT_DOD_RELOAD_PISTOL,
			ACT_DOD_RELOAD_FG42,
			ACT_DOD_RELOAD_RIFLE,
			ACT_DOD_RELOAD_RIFLEGRENADE,
			ACT_DOD_RELOAD_C96,

			// Crouch
			ACT_DOD_RELOAD_CROUCH_BAR,
			ACT_DOD_RELOAD_CROUCH_RIFLE,
			ACT_DOD_RELOAD_CROUCH_RIFLEGRENADE,
			ACT_DOD_RELOAD_CROUCH_BOLT,
			ACT_DOD_RELOAD_CROUCH_MP44,
			ACT_DOD_RELOAD_CROUCH_MP40,
			ACT_DOD_RELOAD_CROUCH_TOMMY,
			ACT_DOD_RELOAD_CROUCH_BAZOOKA,
			ACT_DOD_RELOAD_CROUCH_PSCHRECK,
			ACT_DOD_RELOAD_CROUCH_PISTOL,
			ACT_DOD_RELOAD_CROUCH_M1CARBINE,
			ACT_DOD_RELOAD_CROUCH_C96,

			// Bazookas
			ACT_DOD_RELOAD_BAZOOKA,
			ACT_DOD_ZOOMLOAD_BAZOOKA,
			ACT_DOD_RELOAD_PSCHRECK,
			ACT_DOD_ZOOMLOAD_PSCHRECK,

			// Deployed
			ACT_DOD_RELOAD_DEPLOYED_FG42,
			ACT_DOD_RELOAD_DEPLOYED_30CAL,
			ACT_DOD_RELOAD_DEPLOYED_MG,
			ACT_DOD_RELOAD_DEPLOYED_MG34,
			ACT_DOD_RELOAD_DEPLOYED_BAR,

			// Prone
			ACT_DOD_RELOAD_PRONE_PISTOL,
			ACT_DOD_RELOAD_PRONE_GARAND,
			ACT_DOD_RELOAD_PRONE_M1CARBINE,
			ACT_DOD_RELOAD_PRONE_BOLT,
			ACT_DOD_RELOAD_PRONE_K43,
			ACT_DOD_RELOAD_PRONE_MP40,
			ACT_DOD_RELOAD_PRONE_MP44,
			ACT_DOD_RELOAD_PRONE_BAR,
			ACT_DOD_RELOAD_PRONE_GREASEGUN,
			ACT_DOD_RELOAD_PRONE_TOMMY,
			ACT_DOD_RELOAD_PRONE_FG42,
			ACT_DOD_RELOAD_PRONE_RIFLE,
			ACT_DOD_RELOAD_PRONE_RIFLEGRENADE,
			ACT_DOD_RELOAD_PRONE_C96,

			// Prone bazooka
			ACT_DOD_RELOAD_PRONE_BAZOOKA,
			ACT_DOD_ZOOMLOAD_PRONE_BAZOOKA,
			ACT_DOD_RELOAD_PRONE_PSCHRECK,
			ACT_DOD_ZOOMLOAD_PRONE_PSCHRECK,

			// Prone deployed
			ACT_DOD_RELOAD_PRONE_DEPLOYED_BAR,
			ACT_DOD_RELOAD_PRONE_DEPLOYED_FG42,
			ACT_DOD_RELOAD_PRONE_DEPLOYED_30CAL,
			ACT_DOD_RELOAD_PRONE_DEPLOYED_MG,
			ACT_DOD_RELOAD_PRONE_DEPLOYED_MG34,

			// Prone zoomed aim
			ACT_DOD_PRONE_ZOOM_FORWARD_RIFLE,
			ACT_DOD_PRONE_ZOOM_FORWARD_BOLT,
			ACT_DOD_PRONE_ZOOM_FORWARD_BAZOOKA,
			ACT_DOD_PRONE_ZOOM_FORWARD_PSCHRECK,

			// Crouch attack
			ACT_DOD_PRIMARYATTACK_CROUCH,
			ACT_DOD_PRIMARYATTACK_CROUCH_SPADE,
			ACT_DOD_PRIMARYATTACK_CROUCH_KNIFE,
			ACT_DOD_PRIMARYATTACK_CROUCH_GREN_FRAG,
			ACT_DOD_PRIMARYATTACK_CROUCH_GREN_STICK,
			ACT_DOD_SECONDARYATTACK_CROUCH,
			ACT_DOD_SECONDARYATTACK_CROUCH_TOMMY,
			ACT_DOD_SECONDARYATTACK_CROUCH_MP40,

			// Hand Signals
			ACT_DOD_HS_IDLE,
			ACT_DOD_HS_CROUCH,
			ACT_DOD_HS_IDLE_30CAL,
			ACT_DOD_HS_IDLE_BAZOOKA,
			ACT_DOD_HS_IDLE_PSCHRECK,
			ACT_DOD_HS_IDLE_KNIFE,
			ACT_DOD_HS_IDLE_MG42,
			ACT_DOD_HS_IDLE_PISTOL,
			ACT_DOD_HS_IDLE_STICKGRENADE,
			ACT_DOD_HS_IDLE_TOMMY,
			ACT_DOD_HS_IDLE_MP44,
			ACT_DOD_HS_IDLE_K98,
			ACT_DOD_HS_CROUCH_30CAL,
			ACT_DOD_HS_CROUCH_BAZOOKA,
			ACT_DOD_HS_CROUCH_PSCHRECK,
			ACT_DOD_HS_CROUCH_KNIFE,
			ACT_DOD_HS_CROUCH_MG42,
			ACT_DOD_HS_CROUCH_PISTOL,
			ACT_DOD_HS_CROUCH_STICKGRENADE,
			ACT_DOD_HS_CROUCH_TOMMY,
			ACT_DOD_HS_CROUCH_MP44,
			ACT_DOD_HS_CROUCH_K98,

			ACT_DOD_STAND_IDLE_TNT,
			ACT_DOD_CROUCH_IDLE_TNT,
			ACT_DOD_CROUCHWALK_IDLE_TNT,
			ACT_DOD_WALK_IDLE_TNT,
			ACT_DOD_RUN_IDLE_TNT,
			ACT_DOD_SPRINT_IDLE_TNT,
			ACT_DOD_PRONEWALK_IDLE_TNT,

			ACT_DOD_PLANT_TNT,
			ACT_DOD_DEFUSE_TNT,

			// HL2MP
			ACT_HL2MP_IDLE,
			ACT_HL2MP_RUN,
			ACT_HL2MP_IDLE_CROUCH,
			ACT_HL2MP_WALK_CROUCH,
			ACT_HL2MP_GESTURE_RANGE_ATTACK,
			ACT_HL2MP_GESTURE_RELOAD,
			ACT_HL2MP_JUMP,

			ACT_HL2MP_IDLE_PISTOL,
			ACT_HL2MP_RUN_PISTOL,
			ACT_HL2MP_IDLE_CROUCH_PISTOL,
			ACT_HL2MP_WALK_CROUCH_PISTOL,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_PISTOL,
			ACT_HL2MP_GESTURE_RELOAD_PISTOL,
			ACT_HL2MP_JUMP_PISTOL,

			ACT_HL2MP_IDLE_SMG1,
			ACT_HL2MP_RUN_SMG1,
			ACT_HL2MP_IDLE_CROUCH_SMG1,
			ACT_HL2MP_WALK_CROUCH_SMG1,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_SMG1,
			ACT_HL2MP_GESTURE_RELOAD_SMG1,
			ACT_HL2MP_JUMP_SMG1,

			ACT_HL2MP_IDLE_AR2,
			ACT_HL2MP_RUN_AR2,
			ACT_HL2MP_IDLE_CROUCH_AR2,
			ACT_HL2MP_WALK_CROUCH_AR2,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_AR2,
			ACT_HL2MP_GESTURE_RELOAD_AR2,
			ACT_HL2MP_JUMP_AR2,

			ACT_HL2MP_IDLE_SHOTGUN,
			ACT_HL2MP_RUN_SHOTGUN,
			ACT_HL2MP_IDLE_CROUCH_SHOTGUN,
			ACT_HL2MP_WALK_CROUCH_SHOTGUN,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_SHOTGUN,
			ACT_HL2MP_GESTURE_RELOAD_SHOTGUN,
			ACT_HL2MP_JUMP_SHOTGUN,

			ACT_HL2MP_IDLE_RPG,
			ACT_HL2MP_RUN_RPG,
			ACT_HL2MP_IDLE_CROUCH_RPG,
			ACT_HL2MP_WALK_CROUCH_RPG,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_RPG,
			ACT_HL2MP_GESTURE_RELOAD_RPG,
			ACT_HL2MP_JUMP_RPG,

			ACT_HL2MP_IDLE_GRENADE,
			ACT_HL2MP_RUN_GRENADE,
			ACT_HL2MP_IDLE_CROUCH_GRENADE,
			ACT_HL2MP_WALK_CROUCH_GRENADE,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_GRENADE,
			ACT_HL2MP_GESTURE_RELOAD_GRENADE,
			ACT_HL2MP_JUMP_GRENADE,

			ACT_HL2MP_IDLE_PHYSGUN,
			ACT_HL2MP_RUN_PHYSGUN,
			ACT_HL2MP_IDLE_CROUCH_PHYSGUN,
			ACT_HL2MP_WALK_CROUCH_PHYSGUN,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_PHYSGUN,
			ACT_HL2MP_GESTURE_RELOAD_PHYSGUN,
			ACT_HL2MP_JUMP_PHYSGUN,

			ACT_HL2MP_IDLE_CROSSBOW,
			ACT_HL2MP_RUN_CROSSBOW,
			ACT_HL2MP_IDLE_CROUCH_CROSSBOW,
			ACT_HL2MP_WALK_CROUCH_CROSSBOW,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_CROSSBOW,
			ACT_HL2MP_GESTURE_RELOAD_CROSSBOW,
			ACT_HL2MP_JUMP_CROSSBOW,

			ACT_HL2MP_IDLE_MELEE,
			ACT_HL2MP_RUN_MELEE,
			ACT_HL2MP_IDLE_CROUCH_MELEE,
			ACT_HL2MP_WALK_CROUCH_MELEE,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_MELEE,
			ACT_HL2MP_GESTURE_RELOAD_MELEE,
			ACT_HL2MP_JUMP_MELEE,

			ACT_HL2MP_IDLE_SLAM,
			ACT_HL2MP_RUN_SLAM,
			ACT_HL2MP_IDLE_CROUCH_SLAM,
			ACT_HL2MP_WALK_CROUCH_SLAM,
			ACT_HL2MP_GESTURE_RANGE_ATTACK_SLAM,
			ACT_HL2MP_GESTURE_RELOAD_SLAM,
			ACT_HL2MP_JUMP_SLAM,

			// Portal!
			ACT_VM_FIZZLE,

			// Multiplayer
			ACT_MP_STAND_IDLE,
			ACT_MP_CROUCH_IDLE,
			ACT_MP_CROUCH_DEPLOYED_IDLE,
			ACT_MP_CROUCH_DEPLOYED,
			ACT_MP_DEPLOYED_IDLE,
			ACT_MP_RUN,
			ACT_MP_WALK,
			ACT_MP_AIRWALK,
			ACT_MP_CROUCHWALK,
			ACT_MP_SPRINT,
			ACT_MP_JUMP,
			ACT_MP_JUMP_START,
			ACT_MP_JUMP_FLOAT,
			ACT_MP_JUMP_LAND,
			ACT_MP_DOUBLEJUMP,
			ACT_MP_SWIM,
			ACT_MP_DEPLOYED,
			ACT_MP_SWIM_DEPLOYED,
			ACT_MP_VCD,

			ACT_MP_ATTACK_STAND_PRIMARYFIRE,
			ACT_MP_ATTACK_STAND_PRIMARYFIRE_DEPLOYED,
			ACT_MP_ATTACK_STAND_SECONDARYFIRE,
			ACT_MP_ATTACK_STAND_GRENADE,
			ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,
			ACT_MP_ATTACK_CROUCH_PRIMARYFIRE_DEPLOYED,
			ACT_MP_ATTACK_CROUCH_SECONDARYFIRE,
			ACT_MP_ATTACK_CROUCH_GRENADE,
			ACT_MP_ATTACK_SWIM_PRIMARYFIRE,
			ACT_MP_ATTACK_SWIM_SECONDARYFIRE,
			ACT_MP_ATTACK_SWIM_GRENADE,
			ACT_MP_ATTACK_AIRWALK_PRIMARYFIRE,
			ACT_MP_ATTACK_AIRWALK_SECONDARYFIRE,
			ACT_MP_ATTACK_AIRWALK_GRENADE,
			ACT_MP_RELOAD_STAND,
			ACT_MP_RELOAD_STAND_LOOP,
			ACT_MP_RELOAD_STAND_END,
			ACT_MP_RELOAD_CROUCH,
			ACT_MP_RELOAD_CROUCH_LOOP,
			ACT_MP_RELOAD_CROUCH_END,
			ACT_MP_RELOAD_SWIM,
			ACT_MP_RELOAD_SWIM_LOOP,
			ACT_MP_RELOAD_SWIM_END,
			ACT_MP_RELOAD_AIRWALK,
			ACT_MP_RELOAD_AIRWALK_LOOP,
			ACT_MP_RELOAD_AIRWALK_END,
			ACT_MP_ATTACK_STAND_PREFIRE,
			ACT_MP_ATTACK_STAND_POSTFIRE,
			ACT_MP_ATTACK_STAND_STARTFIRE,
			ACT_MP_ATTACK_CROUCH_PREFIRE,
			ACT_MP_ATTACK_CROUCH_POSTFIRE,
			ACT_MP_ATTACK_SWIM_PREFIRE,
			ACT_MP_ATTACK_SWIM_POSTFIRE,

			// Multiplayer - Primary
			ACT_MP_STAND_PRIMARY,
			ACT_MP_CROUCH_PRIMARY,
			ACT_MP_RUN_PRIMARY,
			ACT_MP_WALK_PRIMARY,
			ACT_MP_AIRWALK_PRIMARY,
			ACT_MP_CROUCHWALK_PRIMARY,
			ACT_MP_JUMP_PRIMARY,
			ACT_MP_JUMP_START_PRIMARY,
			ACT_MP_JUMP_FLOAT_PRIMARY,
			ACT_MP_JUMP_LAND_PRIMARY,
			ACT_MP_SWIM_PRIMARY,
			ACT_MP_DEPLOYED_PRIMARY,
			ACT_MP_SWIM_DEPLOYED_PRIMARY,

			ACT_MP_ATTACK_STAND_PRIMARY,		// RUN, WALK
			ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED,
			ACT_MP_ATTACK_CROUCH_PRIMARY,		// CROUCHWALK
			ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED,
			ACT_MP_ATTACK_SWIM_PRIMARY,
			ACT_MP_ATTACK_AIRWALK_PRIMARY,

			ACT_MP_RELOAD_STAND_PRIMARY,		// RUN, WALK
			ACT_MP_RELOAD_STAND_PRIMARY_LOOP,
			ACT_MP_RELOAD_STAND_PRIMARY_END,
			ACT_MP_RELOAD_CROUCH_PRIMARY,		// CROUCHWALK
			ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP,
			ACT_MP_RELOAD_CROUCH_PRIMARY_END,
			ACT_MP_RELOAD_SWIM_PRIMARY,
			ACT_MP_RELOAD_SWIM_PRIMARY_LOOP,
			ACT_MP_RELOAD_SWIM_PRIMARY_END,
			ACT_MP_RELOAD_AIRWALK_PRIMARY,
			ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP,
			ACT_MP_RELOAD_AIRWALK_PRIMARY_END,

			ACT_MP_ATTACK_STAND_GRENADE_PRIMARY,		// RUN, WALK
			ACT_MP_ATTACK_CROUCH_GRENADE_PRIMARY,		// CROUCHWALK
			ACT_MP_ATTACK_SWIM_GRENADE_PRIMARY,
			ACT_MP_ATTACK_AIRWALK_GRENADE_PRIMARY,

			// Secondary
			ACT_MP_STAND_SECONDARY,
			ACT_MP_CROUCH_SECONDARY,
			ACT_MP_RUN_SECONDARY,
			ACT_MP_WALK_SECONDARY,
			ACT_MP_AIRWALK_SECONDARY,
			ACT_MP_CROUCHWALK_SECONDARY,
			ACT_MP_JUMP_SECONDARY,
			ACT_MP_JUMP_START_SECONDARY,
			ACT_MP_JUMP_FLOAT_SECONDARY,
			ACT_MP_JUMP_LAND_SECONDARY,
			ACT_MP_SWIM_SECONDARY,

			ACT_MP_ATTACK_STAND_SECONDARY,		// RUN, WALK
			ACT_MP_ATTACK_CROUCH_SECONDARY,		// CROUCHWALK
			ACT_MP_ATTACK_SWIM_SECONDARY,
			ACT_MP_ATTACK_AIRWALK_SECONDARY,

			ACT_MP_RELOAD_STAND_SECONDARY,		// RUN, WALK
			ACT_MP_RELOAD_STAND_SECONDARY_LOOP,
			ACT_MP_RELOAD_STAND_SECONDARY_END,
			ACT_MP_RELOAD_CROUCH_SECONDARY,		// CROUCHWALK
			ACT_MP_RELOAD_CROUCH_SECONDARY_LOOP,
			ACT_MP_RELOAD_CROUCH_SECONDARY_END,
			ACT_MP_RELOAD_SWIM_SECONDARY,
			ACT_MP_RELOAD_SWIM_SECONDARY_LOOP,
			ACT_MP_RELOAD_SWIM_SECONDARY_END,
			ACT_MP_RELOAD_AIRWALK_SECONDARY,
			ACT_MP_RELOAD_AIRWALK_SECONDARY_LOOP,
			ACT_MP_RELOAD_AIRWALK_SECONDARY_END,

			ACT_MP_ATTACK_STAND_GRENADE_SECONDARY,		// RUN, WALK
			ACT_MP_ATTACK_CROUCH_GRENADE_SECONDARY,		// CROUCHWALK
			ACT_MP_ATTACK_SWIM_GRENADE_SECONDARY,
			ACT_MP_ATTACK_AIRWALK_GRENADE_SECONDARY,

			// Melee
			ACT_MP_STAND_MELEE,
			ACT_MP_CROUCH_MELEE,
			ACT_MP_RUN_MELEE,
			ACT_MP_WALK_MELEE,
			ACT_MP_AIRWALK_MELEE,
			ACT_MP_CROUCHWALK_MELEE,
			ACT_MP_JUMP_MELEE,
			ACT_MP_JUMP_START_MELEE,
			ACT_MP_JUMP_FLOAT_MELEE,
			ACT_MP_JUMP_LAND_MELEE,
			ACT_MP_SWIM_MELEE,

			ACT_MP_ATTACK_STAND_MELEE,		// RUN, WALK
			ACT_MP_ATTACK_STAND_MELEE_SECONDARY,
			ACT_MP_ATTACK_CROUCH_MELEE,		// CROUCHWALK
			ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY,
			ACT_MP_ATTACK_SWIM_MELEE,
			ACT_MP_ATTACK_AIRWALK_MELEE,

			ACT_MP_ATTACK_STAND_GRENADE_MELEE,		// RUN, WALK
			ACT_MP_ATTACK_CROUCH_GRENADE_MELEE,		// CROUCHWALK
			ACT_MP_ATTACK_SWIM_GRENADE_MELEE,
			ACT_MP_ATTACK_AIRWALK_GRENADE_MELEE,

			// Flinches
			ACT_MP_GESTURE_FLINCH,
			ACT_MP_GESTURE_FLINCH_PRIMARY,
			ACT_MP_GESTURE_FLINCH_SECONDARY,
			ACT_MP_GESTURE_FLINCH_MELEE,

			ACT_MP_GESTURE_FLINCH_HEAD,
			ACT_MP_GESTURE_FLINCH_CHEST,
			ACT_MP_GESTURE_FLINCH_STOMACH,
			ACT_MP_GESTURE_FLINCH_LEFTARM,
			ACT_MP_GESTURE_FLINCH_RIGHTARM,
			ACT_MP_GESTURE_FLINCH_LEFTLEG,
			ACT_MP_GESTURE_FLINCH_RIGHTLEG,

			// Team Fortress specific - medic heal, medic infect, etc.....
			ACT_MP_GRENADE1_DRAW,
			ACT_MP_GRENADE1_IDLE,
			ACT_MP_GRENADE1_ATTACK,
			ACT_MP_GRENADE2_DRAW,
			ACT_MP_GRENADE2_IDLE,
			ACT_MP_GRENADE2_ATTACK,

			ACT_MP_PRIMARY_GRENADE1_DRAW,
			ACT_MP_PRIMARY_GRENADE1_IDLE,
			ACT_MP_PRIMARY_GRENADE1_ATTACK,
			ACT_MP_PRIMARY_GRENADE2_DRAW,
			ACT_MP_PRIMARY_GRENADE2_IDLE,
			ACT_MP_PRIMARY_GRENADE2_ATTACK,

			ACT_MP_SECONDARY_GRENADE1_DRAW,
			ACT_MP_SECONDARY_GRENADE1_IDLE,
			ACT_MP_SECONDARY_GRENADE1_ATTACK,
			ACT_MP_SECONDARY_GRENADE2_DRAW,
			ACT_MP_SECONDARY_GRENADE2_IDLE,
			ACT_MP_SECONDARY_GRENADE2_ATTACK,

			ACT_MP_MELEE_GRENADE1_DRAW,
			ACT_MP_MELEE_GRENADE1_IDLE,
			ACT_MP_MELEE_GRENADE1_ATTACK,
			ACT_MP_MELEE_GRENADE2_DRAW,
			ACT_MP_MELEE_GRENADE2_IDLE,
			ACT_MP_MELEE_GRENADE2_ATTACK,

			// Building
			ACT_MP_STAND_BUILDING,
			ACT_MP_CROUCH_BUILDING,
			ACT_MP_RUN_BUILDING,
			ACT_MP_WALK_BUILDING,
			ACT_MP_AIRWALK_BUILDING,
			ACT_MP_CROUCHWALK_BUILDING,
			ACT_MP_JUMP_BUILDING,
			ACT_MP_JUMP_START_BUILDING,
			ACT_MP_JUMP_FLOAT_BUILDING,
			ACT_MP_JUMP_LAND_BUILDING,
			ACT_MP_SWIM_BUILDING,

			ACT_MP_ATTACK_STAND_BUILDING,		// RUN, WALK
			ACT_MP_ATTACK_CROUCH_BUILDING,		// CROUCHWALK
			ACT_MP_ATTACK_SWIM_BUILDING,
			ACT_MP_ATTACK_AIRWALK_BUILDING,

			ACT_MP_ATTACK_STAND_GRENADE_BUILDING,		// RUN, WALK
			ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING,		// CROUCHWALK
			ACT_MP_ATTACK_SWIM_GRENADE_BUILDING,
			ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING,

			ACT_MP_STAND_PDA,
			ACT_MP_CROUCH_PDA,
			ACT_MP_RUN_PDA,
			ACT_MP_WALK_PDA,
			ACT_MP_AIRWALK_PDA,
			ACT_MP_CROUCHWALK_PDA,
			ACT_MP_JUMP_PDA,
			ACT_MP_JUMP_START_PDA,
			ACT_MP_JUMP_FLOAT_PDA,
			ACT_MP_JUMP_LAND_PDA,
			ACT_MP_SWIM_PDA,

			ACT_MP_ATTACK_STAND_PDA,
			ACT_MP_ATTACK_SWIM_PDA,

			ACT_MP_GESTURE_VC_HANDMOUTH,
			ACT_MP_GESTURE_VC_FINGERPOINT,
			ACT_MP_GESTURE_VC_FISTPUMP,
			ACT_MP_GESTURE_VC_THUMBSUP,
			ACT_MP_GESTURE_VC_NODYES,
			ACT_MP_GESTURE_VC_NODNO,

			ACT_MP_GESTURE_VC_HANDMOUTH_PRIMARY,
			ACT_MP_GESTURE_VC_FINGERPOINT_PRIMARY,
			ACT_MP_GESTURE_VC_FISTPUMP_PRIMARY,
			ACT_MP_GESTURE_VC_THUMBSUP_PRIMARY,
			ACT_MP_GESTURE_VC_NODYES_PRIMARY,
			ACT_MP_GESTURE_VC_NODNO_PRIMARY,

			ACT_MP_GESTURE_VC_HANDMOUTH_SECONDARY,
			ACT_MP_GESTURE_VC_FINGERPOINT_SECONDARY,
			ACT_MP_GESTURE_VC_FISTPUMP_SECONDARY,
			ACT_MP_GESTURE_VC_THUMBSUP_SECONDARY,
			ACT_MP_GESTURE_VC_NODYES_SECONDARY,
			ACT_MP_GESTURE_VC_NODNO_SECONDARY,

			ACT_MP_GESTURE_VC_HANDMOUTH_MELEE,
			ACT_MP_GESTURE_VC_FINGERPOINT_MELEE,
			ACT_MP_GESTURE_VC_FISTPUMP_MELEE,
			ACT_MP_GESTURE_VC_THUMBSUP_MELEE,
			ACT_MP_GESTURE_VC_NODYES_MELEE,
			ACT_MP_GESTURE_VC_NODNO_MELEE,

			ACT_MP_GESTURE_VC_HANDMOUTH_BUILDING,
			ACT_MP_GESTURE_VC_FINGERPOINT_BUILDING,
			ACT_MP_GESTURE_VC_FISTPUMP_BUILDING,
			ACT_MP_GESTURE_VC_THUMBSUP_BUILDING,
			ACT_MP_GESTURE_VC_NODYES_BUILDING,
			ACT_MP_GESTURE_VC_NODNO_BUILDING,

			ACT_MP_GESTURE_VC_HANDMOUTH_PDA,
			ACT_MP_GESTURE_VC_FINGERPOINT_PDA,
			ACT_MP_GESTURE_VC_FISTPUMP_PDA,
			ACT_MP_GESTURE_VC_THUMBSUP_PDA,
			ACT_MP_GESTURE_VC_NODYES_PDA,
			ACT_MP_GESTURE_VC_NODNO_PDA,


			ACT_VM_UNUSABLE,
			ACT_VM_UNUSABLE_TO_USABLE,
			ACT_VM_USABLE_TO_UNUSABLE,

			// this is the end of the global activities, private per-monster activities start here.
			LAST_SHARED_ACTIVITY,
} Activity;
enum Joints
{
	/*
		use this in lookupbone.
	*/
	Pelvis = 0,
	Spine,
	Spine1,
	Spine2,
	Spine3,
	Neck,
	Head,
	RCalvicle,
	RShoulder,
	RForearm,
	RHand,
	LCalvicle,
	LShoulder,
	LForearm,
	LHand,
	RHip,
	RCalf,
	RFoot,
	RToe,
	LHip,
	LCalf,
	LFoot,
	LToe,
};

#define MAT_ANTLION 65
#define MAT_BLOODYFLESH 66
#define MAT_CONCRETE 67
#define MAT_DIRT 68
#define MAT_EGGSHELL 69
#define MAT_FLESH 70
#define MAT_GRATE 71
#define MAT_ALIENFLESH 72
#define MAT_CLIP 73
#define MAT_SNOW 74
#define MAT_PLASTIC 76
#define MAT_METAL 77
#define MAT_SAND 78
#define MAT_FOLIAGE 79
#define MAT_COMPUTER 80
#define MAT_SLOSH 83
#define MAT_TILE 84
#define MAT_GRASS 85
#define MAT_VENT 86
#define MAT_WOOD 87
#define MAT_DEFAULT 88
#define MAT_GLASS 89
#define MAT_WARPSHIELD 90