// lazy and I didn't need more than this do this yourself if you want.
class SurfInfo;
class IMaterial;
class matrix3x4_t;
class CPhysCollide;
struct client_textmessage_t;
class CSentence;
class CAudioSource;
class ISpatialQuery;
class IAchievementMgr;
class CGamestatsData;
struct AudioState_t
{
	Vector m_Origin;
	QAngle m_Angles;
	bool m_bIsUnderwater;
};
typedef struct vmode_s
{
	int			width;
	int			height;
	int			bpp;
	int			refreshRate;
} vmode_t;
struct OcclusionParams_t
{
	float	m_flMaxOccludeeArea;
	float	m_flMinOccluderArea;
};
enum SkyboxVisibility_t
{
	SKYBOX_NOT_VISIBLE = 0,
	SKYBOX_3DSKYBOX_VISIBLE,
	SKYBOX_2DSKYBOX_VISIBLE,
};
class CEngineClient
{
public:
	/*
		Look here: https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/cdll_int.h#L194
		for function comments etc.
	*/
	virtual int					GetIntersectingSurfaces(
		const model_t *model,
		const Vector &vCenter,
		const float radius,
		const bool bOnlyVisibleSurfaces,	// Only return surfaces visible to vCenter.
		SurfInfo *pInfos,
		const int nMaxInfos) = 0;
	virtual Vector			GetLightForPoint(const Vector &pos, bool bClamp) = 0;
	virtual IMaterial*		TraceLineMaterialAndLighting(const Vector &start, const Vector &end,Vector &diffuseLightColor, Vector& baseColor) = 0;
	virtual const char*		ParseFile(const char *data, char *token, int maxlen) = 0;
	virtual bool			CopyLocalFile(const char *source, const char *destination) = 0;
	virtual void			GetScreenSize(int& width, int& height) = 0;
	virtual void			ServerCmd(const char *szCmdString, bool bReliable = true) = 0;
	virtual void			ClientCmd(const char *szCmdString) = 0;
	virtual bool			GetPlayerInfo(int ent_num, player_info_t *pinfo) = 0;
	virtual int				GetPlayerForUserID(int userID) = 0;
	virtual client_textmessage_t*TextMessageGet(const char *pName) = 0;
	virtual bool			Con_IsVisible(void) = 0;
	virtual int				GetLocalPlayer(void) = 0;
	virtual const model_t*	LoadModel(const char *pName, bool bProp = false) = 0;
	virtual float			Time(void) = 0;
	virtual float			GetLastTimeStamp(void) = 0;
	virtual CSentence*		GetSentence(CAudioSource *pAudioSource) = 0;
	virtual float			GetSentenceLength(CAudioSource *pAudioSource) = 0;
	virtual bool			IsStreaming(CAudioSource *pAudioSource) const = 0;
	virtual void			GetViewAngles(QAngle& va) = 0;
	virtual void			SetViewAngles(QAngle& va) = 0;
	virtual int				GetMaxClients(void) = 0;
	virtual	const char*		Key_LookupBinding(const char *pBinding) = 0;
	virtual const char*		Key_BindingForKey(ButtonCode_t code) = 0;
	virtual void			StartKeyTrapMode(void) = 0;
	virtual bool			CheckDoneKeyTrapping(ButtonCode_t &code) = 0;
	virtual bool			IsInGame(void) = 0;
	virtual bool			IsConnected(void) = 0;
	virtual bool			IsDrawingLoadingImage(void) = 0;
	virtual void			Con_NPrintf(int pos, PRINTF_FORMAT_STRING const char *fmt, ...) = 0;
	virtual void			Con_NXPrintf( const struct con_nprint_s *info, PRINTF_FORMAT_STRING const char *fmt, ... ) = 0;
	virtual int				IsBoxVisible(const Vector& mins, const Vector& maxs) = 0;
	virtual int				IsBoxInViewCluster(const Vector& mins, const Vector& maxs) = 0;
	virtual bool			CullBox(const Vector& mins, const Vector& maxs) = 0;
	virtual void			Sound_ExtraUpdate(void) = 0;
	virtual const char*		GetGameDirectory(void) = 0;
	virtual const VMatrix&	WorldToScreenMatrix() = 0;
	virtual const VMatrix&	WorldToViewMatrix() = 0;
	virtual int				GameLumpVersion(int lumpId) const = 0;
	virtual int				GameLumpSize(int lumpId) const = 0;
	virtual bool			LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
	virtual int	LevelLeafCount() const = 0;
	virtual ISpatialQuery* GetBSPTreeQuery() = 0;
	virtual void	LinearToGamma(float* linear, float* gamma) = 0;
	virtual float	LightStyleValue(int style) = 0;
	virtual void		ComputeDynamicLighting(const Vector& pt, const Vector* pNormal, Vector& color) = 0;
	virtual void	GetAmbientLightColor(Vector& color) = 0;
	virtual int	GetDXSupportLevel() = 0;
	virtual bool        SupportsHDR() = 0;
	virtual void	Mat_Stub(IMaterialSystem *pMatSys) = 0;
	virtual void GetChapterName(char *pchBuff, int iMaxLength) = 0;
	virtual char const*	GetLevelName(void) = 0;
	virtual int	GetLevelVersion(void) = 0;
	virtual struct IVoiceTweak_s *GetVoiceTweakAPI(void) = 0;
	virtual void		EngineStats_BeginFrame(void) = 0;
	virtual void	EngineStats_EndFrame(void) = 0;
	virtual void	FireEvents() = 0;
	virtual int	GetLeavesArea(int *pLeaves, int nLeaves) = 0;
	virtual bool	DoesBoxTouchAreaFrustum(const Vector &mins, const Vector &maxs, int iArea) = 0;
	virtual void	SetAudioState(const AudioState_t& state) = 0;
	virtual int		SentenceGroupPick(int groupIndex, char *name, int nameBufLen) = 0;
	virtual int			SentenceGroupPickSequential(int groupIndex, char *name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int			SentenceIndexFromName(const char *pSentenceName) = 0;
	virtual const char *SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int			SentenceGroupIndexFromName(const char *pGroupName) = 0;
	virtual const char *SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float	SentenceLength(int sentenceIndex) = 0;
	virtual void		ComputeLighting(const Vector& pt, const Vector* pNormal, bool bClamp, Vector& color, Vector *pBoxColors = NULL) = 0;
	virtual void		ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool	IsOccluded(const Vector &vecAbsMins, const Vector &vecAbsMaxs) = 0;
	virtual void*	SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void	SaveFreeMemory(void *pSaveMem) = 0;
	virtual INetChannelInfo *GetNetChannelInfo(void) = 0;
	CNetChannel* GetNetChannel() { return (CNetChannel*)GetNetChannelInfo(); }
	virtual void		DebugDrawPhysCollide(const CPhysCollide *pCollide, IMaterial *pMaterial, matrix3x4_t& transform, const color32 &color) = 0;
	virtual void	CheckPoint(const char *pName) = 0;
	virtual void	DrawPortals() = 0;
	virtual bool	IsPlayingDemo(void) = 0;
	virtual bool	IsRecordingDemo(void) = 0;
	virtual bool	IsPlayingTimeDemo(void) = 0;
	virtual int			GetDemoRecordingTick(void) = 0;
	virtual int			GetDemoPlaybackTick(void) = 0;
	virtual int			GetDemoPlaybackStartTick(void) = 0;
	virtual float		GetDemoPlaybackTimeScale(void) = 0;
	virtual int	GetDemoPlaybackTotalTicks(void) = 0;
	virtual bool	IsPaused(void) = 0;
	virtual bool	IsTakingScreenshot(void) = 0;
	virtual bool	IsHLTV(void) = 0;
	virtual bool	IsLevelMainMenuBackground(void) = 0;
	virtual void	GetMainMenuBackgroundName(char *dest, int destlen) = 0;
	virtual void	GetVideoModes(int &nCount, vmode_s *&pModes) = 0;
	virtual void	SetOcclusionParameters(const OcclusionParams_t &params) = 0;
	virtual void	GetUILanguage(char *dest, int destlen) = 0;
	virtual SkyboxVisibility_t IsSkyboxVisibleFromPoint(const Vector &vecPoint) = 0;
	virtual const char* GetMapEntitiesString() = 0;
	virtual bool	IsInEditMode(void) = 0;
	virtual float	GetScreenAspectRatio() = 0;
	virtual bool	REMOVED_SteamRefreshLogin(const char *password, bool isSecure) = 0;
	virtual bool	REMOVED_SteamProcessCall(bool & finished) = 0;
	virtual unsigned int	GetEngineBuildNumber() = 0; // engines build
	virtual const char * GetProductVersionString() = 0; // mods version number (steam.inf
	virtual void			GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
	virtual bool	IsHammerRunning() const = 0;
	virtual void	ExecuteClientCmd(const char *szCmdString) = 0;
	virtual bool MapHasHDRLighting(void) = 0;
	virtual int	GetAppID() = 0;
	virtual Vector GetLightForPointFast(const Vector &pos, bool bClamp) = 0;
	virtual void	ClientCmd_Unrestricted(const char *szCmdString) = 0;
	virtual void	SetRestrictServerCommands(bool bRestrict) = 0;
	virtual void	SetRestrictClientCommands(bool bRestrict) = 0;
	virtual void	SetOverlayBindProxy(int iOverlayID, void *pBindProxy) = 0;
	virtual bool	CopyFrameBufferToMaterial(const char *pMaterialName) = 0;
	virtual void	ChangeTeam(const char *pTeamName) = 0;
	virtual void	ReadConfiguration(const bool readDefault = false) = 0;
	virtual void	SetAchievementMgr(IAchievementMgr *pAchievementMgr) = 0;
	virtual IAchievementMgr *GetAchievementMgr() = 0;
	virtual bool			MapLoadFailed(void) = 0;
	virtual void	SetMapLoadFailed(bool bState) = 0;
	virtual bool	IsLowViolence() = 0;
	virtual const char		*GetMostRecentSaveGame(void) = 0;
	virtual void	SetMostRecentSaveGame(const char *lpszFilename) = 0;
	virtual void			StartXboxExitingProcess() = 0;
	virtual bool			IsSaveInProgress() = 0;
	virtual UINT			OnStorageDeviceAttached(void) = 0;
	virtual void	OnStorageDeviceDetached(void) = 0;
	virtual void	ResetDemoInterpolation(void) = 0;
	virtual void SetGamestatsData(CGamestatsData *pGamestatsData) = 0;
	virtual CGamestatsData *GetGamestatsData() = 0;
	virtual void GetMouseDelta(int &x, int &y, bool bIgnoreNextMouseDelta = false) = 0;
	virtual void ServerCmdKeyValues(KeyValues *pKeyValues) = 0;
	virtual bool IsSkippingPlayback(void) = 0;
	virtual bool IsLoadingDemo(void) = 0;
	virtual bool IsPlayingDemoALocallyRecordedDemo() = 0;
	virtual	const char	*Key_LookupBindingExact(const char *pBinding) = 0;
};
