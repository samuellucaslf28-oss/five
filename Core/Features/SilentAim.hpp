#pragma once
#include <Includes/Includes.hpp>
#include <Core/Offsets.hpp>
#include <Core/SDK/SDK.hpp>
namespace Core
{
	namespace Features
	{
		class cSilentAim
		{
		private:
			static bool SilentAimInitialized;
		private:
			static std::uintptr_t StartAddy;
			std::uintptr_t SilentAimHook;
		private:
			std::vector<std::uint8_t> OriginalFuncTable;
			std::vector<std::uint8_t> SilentAimShell =
			{
			0xC7, 0x45, 0x07,
			0x00, 0x00, 0x00, 0x00,
			0xC7, 0x45, 0x0B,
			0x00, 0x00, 0x00, 0x00,
			0xC7, 0x45, 0x0F,
			0x00, 0x00, 0x00, 0x00,
			0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};
		public:
			void InitializeSilentAim();
			void RestoreSilent();
			void HookSilent();
		};
		inline cSilentAim g_SilentAim;
	}
}
