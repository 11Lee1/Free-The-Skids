class BaseEntity;
class CAnimationLayer;
struct GestureSlot_t
{
	int					m_iGestureSlot;
	Activity			m_iActivity;
	bool				m_bAutoKill;
	bool				m_bActive;
	CAnimationLayer		*m_pAnimLayer;
};
struct MultiPlayerPoseData_t
{
	int		m_iMoveX;
	int		m_iMoveY;
	int		m_iAimYaw;
	int		m_iAimPitch;
	int		m_iBodyHeight;
	int		m_iMoveYaw;
	int		m_iMoveScale;
	float	m_flEstimateYaw;
	float	m_flLastAimTurnTime;
	void Init()
	{
		m_iMoveX = 0;
		m_iMoveY = 0;
		m_iAimYaw = 0;
		m_iAimPitch = 0;
		m_iBodyHeight = 0;
		m_iMoveYaw = 0;
		m_iMoveScale = 0;
		m_flEstimateYaw = 0.0f;
		m_flLastAimTurnTime = 0.0f;
	}
};
struct DebugPlayerAnimData_t
{
	float		m_flSpeed;
	float		m_flAimPitch;
	float		m_flAimYaw;
	float		m_flBodyHeight;
	Vector2D	m_vecMoveYaw;

	void Init()
	{
		m_flSpeed = 0.0f;
		m_flAimPitch = 0.0f;
		m_flAimYaw = 0.0f;
		m_flBodyHeight = 0.0f;
		m_vecMoveYaw.Init();
	}
};
class CHL2MPPlayerAnimState : public CMultiPlayerAnimState
{
public:
	// stuff thats padded is useless imo (jk idk i'm just a very lazy man lol)
	bool						m_bForceAimYaw;
	CUtlVector<GestureSlot_t>	m_aGeustureSlots;
	BaseEntity*					m_pPlayer;
	QAngle						m_angRender;
	bool						m_bPoseParameterInit;
	MultiPlayerPoseData_t		m_PoseParameterData;
	DebugPlayerAnimData_t		m_DebugAnimData;
	bool						m_bCurrentFeetYawInitialized;
	float						m_flLastAnimationStateClearTime;
	float						m_flEyeYaw;
	float						m_flEyePitch;
	float						m_flGoalFeetYaw;
	float						m_flCurrentFeetYaw;
	float						m_flLastAimTurnTime;
	MultiPlayerMovementData_t	m_MovementData;
	bool						m_bJumping;
	float						m_flJumpStartTime;
	bool						m_bFirstJumpFrame;
	bool						m_bInSwim;
	bool						m_bFirstSwimFrame;
	bool						m_bDying;
	bool						m_bFirstDyingFrame;
	// Last activity we've used on the lower body. Used to determine if animations should restart.
	Activity					m_eCurrentMainSequenceActivity;
	int							m_nSpecificMainSequence;
	void*						m_hActiveWeapon;
	float						m_flLastGroundSpeedUpdateTime;
	BYTE PAD1[48];
	float						m_flMaxGroundSpeed;
	int							m_nMovementSequence;
};
