// File: tests/config_benchmarkWarmupTime_745_tests.cpp

#include <gtest/gtest.h>
#include <chrono>
#include "catch2/catch_config.hpp"

using namespace std::chrono;

class ConfigBenchmarkWarmupTimeTest_745 : public ::testing::Test {};

// Normal operation: uses the default-initialized value from ConfigData
TEST_F(ConfigBenchmarkWarmupTimeTest_745, ReturnsDefaultValue_745) {
    Catch::ConfigData data; // benchmarkWarmupTime defaults to 100 (rep)
    Catch::Config cfg{data};

    EXPECT_EQ(cfg.benchmarkWarmupTime(), milliseconds(100))
        << "Expected default benchmark warmup time to be 100ms";
}

// Boundary: zero warmup time
TEST_F(ConfigBenchmarkWarmupTimeTest_745, ReturnsZeroWhenConfiguredZero_745) {
    Catch::ConfigData data;
    data.benchmarkWarmupTime = milliseconds::rep{0};
    Catch::Config cfg{data};

    EXPECT_EQ(cfg.benchmarkWarmupTime(), milliseconds(0))
        << "Expected benchmark warmup time to be exactly 0ms when configured as such";
}

// Boundary: small positive value (1ms)
TEST_F(ConfigBenchmarkWarmupTimeTest_745, ReturnsOneMillisecondWhenConfigured_745) {
    Catch::ConfigData data;
    data.benchmarkWarmupTime = milliseconds::rep{1};
    Catch::Config cfg{data};

    EXPECT_EQ(cfg.benchmarkWarmupTime(), milliseconds(1))
        << "Expected benchmark warmup time to be exactly 1ms";
}

// Normal operation: a larger, typical value
TEST_F(ConfigBenchmarkWarmupTimeTest_745, ReturnsCustomLargeValue_745) {
    Catch::ConfigData data;
    // 1 hour expressed in milliseconds
    data.benchmarkWarmupTime = milliseconds::rep{60 * 60 * 1000};
    Catch::Config cfg{data};

    EXPECT_EQ(cfg.benchmarkWarmupTime(), milliseconds(60 * 60 * 1000))
        << "Expected benchmark warmup time to reflect the configured large value precisely";
}

// Exceptional/edge (if allowed by type): negative warmup time propagates as-is
// (We do not assert any clamping or validation, only observable return value.)
TEST_F(ConfigBenchmarkWarmupTimeTest_745, ReturnsNegativeWhenConfiguredNegative_745) {
    Catch::ConfigData data;
    data.benchmarkWarmupTime = milliseconds::rep{-5};
    Catch::Config cfg{data};

    EXPECT_EQ(cfg.benchmarkWarmupTime(), milliseconds(-5))
        << "Expected benchmark warmup time to propagate negative values as provided";
}
