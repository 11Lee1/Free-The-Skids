namespace vgui
{
	class SurfacePlat;
	class VPanel;
	typedef unsigned long HPanel;
	typedef unsigned long HScheme;
	typedef unsigned int VPANEL;
	enum EInterfaceID
	{
		ICLIENTPANEL_STANDARD_INTERFACE = 0,
	};
	class IClientPanel
	{
	public:
		virtual vgui::VPanel* GetVPanel() = 0;

		// straight interface to Panel functions
		virtual void Think() = 0;
		virtual void PerformApplySchemeSettings() = 0;
		virtual void PaintTraverse(bool forceRepaint, bool allowForce) = 0;
		virtual void Repaint() = 0;
		virtual vgui::VPanel* IsWithinTraverse(int x, int y, bool traversePopups) = 0;
		virtual void GetInset(int &top, int &left, int &right, int &bottom) = 0;
		virtual void GetClipRect(int &x0, int &y0, int &x1, int &y1) = 0;
		virtual void OnChildAdded(vgui::VPanel* child) = 0;
		virtual void OnSizeChanged(int newWide, int newTall) = 0;

		virtual void InternalFocusChanged(bool lost) = 0;
		virtual bool RequestInfo(KeyValues *outputData) = 0;
		virtual void RequestFocus(int direction) = 0;
		virtual bool RequestFocusPrev(vgui::VPanel* existingPanel) = 0;
		virtual bool RequestFocusNext(vgui::VPanel* existingPanel) = 0;
		virtual void OnMessage(const KeyValues *params, vgui::VPanel* ifromPanel) = 0;
		virtual vgui::VPanel* GetCurrentKeyFocus() = 0;
		virtual int GetTabPosition() = 0;

		// for debugging purposes
		virtual const char *GetName() = 0;
		virtual const char *GetClassName() = 0;

		// get scheme handles from panels
		virtual HScheme GetScheme() = 0;
		// gets whether or not this panel should scale with screen resolution
		virtual bool IsProportional() = 0;
		// auto-deletion
		virtual bool IsAutoDeleteSet() = 0;
		// deletes this
		virtual void DeletePanel() = 0;

		// interfaces
		virtual void *QueryInterface(EInterfaceID id) = 0;

		// returns a pointer to the vgui controls baseclass Panel *
		virtual Panel *GetPanel() = 0;

		// returns the name of the module this panel is part of
		virtual const char *GetModuleName() = 0;

		virtual void OnTick() = 0;
	};

	class VPanel
	{
	public:
		virtual ~VPanel() = 0;
	public:
		IClientPanel* Client()
		{
			return (IClientPanel*)_clientPanel;
		}
		vgui::Panel* Panel()
		{
			return (vgui::Panel*)_clientPanel;
		}

	public:
		void*							_childDar;
		BYTE							pad[8];
		int								nChildren;
		void*							_childDar2;
		vgui::VPanel*					_parent;
		SurfacePlat*					_plat;
		HPanel							_hPanel;
		IClientPanel*					_clientPanel;
		short							_zpos;
		bool							_visible;
		bool							_enabled;
		bool							_popup;
		bool							_mouseInput;
		bool							_kbInput;
		bool							_isTopmostPopup;
		BYTE							pad2[8];
		bool							_PopupWantsFont;
		int								_pos[2];
		int								_size[2];
		int								_minimumSize[2];
		int								_inset[4];
		int								_clipRect[4];
		int								_absPos[2];
	};
};