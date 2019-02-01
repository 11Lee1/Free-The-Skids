namespace Menu
{
	bool initialised = false;
	bool opened = false;
	bool InsertDown = false;
	int n_open = 0;


	void DrawMenu()
	{
		ImGui::GetIO().MouseDrawCursor = 0;

		if (!opened)
			return;

		if (ImGui::Begin("Menu", &opened, ImVec2(350, 500), 1.0f, ImGuiWindowFlags_NoResize))
		{
			ImGui::GetIO().MouseDrawCursor = 1;

			if (ImGui::CollapsingHeader("Aimbot", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Spacing();
				ImGui::Checkbox("Enable Aimbot (LALT the key)", &HackVars::Aimbot::Enabled);
				ImGui::Spacing(); ImGui::Spacing();

				ImGui::Checkbox("Silent Aim", &HackVars::Aimbot::Silent);
				ImGui::SliderInt("Aimbot FOV", &HackVars::Aimbot::FOV, 0, 360);
			}
			if (ImGui::CollapsingHeader("Visuals", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Checkbox("Enable ", &HackVars::Visuals::Enabled);
				if (ImGui::CollapsingHeader("RenderView"))
				{
					ImGui::Spacing();
					ImGui::Checkbox("ThirdPerson (F6)", &HackVars::Visuals::RenderView::ThirdPerson);
					ImGui::SliderInt("ThirdPerson Distance", &HackVars::Visuals::RenderView::ThirdPersonDistance, 0, 500);
					ImGui::SliderInt("FOV", &HackVars::Visuals::RenderView::FOV, 0, 180);
					ImGui::SliderInt("Viewmodel FOV", &HackVars::Visuals::RenderView::ViewModelFOV, 0, 180);
				}
				if (ImGui::CollapsingHeader("Aimbot "))
				{
					ImGui::Spacing();
					ImGui::Checkbox("FOV Circle", &HackVars::Visuals::Aimbot::FOVCircle);
				}
				if (ImGui::CollapsingHeader("Player"))
				{
					ImGui::Spacing();
					ImGui::Checkbox("Enable Player ESP", &HackVars::Visuals::ESP::PlayerESP);
					ImGui::Spacing(); ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
					ImGui::Checkbox("Draw Box", &HackVars::Visuals::ESP::PlayerBox);
					ImGui::Checkbox("Draw Name", &HackVars::Visuals::ESP::PlayerDrawname);
					ImGui::SameLine();
					ImGui::Checkbox("Draw Health", &HackVars::Visuals::ESP::PlayerDrawHealth);
					ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
					ImGui::Checkbox("Chams", &HackVars::Visuals::ESP::PlayerChamsEnabled);
					ImGui::SameLine();
					ImGui::Checkbox("XQZ", &HackVars::Visuals::ESP::PlayerXQZ);
					ImGui::SameLine();
					ImGui::Checkbox("Flat", &HackVars::Visuals::ESP::PlayerCFlat);
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();
					if (ImGui::CollapsingHeader("Player ESP Colors", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
					{
						ImGui::ColorEdit4("Box Color", HackVars::Visuals::ESP::fPBoxColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::ColorEdit4("Chams", HackVars::Visuals::ESP::fVPlayerChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
						ImGui::ColorEdit4("Chams XQZ", HackVars::Visuals::ESP::fNVPlayerChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
					}
				}

				if (ImGui::CollapsingHeader("Lua Entities"))
				{
					ImGui::Spacing();
					ImGui::Checkbox("Enable Lua Entity ESP", &HackVars::Visuals::ESP::LuaESP);
					ImGui::Spacing(); ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing();
					ImGui::Checkbox("Draw Box ", &HackVars::Visuals::ESP::LuaBox);
					ImGui::Checkbox("Draw Name ", &HackVars::Visuals::ESP::LuaDrawName);
					ImGui::SameLine();
					ImGui::Checkbox("Draw Health ", &HackVars::Visuals::ESP::LuaDrawHealth);
					ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
					ImGui::Checkbox("Chams ", &HackVars::Visuals::ESP::LuaChamsEnabled);
					ImGui::SameLine();
					ImGui::Checkbox("XQZ ", &HackVars::Visuals::ESP::LuaXQZ);
					ImGui::SameLine();
					ImGui::Checkbox("Flat ", &HackVars::Visuals::ESP::LuaCFlat);
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();
					if (ImGui::CollapsingHeader("Lua Entity ESP Colors", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
					{
						ImGui::ColorEdit4("Box Color ", HackVars::Visuals::ESP::fLBoxColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::ColorEdit4("Chams ", HackVars::Visuals::ESP::fVLuaChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
						ImGui::ColorEdit4("Chams XQZ ", HackVars::Visuals::ESP::fNVLuaChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
					}
				}
				if (ImGui::CollapsingHeader("Weapons"))
				{
					ImGui::Spacing();
					ImGui::Checkbox("Chams  ", &HackVars::Visuals::ESP::WeaponChamsEnabled);
					ImGui::SameLine();
					ImGui::Checkbox("XQZ  ", &HackVars::Visuals::ESP::WeaponXQZ);
					ImGui::SameLine();
					ImGui::Checkbox("Flat  ", &HackVars::Visuals::ESP::WeaponCFlat);
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();
					if (ImGui::CollapsingHeader("Weapons ESP Colors", ImGuiTreeNodeFlags_NoAutoOpenOnLog))
					{
						ImGui::ColorEdit4("Chams  ", HackVars::Visuals::ESP::fVWeapChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
						ImGui::ColorEdit4("Chams XQZ  ", HackVars::Visuals::ESP::fNVWeapChamsColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8);
					}
				}
			}
			// fix the colors up lol.
			HackVars::Visuals::ESP::PBoxColor = Color(HackVars::Visuals::ESP::fPBoxColor);
			HackVars::Visuals::ESP::LBoxColor = Color(HackVars::Visuals::ESP::fLBoxColor);
		}
		ImGui::End();
	}
	void OpenMenuThing()
	{
		if (InsertDown)
		{
			n_open++;
			if (n_open == 1)
			{
				opened = !opened;
			}
		}
		else
			n_open = 0;
	}
};