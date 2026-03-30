// File: tests/config_defaultColourMode_735.cpp
#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"  // Declares Catch::Config, Catch::ConfigData, Catch::ColourMode

using Catch::Config;
using Catch::ConfigData;
using Catch::ColourMode;

class ConfigDefaultColourModeTest_735 : public ::testing::Test {};

// Normal operation: default-initialized ConfigData should yield PlatformDefault.
TEST_F(ConfigDefaultColourModeTest_735, DefaultIsPlatformDefault_735) {
    ConfigData data; // uses default member initializers
    Config cfg{ data };

    EXPECT_EQ(ColourMode::PlatformDefault, cfg.defaultColourMode());
}

// Normal operation with default constructor: also expected to reflect defaults.
TEST_F(ConfigDefaultColourModeTest_735, DefaultCtorYieldsPlatformDefault_735) {
    Config cfg; // relies on class's default construction semantics

    EXPECT_EQ(ColourMode::PlatformDefault, cfg.defaultColourMode());
}

// Interface const-correctness & observable behavior: callable on const instance and returns same value.
TEST_F(ConfigDefaultColourModeTest_735, ConstAccessReturnsSameValue_735) {
    ConfigData data; // default -> PlatformDefault
    const Config cfg{ data };

    // Ensure method is callable on const object and matches expected observable value.
    EXPECT_EQ(ColourMode::PlatformDefault, cfg.defaultColourMode());
}
