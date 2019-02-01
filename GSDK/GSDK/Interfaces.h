typedef void* (*CreateInterfaceFn)(const char *Name, int *ReturnCode);
class InterfaceReg
{
public:
	BYTE			m_CreateFn[4];
	const char		*m_pName;
	InterfaceReg	*m_pNext;
};
class IBaseInterface
{
public:
	virtual	~IBaseInterface() {}
};
class IClientDLLSharedAppSystems
{
public:
	virtual int	Count() = 0;
	virtual char const *GetDllName(int idx) = 0;
	virtual char const *GetInterfaceName(int idx) = 0;
};
class IAppSystem
{
public:
	virtual void		Nothing_Important__00() = 0;
	virtual void		Nothing_Important__01() = 0;
	virtual void		Nothing_Important__02() = 0;
	virtual void		Nothing_Important__03() = 0;
};
enum InitReturnVal_t
{
	INIT_FAILED = 0,
	INIT_OK,

	INIT_LAST_VAL,
};
class CAppSystemGroup; // look into later
struct StartupInfo_t
{
	void *m_pInstance;
	const char *m_pBaseDirectory;	// Executable directory ("c:/program files/half-life 2", for example)
	const char *m_pInitialMod;		// Mod name ("cstrike", for example)
	const char *m_pInitialGame;		// Root game name ("hl2", for example, in the case of cstrike)
	CAppSystemGroup *m_pParentAppSystemGroup;
	bool m_bTextMode;
};
class CEngineAPI
{
public:
	virtual bool Connect(CreateInterfaceFn factory) = 0;
	virtual void Disconnect() = 0;
	virtual void *QueryInterface(const char *pInterfaceName) = 0;
	virtual InitReturnVal_t Init() = 0;
	virtual void Shutdown() = 0;
	virtual void SetStartupInfo(StartupInfo_t &info) = 0;
	virtual int Run() = 0;
	virtual void SetEngineWindow(void *hWnd) = 0;
	virtual void PostConsoleCommand(const char *pConsoleCommand) = 0;
	virtual bool IsRunningSimulation() const = 0;
	virtual void ActivateSimulation(bool bActive) = 0;
	virtual void SetMap(const char *pMapName) = 0;
};

namespace vgui
{
	class IInput;
	class IInputInternal;
	class SurfacePlat;
	class IClientPanel;
	class Panel;
	class IScheme;
	class ISchemeManager;
	class IPanel;
	class IVGui;
	class ISystem;
};

class CUniformRandomStream;
class IBaseFileSystem;
class IFileSystem;
class IEngineVGui;
class CHLClient;
class CEngineClient;
class ClientEntityList;
class IPanel;
class ISurface;
class ClientMode;
class CGlobalVarsBase;
class CModelInfo;
class IDirect3DDevice9;
class RenderView;
class CEngineVGui;
class IRender;
class IViewRender;
class IMaterialSystem;
class IMatRenderContext;
class IInputSystem;
class IVModelRender;
class IEngineTrace;
class CInput;
class CLuaShared;
class IGameMovement;
class IPrediction;
class IMoveHelper;
class CBaseClientState;
class CIVPhysicsDebugOverlay;
class IPhysicsSurfaceProps;
class ICvar;
class CServerGameClients;
class CGameEventManager;
class IMemAlloc;
class IShaderAPI;
class Event_HitMarker;
namespace Interfaces
{
	namespace _I
	{
		CHLClient*					client;
		CEngineClient*				engine;
		ClientEntityList*			cliententlist;
		CEngineAPI*					EngineAPI;

		IEngineVGui*				EngineVGui;
		vgui::IPanel*				panel;
		vgui::IVGui*				IVGui;
		vgui::ISystem*				ISystem;
		vgui::ISchemeManager*		Scheme;
		vgui::IInput*				vgui_IInput;
		vgui::IInputInternal*		vgui_IInputInternal;

