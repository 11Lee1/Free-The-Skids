namespace vgui
{
	typedef unsigned long HScheme;
	typedef unsigned int VPANEL;
	class SurfacePlat;
	class IClientPanel;

	//!! must be removed
	class Panel;
	class IPanel : public IBaseInterface
	{
	public:
		virtual void Init(VPanel* vguiPanel, IClientPanel *panel) = 0;
		virtual void SetPos(VPanel* vguiPanel, int x, int y) = 0;
		virtual void GetPos(VPanel* vguiPanel, int &x, int &y) = 0;
		virtual void SetSize(VPanel* vguiPanel, int wide, int tall) = 0;
		virtual void GetSize(VPanel* vguiPanel, int &wide, int &tall) = 0;
		virtual void SetMinimumSize(VPanel* vguiPanel, int wide, int tall) = 0;
		virtual void GetMinimumSize(VPanel* vguiPanel, int &wide, int &tall) = 0;
		virtual void SetZPos(VPanel* vguiPanel, int z) = 0;
		virtual int  GetZPos(VPanel* vguiPanel) = 0;
		virtual void GetAbsPos(VPanel* vguiPanel, int &x, int &y) = 0;
		virtual void GetClipRect(VPanel* vguiPanel, int &x0, int &y0, int &x1, int &y1) = 0;
		virtual void SetInset(VPanel* vguiPanel, int left, int top, int right, int bottom) = 0;
		virtual void GetInset(VPanel* vguiPanel, int &left, int &top, int &right, int &bottom) = 0;
		virtual void SetVisible(VPanel* vguiPanel, bool state) = 0;
		virtual bool IsVisible(VPanel* vguiPanel) = 0;
		virtual void SetParent(VPanel* vguiPanel, VPanel* newParent) = 0;
		virtual int GetChildCount(VPanel* vguiPanel) = 0;
		virtual VPanel* GetChild(VPanel* vguiPanel, int index) = 0;
		virtual CUtlVector< VPanel* > &GetChildren(VPanel* vguiPanel) = 0;
		virtual VPanel* GetParent(VPanel* vguiPanel) = 0;
		virtual void MoveToFront(VPanel* vguiPanel) = 0; // 20
		virtual void MoveToBack(VPanel* vguiPanel) = 0;
		virtual bool HasParent(VPanel* vguiPanel, VPanel* potentialParent) = 0;
		virtual bool IsPopup(VPanel* vguiPanel) = 0;
		virtual void SetPopup(VPanel* vguiPanel, bool state) = 0;
		virtual bool IsFullyVisible(VPanel* vguiPanel) = 0;
		virtual HScheme GetScheme(VPanel* vguiPanel) = 0;
		virtual bool IsProportional(VPanel* vguiPanel) = 0;
		virtual bool IsAutoDeleteSet(VPanel* vguiPanel) = 0;
		virtual void DeletePanel(VPanel* vguiPanel) = 0;
		virtual void SetKeyBoardInputEnabled(VPanel* vguiPanel, bool state) = 0; // 30
		virtual void SetMouseInputEnabled(VPanel* vguiPanel, bool state) = 0;
		virtual bool IsKeyBoardInputEnabled(VPanel* vguiPanel) = 0;
		virtual bool IsMouseInputEnabled(VPanel* vguiPanel) = 0;
		virtual void Solve(VPanel* vguiPanel) = 0;
		virtual const char *GetName(VPanel* vguiPanel) = 0;
		virtual const char *GetClassName(VPanel* vguiPanel) = 0;
		virtual void SendMessage(VPanel* vguiPanel, KeyValues *params, VPanel* ifromPanel) = 0;
		virtual void Think(VPanel* vguiPanel) = 0;
		virtual void PerformApplySchemeSettings(VPanel* vguiPanel) = 0;
		virtual void PaintTraverse(VPanel* vguiPanel, bool forceRepaint, bool allowForce = true) = 0;
		virtual void Repaint(VPanel* vguiPanel) = 0;
		virtual VPanel* IsWithinTraverse(VPanel* vguiPanel, int x, int y, bool traversePopups) = 0;
		virtual void OnChildAdded(VPanel* vguiPanel, VPanel* child) = 0;
		virtual void OnSizeChanged(VPanel* vguiPanel, int newWide, int newTall) = 0;
		virtual void InternalFocusChanged(VPanel* vguiPanel, bool lost) = 0;
		virtual bool RequestInfo(VPanel* vguiPanel, KeyValues *outputData) = 0;
		virtual void RequestFocus(VPanel* vguiPanel, int direction = 0) = 0;
		virtual bool RequestFocusPrev(VPanel* vguiPanel, VPanel* existingPanel) = 0;
		virtual bool RequestFocusNext(VPanel* vguiPanel, VPanel* existingPanel) = 0;
		virtual VPanel* GetCurrentKeyFocus(VPanel* vguiPanel) = 0;
		virtual int GetTabPosition(VPanel* vguiPanel) = 0;
		virtual SurfacePlat *Plat(VPanel* vguiPanel) = 0;
		virtual void SetPlat(VPanel* vguiPanel, SurfacePlat *Plat) = 0;
		virtual Panel *GetPanel(VPanel* vguiPanel, const char *destinationModule) = 0;
		virtual bool IsEnabled(VPanel* vguiPanel) = 0;
		virtual void SetEnabled(VPanel* vguiPanel, bool state) = 0;
		virtual bool IsTopmostPopup(VPanel* vguiPanel) = 0;
		virtual void SetTopmostPopup(VPanel* vguiPanel, bool state) = 0;
		virtual void SetSiblingPin(VPanel* vguiPanel, VPanel* newSibling, byte iMyCornerToPin = 0, byte iSiblingCornerToPinTo = 0) = 0;
	};
};