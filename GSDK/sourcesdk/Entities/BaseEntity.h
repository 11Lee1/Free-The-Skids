#define TICK_INTERVAL			(globals()->interval_per_tick)
#define TIME_TO_TICKS( dt ) ( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL *( t ) )
#define ROUND_TO_TICKS( t ) ( TICK_INTERVAL * TIME_TO_TICKS( t ) )
#define MEMALLOC_REGION 0
#define ALLOW_DATATABLES_PRIVATE_ACCESS() \
	template <typename T> friend int ClientClassInit(T *);


#define DECLARE_CLIENTCLASS_NOBASE ALLOW_DATATABLES_PRIVATE_ACCESS

#define DECLARE_CLIENTCLASS() \
	virtual int YouForgotToImplementOrDeclareClientClass();\
	virtual ClientClass* GetClientClass();\
	static RecvTable *m_pClassRecvTable; \
DECLARE_CLIENTCLASS_NOBASE()

#define DECLARE_NETWORKCLASS()											\
	DECLARE_CLIENTCLASS()

#define DECLARE_PREDICTABLE() template <typename T> friend datamap_t *PredMapInit(T *)
#define DECLARE_INTERPOLATION()


class IPhysicsObject;
class CBaseCombatWeapon;
class IMemAlloc
{
public:
	virtual void *Alloc(size_t nSize, const char *pFileName, int nLine) = 0;
	virtual void *Realloc(void *pMem, size_t nSize, const char *pFileName, int nLine) = 0;
	virtual void  Free(void *pMem, const char *pFileName, int nLine) = 0;
	virtual void *Expand_NoLongerSupported(void *pMem, size_t nSize, const char *pFileName, int nLine) = 0;
};
class ClientEntityList;
enum FireBulletsFlags_t
{
	FIRE_BULLETS_FIRST_SHOT_ACCURATE = 0x1,		// Pop the first shot with perfect accuracy
	FIRE_BULLETS_DONT_HIT_UNDERWATER = 0x2,		// If the shot hits its target underwater, don't damage it
	FIRE_BULLETS_ALLOW_WATER_SURFACE_IMPACTS = 0x4,	// If the shot hits water surface, still call DoImpactEffect
	FIRE_BULLETS_TEMPORARY_DANGER_SOUND = 0x8,		// Danger sounds added from this impact can be stomped immediately if another is queued
};
struct FireBulletsInfo_t
{
	FireBulletsInfo_t()
	{
		m_iShots = 1;
		m_vecSpread.Init(0, 0, 0);
		m_flDistance = 8192;
		m_iTracerFreq = 4;
		m_flDamage = 0;
		m_iPlayerDamage = 0;
		m_pAttacker = NULL;
		m_nFlags = 0;
		m_pAdditionalIgnoreEnt = NULL;
		m_flDamageForceScale = 1.0f;
		m_bPrimaryAttack = true;
		m_bUseServerRandomSeed = false;
	}

	FireBulletsInfo_t(int nShots, const Vector &vecSrc, const Vector &vecDir, const Vector &vecSpread, float flDistance, int nAmmoType, bool bPrimaryAttack = true)
	{
		m_iShots = nShots;
		m_vecSrc = vecSrc;
		m_vecDirShooting = vecDir;
		m_vecSpread = vecSpread;
		m_flDistance = flDistance;
		m_iAmmoType = nAmmoType;
		m_iTracerFreq = 4;
		m_flDamage = 0;
		m_iPlayerDamage = 0;
		m_pAttacker = NULL;
		m_nFlags = 0;
		m_pAdditionalIgnoreEnt = NULL;
		m_flDamageForceScale = 1.0f;
		m_bPrimaryAttack = bPrimaryAttack;
		m_bUseServerRandomSeed = false;
	}