		IClientDLLSharedAppSystems* CLIENT_DLL_SHARED_APPSYSTEMS;
		CUniformRandomStream*		Random;
		IBaseFileSystem*			BaseFileSystem;
		IFileSystem*				FileSystem;
		ISurface*					surface;
		ClientMode*					clientmode;
		CGlobalVarsBase*			globalvars;
		CModelInfo*					modelinfo;
		IDirect3DDevice9*			d3ddevice;
		RenderView*					renderview;
		IViewRender*				viewrender;
		CEngineVGui*				cenginevgui;
		IRender*					render;
		IMaterialSystem*			materialsystem;
		IMatRenderContext*			MatRenderContext;
		IInputSystem*				InputSystem;
		IVModelRender*				ModelRender;
		IEngineTrace*				EngineTrace;
		CInput*						Input;
		CLuaShared*					LuaShared;
		IGameMovement*				GameMovement;
		IPrediction*				Prediction;
		IMoveHelper*				MoveHelper;
		CBaseClientState*			BaseClientState;
		CIVPhysicsDebugOverlay*		PhysicsDebugOverlay;
		IPhysicsSurfaceProps*		PhysicsSurfaceProps;
		ICvar*						cvar;
		CServerGameClients*			ServerGameClients;
		CGameEventManager*			GameEventManager;
		IMemAlloc*					MemAlloc;
		IShaderAPI*					ShaderAPI;
		Event_HitMarker*			HitMarkerEvent;
	};

	CHLClient* client() { return _I::client; }
	CEngineClient* engine() { return _I::engine; }

	ClientEntityList* cliententitylist() { return _I::cliententlist; }
	CEngineAPI* EngineAPI() { return _I::EngineAPI; }
	IEngineVGui* EngineVGui() { return _I::EngineVGui; }
	vgui::IPanel* IPanel() { return _I::panel; }
	vgui::IVGui* IVGui() { return _I::IVGui; }
	vgui::ISystem* ISystem() { return _I::ISystem; }
	vgui::ISchemeManager* Scheme() { return _I::Scheme; }
	vgui::IInput* vgui_Input() { return _I::vgui_IInput; }
	vgui::IInputInternal* vgui_InputInternal() { return _I::vgui_IInputInternal; }
	IClientDLLSharedAppSystems* CLIENT_DLL_SHARED_APPSYSTEMS() { return _I::CLIENT_DLL_SHARED_APPSYSTEMS; }
	CUniformRandomStream* Random() { return _I::Random; }
	IBaseFileSystem* BaseFileSystem() { return _I::BaseFileSystem; }
	IFileSystem* FileSystem() { return _I::FileSystem; }
	ISurface* surface() { return _I::surface; }
	ClientMode* clientmode() { return _I::clientmode; }
	CGlobalVarsBase* globals() { return _I::globalvars; }
	CModelInfo* ModelInfo() { return _I::modelinfo; }
	IDirect3DDevice9* D3DDevice() { return _I::d3ddevice; }
	RenderView* renderview() { return _I::renderview; }
	IViewRender* ViewRender() { return _I::viewrender; }
	CEngineVGui* cEngineVGui() { return _I::cenginevgui; }
	IRender* Render() { return _I::render; }
	IMaterialSystem* MaterialSystem() { return _I::materialsystem; }
	IMatRenderContext* MatRenderContext() { return _I::MatRenderContext; }
	IInputSystem* InputSystem() { return _I::InputSystem; }
	IVModelRender* ModelRender() { return _I::ModelRender; }
	IEngineTrace* EngineTrace() { return _I::EngineTrace; }
	CInput* Input() { return _I::Input; }
	CLuaShared* LuaShared() { return _I::LuaShared; }
	IGameMovement* GameMovement() { return _I::GameMovement; }
	IPrediction* Prediction() { return _I::Prediction; }
	IMoveHelper* MoveHelper() { return _I::MoveHelper; }
	CBaseClientState* BaseClientState() { return _I::BaseClientState; }
	CIVPhysicsDebugOverlay* PhysicsDebugOverlay() { return _I::PhysicsDebugOverlay; }
	IPhysicsSurfaceProps* PhysicsSurfaceProps() { return _I::PhysicsSurfaceProps; }
	ICvar* CVar() { return _I::cvar; }
	CServerGameClients* ServerGameClients() { return _I::ServerGameClients; }
	CGameEventManager* GameEventManager() { return _I::GameEventManager; }
	IMemAlloc* MemAlloc() { return _I::MemAlloc; }
	IShaderAPI* ShaderAPI() { return _I::ShaderAPI; }




