#include "utilitys.h"
#include "settings.h"
#include <algorithm>

int X, Y;

int Width;
int Height;

struct {
	// Basic colors: ========================================================
	float Black[3];
	float RGBRed[3] = { 1.0f, 0.0f, 0.0f };
	float RGBYelllow[3] = { 1.0f, 1.0f, 0.0f };
	float RGBGreen[3] = { 0.0f, 1.0f, 0.0f };
	float RGBBlue[3] = { 0.0f, 0.0f, 1.0f };
	float CMYKRed[3] = { 0.92f, 0.10f, 0.14f };
	float CMYKYellow[3] = { 1.0f, 0.94f, 0.0f };
	float CMYKGreen[3] = { 0.0f, 0.65f, 3.17f };
	float CMYKBlue[3] = { 0.18f, 0.19f, 0.57f };
	float PastelRed[3] = { 0.96f, 0.58f, 0.47f };
	float PastelRedOrange[3] = { 0.97f, 0.67f, 0.50f };
	float PastelYellowOrange[3] = { 0.99f, 0.77f, 0.53f };
	float PastelYellow[3] = { 1.0f, 0.96f, 0.6f };
	float PastelPeaGreen[3] = { 0.76f, 0.87f, 0.60f };
	float PastelYellowGreen[3] = { 0.63f, 0.82f, 0.61f };
	float PastelGreen[3] = { 0.50f, 0.79f, 0.61f };
	float PastelGreenCyan[3] = { 0.47f, 0.8f, 0.78f };
	float PastelCyan[3] = { 0.42f, 0.81f, 0.96f };
	float PastelCyanBlue[3] = { 0.49f, 0.65f, 0.85f };
	float PastelBlue[3] = { 0.51f, 0.57f, 0.79f };
	float PastelBlueViolet[3] = { 0.52f, 0.50f, 0.74f };
	float PastelViolet[3] = { 0.63f, 0.52f, 0.74f };
	float PastelVioletMagenta[3] = { 0.74f, 0.54f, 0.74f };
	float PastelMagenta[3] = { 0.95f, 0.60f, 0.75f };
	float PastelMagentaRed[3] = { 0.96f, 0.59f, 0.61f };
	float LightRed[3] = { 0.94f, 0.42f, 0.30f };
	float LightRedOrange[3] = { 0.96f, 0.55f, 0.33f };
	float LightYellowOrange[3] = { 0.98f, 0.68f, 0.36f };
	float LightYellow[3] = { 1.0f, 0.96f, 0.40f };
	float LightPeaGreen[3] = { 0.67f, 0.82f, 0.45f };
	float LightYellowGreen[3] = { 0.48f, 0.77f, 0.46f };
	float LightGreen[3] = { 0.23f, 0.72f, 0.47f };
	float LightGreenCyan[3] = { 0.10f, 0.73f, 0.70f };
	float LightCyan[3] = { 0.0f, 0.74f, 0.95f };
	float LightCyanBlue[3] = { 0.26f, 0.54f, 0.79f };
	float LightBlue[3] = { 0.33f, 0.45f, 0.72f };
	float LightBlueViolet[3] = { 0.37f, 0.36f, 0.65f };
	float LightViolet[3] = { 0.52f, 0.37f, 0.65f };
	float LightVioletMagenta[3] = { 0.65f, 0.39f, 0.65f };
	float LightMagenta[3] = { 0.94f, 0.43f, 0.66f };
	float LightMagentaRed[3] = { 0.94f, 0.42f, 0.49f };
	float Red[3] = { 0.92f, 0.10f, 0.14f };
	float RedOrange[3] = { 0.94f, 0.39f, 0.13f };
	float YellowOrange[3] = { 0.96f, 0.58f, 0.11f };
	float Yellow[3] = { 1.0f, 0.94f, 0.0f };
	float PeaGreen[3] = { 0.55f, 0.77f, 0.24f };
	float YellowGreen[3] = { 0.22f, 0.70f, 0.29f };
	float Green[3] = { 0.0f, 0.65f, 0.31f };
	float GreenCyan[3] = { 0.0f, 0.66f, 0.61f };
	float Cyan[3] = { 0.0f, 0.68f, 0.93f };
	float CyanBlue[3] = { 0.0f, 0.44f, 0.34f };
	float Blue[3] = { 0.0f, 0.32f, 0.65f };
	float BlueViolet[3] = { 0.19f, 0.19f, 0.57f };
	float Violet[3] = { 0.18f, 0.19f, 0.57f };
	float VioletMagenta[3] = { 0.57f, 0.15f, 5.63f };
	float Magenta[3] = { 0.92f, 0.0f, 0.54f };
	float MagentaRed[3] = { 0.92f, 0.07f, 0.35f };
	float DarkRed[3] = { 0.61f, 0.04f, 0.05f };
	float DarkROrange[3] = { 0.62f, 0.25f, 0.05f };
	float DarkYellowOrange[3] = { 0.53f, 0.38f, 0.03f };
	float DarkYellow[3] = { 0.67f, 0.62f, 0.0f };
	float DarkPeaGreen[3] = { 0.34f, 0.52f, 0.15f };
	float DarkYellowGreen[3] = { 0.09f, 0.48f, 0.18f };
	float DarkGreen[3] = { 0.0f, 0.44f, 0.21f };
	float DarkGreenCyan[3] = { 0.0f, 0.45f, 0.41f };
	float DarkCyan[3] = { 0.0f, 0.46f, 0.63f };
	float DarkCyanBlue[3] = { 0.0f, 0.29f, 0.50f };
	float DarkBlue[3] = { 0.0f, 0.20f, 0.44f };
	float DarkBlueViolet[3] = { 0.10f, 0.07f, 0.39f };
	float DarkViolet[3] = { 0.26f, 0.05f, 0.38f };
	float DarkVioletMagenta[3] = { 0.38f, 0.01f, 0.37f };
	float DarkMagenta[3] = { 0.61f, 0.0f, 0.36f };
	float DarkMagentaRed[3] = { 0.61f, 0.0f, 0.22f };
	float DarkerRed[3] = { 0.47f, 0.0f, 0.0f };
	float DarkerROrange[3] = { 0.48f, 0.18f, 0.0f };
	float DarkerYellowOrange[3] = { 0.49f, 0.28f, 0.0f };
	float DarkerYellow[3] = { 0.50f, 0.48f, 0.0f };
	float DarkerPeaGreen[3] = { 0.25f, 0.4f, 0.09f };
	float DarkerYellowGreen[3] = { 0.0f, 0.36f, 0.12f };
	float DarkerGreen[3] = { 0.0f, 0.34f, 0.14f };
	float DarkerGreenCyan[3] = { 0.0f, 0.34f, 0.32f };
	float DarkerCyan[3] = { 0.0f, 0.35f, 0.49f };
	float DarkerCyanBlue[3] = { 0.0f, 0.21f, 0.38f };
	float DarkerBlue[3] = { 0.0f, 0.12f, 0.34f };
	float DarkerBlueViolet[3] = { 0.05f, 0.0f, 0.29f };
	float DarkerViolet[3] = { 0.19f, 0.0f, 0.29f };
	float DarkerVioletMagenta[3] = { 0.29f, 0.0f, 0.28f };
	float DarkerMagenta[3] = { 0.48f, 0.0f, 0.27f };
	float DarkerMagentaRed[3] = { 0.47f, 0.27f, 0.14f };
	float PaleCoolBrown[3] = { 0.78f, 0.69f, 0.61f };
	float LightCoolBrown[3] = { 0.6f, 0.52f, 0.45f };
	float MiumCoolBrown[3] = { 0.45f, 0.38f, 0.34f };
	float DarkCoolBrown[3] = { 0.32f, 0.27f, 0.25f };
	float DarkerCoolBrown[3] = { 0.21f, 0.18f, 0.17f };
	float PaleWarmBrown[3] = { 0.77f, 0.61f, 0.43f };
	float LightWarmBrown[3] = { 0.65f, 0.48f, 0.32f };
	float MiumWarmBrown[3] = { 0.54f, 0.38f, 0.22f };
	float DarkWarmBrown[3] = { 0.45f, 0.29f, 0.14f };
	float DarkerWarmBrown[3] = { 0.37f, 0.22f, 0.07f };
} color;

