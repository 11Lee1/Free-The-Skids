#define VALVE_LIGHT_GREY Color(112,115,118,255)
#define VALVE_DARK_GREY Color(80,83,86,255)
#define VALVE_LIGHT_WHITE Color(241,241,241,255)
#define VALVE_DARK_WHITE Color(222,222,222,255)
#define VALVE_BORDER Color(35,35,35,255)
#define VALVE_DARK_BORDER Color(79,79,79,255)
#define VALVE_CHECKBOX_GREEN Color(119,190,119,255)

class IForceVirtualInheritancePanel
{
	// We need Panel to use virtual inheritance so that
	// pointers to its members are max size.
	// This is due to a limitation in C++ with ahead
	// declarations of points to members as used in MessageMap.
};
namespace vgui
{
	enum CursorCode
	{
		dc_user,
		dc_none,
		dc_arrow,
		dc_ibeam,
		dc_hourglass,
		dc_waitarrow,
		dc_crosshair,
		dc_up,
		dc_sizenwse,
		dc_sizenesw,
		dc_sizewe,
		dc_sizens,
		dc_sizeall,
		dc_no,
		dc_hand,
		dc_blank, // don't show any custom vgui cursor, just let windows do it stuff (for HTML widget)
		dc_last,
	};
	enum BuildModeFlags_t
	{
		BUILDMODE_EDITABLE = 0x01,
		BUILDMODE_DELETABLE = 0x02,
		BUILDMODE_SAVE_XPOS_RIGHTALIGNED = 0x04,
		BUILDMODE_SAVE_XPOS_CENTERALIGNED = 0x08,
		BUILDMODE_SAVE_YPOS_BOTTOMALIGNED = 0x10,
		BUILDMODE_SAVE_YPOS_CENTERALIGNED = 0x20,
		BUILDMODE_SAVE_WIDE_FULL = 0x40,
	};
	enum PanelFlags_t
	{
		MARKED_FOR_DELETION = 0x0001,
		NEEDS_REPAINT = 0x0002,
		PAINT_BORDER_ENABLED = 0x0004,
		PAINT_BACKGROUND_ENABLED = 0x0008,
		PAINT_ENABLED = 0x0010,
		POST_CHILD_PAINT_ENABLED = 0x0020,
		AUTODELETE_ENABLED = 0x0040,
		NEEDS_LAYOUT = 0x0080,
		NEEDS_SCHEME_UPDATE = 0x0100,
		NEEDS_DEFAULT_SETTINGS_APPLIED = 0x0200,
		ALLOW_CHAIN_KEYBINDING_TO_PARENT = 0x0400,
		IN_PERFORM_LAYOUT = 0x0800,
		IS_PROPORTIONAL = 0x1000,
		TRIPLE_PRESS_ALLOWED = 0x2000,
		DRAG_REQUIRES_PANEL_EXIT = 0x4000,
		IS_MOUSE_DISABLED_FOR_THIS_PANEL_ONLY = 0x8000,
		ALL_FLAGS = 0xFFFF,
	};
	class PHandle;
	class DHANDLE;
	struct Mouse_t
	{
		Mouse_t()
		{
			MouseInputEnabled = true;
			MouseWithinMainPanel = false;
			MousePosition = Vector2D(0, 0);
			MouseButtonDown = false;
			MouseDownPosInPanel[2] = { };
			MouseClicked = false;
			MouseDoubleClicked = false;
		}

		bool MouseInputEnabled;
		bool MouseWithinMainPanel;
		bool MouseButtonDown;
		bool MouseClicked;
		bool MouseDoubleClicked;

		Vector2D MousePosition;
		int MouseDownPosInPanel[2];
	};
	class Panel : public IClientPanel, virtual IForceVirtualInheritancePanel
	{
	public:
		virtual ~Panel();
		Panel();

		Panel(Panel* parent);
		Panel(Panel* parent, char const* panelName);
		Panel(Panel* parent, char const* panelName, HScheme scheme);
		void Init(int posX, int posY, int panel_width, int panel_height);
		

