class C_BaseCombatWeapon;
class C_WeaponCombatShield;
#define BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE 0.9f
class C_BaseCombatCharacter : public C_BaseFlex
{
public: // 278 - 9
	virtual bool				IsLookingTowards(const BaseEntity *target, float cosTolerance = BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE) const; // return true if our view direction is pointing at the given target, within the cosine of the angular tolerance. LINE OF SIGHT IS NOT CHECKED.
	virtual bool				IsLookingTowards(const Vector &target, float cosTolerance = BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE) const; // return true if our view direction is pointing at the given target, within the cosine of the angular tolerance. LINE OF SIGHT IS NOT CHECKED.
	virtual bool				IsInFieldOfView(BaseEntity *entity) const; // Calls IsLookingAt with the current field of view.  
	virtual bool				IsInFieldOfView(const Vector &pos) const;
	enum LineOfSightCheckType
	{
		IGNORE_NOTHING,
		IGNORE_ACTORS
	};
	virtual bool				IsLineOfSightClear(BaseEntity *entity, LineOfSightCheckType checkType = IGNORE_NOTHING) const;// strictly LOS check with no other considerations
	virtual bool				IsLineOfSightClear(const Vector &pos, LineOfSightCheckType checkType = IGNORE_NOTHING, BaseEntity *entityToIgnore = NULL) const;
	virtual	bool				Weapon_Switch(C_BaseCombatWeapon *pWeapon, int viewmodelindex = 0);
	virtual bool				Weapon_CanSwitchTo(C_BaseCombatWeapon *pWeapon);
	virtual CBaseCombatWeapon*	GetActiveWeapon(void);
};