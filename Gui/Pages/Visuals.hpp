#pragma once
#include <Includes/includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <Includes/CustomWidgets/Preview.hpp>
#include <Core/Core.hpp>
using namespace std;
namespace Visuals {
static int iSubTabCount = 0;
static float SubTabAlpha = 0.f;
static int iSubTab = 0;
void Render( ) {
SubTabAlpha = ImClamp( SubTabAlpha + ( 5.f * ImGui::GetIO( ).DeltaTime * ( iSubTabCount == iSubTab ? 1.f : -1.f ) ), 0.f, 1.f );
if ( SubTabAlpha == 0.f )
iSubTab = iSubTabCount;
ImGui::PushStyleVar( ImGuiStyleVar_Alpha, SubTabAlpha * ImGui::GetStyle( ).Alpha );
ImGui::SetCursorPos( ImVec2(90, 76) );
ImGui::BeginGroup( );
{
switch ( iSubTab )
{
case 0:
ImGui::BeginGroup( );
{
ImGui::BeginChild(xorstr("Player ESP"), ImVec2(230, 400), false, 0);
{
Custom::CheckBox(xorstr("Enable"), &g_Config.ESP->Enabled );
ImGui::SliderInt(xorstr("Render Distance"), &g_Config.ESP->MaxDistance, 0, 500, xorstr("%dm"), 0);
Custom::CheckBox(xorstr("Show LocalPlayer"), &g_Config.ESP->ShowLocalPlayer);
Custom::CheckBox(xorstr("Visible Check"), &g_Config.ESP->VisibleCheck);
Custom::CheckBox(xorstr("Ignore Dead"), &g_Config.ESP->IgnoreDead);
Custom::CheckBox(xorstr("Ignore NPCs"), &g_Config.ESP->IgnoreNPCs);
Custom::CheckBox(xorstr("Box"), &g_Config.ESP->Box);
if (Custom::CheckBox(xorstr("Skeleton"), &g_Config.ESP->Skeleton))
{
Core::SDK::Pointers::pLocalPlayer->RemoveKinematics();
}
if (g_Config.ESP->Skeleton)
{
ImGui::SliderFloat("Skeleton", &g_Config.ESP->SkeletonThickness, 0.5f, 3.0f, "%.1f");
}
Custom::CheckBox( xorstr( "Player Name" ), &g_Config.ESP->UserNames );
Custom::CheckBox( xorstr( "Weapon Name" ), &g_Config.ESP->WeaponName );
Custom::CheckBox( xorstr( "Head Circle" ), &g_Config.ESP->HeadCircle );
Custom::CheckBox( xorstr( "Health Bar" ), &g_Config.ESP->HealthBar );
Custom::CheckBox( xorstr( "Armor Bar" ), &g_Config.ESP->ArmorBar );
Custom::CheckBox(xorstr("SnapLines"), &g_Config.ESP->SnapLines);
Custom::CheckBox(xorstr("Distance"), &g_Config.ESP->DistanceFromMe);
}
ImGui::EndChild( );
}
ImGui::EndGroup( );
ImGui::SameLine();
ImGui::BeginGroup();
{
ImGui::BeginChild(xorstr("Vehicle ESP"), ImVec2(230, 300), false, 0);
{
Custom::CheckBox(xorstr("Enable"), &g_Config.VehicleESP->Enabled);
ImGui::SliderInt(xorstr("Render Distance"), &g_Config.VehicleESP->MaxDistance, 0, 500, xorstr("%dm"), 0);
Custom::CheckBox(xorstr("Vehicle Name"), &g_Config.VehicleESP->VehName);
Custom::CheckBox(xorstr("Locked/Unlocked"), &g_Config.VehicleESP->ShowLockUnlock);
Custom::CheckBox(xorstr("Distance"), &g_Config.VehicleESP->DistanceFromMe);
Custom::CheckBox(xorstr("SnapLines"), &g_Config.VehicleESP->SnapLines);
}
ImGui::EndChild();
}
ImGui::EndGroup();
ImGui::SameLine();
ImGui::BeginGroup();
{
ImGui::BeginChild(xorstr("Player Preview"), ImVec2(230, 400), false, ImGuiWindowFlags_NoScrollbar);
{
Custom::g_EspPreview.DragDropHandler();
Custom::g_EspPreview.Draw();
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
