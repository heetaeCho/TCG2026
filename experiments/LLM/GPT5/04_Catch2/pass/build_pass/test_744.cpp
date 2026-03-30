// File: tests/config_benchmarkResamples_744_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"  // Path as in your build; adjust if needed
#include <limits>

using namespace Catch;

class ConfigBenchmarkResamplesTest_744 : public ::testing::Test {};

// [Normal] Returns the value provided via ConfigData
TEST_F(ConfigBenchmarkResamplesTest_744, ReturnsCustom_744) {
    ConfigData data;
    data.benchmarkResamples = 777u;

    const Config cfg{data};
    EXPECT_EQ(cfg.benchmarkResamples(), 777u);
}

// [Normal] Default-constructed ConfigData yields its documented default
TEST_F(ConfigBenchmarkResamplesTest_744, ReturnsDefault_744) {
    ConfigData data;                  // uses defaults from the real codebase
    const Config cfg{data};

    // Observable behavior: getter reflects whatever default ConfigData provides.
    // Known default in the codebase is 100000; assert to lock this behavior.
    EXPECT_EQ(cfg.benchmarkResamples(), 100000u);
}

// [Boundary] Zero is accepted and returned unchanged
TEST_F(ConfigBenchmarkResamplesTest_744, ZeroValue_744) {
    ConfigData data;
    data.benchmarkResamples = 0u;

    const Config cfg{data};
    EXPECT_EQ(cfg.benchmarkResamples(), 0u);
}

// [Boundary] Large value (max unsigned int) is accepted and returned unchanged
TEST_F(ConfigBenchmarkResamplesTest_744, MaxUnsignedInt_744) {
    ConfigData data;
    data.benchmarkResamples = std::numeric_limits<unsigned int>::max();

    const Config cfg{data};
    EXPECT_EQ(cfg.benchmarkResamples(), std::numeric_limits<unsigned int>::max());
}

// [Behavioral] Idempotent and const-correct: repeated calls on const object are stable
TEST_F(ConfigBenchmarkResamplesTest_744, IdempotentGetter_744) {
    ConfigData data;
    data.benchmarkResamples = 12345u;

    const Config cfg{data};
    const auto first = cfg.benchmarkResamples();
    const auto second = cfg.benchmarkResamples();
    EXPECT_EQ(first, 12345u);
    EXPECT_EQ(second, 12345u);
    EXPECT_EQ(first, second);
}
