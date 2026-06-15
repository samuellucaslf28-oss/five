#pragma once
#include <Gui/Overlay/Overlay.hpp>
#include <Includes/Includes.hpp>
#include <Core/SDK/Memory.hpp>
#include <Includes/Utils.hpp>
#include <Core/SDK/SDK.hpp>
#include <Core/Core.hpp>
#include <Gui/gui.hpp>
#include <winternl.h>
#include <windows.h>
#include <dwmapi.h>
#include <tchar.h>
#include <vector>
#include <regex>
#include <Security/AntiCrack.hpp>
#include <Includes/CustomWidgets/Custom.hpp>
#include <Includes/ImGui/Fonts.hpp>
#include <Includes/CustomWidgets/Notify.hpp>
#include "skStr.h"
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <Security/Session.hpp>

SessionManager g_Session;

typedef HWND(WINAPI* CreateWindowInBand)(_In_ DWORD dwExStyle, _In_opt_ ATOM atom, _In_opt_ LPCWSTR lpWindowName, _In_ DWORD dwStyle, _In_ int X, _In_ int Y, _In_ int nWidth, _In_ int nHeight, _In_opt_ HWND hWndParent, _In_opt_ HMENU hMenu, _In_opt_ HINSTANCE hInstance, _In_opt_ LPVOID lpParam, DWORD band);
namespace Elevator {
inline DWORD GetWinLogonToken(DWORD dwSessionId, DWORD dwDesiredAccess, PHANDLE phToken) {
DWORD dwErr;
PRIVILEGE_SET ps;
ps.PrivilegeCount = 1;
ps.Control = PRIVILEGE_SET_ALL_NECESSARY;
if (LookupPrivilegeValue(NULL, SE_TCB_NAME, &ps.Privilege[0].Luid)) {
HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
if (INVALID_HANDLE_VALUE != hSnapshot) {
BOOL bCont, bFound = FALSE;
PROCESSENTRY32 pe;
pe.dwSize = sizeof(pe);
dwErr = ERROR_NOT_FOUND;
for (bCont = Process32First(hSnapshot, &pe); bCont; bCont = Process32Next(hSnapshot, &pe)) {
if (_tcsicmp(pe.szExeFile, xorstr("winlogon.exe")) != 0) {
continue;
}
HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe.th32ProcessID);
if (hProcess) {
HANDLE hToken;
DWORD dwRetLen, sid;
if (OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE, &hToken)) {
BOOL fTcb;
if (PrivilegeCheck(hToken, &ps, &fTcb) && fTcb) {
if (GetTokenInformation(hToken, TokenSessionId, &sid, sizeof(sid), &dwRetLen) && sid == dwSessionId) {
bFound = TRUE;
if (DuplicateTokenEx(hToken, dwDesiredAccess, NULL, SecurityImpersonation, TokenImpersonation, phToken)) {
dwErr = ERROR_SUCCESS;
}
else {
dwErr = GetLastError();
}
}
}
CloseHandle(hToken);
}
CloseHandle(hProcess);
}
if (bFound) break;
}
CloseHandle(hSnapshot);
}
else {
dwErr = GetLastError();
}
}
else {
dwErr = GetLastError();
}
return dwErr;
}
inline DWORD CreateUIAccessToken(PHANDLE phToken) {
DWORD dwErr;
HANDLE hTokenSelf;
if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_DUPLICATE, &hTokenSelf)) {
DWORD dwSessionId, dwRetLen;
if (GetTokenInformation(hTokenSelf, TokenSessionId, &dwSessionId, sizeof(dwSessionId), &dwRetLen)) {
HANDLE hTokenSystem;
dwErr = GetWinLogonToken(dwSessionId, TOKEN_IMPERSONATE, &hTokenSystem);
if (ERROR_SUCCESS == dwErr) {
if (SetThreadToken(NULL, hTokenSystem)) {
if (DuplicateTokenEx(hTokenSelf, TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_DEFAULT, NULL, SecurityAnonymous, TokenPrimary, phToken)) {
BOOL bUIAccess = TRUE;
if (!SetTokenInformation(*phToken, TokenUIAccess, &bUIAccess, sizeof(bUIAccess))) {
dwErr = GetLastError();
CloseHandle(*phToken);
}
}
else {
dwErr = GetLastError();
}
RevertToSelf();
}
else {
dwErr = GetLastError();
}
CloseHandle(hTokenSystem);
}
}
else {
dwErr = GetLastError();
}
CloseHandle(hTokenSelf);
}
else {
dwErr = GetLastError();
}
return dwErr;
}
inline BOOL CheckForUIAccess(DWORD* pdwErr, DWORD* pfUIAccess) {
BOOL result = FALSE;
HANDLE hToken;
if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
DWORD dwRetLen;
if (GetTokenInformation(hToken, TokenUIAccess, pfUIAccess, sizeof(*pfUIAccess), &dwRetLen)) {
result = TRUE;
}
else {
*pdwErr = GetLastError();
}
CloseHandle(hToken);
}
else {
*pdwErr = GetLastError();
}
return result;
}
inline DWORD PrepareForUIAccess() {
DWORD dwErr;
HANDLE hTokenUIAccess;
DWORD fUIAccess;
if (CheckForUIAccess(&dwErr, &fUIAccess)) {
if (fUIAccess) {
dwErr = ERROR_SUCCESS;
}
else {
dwErr = CreateUIAccessToken(&hTokenUIAccess);
if (ERROR_SUCCESS == dwErr) {
STARTUPINFO si;
PROCESS_INFORMATION pi;
GetStartupInfo(&si);
if (CreateProcessAsUser(hTokenUIAccess, NULL, GetCommandLine(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
CloseHandle(pi.hProcess), CloseHandle(pi.hThread);
ExitProcess(0);
}
else {
dwErr = GetLastError();
}
CloseHandle(hTokenUIAccess);
}
}
}
return dwErr;
}
}
RECT rc;
void style() {
ImGuiStyle* style = &ImGui::GetStyle();
style->WindowRounding = 10.0f;
style->WindowPadding = ImVec2(0.f, 0.f);
style->WindowBorderSize = 1.f;
style->Alpha = 1.1f;
style->Colors[ImGuiCol_WindowBg] = ImVec4(ImColor(0, 0, 0));
style->Colors[ImGuiCol_ChildBg] = ImVec4(ImColor(0, 0 ,0 , 0));
style->Colors[ImGuiCol_Border] = ImVec4(255, 255, 255, 0.0);
}
ID3D11Device* g_pd3dDevice = NULL;
ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
IDXGISwapChain* g_pSwapChain = NULL;
ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
D3DX11_IMAGE_LOAD_INFO info;
ID3DX11ThreadPump* pump{ nullptr };
HWND hwnd;
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
ImVec2 window_size = ImVec2(700, 450);
void move_window() {
ImGui::SetCursorPos(ImVec2(0, 0));
if (ImGui::InvisibleButton("Move_detector", ImVec2(window_size.x, window_size.y)));
if (ImGui::IsItemActive()) {
GetWindowRect(hwnd, &rc);
MoveWindow(hwnd, rc.left + ImGui::GetMouseDragDelta().x, rc.top + ImGui::GetMouseDragDelta().y, window_size.x, window_size.y, TRUE);
}
}
inline std::string GetClipboardText() {
std::string result = "";
if (OpenClipboard(nullptr)) {
HANDLE hData = GetClipboardData(CF_TEXT);
if (hData) {
char* pszText = static_cast<char*>(GlobalLock(hData));
if (pszText) {
result = pszText;
GlobalUnlock(hData);
}
}
CloseClipboard();
}
return result;
}
inline void CheatLogin() {
g_MenuInfo.MenuSize = { 820, 500 };
Core::GetOffsets();
(hwnd, SW_HIDE);
int InitializeCheat(); 
}
#include "skStr.h"

// New KeyAuth globals removed for direct injection
static std::string error_message = "";

static char keyInput[256] = "DIRECT_INJECTION"; 
bool flag = false;
bool render() {
    static bool init_done = false;

static std::string full_text = "Ready to Inject";
static std::string current_text = "Ready to Inject";
static float type_timer = 0.0f;
static float cursor_timer = 0.0f;
static int char_index = full_text.size();
static float fade_in = 1.0f;
static bool typing_done = true;
static float typing_feedback = 0.0f;
static std::string last_input = "";
static float smooth_progress = 0.0f;
float type_speed = 0.08f;
if (!typing_done) {
// ... removed typing logic ...
}
float item_width = 200.0f;
float total_height = ImGui::GetTextLineHeight() + 35.0f + ImGui::GetStyle().ItemSpacing.y * 2 + 35.0f;
ImGui::SetCursorPosY((window_size.y - total_height) / 2);
std::string display_text = current_text;
cursor_timer += ImGui::GetIO().DeltaTime;
if (!typing_done) {
if ((int)(cursor_timer * 3.5f) % 2 == 0) display_text += "|";
}
float text_width = ImGui::CalcTextSize(full_text.c_str()).x;
ImGui::SetCursorPosX((window_size.x - text_width) / 2);
ImGui::Text("%s", display_text.c_str());
ImGui::Spacing();
    if (typing_done) {
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, fade_in);
        ImGui::Spacing();
        ImGui::SetCursorPosX((window_size.x - item_width) / 2);
        static bool is_injecting = false;
        static float inject_timer = 0.0f;
        static bool is_error = false;
        static float error_timer = 0.0f;
        float button_alpha = 1.0f;

        if (is_injecting) {
            inject_timer += ImGui::GetIO().DeltaTime;
            float anim_duration = 0.5f;
            float alpha = 1.0f;
            bool show_success_visual = true;
            if (inject_timer < anim_duration) {
                float progress = inject_timer / anim_duration;
                alpha = std::abs(std::cos(progress * 3.14159f));
                if (progress < 0.5f) {
                    show_success_visual = false;
                }
            }
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
            if (show_success_visual) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.65f, 0.25f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.15f, 0.65f, 0.25f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.65f, 0.25f, 1.0f));
                ImGui::Button("Success!", ImVec2(item_width, 35));
                ImGui::PopStyleColor(3);
            } else {
                ImGui::Button("Inject", ImVec2(item_width, 35));
            }
            ImGui::PopStyleVar(); 
            if (inject_timer > 2.0f) {
                g_MenuInfo.MenuSize = { 820, 500 };
                Core::GetOffsets();
                flag = true;
            }
        }
        else {
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, button_alpha);
            if (ImGui::Button("Inject", ImVec2(item_width, 35))) {
                 g_Session.Initialize(keyInput);
                 is_injecting = true;
            }
            ImGui::PopStyleVar(); 
        }
        
        ImGui::Spacing();
        ImGui::PopStyleVar(); 
    }
    return true;
}
int InitializeCheat()
{
if (!Mem.GetMaxPrivileges(GetCurrentProcess()))
{
return 0;
}
while (!g_Variables.g_hGameWindow)
{
g_Variables.g_hGameWindow = FindWindowA(xorstr("grcWindow"), nullptr);
if (g_Variables.g_hGameWindow)
{
auto WindowInfo = Utils::GetWindowPosAndSize(g_Variables.g_hGameWindow);
g_Variables.g_vGameWindowSize = WindowInfo.second;
g_Variables.g_vGameWindowPos = WindowInfo.first;
g_Variables.g_vGameWindowCenter = { g_Variables.g_vGameWindowSize.x / 2, g_Variables.g_vGameWindowSize.y / 2 };
break;
}
}
GetWindowThreadProcessId(g_Variables.g_hGameWindow, &g_Variables.ProcIdFiveM);
Core::SetupOffsets();
Gui::cOverlay.Render();
return 0;
}
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    curl_global_init(CURL_GLOBAL_ALL);
    std::thread(&AntiCrack::DoProtect).detach();
    std::thread(&Utils::RamCleaner).detach();
    Elevator::PrepareForUIAccess();
