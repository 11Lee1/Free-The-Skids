class CBaseHandle;

typedef CBaseHandle EntityHandle_t;

class CMoveData
{
public:
	char pad_0000[4]; //0x0000
	uint32_t m_nPlayerHandle; //0x0004
	int32_t m_nImpulseCommand; //0x0008
	QAngle m_vecViewAngles; //0x000C
	QAngle m_vecAbsViewAngles; //0x0018
	int32_t m_nButtons; //0x0024
	int32_t m_nOldButtons; //0x0028
	float m_flForwardMove; //0x002C
	float m_flSideMove; //0x0030
	float m_flUpMove; //0x0034
	float m_flMaxSpeed; //0x0038
	float m_flClientMaxSpeed; //0x003C
	Vector m_vecVelocity; //0x0040
	QAngle m_vecAngles; //0x004C
	QAngle m_vecOldAngles; //0x0058
	float m_outStepHeight; //0x0064
	Vector m_outWishVel; //0x0068
	Vector m_outJumpVel; //0x0074
	Vector m_vecConstraintCenter; //0x0080
	float m_flConstraintRadius; //0x008C
	float m_flConstraintWidth; //0x0090
	float m_flConstraintSpeedFactor; //0x0094
	Vector m_vecAbsOrigin; //0x0098
};
class IGameMovement
{
public:
	virtual	~IGameMovement(void) = 0;
	virtual void	ProcessMovement(BaseEntity *pPlayer, CMoveData *pMove) = 0;

	virtual void	StartTrackPredictionErrors(BaseEntity *pPlayer) = 0;
	virtual void	FinishTrackPredictionErrors(BaseEntity *pPlayer) = 0;
	virtual void	idk() = 0;
	virtual void	idk2() = 0;
	virtual Vector	GetPlayerMins(bool ducked) = 0;
	virtual Vector	GetPlayerMaxs(bool ducked) = 0;
	virtual Vector	GetPlayerViewOffset(bool ducked) = 0;
	virtual void	idk3() = 0;
	virtual void	idk4() = 0;
	virtual void	TracePlayerBBox(const Vector& start, const Vector& end, unsigned int fMask, int collisionGroup, trace_t& pm) = 0;
	virtual void	TryTouchGround(const Vector& start, const Vector& end, const Vector& mins, const Vector& maxs, unsigned int fMask, int collisionGroup, trace_t& pm) = 0;
	virtual void	idk5() = 0;
	virtual void	PlayerMove(void) = 0;
	virtual float	CalcRoll(const QAngle &angles, const Vector &velocity, float rollangle, float rollspeed) = 0;
	virtual	void	DecayPunchAngle(void) = 0;
	virtual void	CheckWaterJump(void) = 0;
	virtual void	WaterMove(void) = 0;
	virtual void	AirAccelerate(Vector& wishdir, float wishspeed, float accel) = 0;
	virtual void	AirMove(void) = 0;
	virtual float	GetAirSpeedCap(void) = 0;
	virtual bool	CanAccelerate() = 0;
	virtual void	Accelerate(Vector& wishdir, float wishspeed, float accel) = 0;
	virtual void	WalkMove(void) = 0;
	virtual void	FullWalkMove() = 0;
	virtual void	idk6() = 0;
	virtual void	idk7() = 0;
	virtual void	idk8() = 0;
	typedef enum
	{
		GROUND = 0,
		STUCK,
		LADDER
	} IntervalType_t;
	virtual int	GetCheckInterval(IntervalType_t type) = 0;
	// Returns true if he started a jump (ie: should he play the jump animation)?
	virtual bool	CheckJumpButton(void) = 0; // Overridden by each game.
	virtual void	FullTossMove(void) = 0;
	virtual void	FullLadderMove() = 0;
	// The basic solid body movement clip that slides along multiple planes
	virtual int		TryPlayerMove(Vector *pFirstDest = NULL, trace_t *pFirstTrace = NULL) = 0;
	virtual bool	LadderMove(void) = 0;
	virtual bool	OnLadder(trace_t &trace) = 0;
	virtual float	LadderDistance(void) const { return 2.0f; }
	virtual unsigned int LadderMask(void) const { return MASK_PLAYERSOLID; }
	virtual float	ClimbSpeed(void) const { return 200; }
	virtual float	LadderLateralMultiplier(void) const { return 1.0f; }
	virtual int		CheckStuck(void);
	virtual bool	CheckWater(void);
	virtual void	CategorizePosition(void);
	virtual void	CheckParameters(void);
	virtual	void	ReduceTimers(void);
	virtual void	CheckFalling(void);
	virtual void	PlayerRoughLandingEffects(float fvol);
	virtual void	Duck(void);
	virtual void	HandleDuckingSpeedCrop();
	virtual void	FinishUnDuck(void);
	virtual void	FinishDuck(void);
	virtual bool	CanUnduck();
	virtual CBaseHandle TestPlayerPosition(const Vector& pos, int collisionGroup, trace_t& pm);
	virtual void	SetGroundEntity(trace_t *pm);
	virtual void	StepMove(Vector &vecDestination, trace_t &trace);
	virtual void	idk04();
	virtual bool	GameHasLadders() const;

};