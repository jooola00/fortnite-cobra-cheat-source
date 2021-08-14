#include "offsets.h"

#define ReadPointer(base, offset) (*(PVOID *)(((PBYTE)base + offset)))
#define ReadDWORD(base, offset) (*(PDWORD)(((PBYTE)base + offset)))
#define ReadBYTE(base, offset) (*(((PBYTE)base + offset)))
#define ReadDWORD_PTR(base, offset) (*(DWORD_PTR *)(((PBYTE)base + offset)))

SDK::Structs::FVector* GetPawnRootLocations(uintptr_t pawn) {
	auto root = SDK::Utilities::ReadMemory<uintptr_t>(pawn + SDK::Classes::StaticOffsets::RootComponent);
	if (!root) {
		return nullptr;
	}
	return reinterpret_cast<SDK::Structs::FVector*>(reinterpret_cast<PBYTE>(root) + SDK::Classes::StaticOffsets::RelativeLocation);
}

PVOID FindTargetedPawn;

SDK::Structs::Vector3 GetBonePos(DWORD_PTR mesh, int id)
{
	auto bonearray = ReadPointer(mesh, 0x4A8);
	if (bonearray == NULL)
	{
		bonearray = ReadPointer(mesh, 0x4A8 + 0x10);
	}
	FTransform bone = ReadFTRANSFORM(bonearray, (id * 0x30));
	FTransform ComponentToWorld = ReadFTRANSFORM(mesh, 0x1C0);
	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return SDK::Structs::Vector3(Matrix._41, Matrix._42, Matrix._43);
}

SDK::Structs::Vector3 CamLoc;
SDK::Structs::Vector3 CamRot;
float GlobalFOV = 80.f;

INT(*GetViewPoint)(PVOID, SDK::Structs::FMinimalViewInfo*, BYTE) = nullptr;
INT GetViewPointHook(PVOID player, SDK::Structs::FMinimalViewInfo* viewInfo, BYTE stereoPass)
{
	auto ret = GetViewPoint(player, viewInfo, stereoPass);
	CamLoc = viewInfo->Loc;
	CamRot = viewInfo->Rot;
	if (Settings::FOVSlider)
	{
		viewInfo->FOV = (float)Settings::FOVAmt;
	}
	GlobalFOV = viewInfo->FOV;
	return ret;
}

