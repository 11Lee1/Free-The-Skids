class CBaseCombatCharacter;
class CBasePlayer;
class CHudTexture;
class CBaseViewModel;
class C_BaseViewModel;
class C_GMOD_Player;
struct WeaponProficiencyInfo_t
{
	float	spreadscale;
	float	bias;
};
struct acttable_t
{
	int			baseAct;
	int			weaponAct;
	bool		required;
};
typedef enum {
	EMPTY,
	SINGLE,
	SINGLE_NPC,
	WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
	DOUBLE_NPC,
	BURST,
	RELOAD,
	RELOAD_NPC,
	MELEE_MISS,
	MELEE_HIT,
	MELEE_HIT_WORLD,
	SPECIAL1,
	SPECIAL2,
	SPECIAL3,
	TAUNT,
	DEPLOY,

	// Add new shoot sound types here

	NUM_SHOOT_SOUND_TYPES,
} WeaponSound_t;

enum WeaponProficiency_t
{
	WEAPON_PROFICIENCY_POOR = 0,
	WEAPON_PROFICIENCY_AVERAGE,
	WEAPON_PROFICIENCY_GOOD,
	WEAPON_PROFICIENCY_VERY_GOOD,
	WEAPON_PROFICIENCY_PERFECT,
};
class CBaseCombatWeapon : public C_BaseAnimating
{
public: // 442 - 183
	// fix this.
	DECLARE_CLASS(CBaseCombatWeapon, C_BaseAnimating);