	void* _GetInterface(const char* Module, const char* InterfaceName)
	{
		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(Module), "CreateInterface");

		return (void*)CreateInterface(InterfaceName, NULL);
	}
	void _SetupInterfaces()
	{
		_I::client = (CHLClient*)_GetInterface("client.dll", "VClient017");
		_I::engine = (CEngineClient*)_GetInterface("engine.dll", "VEngineClient015");
		_I::cliententlist = (ClientEntityList*)_GetInterface("client.dll", "VClientEntityList003");

		_I::panel = (vgui::IPanel*)_GetInterface("vgui2.dll", "VGUI_Panel009");
		_I::IVGui = (vgui::IVGui*)_GetInterface("vgui2.dll", "VGUI_ivgui008");
		_I::ISystem = (vgui::ISystem*)_GetInterface("vgui2.dll", "VGUI_System010");
		_I::surface = (ISurface*)_GetInterface("vguimatsurface", "VGUI_Surface030");
		_I::Scheme = (vgui::ISchemeManager*)_GetInterface("vgui2.dll", "VGUI_Scheme010");
		_I::vgui_IInput = (vgui::IInput*)_GetInterface("vgui2.dll", "VGUI_Input005");
		_I::vgui_IInputInternal = (vgui::IInputInternal*)_GetInterface("vgui2.dll", "VGUI_InputInternal001");



		_I::BaseFileSystem = (IBaseFileSystem*)_GetInterface("filesystem_stdio.dll", "VBaseFileSystem011");
		_I::FileSystem = (IFileSystem*)_GetInterface("filesystem_stdio.dll", "VFileSystem022");

		_I::CLIENT_DLL_SHARED_APPSYSTEMS = (IClientDLLSharedAppSystems*)_GetInterface("client.dll", "VClientDllSharedAppSystems001");


		_I::EngineAPI = (CEngineAPI*)_GetInterface("engine.dll", "VENGINE_LAUNCHER_API_VERSION004");
		_I::EngineVGui = (IEngineVGui*)_GetInterface("engine.dll", "VEngineVGui001");


		_I::modelinfo = (CModelInfo*)_GetInterface("engine.dll", "VModelInfoClient006");
		_I::renderview = (RenderView*)_GetInterface("engine.dll", "VEngineRenderView014");
		_I::materialsystem = (IMaterialSystem*)_GetInterface("materialsystem.dll", "VMaterialSystem080");
		_I::InputSystem = (IInputSystem*)_GetInterface("inputsystem.dll", "InputSystemVersion001");
		_I::ModelRender = (IVModelRender*)_GetInterface("engine.dll", "VEngineModel016");
		_I::EngineTrace = (IEngineTrace*)_GetInterface("engine.dll", "EngineTraceClient003");
		_I::PhysicsDebugOverlay = (CIVPhysicsDebugOverlay*)_GetInterface("engine.dll", "VPhysicsDebugOverlay001");
		_I::PhysicsSurfaceProps = (IPhysicsSurfaceProps*)_GetInterface("vphysics.dll", "VPhysicsSurfaceProps001");
		_I::cvar = (ICvar*)_GetInterface("vstdlib.dll", "VEngineCvar004");
		_I::ShaderAPI = (IShaderAPI*)_GetInterface("shaderapidx9.dll", "ShaderApi030");
		_I::GameEventManager = (CGameEventManager*)_GetInterface("engine.dll", "GAMEEVENTSMANAGER002");
		_I::GameMovement = (IGameMovement*)_GetInterface("client.dll", "GameMovement001");
		_I::Prediction = (IPrediction*)_GetInterface("client.dll", "VClientPrediction001");
		_I::MoveHelper = **(IMoveHelper***)(Util::Pattern::FindPattern("client.dll", "8B 0D ? ? ? ? 8B 46 08 68") + 0x2);
		_I::LuaShared = (CLuaShared*)_GetInterface("lua_shared.dll", "LUASHARED003");
		_I::ServerGameClients = **(CServerGameClients***)(Util::Pattern::FindPattern("engine.dll", "8B 0D ?? ?? ?? ?? FF 75 F8 D9 1D ?? ?? ?? ??") + 0x2);


		_I::MemAlloc = *(IMemAlloc**)GetProcAddress(GetModuleHandleA("tier0.dll"), "g_pMemAlloc");

		_I::BaseClientState = *(CBaseClientState**)((*(uintptr_t**)_I::engine)[84] + 1);
		//https://gyazo.com/bd8a8ff6954c10c2cbb282ad3be6fb1a
		_I::Input = **(CInput***)((*(uintptr_t**)_I::client)[14] + 0x2);
		//https://gyazo.com/24bd0072301f9c8dd5aeccae36060162
		_I::globalvars = **(CGlobalVarsBase***)((*(uintptr_t**)_I::client)[0] + 0x55);
		//https://gyazo.com/3e0317e5c7846d619f7b2df7b19a6612
		_I::clientmode = **(ClientMode***)((*(uintptr_t**)_I::client)[10] + 0x5);

		//https://gyazo.com/f1e7ea6cce0f9b00081fdac1c9945a77
		_I::d3ddevice = **(IDirect3DDevice9***)(Util::Pattern::FindPattern("shaderapidx9.dll", "55 8B EC 51 56 8B F1 83 7E 24 00") + 0x2B);


		//https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/ivrenderview.h#L253
		//https://gyazo.com/29fb21c0e0abb38de5d9641771750c6f
		//https://gyazo.com/08322dbe3547be437462d4dafef619e3
		//https://gyazo.com/d4b482bebda0f6d2648058416e674085
		_I::cenginevgui = (CEngineVGui*)(int(__stdcall ***)(BYTE))((*(uintptr_t**)_I::renderview)[23] + 1);

		// https://gyazo.com/b820eeb2498fb4cba6b848893d2448f0
		// https://gyazo.com/d10ebf84afd112151861498c5f23536b
		_I::render = **(IRender***)((*(uintptr_t**)_I::renderview)[12] + 0x5);

		// https://gyazo.com/2f17bccc068c5e9cb316ba6eecc7b40f
		_I::viewrender = **(IViewRender***)((*(uintptr_t**)_I::client)[27] + 0x5);


		
		void* RandomSeed = *(void**)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed");
		if (RandomSeed)
			_I::Random = **(CUniformRandomStream***)((uintptr_t)RandomSeed + 0x5);
	}
	void _printInterfaceAddresses()
	{
		// IClientDLLSharedAppSystems
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IClientDLLSharedAppSystems            = ");
		print("0x%X\n", _I::CLIENT_DLL_SHARED_APPSYSTEMS);


		// CHLClient
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "CHLClient            = ");
		print("0x%X\n", _I::client);

		// Engine
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IEnine               = ");
		print("0x%X\n", _I::engine);

		// ClientEntityList
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IClientEntList       = ");
		print("0x%X\n", _I::cliententlist);

		// ISystem
		printColor(COLOR_YELLOW, "[SYSTEM] ");    //
		printColor(COLOR_PURPLE, "ISystem              = ");
		print("0x%X\n", _I::ISystem);

		// IScheme
		printColor(COLOR_YELLOW, "[SYSTEM] ");    //
		printColor(COLOR_PURPLE, "IScheme              = ");
		print("0x%X\n", _I::Scheme);

		// vgui::IInput
		printColor(COLOR_YELLOW, "[SYSTEM] ");    //
		printColor(COLOR_PURPLE, "vgui::IInput         = ");
		print("0x%X\n", _I::vgui_IInput);

		// vgui::IInputInternal
		printColor(COLOR_YELLOW, "[SYSTEM] ");    //
		printColor(COLOR_PURPLE, "vgui::IInputInternal = ");
		print("0x%X\n", _I::vgui_IInputInternal);

		// IPanel
		printColor(COLOR_YELLOW, "[SYSTEM] ");    //
		printColor(COLOR_PURPLE, "IPanel               = ");
		print("0x%X\n", _I::panel);

		// IVGui
		printColor(COLOR_YELLOW, "[SYSTEM] ");    //
		printColor(COLOR_PURPLE, "IVGui                = ");
		print("0x%X\n", _I::IVGui);

		// ISurface
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "ISurface             = ");
		print("0x%X\n", _I::surface);

		// IClientMode
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IClientMode          = ");
		print("0x%X\n", _I::clientmode);


		// CGlobalVarsBase
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "GlobalVarsBase       = ");
		print("0x%X\n", _I::globalvars);


		// CModelInfo
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "ModelInfo            = ");
		print("0x%X\n", _I::modelinfo);

		// IDirect3DDevice9
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IDirect3DDevice9     = ");
		print("0x%X\n", _I::d3ddevice);

		// RenderView
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "RenderView           = ");
		print("0x%X\n", _I::renderview);

		// CEngineVGui
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "EngineVGui           = ");
		print("0x%X\n", _I::cenginevgui);

		// IRender
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IRender              = ");
		print("0x%X\n", _I::render);

		// ViewRender
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "ViewRender           = ");
		print("0x%X\n", _I::viewrender);

		// IMaterialSystem
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IMaterialSystem      = ");
		print("0x%X\n", _I::materialsystem);

		// IMatRenderContext
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IMatRenderContext    = ");
		print("0x%X\n", _I::MatRenderContext);

		// IInputSystem
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IInputSystem         = ");
		print("0x%X\n", _I::InputSystem);

		// IIEngineTrace
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IIEngineTrace        = ");
		print("0x%X\n", _I::EngineTrace);

		// CInput
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IInput               = ");
		print("0x%X\n", _I::Input);

		// ILuaShared
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "ILuaShared           = ");
		print("0x%X\n", _I::LuaShared);



		// IGameMovement
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IGameMovement        = ");
		print("0x%X\n", _I::GameMovement);

		// IPrediction
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IPrediction          = ");
		print("0x%X\n", _I::Prediction);

		// IMoveHelper
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IMoveHelper          = ");
		print("0x%X\n", _I::MoveHelper);

		// CBaseClientState
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "BaseClientState      = ");
		print("0x%X\n", _I::BaseClientState); // 148

		// PhysicsDebugOverlay
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "PhysicsDebugOverlay  = ");
		print("0x%X\n", _I::PhysicsDebugOverlay); // 148

		// PhysicsSurfaceProps
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "PhysicsSurfaceProps  = ");
		print("0x%X\n", _I::PhysicsSurfaceProps); // 148

		// cvar
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "EngineCvar           = ");
		print("0x%X\n", _I::cvar); // 148


		// CServerGameClients
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "ServerGameClients    = ");
		print("0x%X\n", _I::ServerGameClients); // 148

		// GameEventManager
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "GameEventManager     = ");
		print("0x%X\n", _I::GameEventManager); // 148

		// IMemAlloc
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IMemAlloc            = ");
		print("0x%X\n", _I::MemAlloc); // 148


		// IShaderAPI
		printColor(COLOR_YELLOW, "[SYSTEM] ");
		printColor(COLOR_PURPLE, "IShaderAPI           = ");
		print("0x%X\n", _I::ShaderAPI); // 148
	}
};
using namespace Interfaces;