	public:
		void MakePopup(bool showTaskBarIcon = true, bool disabled = false) { surface()->CreatePopup(GetVPanel(), false, showTaskBarIcon, disabled); }
		bool IsMouseOver() { return (vgui_Input()->GetMouseOver() == GetVPanel()); }
		void SetName(char const* panelName);
		void SetScheme(HScheme scheme);
		int GetWide();
		int GetTall();
	public:
		// stuff from IPanel to make life easier.
		void SetPos(int x, int y) { Interfaces::IPanel()->SetPos(GetVPanel(), x, y); }
		void GetPos(int &x, int &y) { Interfaces::IPanel()->GetPos(GetVPanel(),x, y); }
		void SetSize(int wide, int tall) { Interfaces::IPanel()->SetSize(GetVPanel(),wide, tall); }
		void GetSize(int &wide, int &tall) { Interfaces::IPanel()->GetSize(GetVPanel(), wide, tall); }
		void SetMinimumSize(int wide, int tall) { Interfaces::IPanel()->SetMinimumSize(GetVPanel(), wide, tall); }
		void GetMinimumSize(int &wide, int &tall) { Interfaces::IPanel()->GetMinimumSize(GetVPanel(), wide, tall); }
		void SetZPos(int z) { Interfaces::IPanel()->SetZPos(GetVPanel(), z); }
		int GetZPos() { Interfaces::IPanel()->GetZPos(GetVPanel()); }
		void GetAbsPos(int &x, int &y) { Interfaces::IPanel()->GetAbsPos(GetVPanel(), x, y); }
		void GetClipRect(int &x0, int &y0, int &x1, int &y1) { Interfaces::IPanel()->GetClipRect(GetVPanel(), x0, y0, x1, y1); }
		void SetInset(int left, int top, int right, int bottom) { Interfaces::IPanel()->SetInset(GetVPanel(), left, top, right, bottom); }
		void GetInset(int &left, int &top, int &right, int &bottom) { Interfaces::IPanel()->GetInset(GetVPanel(), left, top, right, bottom); }
		void SetVisible(bool state) { Interfaces::IPanel()->SetVisible(GetVPanel(), state); }
		bool IsVisible() { return Interfaces::IPanel()->IsVisible(GetVPanel()); }
		HCursor GetCursor() { return _cursor; }
		void SetCursor(HCursor cursor) { _cursor = cursor; surface()->SetCursor(_cursor); }
		void SetParent(Panel* newParent);
		void SetParent(VPanel* newParent);

		int GetChildCount() { return Interfaces::IPanel()->GetChildCount(GetVPanel()); }
		VPanel* GetChild(int index = 0) { return Interfaces::IPanel()->GetChild(GetVPanel(), index); }
		CUtlVector<VPanel*>& GetChildren() { return Interfaces::IPanel()->GetChildren(GetVPanel()); }
		VPanel* GetParent() { return Interfaces::IPanel()->GetParent(GetVPanel()); }
		void MoveToFront() { Interfaces::IPanel()->MoveToFront(GetVPanel()); }
		void MoveToBack() { Interfaces::IPanel()->MoveToBack(GetVPanel()); }
		bool hasParent(VPanel* potentialParent) { return Interfaces::IPanel()->HasParent(GetVPanel(), potentialParent); }
		bool IsPopup() { return Interfaces::IPanel()->IsPopup(GetVPanel()); }
		void SetPopup(bool status) { Interfaces::IPanel()->SetPopup(GetVPanel(),status); }
		bool IsFullyVisible() { return Interfaces::IPanel()->IsFullyVisible(GetVPanel()); }
		HScheme GetScheme() { return m_iScheme; }
		bool IsProportional() { return _flags.IsFlagSet(IS_PROPORTIONAL); }
		bool IsAutoDeleteSet() { return _flags.IsFlagSet(AUTODELETE_ENABLED); };
		void DeletePanel() { _flags.SetFlag(MARKED_FOR_DELETION); _flags.ClearFlag(AUTODELETE_ENABLED); delete this; };
		void SetKeyBoardInputEnabled(bool state) { Interfaces::IPanel()->SetKeyBoardInputEnabled(GetVPanel(), state); }
		void SetMouseInputEnabled(bool state) { Interfaces::IPanel()->SetMouseInputEnabled(GetVPanel(), state); }
		bool IsKeyBoardInputEnabled() { return Interfaces::IPanel()->IsKeyBoardInputEnabled(GetVPanel()); }
		bool IsMouseInputEnabled() { return Interfaces::IPanel()->IsMouseInputEnabled(GetVPanel()); }
		void Solve() { Interfaces::IPanel()->Solve(GetVPanel()); }
		char const* GetName() { return _panelName; }
		char const* GetClassName() { return "Do this Later"; }
		void SendMessage(KeyValues* params, VPanel* ifromPanel) { Interfaces::IPanel()->SendMessageW(GetVPanel(), params, ifromPanel); }