	int m_iShots;
	Vector m_vecSrc;
	Vector m_vecDirShooting;
	Vector m_vecSpread;
	float m_flDistance;
	int m_iAmmoType;
	int m_iTracerFreq;
	float m_flDamage;
	int m_iPlayerDamage;	// Damage to be used instead of m_flDamage if we hit a player
	int m_nFlags;			// See FireBulletsFlags_t
	float m_flDamageForceScale;
	BaseEntity *m_pAttacker;
	BaseEntity *m_pAdditionalIgnoreEnt;
	bool m_bPrimaryAttack;
	bool m_bUseServerRandomSeed;
};
class CTakeDamageInfo;
class CDmgAccumulator;
class ITraceFilter;
class CEntityMapData;
struct trace_t;
struct Ray_t;
class CClientThinkHandlePtr;
typedef CClientThinkHandlePtr* ClientThinkHandle_t;
class ISave;
class IRestore;
class IPhysicsObject;
struct EmitSound_t;
enum RenderGroup_Config_t
{
	// Number of buckets that are used to hold opaque entities
	// and opaque static props by size. The bucketing should be used to reduce overdraw.
	RENDER_GROUP_CFG_NUM_OPAQUE_ENT_BUCKETS = 4,
};
enum RenderGroup_t
{
	RENDER_GROUP_OPAQUE_STATIC_HUGE = 0,		// Huge static prop
	RENDER_GROUP_OPAQUE_ENTITY_HUGE = 1,		// Huge opaque entity
	RENDER_GROUP_OPAQUE_STATIC = RENDER_GROUP_OPAQUE_STATIC_HUGE + (RENDER_GROUP_CFG_NUM_OPAQUE_ENT_BUCKETS - 1) * 2,
	RENDER_GROUP_OPAQUE_ENTITY,					// Opaque entity (smallest size, or default)

	RENDER_GROUP_TRANSLUCENT_ENTITY,
	RENDER_GROUP_TWOPASS,						// Implied opaque and translucent in two passes
	RENDER_GROUP_VIEW_MODEL_OPAQUE,				// Solid weapon view models
	RENDER_GROUP_VIEW_MODEL_TRANSLUCENT,		// Transparent overlays etc

	RENDER_GROUP_OPAQUE_BRUSH,					// Brushes

	RENDER_GROUP_OTHER,							// Unclassfied. Won't get drawn.

	// This one's always gotta be last
	RENDER_GROUP_COUNT
};
enum ShouldTransmitState_t
{
	SHOULDTRANSMIT_START = 0,	// The entity is starting to be transmitted (maybe it entered the PVS).

	SHOULDTRANSMIT_END		// Called when the entity isn't being transmitted by the server.
							// This signals a good time to hide the entity until next time
							// the server wants to transmit its state.
};
enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,	// indicates it was created +and+ entered the pvs
	//	DATA_UPDATE_ENTERED_PVS,
	DATA_UPDATE_DATATABLE_CHANGED,
	//	DATA_UPDATE_LEFT_PVS,
	//	DATA_UPDATE_DESTROYED,		// FIXME: Could enable this, but it's a little worrying
									// since it changes a bunch of existing code
};
typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned int StudioDecalHandle_t;
typedef unsigned short ModelInstanceHandle_t;
typedef unsigned int LightCacheHandle_t;
enum CollideType_t
{
	ENTITY_SHOULD_NOT_COLLIDE = 0,
	ENTITY_SHOULD_COLLIDE,
	ENTITY_SHOULD_RESPOND
};
class CDamageModifier;


