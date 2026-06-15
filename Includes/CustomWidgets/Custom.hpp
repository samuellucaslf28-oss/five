#pragma once
#include <Includes/includes.hpp>
#include <Includes/Utils.hpp>
#include <map>
#include <vector>
#include <cmath>
#include <cstdlib>
namespace Custom {
using namespace ImGui;
struct Point {
float x, y;
float vx, vy;
float life;
float maxlife;
};
class GeometricEffect {
public:
GeometricEffect( int width, int height, int numPoints, ImColor color )
: width( width ), height( height ), numPoints( numPoints ), color( color ) {
initPoints( );
}
void setDimensions( int w, int h ) {
width = w;
height = h;
}
void render( ImDrawList * drawList, ImVec2 origin ) {
updatePoints( );
for ( int i = 0; i < points.size( ); ++i ) {
Point & p = points[ i ];
ImVec2 pos = ImVec2( origin.x + p.x, origin.y + p.y );
float t = ( p.life / p.maxlife );
float alpha = t < 0.5f ? t * 2.f : ( 1.f - t ) * 2.f;
alpha = ImClamp( alpha, 0.f, 1.f );
ImColor baseCol = color;
baseCol.Value.w *= alpha;
drawList->AddCircleFilled( pos, 2.0f, baseCol );
for ( int j = i + 1; j < points.size( ); ++j ) {
Point & other = points[ j ];
float dx = p.x - other.x;
float dy = p.y - other.y;
float distance = std::sqrt( dx * dx + dy * dy );
const float linkDist = 140.0f;
if ( distance < linkDist ) {
float alphaFactor = ( 1.0f - distance / linkDist );
ImColor lineColor = baseCol;
lineColor.Value.w *= alphaFactor;
drawList->AddLine(
ImVec2( origin.x + p.x, origin.y + p.y ),
ImVec2( origin.x + other.x, origin.y + other.y ),
lineColor, 1.0f
);
}
}
}
}
void setColor( ImColor newColor ) {
color = newColor;
}
private:
int width, height, numPoints;
ImColor color;
std::vector<Point> points;
void initPoints( ) {
points.clear( );
for ( int i = 0; i < numPoints; ++i ) {
points.push_back( spawnPoint( ) );
}
}
Point spawnPoint( ) {
Point p;
p.x = randomFloat( 0.f, ( float ) width );
p.y = randomFloat( 0.f, ( float ) height );
p.vx = 0.0f;
p.vy = randomFloat( 0.01f, 0.04f );
p.maxlife = randomFloat( 4.f, 9.f );
p.life = p.maxlife;
return p;
}
void updatePoints( ) {
float speedFactor = g_Variables.ParticleSpeed;
speedFactor = ImClamp( speedFactor, 0.05f, 2.0f );
for ( auto & p : points ) {
if ( std::fabs( p.vy ) < 0.005f ) {
p.vy = randomFloat( 0.01f, 0.04f );
}
p.vx = 0.0f;
p.y += p.vy * ( 0.5f * speedFactor );
p.vy *= 0.99f;
p.vy += randomFloat( -0.005f, 0.008f );
if ( p.x < 0 ) { p.x = 0; }
if ( p.x > width ) { p.x = ( float ) width; }
if ( p.y < 0 ) { p.y = 0; p.vy *= -1; }
if ( p.y > height ) { p.y = ( float ) height; p.vy *= -1; }
const float vmax = 0.08f;
if ( p.vy > vmax ) p.vy = vmax;
if ( p.vy < -vmax ) p.vy = -vmax;
p.life -= 0.02f;
if ( p.life <= 0.f || p.y >= height + 50.f ) {
p = spawnPoint( );
}
}
}
float randomFloat( float min, float max ) {
return min + static_cast< float >( std::rand( ) ) / ( static_cast< float >( RAND_MAX / ( max - min ) ) );
}
};
inline GeometricEffect & GetBackgroundEffect( ) {
static GeometricEffect effect( 700, 500, 40, ImColor( 255, 255, 255, 28 ) );
return effect;
}
inline double EaseInOutCirc( double t )
{
if ( t < 0.5 )
return ( 1 - std::sqrt( 1 - 2 * t ) ) * 0.5;
else
return ( 1 + std::sqrt( 2 * t - 1 ) ) * 0.5;
}
inline int rotation_start_index;
inline void ImRotateStart( )
{
rotation_start_index = ImGui::GetWindowDrawList( )->VtxBuffer.Size;
}
inline ImVec2 ImRotationCenter( )
{
ImVec2 l( FLT_MAX, FLT_MAX ), u( -FLT_MAX, -FLT_MAX );
const auto & buf = ImGui::GetWindowDrawList( )->VtxBuffer;
for ( int i = rotation_start_index; i < buf.Size; i++ )
l = ImMin( l, buf[ i ].pos ), u = ImMax( u, buf[ i ].pos );
return ImVec2( ( l.x + u.x ) / 2, ( l.y + u.y ) / 2 );
}
inline void ImRotateEnd( float rad, ImVec2 center = ImRotationCenter( ) )
{
float s = sin( rad ), c = cos( rad );
center = ImRotate( center, s, c ) - center;
auto & buf = ImGui::GetWindowDrawList( )->VtxBuffer;
for ( int i = rotation_start_index; i < buf.Size; i++ )
buf[ i ].pos = ImRotate( buf[ i ].pos, s, c ) - center;
}
inline void DrawBackground( bool Logged ) {
const ImVec2 pos = ImGui::GetWindowPos( );
ImDrawList * draw = ImGui::GetWindowDrawList( );
if (g_MenuInfo.IsOpen)
{
float extraRight = (g_MenuInfo.iCurrentPage == g_MenuInfo.Visuals) ? 260.0f : 0.0f;
draw->AddRectFilled(
ImVec2(pos.x, pos.y),
ImVec2(pos.x + g_MenuInfo.MenuSize.x + extraRight, pos.y + g_MenuInfo.MenuSize.y),
ImColor(0, 0, 0, 255),
12.f
);
auto & effect = GetBackgroundEffect( );
effect.setDimensions( (int)(g_MenuInfo.MenuSize.x + extraRight), (int)g_MenuInfo.MenuSize.y );
effect.render( draw, pos );
}
if ( Logged ){
static int Pad = 8;
ImGui::SetCursorPos( ImVec2( 395 - Pad, - 5 - Pad ) );
ImGui::Image( g_Variables.Logo, ImVec2(  100 + Pad, 100 + Pad ) );
}
}
inline bool Tab(const char* icon, const char* label, bool active)
{
struct Tab_t {
ImVec4 BackgroundColor;
ImVec2 BackgroundGrow;
ImVec4 IconColor;
ImVec4 TextColor;
float UnSelectedAnim;
float BarAlpha;
};
ImGuiWindow* window = ImGui::GetCurrentWindow();
ImDrawList* DrawList = window->DrawList;
if (window->SkipItems) {
return false;
}
ImGuiContext& g = *GImGui;
const ImGuiStyle& style = g.Style;
const ImGuiID id = window->GetID(label);
const ImGuiIO IO = g.IO;
const ImVec2 pos = window->DC.CursorPos;
const ImRect rect(pos, pos + ImVec2(45, 45));
ImGui::ItemSize(rect, style.FramePadding.y);
if (!ImGui::ItemAdd(rect, id)) {
return false;
}
bool hovered, held;
bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held);
if (pressed) { ImGui::MarkItemEdited(id); }
static std::map<ImGuiID, Tab_t> anim;
auto TabAnim = anim.find(id);
if (TabAnim == anim.end()) {
anim.insert({ id, Tab_t() });
TabAnim = anim.find(id);
}
float NormalizedTime = ImClamp(IO.DeltaTime * 10.f, 0.0f, 1.0f);
float NormalizedTime2 = ImClamp(IO.DeltaTime * 8.f, 0.0f, 1.0f);
TabAnim->second.BackgroundColor = ImLerp(TabAnim->second.BackgroundColor, active ? ImVec4(g_Col.Tabs.x, g_Col.Tabs.y, g_Col.Tabs.z, 1.0f) : ImVec4(g_Col.Tabs.x, g_Col.Tabs.y, g_Col.Tabs.z, 0.0f), Custom::EaseInOutCirc(NormalizedTime));
TabAnim->second.IconColor = ImLerp(TabAnim->second.IconColor, active ? ImColor(9, 11, 11) : ImColor(74, 74, 74), Custom::EaseInOutCirc(NormalizedTime));
TabAnim->second.TextColor = ImLerp(TabAnim->second.TextColor, active ? ImColor(200, 200, 200) : ImColor(60, 60, 60), Custom::EaseInOutCirc(NormalizedTime));
TabAnim->second.BackgroundGrow = ImLerp(TabAnim->second.BackgroundGrow, active ? ImVec2(4, 4) : ImVec2(0, 0), Custom::EaseInOutCirc(NormalizedTime2));
TabAnim->second.UnSelectedAnim = ImLerp(TabAnim->second.UnSelectedAnim, hovered && !active ? 4.f : 0.f, IO.DeltaTime * 8.f);
TabAnim->second.BarAlpha = ImLerp(TabAnim->second.BarAlpha, active ? 1.0f : 0.0f, Custom::EaseInOutCirc(NormalizedTime));
const float rounding = 6.f;
ImVec4 glowColor = TabAnim->second.BackgroundColor;
glowColor.w *= 0.3f;
DrawList->AddRectFilled(
ImVec2(rect.Min.x - TabAnim->second.BackgroundGrow.x - 4, rect.Min.y - TabAnim->second.BackgroundGrow.x - 4),
ImVec2(rect.Max.x + TabAnim->second.BackgroundGrow.x + 4, rect.Max.y + TabAnim->second.BackgroundGrow.x + 4),
ImGui::GetColorU32(glowColor),
rounding + 4
);
DrawList->AddRectFilled(ImVec2(rect.Min.x - TabAnim->second.BackgroundGrow.x, rect.Min.y - TabAnim->second.BackgroundGrow.x), ImVec2(rect.Max.x + TabAnim->second.BackgroundGrow.x, rect.Max.y + TabAnim->second.BackgroundGrow.x), ImGui::GetColorU32(TabAnim->second.BackgroundColor), rounding, 0);
auto IconTextSize = Utils::CalcTextSize(g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize, icon);
DrawList->AddText(g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize, ImVec2(rect.Min.x + 11 + TabAnim->second.UnSelectedAnim, pos.y + ((rect.GetHeight() - IconTextSize.y) / 2)), ImGui::GetColorU32(TabAnim->second.IconColor), icon);
IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
return pressed;
}
inline bool SubTab( const char * label, bool active )
{
struct SubTab_t {
ImVec4 BackgroundColor;
ImVec2 BackgroundGrow;
ImVec4 TextColor;
float UnSelectedAnim;
};
ImGuiWindow * window = ImGui::GetCurrentWindow( );
ImDrawList * DrawList = window->DrawList;
if ( window->SkipItems ) {
return false;
}
ImGuiContext & g = *GImGui;
const ImGuiStyle & style = g.Style;
std::string IdStr = std::string( label );
const ImGuiID id = window->GetID( IdStr.c_str( ) );
const ImGuiIO IO = g.IO;
const ImVec2 pos = window->DC.CursorPos;
auto TextSize = Utils::CalcTextSize( g_Variables.m_FontSecundary, g_Variables.m_FontSecundary->FontSize, label );
const ImRect rect( pos, pos + ImVec2( TextSize.x + 16, 30 ) );
ImGui::ItemSize( rect, style.FramePadding.y );
if ( !ImGui::ItemAdd( rect, id ) ) {
return false;
}
bool hovered, held;
bool pressed = ImGui::ButtonBehavior( rect, id, &hovered, &held );
if ( pressed ) { ImGui::MarkItemEdited( id ); }
static std::map<ImGuiID, SubTab_t> anim;
auto SubTabAnim = anim.find( id );
if ( SubTabAnim == anim.end( ) ) {
anim.insert( { id, SubTab_t( ) } );
SubTabAnim = anim.find( id );
}
float NormalizedTime = ImClamp( IO.DeltaTime * 10.f, 0.0f, 1.0f );
float NormalizedTime2 = ImClamp( IO.DeltaTime * 8.f, 0.0f, 1.0f );
SubTabAnim->second.BackgroundColor = ImLerp( SubTabAnim->second.BackgroundColor, active ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 255.f / 255.f ) : ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.f ), Custom::EaseInOutCirc( NormalizedTime ) );
SubTabAnim->second.TextColor = ImLerp( SubTabAnim->second.TextColor, active ? ImColor(9, 11, 11) : ImColor( 60, 60, 60 ), Custom::EaseInOutCirc( NormalizedTime ) );
SubTabAnim->second.BackgroundGrow = ImLerp( SubTabAnim->second.BackgroundGrow, active ? ImVec2( 4, 4 ) : ImVec2( 0, 0 ), Custom::EaseInOutCirc( NormalizedTime2 ) );
SubTabAnim->second.UnSelectedAnim = ImLerp( SubTabAnim->second.UnSelectedAnim, hovered && !active ? 2.f : 0.f, IO.DeltaTime * 4.f );
const float rounding = 8.f;
ImVec4 glowColor = SubTabAnim->second.BackgroundColor;
glowColor.w *= 0.3f;
DrawList->AddRectFilled(
ImVec2(rect.Min.x - SubTabAnim->second.BackgroundGrow.x - 4, rect.Min.y - SubTabAnim->second.BackgroundGrow.x - 4),
ImVec2(rect.Max.x + SubTabAnim->second.BackgroundGrow.x + 4, rect.Max.y + SubTabAnim->second.BackgroundGrow.x + 4),
ImGui::GetColorU32(glowColor),
rounding + 4
);
DrawList->AddRectFilled(
ImVec2(rect.Min.x - SubTabAnim->second.BackgroundGrow.x, rect.Min.y - SubTabAnim->second.BackgroundGrow.x),
ImVec2(rect.Max.x + SubTabAnim->second.BackgroundGrow.x, rect.Max.y + SubTabAnim->second.BackgroundGrow.x),
ImGui::GetColorU32(SubTabAnim->second.BackgroundColor),
rounding,
0
);
DrawList->AddText( g_Variables.m_FontSecundary, g_Variables.m_FontSecundary->FontSize, ImVec2( pos.x + ( ( rect.GetWidth( ) - TextSize.x ) / 2 ), pos.y + ( ( rect.GetHeight( ) - TextSize.y ) / 2 ) - 1 ), ImGui::GetColorU32( SubTabAnim->second.TextColor ), label );
IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );
return pressed;
}
inline void InvisibleShadow( const float alpha, const ImVec2 pos_min, const ImVec2 pos_max, ImU32 color, float shadow_tickness )
{
ImGui::PushStyleVar( ImGuiStyleVar_Alpha, alpha );
ImGui::PushClipRect( pos_min, pos_max, true );
ImGui::GetWindowDrawList( )->AddShadowCircle( ImVec2( ImGui::GetMousePos( ) ), 1.f, ImGui::GetColorU32( color ), shadow_tickness, ImVec2( 0, 0 ), 1.f );
ImGui::PopClipRect( );
ImGui::PopStyleVar( );
}
inline void ToolTip( const char * Label, const char * Desc, const char * Icon, bool State ) {
bool Hovered = State;
ImVec2 Pos = ImGui::GetMousePos( ) + ImVec2( 20, 0 );
auto DrawList = ImGui::GetForegroundDrawList( );
float Padding = 12;
float Rounding = 4;
float Spacing = 6;
struct ToolTip_t {
ImVec4 BackGroundColor = ImColor( 20, 20, 22 );
ImVec4 TextColor = ImColor( 200, 200, 200, 0 );
ImVec4 IconColor = ImColor( 245, 158, 66, 0 );
float GlobalAlpha = 0.f;
float SlideX = 0.f;
};
static std::map<std::string, ToolTip_t> anim;
std::string a1 = std::string( Label ) + std::string( Desc );
auto ToolTipAnim = anim.find( a1 );
if ( ToolTipAnim == anim.end( ) ) {
anim.insert( { a1, ToolTip_t( ) } );
}
ImVec2 TextSize = Utils::CalcTextSize( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, Desc );
ImVec2 IconTextSize = Utils::CalcTextSize( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize, Icon );
ToolTipAnim->second.GlobalAlpha = ImLerp( ToolTipAnim->second.GlobalAlpha, Hovered ? 1.f : 0.f, ImGui::GetIO( ).DeltaTime * 8 );
ToolTipAnim->second.SlideX = ImLerp( ToolTipAnim->second.SlideX, Hovered ? ( IconTextSize.x + TextSize.x + Padding + Spacing ) : 0.f, ImGui::GetIO( ).DeltaTime * 8 );
ToolTipAnim->second.TextColor = ImLerp( ToolTipAnim->second.TextColor, Hovered ? ImColor( 180, 180, 180 ) : ImColor( 180, 180, 180, 0 ), ImGui::GetIO( ).DeltaTime * 12 );
ToolTipAnim->second.IconColor = ImLerp( ToolTipAnim->second.IconColor, Hovered ? ImVec4( g_Col.Base ) : ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.f / 255.f ), ImGui::GetIO( ).DeltaTime * 8 );
ImGui::PushStyleVar( ImGuiStyleVar_Alpha, ToolTipAnim->second.GlobalAlpha );
ImVec2 RectEndPos = ImVec2( Pos.x + ToolTipAnim->second.SlideX, Pos.y + TextSize.y + Padding );
DrawList->AddRectFilled( Pos, RectEndPos, ImGui::GetColorU32( ImVec4( ImColor( 16, 16, 18 ) ) ), Rounding );
DrawList->AddRect( Pos, RectEndPos, ImGui::GetColorU32( ImVec4( ImColor( 22, 22, 24 ) ) ), Rounding );
DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize, ImVec2( Pos.x + Padding / 2, Pos.y + ( ( TextSize.y + Padding ) / 2 - IconTextSize.y / 2 ) ), ImGui::GetColorU32( ToolTipAnim->second.IconColor ), Icon );
if ( ToolTipAnim->second.SlideX < TextSize.x + Padding ) {
std::string ClippedDesc = Desc;
while ( ImGui::CalcTextSize( ClippedDesc.c_str( ) ).x > ToolTipAnim->second.SlideX - Padding && !ClippedDesc.empty( ) ) {
ClippedDesc.pop_back( );
}
DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, ImVec2( Pos.x + Padding / 2 + ( IconTextSize.x + Spacing ), Pos.y + Padding / 2 ), ImGui::GetColorU32( ToolTipAnim->second.TextColor ), ClippedDesc.c_str( ) );
}
else {
DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, ImVec2( Pos.x + Padding / 2 + ( IconTextSize.x + Spacing ), Pos.y + Padding / 2 ), ImGui::GetColorU32( ToolTipAnim->second.TextColor ), Desc );
}
ImGui::PopStyleVar( );
}
inline bool CheckBox(const char* Label, bool* Checked, bool bToolTip = false, const char* ToolTipMsg = "", const char* ToolTipIcon = "") {
ImGuiWindow* Window = ImGui::GetCurrentWindow();
if (Window->SkipItems || !Window->Active || Window->Hidden)
return false;
ImGuiContext& g = *GImGui;
const ImGuiStyle& style = g.Style;
std::string UniqueID = std::string(Label) + std::to_string((int)Checked);
const ImGuiID id = Window->GetID(UniqueID.c_str());
const float square_sz = 12;
const ImVec2 label_size = ImGui::CalcTextSize(Label, NULL, true);
const float w = ImGui::GetContentRegionMax().x - style.WindowPadding.x * 2;
const ImVec2 pos = Window->DC.CursorPos + ImVec2(-5, 0);
const ImRect total_bb(pos, pos + ImVec2(square_sz + w, label_size.y));
ImGui::ItemSize(total_bb, 0.f);
if (!ImGui::ItemAdd(total_bb, id)) {
IMGUI_TEST_ENGINE_ITEM_INFO(id, Label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*Checked ? ImGuiItemStatusFlags_Checked : 0));
return false;
}
bool Hovered, Held;
bool Pressed = ImGui::ButtonBehavior(total_bb, id, &Hovered, &Held);
if (Pressed) {
*Checked = !(*Checked);
ImGui::MarkItemEdited(id);
}
struct checkbox_state {
ImVec4 background, circle, text;
float slow_circle;
};
static std::map<ImGuiID, checkbox_state> anim;
auto it_anim = anim.find(id);
if (it_anim == anim.end()) {
anim.insert({ id, checkbox_state() });
it_anim = anim.find(id);
it_anim->second.background = *Checked ? ImVec4(1.00f, 1.00f, 1.00f, 1.00f) : ImVec4(18 / 255.0f, 18 / 255.0f, 18 / 255.0f, 1.00f);
it_anim->second.circle = *Checked ? ImVec4(0.00f, 0.00f, 0.00f, 1.00f) : ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
it_anim->second.text = *Checked ? ImVec4(1.00f, 1.00f, 1.00f, 1.00f) : ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
it_anim->second.slow_circle = *Checked ? -13.f : 0.f;
}
const ImVec4 c_accent_color = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
const ImVec4 c_circle_inactive = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
const ImVec4 c_checkbox_active = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
const ImVec4 c_checkbox_inactive = ImVec4(18 / 255.0f, 18 / 255.0f, 18 / 255.0f, 1.00f);
const ImVec4 c_text_active = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
const ImVec4 c_text_hov = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
const ImVec4 c_text = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
it_anim->second.circle = ImLerp(it_anim->second.circle, *Checked ? c_accent_color : c_circle_inactive, g.IO.DeltaTime * 6.f);
it_anim->second.background = ImLerp(it_anim->second.background, *Checked ? c_checkbox_active : c_checkbox_inactive, g.IO.DeltaTime * 6.f);
it_anim->second.text = ImLerp(it_anim->second.text, *Checked ? c_text_active : Hovered ? c_text_hov : c_text, g.IO.DeltaTime * 6.f);
it_anim->second.slow_circle = ImLerp(it_anim->second.slow_circle, *Checked ? -13.f : 0.f, g.IO.DeltaTime * 6.f);
const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
Window->DrawList->AddRectFilled(
check_bb.Min + ImVec2((w - 9), 0),
check_bb.Max + ImVec2(w + 11, 7.5f),
ImGui::GetColorU32(it_anim->second.background),
100
);
Window->DrawList->AddRect(
check_bb.Min + ImVec2((w - 9), 0),
check_bb.Max + ImVec2(w + 11, 7.5f),
ImGui::GetColorU32(ImVec4(0.12f, 0.12f, 0.12f, 1.00f)),
100
);
Window->DrawList->AddCircleFilled(
check_bb.Min + ImVec2((w + 1 - it_anim->second.slow_circle), 9.5f),
5.5f,
ImGui::GetColorU32(it_anim->second.circle)
);
Window->DrawList->AddText(
ImVec2(check_bb.Max.x - square_sz + 5, check_bb.Min.y + 3.5f),
ImGui::GetColorU32(it_anim->second.text),
Label
);
if (bToolTip && Hovered && g_MenuInfo.IsOpen && ImGui::GetStyle().Alpha > 0.01f) {
ImGui::SetTooltip("%s", ToolTipMsg);
}
IMGUI_TEST_ENGINE_ITEM_INFO(id, Label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*Checked ? ImGuiItemStatusFlags_Checked : 0));
return Pressed;
}
inline bool CheckBoxCfg(const char* Label, bool* Checked, std::function<void()> Components, bool bToolTip = false, const char* ToolTipMsg = "", const char* ToolTipIcon = "") {
ImGuiWindow* Window = ImGui::GetCurrentWindow();
if (Window->SkipItems)
return false;
ImGuiContext& g = *GImGui;
const ImGuiStyle& style = g.Style;
std::string UniqueID = std::string(Label) + std::to_string((int)Checked);
const ImGuiID id = Window->GetID(UniqueID.c_str());
const float CheckBoxSizeVal = 22.f;
const ImVec2 CheckBoxSize(CheckBoxSizeVal, CheckBoxSizeVal);
const float IconSize = 16.f;
const float IconSpacing = 6.f;
ImVec2 TextSize = ImGui::CalcTextSize(Label);
float TotalWidth = ImGui::GetContentRegionAvail().x;
float RightBlockWidth = CheckBoxSize.x +
(bToolTip ? IconSize + IconSpacing : 0) +
(Components ? IconSize + IconSpacing : 0);
ImVec2 Pos = Window->DC.CursorPos;
ImVec2 LabelPos = Pos;
ImVec2 CheckBoxPos = ImVec2(Pos.x + TotalWidth - CheckBoxSize.x, Pos.y);
ImVec2 GearPos = ImVec2(CheckBoxPos.x - IconSpacing - IconSize, Pos.y + (CheckBoxSize.y - IconSize) / 2);
ImVec2 WarnPos = ImVec2(GearPos.x - IconSpacing - IconSize, Pos.y + (CheckBoxSize.y - IconSize) / 2);
const ImRect Rect(CheckBoxPos, CheckBoxPos + CheckBoxSize);
const ImRect Clickable = Rect;
ImGui::ItemSize(Rect, style.FramePadding.y);
if (!ImGui::ItemAdd(Rect, id, &Clickable)) {
IMGUI_TEST_ENGINE_ITEM_INFO(id, Label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*Checked ? ImGuiItemStatusFlags_Checked : 0));
return false;
}
bool Hovered, Held;
bool Pressed = ImGui::ButtonBehavior(Clickable, id, &Hovered, &Held);
if (Pressed) {
*Checked = !(*Checked);
ImGui::MarkItemEdited(id);
}
struct WidCheckBox_t {
ImVec4 BackGroundColor = ImColor(18, 18, 20);
ImVec4 UnCheckedBackGroundColor = ImColor(18, 18, 20);
ImVec4 CheckColor = ImColor(18, 18, 20);
ImVec4 LabelColor = g_Col.SecundaryText;
ImVec2 BackGroundSize = ImVec2(0, 0);
float CheckUp = 0.f;
float AnimKeyBind = 0.f;
float PopupAlpha = 0.f;
float SlideX = 0.f;
ImVec4 IconColor = ImColor(245, 158, 66, 0);
float GearRotation = 0.f;
bool PopupActive = false;
};
static std::map<ImGuiID, WidCheckBox_t> anim;
auto& animRef = anim[id];
animRef.LabelColor = ImLerp(animRef.LabelColor, *Checked ? ImColor(g_Col.FeaturesText) : ImColor(g_Col.SecundaryFeaturesText), g.IO.DeltaTime * 8.f);
animRef.BackGroundColor = ImLerp(animRef.BackGroundColor, *Checked ? ImColor(g_Col.Base) : Hovered ? ImColor(20, 20, 22) : ImColor(18, 18, 20), g.IO.DeltaTime * 10.f);
animRef.UnCheckedBackGroundColor = ImLerp(animRef.UnCheckedBackGroundColor, Hovered ? ImColor(20, 20, 22) : ImColor(18, 18, 20), g.IO.DeltaTime * 6.f);
animRef.BackGroundSize = ImLerp(animRef.BackGroundSize, (*Checked) ? ImVec2(CheckBoxSize / 2) : ImVec2(0, 0), g.IO.DeltaTime * 8.f);
if (animRef.BackGroundSize.x > (CheckBoxSize.x / 2) - 2.f && (*Checked)) {
animRef.CheckColor = ImLerp(animRef.CheckColor, ImColor(21, 21, 23, 255), g.IO.DeltaTime * 14.f);
animRef.CheckUp = ImLerp(animRef.CheckUp, CheckBoxSize.x / 4, g.IO.DeltaTime * 6.f);
}
else {
animRef.CheckColor = ImLerp(animRef.CheckColor, ImColor(21, 21, 23, 0), g.IO.DeltaTime * 14.f);
animRef.CheckUp = ImLerp(animRef.CheckUp, 0.f, g.IO.DeltaTime * 6.f);
}
Window->DrawList->AddText(LabelPos, ImGui::GetColorU32(animRef.LabelColor), Label);
ImVec2 CheckBoxCenter = CheckBoxPos + CheckBoxSize / 2;
Window->DrawList->AddRectFilled(CheckBoxPos, CheckBoxPos + CheckBoxSize, ImGui::GetColorU32(animRef.UnCheckedBackGroundColor), 80.f);
Window->DrawList->AddRectFilled(CheckBoxCenter - animRef.BackGroundSize, CheckBoxCenter + animRef.BackGroundSize, ImGui::GetColorU32(animRef.BackGroundColor), 80.f);
ImGui::RenderCheckMark(Window->DrawList, ImVec2(CheckBoxPos.x + CheckBoxSize.x / 4, CheckBoxPos.y + CheckBoxSize.x / 2 - animRef.CheckUp), ImGui::GetColorU32(animRef.CheckColor), CheckBoxSize.x / 2);
if (bToolTip && g_MenuInfo.IsOpen && ImGui::GetStyle().Alpha > 0.0f) {
ImColor color = ImColor(245, 158, 66, static_cast<int>(ImGui::GetStyle().Alpha * 255.0f));
Window->DrawList->AddText(g_Variables.FontAwesomeSolid, IconSize, WarnPos, color, ICON_FA_TRIANGLE_EXCLAMATION);
if (Hovered && g_MenuInfo.IsOpen)
ToolTip(Label, ToolTipMsg, ToolTipIcon, true);
}
if (*Checked) {
ImVec4 glowColor = animRef.BackGroundColor;
glowColor.w = 0.3f;
Window->DrawList->AddCircleFilled(
CheckBoxCenter,
CheckBoxSize.x * 0.7f,
ImGui::GetColorU32(glowColor),
48
);
}
static bool IconHovered = false;
ImVec2 MousePos = ImGui::GetMousePos();
ImVec2 IconTextSize = Utils::CalcTextSize(g_Variables.FontAwesomeSolid, IconSize, ICON_FA_GEAR);
ImVec2 GearIconMax = GearPos + IconTextSize;
IconHovered = MousePos.x > GearPos.x && MousePos.x < GearIconMax.x &&
MousePos.y > GearPos.y && MousePos.y < GearIconMax.y;
if (IconHovered && g.IO.MouseClicked[0]) {
animRef.PopupActive = !animRef.PopupActive;
}
else if (!IconHovered && g.IO.MouseClicked[0] && animRef.PopupActive) {
ImVec2 PopupSize(180, 90);
ImVec2 PopupMin = GearPos + ImVec2(0, IconSize + 4);
if (!(MousePos.x > PopupMin.x && MousePos.x < PopupMin.x + PopupSize.x &&
MousePos.y > PopupMin.y && MousePos.y < PopupMin.y + PopupSize.y)) {
animRef.PopupActive = false;
}
}
animRef.GearRotation = ImLerp(animRef.GearRotation, animRef.PopupActive ? 1.f : -1.f, g.IO.DeltaTime * 10.f);
animRef.IconColor = ImLerp(animRef.IconColor, animRef.PopupActive ? ImColor(g_Col.Base) : ImColor(60, 60, 60), g.IO.DeltaTime * 10.f);
ImRotateStart();
Window->DrawList->AddText(g_Variables.FontAwesomeSolid, IconSize, GearPos, ImGui::GetColorU32(animRef.IconColor), ICON_FA_GEAR);
ImRotateEnd(1.57f * animRef.GearRotation);
animRef.PopupAlpha = ImClamp(animRef.PopupAlpha + (6.f * g.IO.DeltaTime * (animRef.PopupActive && g_MenuInfo.IsOpen ? 1.f : -1.f)), 0.f, 1.f);
if (animRef.PopupAlpha >= 0.001f) {
PushStyleVar(ImGuiStyleVar_Alpha, animRef.PopupAlpha);
PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(10, 10));
PushStyleVar(ImGuiStyleVar_WindowRounding, 4.f);
PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(15, 15));
PushStyleVar(ImGuiStyleVar_PopupBorderSize, 1);
PushStyleColor(ImGuiCol_Border, GetColorU32(ImVec4(ImColor(20, 20, 22))));
PushStyleColor(ImGuiCol_PopupBg, GetColorU32(ImVec4(ImColor(14, 14, 16))));
ImVec2 PopupSize(180, 90);
ImVec2 PopupMin = GearPos + ImVec2(0, IconSize + 4);
SetNextWindowSize(PopupSize);
SetNextWindowPos(PopupMin);
Begin(Label, NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_WithoutScrollClamp | ImGuiWindowFlags_Tooltip);
{
PopupSize = ImGui::GetWindowSize();
Components();
}
PopStyleVar(7);
PopStyleColor(2);
End();
}
if (g_MenuInfo.IsOpen) {
float lineOffset = 6.0f;
float lineY = Rect.Max.y + lineOffset;
float contentMinX = Window->Pos.x + ImGui::GetWindowContentRegionMin().x;
float contentMaxX = Window->Pos.x + ImGui::GetWindowContentRegionMax().x;
}
IMGUI_TEST_ENGINE_ITEM_INFO(id, Label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*Checked ? ImGuiItemStatusFlags_Checked : 0));
return Pressed;
}
inline bool CfgButton( const char * Label, std::function<void( )> Components )
{
ImGuiWindow * Window = ImGui::GetCurrentWindow( );
if ( Window->SkipItems )
return false;
ImGuiContext & g = *GImGui;
const ImGuiStyle & style = g.Style;
std::string IdStr = ( std::string ) Label;
const ImGuiID id = Window->GetID( IdStr.c_str( ) );
ImVec2 IconTextSize = Utils::CalcTextSize( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize - 4, ICON_FA_GEAR );
ImVec2 MousePos = ImGui::GetMousePos( );
const ImVec2 Pos = Window->DC.CursorPos;
const ImRect Rect( Pos, Pos + ImVec2( IconTextSize.x, IconTextSize.y ) );
ImGui::ItemSize( Rect, style.FramePadding.y );
if ( !ImGui::ItemAdd( Rect, id ) ) {
return false;
}
bool Hovered, Held;
bool Pressed = ImGui::ButtonBehavior( Rect, id, &Hovered, &Held );
if ( Pressed ) {
ImGui::MarkItemEdited( id );
}
struct CfgBtn_t {
ImVec4 IconColor = ImColor( 245, 158, 66, 0 );
float GearRotation = 0.f;
float PopupAlpha = 0.f;
bool PopupActive = false;
};
static std::map<ImGuiID, CfgBtn_t> anim;
auto CfgAnim = anim.find( id );
if ( CfgAnim == anim.end( ) )
{
anim.insert( { id, CfgBtn_t( ) } );
CfgAnim = anim.find( id );
}
static ImVec2 PopupSize( 180, 90 );
ImVec2 PopupMin = Pos + ImVec2( IconTextSize.x + 4, IconTextSize.y + 4 );
if ( Hovered && g.IO.MouseClicked[ 0 ] ) {
CfgAnim->second.PopupActive = !CfgAnim->second.PopupActive;
}
else if ( !Hovered && g.IO.MouseClicked[ 0 ] && CfgAnim->second.PopupActive ) {
if ( !( MousePos.x > PopupMin.x && MousePos.x < PopupMin.x + PopupSize.x && MousePos.y > PopupMin.y && MousePos.y < PopupMin.y + PopupSize.y ) ) {
CfgAnim->second.PopupActive = false;
}
}
CfgAnim->second.GearRotation = ImLerp( CfgAnim->second.GearRotation, CfgAnim->second.PopupActive ? 1.f : -1.f, g.IO.DeltaTime * 10.f );
CfgAnim->second.IconColor = ImLerp( CfgAnim->second.IconColor, CfgAnim->second.PopupActive ? ImColor( g_Col.Base ) : ImColor( 60, 60, 60 ), g.IO.DeltaTime * 10.f );
ImRotateStart( );
Window->DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize - 4, Pos, ImGui::GetColorU32( CfgAnim->second.IconColor ), ICON_FA_GEAR );
ImRotateEnd( 1.57f * CfgAnim->second.GearRotation );
CfgAnim->second.PopupAlpha = ImClamp( CfgAnim->second.PopupAlpha + ( 6.f * g.IO.DeltaTime * ( CfgAnim->second.PopupActive && g_MenuInfo.IsOpen ? 1.f : -1.f ) ), 0.f, 1.f );
if ( CfgAnim->second.PopupAlpha >= 0.001f ) {
PushStyleVar( ImGuiStyleVar_Alpha, CfgAnim->second.PopupAlpha );
PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 10, 10 ) );
PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( 10, 10 ) );
PushStyleVar( ImGuiStyleVar_CellPadding, ImVec2( 10, 10 ) );
PushStyleVar( ImGuiStyleVar_WindowRounding, 4.f );
PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 15, 15 ) );
PushStyleVar( ImGuiStyleVar_PopupBorderSize, 1 );
PushStyleColor( ImGuiCol_Border, GetColorU32( ImVec4( ImColor( 20, 20, 22 ) ) ) );
PushStyleColor( ImGuiCol_PopupBg, GetColorU32( ImVec4( ImColor( 14, 14, 16 ) ) ) );
SetNextWindowSize( ImVec2( PopupSize.x, 0 ) );
SetNextWindowPos( PopupMin );
Begin( Label, NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_WithoutScrollClamp | ImGuiWindowFlags_Tooltip );
{
PopupSize = ImGui::GetWindowSize( );
Components( );
}
PopStyleVar( 7 );
PopStyleColor( 2 );
End( );
}
}
inline bool CheckBoxPage( const char * Label, bool * Checked, std::function<void( )> Code, bool bToolTip = false, const char * ToolTipMsg = "" ) {
ImGuiWindow * Window = ImGui::GetCurrentWindow( );
if ( Window->SkipItems )
return false;
ImGuiContext & g = *GImGui;
const ImGuiStyle & style = g.Style;
std::string UniqueID = ( std::string ) Label + std::to_string( ( int ) Checked );
const ImGuiID id = Window->GetID( UniqueID.c_str( ) );
float Width = ImGui::GetWindowContentRegionMax( ).x - ImGui::GetWindowContentRegionMin( ).x - ( Window->ScrollbarY ? 5.f : 0.f );
ImVec2 TextSize = ImGui::CalcTextSize( Label );
const ImVec2 CheckBoxSize( 22, 22 );
const ImVec2 Pos = Window->DC.CursorPos;
const ImRect Rect( Pos, Pos + ImVec2( Width, CheckBoxSize.y - 4 ) );
const ImRect Clickable( Pos, Pos + ImVec2( CheckBoxSize.x + TextSize.x + 8, CheckBoxSize.y ) );
ImGui::ItemSize( Rect, style.FramePadding.y );
if ( !ImGui::ItemAdd( Rect, id, &Clickable ) ) {
IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | ( *v ? ImGuiItemStatusFlags_Checked : 0 ) );
return false;
}
bool Hovered, Held;
bool Pressed = ImGui::ButtonBehavior( Clickable, id, &Hovered, &Held );
if ( Pressed ) {
*Checked = !( *Checked );
ImGui::MarkItemEdited( id );
}
struct WidCheckBox_t {
ImVec4 BackGroundColor = ImColor( 18, 18, 20 );
ImVec4 UnCheckedBackGroundColor = ImColor( 18, 18, 20 );
ImVec4 CheckColor = ImColor( 18, 18, 20 );
ImVec4 LabelColor = g_Col.SecundaryText;
ImVec2 BackGroundSize = ImVec2( 0, 0 );
float CheckUp = 0.f;
float AnimKeyBind = 0.f;
float SlideUp = 0.f;
ImVec4 IconColor = ImColor( 245, 158, 66, 0 );
};
static std::map<ImGuiID, WidCheckBox_t> anim;
auto CheckBoxAnim = anim.find( id );
if ( CheckBoxAnim == anim.end( ) )
{
anim.insert( { id, WidCheckBox_t( ) } );
CheckBoxAnim = anim.find( id );
}
CheckBoxAnim->second.LabelColor = ImLerp( CheckBoxAnim->second.LabelColor, *Checked ? ImColor( g_Col.FeaturesText ) : ImColor( g_Col.SecundaryFeaturesText ), g.IO.DeltaTime * 8.f );
CheckBoxAnim->second.BackGroundColor = ImLerp( CheckBoxAnim->second.BackGroundColor, *Checked ? ImColor( g_Col.Base ) : Hovered ? ImColor( 20, 20, 22 ) : ImColor( 18, 18, 20 ), g.IO.DeltaTime * 10.f );
CheckBoxAnim->second.UnCheckedBackGroundColor = ImLerp( CheckBoxAnim->second.UnCheckedBackGroundColor, Hovered ? ImColor( 20, 20, 22 ) : ImColor( 18, 18, 20 ), g.IO.DeltaTime * 6.f );
CheckBoxAnim->second.BackGroundSize = ImLerp( CheckBoxAnim->second.BackGroundSize, ( *Checked ) ? ImVec2( CheckBoxSize / 2 ) : ImVec2( 0, 0 ), g.IO.DeltaTime * 8.f );
if ( CheckBoxAnim->second.BackGroundSize.x > ( CheckBoxSize.x / 2 ) - 2.f && ( *Checked ) ) {
CheckBoxAnim->second.CheckColor = ImLerp( CheckBoxAnim->second.CheckColor, ImColor( 21, 21, 23, 255 ), g.IO.DeltaTime * 14.f );
CheckBoxAnim->second.CheckUp = ImLerp( CheckBoxAnim->second.CheckUp, CheckBoxSize.x / 4, g.IO.DeltaTime * 6.f );
}
else {
CheckBoxAnim->second.CheckColor = ImLerp( CheckBoxAnim->second.CheckColor, ImColor( 21, 21, 23, 0 ), g.IO.DeltaTime * 14.f );
CheckBoxAnim->second.CheckUp = ImLerp( CheckBoxAnim->second.CheckUp, 0.f, g.IO.DeltaTime * 6.f );
}
ImVec2 CheckBoxCenter( Rect.Min + CheckBoxSize / 2 );
Window->DrawList->AddRectFilled( Rect.Min, Rect.Min + CheckBoxSize, ImGui::GetColorU32( CheckBoxAnim->second.UnCheckedBackGroundColor ), 4.f );
Window->DrawList->AddRect( Rect.Min, Rect.Min + CheckBoxSize, ImGui::GetColorU32( ImVec4( ImColor( 24, 24, 26 ) ) ), 4.f );
Window->DrawList->AddRectFilled( CheckBoxCenter - CheckBoxAnim->second.BackGroundSize, CheckBoxCenter + CheckBoxAnim->second.BackGroundSize, ImGui::GetColorU32( CheckBoxAnim->second.BackGroundColor ), 4.f );
ImGui::RenderCheckMark( Window->DrawList, ImVec2( Pos.x + CheckBoxSize.x / 4, Pos.y + CheckBoxSize.x / 2 - CheckBoxAnim->second.CheckUp ), ImGui::GetColorU32( CheckBoxAnim->second.CheckColor ), CheckBoxSize.x / 2 );
ImVec2 TextPos = ImVec2( Rect.Min.x + CheckBoxSize.x + 8.f, Pos.y + Rect.Max.y / 2 - ( Pos.y + TextSize.y ) / 2 );
Window->DrawList->AddText( TextPos, ImGui::GetColorU32( CheckBoxAnim->second.LabelColor ), Label );
static bool IconHovered = false;
ImVec2 IconTextSize = Utils::CalcTextSize( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize - 4, ICON_FA_SHARE );
ImVec2 MousePos = ImGui::GetMousePos( );
ImVec2 MinPos = TextPos + ImVec2( TextSize.x, ( CheckBoxSize.y / 2 - TextSize.y / 2 ) - 4 );
ImVec2 MaxPos = TextPos + ImVec2( TextSize.x + ( 10 * 2 ) + IconTextSize.x, ( MinPos.y - TextPos.y ) + IconTextSize.y + 4 );
if ( MousePos.x > MinPos.x && MousePos.x < MaxPos.x && MousePos.y > MinPos.y && MousePos.y < MaxPos.y ) {
IconHovered = true;
}
else {
IconHovered = false;
}
if ( bToolTip ) {
ToolTip( Label, ToolTipMsg, ICON_FA_SHARE, IconHovered && g_MenuInfo.IsOpen );
}
CheckBoxAnim->second.SlideUp = ImLerp( CheckBoxAnim->second.SlideUp, IconHovered ? 2.f : 0.f,
g.IO.DeltaTime * 10.f );
CheckBoxAnim->second.IconColor = ImLerp( CheckBoxAnim->second.IconColor, IconHovered
? ImColor( g_Col.Base ) : ImColor( 60, 60, 60 ), g.IO.DeltaTime * 10.f );
Window->DrawList->AddText( g_Variables.FontAwesomeSolid, g_Variables.FontAwesomeSolid->FontSize - 4
, TextPos + ImVec2( TextSize.x + 10, ( CheckBoxSize.y / 2 - TextSize.y / 2 ) - CheckBoxAnim->second.SlideUp ),
ImGui::GetColorU32( CheckBoxAnim->second.IconColor ), ICON_FA_SHARE );
if ( IconHovered && g.IO.MouseClicked[ 0 ] ) {
Code( );
}
IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | ( *Checked ? ImGuiItemStatusFlags_Checked : 0 ) );
return Pressed;
}
inline void TextCentered( const char * text, int m ) {
ImVec2 textSize = ImGui::CalcTextSize( text );
float posX = ( g_MenuInfo.MenuSize.x  -textSize.x ) * 0.5f;
float posY = ( g_MenuInfo.MenuSize.y - textSize.y ) * 0.5f;
switch ( m ) {
case 0:
ImGui::SetCursorPos( { posX, posY } );
ImGui::Text( text );
break;
case 1:
ImGui::SetCursorPosX( posX );
ImGui::Text( text );
break;
case 2:
ImGui::SetCursorPosY( posY );
ImGui::Text( text );
break;
default:
ImGui::SetCursorPos( { posX, posY } );
ImGui::Text( text );
break;
}
}
inline bool ButtonIJ(const char* icon, const ImVec2& size_arg, ImGuiButtonFlags flags, bool bToolTip = false, const char* ToolTipMsg = "", const char* ToolTipIcon = "")
{
struct button13Anims {
float closing_anim;
float closing_alpha;
float label_alpha;
bool animation_complete;
};
ImGuiWindow* window = ImGui::GetCurrentWindow();
if (window->SkipItems)
return false;
ImGuiContext& g = *ImGui::GetCurrentContext();
const ImGuiStyle& style = g.Style;
const ImGuiID id = window->GetID(icon);
ImDrawList* draw = window->DrawList;
static std::map<ImGuiID, button13Anims> anim;
auto it_anim = anim.find(id);
if (it_anim == anim.end()) {
anim.insert({ id, button13Anims() });
it_anim = anim.find(id);
}
ImVec2 pos = window->DC.CursorPos;
ImVec2 size = ImGui::CalcItemSize(size_arg, size_arg.x, size_arg.y);
const ImRect bb(pos, pos + size);
ImGui::ItemSize(size, style.FramePadding.y);
if (!ImGui::ItemAdd(bb, id))
return false;
if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
flags |= ImGuiButtonFlags_Repeat;
bool hovered, held;
bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);
if (bToolTip) {
ToolTip(icon, ToolTipMsg, ToolTipIcon, hovered && g_MenuInfo.IsOpen);
}
it_anim->second.closing_anim = ImLerp(it_anim->second.closing_anim, (hovered ? size.y : 0.0f), g.IO.DeltaTime * 8.f);
if (hovered || pressed) {
if (it_anim->second.label_alpha < 255.f)
it_anim->second.label_alpha += 5.f / g.IO.Framerate * 160.f;
if (it_anim->second.closing_alpha < 255.f)
it_anim->second.closing_alpha += 15.f / g.IO.Framerate * 160.f;
}
else {
if (it_anim->second.label_alpha > 0.f)
it_anim->second.label_alpha -= 5.f / g.IO.Framerate * 160.f;
if (it_anim->second.closing_alpha > 0.f)
it_anim->second.closing_alpha -= 10.f / g.IO.Framerate * 160.f;
}
const ImVec2 center = bb.GetCenter();
const float shadow_radius = size.x * 0.6f;
ImU32 shadow_color = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 0.20f));
draw->AddCircleFilled(center, shadow_radius, shadow_color, 64);
const ImU32 inside_solid_col = ImGui::GetColorU32(ImVec4(ImColor(255, 255, 255)));
draw->AddRectFilled(bb.Min, bb.Max, inside_solid_col, 150);
ImFont* iconFont = g_Variables.FontAwesomeSolid;
if (!iconFont) iconFont = ImGui::GetFont();
ImVec2 iconTextSize = Utils::CalcTextSize(iconFont, iconFont->FontSize, icon);
ImVec2 iconPos = ImVec2(
bb.Min.x + (bb.GetWidth() - iconTextSize.x) * 0.5f,
bb.Min.y + (bb.GetHeight() - iconTextSize.y) * 0.5f
);
draw->AddText(iconFont, iconFont->FontSize, iconPos, IM_COL32(0, 0, 0, 255), icon);
return pressed;
}
inline bool ButtonWithIcon( const char * icon, const char * label, const ImVec2 & size_arg, ImGuiButtonFlags flags ) {
struct button_struct {
ImVec4 BorderCol;
ImVec4 background;
ImVec4 LabelColor;
float UpBackground;
};
ImGuiWindow * window = ImGui::GetCurrentWindow( );
if ( window->SkipItems )
return false;
ImGuiContext & g = *GImGui;
const ImGuiStyle & style = g.Style;
const ImGuiID id = window->GetID( label );
const ImVec2 label_size = g_Variables.m_FontNormal->CalcTextSizeA( g_Variables.m_FontNormal->FontSize, FLT_MAX, 0, label );
const ImVec2 IconTextSize = g_Variables.FontAwesomeSolid->CalcTextSizeA( g_Variables.FontAwesomeSolid->FontSize - 4, FLT_MAX, 0, icon );
const ImVec2 pos = window->DC.CursorPos;
static std::map<ImGuiID, button_struct> anim;
auto it_anim = anim.find( id );
if ( it_anim == anim.end( ) ) {
anim.insert( { id, button_struct( ) } );
it_anim = anim.find( id );
}
ImVec2 size = ImGui::CalcItemSize( size_arg, label_size.x + IconTextSize.x + style.FramePadding.x * 3.0f, label_size.y + style.FramePadding.y * 2.0f );
const ImRect bb( pos, ImVec2( pos.x + size.x, pos.y + size.y ) );
ImGui::ItemSize( size, 0.f );
if ( !ImGui::ItemAdd( bb, id ) )
return false;
bool Hovered, Held, Pressed = ImGui::ButtonBehavior( bb, id, &Hovered, &Held, flags );
it_anim->second.BorderCol = ImLerp( it_anim->second.BorderCol, Hovered ? ImVec4( g_Col.Base ) : ImVec4( ImColor( 18, 18, 20 ) ), g.IO.DeltaTime * 6.f );
it_anim->second.background = ImLerp( it_anim->second.background, Hovered ? ImVec4( ImColor( 14, 14, 16 ) ) : ImVec4( ImColor( 14, 14, 16 ) ), g.IO.DeltaTime * 6.f );
it_anim->second.LabelColor = ImLerp( it_anim->second.LabelColor, Hovered ? ImVec4( ImColor( 225, 225, 225 ) ) : ImVec4( ImColor( 225, 225, 225 ) ), g.IO.DeltaTime * 6.f );
it_anim->second.UpBackground = ImLerp( it_anim->second.UpBackground, Hovered ? ( bb.Min.y - pos.y ) - ( bb.Max.y - pos.y ) : 0.f, g.IO.DeltaTime * 6.f );
float totalWidth = label_size.x + IconTextSize.x + style.FramePadding.x;
ImVec2 TextPos = { pos.x + ( size.x - totalWidth ) * 0.5f + IconTextSize.x + style.FramePadding.x, pos.y + ( size.y - label_size.y ) * 0.5f - 0.5f };
ImVec2 TextWithoutIconPos = { pos.x + ( size.x - label_size.x ) * 0.5f + style.FramePadding.x, pos.y + ( size.y - label_size.y ) * 0.5f - 0.5f };
ImVec2 IconPos = { pos.x + ( size.x - totalWidth ) * 0.5f, pos.y + ( size.y - IconTextSize.y ) * 0.5f - 0.5f };
window->DrawList->AddRectFilled( bb.Min, bb.Max, ImGui::GetColorU32( it_anim->second.background ), 4 );
window->DrawList->AddRect( bb.Min, bb.Max, ImGui::GetColorU32( it_anim->second.BorderCol ), 4 );
window->DrawList->AddRectFilled( ImVec2( bb.Min.x, bb.Max.y ), ImVec2( bb.Max.x, bb.Max.y + it_anim->second.UpBackground ), ImGui::GetColorU32( g_Col.Base ), 4 );
window->DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, TextWithoutIconPos, ImGui::GetColorU32( it_anim->second.LabelColor ), label );
return Pressed;
}
inline bool Button( const char * label, const ImVec2 & size_arg, ImGuiButtonFlags flags, bool bToolTip = false, const char * ToolTipMsg = "", const char * ToolTipIcon = "" )
{
struct button13Anims {
float closing_anim;
float closing_alpha;
float label_alpha;
bool animation_complete;
};
ImGuiWindow * window = GetCurrentWindow( );
if ( window->SkipItems )
return false;
ImGuiContext & g = *GImGui;
const ImGuiStyle & style = g.Style;
const ImGuiID id = window->GetID( label );
const ImVec2 label_size = CalcTextSize( label, NULL, true );
ImDrawList * draw = GetWindowDrawList( );
static std::map<ImGuiID, button13Anims> anim;
auto it_anim = anim.find( id );
if ( it_anim == anim.end( ) )
{
anim.insert( { id, button13Anims( ) } );
it_anim = anim.find( id );
}
ImVec2 pos = window->DC.CursorPos;
if ( ( flags & ImGuiButtonFlags_AlignTextBaseLine ) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset )
pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
ImVec2 size = CalcItemSize( size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f );
const ImRect bb( pos, pos + size );
ItemSize( size, style.FramePadding.y );
if ( !ItemAdd( bb, id ) )
return false;
if ( g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat )
flags |= ImGuiButtonFlags_Repeat;
bool hovered, held;
bool pressed = ButtonBehavior( bb, id, &hovered, &held, flags );
if ( bToolTip ) {
ToolTip( label, ToolTipMsg, ToolTipIcon, hovered && g_MenuInfo.IsOpen );
}
it_anim->second.closing_anim = ImLerp( it_anim->second.closing_anim, ( hovered ? size.y : 0 ), g.IO.DeltaTime * 8.f );
if ( hovered || pressed ) {
if ( it_anim->second.label_alpha < 255.f )
it_anim->second.label_alpha += 5.f / GetIO( ).Framerate * 160.f;
if ( it_anim->second.closing_alpha < 255.f )
it_anim->second.closing_alpha += 15.f / GetIO( ).Framerate * 160.f;
}
else {
if ( it_anim->second.label_alpha > 0.f )
it_anim->second.label_alpha -= 5.f / GetIO( ).Framerate * 160.f;
if ( it_anim->second.closing_alpha > 0.f )
it_anim->second.closing_alpha -= 10.f / GetIO( ).Framerate * 160.f;
}
const ImU32 inside_solid_col = GetColorU32( ImVec4( ImColor(255, 255, 255, 20) ) );
const ImU32 inside_hover_col = GetColorU32( ImVec4( ImColor(255, 255, 255, ( int ) it_anim->second.closing_alpha ) ) );
draw->AddRectFilled( ImVec2( bb.Min.x, bb.Min.y ), ImVec2( bb.Max.x, bb.Max.y ), inside_solid_col, 6 );
draw->AddRectFilled( ImVec2( bb.Min.x, bb.Max.y - it_anim->second.closing_anim ), ImVec2( bb.Max.x, bb.Max.y ), inside_hover_col, 6 );
PushStyleColor( ImGuiCol_Text, ColorConvertFloat4ToU32( ImColor(255, 255, 255, 255 - ( int ) it_anim->second.label_alpha ) ) );
RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb );
PopStyleColor( );
PushStyleColor( ImGuiCol_Text, ColorConvertFloat4ToU32( ImColor( 0, 0, 0, ( int ) it_anim->second.label_alpha ) ) );
RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb );
PopStyleColor( );
IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );
return pressed;
}
inline bool ButtonHeld( const char * label, const ImVec2 & size_arg, ImGuiButtonFlags flags )
{
struct button13Anims {
float closing_anim;
float closing_alpha;
float label_alpha;
bool animation_complete;
};
ImGuiWindow * window = GetCurrentWindow( );
if ( window->SkipItems )
return false;
ImGuiContext & g = *GImGui;
const ImGuiStyle & style = g.Style;
const ImGuiID id = window->GetID( label );
const ImVec2 label_size = CalcTextSize( label, NULL, true );
ImDrawList * draw = GetWindowDrawList( );
static std::map<ImGuiID, button13Anims> anim;
auto it_anim = anim.find( id );
if ( it_anim == anim.end( ) )
{
anim.insert( { id, button13Anims( ) } );
it_anim = anim.find( id );
}
ImVec2 pos = window->DC.CursorPos;
if ( ( flags & ImGuiButtonFlags_AlignTextBaseLine ) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset )
pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
ImVec2 size = CalcItemSize( size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f );
const ImRect bb( pos, pos + size );
ItemSize( size, style.FramePadding.y );
if ( !ItemAdd( bb, id ) )
return false;
if ( g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat )
flags |= ImGuiButtonFlags_Repeat;
bool hovered, held;
bool pressed = ButtonBehavior( bb, id, &hovered, &held, flags );
it_anim->second.closing_anim = ImLerp( it_anim->second.closing_anim, ( held ? size.y : 0 ), g.IO.DeltaTime * 8.f );
if ( held || pressed ) {
if ( it_anim->second.label_alpha < 255.f )
it_anim->second.label_alpha += 5.f / GetIO( ).Framerate * 160.f;
if ( it_anim->second.closing_alpha < 255.f )
it_anim->second.closing_alpha += 15.f / GetIO( ).Framerate * 160.f;
}
else {
if ( it_anim->second.label_alpha > 0.f )
it_anim->second.label_alpha -= 5.f / GetIO( ).Framerate * 160.f;
if ( it_anim->second.closing_alpha > 0.f )
it_anim->second.closing_alpha -= 10.f / GetIO( ).Framerate * 160.f;
}
const ImU32 inside_solid_col = GetColorU32( ImVec4( ImColor( 16, 16, 18 ) ) );
const ImU32 outside_solid_col = GetColorU32( ImVec4( ImColor( 24, 24, 26 ) ) );
const ImU32 inside_hover_col = ImColor( 180, 180, 180, ( int ) it_anim->second.closing_alpha );
draw->AddRectFilled( ImVec2( bb.Min.x, bb.Min.y ), ImVec2( bb.Max.x, bb.Max.y ), inside_solid_col, 6 );
draw->AddRect( bb.Min, bb.Max, outside_solid_col, 6 );
draw->AddRectFilled( ImVec2( bb.Min.x, bb.Max.y - it_anim->second.closing_anim ), ImVec2( bb.Max.x, bb.Max.y ), inside_hover_col, 6 );
PushStyleColor( ImGuiCol_Text, ColorConvertFloat4ToU32( ImColor( 140, 140, 140, 255 - ( int ) it_anim->second.label_alpha ) ) );
RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb );
PopStyleColor( );
PushStyleColor( ImGuiCol_Text, ColorConvertFloat4ToU32( ImColor( 225, 225, 225, ( int ) it_anim->second.label_alpha ) ) );
RenderTextClipped( bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb );
PopStyleColor( );
IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );
bool completed = it_anim->second.closing_anim >= ( size.y - 1.f );
if ( completed && !it_anim->second.animation_complete ) {
it_anim->second.animation_complete = true;
return true;
}
if ( pressed ) {
it_anim->second.animation_complete = false;
}
return false;
}
inline bool PedButtonHeld( ImTextureID Icon, const char * label, ImGuiButtonFlags flags )
{
ImGuiWindow * window = GetCurrentWindow( );
if ( window->SkipItems )
return false;
ImGuiContext & g = *GImGui;
const ImGuiStyle & style = g.Style;
const ImVec2 LabelSize = Utils::CalcTextSize( g_Variables.m_FontSecundary, g_Variables.m_FontSecundary->FontSize, label );
const ImGuiID id = window->GetID( label );
ImDrawList * Draw = window->DrawList;
struct  PedButtonHeld_t {
ImVec4 ProgressCol = ImColor( );
ImVec4 ShadowProgressCol = ImColor( );
ImVec4 SlideCol = ImColor( );
float Alpha = 0.f;
float SlideX = 0.f;
float SlideXShadow = 0.f;
float IconSize = 0.f;
bool Completed = false;
};
static std::map<ImGuiID, PedButtonHeld_t> anim;
auto WeaponButtonAnim = anim.find( id );
if ( WeaponButtonAnim == anim.end( ) )
{
anim.insert( { id, PedButtonHeld_t( ) } );
WeaponButtonAnim = anim.find( id );
}
const float Width = 120;
const float Height = 150;
ImVec2 Pos = window->DC.CursorPos;
const ImRect Rect( Pos, Pos + ImVec2( Width, Height ) );
ItemSize( ImVec2( Width, Height ), style.FramePadding.y );
if ( !ItemAdd( Rect, id ) )
return false;
if ( g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat )
flags |= ImGuiButtonFlags_Repeat;
bool Hovered, Held;
bool Pressed = ButtonBehavior( Rect, id, &Hovered, &Held, flags );
bool Condition = WeaponButtonAnim->second.Completed ? false : Held;
WeaponButtonAnim->second.Alpha = ImLerp( WeaponButtonAnim->second.Alpha, Condition ? 0.8f : Hovered ? 1.f : 0.6f, g.IO.DeltaTime * 8.f );
WeaponButtonAnim->second.IconSize = ImLerp( WeaponButtonAnim->second.IconSize, Condition ? 4.f : 0.f, g.IO.DeltaTime * 8.f );
WeaponButtonAnim->second.SlideX = ImLerp( WeaponButtonAnim->second.SlideX, Condition ? Width : 0.f, g.IO.DeltaTime * 2.2f );
WeaponButtonAnim->second.SlideXShadow = ImLerp( WeaponButtonAnim->second.SlideXShadow, WeaponButtonAnim->second.SlideX >= 1.f ? WeaponButtonAnim->second.SlideX + 1.f : WeaponButtonAnim->second.SlideX, g.IO.DeltaTime * 3.f );
WeaponButtonAnim->second.ProgressCol = ImLerp( WeaponButtonAnim->second.ProgressCol, WeaponButtonAnim->second.SlideX >= 0.6f ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 255.f / 255.f ) : ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.f ), g.IO.DeltaTime * 18.f );
WeaponButtonAnim->second.ShadowProgressCol = ImLerp( WeaponButtonAnim->second.ShadowProgressCol, WeaponButtonAnim->second.SlideXShadow >= 0.6f ? ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.4f ) : ImVec4( g_Col.Base.x, g_Col.Base.y, g_Col.Base.z, 0.f ), g.IO.DeltaTime * 18.f );
float Size = ( 10 + WeaponButtonAnim->second.IconSize );
ImGui::PushStyleVar( ImGuiStyleVar_Alpha, g.Style.Alpha * WeaponButtonAnim->second.Alpha );
{
Draw->AddRectFilledMultiColor( Rect.Min, Rect.Max, GetColorU32( ImVec4( ImColor( g_Col.SideBar) ) ), GetColorU32( ImVec4( ImColor( g_Col.SideBar) ) ), GetColorU32( ImVec4( ImColor(g_Col.SideBar) ) ), GetColorU32( ImVec4( ImColor(g_Col.SideBar) ) ), 8 );
Draw->AddRectFilled( Pos + ImVec2( 0, Height - 4 ), Pos + ImVec2( WeaponButtonAnim->second.SlideX, Height ), GetColorU32( WeaponButtonAnim->second.ProgressCol ), 8 );
Draw->AddImage( Icon, ImVec2( Rect.Min.x + Size, Rect.Min.y + Size ), ImVec2( Rect.Max.x - Size, Rect.Max.y - Size ), { 0,0 }, { 1,1 }, GetColorU32( ImVec4( ImColor( 255, 255, 255 ) ) ) );
}
ImGui::PopStyleVar( );
IMGUI_TEST_ENGINE_ITEM_INFO( id, label, g.LastItemData.StatusFlags );
bool Completed = WeaponButtonAnim->second.SlideX >= ( Width - 1.f );
if ( WeaponButtonAnim->second.Completed && Held ) {
return false;
}
if ( Completed ) {
WeaponButtonAnim->second.Completed = true;
return true;
}
if ( !Held ) {
WeaponButtonAnim->second.Completed = false;
}
return false;
}
inline bool ResourceListButton( const char * Label, uint32_t ResourceState, ImVec2 SizeArg, ImGuiButtonFlags flags ) {
ImGuiWindow * Window = ImGui::GetCurrentWindow( );
if ( Window->SkipItems )
return false;
ImGuiContext & g = *GImGui;
const ImGuiStyle & style = g.Style;
const ImGuiID id = Window->GetID( Label );
const ImVec2 LabelSize = g_Variables.m_FontNormal->CalcTextSizeA( g_Variables.m_FontNormal->FontSize, FLT_MAX, 0, Label );
const ImVec2 TwoTextSize = g_Variables.m_FontSecundary->CalcTextSizeA( g_Variables.m_FontSecundary->FontSize, FLT_MAX, 0, xorstr( "Stop" ) );
const ImVec2 IconTextSize = g_Variables.FontAwesomeSolid->CalcTextSizeA( g_Variables.FontAwesomeSolid->FontSize, FLT_MAX, 0, ICON_FA_CIRCLE_STOP );
const ImVec2 pos = Window->DC.CursorPos;
float Width = ImGui::GetWindowContentRegionMax( ).x - ImGui::GetWindowContentRegionMin( ).x - ( Window->ScrollbarY ? 12.f : 0.f );
SizeArg.x = Width;
ImVec2 size = ImGui::CalcItemSize( SizeArg, LabelSize.x + IconTextSize.x + style.FramePadding.x * 3.0f, LabelSize.y + style.FramePadding.y * 2.0f );
const ImRect Rect( pos, ImVec2( pos.x + size.x, pos.y + size.y ) );
ImGui::ItemSize( size, 0.f );
if ( !ImGui::ItemAdd( Rect, id ) )
return false;
bool Hovered, Held, Pressed = ImGui::ButtonBehavior( Rect, id, &Hovered, &Held, flags );
struct ResourceBtn_t {
float Alpha = 0.f;
float SlideHeld = 0.f;
float Size = 0.f;
bool Completed = false;
};
static std::map<ImGuiID, ResourceBtn_t> anim;
auto ResourceBtnAnim = anim.find( id );
if ( ResourceBtnAnim == anim.end( ) ) {
anim.insert( { id, ResourceBtn_t( ) } );
ResourceBtnAnim = anim.find( id );
}
auto TextPos = ImVec2( Rect.Min.x + 8, pos.y + ( size.y / 2 - LabelSize.y / 2 ) );
ResourceBtnAnim->second.Alpha = ImLerp( ResourceBtnAnim->second.Alpha, ResourceState == 3 ? 1.f : 0.4f, g.IO.DeltaTime * 8 );
ResourceBtnAnim->second.SlideHeld = ImLerp( ResourceBtnAnim->second.SlideHeld, Held && ResourceState == 3 ? Rect.Max.x - pos.x : TextPos.x - pos.x + LabelSize.x + 8, g.IO.DeltaTime * 4 );
ResourceBtnAnim->second.Size = ImLerp( ResourceBtnAnim->second.Size, ResourceState == 3 && Held ? 4.f : 3.f, g.IO.DeltaTime * 4 );
ImGui::PushStyleVar( ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * ResourceBtnAnim->second.Alpha );
Window->DrawList->AddRectFilled( Rect.Min, Rect.Max, GetColorU32( ( ImVec4 ) ImColor( 16, 16, 18 ) ), 6 );
Window->DrawList->AddRectFilled( Rect.Min, ImVec2( pos.x + ResourceBtnAnim->second.SlideHeld, Rect.Max.y ), GetColorU32( ( ImVec4 ) ImColor( 24, 24, 26 ) ), 6 );
Window->DrawList->AddText( g_Variables.m_FontNormal, g_Variables.m_FontNormal->FontSize, TextPos, GetColorU32( ImVec4( ImColor( g_Col.FeaturesText ) ) ), Label );
ImVec2 CirclePos( Rect.Max.x - 16, pos.y + ( size.y ) / 2 );
if ( ResourceState == 3 ) {
Window->DrawList->AddCircleFilled( CirclePos, ResourceBtnAnim->second.Size, GetColorU32( ImVec4( ImColor( 55, 237, 125, 180 ) ) ), 99 );
}
else {
Window->DrawList->AddCircleFilled( CirclePos, ResourceBtnAnim->second.Size, GetColorU32( ImVec4( ImColor( 237, 55, 55, 180 ) ) ), 99 );
}
ImGui::PopStyleVar( );
if ( ResourceState == 3 ) {
if( Held && ResourceBtnAnim->second.SlideHeld >= (Rect.Max.x - pos.x) - 1.f )
{
return true;
}
else {
return false;
}
}
else {
return false;
}
}
inline bool ListSelectableCustom( const char * Label, bool * Selected, int Type )
{
if ( Type == 0 )
{
}
else if ( Type == 1 )
{
}
return false;
}
}