	public:
		inline void DisableMouseInputForThisPanel(bool bDisable) { _flags.SetFlag(IS_MOUSE_DISABLED_FOR_THIS_PANEL_ONLY, bDisable); }
		inline bool IsMouseInputDisabledForThisPanel() const { return _flags.IsFlagSet(IS_MOUSE_DISABLED_FOR_THIS_PANEL_ONLY); }
		void InvalidateLayout(bool layoutNow = false, bool reloadScheme = false);
		bool IsWithin(int x, int y);
	public:
		//	functions you can modify yourself in seperate panels.
		
		virtual void OnThink();

		// these 4 are in call order
		virtual void PaintBackground();
		virtual void Paint();
		virtual void PaintBorder();
		virtual void PostChildPaint();


		virtual void PerformLayout();
	private:
		void InternalPerformLayout();
	public:
		// Functions from IClientPanel, I do not recomend you touch this stuff unless you know what you're doing.
		VPanel* GetVPanel() { return _vpanel; };
		VPanel* GetVParent() { return GetParent(); }
	private:
		void Think();
		void PerformApplySchemeSettings();
		void PaintTraverse(bool forceRepaint, bool allowForce);
		void Repaint();
		VPanel* IsWithinTraverse(int x, int y, bool traversePopups);
		void OnChildAdded(VPanel* child);
		void OnSizeChanged(int newWide, int newTall);
		void InternalFocusChanged(bool lost);
		bool RequestInfo(KeyValues *outputData);
		void RequestFocus(int direction);
		bool RequestFocusPrev(vgui::VPanel* existingPanel);
		bool RequestFocusNext(vgui::VPanel* existingPanel);
		void OnMessage(const KeyValues *params, vgui::VPanel* ifromPanel);
		VPanel* GetCurrentKeyFocus();
		int GetTabPosition();

		void *QueryInterface(EInterfaceID id);
		Panel *GetPanel() { return this; };
		const char *GetModuleName();
		void OnTick();
	protected:
		VPanel*				_vpanel;
		char*				_panelName;
		HCursor				_cursor;
		IBorder*			_border;
		CUtlFlags<int>		_flags;
		unsigned char		_tabPosition;
		HScheme				m_iScheme;
		float				m_flAlpha;
	};
	void Panel::OnThink() {
		if(IsMouseOver())
			SetCursor(_cursor);
		// do your stuff here.
	}
	void Panel::PerformLayout(){
		// this should be overridden to relayout controls
	}

	void Panel::PaintBackground(){
		// background paint code.
	}
	void Panel::Paint(){
		// paint code.
	}
	void Panel::PaintBorder(){
		// border paint code.
	}
	void Panel::PostChildPaint(){
		// post child paint code.
	}


