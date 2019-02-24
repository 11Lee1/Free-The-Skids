typedef HRESULT(__stdcall* EndSceneFn)(IDirect3DDevice9*);
EndSceneFn orgEndScene = nullptr;

extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC orgproc = nullptr;

LRESULT __stdcall proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
		if (wParam == VK_INSERT){Menu::InsertDown = true;}
		
	if (msg == WM_KEYUP)
		if (wParam == VK_INSERT) { Menu::InsertDown = false; }

	ImGui_ImplDX9_WndProcHandler(hwnd, msg, wParam, lParam);

	return CallWindowProcA(orgproc, hwnd, msg, wParam, lParam);
}


HRESULT __stdcall hookEndScene(IDirect3DDevice9* device)
{
	if (!Menu::initialised)
	{
		auto gmod = FindWindowW(L"Valve001", nullptr);

		orgproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(gmod, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(proc)));

		ImGui_ImplDX9_Init(gmod, device);
		ImGuiStyle& style = ImGui::GetStyle();

		Menu::initialised = true;
	}
	else
	{
		if (Menu::opened)
		{
			InputSystem()->EnableInput(false);
			surface()->SetCursorAlwaysVisible(true);
		}
		else
		{
			InputSystem()->EnableInput(true);
			surface()->SetCursorAlwaysVisible(false);
		}
		ImGui_ImplDX9_NewFrame();
		Menu::OpenMenuThing();
		Menu::DrawMenu();
		ImGui::Render();
	}
	return orgEndScene(device);
}
