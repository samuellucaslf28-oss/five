#pragma once
namespace Core {
class OffsetsClass {
public:
uintptr_t m_World,
m_ReplayInterFace,
m_ViewPort,
m_BlipList,
m_CamGameplayDirector,
m_LocalPlayer;
uintptr_t m_SilentAim,
m_InfiniteAmmo0,
m_InfiniteAmmo1,
m_MagicBulletsPatch,
m_ArmsKinematics,
m_LegsKinematics,
m_InfiniteCombatRoll,
m_GiveWeapon;
uintptr_t m_LastVehicle,
m_Handling,
m_VehicleEngineHealth,
m_PlayerInfo,
m_FragInst,
m_OffsetPool,
m_Armor,
m_Recoil,
m_PedFlag,
m_Spread,
m_WeaponManager,
m_WeaponInfo,
m_VehicleDoorsLockState,
m_EntityType,
m_Speed,
m_MaxHealth,
m_VehicleDriver,
m_VehicleGravity,
m_CObject,
m_NoRagDoll,
m_CWeapon,
m_PlayerId,
m_CitizenNamesModBase,
m_NetIdToNamesEntry,
m_SeatBealt,
m_AimCPedPatternResult,
m_VehicleExtras,
m_LastVisibleTime,
m_RaycastTable;
int CurrentBuild;
std::string ServerIp;
};
inline OffsetsClass g_Offsets;
}
