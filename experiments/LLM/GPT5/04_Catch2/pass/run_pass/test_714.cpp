// File: tests/config_listReporters_714.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using Catch::Config;
using Catch::ConfigData;

class Config_ListReporters_Test_714 : public ::testing::Test {};

// [Normal] Default-constructed Config should not list reporters.
TEST_F(Config_ListReporters_Test_714, DefaultIsFalse_714) {
    Config cfg; // relies on ConfigData default member initializers
    EXPECT_FALSE(cfg.listReporters());
}

// [Normal] When Config is constructed with listReporters=true, it should report true.
TEST_F(Config_ListReporters_Test_714, ReturnsTrueWhenSet_714) {
    ConfigData data;
    data.listReporters = true;
    Config cfg(data);
    EXPECT_TRUE(cfg.listReporters());
}

// [Boundary] Explicitly setting listReporters=false should report false.
TEST_F(Config_ListReporters_Test_714, ReturnsFalseWhenExplicitFalse_714) {
    ConfigData data;
    data.listReporters = false;
    Config cfg(data);
    EXPECT_FALSE(cfg.listReporters());
}

// [Stability] Calling listReporters() multiple times should be idempotent and not change state.
TEST_F(Config_ListReporters_Test_714, IdempotentCalls_714) {
    ConfigData data;
    data.listReporters = true;
    Config cfg(data);

    // Multiple invocations should consistently return the same value.
    EXPECT_TRUE(cfg.listReporters());
    EXPECT_TRUE(cfg.listReporters());
    EXPECT_TRUE(cfg.listReporters());
}

// [Isolation] listReporters should be independent of other flags in ConfigData.
TEST_F(Config_ListReporters_Test_714, IndependentFromOtherFlags_714) {
    ConfigData data;

    // Flip a bunch of unrelated switches to ensure no coupling affects listReporters.
    data.listTests = true;
    data.listTags = true;
    data.listListeners = true;
    data.showSuccessfulTests = true;
    data.noThrow = true;
    data.showHelp = true;
    data.showInvisibles = true;
    data.filenamesAsTags = true;
    data.libIdentify = true;
    data.allowZeroTests = true;
    data.abortAfter = 7;
    data.rngSeed = 123u;
    data.shardCount = 3u;
    data.shardIndex = 1u;
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = true;
    data.benchmarkSamples = 10u;
    data.benchmarkConfidenceInterval = 0.9;
    data.benchmarkResamples = 1000u;
    data.benchmarkWarmupTime = 50;
    // leave verbosity/others as defaults

    // Case A: listReporters=false -> expect false regardless of other flags
    data.listReporters = false;
    Config cfgFalse(data);
    EXPECT_FALSE(cfgFalse.listReporters());

    // Case B: listReporters=true -> expect true regardless of other flags
    data.listReporters = true;
    Config cfgTrue(data);
    EXPECT_TRUE(cfgTrue.listReporters());
}
