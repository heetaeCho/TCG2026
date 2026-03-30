// File: tests/config_showInvisibles_738_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigShowInvisiblesTest_738 : public ::testing::Test {
protected:
    static Config makeConfigWithShowInvisibles(bool value) {
        ConfigData data;
        data.showInvisibles = value;
        return Config{data};
    }
};

// Normal operation: default-initialized ConfigData should yield false.
TEST_F(ConfigShowInvisiblesTest_738, DefaultIsFalse_738) {
    ConfigData data; // uses defaults from header
    const Config cfg{data};
    EXPECT_FALSE(cfg.showInvisibles());
}

// Normal operation: returns true when configured true.
TEST_F(ConfigShowInvisiblesTest_738, ReturnsTrueWhenSet_738) {
    const Config cfg = makeConfigWithShowInvisibles(true);
    EXPECT_TRUE(cfg.showInvisibles());
}

// Normal operation: returns false when configured false.
TEST_F(ConfigShowInvisiblesTest_738, ReturnsFalseWhenSet_738) {
    const Config cfg = makeConfigWithShowInvisibles(false);
    EXPECT_FALSE(cfg.showInvisibles());
}

// Const-correctness: method callable on const instance and returns the configured value.
TEST_F(ConfigShowInvisiblesTest_738, ConstCorrectness_738) {
    const Config cfg = makeConfigWithShowInvisibles(true);
    const Config& cref = cfg; // ensure const usage
    EXPECT_TRUE(cref.showInvisibles());
}

// Independence from unrelated fields: changing other fields does not affect the result.
TEST_F(ConfigShowInvisiblesTest_738, UnaffectedByUnrelatedFields_738) {
    ConfigData data;
    data.showInvisibles = true;

    // Flip a bunch of unrelated fields to non-defaults to ensure no coupling is observed.
    data.listTests = true;
    data.listTags = true;
    data.listReporters = true;
    data.listListeners = true;
    data.showSuccessfulTests = true;
    data.noThrow = true;
    data.showHelp = true;
    data.filenamesAsTags = true;
    data.libIdentify = true;
    data.allowZeroTests = true;
    data.abortAfter = 0;
    data.rngSeed = 12345u;
    data.shardCount = 7u;
    data.shardIndex = 3u;
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = true;
    data.benchmarkSamples = 7u;
    data.benchmarkConfidenceInterval = 0.8;
    data.benchmarkResamples = 10u;
    data.benchmarkWarmupTime = 250;
    data.defaultOutputFilename = "out.txt";
    data.processName = "proc";
    data.testsOrTags = {"[fast]"};
    data.sectionsToRun = {"sectionA"};

    const Config cfg{data};
    EXPECT_TRUE(cfg.showInvisibles());

    // Also verify the opposite setting remains respected with the same unrelated field mutations.
    data.showInvisibles = false;
    const Config cfg2{data};
    EXPECT_FALSE(cfg2.showInvisibles());
}
