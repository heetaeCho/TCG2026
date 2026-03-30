// File: tests/config_verbosity_739_tests.cpp

#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"  // Uses the real interface/types

// Test fixture kept minimal; we only exercise the public interface.
class ConfigVerbosityTest_739 : public ::testing::Test {};

// [Normal operation] Default-constructed ConfigData should yield Verbosity::Normal
TEST_F(ConfigVerbosityTest_739, DefaultVerbosityIsNormal_739) {
    Catch::ConfigData data;              // uses default Verbosity::Normal
    Catch::Config cfg{data};

    EXPECT_EQ(cfg.verbosity(), Catch::Verbosity::Normal);
}

// [Boundary-ish] If Verbosity supports a “quiet/low” setting, it should be returned verbatim.
// We only rely on public enum values from the interface.
TEST_F(ConfigVerbosityTest_739, ReturnsQuietWhenConfigured_739) {
    Catch::ConfigData data;
    data.verbosity = Catch::Verbosity::Quiet;  // set through the public data holder
    const Catch::Config cfg{data};             // call on a const object to verify const-correctness

    EXPECT_EQ(cfg.verbosity(), Catch::Verbosity::Quiet);
}

// [Boundary-ish] If Verbosity supports a “high/verbose” setting, it should be returned verbatim.
TEST_F(ConfigVerbosityTest_739, ReturnsHighWhenConfigured_739) {
    Catch::ConfigData data;
    data.verbosity = Catch::Verbosity::High;
    Catch::Config cfg{data};

    EXPECT_EQ(cfg.verbosity(), Catch::Verbosity::High);
}
