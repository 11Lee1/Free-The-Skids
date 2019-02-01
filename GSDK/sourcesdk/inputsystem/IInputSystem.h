#define INVALID_USER_ID	-1
#define JOYSTICK_AXIS_INTERNAL( _joystick, _axis ) ( JOYSTICK_FIRST_AXIS + ((_joystick) * MAX_JOYSTICK_AXES) + (_axis) )
#define JOYSTICK_AXIS( _joystick, _axis ) ( (AnalogCode_t)JOYSTICK_AXIS_INTERNAL( _joystick, _axis ) )

enum
{
	MAX_JOYSTICKS = 1,
	MOUSE_BUTTON_COUNT = 5,
	MAX_NOVINT_DEVICES = 2,
};
enum JoystickAxis_t
{
	JOY_AXIS_X = 0,
	JOY_AXIS_Y,
	JOY_AXIS_Z,
	JOY_AXIS_U,
	JOY_AXIS_R,
	JOY_AXIS_V,
	MAX_JOYSTICK_AXES,
};
enum AnalogCode_t
{
	ANALOG_CODE_INVALID = -1,
	MOUSE_X = 0,
	MOUSE_Y,
	MOUSE_XY,		// Invoked when either x or y changes
	MOUSE_WHEEL,

	JOYSTICK_FIRST_AXIS,
	JOYSTICK_LAST_AXIS = JOYSTICK_AXIS_INTERNAL(MAX_JOYSTICKS - 1, MAX_JOYSTICK_AXES - 1),

	ANALOG_CODE_LAST,
};
class IInputSystem
{
public:
	// didn't need more than this do this yourself if you want.
	virtual void not_important_00() = 0;
	virtual void not_important_01() = 0;
	virtual void not_important_02() = 0;
	virtual void not_important_03() = 0;
	virtual void not_important_04() = 0;
	virtual void AttachToWindow(void* hWnd) = 0;
	virtual void DetachFromWindow() = 0;
	virtual void EnableInput(bool bEnable) = 0;
	virtual void EnableMessagePump(bool bEnable) = 0;
	virtual void PollInputState() = 0;
	virtual int GetPollTick() const = 0;
	virtual bool IsButtonDown(ButtonCode_t code) const = 0;
	virtual int GetButtonPressedTick(ButtonCode_t code) const = 0;
	virtual int GetButtonReleasedTick(ButtonCode_t code) const = 0;
	virtual int GetAnalogValue(AnalogCode_t code) const = 0;
	virtual int GetAnalogDelta(AnalogCode_t code) const = 0;
	virtual int GetEventCount() const = 0;
	virtual const InputEvent_t* GetEventData() const = 0;
	virtual void PostUserEvent(const InputEvent_t &event) = 0;
	virtual int GetJoystickCount() const = 0;
	virtual void EnableJoystickInput(int nJoystick, bool bEnable) = 0;
	virtual void EnableJoystickDiagonalPOV(int nJoystick, bool bEnable) = 0;
	virtual void SampleDevices(void) = 0;
	virtual void SetRumble(float fLeftMotor, float fRightMotor, int userId = INVALID_USER_ID) = 0;
	virtual void StopRumble(void) = 0;
	virtual void ResetInputState() = 0;
	virtual void SetPrimaryUserId(int userId) = 0;
	virtual const char *ButtonCodeToString(ButtonCode_t code) const = 0;
	virtual const char *AnalogCodeToString(AnalogCode_t code) const = 0;
	virtual ButtonCode_t StringToButtonCode(const char *pString) const = 0;
	virtual AnalogCode_t StringToAnalogCode(const char *pString) const = 0;
	virtual void SleepUntilInput(int nMaxSleepTimeMS = -1) = 0;
	virtual ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey) const = 0;
	virtual int ButtonCodeToVirtualKey(ButtonCode_t code) const = 0;
	virtual ButtonCode_t ScanCodeToButtonCode(int lParam) const = 0;
	virtual int GetPollCount() const = 0;
	virtual void SetCursorPosition(int x, int y) = 0;
	virtual void *GetHapticsInterfaceAddress() const = 0;
	virtual void SetNovintPure(bool bPure) = 0;
	virtual bool GetRawMouseAccumulators(int& accumX, int& accumY) = 0;
	virtual void SetConsoleTextMode(bool bConsoleTextMode) = 0;
};