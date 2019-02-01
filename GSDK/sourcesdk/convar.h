class IConsoleDisplayFunc;
class ConCommandBase;
class ConCommand;
typedef int CVarDLLIdentifier_t;
class ICvarQuery;
class Color;
class ConVar
{
public:
	virtual				~ConVar() = 0;
	virtual	bool		IsCommand(void) const = 0;
	virtual bool		IsFlagSet(int flag) const = 0;
	virtual void		AddFlags(int flags) = 0;
	virtual const char*	GetName(void) const = 0;
	virtual const char* GetHelpText(void) const = 0;
	virtual bool		IsRegistered(void) const = 0;
	virtual CVarDLLIdentifier_t GetDLLIdentifier() const = 0;
	virtual void		CreateBase(const char *pName, const char *pHelpString = 0, int flags = 0) = 0;
	virtual void		Init() = 0;
	virtual void		SetValue(const char *value) = 0;
	virtual void		SetValue(float value) = 0;
	virtual void		SetValue(int value) = 0;
	virtual bool		ClampValue(float& value) = 0;
	virtual void		ChangeStringValue(const char *tempVal, float flOldValue) = 0;
public:
	const char* GetName()
	{
		return *(const char**)((uintptr_t)this + 0xC);
	}
	float GetFloat()
	{
		return *(float*)((uintptr_t)this + 0x2C);
	}
	int GetInt()
	{
		return *(int*)((uintptr_t)this + 0x30);
	}
};
typedef void(*FnChangeCallback_t)(ConVar *var, const char *pOldValue, float flOldValue);
class ICvar
{
public:
	// Iappsystem stuff
	virtual void Connect() = 0;
	virtual void Disconnect() = 0;
	virtual void QueryInterface() = 0;
	virtual void Init() = 0;
	virtual void Shutdown() = 0;


	virtual void AllocateDLLIdentifier() = 0;
	// Register, unregister commands
	virtual void			RegisterConCommand(ConCommandBase *pCommandBase) = 0;
	virtual void			UnregisterConCommand(ConCommandBase *pCommandBase) = 0;
	virtual void			UnregisterConCommands(CVarDLLIdentifier_t id) = 0;

	// If there is a +<varname> <value> on the command line, this returns the value.
	// Otherwise, it returns NULL.
	virtual const char* GetCommandLineValue(const char *pVariableName) = 0;

	// Try to find the cvar pointer by name
	virtual ConCommandBase *FindCommandBase(const char *name) = 0;
	virtual const ConCommandBase *FindCommandBase(const char *name) const = 0;
	virtual ConVar			*FindVar(const char *var_name) = 0;
	virtual const ConVar	*FindVar(const char *var_name) const = 0;
	virtual ConCommand		*FindCommand(const char *name) = 0;
	virtual const ConCommand *FindCommand(const char *name) const = 0;

	// Get first ConCommandBase to allow iteration
	virtual ConCommandBase	*GetCommands(void) = 0;
	virtual const ConCommandBase *GetCommands(void) const = 0;

	// Install a global change callback (to be called when any convar changes) 
	virtual void			InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void			RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void			CallGlobalChangeCallbacks(ConVar *var, const char *pOldString, float flOldValue) = 0;

	// Install a console printer
	virtual void			InstallConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
	virtual void			RemoveConsoleDisplayFunc(IConsoleDisplayFunc* pDisplayFunc) = 0;
	virtual void			ConsoleColorPrintf(const Color& clr, PRINTF_FORMAT_STRING const char *pFormat, ...) const = 0;
	virtual void			ConsolePrintf(PRINTF_FORMAT_STRING const char *pFormat, ...) const = 0;
	virtual void			ConsoleDPrintf(PRINTF_FORMAT_STRING const char *pFormat, ...) const = 0;

	// Reverts cvars which contain a specific flag
	virtual void	RevertFlaggedConVars(int nFlag) = 0;

	// Method allowing the engine ICvarQuery interface to take over
	// A little hacky, owing to the fact the engine is loaded
	// well after ICVar, so we can't use the standard connect pattern
	virtual void	InstallCVarQuery(ICvarQuery *pQuery) = 0;
};