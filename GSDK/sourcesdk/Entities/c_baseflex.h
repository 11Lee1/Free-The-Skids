class CSceneEventInfo;
class CChoreoScene;
class CChoreoEvent;
class CChoreoActor;
class IHasLocalToGlobalFlexSettings
{
public:
	//virtual void		EnsureTranslations(const flexsettinghdr_t *pSettinghdr) = 0;
};

class C_BaseFlex : public C_BaseAnimatingOverlay, public IHasLocalToGlobalFlexSettings
{
public: // 269 - 10
	virtual void	InitPhonemeMappings();
	virtual	bool	SetupGlobalWeights(const matrix3x4_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights);
	virtual	void	SetupLocalWeights(const matrix3x4_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights);
	virtual Vector	SetViewTarget(CStudioHdr *pStudioHdr);
	virtual bool	StartSceneEvent(CSceneEventInfo *info, CChoreoScene *scene, CChoreoEvent *event, CChoreoActor *actor, BaseEntity *pTarget);
	virtual void	ProcessSceneEvents(bool bFlexEvents);
	virtual	bool	ProcessSceneEvent(bool bFlexEvents, CSceneEventInfo *info, CChoreoScene *scene, CChoreoEvent *event);
	virtual bool	ProcessSequenceSceneEvent(CSceneEventInfo *info, CChoreoScene *scene, CChoreoEvent *event);
	virtual	bool	ClearSceneEvent(CSceneEventInfo *info, bool fastKill, bool canceled);
	virtual bool	CheckSceneEventCompletion(CSceneEventInfo *info, float currenttime, CChoreoScene *scene, CChoreoEvent *event);
};