namespace detail
{
	extern "C" void* _spoofer_stub();

	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(
		const void* shell,
		Args... args
	) -> Ret
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper
	{
		template<
			typename Ret,
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
			static auto do_call(const void* shell, void* shell_param, First first, Second second,
				Third third, Fourth fourth, Pack... pack) -> Ret
		{
			return shellcode_stub_helper< Ret, First, Second, Third, Fourth, void*, void*, Pack... >(shell, first, second, third, fourth, shell_param, nullptr, pack...);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		template<
			typename Ret,
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first = First{},
				Second second = Second{},
				Third third = Third{},
				Fourth fourth = Fourth{}
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr
				);
		}
	};
}

namespace SDK
{
	namespace Utilities {
		uintptr_t GetImageBase() {
			return (uintptr_t)GetModuleHandleA(0);
		}

		template <typename Ret, typename... Args>
		static inline auto SpoofCall(Ret(*fn)(Args...), Args... args) -> Ret
		{
			static const void* jmprbx = nullptr;
			if (!jmprbx) {
				const auto ntdll = reinterpret_cast<const unsigned char*>(::GetModuleHandleW(NULL));
				const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(ntdll);
				const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(ntdll + dos->e_lfanew);
				const auto sections = IMAGE_FIRST_SECTION(nt);
				const auto num_sections = nt->FileHeader.NumberOfSections;

				constexpr char section_name[5]{ '.', 't', 'e', 'x', 't' };
				const auto     section = std::find_if(sections, sections + num_sections, [&](const auto& s) {
					return std::equal(s.Name, s.Name + 5, section_name);
					});

				constexpr unsigned char instr_bytes[2]{ 0xFF, 0x26 };
				const auto              va = ntdll + section->VirtualAddress;
				jmprbx = std::search(va, va + section->Misc.VirtualSize, instr_bytes, instr_bytes + 2);
			}

			struct shell_params
			{
				const void* trampoline;
				void* function;
				void* rdx;
			};

			shell_params p
			{
				jmprbx,
				reinterpret_cast<void*>(fn)
			};

			using mapper = detail::argument_remapper<sizeof...(Args), void>;
			return mapper::template do_call<Ret, Args...>((const void*)&detail::_spoofer_stub, &p, args...);
		}

