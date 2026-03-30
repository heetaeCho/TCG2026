// File: tests/config_allowThrows_723_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"  // Path per your tree; adjust include if needed

namespace {

using namespace Catch;

class ConfigAllowThrowsTest_723 : public ::testing::Test {
protected:
    // Helper to build Config from ConfigData while keeping the class a black box
    static Config makeConfigWithNoThrow(bool noThrow) {
        ConfigData data;            // default-constructed data
        data.noThrow = noThrow;     // set observable input knob
        return Config{ data };      // construct CUT
    }
};

// Normal operation: default-constructed ConfigData has noThrow == false,
// so allowThrows() should be true.
TEST_F(ConfigAllowThrowsTest_723, Default_AllowsThrows_723) {
    ConfigData data;          // default noThrow=false (from provided interface snippet)
    Config cfg{ data };

    EXPECT_TRUE(cfg.allowThrows());
}

// Boundary: explicitly set noThrow=true; observable result is allowThrows() == false.
TEST_F(ConfigAllowThrowsTest_723, NoThrowTrue_DisallowsThrows_723) {
    auto cfg = ConfigAllowThrowsTest_723::makeConfigWithNoThrow(true);
    EXPECT_FALSE(cfg.allowThrows());
}

// Boundary: explicitly set noThrow=false; observable result is allowThrows() == true.
TEST_F(ConfigAllowThrowsTest_723, NoThrowFalse_AllowsThrows_723) {
    auto cfg = ConfigAllowThrowsTest_723::makeConfigWithNoThrow(false);
    EXPECT_TRUE(cfg.allowThrows());
}

// Stability/idempotence: multiple calls should not change the observable result.
TEST_F(ConfigAllowThrowsTest_723, Idempotent_MultipleCallsSameResult_723) {
    auto cfg = ConfigAllowThrowsTest_723::makeConfigWithNoThrow(true);

    // Call multiple times and verify the observable behavior is stable.
    EXPECT_FALSE(cfg.allowThrows());
    EXPECT_FALSE(cfg.allowThrows());
    EXPECT_FALSE(cfg.allowThrows());
}

} // namespace
