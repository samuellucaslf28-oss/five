#pragma once
#include <Includes/includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <Core/Core.hpp>
#include <Core/Features/Exploits/Exploits.hpp>
#include <Core/Features/Exploits/HandlingEditor.hpp>
using namespace std;
namespace Local {
static int iSubTabCount = 0;
static float SubTabAlpha = 0.f;
static int iSubTab = 0;
void Render( )
{
SubTabAlpha = ImClamp( SubTabAlpha + ( 5.f * ImGui::GetIO( ).DeltaTime * ( iSubTabCount == iSubTab ? 1.f : -1.f ) ), 0.f, 1.f );
if ( SubTabAlpha == 0.f ) iSubTab = iSubTabCount;
ImGui::PushStyleVar( ImGuiStyleVar_Alpha, SubTabAlpha * ImGui::GetStyle( ).Alpha );
ImGui::SetCursorPos( ImVec2(90, 76) );
ImGui::BeginGroup( );
{
switch ( iSubTab )
{
case 0:
ImGui::BeginGroup( );
{
ImGui::BeginChild(xorstr("Local Player Mods"), ImVec2(230, 400), false, 0);
{
if (Custom::CheckBox(xorstr("God Mode"), &g_Config.Player->EnableGodMode)) {
Core::SDK::Pointers::pLocalPlayer->SetGodMode(g_Config.Player->EnableGodMode);
}
static int KeyModeGod = 1;
ImGui::Keybind(xorstr("God Mode Key"), &g_Config.Player->GodModeKey, &KeyModeGod);
if ( Custom::CheckBox( xorstr( "Anti-Aim" ), &g_Config.Player->AntiAimEnabled ) )
{
    if ( g_Config.Player->AntiAimEnabled ) {
        Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( ePedConfigFlag::CPED_CONFIG_FLAG_DisablePlayerLockon, true );
        Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( ePedConfigFlag::CPED_CONFIG_FLAG_AllowPlayerLockOnIfFriendly, true );
        Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( ePedConfigFlag::CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamage, true );
    }
    else {
        Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( ePedConfigFlag::CPED_CONFIG_FLAG_DisablePlayerLockon, false );
        Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( ePedConfigFlag::CPED_CONFIG_FLAG_AllowPlayerLockOnIfFriendly, false );
        Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( ePedConfigFlag::CPED_CONFIG_FLAG_TreatAsFriendlyForTargetingAndDamage, false );
    }
}
if (g_Config.Player->AntiAimEnabled)
{
    static int AntiAimKeyMode = 1;
    ImGui::Keybind(xorstr("Anti-Aim Bind"), &g_Config.Player->AntiAimKey, &AntiAimKeyMode);
}
if (Custom::CheckBox(xorstr("Anti HeadShot"), &g_Config.Player->AntiHSEnabled, true, xorstr("That function can be detected by server AntiCheat"), ICON_FA_TRIANGLE_EXCLAMATION))
{
Core::SDK::Pointers::pLocalPlayer->SetConfigFlag(ePedConfigFlag::CPED_CONFIG_FLAG_NoCriticalHits, g_Config.Player->AntiHSEnabled);
if (g_Config.Player->AntiHSEnabled) {
Features::Exploits::SmartAntiHeadshot();
}
}
if (Custom::CheckBox(xorstr("No Clip"), &g_Config.Player->NoClipEnabled)) {
}
if (g_Config.Player->NoClipEnabled)
{
static int KeyMode = 1;
ImGui::Keybind(xorstr("Bind"), &g_Config.Player->NoClipKey, &KeyMode);
Custom::CheckBox(xorstr("Hold Mode"), &g_Config.Player->NoClipHoldMode);
ImGui::SliderFloat(xorstr("Nc Velocity"), &g_Config.Player->NoClipSpeed, 0.1f, 20.f, xorstr("%1.2fm/s"));
}
if (Custom::CheckBox(xorstr("Run Faster"), &g_Config.Player->FastRun))
{
if (!g_Config.Player->FastRun) {
Core::SDK::Pointers::pLocalPlayer->SetSpeed(1.f);
}
}
if (g_Config.Player->FastRun)
{
if (ImGui::SliderFloat(xorstr("Speed"), &g_Config.Player->RunSpeed, 1.f, 10.f, xorstr("%1.2fm/s")))
{
Core::SDK::Pointers::pLocalPlayer->SetSpeed(g_Config.Player->RunSpeed);
}
}
if ( Custom::CheckBox( xorstr( "Shrink" ), &g_Config.Player->ShrinkEnabled ) )
{
Core::SDK::Pointers::pLocalPlayer->SetConfigFlag( ePedConfigFlag::CPED_CONFIG_FLAG_UseAmbientModelScaling, g_Config.Player->ShrinkEnabled );
}
if ( Custom::CheckBox( xorstr( "No RagDoll" ), &g_Config.Player->NoRagDollEnabled ) )
{
Core::SDK::Pointers::pLocalPlayer->NoRagDoll( g_Config.Player->NoRagDollEnabled );
}
if ( Custom::CheckBox( xorstr( "Infinite CombatRoll" ), &g_Config.Player->InfiniteCombatRoll ) )
{
std::thread InfiniteCombatRoll( [ ] ( ) { Core::SDK::Pointers::pLocalPlayer->SetInfCombatRoll( g_Config.Player->InfiniteCombatRoll ); } );
InfiniteCombatRoll.detach( );
}
if ( Custom::CheckBox( xorstr( "Infinite Stamina" ), &g_Config.Player->InfiniteStamina ) )
{
Core::SDK::Pointers::pLocalPlayer->SetInfStamina( g_Config.Player->InfiniteStamina );
}
g_Config.Player->CurrentHealthValue = Core::SDK::Pointers::pLocalPlayer->GetHealth() - 100.f > Core::SDK::Pointers::pLocalPlayer->GetMaxHealth() - 100.f ? Core::SDK::Pointers::pLocalPlayer->GetHealth() - 100.f : Core::SDK::Pointers::pLocalPlayer->GetHealth() - 99.f;
if (ImGui::SliderFloat(xorstr("Life"), &g_Config.Player->CurrentHealthValue, -1, Core::SDK::Pointers::pLocalPlayer->GetMaxHealth(), xorstr("%1.f")))
{
Core::SDK::Pointers::pLocalPlayer->SetHealth(g_Config.Player->CurrentHealthValue + 100.f);
}
}
ImGui::EndChild( );
}
ImGui::EndGroup( );
ImGui::SameLine();
ImGui::BeginGroup();
{
bool InVehicle = Core::SDK::Pointers::pLocalPlayer->InVehicle();
auto CurrentVehicle = Core::SDK::Pointers::pLocalPlayer->GetLastVehicle();
ImGui::BeginChild(xorstr("Vehicles Mods"), ImVec2(230, 400), false, 0);
{
if (Custom::CheckBox(xorstr("Vehicle GodMode"), &g_Config.Player->VehicleGodMode))
{
if (!InVehicle)
{
g_Config.Player->VehicleGodMode = false;
NotifyManager::Send(xorstr("You must be in a car"), 4000);
}
else {
CurrentVehicle->SetGodMode(g_Config.Player->VehicleGodMode);
}
}
if (Custom::CheckBox(xorstr("Seat Belt"), &g_Config.Player->SeatBelt))
{
if (!InVehicle)
{
g_Config.Player->SeatBelt = false;
NotifyManager::Send(xorstr("You must be in a car"), 4000);
}
else {
Core::SDK::Pointers::pLocalPlayer->SeatBealt(g_Config.Player->SeatBelt);
}
}
static bool Extras_Restore{ false };
static bool Extras_Restore2{ false };
if (Custom::CheckBox(xorstr("Rocket Boost (E)"), &g_Config.Player->HornetBoost)) {
Extras_Restore2 = false;
CVehicle* CurrentVehicle = Core::SDK::Pointers::pLocalPlayer->GetLastVehicle();
CVehicle* ModelInfo = reinterpret_cast<CVehicle*>(CurrentVehicle->GetModelInfo());
ModelInfo->SetExtras(0x40);
Extras_Restore = true;
}
else if (!g_Config.Player->HornetBoost && Extras_Restore) {
CVehicle* CurrentVehicle = Core::SDK::Pointers::pLocalPlayer->GetLastVehicle();
CVehicle* ModelInfo = reinterpret_cast<CVehicle*>(CurrentVehicle->GetModelInfo());
ModelInfo->SetExtras(0x0);
Extras_Restore = false;
}
if (Custom::CheckBox(xorstr("Noclip Car"), &g_Config.Player->NoClipCarEnabled))
{
    if (!g_Config.Player->NoClipCarEnabled)
        Core::Features::Exploits::NoClipCarDesativado();
}
if (g_Config.Player->NoClipCarEnabled)
{
    ImGui::SliderFloat(xorstr("Car Velocity"), &g_Config.Player->NoClipCarSpeed, 0.1f, 20.f, xorstr("%1.2fm/s"));
}
if (Custom::Button(xorstr("Fix Vehicle"), ImVec2(-1, 30), 0))
{
if (!InVehicle || !CurrentVehicle)
{
NotifyManager::Send(xorstr("You must be in a car"), 4000);
}
else
{
CurrentVehicle->Fix();
}
}
static int FixCar = 1;
ImGui::Keybind(xorstr("Fix Bind"), &g_Config.Player->FixCar, &FixCar);
if (Custom::CheckBox(xorstr("Modify Handling"), &g_Config.Player->HandlingEditor))
{
if (!InVehicle)
{
g_Config.Player->HandlingEditor = false;
NotifyManager::Send(xorstr("You must be in a car"), 4000);
}
else
{
if (g_Config.Player->HandlingEditor)
Features::Exploits::g_HandlingEditor.SaveHandlingValues();
else
Features::Exploits::g_HandlingEditor.RestoreHandlingValues();
}
}
else
{
if (!g_Config.Player->HandlingEditor)
ImGui::BeginDisabled();
if (ImGui::SliderFloat(xorstr("Acceleration"), &Features::Exploits::g_HandlingEditor.fAcceleration, 0.0f, 400.f, xorstr("%1.1f")))
{
if (g_Config.Player->HandlingEditor)
Features::Exploits::g_HandlingEditor.ApplyHandlingValues();
}
if (ImGui::SliderFloat(xorstr("Break Force"), &Features::Exploits::g_HandlingEditor.fBreakForce, 0.0f, 100.f, xorstr("%1.1f")))
{
if (g_Config.Player->HandlingEditor)
Features::Exploits::g_HandlingEditor.ApplyHandlingValues();
}
if (ImGui::SliderFloat(xorstr("Traction Curve Min"), &Features::Exploits::g_HandlingEditor.fTractionCurveMin, 0.0f, 100.f, xorstr("%1.1f")))
{
if (g_Config.Player->HandlingEditor)
Features::Exploits::g_HandlingEditor.ApplyHandlingValues();
}
if (!g_Config.Player->HandlingEditor)
ImGui::EndDisabled();
if (!g_Config.Player->HandlingEditor)
ImGui::BeginDisabled();
if (Custom::Button(xorstr("Reset Handling"), ImVec2(-1, 30), 0))
{
Features::Exploits::g_HandlingEditor.RestoreHandlingValues();
}
if (!g_Config.Player->HandlingEditor)
ImGui::EndDisabled();
}
}
ImGui::EndChild();
}
ImGui::EndGroup();
ImGui::SameLine();
ImGui::BeginGroup();
{
ImGui::BeginChild(xorstr("Weapons Options"), ImVec2(230, 185), false, 0);
{
if (Custom::CheckBox(xorstr("Remove Recoil"), &g_Config.Player->NoRecoilEnabled)) {
if (g_Config.Player->NoRecoilEnabled) {
Core::SDK::Pointers::pLocalPlayer->GetWeaponManager()->SetRecoil(0.0f);
}
}
if (Custom::CheckBox(xorstr("Remove Spread"), &g_Config.Player->NoSpreadEnabled)) {
if (g_Config.Player->NoSpreadEnabled) {
Core::SDK::Pointers::pLocalPlayer->GetWeaponManager()->SetSpread(0.0f);
}
}
if (Custom::CheckBox(xorstr("Infinite Ammo"), &g_Config.Player->InfiniteAmmoEnabled))
{
if (g_Config.Player->InfiniteAmmoEnabled) {
Mem.PatchFunc(g_Offsets.m_InfiniteAmmo0, 3);
Mem.PatchFunc(g_Offsets.m_InfiniteAmmo1, 3);
}
else {
if (!g_Config.Player->NoReloadEnabled)
{
Mem.WriteBytes(g_Offsets.m_InfiniteAmmo0, { 0x41, 0x2B, 0xC9, 0x3B, 0xC8, 0x0F, 0x4D, 0xC8 });
}
Mem.WriteBytes(g_Offsets.m_InfiniteAmmo1, { 0x41, 0x2B, 0xD1, 0xE8 });
}
}
if (Custom::CheckBox(xorstr("No Reload"), &g_Config.Player->NoReloadEnabled))
{
    if (g_Config.Player->NoReloadEnabled) {
        Mem.PatchFunc(g_Offsets.m_InfiniteAmmo0, 3);
    }
    else {
        Mem.WriteBytes(g_Offsets.m_InfiniteAmmo0, { 0x41, 0x2B, 0xC9, 0x3B, 0xC8, 0x0F, 0x4D, 0xC8 });
    }
}
if (Custom::CheckBox(xorstr("Weapon Scale"), &g_Config.Player->WeaponScaleEnabled))
{
}
if (g_Config.Player->WeaponScaleEnabled)
{
    ImGui::SliderFloat(xorstr("Weapon Size"), &g_Config.Player->WeaponSize, 0.0f, 10.0f, xorstr("%.1f"));
}
}
ImGui::EndChild();
ImGui::BeginChild(xorstr("Teleport"), ImVec2(230, 207), false, 0);
{
struct Locations_t {
std::string Name;
D3DXVECTOR3 Coords;
};
std::vector<Locations_t> Locations = {
Locations_t(xorstr("Waypoint"), D3DXVECTOR3(0, 0, 0)),
Locations_t(xorstr("Square"), D3DXVECTOR3(156.184, -1043.17, 29.3236)),
Locations_t(xorstr("Pier"), D3DXVECTOR3(-1847.72, -1223.36, 13.8745)),
Locations_t(xorstr("Paleto Bay"), D3DXVECTOR3(-397.605, 6047.57, 32.1797)),
Locations_t(xorstr("Central Bank"), D3DXVECTOR3(221.781, 217.278, 106.705)),
Locations_t(xorstr("Cassino"), D3DXVECTOR3(885.322, 16.8489, 80.65)),
Locations_t(xorstr("Ls Airport"), D3DXVECTOR3(-975.532, -2880.89, 16.2665)),
Locations_t(xorstr("Sandy Shores"), D3DXVECTOR3(1681.48, 3251.91, 40.809)),
};
static int SeletedIndex = 0;
bool IsSelected;
ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(14, 8));
for (int i = 0; i < Locations.size(); i++)
{
IsSelected = SeletedIndex == i;
if (ImGui::ListSelectable(Locations[i].Name.c_str(), &IsSelected)) SeletedIndex = i;
}
ImGui::PopStyleVar();
static ImVec2 ContentSize = ImVec2(g_MenuInfo.MenuSize.x - (-1 + 24), 180);
auto Location = Locations[SeletedIndex];
std::string Loc = xorstr("Teleport to ") + Location.Name;
if (Custom::Button(Loc.c_str(), ImVec2(-1, 30), 0)) {
if (SeletedIndex == 0)
{
Core::Features::Exploits::TpToWaypoint();
}
else {
Core::SDK::Pointers::pLocalPlayer->SetPos(Location.Coords);
}
}
}
ImGui::EndChild();
}
ImGui::EndGroup();
break;
default:
break;
}
}
ImGui::EndGroup( );
ImGui::PopStyleVar( );
}
}