		BOOL valid_pointer(DWORD64 address)
		{
			if (!IsBadWritePtr((LPVOID)address, (UINT_PTR)8)) return TRUE;
			else return FALSE;
		}

		template<typename T>
		T ReadMemory(DWORD_PTR address, const T& def = T())
		{
			if (valid_pointer(address))
				return *(T*)address;
		}

		template<typename T>
		T write(DWORD_PTR address, DWORD_PTR value, const T& def = T())
		{
			if (valid_pointer(address))
				return *(T*)address = value;
			else
				return T();
		}

		namespace Scanners
		{
			uintptr_t PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex = 0);
			uintptr_t PatternScan(const char* sSignature, size_t nSelectResultIndex = 0);

			uintptr_t PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex)
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
						else
							bytes.push_back(strtoul(current, &current, 16));
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
								return reinterpret_cast<uintptr_t>(&scanBytes[i]);
						}
						else
							return reinterpret_cast<uintptr_t>(&scanBytes[i]);
					}
				}

				return NULL;
			}

			uintptr_t PatternScan(const char* sSignature, size_t nSelectResultIndex)
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
		}
	}

	namespace Structs {
		class FLinearColor {
		public:

		};

		template<class T>
		struct TArray
		{
			friend struct FString;

		public:
			inline TArray()
			{
				Data = nullptr;
				Count = Max = 0;
			};

			inline int Num() const
			{
				return Count;
			};

			inline T& operator[](int i)
			{
				return Data[i];
			};

			inline const T& operator[](int i) const
			{
				return Data[i];
			};

			inline bool IsValidIndex(int i) const
			{
				return i < Num();
			}

		private:
			T* Data;
			int32_t Count;
			int32_t Max;
		};

		class FText {
		private:
			char _padding_[0x28];
			PWCHAR Name;
			DWORD Length;
		public:
			inline char* c_str()
			{
				char sBuff[255];
				Utilities::SpoofCall(wcstombs, (char*)sBuff, (const wchar_t*)this->Name, sizeof(sBuff));
				return sBuff;
			}
		};

		struct FString : private TArray<wchar_t>
		{
			inline FString()
			{
			};

			FString(const wchar_t* other)
			{
				Max = Count = *other ? std::wcslen(other) + 1 : 0;

				if (Count)
				{
					Data = const_cast<wchar_t*>(other);
				}
			};

			inline bool IsValid() const
			{
				return Data != nullptr;
			}

			inline const wchar_t* c_str() const
			{
				return Data;
			}

			std::string ToString() const
			{
				auto length = std::wcslen(Data);

				std::string str(length, '\0');

				std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

				return str;
			}
		};

		struct FVector2D {
			float x;
			float y;

			inline BOOL IsValid() {
				return X != NULL && Y != NULL;
			}

			inline float distance() {
				return sqrtf(this->x * this->x + this->y * this->y);
			}
		};

		class Vector3
		{
		public:
			// Constructors
			Vector3() : x(0.f), y(0.f), z(0.f)
			{

			}

			Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
			{

			}

			Vector3(float _v) : x(_v), y(_v), z(_v)
			{

			}

			~Vector3()
			{

			}

			// Variables
			float x;
			float y;
			float z;

			//Functions
			inline bool Zero() const
			{
				return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f && z > -0.1f && z < 0.1f);
			}

			inline float Dot(Vector3 v)
			{
				return x * v.x + y * v.y + z * v.z;
			}

			// Functions
			inline float Distance(Vector3 v)
			{
				return Utilities::SpoofCall(sqrtf, (Utilities::SpoofCall(powf, (v.x - x), 2.0f) + Utilities::SpoofCall(powf, (v.y - y), 2.0f) + Utilities::SpoofCall(powf, (v.z - z), 2.0f))) / 100.0f;
			}

			inline double Length() {
				return sqrt(x * x + y * y + z * z);
			}

			// Operators
			Vector3 operator+(Vector3 v)
			{
				return Vector3(x + v.x, y + v.y, z + v.z);
			}

			Vector3 operator-(Vector3 v)
			{
				return Vector3(x - v.x, y - v.y, z - v.z);
			}

			Vector3 operator*(float number) const {
				return Vector3(x * number, y * number, z * number);
			}

			Vector3 operator/(float number) const {
				return Vector3(x / number, y / number, z / number);
			}
		};

		class FRotator
		{
		public:
			FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f)
			{

			}

			FRotator(float _Pitch, float _Yaw, float _Roll) : Pitch(_Pitch), Yaw(_Yaw), Roll(_Roll)
			{

			}
			~FRotator()
			{

			}

			float Pitch;
			float Yaw;
			float Roll;


			double Length() {
				return sqrt(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
			}

			FRotator operator+(FRotator angB) { return FRotator(Pitch + angB.Pitch, Yaw + angB.Yaw, Roll + angB.Roll); }
			FRotator operator-(FRotator angB) { return FRotator(Pitch - angB.Pitch, Yaw - angB.Yaw, Roll - angB.Roll); }
			FRotator operator/(float flNum) { return FRotator(Pitch / flNum, Yaw / flNum, Roll / flNum); }
			FRotator operator*(float flNum) { return FRotator(Pitch * flNum, Yaw * flNum, Roll * flNum); }
			bool operator==(FRotator angB) { return Pitch == angB.Pitch && Yaw == angB.Yaw && Yaw == angB.Yaw; }
			bool operator!=(FRotator angB) { return Pitch != angB.Pitch || Yaw != angB.Yaw || Yaw != angB.Yaw; }

		};

		typedef struct {
			float X, Y, Z;
		} FVector;

		class PlayerInfo {
		public:
			uintptr_t Mesh;
			uintptr_t Raw;
			uintptr_t State;
			uintptr_t TeamIndex;
		};

		class FMinimalViewInfo
		{
		public:
			Vector3 Loc;
			Vector3 Rot;
			float FOV;
		};

		struct FMatrix
		{
			float M[4][4];
		};
		static FMatrix* myMatrix = new FMatrix();
	}

	namespace Classes
	{
		namespace StaticOffsets {
			uintptr_t OwningGameInstance = 0x180;
			uintptr_t LocalPlayers = 0x38;
			uintptr_t PlayerController = 0x30;
			uintptr_t PlayerCameraManager = 0x2B8;
			uintptr_t AcknowledgedPawn = 0x2A0;

			uintptr_t Levels = 0x138;
			uintptr_t PersistentLevel = 0x30;
			uintptr_t AActors = 0x98;
			uintptr_t ActorCount = 0xA0;

			uintptr_t RootComponent = 0x130;
			uintptr_t FireStartLoc = 0x878;
			uintptr_t RelativeLocation = 0x11c;
			uintptr_t RelativeRotation = 0x128;
			uintptr_t CurrentWeapon = 0x5D0;
			uintptr_t PlayerState = 0x240;
			uintptr_t Mesh = 0x280;
			uintptr_t TeamIndex = 0xED0;
			uintptr_t SquadID = 0x103C;

			uintptr_t bIsDying = 0x538;
			uintptr_t bIsDBNO = 0x552;

			uintptr_t WeaponData = 0x378;
			uintptr_t DisplayName = 0x80;
			uintptr_t PrimaryPickupItemEntry = 0x2A8;
			uintptr_t ItemDefinition = 0x18;
			uintptr_t Tier = 0x64;

			uintptr_t LastFireTime = 0x8FC;
			uintptr_t LastFireTimeVerified = 0x900;
			uintptr_t LastFireAbilityTime = 0xB40;

			uintptr_t bAlreadySearched = 0xC61;
			uintptr_t IsReloading = 0x2B1;
		}

		class USkeletalMeshComponent
		{
		private:
		public:
			static Structs::Vector3 GetBoneLocation(uintptr_t CurrentActor, int id, Structs::Vector3* out)
			{
				static uintptr_t addr = 0;
				if (!addr) {
					addr = SDK::Utilities::Scanners::PatternScan(E("E8 ? ? ? ? 48 8B 47 30 F3 0F 10 45"));
					addr = (addr + *(DWORD*)(addr + 0x1) + 0x5 - 0x100000000);
					if (!addr) {
						SDK::Utilities::SpoofCall(MessageBoxA, (HWND)0, (LPCSTR)E("Something Failed!!"), (LPCSTR)0, (UINT)0);
						exit(0);
					}
				}

				uintptr_t mesh = SDK::Utilities::ReadMemory<uintptr_t>(CurrentActor + StaticOffsets::Mesh);
				if (!mesh) return { 0,0,0 };

				auto fGetBoneMatrix = ((Structs::FMatrix * (__fastcall*)(uintptr_t, Structs::FMatrix*, int))(addr));
				Utilities::SpoofCall(fGetBoneMatrix, mesh, Structs::myMatrix, id);

				out->x = Structs::myMatrix->M[3][0];
				out->y = Structs::myMatrix->M[3][1];
				out->z = Structs::myMatrix->M[3][2];

				return Structs::Vector3(0, 0, 0);
			}
		};

		class APlayerCameraManager
		{
		public:
			static float GetFOVAngle(uintptr_t PlayerCameraManager)
			{
				auto GetFOVAngle = reinterpret_cast<float(*)(UINT64, char*)>(*(ULONG_PTR*)(*(ULONG_PTR*)PlayerCameraManager + 0x6D0));
				return Utilities::SpoofCall(GetFOVAngle, (ULONG_PTR)PlayerCameraManager, (char*)0);
			}

			static Structs::Vector3 GetCameraLocation(uintptr_t PlayerCameraManager)
			{
				auto GetCameraLocation = reinterpret_cast<Structs::Vector3(*)(UINT64, char*)>(*(ULONG_PTR*)(*(ULONG_PTR*)PlayerCameraManager + 0x718));
				return Utilities::SpoofCall(GetCameraLocation, (ULONG_PTR)PlayerCameraManager, (char*)0);
			}

			static Structs::Vector3 GetCameraRotation(uintptr_t PlayerCameraManager)
			{
				auto GetCameraRotation = reinterpret_cast<Structs::Vector3(*)(UINT64, char*)>(*(ULONG_PTR*)(*(ULONG_PTR*)PlayerCameraManager + 0x710));
				return Utilities::SpoofCall(GetCameraRotation, (ULONG_PTR)PlayerCameraManager, (char*)0);
			}

			static VOID GetCameraInfo(uintptr_t Controller, Structs::Vector3* pLocation, Structs::Vector3* pRotation) {
				auto GetPlayerViewPoint = reinterpret_cast<char(*)(ULONG_PTR, Structs::Vector3*, Structs::Vector3*)>(*(ULONG_PTR*)(*(ULONG_PTR*)Controller + 0x708));
				Utilities::SpoofCall(GetPlayerViewPoint, (ULONG_PTR)Controller, pLocation, pRotation);
			}
			static BOOLEAN LineOfSightTo(PVOID PlayerController, PVOID Actor, SDK::Structs::Vector3* ViewPoint) {

				auto LOSTo = reinterpret_cast<bool(__fastcall*)(PVOID PlayerController, PVOID Actor, SDK::Structs::Vector3 * ViewPoint)>(LineOfS);

				return Utilities::SpoofCall(LOSTo, PlayerController, Actor, ViewPoint);
			}
			uintptr_t GetCurrentState(uintptr_t base)
			{
				static uintptr_t returnval = 0;
				returnval = SDK::Utilities::ReadMemory<uintptr_t>(base + SDK::Classes::StaticOffsets::PlayerState);
				return returnval;
			}
		};

		class AController
		{
		public:
			static uintptr_t GetControlRotation(uintptr_t a1, uintptr_t a2, uintptr_t a3)
			{
				uintptr_t v3; // rbx
				uintptr_t v4; // rax
				uintptr_t result; // rax
				char v6; // [rsp+20h] [rbp-18h]

				v3 = a3;
				*(uintptr_t*)(a2 + 32) += *(uintptr_t*)(a2 + 32) != 0x0;
				v4 = (*(__int64(__fastcall**)(__int64, char*))(*(uintptr_t*)a1 + 0x688))(a1, &v6);
				*(uintptr_t*)v3 = *(uintptr_t*)v4;
				result = *(unsigned int*)(v4 + sizeof(uintptr_t));
				*(uintptr_t*)(v3 + 8) = result;
				return result;
			}

			static bool LineOfSightTo(uintptr_t Actor)
			{
				auto LineOfSightTo_ = (*(bool(__fastcall**)(uintptr_t Controller, uintptr_t Other, SDK::Structs::Vector3 ViewPoint, bool bAlternativeChecks))(*(uintptr_t*)PlayerController + 0x698));
				return SDK::Utilities::SpoofCall(LineOfSightTo_, PlayerController, Actor, SDK::Structs::Vector3(0, 0, 0), true);
			}

			static void ClientSetRotation(SDK::Structs::Vector3 NewRotation, bool bResetCamera = false)
			{
				auto ClientSetRotation_ = (*(void(__fastcall**)(uintptr_t Controller, SDK::Structs::Vector3 NewRotation, bool bResetCamera))(*(uintptr_t*)PlayerController + 0x640));
				SDK::Utilities::SpoofCall(ClientSetRotation_, PlayerController, NewRotation, bResetCamera);
			}

			static void ValidateClientSetRotation(SDK::Structs::Vector3 NewRotation, bool bResetCamera = false)
			{
				auto ValidateClientSetRotation_ = (*(void(__fastcall**)(uintptr_t Controller, SDK::Structs::Vector3 NewRotation, bool bResetCamera))(*(uintptr_t*)PlayerController + 0x638));
				SDK::Utilities::SpoofCall(ValidateClientSetRotation_, PlayerController, NewRotation, bResetCamera);
			}

			static void SetControlRotation(SDK::Structs::Vector3 NewRotation, bool bResetCamera = false)
			{
				auto SetControlRotation_ = (*(void(__fastcall**)(uintptr_t Controller, SDK::Structs::Vector3 NewRotation, bool bResetCamera))(*(uintptr_t*)PlayerController + 0x688));
				SDK::Utilities::SpoofCall(SetControlRotation_, PlayerController, NewRotation, bResetCamera);
			}

			static void SetIgnoreLookInput(char bNewLookInput)
			{
				auto SetIgnoreLookInput_ = (*(void(__fastcall**)(uintptr_t Controller, char bNewLookInput))(*(uintptr_t*)PlayerController + 0x748));
				SDK::Utilities::SpoofCall(SetIgnoreLookInput_, (uintptr_t)PlayerController, bNewLookInput);
			}

			static void ClientSetCameraMode(int h)
			{
				auto ClientSetCameraMode_ = (*(void(__fastcall**)(uintptr_t Controller, int h))(*(uintptr_t*)PlayerController + 0x920));
				SDK::Utilities::SpoofCall(ClientSetCameraMode_, (uintptr_t)PlayerController, h);
			}

			static Structs::Vector3 WorldToScreen(SDK::Structs::Vector3 vWorldPos, SDK::Structs::Vector3* vScreenPos)
			{
				static uintptr_t addr = 0;

				if (!addr) {
					addr = SDK::Utilities::Scanners::PatternScan(E("E8 ? ? ? ? 41 88 07 48 83 C4 30"));;
					addr = RVA(addr, 5);
					if (!addr) {
						SDK::Utilities::SpoofCall(MessageBoxA, (HWND)0, (LPCSTR)E("Something Failed"), (LPCSTR)0, (UINT)0);
						exit(0);
					}
				}

				auto WorldToScreen = reinterpret_cast<bool(__fastcall*)(uintptr_t pPlayerController, SDK::Structs::Vector3 vWorldPos, SDK::Structs::Vector3 * vScreenPosOut, char)>(addr);

				return SDK::Utilities::SpoofCall(WorldToScreen, (uintptr_t)PlayerController, vWorldPos, vScreenPos, (char)0);
				//auto WorldToScreen_ = (*(void(__fastcall**)(uintptr_t Controller, SDK::Structs::Vector3 vWorldPos, SDK::Structs::Vector3 * vScreenPosOut, char camerareset))(*(uintptr_t*)PlayerController + 0xAD8));
				//SDK::Utilities::SpoofCall(WorldToScreen_, PlayerController, vWorldPos, vScreenPos, (char)0);
			}
		};

		namespace Utils
		{
			uintptr_t State(uintptr_t base)
			{
				static uintptr_t returnval = 0;
				returnval = SDK::Utilities::ReadMemory<uintptr_t>(base + SDK::Classes::StaticOffsets::PlayerState);
				return returnval;
			}

			bool CheckInScreen(uintptr_t CurrentActor, int Width, int Height) {
				SDK::Structs::Vector3 Pos;
				Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 66, &Pos);
				Classes::AController::WorldToScreen(Pos, &Pos);
				if (CurrentActor)
				{
					if (Pos.x > 0 and Pos.y > 0) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
		class UCanvas
		{
		public:
			unsigned char Padding_jYrEa[0x28];
			float OrgX; // 0x28(0x4)
			// No Padding Required Here
			float OrgY; // 0x2c(0x4)
			// No Padding Required Here
			float ClipX; // 0x30(0x4)
			// No Padding Required Here
			float ClipY; // 0x34(0x4)
			// No Padding Required Here
			//struct SDK::Structs::FColor DrawColor; // 0x38(0x4)
			// No Padding Required Here
			char bCenterX : 1; // 0x3c(0x1)
			// No Padding Required Here
			char bCenterY : 1; // 0x3c(0x1)
			// No Padding Required Here
			char bNoSmooth : 1; // 0x3c(0x1)
			// No Padding Required Here
			unsigned char UnknownBuffer_GsD24 : 5; // 0x3c(0x1)
			// No Padding Required Here
			unsigned char UnknownBuffer_Pu72n[0x3]; // 0x3d(0x3)
			// No Padding Required Here
			int32_t SizeX; // 0x40(0x4)
			// No Padding Required Here
			int32_t SizeY; // 0x44(0x4)
			// No Padding Required Here
			unsigned char UnknownBuffer_67hdW[0x8]; // 0x48(0x8)
			// No Padding Required Here
			unsigned char ColorModulate[0x10]; // 0x50(0x10)
			// No Padding Required Here
			PVOID DefaultTexture; // 0x60(0x8)
			// No Padding Required Here
			PVOID GradientTexture0; // 0x68(0x8)
			// No Padding Required Here
			PVOID ReporterGraph; // 0x70(0x8)
		};
	}

	namespace Utilities {
		Structs::Vector3 CamLoc;
		Structs::Vector3 CamRot;

		double GetCrossDistance(double x1, double y1, double x2, double y2)
		{
			return sqrtf_(powf_((float)(x1 - x2), (float)2) + powf_((float)(y1 - y2), (float)2));
		}
		bool CheckInScreen(uintptr_t CurrentActor, int Width, int Height) {
			SDK::Structs::Vector3 Pos;
			Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 66, &Pos);
			Classes::AController::WorldToScreen(Pos, &Pos);
			if (CurrentActor)
			{
				if (Pos.x > 0 and Pos.y > 0) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		bool CheckIfInFOV(uintptr_t CurrentActor, float& max)
		{
			SDK::Structs::Vector3 Pos;
			Classes::USkeletalMeshComponent::GetBoneLocation(CurrentActor, 66, &Pos);
			Classes::AController::WorldToScreen(Pos, &Pos);
			if (CurrentActor)
			{
				float Dist = GetCrossDistance(Pos.x, Pos.y, (X / 2), (Y / 2));

				if (Dist < max)
				{
					float Radius = (Settings::FOVRadius);

					if (Pos.x <= ((X / 2) + Radius) &&
						Pos.x >= ((X / 2) - Radius) &&
						Pos.y <= ((Y / 2) + Radius) &&
						Pos.y >= ((Y / 2) - Radius))
					{
						max = Dist;
						return true;
					}

					return false;
				}
			}

			return false;
		}

		void Snapline(uintptr_t a)
		{
			SDK::Structs::Vector3 rootHead, rootHeadOut;
			SDK::Classes::USkeletalMeshComponent::GetBoneLocation(a, 66, &rootHead);
			SDK::Classes::AController::WorldToScreen(rootHead, &rootHead);;

			if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
				if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, Width / 2, Height / 2) <= Settings::FOVRadius * 1)) {
					if (Settings::Lines) {
						ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(rootHeadOut.x, rootHeadOut.y), ImColor(0, 255, 255, 200), 1);
					}
				}
			}
		}

		Structs::Vector3 GetRotation(uintptr_t a)
		{
			Structs::Vector3 RetVector = { 0,0,0 };

			Structs::Vector3 rootHead;
			SDK::Classes::USkeletalMeshComponent::GetBoneLocation(a, 66, &rootHead);

			if (rootHead.x == 0 && rootHead.y == 0) return Structs::Vector3(0, 0, 0);

			Structs::Vector3 VectorPos = rootHead - CamLoc;

			float distance = VectorPos.Length();
			RetVector.x = -(((float)acos(VectorPos.z / distance) * (float)(180.0f / M_PI)) - 90.f);
			RetVector.y = (float)atan2(VectorPos.y, VectorPos.x) * (float)(180.0f / M_PI);

			return RetVector;
		}

		Structs::Vector3 SmoothAngles(Structs::Vector3 rot1, Structs::Vector3 rot2)
		{
			Structs::Vector3 ret;
			auto currentRotation = rot1;

			ret.x = (rot2.x - rot1.x) / Settings::Smoothing + rot1.x;
			ret.y = (rot2.y - rot1.y) / Settings::Smoothing + rot1.y;

			return ret;
		}

		Structs::Vector3 GetPawnRootLocation(uintptr_t CurrentActor)
		{
			uintptr_t RootComponent = SDK::Utilities::ReadMemory<uintptr_t>(CurrentActor + Classes::StaticOffsets::RootComponent);
			Structs::Vector3 RelativeLocation = *(Structs::Vector3*)(RootComponent + Classes::StaticOffsets::RelativeLocation);
			return RelativeLocation;
		}

		Structs::Vector3 GetPawnRootRotation(uintptr_t CurrentActor)
		{
			uintptr_t RootComponent = SDK::Utilities::ReadMemory<uintptr_t>(CurrentActor + Classes::StaticOffsets::RootComponent);
			Structs::Vector3 RelativeRotation = *(Structs::Vector3*)(RootComponent + Classes::StaticOffsets::RelativeRotation);
			return RelativeRotation;
		}
	}
}

