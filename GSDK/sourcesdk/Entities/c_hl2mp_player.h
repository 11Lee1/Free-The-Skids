class C_HL2MP_Player : public C_BaseHLPlayer
{
public: // 381 - 9
	virtual bool	CanSprint(void);
	virtual void	StartSprinting(void);
	virtual void	StopSprinting(void);
	virtual void	HandleSpeedChanges(void);
	virtual void	UpdateLookAt(void);
	virtual int		GetIDTarget();
	virtual void	UpdateIDTarget(void);
	virtual void	PrecacheFootStepSounds(void);
	virtual const char	*GetPlayerModelSoundPrefix(void);
};