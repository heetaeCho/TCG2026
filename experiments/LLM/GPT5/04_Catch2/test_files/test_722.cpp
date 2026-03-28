// File: tests/config_showHelp_722_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"  // Adjust include path to your tree if needed

// Test fixture kept minimal; we only use public APIs.
class ConfigShowHelpTest_722 : public ::testing::Test {
protected:
    // Helper to create a Config from ConfigData while only touching public fields.
    static Catch::Config makeConfig(const Catch::ConfigData& data) {
        return Catch::Config(data);
    }
};

// [Normal operation] Default-constructed Config should reflect the default of ConfigData::showHelp (false).
TEST_F(ConfigShowHelpTest_722, DefaultIsFalse_722) {
    Catch::Config cfg;  // relies on default-initialized ConfigData
    // Call through const reference to assert const-correct access is usable.
    const Catch::Config& ccfg = cfg;
    EXPECT_FALSE(ccfg.showHelp());
}

// [Normal operation] When Config is constructed with showHelp = true, showHelp() returns true.
TEST_F(ConfigShowHelpTest_722, TrueWhenSet_722) {
    Catch::ConfigData data;
    data.showHelp = true;

    auto cfg = ConfigShowHelpTest_722::makeConfig(data);
    const Catch::Config& ccfg = cfg;
    EXPECT_TRUE(ccfg.showHelp());
}

// [Independence from other options] showHelp() reflects only the configured showHelp flag,
// regardless of other flags set in ConfigData (observable via the getter).
TEST_F(ConfigShowHelpTest_722, IndependentOfOtherFlags_722) {
    Catch::ConfigData data;

    // Flip a bunch of unrelated options to ensure they don't affect showHelp().
    data.listTests = true;
    data.listTags = true;
    data.listReporters = true;
    data.listListeners = true;
    data.showSuccessfulTests = true;
    data.noThrow = true;
    data.showInvisibles = true;
    data.filenamesAsTags = true;
    data.libIdentify = true;
    data.allowZeroTests = true;

    // Case A: showHelp = false -> expect false
    data.showHelp = false;
    {
        auto cfg = ConfigShowHelpTest_722::makeConfig(data);
        const Catch::Config& ccfg = cfg;
        EXPECT_FALSE(ccfg.showHelp());
    }

    // Case B: showHelp = true -> expect true
    data.showHelp = true;
    {
        auto cfg = ConfigShowHelpTest_722::makeConfig(data);
        const Catch::Config& ccfg = cfg;
        EXPECT_TRUE(ccfg.showHelp());
    }
}
