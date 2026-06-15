#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <Security/xorstr.hpp>

// Anti-Global Boolean: Use an enum with random values
enum class SessionState : uint64_t {
    None = 0x0,
    Initialized = 0x1A2B3C4D,
    Authenticated = 0x5E6F7080, // Placeholder, will use dynamic values
    Running = 0x91011213,
    Compromised = 0xDEADDEAD
};

enum class ValidationContext {
    Login,
    MenuOpen,
    Aimbot,
    ESP,
    Exploits,
    Runtime
};

struct SessionToken {
    uint64_t timestamp;
    uint64_t signature;
    uint64_t entropy;
};

class SessionManager {
private:
    struct InternalState {
        uint64_t s1; // Derived from time
        uint64_t s2; // Derived from key
        uint64_t s3; // Derived from s1 ^ s2
        uint64_t integrity_hash;
    };

    InternalState current_state;
    std::vector<uint64_t> check_history;
    
    // Hidden factors
    uint64_t base_offset = 0; // If this is 0, features work. If randomized, they break.

    uint64_t generate_signature(uint64_t input) {
        return (input ^ 0x92837482) * 0x123456789; // Simple obfuscation
    }

    void update_integrity() {
        current_state.integrity_hash = current_state.s1 ^ current_state.s2 ^ current_state.s3;
    }

public:
    SessionManager() {
        current_state = { 0, 0, 0, 0 };
    }

    // A -> B Transition
    void Initialize(std::string key_part) {
        // Derive state from key part, don't just set a flag
        uint64_t key_hash = 0;
        for (char c : key_part) key_hash = key_hash * 31 + c;
        
        current_state.s1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        current_state.s2 = key_hash;
        current_state.s3 = current_state.s1 ^ current_state.s2;
        update_integrity();
    }

    // B -> C Transition
    bool Validate(ValidationContext ctx) {
        // Cross-check internal consistency
        if ((current_state.s1 ^ current_state.s2) != current_state.s3) {
            fail_silently();
            return false;
        }

        if (current_state.integrity_hash != (current_state.s1 ^ current_state.s2 ^ current_state.s3)) {
             fail_silently();
             return false;
        }

        // Context specific checks (time distribution)
        // In a real scenario, we might check if enough time passed since login, etc.
        
        return true; 
    }

    void fail_silently() {
        // Corrupt the base offset or some global state
        // This will cause features to read wrong memory
        base_offset = std::rand() % 0xFFFF;
        current_state.s1 = 0; // Break the chain
    }

    uint64_t GetBaseOffset() {
        // Features should add this to their pointer calculations
        // If session is valid, it's 0. If not, it's garbage.
        return base_offset;
    }
    
    bool IsAuthenticated() {
        // Never expose a simple bool, but for UI we might need a helper.
        // Make it check the chain.
        return (current_state.s1 != 0) && 
               ((current_state.s1 ^ current_state.s2) == current_state.s3);
    }
};

extern SessionManager g_Session;