class ICollideable
{
	virtual void *GetEntityHandle() = 0;
	virtual const Vector&	OBBMinsPreScaled() const = 0;
	virtual const Vector&	OBBMaxsPreScaled() const = 0;
	virtual const Vector&	OBBMins() const = 0;
	virtual const Vector& OBBMaxs() const = 0;
	virtual void  WorldSpaceTriggerBounds(Vector *pVecWorldMins, Vector *pVecWorldMaxs) const = 0;
	virtual bool  TestCollision(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual bool			TestHitboxes(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual int				GetCollisionModelIndex() = 0;
	virtual const model_t* GetCollisionModel() = 0;
	virtual const Vector&	GetCollisionOrigin() const = 0;
	virtual const QAngle& GetCollisionAngles() const = 0;
};

class C_BaseCombatCharacter;
class IPVSNotify
{
public:
	virtual void OnPVSStatusChanged(bool bInPVS) = 0;
};
class IClientNetworkable;
class C_BaseEntity;
class IClientRenderable;
class ICollideable;
class IClientEntity;
class IClientThinkable;

class IClientNetworkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				Release() = 0;
	virtual ClientClass*		GetClientClass() = 0;
	virtual void				NotifyShouldTransmit(ShouldTransmitState_t state) = 0;
	virtual void				OnPreDataChanged(DataUpdateType_t updateType) = 0;
	virtual void				OnDataChanged(DataUpdateType_t updateType) = 0;
	virtual void				PreDataUpdate(DataUpdateType_t updateType) = 0;
	virtual void				PostDataUpdate(DataUpdateType_t updateType) = 0;
	virtual bool				IsDormant() = 0;
	virtual int					entIndex() = 0;
	virtual void				ReceiveMessage(int classID, bf_read &msg) = 0;
	virtual void*				GetDataTableBasePtr() = 0;
	virtual void				SetDestroyedOnRecreateEntities(void) = 0;
};
enum ShadowType_t
{
	SHADOWS_NONE = 0,
	SHADOWS_SIMPLE,
	SHADOWS_RENDER_TO_TEXTURE,
	SHADOWS_RENDER_TO_TEXTURE_DYNAMIC,	// the shadow is always changing state
	SHADOWS_RENDER_TO_DEPTH_TEXTURE,
};
class IClientRenderable
{
public:
	virtual IClientUnknown*			GetIClientUnknown() = 0;
	virtual Vector const&			GetRenderOrigin() = 0;
	virtual QAngle const&			GetRenderAngles() = 0;
	virtual bool					ShouldDraw() = 0;
	virtual bool					IsTransparent() = 0;
	virtual bool					UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool					UsesFullFrameBufferTexture() = 0;
	virtual ClientShadowHandle_t	GetShadowHandle() = 0;
	virtual ClientRenderHandle_t&	RenderHandle() = 0;
	virtual model_t*				GetModel() = 0;
	virtual void					DrawModel(int flags) = 0;
	virtual int						GetBody() = 0;
	virtual void					ComputeFxBled() = 0;
	virtual int						GetFxBlend() = 0;
	virtual void					GetColorModulation(float* color) = 0;
	virtual bool					LODTest() = 0;
	virtual bool					SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void					SetupWeights(const matrix3x4_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) = 0;
	virtual void					DoAnimationEvents(void) = 0;
	virtual IPVSNotify*				GetPVSNotifyInterface() = 0;
	virtual void					GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void					GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void					GetShadowRenderBounds(Vector &mins, Vector &maxs, ShadowType_t shadowType) = 0;
	virtual bool					ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool					GetShadowCastDistance(float *pDist, ShadowType_t shadowType) const = 0;
	virtual bool					GetShadowCastDirection(Vector *pDirection, ShadowType_t shadowType) const = 0;
	virtual bool					IsShadowDirty() = 0;
	virtual void					MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*		GetShadowParent() = 0;
	virtual IClientRenderable*		FirstShadowChild() = 0;
	virtual IClientRenderable*		NextShadowPeer() = 0;
	virtual ShadowType_t			ShadowCastType() = 0;
	virtual void					CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t	GetModelInstance() = 0;
	virtual const matrix3x4_t&		RenderableToWorldTransform() = 0;
	virtual int						LookupAttachment(const char *pAttachmentName) = 0;
	virtual	bool					GetAttachment(int number, Vector &origin, QAngle &angles) = 0;
	virtual bool					GetAttachment(int number, matrix3x4_t &matrix) = 0;
	virtual float*					GetRenderClipPlane(void) = 0;
	virtual int						GetSkin() = 0;
	virtual bool					IsTwoPass(void) = 0;
	virtual void					OnThreadedDrawSetup() = 0;
	virtual bool					UsesFlexDelayedWeights() = 0;
	virtual void					RecordToolMessage() = 0;
	virtual bool					IgnoresZBuffer(void) const = 0;
};
class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual ClientThinkHandle_t	GetThinkHandle() = 0;
	virtual void				SetThinkHandle(ClientThinkHandle_t hThink) = 0;
	virtual void				Release() = 0;
};


class C_BaseAnimating;
class BaseEntity : public IClientEntity
{
	DECLARE_CLASS_NOBASE(BaseEntity);
public: // 200
	virtual ~BaseEntity();
	DECLARE_DATADESC();
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();

