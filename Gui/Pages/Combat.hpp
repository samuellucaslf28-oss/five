#pragma once
#include <Includes/Includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
using namespace std;
namespace Combat {
static int iSubTabCount = 0;
static float SubTabAlpha = 0.f;
static int iSubTab = 0;
void Render( ) {
SubTabAlpha = ImClamp( SubTabAlpha + ( 5.f * ImGui::GetIO( ).DeltaTime * ( iSubTabCount == iSubTab ? 1.f : -1.f ) ), 0.f, 1.f );
if ( SubTabAlpha == 0.f )
iSubTab = iSubTabCount;
ImGui::PushStyleVar( ImGuiStyleVar_Alpha, SubTabAlpha * ImGui::GetStyle( ).Alpha );
ImGui::SetCursorPos( ImVec2( 90, 76 ) );
ImGui::BeginGroup( );
{
switch ( iSubTab )
{
case 0:
ImGui::BeginGroup( );
{
ImGui::BeginChild(xorstr("AimBot"), ImVec2(230, 400), false, 0);
{
Custom::CheckBox( xorstr( "Enable" ), &g_Config.Aimbot->Enabled );
Custom::CheckBox(xorstr("Show Fov"), &g_Config.Aimbot->ShowFov );
float AimbotFovCol[4] = { g_Config.Aimbot->FovColor.Value.x, g_Config.Aimbot->FovColor.Value.y, g_Config.Aimbot->FovColor.Value.z,g_Config.Aimbot->FovColor.Value.w }; if (ImGui::ColorEdit4(xorstr("Fov Color"), AimbotFovCol, ImGuiColorEditFlags_AlphaBar)) { g_Config.Aimbot->FovColor.Value.x = AimbotFovCol[0]; g_Config.Aimbot->FovColor.Value.y = AimbotFovCol[1]; g_Config.Aimbot->FovColor.Value.z = AimbotFovCol[2]; g_Config.Aimbot->FovColor.Value.w = AimbotFovCol[3]; }
Custom::CheckBox( xorstr( "Visible Check" ), &g_Config.Aimbot->OnlyVisible );
Custom::CheckBox( xorstr( "Ignore NPCs" ), &g_Config.Aimbot->IgnoreNPCs );
static int KeyMode = 1;
ImGui::Keybind(xorstr("KeyBind"), &g_Config.Aimbot->KeyBind, &KeyMode);
ImGui::SliderInt(xorstr("Fov Size"), &g_Config.Aimbot->FOV, 0, 400, xorstr("%d"), 0);
ImGui::SliderInt(xorstr("Smooth X"), &g_Config.Aimbot->SmoothHorizontal, 0, 100, xorstr("%d"), 0);
ImGui::SliderInt(xorstr("Smooth Y"), &g_Config.Aimbot->SmoothVertical, 0, 100, xorstr("%d"), 0);
Custom::CheckBox(xorstr("Legit Mode"), &g_Config.Aimbot->LegitMode);
const char* HitBoxItems[] = { "Head", "Neck", "Chest" };
ImGui::Combo(xorstr("Bone"), &g_Config.Aimbot->HitBox, HitBoxItems, IM_ARRAYSIZE(HitBoxItems));
ImGui::SliderInt(xorstr("Max Distance"), &g_Config.Aimbot->MaxDistance, 0, 1000, xorstr("%dm"), 0);;
Custom::CheckBox(xorstr("Closet FOV"), &g_Config.Aimbot->ClosestFOV);
}
ImGui::EndChild( );
}
ImGui::EndGroup( );
ImGui::SameLine();
ImGui::BeginGroup();
{
ImGui::BeginChild(xorstr("Trigger"), ImVec2(230, 400), false, 0);
{
Custom::CheckBox(xorstr("Enable"), &g_Config.TriggerBot->Enabled);
if (!g_Config.TriggerBot->SmartTrigger) {
Custom::CheckBox(xorstr("Show Fov"), &g_Config.TriggerBot->ShowFov);
float TriggerFovCol[4] = { g_Config.TriggerBot->FovColor.Value.x, g_Config.TriggerBot->FovColor.Value.y, g_Config.TriggerBot->FovColor.Value.z, g_Config.TriggerBot->FovColor.Value.w }; if (ImGui::ColorEdit4(xorstr("Fov Color "), TriggerFovCol, ImGuiColorEditFlags_AlphaBar)) { g_Config.TriggerBot->FovColor.Value.x = TriggerFovCol[0]; g_Config.TriggerBot->FovColor.Value.y = TriggerFovCol[1]; g_Config.TriggerBot->FovColor.Value.z = TriggerFovCol[2]; g_Config.TriggerBot->FovColor.Value.w = TriggerFovCol[3]; }
}
else
{
g_Config.TriggerBot->ShowFov = false;
}
Custom::CheckBox(xorstr("Smart Triggerbot"), &g_Config.TriggerBot->SmartTrigger);
Custom::CheckBox(xorstr("Visible Check"), &g_Config.TriggerBot->OnlyVisible);
Custom::CheckBox(xorstr("Ignore NPCs"), &g_Config.TriggerBot->IgnoreNPCs);
static int KeyMode = 1;
ImGui::Keybind(xorstr("KeyBind"), &g_Config.TriggerBot->KeyBind, &KeyMode);
if (!g_Config.TriggerBot->SmartTrigger) {
ImGui::SliderInt(xorstr("Fov Size"), &g_Config.TriggerBot->FOV, 0, 400, xorstr("%d"), 0);
ImGui::SliderInt(xorstr("Max Distance"), &g_Config.TriggerBot->MaxDistance, 0, 1000, xorstr("%dm"), 0);
}
ImGui::SliderInt(xorstr("Reaction Time"), &g_Config.TriggerBot->Delay, 0, 10, xorstr("%d"), 0);
}
ImGui::EndChild();
}
ImGui::EndGroup();
ImGui::SameLine();
ImGui::BeginGroup();
{
ImGui::BeginChild(xorstr("Silent"), ImVec2(230, 400), false, 0);
{
Custom::CheckBox(xorstr("Enable"), &g_Config.SilentAim->Enabled);
Custom::CheckBox(xorstr("Show Fov"), &g_Config.SilentAim->ShowFov);
float SilentAimFovCol[4] = { g_Config.SilentAim->FovColor.Value.x, g_Config.SilentAim->FovColor.Value.y, g_Config.SilentAim->FovColor.Value.z, g_Config.SilentAim->FovColor.Value.w }; if (ImGui::ColorEdit4(xorstr("Fov Color  "), SilentAimFovCol, ImGuiColorEditFlags_AlphaBar)) { g_Config.SilentAim->FovColor.Value.x = SilentAimFovCol[0]; g_Config.SilentAim->FovColor.Value.y = SilentAimFovCol[1]; g_Config.SilentAim->FovColor.Value.z = SilentAimFovCol[2]; g_Config.SilentAim->FovColor.Value.w = SilentAimFovCol[3]; }
Custom::CheckBox(xorstr("Magic Bullets"), &g_Config.SilentAim->MagicBullets);
Custom::CheckBox(xorstr("Visible Check"), &g_Config.SilentAim->OnlyVisible);
Custom::CheckBox(xorstr("Ignore NPCs"), &g_Config.SilentAim->IgnoreNPCs);
static int KeyMode = 1;
ImGui::Keybind(xorstr("KeyBind"), &g_Config.SilentAim->KeyBind, &KeyMode);
ImGui::SliderInt(xorstr("Fov Size"), &g_Config.SilentAim->FOV, 0, 400, xorstr("%d"), 0);
ImGui::SliderInt(xorstr("Miss Chance"), &g_Config.SilentAim->MissChance, 0, 100, xorstr("%dx"), 0);
ImGui::SliderInt(xorstr("Max Distance"), &g_Config.SilentAim->MaxDistance, 0, 1000, xorstr("%dm"), 0);
}
ImGui::EndChild();
}
ImGui::EndGroup();
default:
break;
}
}
ImGui::EndGroup( );
ImGui::PopStyleVar( );
}
}