bool GetPlayerViewPoint(uintptr_t PlayerController, SDK::Structs::Vector3* vCameraPos, SDK::Structs::Vector3* vCameraRot)
{
	if (!PlayerController) return false;

	static uintptr_t pGetPlayerViewPoint = 0;
	if (!pGetPlayerViewPoint)
	{
		uintptr_t VTable = *(uintptr_t*)PlayerController;
		if (!VTable)  return false;

		pGetPlayerViewPoint = *(uintptr_t*)(VTable + 0x708);
		if (!pGetPlayerViewPoint)  return false;
	}

	auto GetPlayerViewPoint = reinterpret_cast<void(__fastcall*)(uintptr_t, SDK::Structs::Vector3*, SDK::Structs::Vector3*)>(pGetPlayerViewPoint);

	SDK::Utilities::SpoofCall(GetPlayerViewPoint, (uintptr_t)PlayerController, vCameraPos, vCameraRot);

	return true;
}

void FreeObjName(__int64 address)
{
	static uintptr_t addr = 0;

	if (!addr) {
		addr = SDK::Utilities::Scanners::PatternScan(E("48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0"));;
		if (!addr) {
			SDK::Utilities::SpoofCall(MessageBoxA, (HWND)0, (LPCSTR)E("Something Failed"), (LPCSTR)0, (UINT)0);
			exit(0);
		}
	}

	auto func = reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(addr);

	func(address);
}
class UClass {
public:
	BYTE _padding_0[0x40];
	UClass* SuperClass;
};
class UObject {
public:
	PVOID VTableObject;
	DWORD ObjectFlags;
	DWORD InternalIndex;
	UClass* Class;
	BYTE _padding_0[0x8];
	UObject* Outer;

