#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>
#include <codecvt>
#include <Psapi.h>
#include <list>

#define RVA(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))
#define M_PI	3.14159265358979323846264338327950288419716939937510

namespace Utilitys
{
	ImGuiWindow& CreateScene();
	VOID DestroyScene(ImGuiWindow& WINDOW);

	void init_sigs();
	void hook();

	uintptr_t Uworld;
	uintptr_t GetObjName;
}
inline float sqrtf_(float x)
{
	union { float f; uint32_t i; } z = { x };
	z.i = 0x5f3759df - (z.i >> 1);
	z.f *= (1.5f - (x * 0.5f * z.f * z.f));
	z.i = 0x7EEEEEEE - z.i;
	return z.f;
}
bool IF_AIMKEY()
{
	return GetAsyncKeyState(VK_RBUTTON);
}
double powf_(double x, int y)
{
	double temp;
	if (y == 0)
		return 1;
	temp = powf_(x, y / 2);
	if ((y % 2) == 0) {
		return temp * temp;
	}
	else {
		if (y > 0)
			return x * temp * temp;
		else
			return (temp * temp) / x;
	}
}
uintptr_t PlayerController;
uintptr_t PlayerCameraManager;
uintptr_t LocalPawn;
uintptr_t LineOfS;
uintptr_t GetNameByIndex;

namespace Scanners
{
    uintptr_t PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex = 0);
    uintptr_t PatternScan(const char* sSignature, size_t nSelectResultIndex = 0);

}

uintptr_t Scanners::PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex)
{
    static auto patternToByte = [](const char* pattern)
    {
        auto       bytes = std::vector<int>{};
        const auto start = const_cast<char*>(pattern);
        const auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
    const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

    const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto       patternBytes = patternToByte(sSignature);
    const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

    const auto s = patternBytes.size();
    const auto d = patternBytes.data();

    size_t nFoundResults = 0;

    for (auto i = 0ul; i < sizeOfImage - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            if (nSelectResultIndex != 0)
            {
                if (nFoundResults < nSelectResultIndex)
                {
                    nFoundResults++;
                    found = false;
                }
                else
                {
                    return reinterpret_cast<uintptr_t>(&scanBytes[i]);
                }
            }
            else
            {
                return reinterpret_cast<uintptr_t>(&scanBytes[i]);
            }
        }
    }

    return NULL;
}

uintptr_t Scanners::PatternScan(const char* sSignature, size_t nSelectResultIndex)
{
    static bool bIsSetted = false;

    static MODULEINFO info = { 0 };

    if (!bIsSetted)
    {
        GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));
        bIsSetted = true;
    }

    return PatternScan((uintptr_t)info.lpBaseOfDll, sSignature, nSelectResultIndex);
}

namespace SteamHelper {
	uintptr_t GetSteamdModule()
	{
		printf("1\n");
		std::string module = ("GameOverlayRenderer64.dll");
		return (uintptr_t)GetModuleHandleA(module.c_str());
	}

	void InsertHook(__int64 addr, __int64 func, __int64* orig)
	{
		printf("2\n");
		static uintptr_t hook_addr;
		if (!hook_addr)
			hook_addr = Scanners::PatternScan(GetSteamdModule(), ("48 ? ? ? ? 57 48 83 EC 30 33 C0"));

		auto hook = ((__int64(__fastcall*)(__int64 addr, __int64 func, __int64* orig, __int64 smthng))(hook_addr));
		hook((__int64)addr, (__int64)func, orig, (__int64)1);
	}

	short GetAsyncKeyState(const int vKey)
	{
		printf("3\n");
		static uintptr_t addrGetAsyncKeyState = NULL;

		if (!addrGetAsyncKeyState)
		{
			addrGetAsyncKeyState = Scanners::PatternScan(GetSteamdModule(),
				("40 53 48 83 EC 20 80 3D ? ? ? ? ? 8B D9"));
		}

		if (!addrGetAsyncKeyState)
			return false;

		using GetAsyncKeyState_t = short(__fastcall*)(int);
		auto fnGetAyncKeyState = (GetAsyncKeyState_t)addrGetAsyncKeyState;

		return fnGetAyncKeyState(vKey);
	}

	short SetCursorPos(int x, int y)
	{
		printf("4\n");
		static uintptr_t addrSetCursorPos = NULL;

		if (!addrSetCursorPos)
		{
			addrSetCursorPos = Scanners::PatternScan(GetSteamdModule(),
				(""));
		}

		if (!addrSetCursorPos)
			return false;

		using SetCursorPos_t = short(__fastcall*)(int, int);
		auto fnSetCursorPos = (SetCursorPos_t)addrSetCursorPos;

		return fnSetCursorPos(x, y);
	}


	bool GetCursorPos(LPPOINT lpPoint)
	{
		printf("5\n");
		static uintptr_t addrGetCursorPos = NULL;

		if (!addrGetCursorPos)
		{
			addrGetCursorPos = Scanners::PatternScan(GetSteamdModule(),
				(""));
		}

		if (!addrGetCursorPos)
			return false;

		using GetCursorPos_t = short(__fastcall*)(LPPOINT);
		auto fnGetCursorPos = (GetCursorPos_t)addrGetCursorPos;

		return fnGetCursorPos(lpPoint);
	}

