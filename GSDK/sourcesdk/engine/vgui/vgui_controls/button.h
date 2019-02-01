void DrawRect(int x, int y, int w, int h, Color color)
{
	surface()->DrawSetColor(color);
	surface()->DrawFilledRect(x, y, x + w, y + h);
	surface()->DrawSetColor(Color(255, 255, 255, 255));
}
void DrawOutlinedRect(int x, int y, int w, int h, Color color)
{
	surface()->DrawSetColor(color);
	surface()->DrawOutlinedRect(x, y, x + w, y + h);
	surface()->DrawSetColor(Color(255, 255, 255, 255));
}
void Drawtext(char const* text = "Sample", int font = 1, int x = 0, int y = 0, Color color = Color(255, 255, 255, 255))
{
	const size_t cSize = strlen(text) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, text, cSize);
	surface()->DrawSetTextFont(font);
	surface()->DrawSetTextColor(color);
	surface()->DrawSetTextPos(x, y);
	surface()->DrawPrintText(wc, cSize - 1);
	surface()->DrawSetTextColor(255, 255, 255, 255);
}
namespace vgui
{
	class Button : public Panel
	{
	public:
		virtual ~Button();
		Button(Panel* parent);
		Button(Panel* parent, char const* name);

		virtual void DoPressed();
		virtual void DoClick();

	protected:
		virtual void OnThink();
		virtual void Paint();
	private:
		int pressedpos[2];
		bool pressed;
		bool mousepressedInPanel;
	};
	void Button::DoPressed() {

	}
	void Button::DoClick() {
		print("lol\n");
	}
	void Button::OnThink() {
		Panel::OnThink();



		if (vgui_Input()->IsMouseDown(MOUSE_LEFT) && pressed == false)
		{
			pressed = true;
			vgui_Input()->GetCursorPos(pressedpos[0], pressedpos[1]);
			if(IsVisible() && IsWithin(pressedpos[0], pressedpos[1]) && IsMouseOver())
				DoClick();
		}
		
		if (!vgui_Input()->IsMouseDown(MOUSE_LEFT))
		{
			pressed = false;
		}
	}
	void Button::Paint()
	{
		int wide, tall;
		GetSize(wide, tall);

		if (IsMouseOver())
			DrawRect(0, 0, wide, tall, VALVE_LIGHT_WHITE);
		else
			DrawRect(0, 0, wide, tall, VALVE_DARK_WHITE);
	}
	Button::Button(Panel* parent) : Panel(parent) {}
	Button::Button(Panel* parent, char const* name) : Panel(parent, name) {}

	Button::~Button() {
		DeletePanel();
	}
};