#pragma once
#include <Includes/Includes.hpp>
#include <Includes/Utils.hpp>
#include <chrono>
#include <map>
namespace NotifyManager
{
enum eType { None, Info, Warning };
enum eState { In, Current, Out, Expired };
class NotifyClass {
private:
std::string Title;
std::string Description;
time_t ExpireTime = 0;
time_t CreationTime = 0;
eType Type = eType::None;
eState CurrentState = eState::In;
public:
void SetTitle(std::string NewTitle) { Title = NewTitle; }
void SetDescription(std::string NewDesc) { Description = NewDesc; }
void SetType(eType NewType) { Type = NewType; }
void SetState(eState NewState) { CurrentState = NewState; }
void SetCreationTime(time_t NewCreationTime) { CreationTime = NewCreationTime; }
std::string GetTitle() { return Title; }
std::string GetDescription() { return Description; }
time_t GetExpireTime() { return ExpireTime; }
time_t GetCreationTime() { return CreationTime; }
eType GetType() { return Type; }
eState GetCurrentState() { return CurrentState; }
time_t GetNowTime() {
using namespace std::chrono;
return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}
time_t GetTimeDiff() {
return (time_t)(GetNowTime() - CreationTime);
}
NotifyClass(eType Type, time_t ExpireTime = 4000)
{
this->Type = Type;
this->ExpireTime = ExpireTime;
this->CreationTime = GetNowTime();
}
};
inline std::vector<NotifyClass> NotifyList;
inline void DeleteNotify(int Index)
{
NotifyList.erase(NotifyList.begin() + Index);
}
inline float ImLength(const ImVec2& a, const ImVec2& b) {
ImVec2 delta = b - a;
return sqrtf(delta.x * delta.x + delta.y * delta.y);
}
inline void Render()
{
const auto DrawList = ImGui::GetForegroundDrawList();
const auto WindowSize = g_Variables.g_vGameWindowSize;
float NextHeight = 0.f;
for (int i = 0; i < NotifyList.size(); i++) {
auto& Notify = NotifyList.at(i);
struct NotifyWid_t {
float SlideX = 0.f;
float YPos = 0.f;
float Alpha = 0.f;
float ContourProgress = 0.f;
};
static std::map<std::string, NotifyWid_t> anim;
const auto Id = Notify.GetDescription() + std::to_string(Notify.GetCreationTime());
auto NotifyAnim = anim.find(Id);
if (NotifyAnim == anim.end()) {
anim.insert({ Id, NotifyWid_t() });
NotifyAnim = anim.find(Id);
}
if (Notify.GetCurrentState() == eState::Expired) {
Notify.SetState(eState::In);
DeleteNotify(i);
anim.erase(Id);
i--;
continue;
}
auto TitleTxtSize = Utils::CalcTextSize(g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, Notify.GetTitle().c_str());
auto DescTxtSize = Utils::CalcTextSize(g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, Notify.GetDescription().c_str());
const float Padding = 8.f;
ImVec2 NotifySize = (TitleTxtSize.x > DescTxtSize.x)
? ImVec2(TitleTxtSize.x + (Padding * 2), DescTxtSize.y + TitleTxtSize.y + (Padding * 2) + 4)
: ImVec2(DescTxtSize.x + (Padding * 2), DescTxtSize.y + TitleTxtSize.y + (Padding * 2) + 4);
if (Notify.GetCurrentState() == eState::In || Notify.GetCurrentState() == eState::Current) {
NotifyAnim->second.SlideX = ImLerp(NotifyAnim->second.SlideX, NotifySize.x, ImGui::GetIO().DeltaTime * 8);
NotifyAnim->second.Alpha = ImLerp(NotifyAnim->second.Alpha, 1.f, ImGui::GetIO().DeltaTime * 8);
NotifyAnim->second.ContourProgress = ImLerp(NotifyAnim->second.ContourProgress, 1.f, ImGui::GetIO().DeltaTime * 2);
}
if (NotifyAnim->second.SlideX >= NotifySize.x - 1.f)
Notify.SetState(eState::Current);
if (Notify.GetCurrentState() == eState::Current && Notify.GetTimeDiff() > Notify.GetExpireTime())
Notify.SetState(eState::Out);
if (Notify.GetCurrentState() == eState::Out) {
NotifyAnim->second.SlideX = ImLerp(NotifyAnim->second.SlideX, 0.f, ImGui::GetIO().DeltaTime * 8);
NotifyAnim->second.Alpha = ImLerp(NotifyAnim->second.Alpha, 0.f, ImGui::GetIO().DeltaTime * 6);
NotifyAnim->second.ContourProgress = ImLerp(NotifyAnim->second.ContourProgress, 0.f, ImGui::GetIO().DeltaTime * 6);
if (NotifyAnim->second.SlideX <= 2.f)
Notify.SetState(eState::Expired);
}
NotifyAnim->second.YPos = ImLerp(NotifyAnim->second.YPos, NextHeight, ImGui::GetIO().DeltaTime * 8);
float NotifyStartX = WindowSize.x - NotifySize.x - 10.f;
float NotifyStartY = 10.f + NotifyAnim->second.YPos;
ImRect NotifyPos(
ImVec2(NotifyStartX + NotifySize.x - NotifyAnim->second.SlideX, NotifyStartY),
ImVec2(NotifyStartX + NotifySize.x - NotifyAnim->second.SlideX + NotifySize.x, NotifyStartY + NotifySize.y)
);
ImGui::PushStyleVar(ImGuiStyleVar_Alpha, NotifyAnim->second.Alpha);
DrawList->AddRectFilled(
NotifyPos.Min,
NotifyPos.Max,
ImColor(ImVec4(14.f / 255.f, 14.f / 255.f, 14.f / 255.f, NotifyAnim->second.Alpha)),
6.f
);
ImVec2 p1 = NotifyPos.Min;
ImVec2 p2 = ImVec2(NotifyPos.Max.x, NotifyPos.Min.y);
ImVec2 p3 = NotifyPos.Max;
ImVec2 p4 = ImVec2(NotifyPos.Min.x, NotifyPos.Max.y);
float lengths[4] = {
ImLength(p1, p2),
ImLength(p2, p3),
ImLength(p3, p4),
ImLength(p4, p1)
};
float totalLength = lengths[0] + lengths[1] + lengths[2] + lengths[3];
float visibleLength = totalLength * NotifyAnim->second.ContourProgress;
float drawn = 0.f;
for (int j = 0; j < 4; ++j) {
ImVec2 a = (j == 0) ? p1 : (j == 1) ? p2 : (j == 2) ? p3 : p4;
ImVec2 b = (j == 0) ? p2 : (j == 1) ? p3 : (j == 2) ? p4 : p1;
float len = lengths[j];
if (drawn + len <= visibleLength) {
DrawList->AddLine(a, b, ImColor(g_Col.Base), 1.5f);
drawn += len;
}
else if (drawn < visibleLength) {
float remain = visibleLength - drawn;
ImVec2 dir = b - a;
float factor = remain / len;
ImVec2 partial = a + dir * factor;
DrawList->AddLine(a, partial, ImColor(g_Col.Base), 1.5f);
break;
}
}
ImVec2 TitlePos = ImVec2(NotifyPos.Min.x + Padding, NotifyPos.Min.y + Padding - 1);
ImVec2 DescPos = TitlePos + ImVec2(0, TitleTxtSize.y + 2.f);
DrawList->AddText(
g_Variables.m_FontNormal,
g_Variables.m_FontNormal->FontSize,
TitlePos,
ImColor(ImVec4(g_Col.PrimaryText.x, g_Col.PrimaryText.y, g_Col.PrimaryText.z, NotifyAnim->second.Alpha)),
Notify.GetTitle().c_str()
);
DrawList->AddText(
g_Variables.m_FontNormal,
g_Variables.m_FontNormal->FontSize,
DescPos,
ImColor(ImVec4(g_Col.SecundaryText.x, g_Col.SecundaryText.y, g_Col.SecundaryText.z, NotifyAnim->second.Alpha)),
Notify.GetDescription().c_str()
);
ImGui::PopStyleVar();
NextHeight += NotifySize.y + 10.f;
}
}
inline void Send(std::string Description, time_t ExpireTime = 4000)
{
Beep(500, 300);
NotifyClass Notify(eType::Info, ExpireTime);
Notify.SetTitle(xorstr("Undefined"));
Notify.SetDescription(Description);
NotifyList.push_back(Notify);
}
}
