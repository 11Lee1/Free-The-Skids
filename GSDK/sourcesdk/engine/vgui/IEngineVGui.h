class IEngineVGui
{
public:
	virtual					~IEngineVGui(void) { }

	virtual vgui::VPanel*	GetPanel(VGuiPanel_t type) = 0;

	virtual bool	IsGameUIVisible() = 0;
};