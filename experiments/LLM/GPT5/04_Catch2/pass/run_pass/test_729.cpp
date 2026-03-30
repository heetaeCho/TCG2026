// File: tests/config_showDurations_729.tests.cpp

#include <gtest/gtest.h>

// Include the Catch2 headers for Config/ConfigData and ShowDurations.
// Adjust the include paths to your repo layout if needed.
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigShowDurationsTest_729 : public ::testing::Test {
protected:
    // Helper to build a Config from ConfigData without exposing internals
    static Config makeConfig(const ConfigData& d) {
        return Config(d);
    }
};

// Normal operation: default-constructed ConfigData should yield
// ShowDurations::DefaultForReporter through the Config interface.
TEST_F(ConfigShowDurationsTest_729, DefaultIsDefaultForReporter_729) {
    ConfigData data; // uses defaults per interface
    auto cfg = ConfigShowDurationsTest_729::makeConfig(data);

    EXPECT_EQ(cfg.showDurations(), ShowDurations::DefaultForReporter);
}

// Boundary/explicit value: forcing Always should be observable via getter.
TEST_F(ConfigShowDurationsTest_729, ExplicitAlwaysIsReturned_729) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    auto cfg = ConfigShowDurationsTest_729::makeConfig(data);

    EXPECT_EQ(cfg.showDurations(), ShowDurations::Always);
}

// Boundary/explicit value: forcing Never should be observable via getter.
TEST_F(ConfigShowDurationsTest_729, ExplicitNeverIsReturned_729) {
    ConfigData data;
    data.showDurations = ShowDurations::Never;
    auto cfg = ConfigShowDurationsTest_729::makeConfig(data);

    EXPECT_EQ(cfg.showDurations(), ShowDurations::Never);
}

// Stability after construction (observable behavior only):
// Changing the original ConfigData after constructing Config should not
// change what the Config instance reports via showDurations().
TEST_F(ConfigShowDurationsTest_729, PostConstructionMutationDoesNotAffectGetter_729) {
    ConfigData data;
    data.showDurations = ShowDurations::Always;
    auto cfg = ConfigShowDurationsTest_729::makeConfig(data);

    // Mutate the local data object AFTER constructing cfg.
    data.showDurations = ShowDurations::Never;

    // Observable behavior via cfg should remain the same.
    EXPECT_EQ(cfg.showDurations(), ShowDurations::Always);
}