	// dont touch below.
	int Panel::GetWide(){
		int w, t;
		GetSize(w, t);
		return w;
	}
	int Panel::GetTall() {
		int w, t;
		GetSize(w, t);
		return t;
	}
	void Panel::SetParent(Panel* newParent){
		if (newParent)
			SetParent(newParent->GetVPanel());
		else
			SetParent((VPanel*)NULL);
	}
	void Panel::SetParent(VPanel* newParent) {
		if (newParent)
			Interfaces::IPanel()->SetParent(GetVPanel(), newParent);
		else
			Interfaces::IPanel()->SetParent(GetVPanel(), NULL);
	}
	void Panel::SetScheme(HScheme scheme){
		if (scheme != m_iScheme)
			m_iScheme = scheme;
	}
	void Panel::SetName(char const* panelName) {
		if (_panelName && panelName && !strcmp(_panelName, panelName))
		{
			return;
		}

		if (_panelName)
		{
			delete[] _panelName;
			_panelName = NULL;
		}

		if (panelName)
		{
			int len = strlen(panelName) + 1;
			_panelName = new char[len];
			strcpy_s(_panelName, len, panelName);
		}
	}
	void Panel::InternalPerformLayout()
	{
		_flags.SetFlag(IN_PERFORM_LAYOUT);
		// make sure the scheme has been applied
		_flags.ClearFlag(NEEDS_LAYOUT);
		PerformLayout();
		_flags.ClearFlag(IN_PERFORM_LAYOUT);
	}
	void Panel::InvalidateLayout(bool layoutNow, bool reloadScheme)
	{
		_flags.SetFlag(NEEDS_LAYOUT);

		if (reloadScheme)
		{
			// make all our children reload the scheme
			_flags.SetFlag(NEEDS_SCHEME_UPDATE);

			for (int i = 0; i < GetChildCount(); i++)
			{
				((Panel*)GetChild(i)->Client())->InvalidateLayout(layoutNow, true);
			}

			PerformApplySchemeSettings();
		}

		if (layoutNow)
		{
			InternalPerformLayout();
			Repaint();
		}
	}
	bool Panel::IsWithin(int x, int y)
	{
		// check against our clip rect
		int clipRect[4];
		GetClipRect(clipRect[0], clipRect[1], clipRect[2], clipRect[3]);

		if (x < clipRect[0])
		{
			return false;
		}

		if (y < clipRect[1])
		{
			return false;
		}

		if (x >= clipRect[2])
		{
			return false;
		}

		if (y >= clipRect[3])
		{
			return false;
		}

		return true;
	}
	void Panel::Think() {
		OnThink();
	}
	void Panel::PerformApplySchemeSettings() { }
	void Panel::PaintTraverse(bool repaint, bool allowForce){
		if (!IsVisible())
			return;

		float oldAlphaMultiplier = surface()->DrawGetAlphaMultiplier();
		float newAlphaMultiplier = oldAlphaMultiplier * m_flAlpha * 1.0f / 255.0f;

		if (_flags.IsFlagSet(NEEDS_REPAINT))
			repaint = true;

		if(allowForce)
			_flags.ClearFlag(NEEDS_REPAINT);



		VPanel* vpanel = GetVPanel();

		int clipRect[4];
		GetClipRect(clipRect[0], clipRect[1], clipRect[2], clipRect[3]);
		if ((clipRect[2] <= clipRect[0]) || (clipRect[3] <= clipRect[1])){
			repaint = false;
		}

		// set global alpha
		surface()->DrawSetAlphaMultiplier(newAlphaMultiplier);

		if (repaint && _flags.IsFlagSet(PAINT_BACKGROUND_ENABLED | PAINT_ENABLED)){
			// draw the background with no inset
			if (_flags.IsFlagSet(PAINT_BACKGROUND_ENABLED)){
				surface()->PushMakeCurrent(vpanel,false);
				PaintBackground();
				surface()->PopMakeCurrent(vpanel);
			}

			// draw the front of the panel with the inset
			if (_flags.IsFlagSet(PAINT_ENABLED)){
				surface()->PushMakeCurrent(vpanel, true);
				Paint();
				surface()->PopMakeCurrent(vpanel);
			}
		}

		// traverse and paint all our children
		int childCount = GetChildCount();
		for (int i = 0; i < childCount; i++)
		{
			VPanel* child = GetChild(i);
			if (surface()->ShouldPaintChildPanel(child))
			{
				Interfaces::IPanel()->PaintTraverse(child, repaint, allowForce);
			}
			else
			{
				// Invalidate the child panel so that it gets redrawn
				surface()->Invalidate(child);

				// keep traversing the tree, just don't allow anyone to paint after here
				Interfaces::IPanel()->PaintTraverse(child, false, false);
			}
		}

		// draw the border last
		if (repaint && _flags.IsFlagSet(PAINT_BORDER_ENABLED))
		{
			// Paint the border over the background with no inset
			surface()->PushMakeCurrent(vpanel, false);
			PaintBorder();
			surface()->PopMakeCurrent(vpanel);
		}


		// All of our children have painted, etc, now allow painting in top of them
		if (repaint && _flags.IsFlagSet(POST_CHILD_PAINT_ENABLED))
		{
			surface()->PushMakeCurrent(vpanel, false);
			PostChildPaint();
			surface()->PopMakeCurrent(vpanel);
		}

		surface()->DrawSetAlphaMultiplier(oldAlphaMultiplier);

		surface()->SwapBuffers(vpanel);
	}
	void Panel::Repaint(){
		_flags.SetFlag(NEEDS_REPAINT);
		surface()->Invalidate(GetVPanel());
	}
	VPanel* Panel::IsWithinTraverse(int x, int y, bool traversePopups){
		if (!IsVisible() || !IsMouseInputEnabled())
			return NULL;

		if (traversePopups)
		{
			// check popups first
			int i;
			for (i = GetChildCount() - 1; i >= 0; i--)
			{
				VPanel* panel = Interfaces::IPanel()->GetChild(GetVPanel(), i);
				if (Interfaces::IPanel()->IsPopup(panel))
				{
					panel = Interfaces::IPanel()->IsWithinTraverse(panel, x, y, true);
					if (panel != NULL)
					{
						return panel;
					}
				}
			}

			// check children recursive, if you find one, just return first one
			// this checks in backwards order so the last child drawn for this panel is chosen which
			// coincides to how it would be visibly displayed
			for (i = GetChildCount() - 1; i >= 0; i--)
			{
				VPanel* panel = Interfaces::IPanel()->GetChild(GetVPanel(), i);
				// we've already checked popups so ignore
				if (!Interfaces::IPanel()->IsPopup(panel))
				{
					panel = Interfaces::IPanel()->IsWithinTraverse(panel, x, y, true);
					if (panel != NULL)
					{
						return panel;
					}
				}
			}

			// check ourself
			if (!IsMouseInputDisabledForThisPanel() && IsWithin(x, y))
			{
				return GetVPanel();
			}
		}
		else
		{
			// since we're not checking popups, it must be within us, so we can check ourself first
			if (IsWithin(x, y))
			{
				// check children recursive, if you find one, just return first one
				// this checks in backwards order so the last child drawn for this panel is chosen which
				// coincides to how it would be visibly displayed
				for (int i = GetChildCount() - 1; i >= 0; i--)
				{
					VPanel* panel = Interfaces::IPanel()->GetChild(GetVPanel(), i);
					// ignore popups
					if (!Interfaces::IPanel()->IsPopup(panel))
					{
						panel = Interfaces::IPanel()->IsWithinTraverse(panel, x, y, false);
						if (panel != NULL)
						{
							return panel;
						}
					}
				}

				// not a child, must be us
				if (!IsMouseInputDisabledForThisPanel())
					return GetVPanel();
			}
		}
		return NULL;
	}
	void Panel::OnChildAdded(VPanel* child){
		//Assert(!_flags.IsFlagSet(IN_PERFORM_LAYOUT));
	}
	void Panel::OnSizeChanged(int newWide, int newTall){
		InvalidateLayout(); // our size changed so force us to layout again
	}
	void Panel::InternalFocusChanged(bool lost){
		/*
		this is commented out in sourcesdk idk
			//if focus is gained tell the focusNavGroup about it so its current can be correct
			if( (!lost) && (_focusNavGroup!=null) )
			{
				_focusNavGroup->setCurrentPanel(this);
			}
		*/
	}
	bool Panel::RequestInfo(KeyValues *outputData){
		if (GetVParent())
			return Interfaces::IPanel()->RequestInfo(GetVParent(), outputData);

		return false;
	}
	void Panel::RequestFocus(int direction) { /* Keyvalues has been a bitch so I'm not doing anything that invoves it xdxd */ }
	bool Panel::RequestFocusPrev(VPanel* panel) {
		if (GetVParent())
			return Interfaces::IPanel()->RequestFocusPrev(GetVPanel(), GetVPanel());
		return false;
	}
	bool Panel::RequestFocusNext(VPanel* panel) {
		// chain to parent
		if (GetVParent())
			return Interfaces::IPanel()->RequestFocusNext(GetVParent(), GetVPanel());
		return false;
	}
	void Panel::OnMessage(const KeyValues* params, VPanel* ifromPanel) 
	{ 
		// I guess since I'm retarded i found keyvalues a pain in the ass, if you want you can setup this and have proper OnMousePressed doublepressed etc shit.
		return;
	}
	VPanel* Panel::GetCurrentKeyFocus() { return NULL; }
	int Panel::GetTabPosition() { return _tabPosition; }
	void* Panel::QueryInterface(EInterfaceID id){
		if (id == ICLIENTPANEL_STANDARD_INTERFACE)
			return this;

		return NULL;
	}
	const char* Panel::GetModuleName(){ return "engine.dll"; /* idk */  }
	void Panel::OnTick() { /*do stuff here later.*/ }

