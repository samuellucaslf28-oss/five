#pragma once
#include <Includes/Includes.hpp>
#include <windows.h>
#include <iostream>
#include <thread>
#include <destruct.hpp>
using namespace std;
namespace Settings {
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
ImGui::BeginChild(xorstr("Misc ESP Settings"), ImVec2(230, 170), false, 0);
{
ImGui::Text(xorstr("Fonts:"));
static bool use_minecraft_font = false;
static bool use_vegas_font = false;
if (Custom::CheckBox(xorstr("Minecraft (ESP)"), &use_minecraft_font))
{
if (use_minecraft_font && g_Variables.m_DrawFontMinecraft)
{
g_Variables.m_DrawFont = g_Variables.m_DrawFontMinecraft;
use_vegas_font = false;
}
else
{
use_minecraft_font = false;
if (g_Variables.m_DrawFontDefault)
g_Variables.m_DrawFont = g_Variables.m_DrawFontDefault;
}
}
if (Custom::CheckBox(xorstr("Vegas (ESP)"), &use_vegas_font))
{
if (use_vegas_font && g_Variables.m_DrawFontVegas)
{
g_Variables.m_DrawFont = g_Variables.m_DrawFontVegas;
use_minecraft_font = false;
}
else
{
use_vegas_font = false;
if (g_Variables.m_DrawFontDefault)
g_Variables.m_DrawFont = g_Variables.m_DrawFontDefault;
}
}
ImGui::EndChild();
}
}
ImGui::EndGroup( );
ImGui::SameLine();
ImGui::BeginChild(xorstr("Menu Settings"), ImVec2(230, 245), false, 0);
{
if (Custom::CheckBox(xorstr("Hide from Screenshot"), &g_Config.General->StreamProof))
{
if (g_Config.General->StreamProof)
{
SetWindowDisplayAffinity(g_Variables.g_hCheatWindow, WDA_EXCLUDEFROMCAPTURE);
}
else
{
SetWindowDisplayAffinity(g_Variables.g_hCheatWindow, WDA_NONE);
SetWindowPos(
g_Variables.g_hCheatWindow,
HWND_TOPMOST,
0, 0, 0, 0,
SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW
);
RedrawWindow(
g_Variables.g_hCheatWindow,
NULL,
NULL,
RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME
);
}
}
Custom::CheckBox(xorstr("Enable V-Sync"), &g_Config.General->VSync);
static int KeyMode = 1;
ImGui::Keybind(xorstr("Menu Key"), &g_Config.General->MenuKey, &KeyMode);
if (Custom::Button(xorstr("Cleaner"), ImVec2(-1, 30), 0))
{
Prefetch_Cleaner();
std::thread([]() {
NotifyManager::Send(xorstr("Destruct starting..."), 4000);
Sleep(5000);
exit(0);
}).detach();
}
if (Custom::Button(xorstr("Unload"), ImVec2(-1, 30), 0))
{
exit(0);
}
}
ImGui::EndChild();
break;
}
}
ImGui::EndGroup( );
ImGui::SameLine();
ImGui::BeginChild(xorstr("Config System"), ImVec2(230, 145), false, 0);
{
if (Custom::Button(xorstr("Export Config"), ImVec2(-1, 30), 0))
{
std::thread cfgExport([] {
std::string CfgMsg = g_Config.SaveCurrentConfig(xorstr("..."));
NotifyManager::Send(CfgMsg.c_str(), 3000);
});
cfgExport.detach();
}
if (Custom::Button(xorstr("Import Config"), ImVec2(-1, 30), 0))
{
std::thread cfgImport([] { NotifyManager::Send(g_Config.LoadCfg(xorstr("..."), Utils::GetClipboard()).c_str(), 3000); });
cfgImport.detach();
}
ImGui::EndChild();
}
ImGui::EndGroup();
ImGui::PopStyleVar( );
}
}