	virtual int				GetSubType(void) = 0;
	virtual void			SetSubType(int iType) = 0;
	virtual void			Equip(CBaseCombatCharacter *pOwner) = 0;
	virtual void			Drop(const Vector &vecVelocity) = 0;
	/*5*/virtual int		UpdateClientData(CBasePlayer *pPlayer) = 0;
	virtual bool			IsAllowedToSwitch(void) = 0;
	virtual bool			CanBeSelected(void) = 0;
	virtual bool			VisibleInWeaponSelection(void) = 0;
	virtual bool			HasAmmo(void) = 0;
	/*10*/virtual void		SetPickupTouch(void) = 0;
	virtual void			DefaultTouch(BaseEntity *pOther) = 0;	// default weapon touch
	virtual void			GiveTo(BaseEntity *pOther) = 0;
	virtual bool			ShouldDisplayAltFireHUDHint() = 0;
	virtual void			DisplayAltFireHudHint() = 0;
	/*15*/virtual void		RescindAltFireHudHint() = 0; ///< undisplay the hud hint and pretend it never showed.
	virtual bool			ShouldDisplayReloadHUDHint() = 0;
	virtual void			DisplayReloadHudHint() = 0;
	virtual void			RescindReloadHudHint() = 0;
	virtual void			SetViewModelIndex(int index = 0) = 0;
	/*20*/virtual bool		SendWeaponAnim(int iActivity) = 0;
	virtual void			SendViewModelAnim(int nSequence) = 0;
	virtual void			SetViewModel() = 0;
	virtual bool			HasWeaponIdleTimeElapsed(void) = 0;
	virtual void			SetWeaponIdleTime(float time) = 0;
	/*25*/virtual float		GetWeaponIdleTime(void) = 0;
	virtual bool			HasAnyAmmo(void) = 0;							// Returns true is weapon has ammo
	virtual bool			HasPrimaryAmmo(void) = 0;						// Returns true is weapon has ammo
	virtual bool			HasSecondaryAmmo(void) = 0;
	virtual bool			CanHolster(void) = 0;
	/*30*/virtual bool		DefaultDeploy(char *szViewModel, char *szWeaponModel, int iActivity, char *szAnimExt) = 0;
	virtual bool			CanDeploy(void) = 0;
	virtual bool			Deploy(void) = 0;
	virtual bool			Holster(CBaseCombatWeapon *pSwitchingTo = NULL) = 0;
	virtual CBaseCombatWeapon *GetLastWeapon(void) = 0;
	/*35*/virtual void		SetWeaponVisible(bool visible) = 0;
	virtual bool			IsWeaponVisible(void) = 0;
	virtual bool			ReloadOrSwitchWeapons(void) = 0;
	virtual void			OnActiveStateChanged(int iOldState) = 0;
	virtual bool			HolsterOnDetach() = 0;
	/*40*/virtual bool		IsHolstered() = 0;
	virtual void			Detach() = 0;
	virtual void			ItemPreFrame(void) = 0;					// called each frame by the player PreThink
	virtual void			ItemPostFrame(void) = 0;					// called each frame by the player PostThink
	virtual void			ItemBusyFrame(void) = 0;					// called each frame by the player PostThink, if the player's not ready to attack yet
	/*45*/virtual void		ItemHolsterFrame(void) = 0;			// called each frame by the player PreThink, if the weapon is holstered
	virtual void			WeaponIdle(void) = 0;						// called when no buttons pressed
	virtual void			HandleFireOnEmpty() = 0; // Called when they have the attack button down
	virtual bool			CanPerformSecondaryAttack() = 0;
	virtual bool			ShouldBlockPrimaryFire() = 0;
	/*50*/virtual void		CreateMove(float flInputSampleTime, CUserCmd *pCmd, const QAngle &vecOldViewAngles) = 0;
	virtual bool			IsWeaponZoomed() = 0;
	virtual	void			CheckReload(void) = 0;
	virtual void			FinishReload(void) = 0;
	virtual void			AbortReload(void) = 0;
	/*55*/virtual bool		Reload(void) = 0;
	virtual bool			AutoFiresFullClip(void) = 0;
	virtual void			UpdateAutoFire(void) = 0;
	virtual void			PrimaryAttack(void) = 0;
	virtual void			SecondaryAttack(void) = 0;
	/*60*/virtual Activity	GetPrimaryAttackActivity(void) = 0;
	virtual Activity		GetSecondaryAttackActivity(void) = 0;
	virtual Activity		GetDrawActivity(void) = 0;
	virtual float			GetDefaultAnimSpeed(void) = 0;
	virtual int				GetBulletType(void) = 0;
	/*65*/virtual Vector	GetBulletSpread(WeaponProficiency_t proficiency) = 0;
	virtual const Vector&	orgGetBulletSpread(void) = 0;
	virtual float			GetSpreadBias(WeaponProficiency_t proficiency) = 0;
	virtual float			GetFireRate(void) = 0;
	virtual int				GetMinBurst() = 0;
	virtual int				GetMaxBurst() = 0;
	virtual float			GetMinRestTime() = 0;
	virtual float			GetMaxRestTime() = 0;
	virtual int				GetRandomBurst() = 0;
	virtual void			WeaponSound(WeaponSound_t sound_type, float soundtime = 0.0f) = 0;
	virtual void			StopWeaponSound(WeaponSound_t sound_type) = 0;
	virtual const			WeaponProficiencyInfo_t *GetProficiencyValues() = 0;
	virtual float			GetMaxAutoAimDeflection() = 0;
	virtual float			WeaponAutoAimScale() = 0;
	virtual bool			StartSprinting(void) = 0;
	virtual bool			StopSprinting(void) = 0;
	virtual float			GetDamage(float flDistance, int iLocation) = 0;
	virtual void			SetActivity(Activity act, float duration) = 0;
	virtual void			AddViewKick(void) = 0;
	virtual char*			GetDeathNoticeName(void) = 0;
	virtual void			OnPickedUp(CBaseCombatCharacter *pNewOwner) = 0;
	virtual void			AddViewmodelBob(CBaseViewModel *viewmodel, Vector &origin, QAngle &angles) = 0;
	virtual float			CalcViewmodelBob(void) = 0;
	virtual void			GetControlPanelInfo(int nPanelIndex, const char *&pPanelName) = 0;
	virtual void			GetControlPanelClassName(int nPanelIndex, const char *&pPanelName) = 0;
	virtual bool			ShouldShowControlPanels(void) = 0;
	virtual bool			CanBePickedUpByNPCs(void) = 0;
	virtual int				GetSkinOverride() = 0;
	virtual const char*		GetViewModel(int viewmodelindex = 0) = 0;
	virtual const char*		GetWorldModel(void) = 0;
	virtual const char*		GetAnimPrefix(void) = 0;
	virtual int				GetMaxClip1(void) = 0;
	virtual int				GetMaxClip2(void) = 0;
	virtual int				GetDefaultClip1(void) = 0;
	virtual int				GetDefaultClip2(void) = 0;
	virtual int				GetWeight(void) = 0;
	virtual bool			AllowsAutoSwitchTo(void) = 0;
	virtual bool			AllowsAutoSwitchFrom(void) = 0;
	virtual void			ForceWeaponSwitch() = 0;
	virtual int				GetWeaponFlags(void) = 0;
	virtual int				GetSlot(void) = 0;
	virtual int				GetPosition(void) = 0;
	virtual char const*		GetName(void) = 0;
	virtual char const*		GetPrintName(void) = 0;
	virtual char const*		GetShootSound(int iIndex) = 0;
	virtual int				GetRumbleEffect() = 0;
	virtual bool			UsesClipsForAmmo1(void) = 0;
	virtual bool			UsesClipsForAmmo2(void) = 0;
	virtual char const*		GetHoldType() = 0;
	virtual void			SetHoldType(char const*) = 0;
	virtual const unsigned char *GetEncryptionKey(void) = 0;
	virtual int				GetPrimaryAmmoType(void) = 0;
	virtual int				GetSecondaryAmmoType(void) = 0;
	virtual int				Clip1() = 0;
	virtual int				Clip2() = 0;
	virtual CHudTexture const*	GetSpriteActive(void) const = 0;
	virtual CHudTexture const*	GetSpriteInactive(void) const = 0;
	virtual CHudTexture const*	GetSpriteAmmo(void) const = 0;
	virtual CHudTexture const*	GetSpriteAmmo2(void) const = 0;
	virtual CHudTexture const*	GetSpriteCrosshair(void) const = 0;
	virtual CHudTexture const*	GetSpriteAutoaim(void) const = 0;
	virtual CHudTexture const*	GetSpriteZoomedCrosshair(void) const = 0;
	virtual CHudTexture const*	GetSpriteZoomedAutoaim(void) const = 0;
	virtual Activity		ActivityOverride(Activity baseAct, bool *pRequired) = 0;
	virtual	acttable_t*		ActivityList(void) = 0;
	virtual	int				ActivityListCount(void) = 0;
	virtual void			PoseParameterOverride(bool) = 0;
	virtual int				PoseParamList(int&) = 0;
	virtual bool			ShouldUseLargeViewModelVROverride() = 0;
	virtual bool			OnFireEvent(C_BaseViewModel *pViewModel, const Vector& origin, const QAngle& angles, int event, const char *options) = 0;
	virtual void			RestartParticleEffect(void) = 0;
	virtual void			Redraw(void) = 0;
	virtual void			ViewModelDrawn(CBaseViewModel *pViewModel) = 0;
	virtual void			RenderScreen() = 0;
	virtual void			dunno() = 0;
	virtual void			DrawCrosshair(void) = 0;
	virtual bool			ShouldDrawCrosshair(void) = 0;
	virtual bool			IsCarriedByLocalPlayer(void) = 0;
	virtual bool			ShouldDrawUsingViewModel(void) = 0;
	virtual bool			IsActiveByLocalPlayer(void) = 0;
	virtual bool			ShouldDrawPickup(void) = 0;
	virtual void			HandleInput(void) = 0;
	virtual void			OverrideMouseInput(float *x, float *y) = 0;
	virtual int				KeyInput(int down, ButtonCode_t keynum, const char *pszCurrentBinding) = 0;
	virtual bool			AddLookShift(void) = 0;
	virtual void			GetViewmodelBoneControllers(C_BaseViewModel *pViewModel, float controllers[MAXSTUDIOBONECTRLS]) = 0;
	virtual void			NotifyShouldTransmit(ShouldTransmitState_t state) = 0;
	virtual int				GetWorldModelIndex(void) = 0;
	virtual void			GetWeaponCrosshairScale(float &flScale) = 0;
	virtual bool			ViewModel_IsTransparent(void) = 0;
	virtual bool			ViewModel_IsUsingFBTexture(void) = 0;
	virtual bool			IsOverridingViewmodel(void) = 0;
	virtual int				DrawOverriddenViewmodel(C_BaseViewModel *pViewmodel, int flags) = 0;
	virtual void			ThirdPersonSwitch(bool) = 0;
	virtual bool			CanLower(void) = 0;
	virtual bool			Ready(void) = 0;
	virtual bool			Lower(void) = 0;
	virtual void			HideThink(void) = 0;
	virtual bool			CanReload(void) = 0;
	virtual void			NetworkStateChanged_m_nNextThinkTick(void) = 0;
	virtual void			NetworkStateChanged_m_nNextThinkTick(void *) = 0;
	virtual int				GetPlayerDamage() = 0;
	virtual void			EquipAmmo(BaseEntity*) = 0;
	virtual bool			ShouldDropOnDie() = 0;
	virtual bool			ShouldDrawViewModel() = 0;
	virtual float			GetLastShootTime() = 0;
	virtual void			UpdateLastShootTime(float) = 0;
	virtual void			GetTracerOrigin(Vector&) = 0;
	virtual void			GetFOV(float) = 0;
	virtual void			OverrideMouseInput() = 0;
	virtual void			DrawWeaponSelection(int, int, int, int, int) = 0;
	virtual bool			DrawHUD() = 0;
	virtual bool			ShouldDrawAmmo() = 0;
	virtual float			GetViewModelFOV(float) = 0;
	virtual float			GetSwayScale() = 0;
	virtual float			GetWeaponBobScale() = 0;
	virtual bool			ShouldFlipViewModel(UINT, bool) = 0;
	virtual bool			ShouldDrawAccurateCrosshair() = 0;
	virtual void			GModNPCAttackHack() = 0;