	/*16*/	virtual void	FireBullets(const FireBulletsInfo_t &info) = 0;
	/*17*/	virtual void	ModifyFireBulletsDamage(CTakeDamageInfo* info) = 0;
	/*18*/	virtual bool	ShouldDrawUnderwaterBulletBubbles() = 0;
	/*19*/	virtual bool	ShouldDrawWaterImpacts() = 0;
	/*20*/	virtual bool	HandleShotImpactingWater(const FireBulletsInfo_t &info, const Vector &vecEnd, ITraceFilter *pTraceFilter, Vector *pVecTracerDest) = 0;
	/*21*/	virtual ITraceFilter* GetBeamTraceFilter() = 0;
	/*22*/	virtual void	DispatchTraceAttack(const CTakeDamageInfo &info, const Vector &vecDir, trace_t *ptr, CDmgAccumulator *pAccumulator = NULL) = 0;
	/*23*/	virtual void	TraceAttack(const CTakeDamageInfo &info, const Vector &vecDir, trace_t *ptr, CDmgAccumulator *pAccumulator = NULL) = 0;
	/*24*/	virtual void	DoImpactEffect(trace_t &tr, int nDamageType) = 0;
	/*25*/	virtual void	MakeTracer(const Vector &vecTracerSrc, const trace_t &tr, int iTracerType) = 0;
	/*26*/	virtual int		GetTracerAttachment(void) = 0;
	/*27*/	virtual int		BloodColor() = 0;
	/*28*/	virtual const char*	GetTracerType() = 0;
	/*29*/	virtual void	Spawn() = 0;
	/*30*/	virtual void	SpawnClientEntity() = 0;
	/*31*/	virtual void	Precache() = 0;
	/*32*/	virtual void	Activate() = 0;
	/*33*/	virtual void	ParseMapData(CEntityMapData *mapData) = 0;
	/*34*/	virtual bool	KeyValue(const char *szKeyName, const char *szValue) = 0;
	/*35*/	virtual bool	KeyValue(const char *szKeyName, float flValue) = 0;
	/*36*/	virtual bool	KeyValue(const char *szKeyName, const Vector &vecValue) = 0;
	/*37*/	virtual bool	GetKeyValue(const char *szKeyName, char *szValue, int iMaxLen) = 0;
	/*38*/	virtual bool	Init(int entnum, int iSerialNum) = 0;
	/*39*/	virtual C_BaseAnimating*	GetBaseAnimating() = 0;
	/*40*/	virtual void	SetClassname(const char *className) = 0;
	/*41*/	virtual Vector	GetObserverCamOrigin(void) = 0;
	/*42*/	virtual bool	TestCollision(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr) = 0;
	/*43*/	virtual bool	TestHitboxes(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr) = 0;
	/*44*/	virtual float	GetAttackDamageScale(void) = 0;
	/*45*/	virtual void	dunno() = 0;
	/*46*/	virtual void	ValidateModelIndex(void) = 0;
	/*47*/	virtual void	SetDormant(bool bDormant) = 0;
	/*48*/	virtual bool	IsDormant(void) = 0;
	/*49*/	virtual void	SetThinkHandle(ClientThinkHandle_t hThink) = 0;
	/*50*/	virtual bool	ShouldSavePhysics() = 0;
	/*51*/	virtual void	OnSave() = 0;
	/*52*/	virtual void	OnRestore() = 0;
	/*53*/	virtual int		ObjectCaps() = 0;
	/*54*/	virtual int		Save(ISave &save) = 0;
	/*55*/	virtual int		Restore(IRestore &restore) = 0;
	/*56*/	virtual bool	CreateVPhysics() = 0;
	/*57*/	virtual void	VPhysicsDestroyObject(void) = 0;
	/*58*/	virtual void	GMOD_VPhysicsTest() = 0; // didn't add args
	/*59*/	virtual void	GMOD_GetPhysBoneMatrix() = 0; // didn't add args
	/*60*/	virtual void	VPhysicsUpdate(IPhysicsObject *pPhysics) = 0;
	/*61*/	virtual int		VPhysicsGetObjectList(IPhysicsObject **pList, int listMax) = 0;
	/*62*/	virtual bool	VPhysicsIsFlesh(void) = 0;
	/*63*/	virtual void	dunno1(void) = 0;
	/*64*/	virtual void	dunno2(void) = 0;
	/*65*/	virtual Vector&	GetPrevLocalOrigin() = 0;
	/*66*/	virtual QAngle&	GetPrevLocalAngles() = 0;
	/*67*/	virtual int		CalcOverrideModelIndex() = 0;
	/*68*/	virtual Vector& WorldAlignMins() = 0;
	/*69*/	virtual Vector& WorldAlignMaxs() = 0;
	/*70*/	virtual Vector& WorldSpaceCenter() = 0;
	/*71*/	virtual int		LookupAttachment(const char*) = 0;
	/*72*/	virtual bool	GetAttachment(int number, matrix3x4_t &matrix) = 0;
	/*73*/	virtual bool	GetAttachment(int number, Vector &origin) = 0;
	/*74*/	virtual	bool	GetAttachment(int number, Vector &origin, QAngle &angles) = 0;
	/*75*/	virtual bool	GetAttachmentVelocity(int number, Vector &originVel, Quaternion &angleVel) = 0;
	/*76*/	virtual void*/*C_Team* */		GetTeam() = 0;
	/*77*/	virtual int		GetTeamNumber(void) = 0;
	/*78*/	virtual void	ChangeTeam(int iTeamNum) = 0;
	/*79*/	virtual int		GetRenderTeamNumber(void) = 0;
	/*80*/	virtual bool	InSameTeam(BaseEntity *pEntity) = 0;
	/*81*/	virtual bool	InLocalTeam(void) = 0;
	/*82*/	virtual bool	IsValidIDTarget() = 0;
	/*83*/	virtual const char	*GetIDString(void) = 0;
	/*84*/	virtual void ModifyEmitSoundParams(EmitSound_t &params) = 0;
	/*85*/	virtual bool InitializeAsClientEntity(const char *pszModelName, RenderGroup_t renderGroup) = 0;
	/*86*/	virtual void	Simulate() = 0;
	/*87*/	virtual void		OnDataChanged(void* type /*DataUpdateType_t type*/) = 0;
	/*88*/	virtual void	GetAimEntOrigin(IClientEntity *pAttachedTo, Vector *pAbsOrigin, QAngle *pAbsAngles) = 0;
	/*89*/	virtual Vector& GetOldOrigin() = 0;
	/*90*/	virtual RenderGroup_t GetRenderGroup() = 0;
	/*91*/	virtual void	GetToolRecordingState(KeyValues *msg) = 0;
	/*92*/	virtual void	CleanupToolRecordingState(KeyValues *msg) = 0;
	/*93*/	virtual CollideType_t GetCollideType(void) = 0;
	/*94*/	virtual bool	ShouldDraw() = 0;
	/*95*/	virtual	void	OnLatchInterpolatedVariables(int flags) = 0;
	/*96*/	virtual int		OnNewModel() = 0;
	/*97*/	virtual void	OnNewParticleEffect() = 0;
	/*98*/	virtual void	ResetLatched() = 0;
	/*99*/	virtual bool	Interpolate(float currentTime) = 0;
	/*100*/	virtual bool	IsSubModel(void) = 0;
	/*101*/	virtual void	CreateLightEffects(void) = 0;
	/*102*/	virtual void	Clear(void) = 0;
	/*103*/	virtual int		DrawBrushModel(bool bTranslucent, int nFlags, bool bTwoPass) = 0;
	/*104*/	virtual float	GetTextureAnimationStartTime() = 0;
	/*105*/	virtual void	TextureAnimationWrapped() = 0;
	/*106*/	virtual void	SetNextClientThink(float nextThinkTime) = 0;
	/*107*/	virtual void	SetHealth(int) = 0;
	/*108*/	virtual int		GetHealth() const { return 0; }
	/*109*/	virtual int		GetMaxHealth() const { return 1; }
	/*110*/	virtual void	AddDecal(const Vector& rayStart, const Vector& rayEnd, const Vector& decalCenter, int hitbox, int decalIndex, bool doTrace, trace_t& tr, int maxLODToDecal = -1) = 0;
	/*111*/	virtual bool	IsClientCreated(void) = 0;
	/*112*/	virtual void	UpdateOnRemove(void) = 0;
	/*113*/	virtual void	SUB_Remove(void) = 0;
	/*114*/	virtual void	SetPredictable(bool state) = 0;
	/*115*/	virtual int		RestoreData(const char *context, int slot, int type) = 0;
	/*116*/	virtual char const *	DamageDecal(int bitsDamageType, int gameMaterial) = 0;
	/*117*/	virtual void	DecalTrace(trace_t *pTrace, char const *decalName) = 0;
	/*118*/	virtual void	ImpactTrace(trace_t *pTrace, int iDamageType, const char *pCustomImpactName) = 0;
	/*119*/	virtual bool	ShouldPredict() = 0;
	/*120*/	virtual void	Think(void) = 0;
	/*121*/	virtual bool	CanBePoweredUp() = 0;
	/*122*/	virtual bool	AttemptToPowerup(int iPowerup, float flTime, float flAmount = 0, BaseEntity *pAttacker = NULL, CDamageModifier *pDamageModifier = NULL) = 0;
	/*123*/	virtual bool	IsCurrentlyTouching(void) = 0;
	/*124*/	virtual void	StartTouch(BaseEntity *pOther) = 0;
	/*125*/	virtual void	Touch(BaseEntity *pOther) = 0;
	/*126*/	virtual void	EndTouch(BaseEntity *pOther) = 0;
	/*127*/	virtual unsigned int	PhysicsSolidMaskForEntity(void) = 0;
	/*128*/	virtual void	PhysicsSimulate(void) = 0;
	/*129*/	virtual bool	IsAlive(void) = 0;
	/*130*/	virtual bool	IsPlayer() = 0;
	/*131*/	virtual bool	IsBaseCombatCharacter() = 0;
	/*132*/	virtual void*	MyCombatCharacterPointer() = 0;
	/*133*/	virtual bool	IsNPC() = 0;
	/*134*/	virtual bool	IsNextBot() = 0;
	/*135*/	virtual bool	IsBaseObject() = 0;
	/*136*/	virtual bool	IsBaseCombatWeapon() = 0;
	/*137*/	virtual CBaseCombatWeapon*	MyCombatWeaponPointer() = 0;
	/*138*/	virtual bool	IsBaseTrain() = 0;
	/*139*/	virtual Vector	EyePosition(void) = 0;
	/*140*/	virtual QAngle&	EyeAngles(void) = 0;		// Direction of eyes
	/*141*/	virtual QAngle&	LocalEyeAngles(void) = 0;
	/*142*/	virtual Vector EarPosition(void) = 0;
	/*143*/	virtual bool	ShouldCollide(int collisionGroup, int contentsMask) = 0;
	/*144*/	virtual Vector& GetViewOffset() = 0;
	/*145*/	virtual void	SetViewOffset(const Vector& v) = 0;
	/*146*/	virtual bool	ShouldInterpolate() = 0;
	/*147*/	virtual int		GetClientSideFade() = 0;
	/*148*/	virtual void	BoneMergeFastCullBloat(Vector &localMins, Vector &localMaxs, const Vector &thisEntityMins, const Vector &thisEntityMaxs) = 0;
	/*149*/	virtual void	OnPredictedEntityRemove() = 0;
	/*150*/	virtual BaseEntity *GetShadowUseOtherEntity(void) = 0;
	/*151*/	virtual void	SetShadowUseOtherEntity(BaseEntity *pEntity) = 0;
	/*152*/	virtual bool	AddRagdollToFadeQueue() = 0;
	/*153*/	virtual bool	IsDeflectable() = 0;
	/*154*/	virtual int		GetStudioBody() = 0;
	/*155*/	virtual void	PerformCustomPhysics(Vector *pNewPosition, Vector *pNewVelocity, QAngle *pNewAngles, QAngle *pNewAngVelocity) = 0;
	/*156*/	virtual void	dunno13() = 0;
	/*157*/	virtual void	VPhysicsGetElement() = 0;
	/*158*/	virtual bool	IsARagdoll() = 0;
	virtual void	SetMaterialOverride() = 0; // dont use the ones I dont have marked with their index, I haven't set the type & function up properly.
	virtual void	SetMaterialOverridePointer() = 0;
	virtual void	GetMaterialOverridePointer() = 0;
	virtual void	GetMaterialOverride() = 0;
	virtual void	StartMaterialOverride() = 0;
	virtual void	EndMaterialOverride() = 0;
	/*165*/virtual float	GetCreationTime() = 0;
	/*166*/virtual bool		IsPredicted() = 0;
	/*167*/virtual bool		IsWeapon() = 0;
	/*168*/virtual bool		IsVehicle() = 0;
	/*169*/virtual bool		IsJeep() = 0;
	/*170*/virtual bool		UsesLua() = 0;
	/*171*/virtual int		GetLuaEntityType() = 0;
	virtual void	PushEntity() = 0;
	virtual void	Push_This_Entity() = 0;
	virtual void	SetEntity() = 0;
	/*175*/virtual int		GetParentPhysicsNum() = 0;
	/*176*/virtual void		SetParentPhysicsNum(int num) = 0;
	virtual void	StartMotionController() = 0;
	virtual void	StopMotionController() = 0;
	virtual void	AttachObjectToMotionController(IPhysicsObject *) = 0;
	virtual void	DetachObjectFromMotionController(IPhysicsObject *) = 0;
	virtual void	GetCustomisedRenderBounds() = 0;
	virtual void	SetCustomisedRenderBounds() = 0;
	/*183*/virtual const char* GetLuaScriptName() = 0;
	virtual bool	SpawnedViaLua() = 0;
	virtual void	OverridePosition() = 0;
	virtual void	InitializeScriptedEntity(const char*) = 0;
	virtual int		ClearLuaData() = 0;
	virtual void	GetLuaTable() = 0;
	virtual void	GetLuaEntity() = 0; // 189
	virtual void	SetLuaTable() = 0;
	virtual void	Lua_OnEntityInitialized() = 0;
	/*192*/virtual bool	HasLuaTable() = 0;
	/*193*/virtual bool	LuaEntityInitialized() = 0;
	virtual void	ForcePhysicsDropObject() = 0;
	virtual void	StartDriving() = 0;
	virtual void	FinishDriving() = 0;
	/*187*/virtual bool	GMod_ShouldRenderEntity() = 0;
	virtual bool	dunnozxd() = 0;
	virtual void*	Lua_GetLuaClass() = 0;
	virtual void	VPhysicsCollision(int, void *) = 0;

public:
	CHL2MPPlayerAnimState* GetAnimState()
	{
		return *(CHL2MPPlayerAnimState**)((uintptr_t)this + offsets::DT_HL2MP_Player::m_hRagdoll - 0x40);
	}