	inline BOOLEAN IsA(PVOID parentClass) {
		for (auto super = this->Class; super; super = super->SuperClass) {
			if (super == parentClass) {
				return TRUE;
			}
		}

		return FALSE;
	}
};

SDK::Structs::FString(*GetObjectNameInternal)(PVOID) = nullptr;

std::string GetObjectName(uintptr_t Object) {

	static uintptr_t addr = 0;
	if (!addr) {
		addr = Utilitys::GetObjName;
	}
	if (Object == NULL)
		return ("");
	auto fGetObjName = reinterpret_cast<SDK::Structs::FString * (__fastcall*)(int* index, SDK::Structs::FString * res)>(addr);
	int index = *(int*)(Object + 0x18);
	SDK::Structs::FString result;
	fGetObjName(&index, &result);
	if (result.c_str() == NULL)
		return ("");
	auto result_str = result.ToString();
	if (result.c_str() != NULL)
		FreeObjName((__int64)result.c_str());
	return result_str;
}

std::wstring GetObjectFirstName(UObject* object) {
	auto internalName = GetObjectNameInternal(object);
	if (!internalName.c_str()) {
		return L"";
	}

	std::wstring name(internalName.c_str());
	FreeObjName((__int64)internalName.c_str());

	return name;
}

#include <d3d9.h>

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};
#define ReadFTRANSFORM(base, offset) (*(FTransform *)(((PBYTE)base + offset)))
struct FTransform
{
	FQuat rot;
	SDK::Structs::Vector3 translation;
	char pad[4];
	SDK::Structs::Vector3 scale;
	char pad1[4];


	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};


D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}