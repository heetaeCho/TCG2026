// File: tests/config_shouldDebugBreak_736_tests.cpp

#include <gtest/gtest.h>

// Include the public interface under test
#include "Catch2/src/catch2/catch_config.hpp"

using namespace Catch;

class ConfigShouldDebugBreakTest_736 : public ::testing::Test {
protected:
    // Helper to build Config from ConfigData without touching any private state
    static Config makeConfigWithDebugBreak(bool shouldBreak) {
        ConfigData data;
        // We only set what is observable via the interface being tested.
        // Other fields remain at their default values.
        // Note: We do NOT rely on defaults of shouldDebugBreak. We set it explicitly.
        // The field exists because the implementation reads m_data.shouldDebugBreak.
        // (We do not inspect private state; we only provide constructor input.)
        // If your codebase uses a setter or different path, adapt here accordingly.
        data.shouldDebugBreak = shouldBreak;
        return Config{data};
    }
};

// [Normal operation] When shouldDebugBreak is set to true in ConfigData,
// the observable method should return true.
TEST_F(ConfigShouldDebugBreakTest_736, ShouldDebugBreak_ReturnsTrueWhenSet_736) {
    Config cfg = makeConfigWithDebugBreak(true);
    EXPECT_TRUE(cfg.shouldDebugBreak());
}

// [Normal operation] When shouldDebugBreak is set to false in ConfigData,
// the observable method should return false.
TEST_F(ConfigShouldDebugBreakTest_736, ShouldDebugBreak_ReturnsFalseWhenUnset_736) {
    Config cfg = makeConfigWithDebugBreak(false);
    EXPECT_FALSE(cfg.shouldDebugBreak());
}

// [Idempotence / const-correctness] Calling the const getter repeatedly
// shows no side effects and returns the same observable value.
TEST_F(ConfigShouldDebugBreakTest_736, ShouldDebugBreak_IsIdempotentAndConst_736) {
    Config cfg = makeConfigWithDebugBreak(true);

    // Multiple calls should consistently reflect the same observable state.
    EXPECT_TRUE(cfg.shouldDebugBreak());
    EXPECT_TRUE(cfg.shouldDebugBreak());
    EXPECT_TRUE(cfg.shouldDebugBreak());
}
