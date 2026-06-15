#pragma once
#include "Overlay.hpp"
#include <Includes/ImGui/Files/imgui_freetype.h>
#include <Includes/CustomWidgets/Notify.hpp>
#include <Includes/ImGui/Images.hpp>
#include <Includes/ImGui/Fonts.hpp>
#include <Core/Core.hpp>
#include <Gui/Gui.hpp>
#include <dwmapi.h>
#include <tchar.h>
#include <thread>
#include <iostream>
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Gui
{
typedef HWND(WINAPI* CreateWindowInBand)(_In_ DWORD dwExStyle, _In_opt_ ATOM atom, _In_opt_ LPCWSTR lpWindowName, _In_ DWORD dwStyle, _In_ int X, _In_ int Y, _In_ int nWidth, _In_ int nHeight, _In_opt_ HWND hWndParent, _In_opt_ HMENU hMenu, _In_opt_ HINSTANCE hInstance, _In_opt_ LPVOID lpParam, DWORD band);
inline HHOOK hKeyboardHook;
inline LRESULT CALLBACK KeyboardCallBack(int nCode, WPARAM wParam, LPARAM lParam)
{
if (nCode >= 0)
{
KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
PostMessage(g_Variables.g_hCheatWindow, wParam, pKeyboard->vkCode, 0);
}
return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}
void Overlay::Render()
{
#ifdef FULLSCREEN_EX
CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
CreateWindowInBand pCreateWindowInBand = reinterpret_cast<CreateWindowInBand>(GetProcAddress(LoadLibraryA(xorstr("user32.dll")), xorstr("CreateWindowInBand")));
PrepareForUIAccess();
#endif
WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, Overlay::WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L" ", NULL };
ATOM RegClass = RegisterClassExW(&wc);
#ifdef FULLSCREEN_EX
g_Variables.g_hCheatWindow = pCreateWindowInBand(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE, RegClass, L" ", WS_POPUP, static_cast<int>(g_Variables.g_vGameWindowPos.x), static_cast<int>(g_Variables.g_vGameWindowPos.y), static_cast<int>(g_Variables.g_vGameWindowSize.x), static_cast<int>(g_Variables.g_vGameWindowSize.y), NULL, NULL, wc.hInstance, NULL, 2);
#else
g_Variables.g_hCheatWindow = CreateWindowExW(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT, wc.lpszClassName, L" ", WS_POPUP, g_Variables.g_vGameWindowPos.x, g_Variables.g_vGameWindowPos.y, g_Variables.g_vGameWindowSize.x, g_Variables.g_vGameWindowSize.y, NULL, NULL, wc.hInstance, NULL);
#endif
SetLayeredWindowAttributes(g_Variables.g_hCheatWindow, RGB(40, 40, 44), 255, LWA_ALPHA);
MARGINS Margin = { g_Variables.g_vGameWindowPos.x, g_Variables.g_vGameWindowPos.y, g_Variables.g_vGameWindowSize.x,g_Variables.g_vGameWindowSize.y };
DwmExtendFrameIntoClientArea(g_Variables.g_hCheatWindow, &Margin);
if (!CreateDeviceD3D(g_Variables.g_hCheatWindow))
{
CleanupDeviceD3D();
UnregisterClassW(wc.lpszClassName, wc.hInstance);
return;
}
SetWindowDisplayAffinity(g_Variables.g_hCheatWindow, WDA_EXCLUDEFROMCAPTURE);
ShowWindow(g_Variables.g_hCheatWindow, SW_SHOWDEFAULT);
UpdateWindow(g_Variables.g_hCheatWindow);
ImGui::CreateContext();
Style();
Fonts();
ImGui_ImplWin32_Init(g_Variables.g_hCheatWindow);
ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
#ifdef FULLSCREEN_EX
hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardCallBack, NULL, 0);
#endif
Core::StartThreads();
if (!Core::ThreadsStarted) return;
std::thread([&]() { NotifyManager::Send(xorstr("Enjoy!"), 4000); }).detach();
static RECT old_rc;
ZeroMemory(&Message, sizeof(MSG));
while (Message.message != WM_QUIT)
{
if (PeekMessage(&Message, g_Variables.g_hCheatWindow, 0, 0, PM_REMOVE)) {
TranslateMessage(&Message);
DispatchMessage(&Message);
}
HWND ActiveWindow = GetForegroundWindow();
if (GetAsyncKeyState(g_Config.General->MenuKey) & 1) {
if (g_MenuInfo.IsOpen == false) {
if (ActiveWindow == g_Variables.g_hGameWindow) {
g_MenuInfo.IsOpen = true;
#ifdef FULLSCREEN_EX
SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);
#else
SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
#endif
}
else {
SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
}
}
else {
g_MenuInfo.IsOpen = false;
SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
}
}
static float BgAlpha = 0.f;
BgAlpha = ImLerp(BgAlpha, g_MenuInfo.IsOpen ? 1.f : 0.f, ImGui::GetIO().DeltaTime * 8);
ImGui_ImplDX11_NewFrame();
ImGui_ImplWin32_NewFrame();
ImGui::NewFrame();
{
ImGui::PushStyleVar(ImGuiStyleVar_Alpha, BgAlpha);
Gui::Rendering();
ImGui::PopStyleVar();
}
ImGui::EndFrame();
const float ClearColor[4] = { 0 };
g_pd3dDeviceContext->OMSetRenderTargets(1U, &g_mainRenderTargetView, NULL);
g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, ClearColor);
ImGui::Render();
ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
g_pSwapChain->Present(g_Config.General->VSync, 0U);
}
ImGui_ImplDX11_Shutdown();
ImGui_ImplWin32_Shutdown();
ImGui::DestroyContext();
CleanupDeviceD3D();
DestroyWindow(g_Variables.g_hCheatWindow);
UnregisterClassW(wc.lpszClassName, wc.hInstance);
#ifdef FULLSCREEN_EX
UnhookWindowsHookEx(hKeyboardHook);
#endif
return;
}
void Overlay::Fonts()
{
ImGuiIO& io = ImGui::GetIO(); (void)io;
io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
io.IniFilename = nullptr;
ImFontConfig Cfg;
Cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;
Cfg.FontDataOwnedByAtlas = false;
ImFontConfig DrawCfg;
DrawCfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_Bitmap;
DrawCfg.FontDataOwnedByAtlas = false;
g_Variables.m_FontBig = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 20.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
g_Variables.m_FontBigSmall = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 18.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
g_Variables.m_FontNormal = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 18.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
g_Variables.m_FontSecundary = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 16.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
g_Variables.m_FontSmaller = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 14.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
g_Variables.m_DrawFontDefault = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 12.f, &DrawCfg, io.Fonts->GetGlyphRangesCyrillic());
g_Variables.m_DrawFontMinecraft = io.Fonts->AddFontFromMemoryTTF(MinecraftFont, sizeof(MinecraftFont), 12.f, &DrawCfg, io.Fonts->GetGlyphRangesDefault());
g_Variables.m_DrawFontVegas = io.Fonts->AddFontFromMemoryTTF(VegasFont, sizeof(VegasFont), 12.f, &DrawCfg, io.Fonts->GetGlyphRangesDefault());
g_Variables.m_DrawFont = g_Variables.m_DrawFontDefault; // Fonte padrão agora é InterSemiBold ao invés de Minecraft
static const ImWchar FontAwesomeRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
static const ImWchar FontAwesomeRangesBrands[] = { ICON_MIN_FAB, ICON_MAX_FAB, 0 };
ImFontConfig FontAwesomeConfig;
FontAwesomeConfig.PixelSnapH = true;
FontAwesomeConfig.GlyphMinAdvanceX = 19;
g_Variables.FontAwesomeSolid = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Solid_compressed_data, sizeof(FontAwesome6Solid_compressed_size), 23, &FontAwesomeConfig, FontAwesomeRanges);
g_Variables.FontAwesomeSolidSmall = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Solid_compressed_data, sizeof(FontAwesome6Solid_compressed_size), 16, &FontAwesomeConfig, FontAwesomeRanges);
g_Variables.FontAwesomeRegular = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Regular_compressed_data, sizeof(FontAwesome6Regular_compressed_size), 19, &FontAwesomeConfig, FontAwesomeRanges);
g_Variables.m_Expand = io.Fonts->AddFontFromMemoryTTF(expand_binary, sizeof(expand_binary), 11.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
}
void Overlay::Style()
{
ImGui::StyleColorsDark();
ImGuiStyle* style = &ImGui::GetStyle();
{
style->WindowPadding = ImVec2(0, 0);
style->WindowBorderSize = 0.f;
style->ItemSpacing = ImVec2(12, 12);
style->ScrollbarSize = 4.f;
style->ChildBorderSize = 0.f;
style->FrameBorderSize = 0.f;
ImVec4 transparent = ImVec4(0.f, 0.f, 0.f, 0.f);
style->Colors[ImGuiCol_WindowBg] = transparent;
style->Colors[ImGuiCol_ChildBg]  = transparent;
style->Colors[ImGuiCol_PopupBg]  = transparent;
style->Colors[ImGuiCol_TitleBg]          = transparent;
style->Colors[ImGuiCol_TitleBgActive]    = transparent;
style->Colors[ImGuiCol_TitleBgCollapsed] = transparent;
style->Colors[ImGuiCol_Header]           = transparent;
style->Colors[ImGuiCol_HeaderHovered]    = transparent;
style->Colors[ImGuiCol_HeaderActive]     = transparent;
style->Colors[ImGuiCol_Tab]              = transparent;
style->Colors[ImGuiCol_TabHovered]       = transparent;
style->Colors[ImGuiCol_TabActive]        = transparent;
style->Colors[ImGuiCol_MenuBarBg]        = transparent;
style->Colors[ImGuiCol_FrameBg]          = transparent;
style->Colors[ImGuiCol_FrameBgHovered]   = transparent;
style->Colors[ImGuiCol_FrameBgActive]    = transparent;
style->Colors[ImGuiCol_Border]           = transparent;
style->Colors[ImGuiCol_BorderShadow]     = transparent;
}
if (g_Variables.Logo == nullptr)
{
D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo_binary, sizeof(logo_binary), &Info, Pump, &g_Variables.Logo, 0);
D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, backgroud, sizeof(backgroud), &Info, Pump, &g_Variables.backgroud, 0);
}
}
bool Overlay::CreateDeviceD3D(HWND hWnd)
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
void Overlay::CleanupDeviceD3D()
{
CleanupRenderTarget();
if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}
void Overlay::CreateRenderTarget()
{
ID3D11Texture2D* pBackBuffer;
g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
pBackBuffer->Release();
}
void Overlay::CleanupRenderTarget()
{
if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}
LRESULT CALLBACK Overlay::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
return true;
switch (msg) {
case WM_SIZE:
if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
Overlay::CleanupRenderTarget();
g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
Overlay::CreateRenderTarget();
}
return 0;
case WM_DESTROY:
::PostQuitMessage(0);
return 0;
break;
}
return DefWindowProc(hWnd, msg, wParam, lParam);
}
DWORD Overlay::GetWinLogonToken(DWORD dwSessionId, DWORD dwDesiredAccess, PHANDLE phToken)
{
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
std::cout << "[OK] Token duplicado do winlogon.exe (PID " << pe.th32ProcessID << ")\n";
dwErr = ERROR_SUCCESS;
}
else {
dwErr = GetLastError();
std::cerr << "[ERRO] DuplicateTokenEx falhou: " << dwErr << "\n";
}
}
}
CloseHandle(hToken);
}
else {
std::cerr << "[ERRO] OpenProcessToken falhou: " << GetLastError() << "\n";
}
CloseHandle(hProcess);
}
if (bFound) break;
}
CloseHandle(hSnapshot);
}
else {
dwErr = GetLastError();
std::cerr << "[ERRO] CreateToolhelp32Snapshot falhou: " << dwErr << "\n";
}
}
else {
dwErr = GetLastError();
std::cerr << "[ERRO] LookupPrivilegeValue falhou: " << dwErr << "\n";
}
return dwErr;
}
DWORD Overlay::CreateUIAccessToken(PHANDLE phToken)
{
DWORD dwErr;
HANDLE hTokenSelf;
if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_DUPLICATE, &hTokenSelf)) {
DWORD dwSessionId, dwRetLen;
if (GetTokenInformation(hTokenSelf, TokenSessionId, &dwSessionId, sizeof(dwSessionId), &dwRetLen)) {
HANDLE hTokenSystem;
dwErr = GetWinLogonToken(dwSessionId, TOKEN_IMPERSONATE, &hTokenSystem);
if (ERROR_SUCCESS == dwErr) {
if (SetThreadToken(NULL, hTokenSystem)) {
if (DuplicateTokenEx(hTokenSelf,
TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_DEFAULT,
NULL, SecurityAnonymous, TokenPrimary, phToken)) {
BOOL bUIAccess = TRUE;
if (!SetTokenInformation(*phToken, TokenUIAccess, &bUIAccess, sizeof(bUIAccess))) {
dwErr = GetLastError();
std::cerr << "[ERRO] SetTokenInformation(UIAccess) falhou: " << dwErr << "\n";
CloseHandle(*phToken);
}
else {
std::cout << "[OK] Token UIAccess criado com sucesso\n";
}
}
else {
dwErr = GetLastError();
std::cerr << "[ERRO] DuplicateTokenEx falhou: " << dwErr << "\n";
}
RevertToSelf();
}
else {
dwErr = GetLastError();
std::cerr << "[ERRO] SetThreadToken falhou: " << dwErr << "\n";
}
CloseHandle(hTokenSystem);
}
}
else {
dwErr = GetLastError();
std::cerr << "[ERRO] GetTokenInformation falhou: " << dwErr << "\n";
}
CloseHandle(hTokenSelf);
}
else {
dwErr = GetLastError();
std::cerr << "[ERRO] OpenProcessToken falhou: " << dwErr << "\n";
}
return dwErr;
}
BOOL Overlay::CheckForUIAccess(DWORD* pdwErr, DWORD* pfUIAccess)
{
BOOL result = FALSE;
HANDLE hToken;
if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
DWORD dwRetLen;
if (GetTokenInformation(hToken, TokenUIAccess, pfUIAccess, sizeof(*pfUIAccess), &dwRetLen)) {
std::cout << "[INFO] Token atual UIAccess = " << *pfUIAccess << "\n";
result = TRUE;
}
else {
*pdwErr = GetLastError();
std::cerr << "[ERRO] GetTokenInformation(UIAccess) falhou: " << *pdwErr << "\n";
}
CloseHandle(hToken);
}
else {
*pdwErr = GetLastError();
std::cerr << "[ERRO] OpenProcessToken falhou: " << *pdwErr << "\n";
}
return result;
}
DWORD Overlay::PrepareForUIAccess()
{
DWORD dwErr;
HANDLE hTokenUIAccess;
DWORD fUIAccess;
if (CheckForUIAccess(&dwErr, &fUIAccess)) {
if (fUIAccess) {
std::cout << "[INFO] Ja em contexto UIAccess\n";
dwErr = ERROR_SUCCESS;
}
else {
std::cout << "[INFO] Tentando criar token UIAccess...\n";
dwErr = CreateUIAccessToken(&hTokenUIAccess);
if (ERROR_SUCCESS == dwErr) {
STARTUPINFO si = { sizeof(si) };
PROCESS_INFORMATION pi = { 0 };
if (CreateProcessAsUser(hTokenUIAccess, NULL, GetCommandLine(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
std::cout << "[OK] Novo processo criado com UIAccess\n";
CloseHandle(pi.hProcess);
CloseHandle(pi.hThread);
ExitProcess(0);
}
else {
dwErr = GetLastError();
std::cerr << "[ERRO] CreateProcessAsUser falhou: " << dwErr << "\n";
}
CloseHandle(hTokenUIAccess);
}
}
}
else {
std::cerr << "[ERRO] CheckForUIAccess falhou: " << dwErr << "\n";
}
return dwErr;
}
void Overlay::LoadWeaponIcons() {
{
}
}
}
