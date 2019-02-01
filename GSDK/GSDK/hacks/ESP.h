namespace H
{
	namespace ESP
	{
		void DrawBoundingBox(BaseEntity* Ent)
		{
			Vector Pos = Ent->GetRenderOrigin();


			Vector min = Pos + Ent->CollisionMins();
			Vector max = Pos + Ent->CollisionMaxs();

			Vector points[] = { Vector(min.x, min.y, min.z),
						Vector(min.x, max.y, min.z),
						Vector(max.x, max.y, min.z),
						Vector(max.x, min.y, min.z),
						Vector(max.x, max.y, max.z),
						Vector(min.x, max.y, max.z),
						Vector(min.x, min.y, max.z),
						Vector(max.x, min.y, max.z) };

			Vector2D blb;
			Vector2D brb;
			Vector2D frb;
			Vector2D flb;

			Vector2D frt;
			Vector2D brt;
			Vector2D blt;
			Vector2D flt;

			if (!Util::Math::WorldToScreen(points[0], blb) || !Util::Math::WorldToScreen(points[1], brb) || !Util::Math::WorldToScreen(points[2], frb) || !Util::Math::WorldToScreen(points[3], flb) ||
				!Util::Math::WorldToScreen(points[4], frt) || !Util::Math::WorldToScreen(points[5], brt) || !Util::Math::WorldToScreen(points[6], blt) || !Util::Math::WorldToScreen(points[7], flt))
				return;

			Vector2D arr[] = { blb,brb,frb,flb,frt,brt,blt,flt };
			float left = flb.x;
			float top = flb.y;
			float right = flb.x;
			float bottom = flb.y;

			for (int i = 1; i < 8; i++)
			{
				if (left > arr[i].x)
					left = arr[i].x;
				if (top < arr[i].y)
					top = arr[i].y;
				if (right < arr[i].x)
					right = arr[i].x;
				if (bottom > arr[i].y)
					bottom = arr[i].y;
			}




			if(Ent->IsPlayer())
			{ 
				if (HackVars::Visuals::ESP::PlayerBox)
				{
					H::Draw::DrawLine(left, bottom, left, top, HackVars::Visuals::ESP::PBoxColor);
					H::Draw::DrawLine(left, top, right, top, HackVars::Visuals::ESP::PBoxColor);
					H::Draw::DrawLine(right, top, right, bottom, HackVars::Visuals::ESP::PBoxColor);
					H::Draw::DrawLine(right, bottom, left, bottom, HackVars::Visuals::ESP::PBoxColor);
				}
				if (HackVars::Visuals::ESP::PlayerDrawname)
				{
					player_info_t player_info;
					if (engine()->GetPlayerInfo(Ent->entIndex(), &player_info))
					{
						H::Draw::Drawtext(player_info.name, HackVars::Fonts::DefaultFont, left, top + 2);
					}
				}
				if (Ent->GetHealth() > 0 && HackVars::Visuals::ESP::PlayerDrawHealth)
					H::Draw::Drawtext(std::to_string(Ent->GetHealth()).c_str(), HackVars::Fonts::DefaultFont, left, top + 17, Color(255, 0, 0, 255));
			}
			else if(Ent->UsesLua())
			{
				if (HackVars::Visuals::ESP::LuaBox)
				{
					H::Draw::DrawLine(left, bottom, left, top, HackVars::Visuals::ESP::LBoxColor);
					H::Draw::DrawLine(left, top, right, top, HackVars::Visuals::ESP::LBoxColor);
					H::Draw::DrawLine(right, top, right, bottom, HackVars::Visuals::ESP::LBoxColor);
					H::Draw::DrawLine(right, bottom, left, bottom, HackVars::Visuals::ESP::LBoxColor);
				}
				if(HackVars::Visuals::ESP::LuaDrawName)
					H::Draw::Drawtext(Ent->GetLuaName(), HackVars::Fonts::DefaultFont, left, top + 2);
				
				if (Ent->GetHealth() > 0 && HackVars::Visuals::ESP::LuaDrawHealth)
					H::Draw::Drawtext(std::to_string(Ent->GetHealth()).c_str(), HackVars::Fonts::DefaultFont, left, top + 17, Color(255, 0, 0, 255));
				
			}

		}
		void FovCircle(float fov)
		{
			// wont be accurate around the edges when the aimbot fov is high, not like that matters.
			int scrw, scrh; engine()->GetScreenSize(scrw, scrh);
			if (fov > 180)
				fov = 180;
			H::Draw::DrawCircle(scrw / 2, scrh / 2, tan(DEG2RAD(fov) / 2) / tan(DEG2RAD(HackVars::FOV) / 2) * scrw, 100, Color(255, 255, 255, 255));
		}
		void DrawAimbotTargetLine()
		{
			if (HackVars::Aimbot::AimbotTarget == nullptr)
				return;

			int scrw, scrh; engine()->GetScreenSize(scrw, scrh);

			Vector2D Screen;

			if (!Util::Math::WorldToScreen(HackVars::Aimbot::AimbotPos, Screen))
				return;

			H::Draw::DrawLine(scrw / 2, scrh, Screen.x, Screen.y, Color(0, 255, 0, 255));
		}
		void DrawAimbotTarget()
		{
			if (HackVars::Aimbot::AimbotTarget == nullptr)
				return;

			player_info_t player_info;
			if (engine()->GetPlayerInfo(HackVars::Aimbot::AimbotTarget->entIndex(), &player_info))
			{
				H::Draw::Drawtext("Target: ", HackVars::Fonts::DefaultFont, 0, 0);
				H::Draw::Drawtext(player_info.name, HackVars::Fonts::DefaultFont, 45, 0);
			}
			DrawAimbotTargetLine();
		}
	};

};