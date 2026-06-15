#include "Aimbot.hpp"
#include "Visibility.hpp"

#define SKEL_HEAD   0x796e
#define SKEL_NECK   0x9995
#define SKEL_SPINE  0x60f2

void Core::Features::cAimbot::SetViewAngles(CPed* ped, D3DXVECTOR3 bonePos) {
    auto cam = Mem.Read<uintptr_t>(Core::SDK::Pointers::pCamGamePlayDirector + 0x2C0);
    if (!cam) return;

    auto camPos = Mem.Read<D3DXVECTOR3>(cam + 0x60);
    auto camAngles = Mem.Read<D3DXVECTOR3>(cam + 0x40);
    D3DXVec3Normalize(&camAngles, &camAngles);

    auto veh = Mem.Read<uintptr_t>(cam + 0x10);
    if (!veh) return;

    if (Core::SDK::Pointers::pLocalPlayer->InVehicle()) {
        float state = Mem.Read<float>(veh + 0x2AC);
        if (state == -2.f) {
            Mem.Write<float>(veh + 0x2AC, 0.f);
            Mem.Write<float>(veh + 0x2C0, 111.f);
            Mem.Write<float>(veh + 0x2C4, 111.f);
        }
    }

    D3DXVECTOR3 aimDir = bonePos - camPos;
    D3DXVec3Normalize(&aimDir, &aimDir);
    D3DXVECTOR3 result = aimDir;

    auto& cfg = g_Config.Aimbot;

    if (cfg->SmoothHorizontal > 1 || cfg->SmoothVertical > 1) {
        D3DXVECTOR3 delta = aimDir - camAngles;
        if (cfg->SmoothHorizontal > 1) {
            result.x = camAngles.x + delta.x / cfg->SmoothHorizontal;
            result.y = camAngles.y + delta.y / cfg->SmoothHorizontal;
        }
        if (cfg->SmoothVertical > 1) {
            result.z = camAngles.z + delta.z / cfg->SmoothVertical;
        }
        auto third = result;
        third.z -= (camAngles.z - Mem.Read<D3DXVECTOR3>(cam + 0x3D0).z);

        Mem.Write<D3DXVECTOR3>(cam + 0x40, result);
        Mem.Write<D3DXVECTOR3>(cam + 0x3D0, third);
    }
    else {
        Mem.Write<D3DXVECTOR3>(cam + 0x40, aimDir);
        Mem.Write<D3DXVECTOR3>(cam + 0x3D0, aimDir);
    }
}

void Core::Features::cAimbot::Start() {
    while (true) {
        auto& cfg = g_Config.Aimbot;

        if (!cfg->Enabled || !cfg->KeyBind || !(GetAsyncKeyState(cfg->KeyBind) & 0x8000) || GetForegroundWindow() == g_Variables.g_hCheatWindow) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            continue;
        }

        auto ped = Core::SDK::Game::GetClosestPed(cfg->MaxDistance, cfg->IgnoreNPCs, cfg->OnlyVisible);
        if (!ped) { std::this_thread::sleep_for(std::chrono::nanoseconds(1)); continue; }

        auto frag = Mem.Read<uintptr_t>((uintptr_t)ped + g_Offsets.m_FragInst);
        auto base = Mem.Read<uintptr_t>(frag + 0x68);
        if (!base) continue;

        Core::SDK::Game::cSkeleton_t Skeleton;
        Skeleton.m_pSkeleton = Mem.Read<uintptr_t>(base + 0x178);
        Skeleton.crSkeletonData.Ptr = Mem.Read<uintptr_t>(Skeleton.m_pSkeleton);
        Skeleton.crSkeletonData.m_Used = Mem.Read<unsigned int>(Skeleton.crSkeletonData.Ptr + 0x1A);
        Skeleton.crSkeletonData.m_NumBones = Mem.Read<unsigned int>(Skeleton.crSkeletonData.Ptr + 0x5E);
        Skeleton.crSkeletonData.m_BoneIdTable_Slots = Mem.Read<unsigned short>(Skeleton.crSkeletonData.Ptr + 0x18);
        if (!Skeleton.crSkeletonData.m_BoneIdTable_Slots) continue;
        Skeleton.crSkeletonData.m_BoneIdTable = Mem.Read<uintptr_t>(Skeleton.crSkeletonData.Ptr + 0x10);
        Skeleton.Arg1 = Mem.Read<D3DXMATRIX>(Mem.Read<uintptr_t>(Skeleton.m_pSkeleton + 0x8));
        Skeleton.Arg2 = Mem.Read<uintptr_t>(Skeleton.m_pSkeleton + 0x18);

        uint16_t boneID;
        switch (cfg->HitBox)
        {
        case 0: boneID = SKEL_HEAD; break;
        case 1: boneID = SKEL_NECK; break;
        case 2: boneID = SKEL_SPINE; break;
        default: boneID = SKEL_HEAD; break;
        }

        auto targetPos = Core::SDK::Game::GetBonePosComplex(ped, boneID, Skeleton);
        auto screen = Core::SDK::Game::WorldToScreen(targetPos);
        if (!Core::SDK::Game::IsOnScreen(screen)) continue;

        float fov = std::hypot(screen.x - g_Variables.g_vGameWindowCenter.x,
            screen.y - g_Variables.g_vGameWindowCenter.y);

        if (fov < cfg->FOV) {
            SetViewAngles(ped, targetPos + D3DXVECTOR3(0, 0, 0.08f));
        }

        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}