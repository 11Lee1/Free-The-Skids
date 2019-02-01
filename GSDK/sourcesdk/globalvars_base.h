class CSaveRestoreData;
class CGlobalVarsBase
{
public:
	bool	IsClient();
	int		GetNetworkBase(int nTick, int nEntity);
public:
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			curtime;
	float			frametime;
	int				maxClients;
	int				tickcount;
	float			interval_per_tick;
	float			interpolation_amount;
	int				simTicksThisFrame;
	int				network_protocol;
	CSaveRestoreData* pSaveData;
private:
	bool			m_bClient;
	int				nTimestampNetworkingBase;
	int				nTimestampRandomizeWindow;

};
inline int CGlobalVarsBase::GetNetworkBase(int nTick, int nEntity)
{
	int nEntityMod = nEntity % nTimestampRandomizeWindow;
	int nBaseTick = nTimestampNetworkingBase * (int)((nTick - nEntityMod) / nTimestampNetworkingBase);
	return nBaseTick;
}