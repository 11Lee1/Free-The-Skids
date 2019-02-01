QAngle ViewAngle = QAngle(0, 0, 0);
namespace HackVars
{
	CUserCmd* CurCmd = nullptr;

	float FOV = 90.0f;
	namespace Fonts
	{
		int DefaultFont = 0;
	};
	namespace convars
	{
		ConVar* FOV = nullptr;
	}
	namespace LastSentInfo
	{
		QAngle viewangles = QAngle(0, 0, 0);
		Vector Position = Vector(0, 0, 0);
	};
	namespace Aimbot
	{
		BaseEntity* AimbotTarget = nullptr;
		Vector AimbotPos = Vector(0, 0, 0);
		bool Enabled = true;
		bool Silent = true;

		int FOV = 30;
	};
	namespace Visuals
	{
		bool Enabled = true;
		namespace Aimbot
		{
			bool FOVCircle = true;
			bool DrawTarget = true;
		};
		namespace RenderView
		{
			bool ThirdPerson = false;
			int ThirdPersonDistance = 100;
			int FOV = 0;
			int ViewModelFOV = 0;
		};
		namespace ESP
		{
			//player 
			bool PlayerESP = true;

			bool PlayerBox = true;
			bool PlayerDrawname = true;
			bool PlayerDrawHealth = true;
			float fPBoxColor[4] = { 1, 1, 1, 1 };
			Color PBoxColor = Color(255, 255, 255, 255);

			bool PlayerChamsEnabled = true;
			bool PlayerXQZ = true;
			bool PlayerCFlat = true;
			float fVPlayerChamsColor[4] = { 0, 0.82f, 0, 0 };
			float fNVPlayerChamsColor[4] = { 0, 0, 1, 0 };

			// lua esp
			bool LuaESP = true;

			bool LuaBox = false;
			bool LuaDrawName = false;
			bool LuaDrawHealth = false;

			float fLBoxColor[4] = { 1, 1, 1, 1 };
			Color LBoxColor = Color(255, 255, 255, 255);

			bool LuaChamsEnabled = false;
			bool LuaXQZ = true;
			bool LuaCFlat = false;
			float fVLuaChamsColor[4] = { 1, 1, 1, 0 };
			float fNVLuaChamsColor[4] = { 1, 1, 1, 0 };

			// weapon esp
			bool WeaponESP = true;

			bool WeaponChamsEnabled = true;
			bool WeaponXQZ = true;
			bool WeaponCFlat = true;
			float fVWeapChamsColor[4] = { 1, 0, 0, 0 };
			float fNVWeapChamsColor[4] = { 1, 1, 0, 0 };
		};
	};
};