	Vector& CollisionMins()
	{
		return *(Vector*)((uintptr_t)this + offsets::DT_BaseEntity::m_Collision + 0x74);
	}
	Vector& CollisionMaxs()
	{
		return *(Vector*)((uintptr_t)this + offsets::DT_BaseEntity::m_Collision + 0x80);
	}

	CStudioHdr* GetModelPtr()
	{
		return *(CStudioHdr**)((uintptr_t)this + 0x16CC);
	}

	int m_iDefaultFOV()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BasePlayer::m_iDefaultFOV);
	}

	int m_iFOV()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BasePlayer::m_iFOV);
	}
	const char* GetLuaName()
	{
		if (!this->UsesLua())
			return "";

		auto Lua = LuaShared()->GetLuaInterface(GarrysMod::Lua::Client);
		this->PushEntity();
		Lua->GetField(-1, "PrintName");
		if (!Lua->IsType(-1, GarrysMod::Lua::Type::STRING))
		{
			Lua->Pop(2);
			return this->GetLuaScriptName();
		}
		const char* out = Lua->GetString(-1);
		Lua->Pop(2);
		return out;
	}
	//0x8c
	float& m_flSimulationTime()
	{
		return *(float*)((uintptr_t)this + offsets::DT_BaseEntity::m_flSimulationTime);
	}

	int& m_nModelIndex()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BaseEntity::m_nModelIndex);
	}

	int& m_lifeState()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BasePlayer::m_lifeState);
	}

	Vector& m_vecOrigin()
	{
		return *(Vector*)((uintptr_t)this + offsets::DT_BaseEntity::m_vecOrigin);
	}
	Vector& m_vecVelocity()
	{
		return *(Vector*)((uintptr_t)this + offsets::DT_BaseEntity::m_vecVelocity0);
	}

	QAngle& m_angRotation()
	{
		return *(QAngle*)((uintptr_t)this + offsets::DT_BaseEntity::m_angRotation);
	}

	bool& m_bClientSideAnimation()
	{
		return *(bool*)((uintptr_t)this + offsets::DT_BaseAnimating::m_bClientSideAnimation);
	}

	CUtlFlags<int> GetFlags()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BasePlayer::m_fFlags);
	}

	/*
		please just use CHL2MPPlayerAnimState for these two
	*/
	void SetAbsOrigin(Vector Pos)
	{
		if (!this)
			return;
		using SetAbsOriginFn = void(__thiscall*)(void*, const Vector&Origin);
		static SetAbsOriginFn SetAbsOrigin;

		if (!SetAbsOrigin)
			SetAbsOrigin = (SetAbsOriginFn)(Util::Pattern::FindPattern("client.dll", "55 8B EC 56 57 8B F1 E8 ? ? ? ? 8B 7D 08 F3 0F 10 07"));
		if (!SetAbsOrigin)
			return;

		SetAbsOrigin(this, Pos);
	}
	void SetAbsAngles(QAngle angles)
	{
		if (!this)
			return;

		using SetAbsAnglesFn = void(__thiscall*)(void*, const QAngle&angles);
		static SetAbsAnglesFn SetAbsAngles;

		if (!SetAbsAngles)
			SetAbsAngles = (SetAbsAnglesFn)(Util::Pattern::FindPattern("client.dll", "55 8B EC 81 EC ? ? ? ? 56 57 8B F1 E8 ? ? ? ? 8B 7D 08"));
		if (!SetAbsAngles)
			return;

		SetAbsAngles(this, angles);
	}

	void InvalidateBoneCache()
	{
		if (!this)
			return;

		using InvalidateBoneCacheFn = void(__thiscall*)(void*);
		static InvalidateBoneCacheFn InvalidateBoneCache;

		if (!InvalidateBoneCache)
			InvalidateBoneCache = (InvalidateBoneCacheFn)(Util::Pattern::FindPattern("client.dll", "A1 ? ? ? ? 48 C7 81 ? ? ? ? ? ? ? ?"));
		if (!InvalidateBoneCache)
			return;
		InvalidateBoneCache(this);
	}
	
	int& m_nSequence()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BaseAnimating::m_nSequence);
	}
	float& m_flCycle()
	{
		return *(float*)((uintptr_t)this + offsets::DT_BaseAnimating::m_nSequence);
	}
	int m_nSkin()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BaseAnimating::m_nSkin);
	}
	int m_nBody()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BaseAnimating::m_nBody);
	}
	int m_nHitboxSet()
	{
		return *(int*)((uintptr_t)this + offsets::DT_BaseAnimating::m_nHitboxSet);
	}
	float m_flModelScale()
	{
		return *(float*)((uintptr_t)this + offsets::DT_BaseAnimating::m_flModelScale);
	}
	Vector Origin()
	{
		return *(Vector*)((uintptr_t)this + offsets::DT_BaseEntity::m_vecOrigin);
	}

	CBaseCombatWeapon* GetActiveWeapon()
	{
		uintptr_t hActiveWeapon = *(uintptr_t*)((uintptr_t)this + offsets::DT_BaseCombatCharacter::m_hActiveWeapon);

		return (CBaseCombatWeapon*)(cliententitylist()->GetClientEntityFromHandle(hActiveWeapon));
	}
	BaseEntity* GetOwner()
	{
		uintptr_t howner = *(uintptr_t*)((uintptr_t)this + offsets::DT_BaseEntity::m_hOwnerEntity);
		if (!howner)
			return nullptr;

		return (BaseEntity*)cliententitylist()->GetClientEntityFromHandle(howner);
	}
	BaseEntity* GetHands()
	{
		uintptr_t m_Hands = *(uintptr_t*)((uintptr_t)this + offsets::DT_GMOD_Player::m_Hands);
		if (!m_Hands)
			return nullptr;

		return (BaseEntity*)cliententitylist()->GetClientEntityFromHandle(m_Hands);
	}
	bool hasowner()
	{
		if (this->GetOwner())
			return true;

		return false;
	}
	bool IsHands()
	{
		if (!this)
			return false;

		BaseEntity* owner = GetOwner();
		if (!owner || !owner->IsPlayer())
			return false;

		BaseEntity* hands = owner->GetHands();
		if (hands == this)
			return true;

		return false;
	}
	int entIndex()
	{
		return GetClientNetworkable()->entIndex();
	}
	float GetPoseParameter(int index)
	{
		return *(float*)((uintptr_t)this + offsets::DT_BaseAnimating::m_flPoseParameter + sizeof(float) * index);
	}
	bool SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		return GetClientRenderable()->SetupBones(pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
	model_t* GetModel()
	{
		return GetClientRenderable()->GetModel();
	}
	int& m_nTickBase()
	{
		return *(int*)((uintptr_t)this + 0x2580);
	}
	bool IsWorld()
	{
		return (this->entIndex() == 0);
	}
};