	Vector GetBulletSpread()
	{
		if (this == nullptr)
			return Vector(0, 0, 0);

		if (this->UsesLua())
		{
			float LUASpreadCone = this->LUASpread();
			if (!strcmp(this->GetWeaponBase(), "weapon_tttbase"))
				LUASpreadCone = this->TTTSpread();

			if(LUASpreadCone != -1.0f)
				return Vector(LUASpreadCone, LUASpreadCone, LUASpreadCone);

			LUASpreadCone = this->LUASpread2();
			if(LUASpreadCone != -1.0f)
				return Vector(LUASpreadCone, LUASpreadCone, LUASpreadCone);
		}

		return this->orgGetBulletSpread();
	}
	float m_flNextPrimaryAttack()
	{
		if (this == nullptr)
			return 0.0f;
		return *reinterpret_cast<float*>((DWORD)this + 0x17CC);
	}
	bool CanShoot()
	{
		if (!this)
			return false;

		if ((this->m_flNextPrimaryAttack() <= globals()->curtime) && (this->HasPrimaryAmmo()))
			return true;

		return false;
	}
public:
	/*
		Make a macro for this shit lol
	*/
	const char* GetWeaponBase()
	{
		auto Lua = LuaShared()->GetLuaInterface(GarrysMod::Lua::Client);
		this->PushEntity();
		Lua->GetField(-1, "Base");
		if (!Lua->IsType(-1, GarrysMod::Lua::Type::STRING))
		{
			Lua->Pop(2);
			return "";
		}
		const char* out = Lua->GetString(-1);
		Lua->Pop(2);
		return out;
	}
	float TTTSpread()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = LuaShared()->GetLuaInterface(GarrysMod::Lua::Client);
		this->PushEntity();
		Lua->GetField(-1, "Primary");
		if (!Lua->IsType(-1, GarrysMod::Lua::Type::TABLE))
		{
			Lua->Pop(2);
			return -1.0f;
		}
		Lua->GetField(-1, "Cone");
		if (!Lua->IsType(-1, GarrysMod::Lua::Type::NUMBER))
		{
			Lua->Pop(3);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(3);
		return out;
	}
	float LUASpread()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = LuaShared()->GetLuaInterface(GarrysMod::Lua::Client);
		this->PushEntity();
		Lua->GetField(-1, "Primary");
		if (!Lua->IsType(-1, GarrysMod::Lua::Type::TABLE))
		{
			Lua->Pop(2);
			return -1.0f;
		}
		Lua->GetField(-1, "Spread");
		if (!Lua->IsType(-1, GarrysMod::Lua::Type::NUMBER))
		{
			Lua->Pop(3);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(3);
		return out;
	}
	float LUASpread2()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = LuaShared()->GetLuaInterface(GarrysMod::Lua::Client);
		this->PushEntity();
		Lua->GetField(-1, "Spread");
		if (!Lua->IsType(-1, GarrysMod::Lua::Type::NUMBER))
		{
			Lua->Pop(2);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(2);
		return out;
	}
};
