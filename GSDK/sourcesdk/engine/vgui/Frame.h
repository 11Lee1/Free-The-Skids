namespace vgui
{
	class Frame : public Panel
	{
	public:
		virtual ~Frame();
		Frame(Panel* Parent);
		Frame(Panel* Parent, char const* FrameName);


		void SetBGColor(Color color) { _bgcolor = color; }
		void SetBorderColor(Color color) { _bordercolor = color; }

	public:
		virtual void PaintBackground();
		virtual void PaintBorder();
		virtual void OnThink();
	protected:
		Color		_bgcolor;
		Color		_bordercolor;
	};

	void Frame::OnThink() {
		Panel::OnThink();

		if (IsMouseOver())
			SetCursor(_cursor);
	}
	void Frame::PaintBackground() {
		Panel::PaintBackground();

		int wide, tall;
		GetSize(wide, tall);

		DrawRect(0, 0, wide, tall, _bgcolor);	
	}

	void Frame::PaintBorder() {
		Panel::PaintBorder();

		int wide, tall;
		GetSize(wide, tall);

		DrawOutlinedRect(0, 0, wide, tall, _bordercolor);
	}
	Frame::Frame(Panel* parent) : Panel(parent) {
		_bgcolor = VALVE_LIGHT_GREY;
		_bordercolor = VALVE_BORDER;
		_flags.SetFlag(PAINT_BORDER_ENABLED);
	}
	Frame::Frame(Panel* parent, char const* FrameName) : Panel(parent, FrameName) {
		_bgcolor = VALVE_LIGHT_GREY;
		_bordercolor = VALVE_BORDER;
		_flags.SetFlag(PAINT_BORDER_ENABLED);
	}
	Frame::~Frame() {
		DeletePanel();
	}
};