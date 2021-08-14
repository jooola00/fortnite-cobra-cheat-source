#include "sdk.h"
#include <d3d11.h>
#include "gui_.h"
#include "Actors.h"

#pragma comment (lib, "d3d11.lib")

ID3D11Device* device = nullptr;
ID3D11DeviceContext* CTX = nullptr;
ID3D11RenderTargetView* CreateTarget_View = nullptr;

HRESULT(*present_init)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*resize_init)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;

WNDPROC WindowProcess = NULL;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND hwnd = NULL;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) && Settings::Menu)
	{
		return true;
	}
	return CallWindowProc(WindowProcess, hWnd, msg, wParam, lParam);
}

int width, height;
float Xs = GetSystemMetrics(0) / 2 - 1;
float Ys = GetSystemMetrics(1) / 2 - 1;
HRESULT PresentHK(IDXGISwapChain* swapchain, UINT sync, UINT flags)
{
	if (!device)
	{
		ID3D11Texture2D* target_fn_render = 0;
		ID3D11Texture2D* VertBuff = 0;
		D3D11_TEXTURE2D_DESC VertBuff_Desync = { 0 };
		swapchain->GetDevice(__uuidof(device), (PVOID*)&device);
		device->GetImmediateContext(&CTX);

		swapchain->GetBuffer(0, __uuidof(target_fn_render), (PVOID*)&target_fn_render);
		device->CreateRenderTargetView(target_fn_render, nullptr, &CreateTarget_View);
		target_fn_render->Release();
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&VertBuff);
		VertBuff->GetDesc(&VertBuff_Desync);

		width = (int)VertBuff_Desync.Width;
		height = (int)VertBuff_Desync.Height;

		VertBuff->Release();
		if (!hwnd)
		{
			hwnd = FindWindow(L"UnrealWindow", L"Fortnite  ");

			if (!hwnd)
				hwnd = GetForegroundWindow();
		}

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 16);

		ImGui_ImplDX11_Init(hwnd, device, CTX);
		ImGui_ImplDX11_CreateDeviceObjects();
	}
	CTX->OMSetRenderTargets(1, &CreateTarget_View, nullptr);
	auto& Present_Window = Utilitys::CreateScene();

	Render::GUI();
	if (Settings::Selected)
	{
		if (Settings::Head)
		{
			overlay::OutlinedString(Present_Window, E("Bone: Head"), ImVec2(990, 70), ImColor(3, 245, 255), true);
		}
		else if (Settings::Chest)
		{
			overlay::OutlinedString(Present_Window, E("Bone: Chest"), ImVec2(990, 70), ImColor(3, 245, 255), true);
		}
		if (Settings::Memory)
		{
			overlay::OutlinedString(Present_Window, E("Method: Memory"), ImVec2(990, 90), ImColor(255, 255, 0), true);
		}
	}
	if (Settings::RenderFOV)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(Xs, Ys), Settings::FOVRadius, ImColor(200, 200, 200, 200), 40, 1);
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(Xs, Ys), Settings::FOVRadius - 1, ImColor(0, 0, 0, 200), 40, 1);
	}
	ActorLoop::Actors(Present_Window);
	//ActorLoop::WorldESP();
	Utilitys::DestroyScene(Present_Window);
	return present_init(swapchain, sync, flags);
}

HRESULT ResizeHK(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_Shutdown();
	CreateTarget_View->Release();
	CTX->Release();
	device->Release();
	device = nullptr;
	return resize_init(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

ImGuiWindow& Utilitys::CreateScene() {
	ImGui_ImplDX11_NewFrame();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	ImGui::Begin(("##InitScene"), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

	return *ImGui::GetCurrentWindow();
}

VOID Utilitys::DestroyScene(ImGuiWindow& window) {
	window.DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	ImGui::Render();
}