// File: tests/teamcity_reporter_getdescription_572_tests.cpp
#include <gtest/gtest.h>
#include "catch2/reporters/catch_reporter_teamcity.hpp"

namespace {

using Catch::TeamCityReporter;

// Suite dedicated to testing the public static interface: getDescription()
class TeamCityReporterGetDescription_572 : public ::testing::Test {};

// [Normal operation] It returns the exact, documented description string.
TEST_F(TeamCityReporterGetDescription_572, ReturnsExactDescription_572) {
    const std::string expected = "Reports test results as TeamCity service messages";
    EXPECT_EQ(TeamCityReporter::getDescription(), expected);
}

// [Sanity/boundary] The returned description should be non-empty (basic contract of a description).
TEST_F(TeamCityReporterGetDescription_572, IsNonEmpty_572) {
    const auto desc = TeamCityReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// [Idempotence/consistency] Multiple calls should consistently return the same value.
TEST_F(TeamCityReporterGetDescription_572, MultipleCallsConsistent_572) {
    const auto first  = TeamCityReporter::getDescription();
    const auto second = TeamCityReporter::getDescription();
    EXPECT_EQ(first, second);
}

// [Exception safety] The call should not throw (observable via the public interface).
TEST_F(TeamCityReporterGetDescription_572, NoThrowOnCall_572) {
    EXPECT_NO_THROW({
        auto s = TeamCityReporter::getDescription();
        (void)s; // suppress unused warning
    });
}

} // namespace
