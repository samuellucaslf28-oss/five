#pragma once
#include <Includes/Includes.hpp>
#include <Core/Offsets.hpp>
#include <unordered_map>
#include <mutex>

namespace Core::SDK::Structs { class CPed; }

namespace Core::Features
{
    namespace Visibility
    {
        struct OcclusionTail { int pixel_count; uint32_t query_flags; };
        inline std::unordered_map<uintptr_t, bool> g_FlaggedPeds;
        inline std::unordered_map<uintptr_t, uintptr_t> g_LastTimeSeenMap;
        inline std::mutex g_FlagMutex;

        inline bool IsVisible(CPed* ped)
        {
            uintptr_t pedAddr = reinterpret_cast<uintptr_t>(ped);
            if (!pedAddr || !Mem.ProcHandle || !Mem.ModBase)
                return true;

            // Flags de entidade no offset 0xC0 (bit 29)
            uint32_t entity_flags = Mem.Read<uint32_t>(pedAddr + 0xC0);
            if ((entity_flags & (1u << 29)) == 0u) {
                Mem.Write<uint32_t>(pedAddr + 0xC0, entity_flags | (1u << 29));
            }

            uint64_t fx_draw_data = Mem.Read<uint64_t>(pedAddr + 0x48);
            if (!fx_draw_data) {
                return ped->HasFlag(ePedConfigFlag::CPED_CONFIG_FLAG_VisibleOnScreen);
            }

            uint32_t query_id = static_cast<uint32_t>(Mem.Read<uint8_t>(fx_draw_data + 0x2B)) & 0xFF;
            bool is_visible = false;

            if (query_id > 0 && query_id <= 1000)
            {
                uintptr_t raycast_table = g_Offsets.m_RaycastTable;
                if (!raycast_table) {
                    // Fallback para builds específicas se o scan falhar
                    switch (g_Offsets.CurrentBuild) {
                        case 2802: case 2944: case 3258: raycast_table = Mem.ModBase + 0x2559A50; break;
                        case 3095: raycast_table = Mem.ModBase + 0x253C750; break;
                        case 3323: raycast_table = Mem.ModBase + 0x2569B20; break;
                        case 3407: raycast_table = Mem.ModBase + 0x257F060; break;
                        case 3570: raycast_table = Mem.ModBase + 0x25945D0; break;
                        default:   raycast_table = Mem.ModBase + 0x2559A50; break;
                    }
                }

                int visibility_value = Mem.Read<int>(raycast_table + ((query_id - 1) * 0x80) + 0x78);
                is_visible = visibility_value > 100;
            }
            else
            {                uintptr_t last_time_seen = Mem.Read<uintptr_t>(fx_draw_data + 0x18);
                
                std::lock_guard<std::mutex> lock(g_FlagMutex);
                if (last_time_seen > g_LastTimeSeenMap[pedAddr]) {
                    is_visible = true;
                }
                g_LastTimeSeenMap[pedAddr] = last_time_seen;
                
                // Limpeza periódica do mapa para evitar leak de memória
                if (g_LastTimeSeenMap.size() > 4096) g_LastTimeSeenMap.clear();
            }

            return is_visible;
        }
    }
}