	HCURSOR SetCursor(HCURSOR hCursor)
	{
		printf("6\n");
		static uintptr_t addrSetCursor = NULL;

		if (!addrSetCursor)
		{
			addrSetCursor = Scanners::PatternScan(GetSteamdModule(),
				(""));
		}

		if (!addrSetCursor)
			return (HCURSOR)false;

		using SetCursor_t = HCURSOR(__fastcall*)(HCURSOR);
		auto fnSetCursor = (SetCursor_t)addrSetCursor;

		return fnSetCursor(hCursor);
	}
}

#pragma once

#include <string>
#include <utility>

namespace
{
	constexpr int const_atoi(char c)
	{
		return c - '0';
	}
}

#ifdef _MSC_VER
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE __attribute__((always_inline))
#endif

template<typename _string_type, size_t _length>
class _Basic_XorStr
{
	using value_type = typename _string_type::value_type;
	static constexpr auto _length_minus_one = _length - 1;

public:
	constexpr ALWAYS_INLINE _Basic_XorStr(value_type const (&str)[_length])
		: _Basic_XorStr(str, std::make_index_sequence<_length_minus_one>())
	{

	}

	inline auto c_str() const
	{
		decrypt();

		return data;
	}

	inline auto str() const
	{
		decrypt();

		return _string_type(data, data + _length_minus_one);
	}

	inline operator _string_type() const
	{
		return str();
	}

private:
	template<size_t... indices>
	constexpr ALWAYS_INLINE _Basic_XorStr(value_type const (&str)[_length], std::index_sequence<indices...>)
		: data{ crypt(str[indices], indices)..., '\0' },
		encrypted(true)
	{

	}

	static constexpr auto XOR_KEY = static_cast<value_type>(
		const_atoi(__TIME__[7]) +
		const_atoi(__TIME__[6]) * 10 +
		const_atoi(__TIME__[4]) * 60 +
		const_atoi(__TIME__[3]) * 600 +
		const_atoi(__TIME__[1]) * 3600 +
		const_atoi(__TIME__[0]) * 36000
		);

	static ALWAYS_INLINE constexpr auto crypt(value_type c, size_t i)
	{
		return static_cast<value_type>(c ^ (XOR_KEY + i));
	}

	inline void decrypt() const
	{
		if (encrypted)
		{
			for (size_t t = 0; t < _length_minus_one; t++)
			{
				data[t] = crypt(data[t], t);
			}
			encrypted = false;
		}
	}

	mutable value_type data[_length];
	mutable bool encrypted;
};
//---------------------------------------------------------------------------
template<size_t _length>
using XorStrA = _Basic_XorStr<std::string, _length>;
template<size_t _length>
using XorStrW = _Basic_XorStr<std::wstring, _length>;
template<size_t _length>
using XorStrU16 = _Basic_XorStr<std::u16string, _length>;
template<size_t _length>
using XorStrU32 = _Basic_XorStr<std::u32string, _length>;
//---------------------------------------------------------------------------
template<typename _string_type, size_t _length, size_t _length2>
inline auto operator==(const _Basic_XorStr<_string_type, _length>& lhs, const _Basic_XorStr<_string_type, _length2>& rhs)
{
	static_assert(_length == _length2, "XorStr== different length");

	return _length == _length2 && lhs.str() == rhs.str();
}
//---------------------------------------------------------------------------
template<typename _string_type, size_t _length>
inline auto operator==(const _string_type& lhs, const _Basic_XorStr<_string_type, _length>& rhs)
{
	return lhs.size() == _length && lhs == rhs.str();
}
//---------------------------------------------------------------------------
template<typename _stream_type, typename _string_type, size_t _length>
inline auto& operator<<(_stream_type& lhs, const _Basic_XorStr<_string_type, _length>& rhs)
{
	lhs << rhs.c_str();

	return lhs;
}
//---------------------------------------------------------------------------
template<typename _string_type, size_t _length, size_t _length2>
inline auto operator+(const _Basic_XorStr<_string_type, _length>& lhs, const _Basic_XorStr<_string_type, _length2>& rhs)
{
	return lhs.str() + rhs.str();
}
//---------------------------------------------------------------------------
template<typename _string_type, size_t _length>
inline auto operator+(const _string_type& lhs, const _Basic_XorStr<_string_type, _length>& rhs)
{
	return lhs + rhs.str();
}
//---------------------------------------------------------------------------
template<size_t _length>
constexpr ALWAYS_INLINE auto _xor_(char const (&str)[_length])
{
	return XorStrA<_length>(str);
}
//---------------------------------------------------------------------------
template<size_t _length>
constexpr ALWAYS_INLINE auto _xor_(wchar_t const (&str)[_length])
{
	return XorStrW<_length>(str);
}
//---------------------------------------------------------------------------
template<size_t _length>
constexpr ALWAYS_INLINE auto _xor_(char16_t const (&str)[_length])
{
	return XorStrU16<_length>(str);
}
//---------------------------------------------------------------------------
template<size_t _length>
constexpr ALWAYS_INLINE auto _xor_(char32_t const (&str)[_length])
{
	return XorStrU32<_length>(str);
}
//---------------------------------------------------------------------------
#define E(str) _xor_(str).c_str()