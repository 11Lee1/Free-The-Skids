typedef HRESULT(__stdcall* ResetFn)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
ResetFn orgReset = nullptr;

HRESULT __stdcall hookReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto Reset = orgReset(device, pPresentationParameters);

	if (Reset >= 0)
	{
		ImGui_ImplDX9_CreateDeviceObjects();
	}

	return Reset;
}