namespace overlay
{
	std::string string_To_UTF8(const std::string& str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);
		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		std::string retStr(pBuf);
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}
	// Drawings for custom menus + Toggle Button's / Checkboxes ETC
	void RegularRGBText(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImColor(color), utf_8_2.c_str());
	}
	void Test(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
	}
	void ShadowRGBText(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 200)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImColor(0, 0, 0, 200)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
	}
	void OutlinedRBGText(int x, int y, ImColor color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 2), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 30 / 30.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 2), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 30 / 30.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
	}
	void Rect(int x, int y, int w, int h, ImColor color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0, thickness);
	}
	void FilledRect(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0);
	}

	void OutlinedString(ImGuiWindow& windowshit, std::string str, ImVec2 loc, ImU32 colr, bool centered = false)
	{
		ImVec2 size = { 0,0 };
		float minx = 0;
		float miny = 0;
		if (centered)
		{
			size = ImGui::GetFont()->CalcTextSizeA(windowshit.DrawList->_Data->FontSize, 0x7FFFF, 0, str.c_str());
			minx = size.x / 2.f;
			miny = size.y / 2.f;
		}

		windowshit.DrawList->AddText(ImVec2((loc.x - 1) - minx, (loc.y - 1) - miny), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), str.c_str());
		windowshit.DrawList->AddText(ImVec2((loc.x + 1) - minx, (loc.y + 1) - miny), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), str.c_str());
		windowshit.DrawList->AddText(ImVec2((loc.x + 1) - minx, (loc.y - 1) - miny), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), str.c_str());
		windowshit.DrawList->AddText(ImVec2((loc.x - 1) - minx, (loc.y + 1) - miny), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), str.c_str());
		windowshit.DrawList->AddText(ImVec2(loc.x - minx, loc.y - miny), colr, str.c_str());
	}
	void DrawLine(int x1, int y1, int x2, int y2, const ImVec4& color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::GetColorU32(color), thickness);
	}
	void DrawCorneredBox(int X, int Y, int W, int H, ImColor color, int thickness) {
		float lineW = (W / 3);
		float lineH = (H / 3);

		DrawLine(X, Y, X, Y + lineH, color, thickness);
		DrawLine(X, Y, X + lineW, Y, color, thickness);
		DrawLine(X + W - lineW, Y, X + W, Y, color, thickness);
		DrawLine(X + W, Y, X + W, Y + lineH, color, thickness);
		DrawLine(X, Y + H - lineH, X, Y + H, color, thickness);
		DrawLine(X, Y + H, X + lineW, Y + H, color, thickness);
		DrawLine(X + W - lineW, Y + H, X + W, Y + H, color, thickness);
		DrawLine(X + W, Y + H - lineH, X + W, Y + H, color, thickness);
	}
	void Outline(int X, int Y, int W, int H, ImColor color) {
		float lineW = (W / 3);
		float lineH = (H / 3);

		DrawLine(X, Y, X, Y + lineH, color, 2);
		DrawLine(X, Y, X + lineW, Y, color, 2);
		DrawLine(X + W - lineW, Y, X + W, Y, color, 2);
		DrawLine(X + W, Y, X + W, Y + lineH, color, 2);
		DrawLine(X, Y + H - lineH, X, Y + H, color, 2);
		DrawLine(X, Y + H, X + lineW, Y + H, color, 2);
		DrawLine(X + W - lineW, Y + H, X + W, Y + H, color, 2);
		DrawLine(X + W, Y + H - lineH, X + W, Y + H, color, 2);
	}
	void DrawEsp(int X, int Y, int W, int H, ImColor Color) {
		float lineW = (W / 5);
		float lineH = (H / 6);
		float lineT = 1;

		DrawLine(X - lineT, Y - lineT, X + lineW, Y - lineT, ImColor(0, 0, 0, 255), 1);
		DrawLine(X - lineT, Y - lineT, X - lineT, Y + lineH, ImColor(0, 0, 0, 255), 1);
		DrawLine(X - lineT, Y + H - lineH, X - lineT, Y + H + lineT, ImColor(0, 0, 0, 255), 1);
		DrawLine(X - lineT, Y + H + lineT, X + lineW, Y + H + lineT, ImColor(0, 0, 0, 255), 1);
		DrawLine(X + W - lineW, Y - lineT, X + W + lineT, Y - lineT, ImColor(0, 0, 0, 255), 1);
		DrawLine(X + W + lineT, Y - lineT, X + W + lineT, Y + lineH, ImColor(0, 0, 0, 255), 1);
		DrawLine(X + W + lineT, Y + H - lineH, X + W + lineT, Y + H + lineT, ImColor(0, 0, 0, 255), 1);
		DrawLine(X + W - lineW, Y + H + lineT, X + W + lineT, Y + H + lineT, ImColor(0, 0, 0, 255), 1);

		DrawLine(X, Y, X, Y + lineH, ImColor(Color), 1);
		DrawLine(X, Y, X + lineW, Y, ImColor(Color), 1);
		DrawLine(X + W - lineW, Y, X + W, Y, ImColor(Color), 1);
		DrawLine(X + W, Y, X + W, Y + lineH, ImColor(Color), 1);
		DrawLine(X, Y + H - lineH, X, Y + H, ImColor(Color), 1);
		DrawLine(X, Y + H, X + lineW, Y + H, ImColor(Color), 1);
		DrawLine(X + W - lineW, Y + H, X + W, Y + H, ImColor(Color), 1);
		DrawLine(X + W, Y + H - lineH, X + W, Y + H, ImColor(Color), 1);

	}
}

DWORD_PTR Levels;
int LevelsCount;

