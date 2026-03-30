// File: tests/config_zeroTestsCountAsSuccess_728_tests.cpp
#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

// [TEST_ID = 728]
TEST(Config_ZeroTestsCountAsSuccess_728, DefaultIsFalse_728) {
    // Default-constructed Config should reflect default settings from its public interface.
    Config cfg; // uses default-initialized ConfigData internally
    EXPECT_FALSE(cfg.zeroTestsCountAsSuccess());
}

// [TEST_ID = 728]
TEST(Config_ZeroTestsCountAsSuccess_728, TrueWhenConfigured_728) {
    // When allowZeroTests is enabled via public constructor, the query should return true.
    ConfigData data;
    data.allowZeroTests = true;

    Config cfg{data};
    EXPECT_TRUE(cfg.zeroTestsCountAsSuccess());
}

// [TEST_ID = 728]
TEST(Config_ZeroTestsCountAsSuccess_728, FalseWhenExplicitlyDisabled_728) {
    // When allowZeroTests is explicitly disabled, the query should return false.
    ConfigData data;
    data.allowZeroTests = false;

    Config cfg{data};
    EXPECT_FALSE(cfg.zeroTestsCountAsSuccess());
}

// [TEST_ID = 728]
TEST(Config_ZeroTestsCountAsSuccess_728, UsesSnapshotOfInputData_728) {
    // The Config should not depend on later mutations of the caller's ConfigData.
    ConfigData data;
    data.allowZeroTests = true;
    Config cfg{data};

    // Mutate original after construction (observable only through the API).
    data.allowZeroTests = false;

    // Behavior should remain based on the constructed configuration, not the mutated source.
    EXPECT_TRUE(cfg.zeroTestsCountAsSuccess());
}

// [TEST_ID = 728]
TEST(Config_ZeroTestsCountAsSuccess_728, CallableOnConstInstance_728) {
    // The query function should be callable on const instances per the public interface.
    ConfigData data;
    data.allowZeroTests = true;
    const Config cfg{data};

    EXPECT_TRUE(cfg.zeroTestsCountAsSuccess());
}
