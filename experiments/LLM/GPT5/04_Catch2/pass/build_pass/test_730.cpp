// File: tests/config_min_duration_730_test.cpp

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// Assume the real project headers are available.
// If paths differ, adjust these includes accordingly.
#include "catch2/catch_config.hpp"
#include "catch2/catch_config.cpp" // If your build exposes the implementation separately, omit this.

// Test suite for Config::minDuration()
namespace {

using Catch::Config;
using Catch::ConfigData;

class ConfigMinDurationTest_730 : public ::testing::Test {};

TEST_F(ConfigMinDurationTest_730, DefaultValueIsMinusOne_730) {
    ConfigData data; // Uses defaults
    Config cfg{data};
    EXPECT_DOUBLE_EQ(cfg.minDuration(), -1.0);
}

TEST_F(ConfigMinDurationTest_730, ReturnsZeroWhenConfigured_730) {
    ConfigData data;
    data.minDuration = 0.0;
    Config cfg{data};
    EXPECT_DOUBLE_EQ(cfg.minDuration(), 0.0);
}

TEST_F(ConfigMinDurationTest_730, ReturnsPositiveValue_730) {
    ConfigData data;
    data.minDuration = 0.123; // typical small positive value
    Config cfg{data};
    EXPECT_DOUBLE_EQ(cfg.minDuration(), 0.123);
}

TEST_F(ConfigMinDurationTest_730, ReturnsLargeValue_730) {
    ConfigData data;
    data.minDuration = 1e9; // large finite value
    Config cfg{data};
    EXPECT_DOUBLE_EQ(cfg.minDuration(), 1e9);
}

TEST_F(ConfigMinDurationTest_730, SupportsNaN_730) {
    ConfigData data;
    data.minDuration = std::numeric_limits<double>::quiet_NaN();
    Config cfg{data};
    EXPECT_TRUE(std::isnan(cfg.minDuration()));
}

TEST_F(ConfigMinDurationTest_730, SupportsInfinity_730) {
    // +infinity
    {
        ConfigData data;
        data.minDuration = std::numeric_limits<double>::infinity();
        Config cfg{data};
        double v = cfg.minDuration();
        EXPECT_TRUE(std::isinf(v));
        EXPECT_GT(v, 0.0);
    }
    // -infinity
    {
        ConfigData data;
        data.minDuration = -std::numeric_limits<double>::infinity();
        Config cfg{data};
        double v = cfg.minDuration();
        EXPECT_TRUE(std::isinf(v));
        EXPECT_LT(v, 0.0);
    }
}

TEST_F(ConfigMinDurationTest_730, ImmutableAfterConstruction_730) {
    // Observes behavior through the public ctor + accessor:
    // changing the source ConfigData after constructing Config should
    // not change what Config reports (based on the provided ctor signature).
    ConfigData data;
    data.minDuration = 3.14;
    Config cfg{data};

    // Mutate the original data afterward
    data.minDuration = 2.71;

    // Observable expectation: cfg's reported value is unaffected
    EXPECT_DOUBLE_EQ(cfg.minDuration(), 3.14);
}

} // namespace
