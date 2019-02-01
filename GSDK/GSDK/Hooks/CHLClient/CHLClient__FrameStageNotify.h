typedef void(__thiscall* FrameStageNotifyFn)(void*, ClientFrameStage_t);
FrameStageNotifyFn orgFrameStageNotify = nullptr;

void __fastcall hookFrameStageNotify(CHLClient* client, void* edx, ClientFrameStage_t stage)
{
	return orgFrameStageNotify(client, stage);
}