uint64_t entityx;
int f, z;


SDK::Structs::Vector3 RootLocation;
namespace ActorLoop
{
	VOID drawItem(uintptr_t pawn, LPCSTR text, ImU32 color, bool noDistance) {
		auto root = GetPawnRootLocations(pawn);

		if (root) {
			//SDK::Structs::Vector3 pos = root;
			//float dx = CamLoc.x - pos.x;
			//float dy = CamLoc.y - pos.y;
			//float dz = CamLoc.z - pos.z;

			//float dist = spoof_call(game_rbx_jmp, sqrtf, dx * dx + dy * dy + dz * dz) / 100.0f;

			CHAR modified[0xFF] = { 0 };
			snprintf(modified, sizeof(modified), E("%s\n(%dm)"), text, static_cast<INT>(300));
		}
	}

	bool WorldESP()
	{
		try
		{
			for (int i = 0; i < LevelsCount; i++) {
				uint64_t Level = SDK::Utilities::ReadMemory<uint64_t>(Levels + (i * 8));
				if (Level == 0) continue;

				for (auto ai = 0UL; ai < SDK::Utilities::ReadMemory<DWORD>(Level + Offsets::AActors + sizeof(PVOID)); ++ai) {
					auto actors = ReadPointer(Level, Offsets::AActors);
					if (!actors) break;

					auto pawn = reinterpret_cast<UObject*>(ReadPointer(actors, ai * sizeof(PVOID)));
					if (!pawn || pawn == (PVOID)LocalPawn) continue;

					auto name = GetObjectFirstName(pawn);
				}
			}
		}
		catch (...) {}
	}

