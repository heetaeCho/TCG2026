// File: tests/config_benchmarkSamples_test_742.cpp

#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigBenchmarkSamplesTest_742 : public ::testing::Test {};

// [Normal operation] Default-constructed Config should use ConfigData's default (100).
TEST_F(ConfigBenchmarkSamplesTest_742, DefaultValueIs100_742) {
    Config cfg; // default-constructed
    EXPECT_EQ(cfg.benchmarkSamples(), 100u);
}

// [Normal operation] Value provided via ConfigData constructor parameter is returned verbatim.
TEST_F(ConfigBenchmarkSamplesTest_742, ReturnsValueFromProvidedData_742) {
    ConfigData data;
    data.benchmarkSamples = 37u;
    Config cfg(data);
    EXPECT_EQ(cfg.benchmarkSamples(), 37u);
}

// [Boundary] Zero is a valid unsigned value and should be returned as-is if set.
TEST_F(ConfigBenchmarkSamplesTest_742, AcceptsBoundaryZero_742) {
    ConfigData data;
    data.benchmarkSamples = 0u;
    Config cfg(data);
    EXPECT_EQ(cfg.benchmarkSamples(), 0u);
}

// [Boundary] Max unsigned int should round-trip through the interface.
TEST_F(ConfigBenchmarkSamplesTest_742, AcceptsMaxUnsignedInt_742) {
    ConfigData data;
    data.benchmarkSamples = std::numeric_limits<unsigned int>::max();
    Config cfg(data);
    EXPECT_EQ(cfg.benchmarkSamples(), std::numeric_limits<unsigned int>::max());
}

// [Behavioral] Mutating the original ConfigData after constructing Config should not affect Config.
TEST_F(ConfigBenchmarkSamplesTest_742, DataIndependenceAfterConstruction_742) {
    ConfigData data;
    data.benchmarkSamples = 123u;
    Config cfg(data);

    // Mutate the original source data after construction.
    data.benchmarkSamples = 456u;

    // Observable behavior: cfg retains its original value.
    EXPECT_EQ(cfg.benchmarkSamples(), 123u);
}
