class IMoveHelper;

class CPredictionSystem {
public:
	void StartPrediction(CUserCmd* cmd);
	void EndPrediction(CUserCmd* cmd);

private:
	float m_flOldCurtime;
	float m_flOldFrametime;
	CMoveData m_MoveData = { };


	CUserCmd* m_current_cmd;
	int* m_pPredictionRandomSeed;
}; CPredictionSystem PredictionSystem;
void CPredictionSystem::StartPrediction(CUserCmd* cmd)
{
	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());

	static bool bInit = false;
	if (!bInit) {
		// https://gyazo.com/39dea3718a1c3e865c711eb493d93b5b
		// https://gyazo.com/20890d3a7fa8ea3bc898f5ec5c9ddf5d
		// https://gyazo.com/72bf0fd31e31b14f5ed0246fb03d76a6
		// https://gyazo.com/6b1ecd0bdc50a1023ade27cfd1f6b4c4
		m_pPredictionRandomSeed = *(int**)(Util::Pattern::FindPattern("client.dll", "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 5D C3 8B 40 30") + 0x2);
		bInit = true;
	}

	*m_pPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

	m_flOldCurtime = globals()->curtime;
	m_flOldFrametime = globals()->frametime;


	globals()->curtime = LocalPlayer->m_nTickBase() * globals()->interval_per_tick;
	globals()->frametime = globals()->interval_per_tick;

	GameMovement()->StartTrackPredictionErrors(LocalPlayer);

	memset(&m_MoveData, 0, sizeof(m_MoveData));
	Prediction()->SetupMove(LocalPlayer, cmd, MoveHelper(), &m_MoveData);
	GameMovement()->ProcessMovement(LocalPlayer, &m_MoveData);
	Prediction()->FinishMove(LocalPlayer, cmd, &m_MoveData);

}
void CPredictionSystem::EndPrediction(CUserCmd* cmd)
{
	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
	GameMovement()->FinishTrackPredictionErrors(LocalPlayer);

	*m_pPredictionRandomSeed = -1;
	m_current_cmd = nullptr;

	globals()->curtime = m_flOldCurtime;
	globals()->frametime = m_flOldFrametime;
}