	void Panel::Init(int posX, int posY, int panel_width, int panel_height)
	{
		_panelName = NULL;

		// get ourselves an internal panel
		_vpanel = Interfaces::IVGui()->AllocPanel();
		Interfaces::IPanel()->Init(_vpanel, this);


		SetPos(posX, posY);
		SetSize(panel_width, panel_height);

		_border = nullptr;
		_flags.SetFlag(NEEDS_LAYOUT | NEEDS_SCHEME_UPDATE | NEEDS_DEFAULT_SETTINGS_APPLIED);
		_flags.SetFlag(AUTODELETE_ENABLED | PAINT_BORDER_ENABLED | PAINT_BACKGROUND_ENABLED | PAINT_ENABLED);
		_flags.SetFlag(ALLOW_CHAIN_KEYBINDING_TO_PARENT);

		_tabPosition = 0;
		m_iScheme = 0;
		m_flAlpha = 255.0f;
		_cursor = dc_arrow;
	}
	Panel::Panel(){
		Init(0, 0, 64, 64);
	}
	Panel::Panel(Panel* parent){
		Init(0, 0, 64, 24);
		SetParent(parent);
	}
	Panel::Panel(Panel* parent, char const* panelName){
		Init(0, 0, 64, 24);
		SetName(panelName);
		SetParent(parent);
	}
	Panel::Panel(Panel* parent, char const* panelName, HScheme scheme){
		Init(0, 0, 64, 24);
		SetName(panelName);
		SetParent(parent);
		SetScheme(scheme);
	}
	Panel::~Panel(){
		_flags.ClearFlag(AUTODELETE_ENABLED);
		_flags.SetFlag(MARKED_FOR_DELETION);

		// remove panel from any list
		SetParent((VPanel*)NULL);

		// Stop our children from pointing at us, and delete them if possible
		while (GetChildCount())
		{
			VPanel* child = GetChild(0);
			if (Interfaces::IPanel()->IsAutoDeleteSet(child))
			{
				Interfaces::IPanel()->DeletePanel(child);
			}
			else
			{
				Interfaces::IPanel()->SetParent(child, NULL);
			}
		}

		// delete VPanel
		Interfaces::IVGui()->FreePanel(_vpanel);
		// free our name
		delete[] _panelName;

		_vpanel = NULL;
	}

};