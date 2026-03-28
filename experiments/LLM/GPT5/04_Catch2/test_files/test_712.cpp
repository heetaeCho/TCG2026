// File: tests/config_listTests_712.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"  // Adjust include path if needed

namespace Catch {

TEST(ConfigListTests_712, ReturnsTrueWhenListTestsFlagIsTrue_712) {
    ConfigData data;
    data.listTests = true;

    const Config cfg{data};
    EXPECT_TRUE(cfg.listTests());
}

TEST(ConfigListTests_712, ReturnsFalseWhenListTestsFlagIsFalse_712) {
    ConfigData data;
    data.listTests = false;

    const Config cfg{data};
    EXPECT_FALSE(cfg.listTests());
}

TEST(ConfigListTests_712, DefaultConstructedConfigReturnsFalse_712) {
    // Per provided interface, default-constructed Config is allowed.
    // Observable behavior: listTests() should reflect default ConfigData value.
    const Config cfg; // default-constructed
    EXPECT_FALSE(cfg.listTests());
}

TEST(ConfigListTests_712, UnaffectedByOtherConfigFlags_712) {
    ConfigData data;
    // Set listTests to true and flip a variety of unrelated flags/fields.
    data.listTests = true;
    data.listTags = false;
    data.listReporters = true;
    data.listListeners = true;
    data.showSuccessfulTests = true;
    data.noThrow = true;
    data.showHelp = false;
    data.showInvisibles = true;
    data.filenamesAsTags = true;
    data.libIdentify = false;
    data.allowZeroTests = true;
    data.abortAfter = 3;
    data.shardCount = 4;
    data.shardIndex = 2;
    data.skipBenchmarks = true;
    data.benchmarkNoAnalysis = true;
    data.benchmarkSamples = 42;
    data.benchmarkConfidenceInterval = 0.9;
    data.benchmarkResamples = 1234;
    data.benchmarkWarmupTime = 250;
    // Leave other complex fields as their defaults or empty.

    const Config cfg{data};
    EXPECT_TRUE(cfg.listTests()); // Should depend only on listTests flag
}

} // namespace Catch
