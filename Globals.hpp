#pragma once
#include <Includes/Includes.hpp>
#include <Security/Session.hpp>
#include <d3dx11.h>
#include <d3d11.h>
#include <D3DX11tex.h>
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "D3DX11.lib" )
class cColors {
public:
// Cyan accent (ZENITH style)
ImVec4 Base = ImColor(0, 210, 255, 255);
ImVec4 Tabs = ImColor(0, 210, 255, 255);
ImVec4 PrimaryText = ImColor(200, 240, 255);
ImVec4 SecundaryText = ImColor(140, 210, 230);
ImVec4 FeaturesText = ImColor(200, 240, 255);
ImVec4 SecundaryFeaturesText = ImColor(50, 80, 95);
ImVec4 BorderCol = ImColor(0, 210, 255, 40);
ImVec4 LinesCol = ImColor(0, 210, 255, 30);
ImVec4 BackgroundCol = ImColor(0, 0, 0);
ImVec4 ChildCol = ImColor(6, 8, 10, 210);
ImVec4 ChildBorderCol = ImColor(0, 210, 255, 18);
ImVec4 Branco = ImColor(255, 255, 255);
ImVec4 TitleBar = ImColor(4, 5, 7, 230);
ImVec4 TitleBarBorder = ImColor(0, 210, 255, 35);
ImVec4 SideBar = ImColor(4, 5, 7, 230);
ImVec4 SideBarBorder = ImColor(0, 210, 255, 40);
ImVec4 ButtonHovered = ImColor(0, 210, 255, 60);
ImVec4 TestingTest = ImColor(0, 210, 255);
ImVec4 InputBackground = ImColor(8, 10, 14, 255);
ImVec4 InputBorder = ImColor(0, 210, 255, 50);
};
inline cColors g_Col;
class c_globals {
public:
std::string id;
std::string version;
DWORD ProcIdFiveM = 0;
int Pid;
bool g_bPassedByThisVerify;
uintptr_t g_VerifyLogin;
bool done;
bool IsOpen;
std::string ServerIp = "192.168.0.25";
std::string UserName = " ";
std::string Role = " ";
ImVec2 TestePos;
char m_Config[ 6000 ];
HWND g_hCheatWindow;
HWND g_hGameWindow;
ImVec2 g_vGameWindowSize;
ImVec2 g_vGameWindowPos;
ImVec2 g_vGameWindowCenter;
ImFont * m_FontBig;
ImFont * m_FontBigSmall;
ImFont * m_FontNormal;
ImFont * m_FontSecundary;
ImFont * m_FontSmaller;
ImFont * m_DrawFont;
ImFont * m_DrawFontDefault;
ImFont * m_DrawFontMinecraft;
ImFont * m_DrawFontVegas;
ImFont * m_Expand;
float ParticleSpeed = 0.5f;
ImFont * FontAwesomeSolid;
ImFont * FontAwesomeSolidSmall;
ImFont * FontAwesomeRegular;
ImFont * FontAwesomeBrands;
ID3D11ShaderResourceView* backgroud = nullptr;
ID3D11ShaderResourceView * Logo = nullptr;
struct FiveM_Peds_t {
ID3D11ShaderResourceView * A_C_Chimp = nullptr;
ID3D11ShaderResourceView* a_m_y_skater_01 = nullptr;
}FiveM_PedsPic;
};
inline c_globals g_Variables;
class c_menu {
public:
enum PAGES {
Combat,
Visuals,
Local,
World,
Exploits,
Settings,
Login
};
bool IsOpen;
int iTabCount = 0;
float TabAlpha = 0.f;
int iCurrentPage = 6;
    float TabAdd = 0.f;
    char cDiscordId[ 200 ] ;
    char user[30] = "";
    char pass[30] = "";
    std::string server_response;
    ImVec2 MenuSize{ 680, 500 };
    bool particles = true;
};
inline c_menu g_MenuInfo;
extern SessionManager g_Session;
