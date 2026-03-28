// File: tests/config_warn_unmatched_tests_727.cpp

#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

using namespace Catch;

TEST(ConfigWarnUnmatchedSpec_727, DefaultReturnsFalse_727) {
    // Default-constructed Config should not warn about unmatched specs
    Config cfg;
    EXPECT_FALSE(cfg.warnAboutUnmatchedTestSpecs());
}

TEST(ConfigWarnUnmatchedSpec_727, ExplicitNothingReturnsFalse_727) {
    ConfigData data;
    data.warnings = WarnAbout::Nothing;
    Config cfg{data};
    EXPECT_FALSE(cfg.warnAboutUnmatchedTestSpecs());
}

TEST(ConfigWarnUnmatchedSpec_727, UnmatchedFlagAloneReturnsTrue_727) {
    ConfigData data;
    data.warnings = WarnAbout::UnmatchedTestSpec;
    Config cfg{data};
    EXPECT_TRUE(cfg.warnAboutUnmatchedTestSpecs());
}

TEST(ConfigWarnUnmatchedSpec_727, OtherFlagAloneReturnsFalse_727) {
    // Setting a different warning flag (NoAssertions) should not trigger this one
    ConfigData data;
    data.warnings = WarnAbout::NoAssertions;
    Config cfg{data};
    EXPECT_FALSE(cfg.warnAboutUnmatchedTestSpecs());
}

TEST(ConfigWarnUnmatchedSpec_727, MultipleFlagsIncludesUnmatchedReturnsTrue_727) {
    ConfigData data;
    data.warnings = static_cast<WarnAbout::What>(
        WarnAbout::NoAssertions | WarnAbout::UnmatchedTestSpec);
    Config cfg{data};
    EXPECT_TRUE(cfg.warnAboutUnmatchedTestSpecs());
}

TEST(ConfigWarnUnmatchedSpec_727, StableAcrossMultipleCalls_727) {
    ConfigData data;
    data.warnings = WarnAbout::UnmatchedTestSpec;
    Config cfg{data};

    // Observable behavior should be stable across repeated invocations
    EXPECT_TRUE(cfg.warnAboutUnmatchedTestSpecs());
    EXPECT_TRUE(cfg.warnAboutUnmatchedTestSpecs());
    EXPECT_TRUE(cfg.warnAboutUnmatchedTestSpecs());
}
