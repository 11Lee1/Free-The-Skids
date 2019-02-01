typedef void(__thiscall* DrawModelExecuteFn)(IVModelRender*, DrawModelState_t &state, ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
DrawModelExecuteFn orgDrawModelExecute = nullptr;

void __fastcall hookDrawModelExecute(IVModelRender* modelrender, void* edx, DrawModelState_t &state, ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	if (pInfo.entity_index)
	{
		C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
		BaseEntity* Ent = (BaseEntity*)cliententitylist()->GetClientEntity(pInfo.entity_index);

		if(!Ent || Ent->IsWorld())
			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);

		float colormod[3];
		colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;

		IMaterial* DebugWhite = MaterialSystem()->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
		DebugWhite->AddRef();

		if (HackVars::Visuals::Enabled && HackVars::Visuals::ESP::PlayerESP && Ent != LocalPlayer && Ent->IsPlayer() && Ent->IsAlive())
		{
			if (HackVars::Visuals::ESP::PlayerXQZ)
			{
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, HackVars::Visuals::ESP::PlayerCFlat);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				colormod[0] = HackVars::Visuals::ESP::fNVPlayerChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fNVPlayerChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fNVPlayerChamsColor[2];
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(DebugWhite);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			}
			if (HackVars::Visuals::ESP::PlayerChamsEnabled)
			{
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, HackVars::Visuals::ESP::PlayerCFlat);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				colormod[0] = HackVars::Visuals::ESP::fVPlayerChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVPlayerChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVPlayerChamsColor[2];
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(DebugWhite);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(nullptr);
				return;
			}
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
			renderview()->SetColorModulation(colormod);
			ModelRender()->ForcedMaterialOverride(nullptr);
			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}
		else if (HackVars::Visuals::Enabled && HackVars::Visuals::ESP::LuaESP && Ent->UsesLua() && !Ent->IsPlayer() && !Ent->IsWeapon() && !Ent->IsHands())
		{
			if (HackVars::Visuals::ESP::LuaXQZ)
			{
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, HackVars::Visuals::ESP::LuaCFlat);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				colormod[0] = HackVars::Visuals::ESP::fNVLuaChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fNVLuaChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fNVLuaChamsColor[2];
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(DebugWhite);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			}
			if (HackVars::Visuals::ESP::LuaChamsEnabled)
			{
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, HackVars::Visuals::ESP::LuaCFlat);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				colormod[0] = HackVars::Visuals::ESP::fVLuaChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVLuaChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVLuaChamsColor[2];
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(DebugWhite);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(nullptr);
				return;
			}
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
			renderview()->SetColorModulation(colormod);
			ModelRender()->ForcedMaterialOverride(nullptr);

			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}
		else if (HackVars::Visuals::Enabled && HackVars::Visuals::ESP::WeaponESP && Ent->IsWeapon() && !Ent->IsHands())
		{
			if (HackVars::Visuals::ESP::WeaponXQZ)
			{
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, HackVars::Visuals::ESP::WeaponCFlat);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				colormod[0] = HackVars::Visuals::ESP::fNVWeapChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fNVWeapChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fNVWeapChamsColor[2];
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(DebugWhite);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			}
			if (HackVars::Visuals::ESP::WeaponChamsEnabled)
			{
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, HackVars::Visuals::ESP::WeaponCFlat);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				colormod[0] = HackVars::Visuals::ESP::fVWeapChamsColor[0]; colormod[1] = HackVars::Visuals::ESP::fVWeapChamsColor[1]; colormod[2] = HackVars::Visuals::ESP::fVWeapChamsColor[2];
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(DebugWhite);
				orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
				colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
				renderview()->SetColorModulation(colormod);
				ModelRender()->ForcedMaterialOverride(nullptr);
				return;
			}
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			colormod[0] = 1.f; colormod[1] = 1.f; colormod[2] = 1.f;
			renderview()->SetColorModulation(colormod);
			ModelRender()->ForcedMaterialOverride(nullptr);
			return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}



		if (Ent->IsHands()) {
			IMaterial* WireFrame = MaterialSystem()->FindMaterial("models/wireframe", TEXTURE_GROUP_MODEL);
			WireFrame->AddRef();

			float colormod[3];
			colormod[0] = 0; colormod[1] = 0.43; colormod[2] = 1;
			ModelRender()->ForcedMaterialOverride(WireFrame);
			renderview()->SetColorModulation(colormod);
			orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			ModelRender()->ForcedMaterialOverride(nullptr);
			colormod[0] = 1; colormod[1] = 1; colormod[2] = 1;
			renderview()->SetColorModulation(colormod);
			return;
		}
		else if (Ent == LocalPlayer) {
			LocalPlayer->InvalidateBoneCache();
			LocalPlayer->EyeAngles() = H::Util::Math::FixAngles(HackVars::LastSentInfo::viewangles);
			LocalPlayer->GetAnimState()->Update(LocalPlayer->EyeAngles().y, LocalPlayer->EyeAngles().x);
			matrix3x4_t bones[128];
			LocalPlayer->m_flPlaybackRate() = 0.0f;
			if (!LocalPlayer->SetupBones(bones, 128, BONE_USED_BY_ANYTHING, 0.0f)) {
				return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
			}
			return orgDrawModelExecute(modelrender, state, pInfo, bones);
		}
	}
	return orgDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
}