namespace vgui
{
	class CheckBox : public Button
	{
	public:
		virtual ~CheckBox();
		CheckBox(Panel* Parent,int width = 72);

		void SetText(char const* Text);
		virtual void DoClick();
	protected:
		virtual void OnThink();
		virtual void Paint();
		virtual void PaintBorder();
	private:
		char* CheckBoxText;
		bool checked;
	};
	void CheckBox::DoClick()
	{
		checked = !checked;
		print("checked: %i\n", checked);
	}
	void CheckBox::OnThink()
	{
		Button::OnThink();

	}
	void CheckBox::PaintBorder()
	{
		DrawOutlinedRect(6, 6, 12, 12, VALVE_DARK_BORDER);
	}
	void CheckBox::SetText(char const* Text) {
		if (CheckBoxText && Text && !strcmp(CheckBoxText, Text))
		{
			return;
		}

		if (CheckBoxText)
		{
			delete[] CheckBoxText;
			CheckBoxText = NULL;
		}

		if (Text)
		{
			int len = strlen(Text) + 1;
			CheckBoxText = new char[len];
			strcpy_s(CheckBoxText, len, Text);
		}
	}

	void CheckBox::Paint()
	{
		if(IsMouseOver())
			DrawRect(6, 6, 12, 12, VALVE_LIGHT_WHITE);
		else
			DrawRect(6, 6, 12, 12, VALVE_DARK_WHITE);

		if (checked)
		{
			Drawtext("a", 35, 5, 5, VALVE_CHECKBOX_GREEN); // marlett font
		}
		if (CheckBoxText)
		{
			Drawtext(CheckBoxText,11,24,4,VALVE_DARK_WHITE);
		}
	}
	CheckBox::CheckBox(Panel* Parent,int width) : Button(Parent)
	{
		// default height is nice change this up if you want idc
		SetSize(24 + width, 24);
	}
	CheckBox::~CheckBox()
	{
		DeletePanel();
	}
};