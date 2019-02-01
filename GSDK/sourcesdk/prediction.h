class IPrediction {
public:
	virtual	~IPrediction(void) = 0;
	virtual void	Init(void) = 0;
	virtual void	Shutdown(void) = 0;
	virtual void	Update
	(
		int startframe,		// World update ( un-modded ) most recently received
		bool validframe,		// Is frame data valid
		int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command	// Last command (most recent) sent to server (un-modded)
	) = 0;
	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
	virtual void	PostEntityPacketReceived(void) = 0;
	virtual void	PostNetworkDataReceived(int commands_acknowledged) = 0;
	virtual void	OnReceivedUncompressedPacket(void) = 0;
	virtual void	GetViewOrigin(Vector& org) = 0;
	virtual void	SetViewOrigin(Vector& org) = 0;
	virtual void	GetViewAngles(QAngle& ang) = 0;
	virtual void	SetViewAngles(QAngle& ang) = 0;
	virtual void	GetLocalViewAngles(QAngle& ang) = 0;
	virtual void	SetLocalViewAngles(QAngle& ang) = 0;
	virtual bool	InPrediction(void) = 0;
	virtual bool	IsFirstTimePredicted(void) = 0;
	virtual int		GetIncomingPacketNumber(void) = 0;
	virtual void	RunCommand(BaseEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper) = 0;
	virtual void	SetupMove(BaseEntity *player, CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move) = 0;
	virtual void	FinishMove(BaseEntity *player, CUserCmd *ucmd, CMoveData *move) = 0;
	virtual void	SetIdealPitch(BaseEntity *player, const Vector& origin, const QAngle& angles, const Vector& viewheight) = 0;
	virtual void	_Update
	(
		bool received_new_world_update,
		bool validframe,		// Is frame data valid
		int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command	// Last command (most recent) sent to server (un-modded)
	) = 0;
};