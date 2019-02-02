typedef bool(__thiscall* CreateMoveFn)(void*, float, CUserCmd*);
CreateMoveFn orgCreateMove = nullptr;



bool __fastcall hookCreateMove(ClientMode* ClientMode, void* edx, float flInputSampleTime, CUserCmd* cmd)
{
	if (!cmd)
		return false;
	C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());


	ViewAngle = cmd->viewangles;
	if (cmd->command_number == 0 || !engine()->IsInGame() || !LocalPlayer || !LocalPlayer->IsAlive()) {
		orgCreateMove(ClientMode, flInputSampleTime, cmd);
		return false;
	}
	static int ChokedCommands = 0;
	bool ForcedPacket = false;

	if (ChokedCommands >= 13)
		ForcedPacket = true;


	HackVars::CurCmd = cmd;

	DWORD move;
	_asm mov move, ebp;
	bool& sendpacket = *(***(bool****)(move)-1);


	CBaseCombatWeapon* weapon = LocalPlayer->GetActiveWeapon();
	QAngle viewpunchangle = LocalPlayer->m_vecViewPunch();
	bool HoldingTool = H::Util::IsHoldingTool();

	H::Bhop(cmd);

	PredictionSystem.StartPrediction(cmd);
	
	
	QAngle SpreadAngle = H::SpreadAngle(cmd);
	if (LocalPlayer->GetActiveWeapon()->CanShoot() && cmd->buttons.IsFlagSet(IN_ATTACK) && !HoldingTool)
		cmd->viewangles += SpreadAngle;


	C_GMOD_Player* Target = nullptr;
	QAngle TargetAngle = QAngle(0, 0, 0);
	bool Aim = false;
	if (InputSystem()->IsButtonDown(KEY_LALT) && HackVars::Aimbot::Enabled && !HoldingTool && !ForcedPacket) {
		if (H::ClosestTargetToCrosshair(cmd, Target, TargetAngle) && LocalPlayer->GetActiveWeapon()->CanShoot()) {
			cmd->viewangles = TargetAngle + SpreadAngle;
			cmd->buttons.SetFlag(IN_ATTACK);
			H::Util::CorrectMovement(cmd, ViewAngle);
			Aim = true;
		}
	}
	HackVars::Aimbot::AimbotTarget = Target;




	cmd->viewangles = H::Util::Math::FixAngles(cmd->viewangles);
	PredictionSystem.EndPrediction(cmd);
	orgCreateMove(ClientMode, flInputSampleTime,cmd);




	if (ForcedPacket)
		sendpacket = true;

	if (sendpacket) {
		HackVars::LastSentInfo::Position = LocalPlayer->GetRenderOrigin();
		HackVars::LastSentInfo::viewangles = cmd->viewangles;
		ChokedCommands = 0;
	}
	else
		ChokedCommands++;

	if(Aim)
		return !HackVars::Aimbot::Silent;
	return false;
};
