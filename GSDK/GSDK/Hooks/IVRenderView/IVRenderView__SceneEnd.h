typedef void(__thiscall* SceneEndFn)(void*);
SceneEndFn orgSceneEnd = nullptr;

void __fastcall hookSceneEnd(RenderView* view, void* edx)
{
	return orgSceneEnd(view);
}