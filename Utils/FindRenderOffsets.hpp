#pragma once
#include <Core/SDK/SDK.hpp>
#include <iostream>
#include <vector>
namespace OffsetFinder {
struct RenderOffsetCandidate {
uintptr_t offset;
float value;
const char* type;
};
std::vector<RenderOffsetCandidate> ScanForRenderOffsets(CPed* ped, uintptr_t startOffset = 0x180, uintptr_t endOffset = 0x200) {
std::vector<RenderOffsetCandidate> candidates;
if (!ped) return candidates;
uintptr_t pedPtr = reinterpret_cast<uintptr_t>(ped);
for (uintptr_t offset = startOffset; offset < endOffset; offset += sizeof(float)) {
try {
float value = Mem.Read<float>(pedPtr + offset);
if (value >= 0.0f && value <= 1.0f) {
RenderOffsetCandidate candidate;
candidate.offset = offset;
candidate.value = value;
candidate.type = "float";
candidates.push_back(candidate);
printf("[CANDIDATE] Float at +0x%llX: %.3f (possible alpha/opacity)\n",
offset, value);
}
} catch (...) {
}
}
for (uintptr_t offset = startOffset; offset < endOffset; offset += sizeof(BYTE)) {
try {
BYTE value = Mem.Read<BYTE>(pedPtr + offset);
if (value == 0x00 || value == 0x01 || value == 0x37 || value == 0xFF) {
RenderOffsetCandidate candidate;
candidate.offset = offset;
candidate.value = static_cast<float>(value);
candidate.type = "byte";
candidates.push_back(candidate);
printf("[CANDIDATE] Byte at +0x%llX: 0x%02X (possible flag)\n",
offset, value);
}
} catch (...) {
}
}
return candidates;
}
bool TestRenderOffset(CPed* ped, uintptr_t offset, const char* type = "float") {
if (!ped) return false;
uintptr_t pedPtr = reinterpret_cast<uintptr_t>(ped);
float originalValue = 0.0f;
if (strcmp(type, "float") == 0) {
originalValue = Mem.Read<float>(pedPtr + offset);
Mem.Write<float>(pedPtr + offset, 0.5f);
printf("[TEST] Testing float offset +0x%llX\n", offset);
printf("       Original: %.3f, Testing with: 0.5f\n", originalValue);
printf("       If player becomes semi-transparent, this might be the offset!\n");
Sleep(2000);
Mem.Write<float>(pedPtr + offset, originalValue);
return true;
}
else if (strcmp(type, "byte") == 0) {
BYTE originalValue = Mem.Read<BYTE>(pedPtr + offset);
BYTE testValue = originalValue ^ 0x01;
Mem.Write<BYTE>(pedPtr + offset, testValue);
printf("[TEST] Testing byte offset +0x%llX\n", offset);
printf("       Original: 0x%02X, Testing with: 0x%02X\n", originalValue, testValue);
printf("       Observe if player visibility changes!\n");
Sleep(2000);
Mem.Write<BYTE>(pedPtr + offset, originalValue);
return true;
}
return false;
}
void FindVisualRenderOffsets(CPed* ped) {
if (!ped) {
printf("[ERROR] Invalid ped pointer!\n");
return;
}
printf("\n=== Starting Render Offset Scan ===\n");
printf("Scanning ped at: 0x%llX\n", reinterpret_cast<uintptr_t>(ped));
printf("Known invisible offsets: 0x189, 0xAC, 0x2C\n");
printf("\nScanning area 0x180-0x200 for candidates...\n\n");
auto candidates = ScanForRenderOffsets(ped, 0x180, 0x200);
printf("\n=== Found %zu Candidates ===\n\n", candidates.size());
for (const auto& candidate : candidates) {
printf("Candidate: +0x%llX (%s) = ", candidate.offset, candidate.type);
if (candidate.type == std::string("float")) {
printf("%.3f\n", candidate.value);
} else {
printf("0x%02X\n", static_cast<BYTE>(candidate.value));
}
if (candidate.offset == 0x189 || candidate.offset == 0xAC || candidate.offset == 0x2C) {
printf("  -> Known offset, skipping test\n");
continue;
}
printf("  -> Test this offset? (You can call TestRenderOffset manually)\n");
}
printf("\n=== Scan Complete ===\n");
printf("To test an offset manually, call:\n");
printf("  TestRenderOffset(ped, 0xXXX, \"float\");\n");
printf("  TestRenderOffset(ped, 0xXXX, \"byte\");\n\n");
}
void CompareMemoryBeforeAfterInvisibility(CPed* ped) {
if (!ped) return;
uintptr_t pedPtr = reinterpret_cast<uintptr_t>(ped);
printf("\n=== Memory Comparison: Before/After Invisibility ===\n");
std::vector<float> beforeFloats;
std::vector<BYTE> beforeBytes;
for (uintptr_t offset = 0x180; offset < 0x200; offset += 4) {
try {
float value = Mem.Read<float>(pedPtr + offset);
beforeFloats.push_back(value);
} catch (...) {
beforeFloats.push_back(0.0f);
}
}
for (uintptr_t offset = 0x180; offset < 0x200; offset += 1) {
try {
BYTE value = Mem.Read<BYTE>(pedPtr + offset);
beforeBytes.push_back(value);
} catch (...) {
beforeBytes.push_back(0);
}
}
printf("Applying known invisibility (0x189 = 0x01)...\n");
ped->Invisible(true);
Sleep(500);
uintptr_t floatIndex = 0;
uintptr_t byteIndex = 0;
for (uintptr_t offset = 0x180; offset < 0x200; offset += 4) {
try {
float afterValue = Mem.Read<float>(pedPtr + offset);
float beforeValue = beforeFloats[floatIndex];
if (afterValue != beforeValue) {
printf("[CHANGED] Float at +0x%llX: %.3f -> %.3f (delta: %.3f)\n",
offset, beforeValue, afterValue, afterValue - beforeValue);
}
} catch (...) {}
floatIndex++;
}
for (uintptr_t offset = 0x180; offset < 0x200; offset += 1) {
try {
BYTE afterValue = Mem.Read<BYTE>(pedPtr + offset);
BYTE beforeValue = beforeBytes[byteIndex];
if (afterValue != beforeValue) {
printf("[CHANGED] Byte at +0x%llX: 0x%02X -> 0x%02X\n",
offset, beforeValue, afterValue);
}
} catch (...) {}
byteIndex++;
}
ped->Invisible(false);
printf("\nInvisibility restored.\n");
printf("=== Comparison Complete ===\n\n");
}
}
