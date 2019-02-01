#define NETMSG_TYPE_BITS	5	// must be 2^NETMSG_TYPE_BITS > SVC_LASTMSG
#include "include.h"

HANDLE console;

void SetupOffsets()
{
	CNetworkedVariableManager* NVMGR = new CNetworkedVariableManager();
	// DT_BasePlayer
	offsets::DT_BasePlayer::m_iFOV						= NVMGR->GetOffset("DT_BasePlayer","m_iFOV");
	offsets::DT_BasePlayer::m_iFOVStart					= NVMGR->GetOffset("DT_BasePlayer", "m_iFOVStart");
	offsets::DT_BasePlayer::m_flFOVTime					= NVMGR->GetOffset("DT_BasePlayer", "m_flFOVTime");
	offsets::DT_BasePlayer::m_iDefaultFOV				= NVMGR->GetOffset("DT_BasePlayer", "m_iDefaultFOV");
	offsets::DT_BasePlayer::m_hZoomOwner				= NVMGR->GetOffset("DT_BasePlayer", "m_hZoomOwner");
	offsets::DT_BasePlayer::m_hVehicle					= NVMGR->GetOffset("DT_BasePlayer", "m_hVehicle");
	offsets::DT_BasePlayer::m_hUseEntity				= NVMGR->GetOffset("DT_BasePlayer", "m_hUseEntity");
	offsets::DT_BasePlayer::m_iHealth					= NVMGR->GetOffset("DT_BasePlayer", "m_iHealth");
	offsets::DT_BasePlayer::m_lifeState					= NVMGR->GetOffset("DT_BasePlayer", "m_lifeState");
	offsets::DT_BasePlayer::m_iBonusProgress			= NVMGR->GetOffset("DT_BasePlayer", "m_iBonusProgress");
	offsets::DT_BasePlayer::m_iBonusChallenge			= NVMGR->GetOffset("DT_BasePlayer", "m_iBonusChallenge");
	offsets::DT_BasePlayer::m_flMaxspeed				= NVMGR->GetOffset("DT_BasePlayer", "m_flMaxspeed");
	offsets::DT_BasePlayer::m_fFlags					= NVMGR->GetOffset("DT_BasePlayer", "m_fFlags");
	offsets::DT_BasePlayer::m_iObserverMode				= NVMGR->GetOffset("DT_BasePlayer", "m_iObserverMode");
	offsets::DT_BasePlayer::m_hObserverTarget			= NVMGR->GetOffset("DT_BasePlayer", "m_hObserverTarget");
	offsets::DT_BasePlayer::m_szLastPlaceName			= NVMGR->GetOffset("DT_BasePlayer", "m_szLastPlaceName");
	offsets::DT_BasePlayer::m_bUseWeaponsInVehicle		= NVMGR->GetOffset("DT_BasePlayer", "m_bUseWeaponsInVehicle");


	// DT_BaseEntity
	offsets::DT_BaseEntity::m_flSimulationTime			= NVMGR->GetOffset("DT_BaseEntity", "m_flSimulationTime");
	offsets::DT_BaseEntity::m_ubInterpolationFrame		= NVMGR->GetOffset("DT_BaseEntity", "m_ubInterpolationFrame");
	offsets::DT_BaseEntity::m_vecOrigin					= NVMGR->GetOffset("DT_BaseEntity", "m_vecOrigin");
	offsets::DT_BaseEntity::m_angRotation				= NVMGR->GetOffset("DT_BaseEntity", "m_angRotation");
	offsets::DT_BaseEntity::m_nModelIndex				= NVMGR->GetOffset("DT_BaseEntity", "m_nModelIndex");
	offsets::DT_BaseEntity::m_fEffects					= NVMGR->GetOffset("DT_BaseEntity", "m_fEffects");
	offsets::DT_BaseEntity::m_nRenderMode				= NVMGR->GetOffset("DT_BaseEntity", "m_nRenderMode");
	offsets::DT_BaseEntity::m_nRenderFX					= NVMGR->GetOffset("DT_BaseEntity", "m_nRenderFX");
	offsets::DT_BaseEntity::m_clrRender					= NVMGR->GetOffset("DT_BaseEntity", "m_clrRender");
	offsets::DT_BaseEntity::m_iTeamNum					= NVMGR->GetOffset("DT_BaseEntity", "m_iTeamNum");
	offsets::DT_BaseEntity::m_CollisionGroup			= NVMGR->GetOffset("DT_BaseEntity", "m_CollisionGroup");
	offsets::DT_BaseEntity::m_flElasticity				= NVMGR->GetOffset("DT_BaseEntity", "m_flElasticity");
	offsets::DT_BaseEntity::m_flShadowCastDistance		= NVMGR->GetOffset("DT_BaseEntity", "m_flShadowCastDistance");
	offsets::DT_BaseEntity::m_hOwnerEntity				= NVMGR->GetOffset("DT_BaseEntity", "m_hOwnerEntity");
	offsets::DT_BaseEntity::m_hEffectEntity				= NVMGR->GetOffset("DT_BaseEntity", "m_hEffectEntity");
	offsets::DT_BaseEntity::moveparent					= NVMGR->GetOffset("DT_BaseEntity", "moveparent");
	offsets::DT_BaseEntity::m_iParentAttachment			= NVMGR->GetOffset("DT_BaseEntity", "m_iParentAttachment");
	offsets::DT_BaseEntity::m_Collision					= NVMGR->GetOffset("DT_BaseEntity", "m_Collision");
	offsets::DT_BaseEntity::m_iTextureFrameIndex		= NVMGR->GetOffset("DT_BaseEntity", "m_iTextureFrameIndex");
	offsets::DT_BaseEntity::m_bSimulatedEveryTick		= NVMGR->GetOffset("DT_BaseEntity", "m_bSimulatedEveryTick");
	offsets::DT_BaseEntity::m_bAnimatedEveryTick		= NVMGR->GetOffset("DT_BaseEntity", "m_bAnimatedEveryTick");
	offsets::DT_BaseEntity::m_bAlternateSorting			= NVMGR->GetOffset("DT_BaseEntity", "m_bAlternateSorting");
	offsets::DT_BaseEntity::m_takedamage				= NVMGR->GetOffset("DT_BaseEntity", "m_takedamage");
	offsets::DT_BaseEntity::m_RealClassName				= NVMGR->GetOffset("DT_BaseEntity", "m_RealClassName");
	offsets::DT_BaseEntity::m_OverrideMaterial			= NVMGR->GetOffset("DT_BaseEntity", "m_OverrideMaterial");
	offsets::DT_BaseEntity::m_iHealth					= NVMGR->GetOffset("DT_BaseEntity", "m_iHealth");
	offsets::DT_BaseEntity::m_iMaxHealth				= NVMGR->GetOffset("DT_BaseEntity", "m_iMaxHealth");
	offsets::DT_BaseEntity::m_spawnflags				= NVMGR->GetOffset("DT_BaseEntity", "m_spawnflags");
	offsets::DT_BaseEntity::m_iGModFlags				= NVMGR->GetOffset("DT_BaseEntity", "m_iGModFlags");
	offsets::DT_BaseEntity::m_bOnFire					= NVMGR->GetOffset("DT_BaseEntity", "m_bOnFire");
	offsets::DT_BaseEntity::m_CreationTime				= NVMGR->GetOffset("DT_BaseEntity", "m_CreationTime");
	offsets::DT_BaseEntity::m_vecVelocity0				= NVMGR->GetOffset("DT_BaseEntity", "m_vecVelocity[0]");
	offsets::DT_BaseEntity::m_vecVelocity1				= NVMGR->GetOffset("DT_BaseEntity", "m_vecVelocity[1]");
	offsets::DT_BaseEntity::m_vecVelocity2				= NVMGR->GetOffset("DT_BaseEntity", "m_vecVelocity[2]");
	offsets::DT_BaseEntity::m_GMOD_DataTable			= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_DataTable");
	offsets::DT_BaseEntity::m_GMOD_bool					= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_bool");
	offsets::DT_BaseEntity::m_GMOD_float				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_float");
	offsets::DT_BaseEntity::m_GMOD_int					= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_int");
	offsets::DT_BaseEntity::m_GMOD_Vector				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_Vector");
	offsets::DT_BaseEntity::m_GMOD_QAngle				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_QAngle");
	offsets::DT_BaseEntity::m_GMOD_EHANDLE				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_EHANDLE");
	offsets::DT_BaseEntity::m_GMOD_String0				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_String0");
	offsets::DT_BaseEntity::m_GMOD_String1				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_String1");
	offsets::DT_BaseEntity::m_GMOD_String2				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_String2");
	offsets::DT_BaseEntity::m_GMOD_String3				= NVMGR->GetOffset("DT_BaseEntity", "m_GMOD_String3");


	//DT_BaseCombatCharacter
	offsets::DT_BaseCombatCharacter::m_hActiveWeapon	= NVMGR->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
	offsets::DT_BaseCombatCharacter::m_hMyWeapons		= NVMGR->GetOffset("DT_BaseCombatCharacter", "m_hMyWeapons");


	//DT_BaseAnimating
	offsets::DT_BaseAnimating::m_nSequence = NVMGR->GetOffset("DT_BaseAnimating", "m_nSequence");
	offsets::DT_BaseAnimating::m_nForceBone = NVMGR->GetOffset("DT_BaseAnimating", "m_nForceBone");
	offsets::DT_BaseAnimating::m_vecForce = NVMGR->GetOffset("DT_BaseAnimating", "m_vecForce");
	offsets::DT_BaseAnimating::m_nSkin = NVMGR->GetOffset("DT_BaseAnimating", "m_nSkin");
	offsets::DT_BaseAnimating::m_nBody = NVMGR->GetOffset("DT_BaseAnimating", "m_nBody");
	offsets::DT_BaseAnimating::m_nHitboxSet = NVMGR->GetOffset("DT_BaseAnimating", "m_nHitboxSet");
	offsets::DT_BaseAnimating::m_flModelScale = NVMGR->GetOffset("DT_BaseAnimating", "m_flModelScale");
	offsets::DT_BaseAnimating::m_flModelWidthScale = NVMGR->GetOffset("DT_BaseAnimating", "m_flModelWidthScale");
	offsets::DT_BaseAnimating::m_flPoseParameter = NVMGR->GetOffset("DT_BaseAnimating", "m_flPoseParameter");
	offsets::DT_BaseAnimating::m_flPlaybackRate = NVMGR->GetOffset("DT_BaseAnimating", "m_flPlaybackRate");
	offsets::DT_BaseAnimating::m_flEncodedController = NVMGR->GetOffset("DT_BaseAnimating", "m_flEncodedController");
	offsets::DT_BaseAnimating::m_bClientSideAnimation = NVMGR->GetOffset("DT_BaseAnimating", "m_bClientSideAnimation");
	offsets::DT_BaseAnimating::m_bClientSideFrameReset = NVMGR->GetOffset("DT_BaseAnimating", "m_bClientSideFrameReset");
	offsets::DT_BaseAnimating::m_nNewSequenceParity = NVMGR->GetOffset("DT_BaseAnimating", "m_nNewSequenceParity");
	offsets::DT_BaseAnimating::m_nResetEventsParity = NVMGR->GetOffset("DT_BaseAnimating", "m_nResetEventsParity");
	offsets::DT_BaseAnimating::m_nMuzzleFlashParity = NVMGR->GetOffset("DT_BaseAnimating", "m_nMuzzleFlashParity");
	offsets::DT_BaseAnimating::m_hLightingOrigin = NVMGR->GetOffset("DT_BaseAnimating", "m_hLightingOrigin");
	offsets::DT_BaseAnimating::m_hLightingOriginRelative = NVMGR->GetOffset("DT_BaseAnimating", "m_hLightingOriginRelative");
	offsets::DT_BaseAnimating::m_fadeMinDist = NVMGR->GetOffset("DT_BaseAnimating", "m_fadeMinDist");
	offsets::DT_BaseAnimating::m_flFadeScale = NVMGR->GetOffset("DT_BaseAnimating", "m_flFadeScale");
	offsets::DT_BaseAnimating::m_pBoneManipulator = NVMGR->GetOffset("DT_BaseAnimating", "m_pBoneManipulator");
	offsets::DT_BaseAnimating::m_pFlexManipulator = NVMGR->GetOffset("DT_BaseAnimating", "m_pFlexManipulator");
	offsets::DT_BaseAnimating::m_OverrideViewTarget = NVMGR->GetOffset("DT_BaseAnimating", "m_OverrideViewTarget");

	//DT_GMOD_Player
	offsets::DT_GMOD_Player::m_iGModPlayerFlags = NVMGR->GetOffset("DT_GMOD_Player", "m_iGModPlayerFlags");
	offsets::DT_GMOD_Player::m_HoveredWidget = NVMGR->GetOffset("DT_GMOD_Player", "m_HoveredWidget");
	offsets::DT_GMOD_Player::m_PressedWidget = NVMGR->GetOffset("DT_GMOD_Player", "m_PressedWidget");
	offsets::DT_GMOD_Player::m_Driving = NVMGR->GetOffset("DT_GMOD_Player", "m_Driving");
	offsets::DT_GMOD_Player::m_DrivingMode = NVMGR->GetOffset("DT_GMOD_Player", "m_DrivingMode");
	offsets::DT_GMOD_Player::m_PlayerClass = NVMGR->GetOffset("DT_GMOD_Player", "m_PlayerClass");
	offsets::DT_GMOD_Player::m_bCanZoom = NVMGR->GetOffset("DT_GMOD_Player", "m_bCanZoom");
	offsets::DT_GMOD_Player::m_bCanWalk = NVMGR->GetOffset("DT_GMOD_Player", "m_bCanWalk");
	offsets::DT_GMOD_Player::m_bIsTyping = NVMGR->GetOffset("DT_GMOD_Player", "m_bIsTyping");
	offsets::DT_GMOD_Player::m_StepSize = NVMGR->GetOffset("DT_GMOD_Player", "m_StepSize");
	offsets::DT_GMOD_Player::m_JumpPower = NVMGR->GetOffset("DT_GMOD_Player", "m_JumpPower");
	offsets::DT_GMOD_Player::m_ViewOffset = NVMGR->GetOffset("DT_GMOD_Player", "m_ViewOffset");
	offsets::DT_GMOD_Player::m_ViewOffsetDucked = NVMGR->GetOffset("DT_GMOD_Player", "m_ViewOffsetDucked");
	offsets::DT_GMOD_Player::m_fGestureEndTime = NVMGR->GetOffset("DT_GMOD_Player", "m_fGestureEndTime");
	offsets::DT_GMOD_Player::m_PlayerColor = NVMGR->GetOffset("DT_GMOD_Player", "m_PlayerColor");
	offsets::DT_GMOD_Player::m_WeaponColor = NVMGR->GetOffset("DT_GMOD_Player", "m_WeaponColor");
	offsets::DT_GMOD_Player::m_Hands = NVMGR->GetOffset("DT_GMOD_Player", "m_Hands");
	offsets::DT_GMOD_Player::m_nWaterLevel = NVMGR->GetOffset("DT_GMOD_Player", "m_nWaterLevel");

	// DT_HL2MP_Player
	offsets::DT_HL2MP_Player::m_hRagdoll = NVMGR->GetOffset("DT_HL2MP_Player", "m_hRagdoll");
	offsets::DT_HL2MP_Player::m_iSpawnInterpCounter = NVMGR->GetOffset("DT_HL2MP_Player", "m_iSpawnInterpCounter");
	offsets::DT_HL2MP_Player::m_iPlayerSoundType = NVMGR->GetOffset("DT_HL2MP_Player", "m_iPlayerSoundType");
	offsets::DT_HL2MP_Player::m_fIsWalking = NVMGR->GetOffset("DT_HL2MP_Player", "m_fIsWalking");
} 


void Main()
{
	CreateConsole("Console");
	// setup interfaces.
	Interfaces::_SetupInterfaces();
	Interfaces::_I::MatRenderContext = Interfaces::_I::materialsystem->GetRenderContext();
	Interfaces::_printInterfaceAddresses();

	//setup offsets
	SetupOffsets();

	// setup some default hack variables  
	HackVars::Fonts::DefaultFont = surface()->ISCreateFont();
	surface()->SetFontGlyphSet(HackVars::Fonts::DefaultFont, "Arial", 15, 500, 0, 0, FONTFLAG_ANTIALIAS);
	HackVars::convars::FOV = CVar()->FindVar("fov_desired");
	HackVars::Visuals::RenderView::FOV = HackVars::convars::FOV->GetInt() + 20;
	HackVars::Visuals::RenderView::ViewModelFOV = HackVars::convars::FOV->GetInt() + 30;


	// hook stuff
	Hook::SetupHooks();
	Hook::HookFunctions();

	Interfaces::_I::HitMarkerEvent = new Event_HitMarker();
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, nullptr);
	//	Main();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

