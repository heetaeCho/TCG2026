// File: tests/config_include_successful_results_725_tests.cpp

#include <gtest/gtest.h>

// Use the real Catch2 headers from your codebase.
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigIncludeSuccessfulResultsTest_725 : public ::testing::Test {
protected:
    // Helper to construct Config from ConfigData with desired flag
    static Config makeConfigWithShowSuccessful(bool value) {
        ConfigData data;
        data.showSuccessfulTests = value;
        return Config{data};
    }
};

// [Normal operation] Explicit true -> getter returns true
TEST_F(ConfigIncludeSuccessfulResultsTest_725, ReturnsTrueWhenEnabled_725) {
    Config cfg = makeConfigWithShowSuccessful(true);
    EXPECT_TRUE(cfg.includeSuccessfulResults());
}

// [Normal operation] Explicit false -> getter returns false
TEST_F(ConfigIncludeSuccessfulResultsTest_725, ReturnsFalseWhenDisabled_725) {
    Config cfg = makeConfigWithShowSuccessful(false);
    EXPECT_FALSE(cfg.includeSuccessfulResults());
}

// [Boundary / default construction] Default-constructed Config reports default flag (expected false)
TEST_F(ConfigIncludeSuccessfulResultsTest_725, DefaultIsFalse_725) {
    Config cfg; // relies on default-initialized ConfigData defaults
    EXPECT_FALSE(cfg.includeSuccessfulResults());
}

// [Observable behavior / construction semantics] Copy independence from source ConfigData
// Construct from data=true, then mutate the original data to false; the Config's observable
// behavior should remain what it was at construction.
TEST_F(ConfigIncludeSuccessfulResultsTest_725, IndependentFromSourceConfigDataAfterConstruction_725) {
    ConfigData source;
    source.showSuccessfulTests = true;

    Config cfg{source};            // construct with true
    source.showSuccessfulTests = false; // mutate source after construction

    EXPECT_TRUE(cfg.includeSuccessfulResults())
        << "Config should reflect the value at construction, not later mutations of the source";
}
