// File: tests/config_benchmarkConfidenceInterval_743_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

namespace {
constexpr double kEps = 1e-12;
}

// Simple fixture for naming consistency and potential future reuse
class ConfigTest_743 : public ::testing::Test {};

// [Normal] Default-constructed ConfigData should yield Catch2's default (≈0.95)
TEST_F(ConfigTest_743, BenchmarkConfidenceInterval_Default_743) {
    ConfigData data;           // default-initialized
    Config cfg{data};

    // Expect the documented default (~0.95). Use NEAR to avoid FP literal issues.
    EXPECT_NEAR(cfg.benchmarkConfidenceInterval(), 0.95, kEps);
}

// [Normal] Custom values should be returned verbatim by the getter
TEST_F(ConfigTest_743, BenchmarkConfidenceInterval_CustomValues_743) {
    {
        ConfigData data;
        data.benchmarkConfidenceInterval = 0.5;
        Config cfg{data};
        EXPECT_NEAR(cfg.benchmarkConfidenceInterval(), 0.5, kEps);
    }
    {
        ConfigData data;
        data.benchmarkConfidenceInterval = 0.123456789012;
        Config cfg{data};
        EXPECT_NEAR(cfg.benchmarkConfidenceInterval(), 0.123456789012, kEps);
    }
}

// [Boundary] Accept and return boundary values in [0, 1]
TEST_F(ConfigTest_743, BenchmarkConfidenceInterval_Boundaries_743) {
    {
        ConfigData data;
        data.benchmarkConfidenceInterval = 0.0;
        Config cfg{data};
        EXPECT_NEAR(cfg.benchmarkConfidenceInterval(), 0.0, kEps);
    }
    {
        ConfigData data;
        data.benchmarkConfidenceInterval = 1.0;
        Config cfg{data};
        EXPECT_NEAR(cfg.benchmarkConfidenceInterval(), 1.0, kEps);
    }
}
