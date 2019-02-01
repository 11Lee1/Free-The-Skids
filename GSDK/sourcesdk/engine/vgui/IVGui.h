namespace vgui
{
	typedef unsigned int VPANEL;
	typedef unsigned long HPanel;
	typedef int HContext;

	enum
	{
		DEFAULT_VGUI_CONTEXT = ((vgui::HContext)~0)
	};
	typedef unsigned long HPanel;

	class IVGui
	{
	public:
		virtual void NotImportant_0() = 0;
		virtual void NotImportant_1() = 0;
		virtual void NotImportant_2() = 0;
		virtual void NotImportant_3() = 0;
		virtual void NotImportant_4() = 0;
		// activates vgui message pump
		virtual void Start() = 0;

		// signals vgui to Stop running
		virtual void Stop() = 0;

		// returns true if vgui is current active
		virtual bool IsRunning() = 0;

		// runs a single frame of vgui
		virtual void RunFrame() = 0;

		// broadcasts "ShutdownRequest" "id" message to all top-level panels in the app
		virtual void ShutdownMessage(unsigned int shutdownID) = 0;

		// panel allocation
		virtual VPanel* AllocPanel() = 0;
		virtual void FreePanel(VPanel* panel) = 0;

		// debugging prints
		virtual void DPrintf(PRINTF_FORMAT_STRING const char *format, ...) = 0;
		virtual void DPrintf2(PRINTF_FORMAT_STRING const char *format, ...) = 0;
		virtual void SpewAllActivePanelNames() = 0;

		// safe-pointer handle methods
		virtual HPanel PanelToHandle(VPanel* panel) = 0;
		virtual VPanel* HandleToPanel(HPanel index) = 0;
		virtual void MarkPanelForDeletion(VPanel* panel) = 0;

		// makes panel receive a 'Tick' message every frame (~50ms, depending on sleep times/framerate)
		// panel is automatically removed from tick signal list when it's deleted
		virtual void AddTickSignal(VPANEL panel, int intervalMilliseconds = 0) = 0;
		virtual void RemoveTickSignal(VPANEL panel) = 0;

		// message sending
		virtual void PostMessage(VPanel* target, KeyValues *params, VPanel* from, float delaySeconds = 0.0f) = 0;

		// Creates/ destroys vgui contexts, which contains information
		// about which controls have mouse + key focus, for example.
		virtual HContext CreateContext() = 0;
		virtual void DestroyContext(HContext context) = 0;

		// Associates a particular panel with a vgui context
		// Associating NULL is valid; it disconnects the panel from the context
		virtual void AssociatePanelWithContext(HContext context, VPanel* pRoot) = 0;

		// Activates a particular context, use DEFAULT_VGUI_CONTEXT
		// to get the one normally used by VGUI
		virtual void ActivateContext(HContext context) = 0;

		// whether to sleep each frame or not, true = sleep
		virtual void SetSleep(bool state) = 0;

		// data accessor for above
		virtual bool GetShouldVGuiControlSleep() = 0;

		// enables VR mode
		virtual void SetVRMode(bool bVRMode) = 0;
		virtual bool GetVRMode() = 0;

		// add a tick signal like above, but to the head of the list of tick signals
		virtual void AddTickSignalToHead(VPanel* panel, int intervalMilliseconds = 0) = 0;
	};
}