namespace Hook
{
	VMTHook* IPanel = nullptr;
	VMTHook* IClientMode = nullptr;
	VMTHook* CHLClient = nullptr;
	VMTHook* EngineClient = nullptr;
	VMTHook* D3DDevice = nullptr;
	VMTHook* MatRenderContext = nullptr;
	VMTHook* ViewRender = nullptr;
	VMTHook* RenderView = nullptr;
	VMTHook* ModelRender = nullptr;
	VMTHook* BaseClientState = nullptr;
	void SetupHooks()
	{
		IPanel = new VMTHook(Interfaces::IPanel());
		IClientMode = new VMTHook(Interfaces::clientmode());
		CHLClient = new VMTHook(client());
		EngineClient = new VMTHook(engine());
		D3DDevice = new VMTHook(Interfaces::D3DDevice());
		MatRenderContext = new VMTHook(Interfaces::MatRenderContext());
		ViewRender = new VMTHook(Interfaces::ViewRender());
		RenderView = new VMTHook(Interfaces::renderview());
		BaseClientState = new VMTHook(Interfaces::BaseClientState());
		ModelRender = new VMTHook(Interfaces::ModelRender());
	}
	void HookFunctions()
	{
		// IPanel
		orgPaintTraverse = (PaintTraverseFn)IPanel->hookFunction(41, hkPaintTraverse);


		// IClientMode
		orgCreateMove = (CreateMoveFn)IClientMode->hookFunction(21, hookCreateMove);
		orgOverrideView = (OverrideViewFn)IClientMode->hookFunction(16, hookOverrideView);

		// CHLClient
		orgFrameStageNotify = (FrameStageNotifyFn)CHLClient->hookFunction(35, hookFrameStageNotify);

		// ViewRender
		orgRenderView = (RenderViewFn)ViewRender->hookFunction(6, hookRenderView);

		// Renderview
		orgSceneEnd = (SceneEndFn)RenderView->hookFunction(9, hookSceneEnd);

		// IVModelRender
		orgDrawModelExecute = (DrawModelExecuteFn)ModelRender->hookFunction(20, hookDrawModelExecute);

		// D3DDevice
		orgReset = (ResetFn)D3DDevice->hookFunction(16, hookReset);
		orgEndScene = (EndSceneFn)D3DDevice->hookFunction(42, hookEndScene);
	}
};