#include "math.h"
namespace H
{
	namespace Util
	{
		namespace Math
		{
			bool WorldToScreen(Vector in, Vector2D& out)
			{
				const VMatrix w2sm = engine()->WorldToScreenMatrix();
				float w = w2sm[3][0] * in.x + w2sm[3][1] * in.y + w2sm[3][2] * in.z + w2sm[3][3];

				if (w > 0.001f)
				{
					int width, height; engine()->GetScreenSize(width, height);

					float fl1DBw = 1 / w;
					out.x = (width / 2) + (0.5f *((w2sm[0][0] * in.x + w2sm[0][1] * in.y + w2sm[0][2] * in.z + w2sm[0][3]) * fl1DBw) * width + 0.5f);
					out.y = (height / 2) - (0.5f * ((w2sm[1][0] * in.x + w2sm[1][1] * in.y + w2sm[1][2] * in.z + w2sm[1][3]) * fl1DBw) * height + 0.5f);
					return true;
				}
				return false;
			}

			float AngleNormalize(float angle)
			{
				angle = fmodf(angle, 360.0f);
				if (angle > 180)
				{
					angle -= 360;
				}
				if (angle < -180)
				{
					angle += 360;
				}
				return angle;
			}
			float AngleNormalizePositive(float angle)
			{
				angle = fmodf(angle, 360.0f);

				if (angle < 0.0f)
				{
					angle += 360.0f;
				}

				return angle;
			}
			float AngleDifference(float destAngle, float srcAngle)
			{
				float delta;

				delta = fmodf(destAngle - srcAngle, 360.0f);
				if (destAngle > srcAngle)
				{
					if (delta >= 180)
						delta -= 360;
				}
				else
				{
					if (delta <= -180)
						delta += 360;
				}
				return delta;
			}
			QAngle FixAngles(QAngle angles)
			{
				angles.x = AngleNormalize(angles.x);
				angles.y = AngleNormalize(angles.y);
				if (angles.x > 89.f)
					angles.x = 89.f;
				else if (angles.x < -89.f)
					angles.x = -89.f;
				return angles;
			}
			QAngle FixAnglePositive(QAngle angles)
			{
				angles.x = AngleNormalizePositive(angles.x);
				angles.y = AngleNormalizePositive(angles.y);
				angles.z = AngleNormalizePositive(angles.z);
				return angles;
			}
			QAngle GetAngle(Vector source, Vector target)
			{
				QAngle OutputAngle;
				VectorAngles(target - source, OutputAngle);
				return OutputAngle;
			}

			Vector Forward(QAngle ang)
			{
				ang = FixAngles(ang);
				float radx = DEG2RAD(ang.x); 
				float rady = DEG2RAD(ang.y);

				return Vector(cos(radx) * cos(rady), cos(radx) * sin(rady), sin(radx));
			}
		};
		bool IsHoldingTool()
		{
			C_GMOD_Player* LocalPlayer = (C_GMOD_Player*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
			CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetActiveWeapon();
			if (!ActiveWeapon)
				return false;

			char const* name = ActiveWeapon->GetName();
			if (!name)
				return false;
			/*
				weapon_physgun weapon_physcannon gmod_tool
			*/

			if (!strcmp(name, "weapon_physgun") || !strcmp(name, "weapon_physcannon") || !strcmp(name, "gmod_tool"))
				return true;

			return false;
		}
		bool IsVisible(BaseEntity* player, Vector TraceEndPos)
		{
			BaseEntity* LocalPlayer = (BaseEntity*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
			if (!LocalPlayer)
				return false;

			trace_t Trace;
			CTraceFilter Filter;
			Filter.pSkip = LocalPlayer;
			Ray_t Ray;

			Ray.Init(LocalPlayer->EyePosition(), TraceEndPos);
			EngineTrace()->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

			if (Trace.m_pEnt == player || Trace.fraction >= 0.98f) // thats basically visible.
				return true;

			return false;
		}
		bool CenterOfHitbox(BaseEntity* player, matrix3x4_t* bones, int joint, Vector &out)
		{

			if (!player || !bones || !player->IsAlive())
				return false;

			model_t* model = player->GetModel();
			if (!model)
				return false;

			mstudiohitboxset_t* hitboxset = ModelInfo()->GetStudiomodel(model)->pHitboxSet(player->m_nHitboxSet());

			if (!hitboxset)
				return false;

			mstudiobbox_t* hitbox = hitboxset->pHitbox(joint);
			if (!hitbox)
				return false;

			Vector mins = hitbox->bbmin; Vector maxs = hitbox->bbmax;
			Vector omin, omax;

			VectorTransform(mins, bones[joint], omin);
			VectorTransform(maxs, bones[joint], omax);

			out = (omin + omax) * 0.5;
			return true;
		}
		void CorrectMovement(CUserCmd* cmd,QAngle oldangles)
		{
			float deltaView;
			float yaw[2];

			float pitch = fmodf(Math::AngleNormalizePositive(cmd->viewangles.x), 360);


			yaw[0] = Math::AngleNormalizePositive(oldangles.y);
			yaw[1] = Math::AngleNormalizePositive(cmd->viewangles.y);
			if (pitch >= 90.0f && pitch <= 270.0f) {
				yaw[1] -= 180;
				yaw[1] = Math::AngleNormalizePositive(yaw[1]);
			}

			if (yaw[1] < yaw[0])
				deltaView = abs(yaw[1] - yaw[0]);
			else
				deltaView = 360.0f - abs(yaw[0] - yaw[1]);

			deltaView = 360.0f - deltaView;

			float fwdmov, sdmov; fwdmov = cmd->forwardmove; sdmov = cmd->sidemove;

			cmd->forwardmove = cos(DEG2RAD(deltaView)) * fwdmov + cos(DEG2RAD(deltaView + 90.f)) * sdmov;
			cmd->sidemove = sin(DEG2RAD(deltaView)) * fwdmov + sin(DEG2RAD(deltaView + 90.f)) * sdmov;
		}
	};
};