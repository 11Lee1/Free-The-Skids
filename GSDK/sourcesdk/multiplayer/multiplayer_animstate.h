struct MultiPlayerMovementData_t
{
	// Set speeds to -1 if they are not used.
	float		m_flWalkSpeed;
	float		m_flRunSpeed;
	float		m_flSprintSpeed;
	float		m_flBodyYawRate;
};
class CMultiPlayerAnimState
{
public:
	virtual ~CMultiPlayerAnimState();
	virtual void ClearAnimationState() = 0;
	virtual void DoAnimationEvent(PlayerAnimEvent_t event, int nData = 0) = 0;
	virtual Activity CalcMainActivity() = 0;
	virtual void Update(float eyeYaw, float eyePitch) = 0;
	virtual void Release(void) = 0;
	virtual Activity TranslateActivity(Activity actDesired) = 0;
	virtual void SetRunSpeed(float flSpeed) = 0;
	virtual void SetWalkSpeed(float flSpeed) = 0;
	virtual void SetSprintSpeed(float flSpeed) = 0;
	// Debug
	virtual void ShowDebugInfo(void) = 0;
	virtual void DebugShowAnimState(int iStartLine) = 0;

	virtual void Init(BaseEntity *pPlayer, MultiPlayerMovementData_t &movementData) = 0;
	virtual int	SelectWeightedSequence(Activity activity) = 0;
	virtual void RestartMainSequence() = 0;

	virtual void GetOuterAbsVelocity(Vector& vel) = 0;

	virtual bool HandleJumping(Activity &idealActivity) = 0;
	virtual bool HandleDucking(Activity &idealActivity) = 0;
	virtual bool HandleMoving(Activity &idealActivity) = 0;
	virtual bool HandleSwimming(Activity &idealActivity) = 0;
	virtual bool HandleDying(Activity &idealActivity) = 0;

	virtual void RestartGesture(int iGestureSlot, Activity iGestureActivity, bool bAutoKill = true) = 0;
	virtual void stub_01() = 0;
	virtual void PlayFlinchGesture(Activity iActivity) = 0;
	virtual float CalcMovementSpeed(bool* bIsMoving) = 0;
	virtual float CalcMovementPlaybackRate(bool *bIsMoving) = 0;
	virtual void ComputePoseParam_MoveYaw(CStudioHdr *pStudioHdr) = 0;
	virtual void ComputePoseParam_AimPitch(CStudioHdr *pStudioHdr) = 0;
	virtual void ComputePoseParam_AimYaw(CStudioHdr *pStudioHdr) = 0;
	virtual void EstimateYaw(void) = 0;
	virtual float GetCurrentMaxGroundSpeed() = 0;
	virtual void ComputeSequences(CStudioHdr *pStudioHdr) = 0;
	virtual bool ShouldUpdateAnimState() = 0;
};