// File: tests/config_skipBenchmarks_740_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"  // Adjust include path if needed

using Catch::Config;
using Catch::ConfigData;

namespace {

TEST(ConfigSkipBenchmarksTest_740, DefaultIsFalse_740) {
    // Arrange: default-constructed Config should rely on ConfigData's defaults
    Config cfg; // uses default-initialized internal data

    // Act & Assert
    EXPECT_FALSE(cfg.skipBenchmarks());
}

TEST(ConfigSkipBenchmarksTest_740, ReturnsTrueWhenSetInCtor_740) {
    // Arrange
    ConfigData data;
    data.skipBenchmarks = true;

    // Act
    Config cfg{data};

    // Assert
    EXPECT_TRUE(cfg.skipBenchmarks());
}

TEST(ConfigSkipBenchmarksTest_740, ReturnsFalseWhenUnsetInCtor_740) {
    // Arrange
    ConfigData data;
    data.skipBenchmarks = false;

    // Act
    Config cfg{data};

    // Assert
    EXPECT_FALSE(cfg.skipBenchmarks());
}

TEST(ConfigSkipBenchmarksTest_740, UnaffectedByOtherFlags_740) {
    // Arrange: flip a variety of unrelated fields to ensure no cross-coupling
    ConfigData data;
    data.skipBenchmarks = true;
    data.listTests = true;
    data.listTags = true;
    data.listReporters = true;
    data.noThrow = true;
    data.allowZeroTests = true;
    data.benchmarkNoAnalysis = true;
    data.benchmarkSamples = 42;
    data.benchmarkConfidenceInterval = 0.9;
    data.benchmarkResamples = 10;
    data.shardCount = 3;
    data.shardIndex = 1;

    // Act
    Config cfg{data};

    // Assert: Only verify the observable accessor under test
    EXPECT_TRUE(cfg.skipBenchmarks());
}

TEST(ConfigSkipBenchmarksTest_740, MultipleCallsAreConsistent_740) {
    // Arrange
    ConfigData data;
    data.skipBenchmarks = false;
    Config cfg{data};

    // Act & Assert: call multiple times to ensure stable observable behavior
    EXPECT_FALSE(cfg.skipBenchmarks());
    EXPECT_FALSE(cfg.skipBenchmarks());
    EXPECT_FALSE(cfg.skipBenchmarks());
}

} // namespace
