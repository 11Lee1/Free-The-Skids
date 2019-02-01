class C_BaseCombatWeapon;
class CameraThirdData_t;
class CHandle;
struct kbutton_t
{
	// key nums holding it down
	int		down[2];
	// low bit is down state
	int		state;
};
class CKeyboardKey
{
public:
	// Name for key
	char				name[32];
	// Pointer to the underlying structure
	kbutton_t			*pkey;
	// Next key in key list.
	CKeyboardKey		*next;
};
enum
{
	GAME_AXIS_NONE = 0,
	GAME_AXIS_FORWARD,
	GAME_AXIS_PITCH,
	GAME_AXIS_SIDE,
	GAME_AXIS_YAW,
	MAX_GAME_AXES
};
enum
{
	CAM_COMMAND_NONE = 0,
	CAM_COMMAND_TOTHIRDPERSON = 1,
	CAM_COMMAND_TOFIRSTPERSON = 2
};
enum
{
	MOUSE_ACCEL_THRESHHOLD1 = 0,	// if mouse moves > this many mickey's double it
	MOUSE_ACCEL_THRESHHOLD2,		// if mouse moves > this many mickey's double it a second time
	MOUSE_SPEED_FACTOR,				// 0 = disabled, 1 = threshold 1 enabled, 2 = threshold 2 enabled

	NUM_MOUSE_PARAMS,
};
class ConVar;
class CVerifiedUserCmd
{
public:
	CUserCmd	m_cmd;
	CRC32_t		m_crc;
};

class CInput
{
public:
	virtual		void		Init_All(void) = 0;
	virtual		void		Shutdown_All(void) = 0;
	virtual		int			GetButtonBits(int) = 0;
	virtual		void		CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
	virtual		void		ExtraMouseSample(float frametime, bool active) = 0;
	virtual		bool		WriteUsercmdDeltaToBuffer(bf_write *buf, int from, int to, bool isnewcommand) = 0;
	virtual		void		EncodeUserCmdToBuffer(bf_write& buf, int slot) = 0;
	virtual		void		DecodeUserCmdFromBuffer(bf_read& buf, int slot) = 0;
	virtual		CUserCmd*	GetUserCmd(int sequence_number) = 0;
	virtual		void		MakeWeaponSelection(C_BaseCombatWeapon *weapon) = 0;
	virtual		float		KeyState(kbutton_t *key) = 0;
	virtual		int			KeyEvent(int down, ButtonCode_t keynum, const char *pszCurrentBinding) = 0;
	virtual		kbutton_t*	FindKey(const char *name) = 0;
	virtual		void		ControllerCommands(void) = 0;
	virtual		void		Joystick_Advanced(void) = 0;
	virtual		void		Joystick_SetSampleTime(float frametime) = 0;
	virtual		void		IN_SetSampleTime(float frametime) = 0;
	virtual		void		AccumulateMouse(void) = 0;
	virtual		void		ActivateMouse(void) = 0;
	virtual		void		DeactivateMouse(void) = 0;
	virtual		void		ClearStates(void) = 0;
	virtual		float		GetLookSpring(void) = 0;

	virtual		void		GetFullscreenMousePos(int *mx, int *my, int *unclampedx = NULL, int *unclampedy = NULL) = 0;
	virtual		void		SetFullscreenMousePos(int mx, int my) = 0;
	virtual		void		ResetMouse(void) = 0;

	//	virtual		bool		IsNoClipping( void );
	virtual		float		GetLastForwardMove(void) = 0;
	virtual		float		Joystick_GetForward(void) = 0;
	virtual		float		Joystick_GetSide(void) = 0;
	virtual		float		Joystick_GetPitch(void) = 0;
	virtual		float		Joystick_GetYaw(void) = 0;

	virtual		void		CAM_Think(void) = 0;
	virtual		int			CAM_IsThirdPerson(void) = 0;
	virtual		void		CAM_ToThirdPerson(void) = 0;
	virtual		void		CAM_ToFirstPerson(void) = 0;
	virtual		void		CAM_StartMouseMove(void) = 0;
	virtual		void		CAM_EndMouseMove(void) = 0;
	virtual		void		CAM_StartDistance(void) = 0;
	virtual		void		CAM_EndDistance(void) = 0;
	virtual		int			CAM_InterceptingMouse(void) = 0;

	// orthographic camera info
	virtual		void		CAM_ToOrthographic() = 0;
	virtual		bool		CAM_IsOrthographic() = 0;
	virtual		void		CAM_OrthographicSize(float& w, float& h) const = 0;
public:
	BYTE pad__01[136]; // 0x8B & m_fCameraMovingWithMouse = true thirdperson working
	// Is the 3rd person camera using the mouse?
	bool		m_fCameraInterceptingMouse;
	// Are we in 3rd person view?
	bool		m_fCameraInThirdPerson;
	// Should we move view along with mouse?
	bool		m_fCameraMovingWithMouse;


	// Is the camera in distance moving mode?
	bool		m_fCameraDistanceMove; // 37
	// Old and current mouse position readings.
	int			m_nCameraOldX; 
	int			m_nCameraOldY;
	int			m_nCameraX;
	int			m_nCameraY;

	// orthographic camera settings
	bool		m_CameraIsOrthographic; // 1

	QAngle		m_angPreviousViewAngles; // 12

	float		m_flLastForwardMove; // 4

	float m_flPreviousJoystickForward;
	float m_flPreviousJoystickSide;
	float m_flPreviousJoystickPitch;
	float m_flPreviousJoystickYaw;
	CUserCmd	*m_pCommands;
	CVerifiedUserCmd *m_pVerifiedCommands;

	CameraThirdData_t	*m_pCameraThirdData;
};