typedef bool(__thiscall* OverrideViewFn)(void*, CViewSetup*);
OverrideViewFn orgOverrideView = nullptr;

bool __fastcall hookOverrideView(ClientMode* ecx, void* edx, CViewSetup *pSetup)
{
	// see IViewRender::RenderView
	// for third person and shit

	return orgOverrideView(ecx, pSetup);
}