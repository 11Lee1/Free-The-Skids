class CSteamID;
class IRagdoll;
class CHintSystem;

class C_BasePlayer : public C_BaseCombatCharacter
{
public: // 372 - 94
	virtual void		SharedSpawn() = 0; // Shared between client and server.
	virtual bool		GetSteamID(CSteamID *pID) = 0;
	virtual float		GetPlayerMaxSpeed() = 0;
	virtual void		CalcView(Vector &eyeOrigin, QAngle &eyeAngles, float &zNear, float &zFar, float &fov) = 0;
	virtual void		CalcViewModelView(const Vector& eyeOrigin, const QAngle& eyeAngles) = 0;
	virtual float		CalcRoll(const QAngle& angles, const Vector& velocity, float rollangle, float rollspeed) = 0;
	virtual void		SetPlayerUnderwater(bool state) = 0;
	virtual Vector		Weapon_ShootPosition() = 0;
	virtual void		Weapon_DropPrimary(void) = 0;
	virtual Vector		GetAutoaimVector(float flScale) = 0;
	virtual bool		CreateMove(float flInputSampleTime, CUserCmd *pCmd) = 0;
	virtual void		AvoidPhysicsProps(CUserCmd *pCmd) = 0;
	virtual void		PlayerUse(void) = 0;
	virtual bool		IsUseableEntity(BaseEntity *pEntity, unsigned int requiredCaps) = 0;
	virtual int			GetObserverMode() const = 0;
	virtual BaseEntity* GetObserverTarget() const = 0;
	virtual IRagdoll* GetRepresentativeRagdoll() const = 0;
	virtual void		TeamChange(int iNewTeam) = 0;
	virtual void		UpdateFlashlight(void) = 0;
	virtual bool		IsAllowedToSwitchWeapons(void) = 0;
	virtual CBaseCombatWeapon *GetActiveWeaponForSelection(void) = 0;
	virtual C_BaseAnimating* GetRenderedWeaponModel() = 0;
	virtual bool		IsOverridingViewmodel(void) = 0;
	virtual int			DrawOverriddenViewmodel(C_BaseViewModel *pViewmodel, int flags) = 0;
	virtual float		GetDefaultAnimSpeed(void) = 0;
	virtual void		ThirdPersonSwitch(bool bThirdperson) = 0;
	virtual bool		CanSetSoundMixer(void) = 0;
	virtual int			GetVisionFilterFlags(bool bWeaponsCheck = false) = 0;
	virtual void		CalculateVisionUsingCurrentFlags(void) = 0;
	virtual bool		ViewModel_IsTransparent(void) = 0;
	virtual bool		ViewModel_IsUsingFBTexture(void) = 0;
	virtual void		PreThink(void) = 0;
	virtual void		PostThink(void) = 0;
	virtual void		ItemPreFrame(void) = 0;
	virtual void		ItemPostFrame(void) = 0;
	virtual void		AbortReload(void) = 0;
	virtual void		SelectLastItem(void) = 0;
	virtual void		Weapon_SetLast(C_BaseCombatWeapon *pWeapon) = 0;
	virtual bool		Weapon_ShouldSetLast(C_BaseCombatWeapon *pOldWeapon, C_BaseCombatWeapon *pNewWeapon) = 0;
	virtual bool		Weapon_ShouldSelectItem(C_BaseCombatWeapon *pWeapon) = 0;
	virtual CBaseCombatWeapon*		GetLastWeapon(void) = 0;
	virtual void		SelectItem(const char *pstr, int iSubType = 0) = 0;
	virtual void		UpdateClientData(void) = 0;
	virtual float		GetFOV(void) = 0;
	virtual bool		IsZoomed(void) = 0;
	virtual void		ViewPunch(const QAngle &angleOffset) = 0;
	virtual void		UpdateButtonState(int nUserCmdButtonMask) = 0;
	virtual void		OverrideView(CViewSetup *pSetup) = 0;
	virtual const Vector	GetPlayerMins(void) const = 0; // uses local player
	virtual const Vector	GetPlayerMaxs(void) const = 0; // uses local player
	virtual void		SetVehicleRole(int nRole) = 0;
	virtual void		SetAnimation(PLAYER_ANIM playerAnim) = 0;
	virtual float		GetMinFOV() const = 0;
	virtual void		PlayPlayerJingle() = 0;
	virtual void		UpdateStepSound(surfacedata_t *psurface, const Vector &vecOrigin, const Vector &vecVelocity) = 0;
	virtual void		PlayStepSound(Vector &vecOrigin, surfacedata_t *psurface, float fvol, bool force) = 0;
	virtual surfacedata_t* GetFootstepSurface(const Vector &origin, const char *surfaceName) = 0;
	virtual void		GetStepSoundVelocities(float *velwalk, float *velrun) = 0;
	virtual void		SetStepSoundTime(stepsoundtimes_t iStepSoundTime, bool bWalking) = 0;
	virtual const char*	GetOverrideStepSound(const char *pszBaseStepSoundName) = 0;
	virtual void		OnEmitFootstepSound(const CSoundParameters& params, const Vector& vecOrigin, float fVolume) = 0;
	virtual void		ExitLadder() = 0;
	virtual CHintSystem*Hints(void) = 0;
	virtual	IMaterial*	GetHeadLabelMaterial(void) = 0;
	virtual void		OnAchievementAchieved(int iAchievement) = 0;
	virtual bool		CanUseFirstPersonCommand(void) = 0;
	virtual void		CalcObserverView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov) = 0;
	virtual Vector		GetChaseCamViewOffset(BaseEntity *target) = 0;
	virtual void		CalcInEyeCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov) = 0;
	virtual float		GetDeathCamInterpolationTime() = 0;
	virtual void		CalcDeathCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov) = 0;
	virtual void		CalcFreezeCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov) = 0;
	virtual void		SetLocalViewAngles(const QAngle &viewAngles) = 0;
	virtual void		SetViewAngles(const QAngle& ang) = 0;
	virtual bool		IsDucked(void) = 0;
	virtual bool		IsDucking(void) = 0;
	virtual float		GetFallVelocity(void) = 0;
	virtual bool		RestrictPlayerPitch() = 0;
	virtual bool		FlashlightIsOn() = 0;
	virtual Vector		GetPlayerViewOffset(bool) = 0;
	virtual float		GetSprintSpeed() = 0;
	virtual float		GetWalkSpeed() = 0;
	virtual float		GetCrouchedWalkSpeed() = 0;
	virtual float		GetDuckSpeed() = 0;
	virtual float		GetUnDuckSpeed() = 0;
	virtual void		SetSprintSpeed(float speed) = 0;
	virtual void		SetWalkSpeed(float speed) = 0;
	virtual void		SetCrouchedWalkSpeed(float speed) = 0;
	virtual void		SetDuckSpeed(float speed) = 0;
	virtual void		SetUnDuckSpeed(float speed) = 0;
	virtual bool		CanAttack() = 0;
	virtual int			MouseWheel() = 0;
	virtual void		SetMouseWheel(int) = 0;
	virtual float		GestureEndTime() = 0;
public:

	QAngle& m_vecViewPunch() // deprecated 
	{
		return *(QAngle*)((uintptr_t)this + 0x22C8);
	}
};