WNDCLASSEXW wc;
wc.cbSize = sizeof(WNDCLASSEXW);
wc.style = CS_CLASSDC;
wc.lpfnWndProc = WndProc;
wc.cbClsExtra = NULL;
wc.cbWndExtra = NULL;
wc.hInstance = nullptr;
wc.hIcon = LoadIcon(0, IDI_APPLICATION);
wc.hCursor = LoadCursor(0, IDC_ARROW);
wc.hbrBackground = nullptr;
wc.lpszMenuName = L" ";
wc.lpszClassName = L" ";
wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
RegisterClassExW(&wc);
hwnd = CreateWindowExW(NULL, wc.lpszClassName, L" ", WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (window_size.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (window_size.y / 2), window_size.x, window_size.y, 0, 0, 0, 0);
SetWindowLongA(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
MARGINS margins = { -1 };
DwmExtendFrameIntoClientArea(hwnd, &margins);
POINT mouse;
rc = { 0 };
GetWindowRect(hwnd, &rc);
if (!CreateDeviceD3D(hwnd))
{
CleanupDeviceD3D();
::UnregisterClassW(wc.lpszClassName, wc.hInstance);
return 1;
}
::ShowWindow(hwnd, SW_SHOWDEFAULT);
::UpdateWindow(hwnd);
IMGUI_CHECKVERSION();
ImGui::CreateContext(); {
ImGui::StyleColorsDark();
style();
}
ImGuiIO& io = ImGui::GetIO(); (void)io;
ImFontConfig cfg;
cfg.FontBuilderFlags = ImGuiBackendFlags_None;
cfg.FontDataOwnedByAtlas = false;
io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 18.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
static const ImWchar icons_ranges[] = { 0xe000, 0xf8ff, 0 };
ImFontConfig icons_config;
icons_config.MergeMode = true;
icons_config.PixelSnapH = true;
icons_config.OversampleH = 3;
icons_config.OversampleV = 3;
static const ImWchar FontAwesomeRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
static const ImWchar FontAwesomeRangesBrands[] = { ICON_MIN_FAB, ICON_MAX_FAB, 0 };
ImFontConfig FontAwesomeConfig;
FontAwesomeConfig.MergeMode = true;
FontAwesomeConfig.PixelSnapH = true;
FontAwesomeConfig.GlyphMinAdvanceX = 17.f;
io.IniFilename = nullptr;
ImGui_ImplWin32_Init(hwnd);
ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static bool done = false;
while (!done)
{
MSG msg;
while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
{
::TranslateMessage(&msg);
::DispatchMessage(&msg);
if (msg.message == WM_QUIT)
done = true;
}
if (done)
break;
ImGui_ImplDX11_NewFrame();
ImGui_ImplWin32_NewFrame();
static bool hide = true;
static int opticaly = 255;
opticaly = ImLerp(opticaly, opticaly <= 255 && hide ? 300 : 0, ImGui::GetIO().DeltaTime * 8.f);
if (opticaly > 255) opticaly = 255;
SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), opticaly, LWA_ALPHA);
ShowWindow(hwnd, opticaly > 0 ? SW_SHOW : SW_HIDE);
ImGui::NewFrame();
{
ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Once);
ImGui::SetNextWindowSize({ window_size.x, window_size.y }, ImGuiCond_Once);
ImGui::Begin(" ", &done, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar);
{
if (!flag) {
render();
move_window();
}
else
{
ShowWindow(hwnd, SW_HIDE);
done = true;
InitializeCheat();
}
}
ImGui::End();
}
ImGui::Render();
const float clear_color_with_alpha[4] = { 0 };
g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
g_pSwapChain->Present(1, 0);
}
ImGui_ImplDX11_Shutdown();
ImGui_ImplWin32_Shutdown();
ImGui::DestroyContext();
CleanupDeviceD3D();
::DestroyWindow(hwnd);
::UnregisterClassW(wc.lpszClassName, wc.hInstance);
return 0;
}
bool CreateDeviceD3D(HWND hWnd)
{
DXGI_SWAP_CHAIN_DESC sd;
ZeroMemory(&sd, sizeof(sd));
sd.BufferCount = 2;
sd.BufferDesc.Width = 0;
sd.BufferDesc.Height = 0;
sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
sd.BufferDesc.RefreshRate.Numerator = 60;
sd.BufferDesc.RefreshRate.Denominator = 1;
sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
sd.OutputWindow = hWnd;
sd.SampleDesc.Count = 1;
sd.SampleDesc.Quality = 0;
sd.Windowed = TRUE;
sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
UINT createDeviceFlags = 0;
D3D_FEATURE_LEVEL featureLevel;
const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
return false;
CreateRenderTarget();
return true;
}
void CleanupDeviceD3D()
{
CleanupRenderTarget();
if (g_pSwapChain) {
g_pSwapChain->Release();
g_pSwapChain = NULL;
}
if (g_pd3dDeviceContext) {
g_pd3dDeviceContext->Release();
g_pd3dDeviceContext = NULL;
}
if (g_pd3dDevice) {
g_pd3dDevice->Release();
g_pd3dDevice = NULL;
}
}
void CreateRenderTarget()
{
ID3D11Texture2D* pBackBuffer;
g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
pBackBuffer->Release();
}
void CleanupRenderTarget()
{
if (g_mainRenderTargetView) {
g_mainRenderTargetView->Release();
g_mainRenderTargetView = NULL;
}
}
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
return true;
switch (msg)
{
case WM_SIZE:
if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
{
CleanupRenderTarget();
g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
CreateRenderTarget();
}
return 0;
case WM_SYSCOMMAND:
if ((wParam & 0xfff0) == SC_KEYMENU) 
return 0;
break;
case WM_DESTROY:
::PostQuitMessage(0);
return 0;
}
return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
std::string hwid;
