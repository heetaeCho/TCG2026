// File: tests/teamcity_reporter_constructor_1087_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the provided interfaces (paths mirror your partial code)
#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using namespace Catch;

namespace {

// Simple helper to construct a ReporterConfig without assuming internal details.
// We pass nullptrs/empty values where allowed by the interface, because the test
// only observes reporter preferences via getPreferences().
ReporterConfig MakeConfig() {
    // Note: ColourMode enum values are not required by the test; use 0 safely.
    return ReporterConfig(
        /*_fullConfig*/ static_cast<IConfig const*>(nullptr),
        /*_stream   */ Detail::unique_ptr<IStream>{}, // empty stream
        /*colourMode*/ static_cast<ColourMode>(0),
        /*customOptions*/ {}
    );
}

struct TeamCityReporterTest_1087 : public ::testing::Test {};

} // namespace

// [Normal operation] Constructing TeamCityReporter should set stdout redirection.
TEST_F(TeamCityReporterTest_1087, Constructor_SetsShouldRedirectStdOutTrue_1087) {
    TeamCityReporter reporter{ MakeConfig() };
    const ReporterPreferences& prefs = reporter.getPreferences();

    // Observable behavior: TeamCityReporter constructor requests stdout redirection.
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
}

// [Boundary/negative check] Constructor should not enable reporting all assertions
// unless explicitly done elsewhere (default is false per interface).
TEST_F(TeamCityReporterTest_1087, Constructor_DoesNotEnableReportAllAssertions_1087) {
    TeamCityReporter reporter{ MakeConfig() };
    const ReporterPreferences& prefs = reporter.getPreferences();

    // Observable behavior: Only stdout redirection is modified; this remains default.
    EXPECT_FALSE(prefs.shouldReportAllAssertions);
}
