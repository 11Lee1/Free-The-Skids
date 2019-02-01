namespace H
{


	QAngle SpreadAngle(CUserCmd* cmd)
	{
		C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());

		Vector SpreadCone = LocalPlayer->GetActiveWeapon()->GetBulletSpread();
		float Spread = FloatNegate((SpreadCone.x + SpreadCone.y + SpreadCone.z) / 3);
		
		float Random[2];
		unsigned int seed = MD5_PseudoRandom(cmd->command_number) & 0xFF;
		Interfaces::Random()->SetSeed(seed);

		Random[0] = Interfaces::Random()->RandomFloat(-0.5f, 0.5f) + Interfaces::Random()->RandomFloat(-0.5f, 0.5f);
		Random[1] = Interfaces::Random()->RandomFloat(-0.5f, 0.5f) + Interfaces::Random()->RandomFloat(-0.5f, 0.5f);

		Vector ShootDirection = Vector(1.0f, 0.0f, 0.0f) + (Vector(0.0f, -1.0f, 0.0f) * Spread * Random[0]) + (Vector(0.0f, 0.0f, 1.0f) * Spread * Random[1]); // 0,0,0

		QAngle out = H::Util::Math::GetAngle(Vector(0, 0, 0), ShootDirection);
		out = H::Util::Math::FixAngles(out);
		return out;
	}
	void Bhop(CUserCmd* cmd)
	{
		C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
		if (!LocalPlayer->GetFlags().IsFlagSet(FL_ONGROUND) && cmd->buttons.IsFlagSet(IN_JUMP))
			cmd->buttons.ClearFlag(IN_JUMP);
	}

	bool ClosestTargetToCrosshair(CUserCmd* cmd, C_GMOD_Player*& Target,QAngle& OutAngle)
	{
		C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
		if (!LocalPlayer || !cmd || !LocalPlayer->IsAlive())
			return false;

		Vector2D AngVec2D = Vector2D(H::Util::Math::AngleNormalizePositive(cmd->viewangles.x), H::Util::Math::AngleNormalizePositive(cmd->viewangles.y));


		bool foundplayer = false;
		float TargetDistance = 720.0f;
		for (int i = 1; i <= globals()->maxClients; i++) {
			C_GMOD_Player* player = (C_GMOD_Player*)cliententitylist()->GetClientEntity(i);

			if (!player || player == LocalPlayer || !player->IsPlayer() || !player->IsAlive())
				continue;


			player->InvalidateBoneCache();
			matrix3x4_t bones[128];
			if (!player->SetupBones(bones, 128, BONE_USED_BY_HITBOX, globals()->curtime))
				continue;

			Vector AimPos = Vector(0, 0, 0);
			int aimjoint = player->LookupBone(Joints::Head);
			if (!Util::CenterOfHitbox(player, bones, (aimjoint >= 0) ? aimjoint : 0, AimPos)) {
				Vector Pos = player->GetRenderOrigin();
				Vector mins = Pos + player->CollisionMins(); Vector maxs = Pos + player->CollisionMaxs();
				AimPos = (mins + maxs) * 0.5;
			}

			if (!Util::IsVisible(player, AimPos))
				continue;

			QAngle AimAngle = H::Util::Math::GetAngle(LocalPlayer->EyePosition(), AimPos);

			Vector2D lol = Vector2D(AngVec2D.x + H::Util::Math::AngleDifference(AngVec2D.x, AimAngle.x), AngVec2D.y + H::Util::Math::AngleDifference(AngVec2D.y, AimAngle.y));
			float DistToCross = AngVec2D.DistTo(lol);
			if ((Target == nullptr || DistToCross < TargetDistance) && DistToCross < HackVars::Aimbot::FOV) {
				Target = player;
				TargetDistance = DistToCross;
				OutAngle = AimAngle;
				foundplayer = true;
				HackVars::Aimbot::AimbotPos = AimPos;
			}
		}
		return foundplayer;
	}


};