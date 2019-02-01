typedef void(__thiscall* PaintTraverseFn)(void*, vgui::VPanel*, bool, bool);
PaintTraverseFn orgPaintTraverse = nullptr;

void __fastcall hkPaintTraverse(void* ecx, void* edx, vgui::VPanel* vguiPanel, bool forceRepaint, bool allowForce)
{
	orgPaintTraverse(ecx, vguiPanel, forceRepaint, allowForce);


	if (!engine()->IsInGame() || (strcmp(Interfaces::IPanel()->GetName(vguiPanel), "HudGMOD")))
		return;


	BaseEntity* LocalPlayer = (BaseEntity*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());

	if (!LocalPlayer)
		return;


	Interfaces::_I::HitMarkerEvent->Paint();

	if (HackVars::Visuals::Aimbot::FOVCircle)
		H::ESP::FovCircle(HackVars::Aimbot::FOV);

	if (HackVars::Visuals::Aimbot::DrawTarget)
		H::ESP::DrawAimbotTarget();

	for (int i = globals()->maxClients; i < cliententitylist()->GetHighestEntityIndex(); i++)
	{
		BaseEntity* ent = (BaseEntity*)cliententitylist()->GetClientEntity(i);
		if (!ent || ent->IsDormant())
			continue;

		if ((ent->UsesLua() && !ent->hasowner() && (HackVars::Visuals::ESP::LuaBox || HackVars::Visuals::ESP::LuaDrawHealth || HackVars::Visuals::ESP::LuaDrawName)))
			H::ESP::DrawBoundingBox(ent);
	}


	for (int i = 1; i <= globals()->maxClients; i++)
	{
		C_GMOD_Player* player = (C_GMOD_Player*)cliententitylist()->GetClientEntity(i);
		if (!player || !player->IsPlayer() || player->IsDormant())
			continue;

		if (player == LocalPlayer || !player->IsAlive())
			continue;

		if (player->ShouldDraw()) {
			if(HackVars::Visuals::ESP::PlayerBox || HackVars::Visuals::ESP::PlayerDrawHealth || HackVars::Visuals::ESP::PlayerDrawHealth)
				H::ESP::DrawBoundingBox(player);
		}
	}
}
