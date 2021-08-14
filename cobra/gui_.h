namespace Draw
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
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
	}
	void BackgroundRBGOutline(int x, int y, int w, int h, ImColor color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0, thickness);
	}
	void BackgroundRBGGradient(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0);
	}

	void BackgroundRBGGradient1(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), ImColor(), ImColor(), ImGui::ColorConvertFloat4ToU32(ImVec4(color)));
	}

	void BackgroundFilledRBG(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0);
	}

	void RoundedRect(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImColor(color), 5);
	}
	void RoundedOutline(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImColor(color), 5);
	}
}

namespace Render
{
	void GUI()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			Settings::Menu = !Settings::Menu;
		}

		if (Settings::Watermark)
		{
			Draw::ShadowRGBText(100, 100, ImColor(255, 255, 255), E("SOFTCLUB (insert for menu)"));
		}

		if (Settings::Menu)
		{
			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_WindowBg] = ImColor(35, 35, 35);
			colors[ImGuiCol_Button] = ImColor();
			colors[ImGuiCol_ButtonActive] = ImColor();
			colors[ImGuiCol_ButtonHovered] = ImColor();
			colors[ImGuiCol_FrameBg] = ImColor(35, 35, 35);
			colors[ImGuiCol_FrameBgHovered] = ImColor(35, 35, 35);
			colors[ImGuiCol_FrameBgActive] = ImColor(35, 35, 35);
			colors[ImGuiCol_Text] = ImColor(225, 225, 225);

			ImGuiStyle* style = &ImGui::GetStyle();
			style->WindowPadding = ImVec2(15, 15);
			style->WindowRounding = 0.0f;
			style->FramePadding = ImVec2(2, 2);
			style->FrameRounding = 0.0f;
			style->ItemSpacing = ImVec2(8, 8);
			style->ItemInnerSpacing = ImVec2(8, 6);
			style->IndentSpacing = 25.0f;
			style->ScrollbarSize = 15.0f;
			style->ScrollbarRounding = 0.0f;
			style->GrabMinSize = 10.0f;
			style->GrabRounding = 0.0f;
			style->ChildRounding = 0.f;

			style->WindowTitleAlign.x = 0.50f;
			style->FrameRounding = 2.0f;

			ImGui::SetNextWindowSize({ 400, 350 });
			ImGui::Begin("#Fortnite", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

			int x = 30;
			int y = 20;

			ImVec2 p = ImGui::GetWindowPos();

			//Draw::BackgroundFilledRBG(p.x, p.y + 30, 50, 320, ImColor(50, 50, 50));
			Draw::BackgroundFilledRBG(p.x, p.y, 400, 30, ImColor(40, 40, 40));
			Draw::BackgroundRBGOutline(p.x, p.y + 30, 400, 0, ImColor(255, 255, 255, 10), 1);

			Draw::BackgroundFilledRBG(p.x, p.y + 320, 400, 30, ImColor(50, 50, 50));
			Draw::ShadowRGBText(p.x + 10, p.y + 325, ImColor(200, 200, 200, 200), E("SOFTCLUB.XYZ | Build: 1.1                                       [©]"));

			Draw::ShadowRGBText(p.x + 120, p.y + 5, ImColor(200, 200, 200, 255), E("aimbot"));
			Draw::ShadowRGBText(p.x + 180, p.y + 5, ImColor(200, 200, 200, 255), E("visuals"));
			Draw::ShadowRGBText(p.x + 240, p.y + 5, ImColor(200, 200, 200, 255), E("exploits"));

			static int fortnitetab;
			ImGuiStyle* Style = &ImGui::GetStyle();
			ImGui::SetCursorPos({ 120, 3 });
			if (ImGui::Button("##Aimbot", ImVec2(50, 20))) fortnitetab = 1;
			ImGui::SameLine();
			if (ImGui::Button("##ESP", ImVec2(50, 20))) fortnitetab = 2;
			ImGui::SameLine();
			if (ImGui::Button("##Misc", ImVec2(50, 20))) fortnitetab = 3;

			if (fortnitetab == 0)
			{
				Draw::ShadowRGBText(p.x + 20, p.y + 70, ImColor(200, 200, 200, 255), E(""));
			}

			if (fortnitetab == 1)
			{
				Draw::ShadowRGBText(p.x + 120, p.y + 5, ImColor(250, 250, 250, 255), E("aimbot"));

				ImGui::Text(E(""));
				ImGui::Checkbox("Aimbot", &Settings::Memory);
				ImGui::Checkbox("Show FOV", &Settings::RenderFOV);

				ImGui::Checkbox("Visible Check", &Settings::VisibleCheck);
				ImGui::Text(E("FOV Radius - (0 to 900)"));
				ImGui::SliderFloat("FOV Radius", &Settings::FOVRadius, 0, 900);
				ImGui::Text(E("Smoothing - (0 to 10)"));
				ImGui::SliderFloat("Smooth", &Settings::Smoothing, 0, 10);
				ImGui::Text(E("Bone Selection"));
				ImGui::Checkbox("Head", &Settings::Head); ImGui::SameLine(); ImGui::Checkbox("Chest", &Settings::Chest);
			}
			if (fortnitetab == 2)
			{
				Draw::ShadowRGBText(p.x + 180, p.y + 5, ImColor(250, 250, 250, 255), E("visuals"));
				static int Pages = 1;
				if (Pages == 1)
				{
					ImGui::Text(E(""));
					ImGui::Checkbox("Box ESP", &Settings::RegularBox);
					ImGui::Checkbox("Filled", &Settings::Filled);
					ImGui::Checkbox("Player Bones", &Settings::Bones);
					ImGui::Text(E(""));
					ImGui::Checkbox("Distance", &Settings::Distance);
					ImGui::Checkbox("Player Lines", &Settings::Snaplines);
					//ImGui::Checkbox("Snaplines", &Settings::Lines);
					if (ImGui::Button("[Page 2]", ImVec2(70, 20))) Pages = 2;
				}
				if (Pages == 2)
				{
					ImGui::Text(E(""));
					//ImGui::Checkbox("Radar", &Settings::Radar);
					ImGui::Checkbox("Visible Enemy", &Settings::EnemyVisible);
					ImGui::Checkbox("Disable Selected Items", &Settings::Selected);
					ImGui::Checkbox("Remove Cobra Watermark", &Settings::Watermark);
					ImGui::Checkbox("Outline Bones", &Settings::OutlinedSkeleton);
					ImGui::Checkbox("Outline Box ESP", &Settings::OutlinedESP);
					ImGui::Checkbox("All Vehicles", &Settings::Vehicles);
					ImGui::Checkbox("Boat ESP", &Settings::Boat);
					ImGui::Checkbox("Player Loot ESP [May Crash]", &Settings::Weapon);
					ImGui::SetCursorPosY({ 275 });
					if (ImGui::Button("[Page 1]", ImVec2(70, 20))) Pages = 1;
				}
				//overlay::OutlinedString(Present_Window, "Enemy Visible", ImVec2(900, 20), ImColor(219, 190, 0), true);
			}
			if (fortnitetab == 3)
			{
				Draw::ShadowRGBText(p.x + 240, p.y + 5, ImColor(250, 250, 250, 255), E("exploits"));

				ImGui::Text(E(""));
				ImGui::Checkbox("Rapid Fire", &Settings::Rapid_Fire);
				ImGui::Checkbox("No Bloom", &Settings::No_Bloom);
				ImGui::Checkbox("Instant Revive", &Settings::InstaRevive);
				ImGui::Checkbox("Jump Aim (Aim When in air)", &Settings::AimAir);
			}

			ImGui::End();
		}
	}
}