#pragma once
#include "Includes/Includes.hpp"
#include <Includes/Utils.hpp>
#include <iostream>
namespace Core {
class Config {
public:
struct General {
public:
inline static bool StreamProof = true;
inline static bool WaterMark = true;
inline static bool WaterMarkCol;
inline static bool ArrayList;
inline static bool ArrayListCol;
inline static bool VSync = true;
inline static int ProcessPriority = 0;
inline static int MenuKey = VK_INSERT;
} *General;
struct Aimbot {
public:
inline static bool Enabled;
inline static bool ShowFov;
inline static bool OnlyVisible;
inline static bool IgnoreNPCs;
inline static bool Prediction;
inline static int FOV = 180;
inline static int MaxDistance = 240;
inline static int SmoothHorizontal = 20;
inline static int SmoothVertical = 20;
inline static bool LegitMode;
inline static int HitBox;
inline static int KeyBind;
inline static bool ClosestFOV;
inline static ImColor FovColor { 255, 255, 255 };
} *Aimbot;
struct TriggerBot {
public:
inline static bool Enabled;
inline static bool ShowFov;
inline static bool OnlyVisible;
inline static bool IgnoreNPCs;
inline static bool SmartTrigger;
inline static int FOV = 20;
inline static int MaxDistance = 200;
inline static int Delay = 0;
inline static int KeyBind;
inline static ImColor FovColor { 0, 255, 255 };
} *TriggerBot;
struct SilentAim {
public:
inline static bool Enabled;
inline static bool ShowFov;
inline static bool OnlyVisible;
inline static bool MagicBullets;
inline static bool IgnoreNPCs;
inline static int FOV = 40;
inline static int MissChance = 0;
inline static int MaxDistance = 200;
inline static int HitBox = 0;
inline static int KeyBind;
inline static ImColor FovColor { 224, 94, 103, 200 };
} *SilentAim;
struct ESP {
public:
inline static bool UpdateCfgESP;
inline static bool Enabled;
inline static bool Box;
inline static bool FilledBox;
inline static int BoxState = 0;
inline static bool Skeleton;
inline static float SkeletonThickness = 1.5f;
inline static bool HealthBar;
inline static ImVec2 HealthBarPos;
inline static int HealthBarState = 0;
inline static bool ArmorBar;
inline static ImVec2 ArmorBarPos;
inline static int ArmorBarState = 0;
inline static bool WeaponName;
inline static ImVec2 WeaponNamePos;
inline static int WeaponNameState = 0;
inline static bool SnapLines;
inline static bool UserNames;
inline static ImVec2 UserNamesPos;
inline static int UserNamesState = 0;
inline static bool HeadCircle;
inline static bool IgnoreNPCs;
inline static bool ShowLocalPlayer;
inline static bool VisibleCheck;
inline static bool HighlightVisible;
inline static bool IgnoreDead;
inline static bool DistanceFromMe;
inline static bool FriendsMarker;
inline static int FriendsMarkerBind;
inline static ImVec2 DistanceFromMePos;
inline static int DistanceFromMeState = 0;
inline static int MaxDistance = 200;
inline static ImColor DistanceCol { 230, 230, 230, 255 };
inline static ImColor UserNamesCol { 230, 230, 230, 255 };
inline static ImColor WeaponNameCol { 230, 230, 230, 255 };
inline static ImColor SkeletonCol { 255, 255, 255, 200 };
inline static ImColor BoxCol { 255, 255, 255, 200 };
inline static ImColor FilledBoxCol { 0, 0, 0, 40 };
inline static ImColor SnapLinesCol { 255, 255, 255, 200 };
inline static ImColor FriendCol { 255, 204, 0, 255 };
inline static int KeyBind;
} *ESP;
struct VehicleESP {
public:
inline static bool Enabled;
inline static bool SnapLines;
inline static bool ShowLockUnlock;
inline static bool VehName;
inline static bool DistanceFromMe;
inline static int MaxDistance = 200;
inline static ImColor SnapLinesCol { 255, 255, 255, 200 };
} *VehicleESP;
struct Player {
public:
inline static float CurrentHealthValue;
inline static float CurrentArmorValue;
inline static bool FastRun;
inline static float RunSpeed = 1.f;
inline static bool InfiniteStamina;
inline static bool WeaponOptions;
inline static bool NoRecoilEnabled;
inline static float RecoilValue;
inline static bool NoSpreadEnabled;
inline static float SpreadValue;
inline static bool InfiniteAmmoEnabled;
inline static bool NoReloadEnabled;
inline static bool WeaponScaleEnabled;
inline static float WeaponSize = 1.0f;
inline static bool AntiAimEnabled;
inline static int AntiAimKey;
inline static bool NoClipEnabled;
inline static bool NoClipDisable = 0;
inline static bool HandlingEditor;
inline static int NoClipKey;
inline static bool NoClipHoldMode;
inline static float NoClipSpeed = 2.0f;
inline static bool InfiniteCombatRoll;
inline static bool EnableGodMode;
inline static bool VehicleGodMode;
inline static bool fix;
inline static bool SeatBelt;
inline static bool ForceWeaponWheel;
inline static bool ShrinkEnabled;
inline static bool NoRagDollEnabled;
inline static bool AntiHSEnabled;
inline static bool StealCarEnabled;
inline static int GodModeKey;
inline static int FixCar;
inline static bool HornetBoost;
} *Player;
nlohmann::json ImColToJson( const ImColor & Col ) {
return nlohmann::json::array( { Col.Value.x, Col.Value.y, Col.Value.z, Col.Value.w } );
}
ImColor JsonToImCol( const nlohmann::json & JsonCol ) {
if ( JsonCol.is_array( ) && JsonCol.size( ) == 4 ) {
float r = JsonCol[ 0 ];
float g = JsonCol[ 1 ];
float b = JsonCol[ 2 ];
float a = JsonCol[ 3 ];
return ImColor( r, g, b, a );
}
else {
return ImColor( 0.0f, 0.0f, 0.0f, 1.0f );
}
}
std::string SaveCurrentConfig( std::string CfgName )
{
try {
nlohmann::json CfgJson;
auto& GeneralCfg = CfgJson[ xorstr( "General" ) ];
auto& FeaturesCfg = CfgJson;
// General
GeneralCfg[ xorstr( "StreamProof" ) ] = General->StreamProof;
GeneralCfg[ xorstr( "WaterMark" ) ] = General->WaterMark;
GeneralCfg[ xorstr( "ArrayList" ) ] = General->ArrayList;
GeneralCfg[ xorstr( "VSync" ) ] = General->VSync;
GeneralCfg[ xorstr( "ProcessPriority" ) ] = General->ProcessPriority;
GeneralCfg[ xorstr( "MenuKey" ) ] = General->MenuKey;
// Aimbot
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "Enabled" ) ] = Aimbot->Enabled;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "ShowFov" ) ] = Aimbot->ShowFov;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "OnlyVisible" ) ] = Aimbot->OnlyVisible;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "IgnoreNPCs" ) ] = Aimbot->IgnoreNPCs;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "Prediction" ) ] = Aimbot->Prediction;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "FOV" ) ] = Aimbot->FOV;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "MaxDistance" ) ] = Aimbot->MaxDistance;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "ClosestFOV" ) ] = Aimbot->ClosestFOV;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "SmoothHorizontal" ) ] = Aimbot->SmoothHorizontal;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "SmoothVertical" ) ] = Aimbot->SmoothVertical;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "LegitMode" ) ] = Aimbot->LegitMode;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "HitBox" ) ] = Aimbot->HitBox;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "KeyBind" ) ] = Aimbot->KeyBind;
FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "FovColor" ) ] = ImColToJson( Aimbot->FovColor );
// TriggerBot
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "Enabled" ) ] = TriggerBot->Enabled;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "ShowFov" ) ] = TriggerBot->ShowFov;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "OnlyVisible" ) ] = TriggerBot->OnlyVisible;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "IgnoreNPCs" ) ] = TriggerBot->IgnoreNPCs;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "SmartTrigger" ) ] = TriggerBot->SmartTrigger;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "FOV" ) ] = TriggerBot->FOV;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "MaxDistance" ) ] = TriggerBot->MaxDistance;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "Delay" ) ] = TriggerBot->Delay;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "KeyBind" ) ] = TriggerBot->KeyBind;
FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "FovColor" ) ] = ImColToJson( TriggerBot->FovColor );
// SilentAim
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "Enabled" ) ] = SilentAim->Enabled;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "ShowFov" ) ] = SilentAim->ShowFov;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "OnlyVisible" ) ] = SilentAim->OnlyVisible;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "IgnoreNPCs" ) ] = SilentAim->IgnoreNPCs;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "FOV" ) ] = SilentAim->FOV;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MaxDistance" ) ] = SilentAim->MaxDistance;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "KeyBind" ) ] = SilentAim->KeyBind;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MissChance" ) ] = SilentAim->MissChance;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "HitBox" ) ] = SilentAim->HitBox;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MagicBullets" ) ] = SilentAim->MagicBullets;
FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "FovColor" ) ] = ImColToJson( SilentAim->FovColor );
// ESP
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Enabled" ) ] = ESP->Enabled;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Box" ) ] = ESP->Box;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FilledBox" ) ] = ESP->FilledBox;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "BoxState" ) ] = ESP->BoxState;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Skeleton" ) ] = ESP->Skeleton;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SkeletonThickness" ) ] = ESP->SkeletonThickness;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HealthBar" ) ] = ESP->HealthBar;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HealthBarState" ) ] = ESP->HealthBarState;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ArmorBar" ) ] = ESP->ArmorBar;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ArmorBarState" ) ] = ESP->ArmorBarState;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponName" ) ] = ESP->WeaponName;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponNameState" ) ] = ESP->WeaponNameState;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SnapLines" ) ] = ESP->SnapLines;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNames" ) ] = ESP->UserNames;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNamesState" ) ] = ESP->UserNamesState;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HeadCircle" ) ] = ESP->HeadCircle;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "IgnoreNPCs" ) ] = ESP->IgnoreNPCs;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HighlightVisible" ) ] = ESP->HighlightVisible;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "IgnoreDead" ) ] = ESP->IgnoreDead;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceFromMe" ) ] = ESP->DistanceFromMe;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceFromMeState" ) ] = ESP->DistanceFromMeState;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "MaxDistance" ) ] = ESP->MaxDistance;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ShowLocalPlayer" ) ] = ESP->ShowLocalPlayer;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "VisibleCheck" ) ] = ESP->VisibleCheck;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FriendsMarker" ) ] = ESP->FriendsMarker;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FriendsMarkerBind" ) ] = ESP->FriendsMarkerBind;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "KeyBind" ) ] = ESP->KeyBind;
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceCol" ) ] = ImColToJson( ESP->DistanceCol );
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNamesCol" ) ] = ImColToJson( ESP->UserNamesCol );
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponNameCol" ) ] = ImColToJson( ESP->WeaponNameCol );
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SkeletonCol" ) ] = ImColToJson( ESP->SkeletonCol );
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "BoxCol" ) ] = ImColToJson( ESP->BoxCol );
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FilledBoxCol" ) ] = ImColToJson( ESP->FilledBoxCol );
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SnapLinesCol" ) ] = ImColToJson( ESP->SnapLinesCol );
FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FriendCol" ) ] = ImColToJson( ESP->FriendCol );
// VehicleESP
FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "Enabled" ) ] = VehicleESP->Enabled;
FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "SnapLines" ) ] = VehicleESP->SnapLines;
FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "ShowLockUnlock" ) ] = VehicleESP->ShowLockUnlock;
FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "VehName" ) ] = VehicleESP->VehName;
FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "DistanceFromMe" ) ] = VehicleESP->DistanceFromMe;
FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "MaxDistance" ) ] = VehicleESP->MaxDistance;
FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "SnapLinesCol" ) ] = ImColToJson( VehicleESP->SnapLinesCol );
// Player
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "EnableGodMode" ) ] = Player->EnableGodMode;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "GodModeKey" ) ] = Player->GodModeKey;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "VehicleGodMode" ) ] = Player->VehicleGodMode;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "AntiHSEnabled" ) ] = Player->AntiHSEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipEnabled" ) ] = Player->NoClipEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipKey" ) ] = Player->NoClipKey;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipHoldMode" ) ] = Player->NoClipHoldMode;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipSpeed" ) ] = Player->NoClipSpeed;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "FastRun" ) ] = Player->FastRun;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "RunSpeed" ) ] = Player->RunSpeed;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "InfiniteStamina" ) ] = Player->InfiniteStamina;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "ShrinkEnabled" ) ] = Player->ShrinkEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoRagDollEnabled" ) ] = Player->NoRagDollEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "InfiniteCombatRoll" ) ] = Player->InfiniteCombatRoll;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoRecoilEnabled" ) ] = Player->NoRecoilEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoSpreadEnabled" ) ] = Player->NoSpreadEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "InfiniteAmmoEnabled" ) ] = Player->InfiniteAmmoEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoReloadEnabled" ) ] = Player->NoReloadEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "WeaponScaleEnabled" ) ] = Player->WeaponScaleEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "WeaponSize" ) ] = Player->WeaponSize;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "AntiAimEnabled" ) ] = Player->AntiAimEnabled;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "AntiAimKey" ) ] = Player->AntiAimKey;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "SeatBelt" ) ] = Player->SeatBelt;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "HornetBoost" ) ] = Player->HornetBoost;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "HandlingEditor" ) ] = Player->HandlingEditor;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "FixCar" ) ] = Player->FixCar;
FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "StealCarEnabled" ) ] = Player->StealCarEnabled;
std::string CfgJsonStr = CfgJson.dump( );
Utils::PasteClipboard( Utils::EncodeB64( Utils::Str2Hex( Utils::EncodeB64( CfgJsonStr ) ) ).c_str( ) );
return xorstr( "Config Exported to Clipboard." );
}
catch ( const std::exception & e ) {
return xorstr( "Failed to save config." );
}
}
std::string LoadCfg( std::string CfgName, std::string CfgCode )
{
try {
std::string DecCfgCodeStr = Utils::DecodeB64( Utils::Hex2Str( Utils::DecodeB64( CfgCode ) ) );
nlohmann::json CfgJson = nlohmann::json( ).parse( DecCfgCodeStr );
auto& GeneralCfg = CfgJson[ xorstr( "General" ) ];
auto& FeaturesCfg = CfgJson;
// General
if ( GeneralCfg != NULL )
{
General->StreamProof = GeneralCfg[ xorstr( "StreamProof" ) ];
General->WaterMark = GeneralCfg[ xorstr( "WaterMark" ) ];
General->ArrayList = GeneralCfg[ xorstr( "ArrayList" ) ];
General->VSync = GeneralCfg[ xorstr( "VSync" ) ];
General->ProcessPriority = GeneralCfg[ xorstr( "ProcessPriority" ) ];
General->MenuKey = GeneralCfg[ xorstr( "MenuKey" ) ];
}
// Aimbot
Aimbot->Enabled = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "Enabled" ) ];
Aimbot->ShowFov = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "ShowFov" ) ];
Aimbot->OnlyVisible = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "OnlyVisible" ) ];
Aimbot->IgnoreNPCs = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "IgnoreNPCs" ) ];
Aimbot->Prediction = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "Prediction" ) ];
Aimbot->FOV = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "FOV" ) ];
Aimbot->MaxDistance = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "MaxDistance" ) ];
if (FeaturesCfg[xorstr("Aimbot")].contains(xorstr("ClosestFOV")))
Aimbot->ClosestFOV = FeaturesCfg[xorstr("Aimbot")][xorstr("ClosestFOV")];
Aimbot->SmoothHorizontal = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "SmoothHorizontal" ) ];
Aimbot->SmoothVertical = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "SmoothVertical" ) ];
if (FeaturesCfg[xorstr("Aimbot")].contains(xorstr("LegitMode")))
Aimbot->LegitMode = FeaturesCfg[xorstr("Aimbot")][xorstr("LegitMode")];
if (FeaturesCfg[xorstr("Aimbot")].contains(xorstr("HitBox")))
Aimbot->HitBox = FeaturesCfg[xorstr("Aimbot")][xorstr("HitBox")];
Aimbot->KeyBind = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "KeyBind" ) ];
Aimbot->FovColor = JsonToImCol( FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "FovColor" ) ] );
// TriggerBot
TriggerBot->Enabled = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "Enabled" ) ];
TriggerBot->ShowFov = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "ShowFov" ) ];
TriggerBot->OnlyVisible = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "OnlyVisible" ) ];
TriggerBot->IgnoreNPCs = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "IgnoreNPCs" ) ];
if (FeaturesCfg[xorstr("TriggerBot")].contains(xorstr("SmartTrigger")))
TriggerBot->SmartTrigger = FeaturesCfg[xorstr("TriggerBot")][xorstr("SmartTrigger")];
TriggerBot->FOV = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "FOV" ) ];
TriggerBot->MaxDistance = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "MaxDistance" ) ];
TriggerBot->Delay = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "Delay" ) ];
TriggerBot->KeyBind = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "KeyBind" ) ];
TriggerBot->FovColor = JsonToImCol( FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "FovColor" ) ] );
// SilentAim
SilentAim->Enabled = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "Enabled" ) ];
SilentAim->ShowFov = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "ShowFov" ) ];
SilentAim->OnlyVisible = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "OnlyVisible" ) ];
SilentAim->IgnoreNPCs = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "IgnoreNPCs" ) ];
SilentAim->FOV = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "FOV" ) ];
SilentAim->MaxDistance = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MaxDistance" ) ];
SilentAim->KeyBind = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "KeyBind" ) ];
if (FeaturesCfg[xorstr("SilentAim")].contains(xorstr("MissChance")))
SilentAim->MissChance = FeaturesCfg[xorstr("SilentAim")][xorstr("MissChance")];
if (FeaturesCfg[xorstr("SilentAim")].contains(xorstr("HitBox")))
SilentAim->HitBox = FeaturesCfg[xorstr("SilentAim")][xorstr("HitBox")];
SilentAim->MagicBullets = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MagicBullets" ) ];
SilentAim->FovColor = JsonToImCol( FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "FovColor" ) ] );
// ESP
ESP->Enabled = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Enabled" ) ];
ESP->Box = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Box" ) ];
if (FeaturesCfg[xorstr("ESP")].contains(xorstr("FilledBox")))
ESP->FilledBox = FeaturesCfg[xorstr("ESP")][xorstr("FilledBox")];
ESP->BoxState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "BoxState" ) ];
ESP->Skeleton = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Skeleton" ) ];
if (FeaturesCfg[xorstr("ESP")].contains(xorstr("SkeletonThickness")))
ESP->SkeletonThickness = FeaturesCfg[xorstr("ESP")][xorstr("SkeletonThickness")];
ESP->HealthBar = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HealthBar" ) ];
ESP->HealthBarState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HealthBarState" ) ];
ESP->ArmorBar = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ArmorBar" ) ];
ESP->ArmorBarState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ArmorBarState" ) ];
ESP->WeaponName = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponName" ) ];
ESP->WeaponNameState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponNameState" ) ];
ESP->SnapLines = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SnapLines" ) ];
ESP->UserNames = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNames" ) ];
ESP->UserNamesState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNamesState" ) ];
ESP->HeadCircle = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HeadCircle" ) ];
ESP->IgnoreNPCs = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "IgnoreNPCs" ) ];
ESP->HighlightVisible = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HighlightVisible" ) ];
ESP->IgnoreDead = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "IgnoreDead" ) ];
ESP->DistanceFromMe = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceFromMe" ) ];
ESP->DistanceFromMeState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceFromMeState" ) ];
ESP->ShowLocalPlayer = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ShowLocalPlayer" ) ];
if (FeaturesCfg[xorstr("ESP")].contains(xorstr("VisibleCheck")))
ESP->VisibleCheck = FeaturesCfg[xorstr("ESP")][xorstr("VisibleCheck")];
ESP->MaxDistance = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "MaxDistance" ) ];
if (FeaturesCfg[xorstr("ESP")].contains(xorstr("FriendsMarker")))
ESP->FriendsMarker = FeaturesCfg[xorstr("ESP")][xorstr("FriendsMarker")];
if (FeaturesCfg[xorstr("ESP")].contains(xorstr("FriendsMarkerBind")))
ESP->FriendsMarkerBind = FeaturesCfg[xorstr("ESP")][xorstr("FriendsMarkerBind")];
if (FeaturesCfg[xorstr("ESP")].contains(xorstr("KeyBind")))
ESP->KeyBind = FeaturesCfg[xorstr("ESP")][xorstr("KeyBind")];
ESP->DistanceCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceCol" ) ] );
ESP->UserNamesCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNamesCol" ) ] );
ESP->WeaponNameCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponNameCol" ) ] );
ESP->SkeletonCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SkeletonCol" ) ] );
ESP->BoxCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "BoxCol" ) ] );
if (FeaturesCfg[xorstr("ESP")].contains(xorstr("FilledBoxCol")))
ESP->FilledBoxCol = JsonToImCol( FeaturesCfg[xorstr("ESP")][xorstr("FilledBoxCol")] );
ESP->SnapLinesCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SnapLinesCol" ) ] );
ESP->FriendCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FriendCol" ) ] );
// VehicleESP
VehicleESP->Enabled = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "Enabled" ) ];
VehicleESP->SnapLines = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "SnapLines" ) ];
VehicleESP->ShowLockUnlock = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "ShowLockUnlock" ) ];
VehicleESP->VehName = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "VehName" ) ];
VehicleESP->DistanceFromMe = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "DistanceFromMe" ) ];
VehicleESP->MaxDistance = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "MaxDistance" ) ];
VehicleESP->SnapLinesCol = JsonToImCol( FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "SnapLinesCol" ) ] );
// Player
if (FeaturesCfg[xorstr("Player")].contains(xorstr("EnableGodMode")))
Player->EnableGodMode = FeaturesCfg[xorstr("Player")][xorstr("EnableGodMode")];
Player->GodModeKey = FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "GodModeKey" ) ];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("VehicleGodMode")))
Player->VehicleGodMode = FeaturesCfg[xorstr("Player")][xorstr("VehicleGodMode")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("AntiHSEnabled")))
Player->AntiHSEnabled = FeaturesCfg[xorstr("Player")][xorstr("AntiHSEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("NoClipEnabled")))
Player->NoClipEnabled = FeaturesCfg[xorstr("Player")][xorstr("NoClipEnabled")];
Player->NoClipKey = FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipKey" ) ];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("NoClipHoldMode")))
Player->NoClipHoldMode = FeaturesCfg[xorstr("Player")][xorstr("NoClipHoldMode")];
Player->NoClipSpeed = FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipSpeed" ) ];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("FastRun")))
Player->FastRun = FeaturesCfg[xorstr("Player")][xorstr("FastRun")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("RunSpeed")))
Player->RunSpeed = FeaturesCfg[xorstr("Player")][xorstr("RunSpeed")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("InfiniteStamina")))
Player->InfiniteStamina = FeaturesCfg[xorstr("Player")][xorstr("InfiniteStamina")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("ShrinkEnabled")))
Player->ShrinkEnabled = FeaturesCfg[xorstr("Player")][xorstr("ShrinkEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("NoRagDollEnabled")))
Player->NoRagDollEnabled = FeaturesCfg[xorstr("Player")][xorstr("NoRagDollEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("InfiniteCombatRoll")))
Player->InfiniteCombatRoll = FeaturesCfg[xorstr("Player")][xorstr("InfiniteCombatRoll")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("NoRecoilEnabled")))
Player->NoRecoilEnabled = FeaturesCfg[xorstr("Player")][xorstr("NoRecoilEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("NoSpreadEnabled")))
Player->NoSpreadEnabled = FeaturesCfg[xorstr("Player")][xorstr("NoSpreadEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("InfiniteAmmoEnabled")))
Player->InfiniteAmmoEnabled = FeaturesCfg[xorstr("Player")][xorstr("InfiniteAmmoEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("NoReloadEnabled")))
Player->NoReloadEnabled = FeaturesCfg[xorstr("Player")][xorstr("NoReloadEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("WeaponScaleEnabled")))
Player->WeaponScaleEnabled = FeaturesCfg[xorstr("Player")][xorstr("WeaponScaleEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("WeaponSize")))
Player->WeaponSize = FeaturesCfg[xorstr("Player")][xorstr("WeaponSize")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("AntiAimEnabled")))
Player->AntiAimEnabled = FeaturesCfg[xorstr("Player")][xorstr("AntiAimEnabled")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("AntiAimKey")))
Player->AntiAimKey = FeaturesCfg[xorstr("Player")][xorstr("AntiAimKey")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("SeatBelt")))
Player->SeatBelt = FeaturesCfg[xorstr("Player")][xorstr("SeatBelt")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("HornetBoost")))
Player->HornetBoost = FeaturesCfg[xorstr("Player")][xorstr("HornetBoost")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("HandlingEditor")))
Player->HandlingEditor = FeaturesCfg[xorstr("Player")][xorstr("HandlingEditor")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("FixCar")))
Player->FixCar = FeaturesCfg[xorstr("Player")][xorstr("FixCar")];
if (FeaturesCfg[xorstr("Player")].contains(xorstr("StealCarEnabled")))
Player->StealCarEnabled = FeaturesCfg[xorstr("Player")][xorstr("StealCarEnabled")];
ESP->UpdateCfgESP = true;
return xorstr( "Config loaded with success." );
}
catch ( const std::exception & e ) {
return xorstr( "Error Loading Config!");
}
}
};
inline Config g_Config;
}
