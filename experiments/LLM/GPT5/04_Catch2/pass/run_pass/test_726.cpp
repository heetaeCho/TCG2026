// TEST_ID: 726

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

namespace {

using Catch::Config;
using Catch::ConfigData;

TEST(ConfigWarnAboutMissingAssertionsTest_726, ReturnsFalse_WhenWarningsIsNothing_726) {
    ConfigData data;
    data.warnings = Catch::WarnAbout::Nothing; // explicit, observable setup
    const Config cfg{data};

    EXPECT_FALSE(cfg.warnAboutMissingAssertions());
}

TEST(ConfigWarnAboutMissingAssertionsTest_726, ReturnsTrue_WhenNoAssertionsBitSet_726) {
    ConfigData data;
    data.warnings = Catch::WarnAbout::NoAssertions; // only this bit set
    const Config cfg{data};

    EXPECT_TRUE(cfg.warnAboutMissingAssertions());
}

TEST(ConfigWarnAboutMissingAssertionsTest_726, ReturnsFalse_WhenUnmatchedTestSpecOnly_726) {
    ConfigData data;
    data.warnings = Catch::WarnAbout::UnmatchedTestSpec; // different bit, NoAssertions not set
    const Config cfg{data};

    EXPECT_FALSE(cfg.warnAboutMissingAssertions());
}

TEST(ConfigWarnAboutMissingAssertionsTest_726, ReturnsTrue_WhenMultipleWarningsIncludeNoAssertions_726) {
    ConfigData data;
    data.warnings = static_cast<Catch::WarnAbout::What>(
        Catch::WarnAbout::NoAssertions | Catch::WarnAbout::UnmatchedTestSpec
    ); // multiple bits, includes NoAssertions
    const Config cfg{data};

    EXPECT_TRUE(cfg.warnAboutMissingAssertions());
}

} // namespace