	bool Actors(ImGuiWindow& presentwindow)
	{
		try
		{
			float FOVmax = 9999.f;
			uintptr_t MyTeamIndex = 0, EnemyTeamIndex = 0;
			uintptr_t GWorld = SDK::Utilities::ReadMemory<uintptr_t>(Utilitys::Uworld);
			if (!GWorld) return false;

			X = SDK::Utilities::SpoofCall(GetSystemMetrics, SM_CXSCREEN);
			Y = SDK::Utilities::SpoofCall(GetSystemMetrics, SM_CYSCREEN);

			uintptr_t Gameinstance = SDK::Utilities::ReadMemory<uint64_t>(GWorld + Offsets::OwningGameInstance);
			if (!Gameinstance) return false;

			uintptr_t LocalPlayers = SDK::Utilities::ReadMemory<uint64_t>(Gameinstance + Offsets::LocalPlayers);
			if (!LocalPlayers) return false;

			uintptr_t LocalPlayer = SDK::Utilities::ReadMemory<uint64_t>(LocalPlayers);
			if (!LocalPlayer) return false;

			PlayerController = SDK::Utilities::ReadMemory<uint64_t>(LocalPlayer + Offsets::PlayerController);
			if (!PlayerController) return false;

			uintptr_t PlayerCameraManager = SDK::Utilities::ReadMemory<uint64_t>(PlayerController + Offsets::PlayerCameraManager);
			if (!PlayerCameraManager) return false;

			//FOVAngle = SDK::Classes::APlayerCameraManager::GetFOVAngle(PlayerCameraManager);
			LocalPawn = SDK::Utilities::ReadMemory<uint64_t>(PlayerController + Offsets::AcknowledgedPawn);

			uintptr_t levels = SDK::Utilities::ReadMemory<uintptr_t>(GWorld + Offsets::PersistentLevel);
			if (!levels) return false;

			uintptr_t Actors = SDK::Utilities::ReadMemory<uintptr_t>(levels + Offsets::AActors);
			if (!Actors) return false;

			int ActorC = *(int*)(levels + Offsets::ActorCount);
			if (!ActorC) return false;

			GetPlayerViewPoint(PlayerCameraManager, &SDK::Utilities::CamLoc, &SDK::Utilities::CamRot);

			uintptr_t LocalRootComponent = SDK::Utilities::ReadMemory<uintptr_t>(LocalPawn + 0x130);
			SDK::Structs::Vector3 LocalRelativeLocation = SDK::Utilities::ReadMemory<SDK::Structs::Vector3>(LocalRootComponent + 0x11C);

			uint64_t CurrentWeapon = SDK::Utilities::ReadMemory<uint64_t>(LocalPawn + 0x600);

			for (int i = 0; i < ActorC; i++) {

				uintptr_t pawn = SDK::Utilities::ReadMemory<uint64_t>(Actors + i * sizeof(uintptr_t));
				auto name = GetObjectName(pawn);

				if (strstr(name.c_str(), ("BP_PlayerPawn")) || strstr(name.c_str(), ("PlayerPawn")))
				{
					SDK::Structs::Vector3 Headbox, bottom, pelviss, localpelviss, WeaponPos;

					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 66, &Headbox);
					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 2, &pelviss);
					SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 0, &bottom);

					SDK::Classes::AController::WorldToScreen(SDK::Structs::Vector3(Headbox.x, Headbox.y, Headbox.z + 20), &Headbox);
					SDK::Classes::AController::WorldToScreen(SDK::Structs::Vector3(pelviss.x, pelviss.y, pelviss.z + 70), &pelviss);
					SDK::Classes::AController::WorldToScreen(bottom, &bottom);

					DWORD_PTR player_mesh = ReadDWORD_PTR(pawn, 0x280);
					SDK::Structs::Vector3 Head = GetBonePos(player_mesh, 66);
					SDK::Structs::Vector3 HeadW2S = SDK::Classes::AController::WorldToScreen(SDK::Structs::Vector3(Head.x, Head.y, Head.z + 15), &Head);

					SDK::Structs::Vector3 head2, neck, pelvis, chest, leftShoulder, rightShoulder, leftElbow, rightElbow, leftHand, rightHand, leftLeg, rightLeg, leftThigh, rightThigh, leftFoot, rightFoot, leftFeet, rightFeet, leftFeetFinger, rightFeetFinger;

					ImColor BoxColor = { 255, 255, 255 };
					ImColor SkelColor = { 255, 255, 255, 220 };
					ImColor LineColor = { 255, 255, 255, 100 };

					SDK::Structs::Vector3 View;
					bool CheckIfVisible;

					if (Settings::VisibleCheck)
					{
						CheckIfVisible = SDK::Classes::APlayerCameraManager::LineOfSightTo((PVOID)PlayerController, (PVOID)pawn, &View);
						if (CheckIfVisible) {
							BoxColor = { 255, 25, 25 };
							SkelColor = { 3, 252, 227 };
							LineColor = { 0, 255, 255, 100 };
						}
						else {
							BoxColor = { 255, 25, 25 };
							SkelColor = { 255, 255, 255 };
							LineColor = { 255, 0, 0, 100 };
						}
					}

					if (SDK::Utilities::valid_pointer(LocalPawn))
					{
						if (Settings::Snaplines)
						{
							SDK::Classes::USkeletalMeshComponent::GetBoneLocation(LocalPawn, 2, &localpelviss);
							SDK::Classes::AController::WorldToScreen(localpelviss, &localpelviss);

							overlay::DrawLine(localpelviss.x, localpelviss.y, pelviss.x, pelviss.y, ImColor(LineColor), 1.5);
						}
					}

					if (SDK::Utilities::valid_pointer(LocalPawn))
					{
						if (Settings::Lines)
						{
							SDK::Classes::USkeletalMeshComponent::GetBoneLocation(CurrentWeapon, 66, &WeaponPos);
							SDK::Classes::AController::WorldToScreen(WeaponPos, &WeaponPos);

							overlay::DrawLine(WeaponPos.x, WeaponPos.y, pelviss.x, pelviss.y, ImColor(0, 255, 255, 100), 1.5);
						}
					}

					//CurWep list 0x610
					if (pawn == LocalPawn) continue;

					if (Headbox.x == 0 && Headbox.y == 0) continue;
					if (bottom.x == 0 && bottom.y == 0) continue;

					float Height = Headbox.y - bottom.y;
					if (Height < 0)
						Height = Height * (-1.f);
					float Width = Height * 0.25;
					Headbox.x = Headbox.x - (Width / 2);

					if (Settings::RegularBox)
					{
						if (Settings::Filled)
						{
							overlay::FilledRect(Headbox.x, Headbox.y, Width, Height, ImColor(0, 0, 0, 50));
						}
						if (Settings::OutlinedESP)
						{
							overlay::Rect(Headbox.x, Headbox.y, Width, Height, ImColor(0, 0, 0, 200), 3.5);
						}
						overlay::Rect(Headbox.x, Headbox.y, Width, Height, ImColor(BoxColor), 1.5);
					}

					if (Settings::Bones)
					{
						SDK::Structs::Vector3 head2, neck, pelvis, chest, leftShoulder, rightShoulder, leftElbow, rightElbow, leftHand, rightHand, leftLeg, rightLeg, leftThigh, rightThigh, leftFoot, rightFoot, leftFeet, rightFeet, leftFeetFinger, rightFeetFinger;

						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 66, &head2);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 65, &neck);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 2, &pelvis);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 36, &chest);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 9, &leftShoulder);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 62, &rightShoulder);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 10, &leftElbow);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 38, &rightElbow);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 11, &leftHand);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 39, &rightHand);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 67, &leftLeg);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 74, &rightLeg);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 73, &leftThigh);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 80, &rightThigh);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 68, &leftFoot);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 75, &rightFoot);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 71, &leftFeet);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 78, &rightFeet);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 72, &leftFeetFinger);
						SDK::Classes::USkeletalMeshComponent::GetBoneLocation(pawn, 79, &rightFeetFinger);

						SDK::Classes::AController::WorldToScreen(head2, &head2);
						SDK::Classes::AController::WorldToScreen(neck, &neck);
						SDK::Classes::AController::WorldToScreen(pelvis, &pelvis);
						SDK::Classes::AController::WorldToScreen(chest, &chest);
						SDK::Classes::AController::WorldToScreen(leftShoulder, &leftShoulder);
						SDK::Classes::AController::WorldToScreen(rightShoulder, &rightShoulder);
						SDK::Classes::AController::WorldToScreen(leftElbow, &leftElbow);
						SDK::Classes::AController::WorldToScreen(rightElbow, &rightElbow);
						SDK::Classes::AController::WorldToScreen(leftHand, &leftHand);
						SDK::Classes::AController::WorldToScreen(rightHand, &rightHand);
						SDK::Classes::AController::WorldToScreen(leftLeg, &leftLeg);
						SDK::Classes::AController::WorldToScreen(rightLeg, &rightLeg);
						SDK::Classes::AController::WorldToScreen(leftThigh, &leftThigh);
						SDK::Classes::AController::WorldToScreen(rightThigh, &rightThigh);
						SDK::Classes::AController::WorldToScreen(leftFoot, &leftFoot);
						SDK::Classes::AController::WorldToScreen(rightFoot, &rightFoot);
						SDK::Classes::AController::WorldToScreen(leftFeet, &leftFeet);
						SDK::Classes::AController::WorldToScreen(rightFeet, &rightFeet);
						SDK::Classes::AController::WorldToScreen(leftFeetFinger, &leftFeetFinger);
						SDK::Classes::AController::WorldToScreen(rightFeetFinger, &rightFeetFinger);

						if (Settings::OutlinedSkeleton)
						{
							overlay::DrawLine(head2.x, head2.y, neck.x, neck.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(neck.x, neck.y, pelvis.x, pelvis.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(chest.x, chest.y, leftShoulder.x, leftShoulder.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(chest.x, chest.y, rightShoulder.x, rightShoulder.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(leftShoulder.x, leftShoulder.y, leftElbow.x, leftElbow.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(rightShoulder.x, rightShoulder.y, rightElbow.x, rightElbow.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(leftElbow.x, leftElbow.y, leftHand.x, leftHand.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(rightElbow.x, rightElbow.y, rightHand.x, rightHand.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(pelvis.x, pelvis.y, leftLeg.x, leftLeg.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(pelvis.x, pelvis.y, rightLeg.x, rightLeg.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(leftLeg.x, leftLeg.y, leftThigh.x, leftThigh.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(rightLeg.x, rightLeg.y, rightThigh.x, rightThigh.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(leftThigh.x, leftThigh.y, leftFoot.x, leftFoot.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(rightThigh.x, rightThigh.y, rightFoot.x, rightFoot.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(leftFoot.x, leftFoot.y, leftFeet.x, leftFeet.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(rightFoot.x, rightFoot.y, rightFeet.x, rightFeet.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(leftFeet.x, leftFeet.y, leftFeetFinger.x, leftFeetFinger.y, ImColor(0, 0, 0, 200), 2);
							overlay::DrawLine(rightFeet.x, rightFeet.y, rightFeetFinger.x, rightFeetFinger.y, ImColor(0, 0, 0, 200), 2);
						}

						overlay::DrawLine(head2.x, head2.y, neck.x, neck.y, SkelColor, 1);
						overlay::DrawLine(neck.x, neck.y, pelvis.x, pelvis.y, SkelColor, 1);
						overlay::DrawLine(chest.x, chest.y, leftShoulder.x, leftShoulder.y, SkelColor, 1);
						overlay::DrawLine(chest.x, chest.y, rightShoulder.x, rightShoulder.y, SkelColor, 1);
						overlay::DrawLine(leftShoulder.x, leftShoulder.y, leftElbow.x, leftElbow.y, SkelColor, 1);
						overlay::DrawLine(rightShoulder.x, rightShoulder.y, rightElbow.x, rightElbow.y, SkelColor, 1);
						overlay::DrawLine(leftElbow.x, leftElbow.y, leftHand.x, leftHand.y, SkelColor, 1);
						overlay::DrawLine(rightElbow.x, rightElbow.y, rightHand.x, rightHand.y, SkelColor, 1);
						overlay::DrawLine(pelvis.x, pelvis.y, leftLeg.x, leftLeg.y, SkelColor, 1);
						overlay::DrawLine(pelvis.x, pelvis.y, rightLeg.x, rightLeg.y, SkelColor, 1);
						overlay::DrawLine(leftLeg.x, leftLeg.y, leftThigh.x, leftThigh.y, SkelColor, 1);
						overlay::DrawLine(rightLeg.x, rightLeg.y, rightThigh.x, rightThigh.y, SkelColor, 1);
						overlay::DrawLine(leftThigh.x, leftThigh.y, leftFoot.x, leftFoot.y, SkelColor, 1);
						overlay::DrawLine(rightThigh.x, rightThigh.y, rightFoot.x, rightFoot.y, SkelColor, 1);
						overlay::DrawLine(leftFoot.x, leftFoot.y, leftFeet.x, leftFeet.y, SkelColor, 1);
						overlay::DrawLine(rightFoot.x, rightFoot.y, rightFeet.x, rightFeet.y, SkelColor, 1);
						overlay::DrawLine(leftFeet.x, leftFeet.y, leftFeetFinger.x, leftFeetFinger.y, SkelColor, 1);
						overlay::DrawLine(rightFeet.x, rightFeet.y, rightFeetFinger.x, rightFeetFinger.y, SkelColor, 1);
					}

					if (Settings::EnemyVisible && CheckIfVisible)
					{
						overlay::OutlinedString(presentwindow, "Enemy Visible", ImVec2(990, 50), ImColor(219, 190, 0), true);
					}

					if (Settings::Distance)
					{
						if (SDK::Utilities::valid_pointer(LocalPawn))
						{
							float dist;
							Headbox + 15;
							uintptr_t localPlayerRoot = SDK::Utilities::ReadMemory<uintptr_t>(LocalPawn + SDK::Classes::StaticOffsets::RootComponent);
							auto localPlayerLocation = reinterpret_cast<float*>(reinterpret_cast<PBYTE>(localPlayerRoot) + SDK::Classes::StaticOffsets::RelativeLocation);
							auto playerRoot = GetPawnRootLocations(pawn);
							if (playerRoot) {
								auto playerPos = *playerRoot;
								float x = localPlayerLocation[0] - playerPos.X;
								float y = localPlayerLocation[1] - playerPos.Y;
								float z = localPlayerLocation[2] - playerPos.Z;

								char draw[64];
								dist = sqrtf((x * x) + (y * y) + (z * z)) / 100.0f;
								sprintf_s(draw, "[%.0f Meters]", dist);

								overlay::ShadowRGBText(Headbox.x - 5, Headbox.y - 35, ImColor(0, 255, 255, 200), draw);
							}
						}
					}

					/*if (Settings::bone == 1)
					{
						Settings::Head = 66;
					}
					else if (Settings::bone == 2)
					{
						Settings::Head = 7;
					}*/

					if (IF_AIMKEY())
					{
						if (SDK::Utilities::CheckIfInFOV(pawn, FOVmax)) {

							if (Settings::Memory)
							{
								if (Settings::VisibleCheck and CheckIfVisible) {

									SDK::Structs::Vector3 NewAngle = SDK::Utilities::GetRotation(pawn);

									if (NewAngle.x == 0 && NewAngle.y == 0) continue;

									if (Settings::Smoothing > 0)
										NewAngle = SDK::Utilities::SmoothAngles(SDK::Utilities::CamRot, NewAngle);

									NewAngle.z = 0;

									SDK::Classes::AController::ValidateClientSetRotation(NewAngle, false);
									SDK::Classes::AController::ClientSetRotation(NewAngle, false);
								}
							}
							else if (!Settings::VisibleCheck) {

								if (Settings::Memory)
								{
									SDK::Structs::Vector3 NewAngle = SDK::Utilities::GetRotation(pawn);

									if (NewAngle.x == 0 && NewAngle.y == 0) continue;

									if (Settings::Smoothing > 0)
										NewAngle = SDK::Utilities::SmoothAngles(SDK::Utilities::CamRot, NewAngle);

									NewAngle.z = 0;

									SDK::Classes::AController::ValidateClientSetRotation(NewAngle, false);
									SDK::Classes::AController::ClientSetRotation(NewAngle, false);
								}
							}
						}

						DWORD_PTR FindClosestPawn = NULL;
						if (Settings::Lines)
						{
							SDK::Utilities::Snapline(pawn);
						}

						if (SDK::Utilities::valid_pointer(LocalPawn))
						{
							if (Settings::Rapid_Fire)
							{
								if (CurrentWeapon) {

									float x = 0;
									float d = 0;

									x = *(float*)(CurrentWeapon + 0x9BC); // LastFireTime = 0x9BC;

									*(float*)(CurrentWeapon + 0x9BC) = x - 0.003f;

									d = *(float*)(CurrentWeapon + 0x9C0); // LastFireTimVerified = 0x9C0;

									*(float*)(CurrentWeapon + 0x9C0) = 0.101f;
								}
							}

							if (Settings::No_Bloom)
							{
								*(float*)(CurrentWeapon + 0x0D90) = 999999.99f;
							}

							if (Settings::InstaRevive)
							{
								*(float*)(LocalPawn + 0x33B8) = 0.11f;
							}
							if (Settings::AimAir)
							{
								*(bool*)(LocalPawn + 0x3AB1) = true;
							}
						}
					}
				}
				else if (Settings::Vehicles and strstr(name.c_str(), E("Valet_Taxi"))) {
					if (SDK::Utilities::valid_pointer(LocalPawn)) {
						uintptr_t VechicleRootComponent = SDK::Utilities::ReadMemory<uintptr_t>(pawn + 0x130);
						SDK::Structs::Vector3 VehicleRoot = SDK::Utilities::ReadMemory<SDK::Structs::Vector3>(VechicleRootComponent + 0x11C);
						SDK::Structs::Vector3  VehicleRootW2S;
						SDK::Classes::AController::WorldToScreen(VehicleRoot, &VehicleRootW2S);

						overlay::OutlinedString(presentwindow, "Vehicle Taxi", ImVec2(VehicleRootW2S.x, VehicleRootW2S.y), ImColor(255, 255, 20), false);
					}
				}
				else if (Settings::Vehicles and strstr(name.c_str(), E("Valet_BigRig")) || strstr(name.c_str(), E("Valet_BasicTr"))) {
					if (SDK::Utilities::valid_pointer(LocalPawn)) {
						uintptr_t VechicleRootComponent = SDK::Utilities::ReadMemory<uintptr_t>(pawn + 0x130);
						SDK::Structs::Vector3 VehicleRoot = SDK::Utilities::ReadMemory<SDK::Structs::Vector3>(VechicleRootComponent + 0x11C);
						SDK::Structs::Vector3  VehicleRootW2S;
						SDK::Classes::AController::WorldToScreen(VehicleRoot, &VehicleRootW2S);

						overlay::OutlinedString(presentwindow, "Basic Truck", ImVec2(VehicleRootW2S.x, VehicleRootW2S.y), ImColor(0, 219, 153), false);
					}
				}

				else if (Settings::Vehicles and strstr(name.c_str(), E("Valet_SportsC")) || strstr(name.c_str(), E("Valet_BasicC"))) {
					if (SDK::Utilities::valid_pointer(LocalPawn)) {
						uintptr_t VechicleRootComponent = SDK::Utilities::ReadMemory<uintptr_t>(pawn + 0x130);
						SDK::Structs::Vector3 VehicleRoot = SDK::Utilities::ReadMemory<SDK::Structs::Vector3>(VechicleRootComponent + 0x11C);
						SDK::Structs::Vector3  VehicleRootW2S;
						SDK::Classes::AController::WorldToScreen(VehicleRoot, &VehicleRootW2S);

						overlay::OutlinedString(presentwindow, "Basic Car", ImVec2(VehicleRootW2S.x, VehicleRootW2S.y), ImColor(255, 0, 0), false);
					}
				}
				else if (Settings::Boat and strstr(name.c_str(), E("MeatballVehicle_L"))) {
					if (SDK::Utilities::valid_pointer(LocalPawn)) {
						uintptr_t VechicleRootComponent = SDK::Utilities::ReadMemory<uintptr_t>(pawn + 0x130);
						SDK::Structs::Vector3 VehicleRoot = SDK::Utilities::ReadMemory<SDK::Structs::Vector3>(VechicleRootComponent + 0x11C);
						SDK::Structs::Vector3  VehicleRootW2S;
						SDK::Classes::AController::WorldToScreen(VehicleRoot, &VehicleRootW2S);

						overlay::OutlinedString(presentwindow, "Booty Boat", ImVec2(VehicleRootW2S.x, VehicleRootW2S.y), ImColor(255, 255, 255), false);
					}
				}

				else if (Settings::Weapon and strstr(name.c_str(), E("FortPickupAthena"))) {

					if (SDK::Utilities::valid_pointer(LocalPawn)) {

						uintptr_t VechicleRootComponent = SDK::Utilities::ReadMemory<uintptr_t>(pawn + Offsets::RootComponent);
						SDK::Structs::Vector3 VehicleRoot = SDK::Utilities::ReadMemory<SDK::Structs::Vector3>(VechicleRootComponent + Offsets::RelativeLocation);
						SDK::Structs::Vector3  VehicleRootW2S;
						SDK::Classes::AController::WorldToScreen(VehicleRoot, &VehicleRootW2S);


						overlay::OutlinedString(presentwindow, "Fort_Pickup", ImVec2(VehicleRootW2S.x, VehicleRootW2S.y), ImColor(50, 255, 100, 220), false);
					}
				}
			}
		}
		catch (...) {}
	}
}
