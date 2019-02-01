class C_GMOD_Player : public C_HL2MP_Player
{
public: // 392 - 11
	virtual bool		IsSprinting();
	virtual void		AchievementThink();
	virtual char const* GetNetworkIDString();
	virtual char const*	GetUniqueID();
	virtual double		GetSnapAngles();
	virtual Vector		SnapToGrid(Vector&);
	virtual int			GetViewEntity();
	virtual Vector		GetPlayerColor();
	virtual Vector		GetWeaponColor();
	virtual void		SetPlayerColor(Vector color);
	virtual void		SetWeaponColor(Vector color);
};