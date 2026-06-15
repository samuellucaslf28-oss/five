#pragma once
#include <Includes/Includes.hpp> /
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "Ws2_32.lib")
namespace Custom
{
}
namespace WaterMark
{
void Render()
{
}
namespace ArrayList
{
void Render()
{
ImDrawList* DrawList = ImGui::GetForegroundDrawList();
const float Padding = 10.0f;
static float distance = 30.f;
const char* alertPart = "{ Alert }";
const char* restText = " ped Invisible ";
double now = ImGui::GetTime();
ImVec2 alertSize = ImGui::CalcTextSize(alertPart);
ImVec2 restSize = ImGui::CalcTextSize(restText);
static double lastToggleTime = now;
static bool visible = false;
static double currentInterval = 0.0;
double secondsSinceVisible = visible ? (now - lastToggleTime) : 0.0;
int metros = 30 + static_cast<int>(secondsSinceVisible * 10.0);
if (metros > 120) metros = 120;
char metrosText[16];
snprintf(metrosText, sizeof(metrosText), "%dm", metros);
ImVec2 metrosSize = ImGui::CalcTextSize(metrosText);
float totalWidth = alertSize.x + restSize.x + metrosSize.x + Padding * 4;
float totalHeight = alertSize.y + Padding * 2;
ImVec2 windowSize = g_Variables.g_vGameWindowSize;
ImVec2 Pos(
(windowSize.x - totalWidth) / 1.65f,
(windowSize.y - totalHeight) / 2.0f
);
if (now - lastToggleTime >= currentInterval)
{
visible = !visible;
lastToggleTime = now;
if (visible)
{
currentInterval = 4.0;
}
else
{
currentInterval = 10.0 + (rand() % 41);
}
}
if (visible)
{
DrawList->AddRectFilled(Pos, Pos + ImVec2(totalWidth, totalHeight), ImColor(g_Col.ChildCol), 6);
ImVec2 textPos = Pos + ImVec2(Padding, Padding);
float hue = fmod(now * 0.1f, 1.0f);
ImU32 rgbColor = ImColor::HSV(hue, 1.0f, 1.0f);
DrawList->AddText(textPos, rgbColor, alertPart);
textPos.x += alertSize.x + Padding;
DrawList->AddText(textPos, ImColor(255, 255, 255), restText);
textPos.x += restSize.x + Padding;
DrawList->AddText(textPos, ImColor(255, 255, 255), metrosText);
}
}
}
}
