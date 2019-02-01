class ClientMode
{
public:
	/*0*/	virtual	~ClientMode() = 0;
	/*1*/	virtual void	Nothing__01() = 0;
	/*2*/	virtual void	Init() = 0;
	/*3*/	virtual void	VGui_Shutdown() = 0;
	/*4*/	virtual void	Nothing__02() = 0;
	/*5*/	virtual void	Enable() = 0;
	/*6*/	virtual void	Disable() = 0;
	/*7*/	virtual void	Layout() = 0;
	/*8*/	virtual void*/*vgui::Panel*/GetViewport() = 0;
	/*9*/	virtual void*/*vgui::Panel*/GetViewportAnimationController() = 0;
	/*10*/	virtual void	ProcessInput(bool bActive) = 0;
	/*11*/	virtual bool	ShouldDrawDetailObjects() = 0;				// Will always return 1
	/*12*/	virtual bool	ShouldDrawEntity(BaseEntity *pEnt) = 0;		// Will always return 1
	/*13*/	virtual bool	ShouldDrawLocalPlayer(BaseEntity *pPlayer) = 0;
	/*14*/	virtual bool	ShouldDrawParticles() = 0;					// Will always return 1
	/*15*/	virtual bool	ShouldDrawFog(void) = 0;					// Will always return 1
	/*16*/	virtual void	OverrideView(CViewSetup *pSetup) = 0;
	/*17*/	virtual int		KeyInput(int down, ButtonCode_t keynum, const char *pszCurrentBinding) = 0;
	/*18*/	virtual void	StartMessageMode(int iMessageModeType) = 0;
	/*19*/	virtual void*/*vgui::Panel*/GetMessagePanel() = 0;
	/*20*/	virtual void	OverrideMouseInput(float *x, float *y) = 0;
	/*21*/	virtual bool	CreateMove(float flInputSampleTime, CUserCmd *cmd) = 0;
	/*22*/	virtual void	LevelInit(const char *newmap) = 0;
	/*23*/	virtual void	LevelShutdown(void) = 0;
	/*24*/	virtual bool	ShouldDrawViewModel(void) = 0;
	/*25*/	virtual bool	ShouldDrawCrosshair(void) = 0;
	/*26*/	virtual void	Nothing__03() = 0;							//	virtual void	AdjustEngineViewport(int& x, int& y, int& width, int& height) = 0;
	/*27*/	virtual void	Nothing__04() = 0;							//	virtual void	PreRender(CViewSetup *pSetup) = 0;
	/*28*/	virtual void	PostRender(void) = 0;
	/*29*/	virtual void	Nothing__05() = 0;							//	virtual void	PostRenderVGui() = 0;
	/*30*/	virtual void	ActivateInGameVGuiContext(vgui::Panel *pPanel) = 0;
	/*31*/	virtual void	DeactivateInGameVGuiContext() = 0;
	/*32*/	virtual float	GetViewModelFOV(void) = 0;
	/*33*/	virtual bool	CanRecordDemo(char *errorMsg, int length) const = 0; // will always return 1
	/*34*/	virtual void	ComputeVguiResConditions(KeyValues *pkvConditions) = 0;
};