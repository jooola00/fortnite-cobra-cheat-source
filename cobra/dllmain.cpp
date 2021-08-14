#include "render.h"

void Utilitys::hook()
{
	HWND fn_window = FindWindow(0, (L"Fortnite  "));
	
	// Initalize Steam hook

	auto address = Scanners::PatternScan(SteamHelper::GetSteamdModule(), E("48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8"));
	SteamHelper::InsertHook(address, (uintptr_t)PresentHK, (long long*)&present_init);

	address = Scanners::PatternScan(SteamHelper::GetSteamdModule(), E("48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8"));
	SteamHelper::InsertHook(address, (uintptr_t)ResizeHK, (long long*)&resize_init);

	WindowProcess = (WNDPROC)SetWindowLongPtr(fn_window, GWLP_WNDPROC, (LONG_PTR)WndProc);
}

void Utilitys::init_sigs()
{
	Utilitys::hook();

	Utilitys::Uworld = Scanners::PatternScan(E("48 8B 05 ? ? ? ? 4D 8B C2"));
	Utilitys::Uworld = RVA(Utilitys::Uworld, 7);
	
	Utilitys::GetObjName = SDK::Utilities::Scanners::PatternScan(("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 33 F6 48 8B F2 44 39 71 04 0F 85 ? ? ? ? 8B 19 0F B7 FB E8 ? ? ? ? 8B CB 48 8D 54 24"));

	GetObjectNameInternal = reinterpret_cast<decltype(GetObjectNameInternal)>(Utilitys::GetObjName);

	LineOfS = SDK::Utilities::Scanners::PatternScan(E("E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 D2 40 8A F8"));
	LineOfS = RVA(LineOfS, 5);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		Utilitys::init_sigs();
	}

	return TRUE;
}
