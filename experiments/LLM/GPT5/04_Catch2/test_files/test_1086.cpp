// File: tests/reporter_tap_reporter_tests_1086.cpp

#include <gtest/gtest.h>
#include <memory>
#include <map>
#include <string>

// Catch2 public headers (interfaces only)
#include "Catch2/src/catch2/reporters/catch_reporter_tap.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"

using namespace Catch;

namespace {

// Helper: create a ReporterConfig without depending on specific IConfig/IStream details.
// We purposefully pass nullptr for IConfig* and an empty unique_ptr for IStream,
// and use a trivial ColourMode value without assuming enum members.
inline ReporterConfig makeMinimalConfig() {
    const IConfig* cfg = nullptr;
    Detail::unique_ptr<IStream> stream; // null
    auto colour = static_cast<ColourMode>(0);
    std::map<std::string, std::string> custom;
    return ReporterConfig(cfg, CATCH_MOVE(stream), colour, CATCH_MOVE(custom));
}

} // namespace

// ------------------------- Tests -------------------------

// Verifies that constructing TAPReporter sets the observable preference flag
// `shouldReportAllAssertions` to true, as exposed through getPreferences().
// Also verifies it does not flip shouldRedirectStdOut from its default (false).
TEST(TAPReporterTest_1086, Constructor_SetsShouldReportAllAssertions_1086) {
    TAPReporter reporter{ makeMinimalConfig() };

    const ReporterPreferences& prefs = reporter.getPreferences();

    // Observable behavior: Constructor configures preferences to report all assertions.
    EXPECT_TRUE(prefs.shouldReportAllAssertions);

    // Boundary/consistency check: other preference not mentioned stays at default (false).
    EXPECT_FALSE(prefs.shouldRedirectStdOut);
}

// Verifies that the static description is present (non-empty).
// We do not assume a specific string, only that the reporter provides one.
TEST(TAPReporterTest_1086, GetDescription_ReturnsNonEmptyString_1086) {
    std::string desc = TAPReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}
