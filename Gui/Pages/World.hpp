#pragma once
#include <Includes/includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <Core/SDK/Network/CNetwork.h>
#include <Core/Features/ExploitsV2/CrashPlayer.h>
using namespace std;
#include <random>
#include <string>
#include <windows.h>
#include <thread>
#include <sstream>
std::string GenerateRandomDiscordId() {
std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<long long> dis(100000000000000000, 999999999999999999);
return std::to_string(dis(gen));
}
std::string GenerateRandomSteamHex() {
std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<uint64_t> dis(0x100000, 0xFFFFFFF);
std::stringstream ss;
ss << "steam:1100001" << std::hex << dis(gen);
return ss.str();
}
void CopyToClipboard(const std::string& text) {
if (OpenClipboard(nullptr)) {
EmptyClipboard();
HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, text.size() + 1);
if (hGlob) {
memcpy(hGlob, text.c_str(), text.size() + 1);
SetClipboardData(CF_TEXT, hGlob);
}
CloseClipboard();
}
}
namespace World {
static int iSubTabCount = 0;
static float SubTabAlpha = 0.f;
static int iSubTab = 0;
void Render( )
{
auto CurrentVehicle = Core::SDK::Pointers::pLocalPlayer->GetLastVehicle();
SubTabAlpha = ImClamp( SubTabAlpha + ( 5.f * ImGui::GetIO( ).DeltaTime * ( iSubTabCount == iSubTab ? 1.f : -1.f ) ), 0.f, 1.f );
if ( SubTabAlpha == 0.f )
iSubTab = iSubTabCount;
ImGui::PushStyleVar( ImGuiStyleVar_Alpha, SubTabAlpha * ImGui::GetStyle( ).Alpha );
ImGui::SetCursorPos( ImVec2( 90, 76) );
ImGui::BeginGroup( );
{
switch ( iSubTab )
{
case 0:
{
static int SelectedPlayerIndex = -1;
static int SelectedVehicleIndex = -1;
bool IsSelected;
ImGui::BeginGroup( );
{
ImGui::BeginChild(xorstr("Player List"), ImVec2(230, 400), false, 0);
{
ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 14, 8 ) );
for ( int i = 0; i < Core::SDK::Game::EntityList.size( ); i++ )
{
if ( Core::SDK::Game::EntityList[ i ].Ped == Core::SDK::Pointers::pLocalPlayer )
continue;
if ( Core::SDK::Game::EntityList[ i ].PedType != 2 )
continue;
IsSelected = SelectedPlayerIndex == i;
if ( ImGui::ListSelectable( Core::SDK::Game::EntityList[ i ].NetworkInfo.UserName.c_str( ), &IsSelected ) ) SelectedPlayerIndex = i;
}
ImGui::PopStyleVar( );
}
ImGui::EndChild( );
}
ImGui::EndGroup( );
ImGui::SameLine();
ImGui::BeginGroup( );
{
ImGui::BeginChild(xorstr("Actions for Players"), ImVec2(230, 135), false, 0);
{
if ( SelectedPlayerIndex == -1 || SelectedPlayerIndex >= Core::SDK::Game::EntityList.size() ) {
SelectedPlayerIndex = -1;
ImGui::TextColored( ImColor( g_Col.SecundaryText ), xorstr( "Select Player" ) );
}
else
{
auto& SelectedPed = Core::SDK::Game::EntityList[ SelectedPlayerIndex ];
ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 14, 8 ) );
bool Friend = SelectedPed.IsFriend;
if ( Custom::CheckBox( xorstr( "Friend" ), &Friend ) )
{
Core::SDK::Game::FriendMap[ SelectedPed.Ped ] = Friend;
}
ImGui::Spacing( );
if ( Custom::Button( xorstr( "Teleport" ), ImVec2( -1, 30 ), 0 ) )
{
Core::SDK::Pointers::pLocalPlayer->SetPos( SelectedPed.Pos );
std::thread([]() { NotifyManager::Send(xorstr("Sucessfully"), 4000); }).detach();
}
ImGui::PopStyleVar( );
}
}
ImGui::EndChild( );
ImGui::BeginChild(xorstr("Actions for Vehicles"), ImVec2(230, 180), false, 0);
{
if (SelectedVehicleIndex == -1 || SelectedVehicleIndex >= Core::SDK::Game::VehicleList.size()) {
SelectedVehicleIndex = -1;
ImGui::TextColored(ImColor(g_Col.SecundaryText), xorstr("Select Vehicle"));
}
else
{
auto Veh = Core::SDK::Game::VehicleList[SelectedVehicleIndex].Pointer;
ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(14, 8));
if (Veh->IsLocked())
{
if (Custom::Button(xorstr("Unlock"), ImVec2(-1, 30), 0)) {
Veh->DoorState(true);
}
}
else {
if (Custom::Button(xorstr("Lock"), ImVec2(-1, 30), 0)) {
Veh->DoorState(false);
}
}
if (Custom::Button(xorstr("Repair Vehicle"), ImVec2(-1, 33), 0))
{
CurrentVehicle->Fix();
}
if (Custom::Button(xorstr("Teleport"), ImVec2(-1, 30), 0)) {
Core::SDK::Pointers::pLocalPlayer->SetPos(Veh->GetPos());
}
ImGui::PopStyleVar();
}
}
ImGui::EndChild();
}
ImGui::EndGroup( );
ImGui::SameLine();
ImGui::BeginGroup();
{
ImGui::BeginChild(xorstr("Vehicle List"), ImVec2(230, 400), false, 0);
{
ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(14, 8));
{
std::lock_guard<std::mutex> lock(Core::Threads::g_VehicleList.vehicleListMutex);
for (int i = 0; i < Core::SDK::Game::VehicleList.size(); i++)
{
IsSelected = SelectedVehicleIndex == i;
std::string Name = Core::SDK::Game::VehicleList[i].Name + xorstr(" (") + std::to_string((int)Core::SDK::Game::VehicleList[i].Dist) + xorstr("m)");
if (ImGui::ListSelectable(Name.c_str(), &IsSelected)) SelectedVehicleIndex = i;
}
}
ImGui::PopStyleVar();
}
ImGui::EndChild();
}
ImGui::EndGroup();
}
break;
default:
break;
}
}
ImGui::EndGroup( );
ImGui::PopStyleVar( );
}
}
