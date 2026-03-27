// File: tests/json_reporter_listReporters_874.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <vector>

// Catch2 reporter headers under test
#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/internal/catch_list.hpp"

using ::testing::HasSubstr;

namespace {

// Helper to construct a JsonReporter backed by an ostringstream.
// ReporterConfig's exact signature varies across versions of Catch2;
// the common one takes (IConfig*, ColourMode, std::ostream&).
// We only rely on the observable: the reporter writes to the provided stream.
struct JsonReporterHarness_874 {
    std::ostringstream oss;
    // Minimal shim to build ReporterConfig in typical Catch2 layouts.
    // If your local ReporterConfig differs, adjust the construction here
    // without changing the tests’ expectations.
    Catch::JsonReporter make() {
        // The constructor in the provided header is `JsonReporter(ReporterConfig&&)`.
        // Build a ReporterConfig that uses `oss`.
        Catch::ReporterConfig cfg{ nullptr, Catch::ColourMode::None, oss };
        return Catch::JsonReporter{ std::move(cfg) };
    }
};

} // namespace

// ========== TESTS ==========

TEST(JsonReporter_listReporters_874, WritesEmptyArrayForNoReporters_874) {
    JsonReporterHarness_874 h;
    auto reporter = h.make();

    std::vector<Catch::ReporterDescription> descriptions; // empty
    ASSERT_NO_THROW(reporter.listReporters(descriptions));

    const std::string out = h.oss.str();
    // Observable behavior: should contain a "reporters" array; allow any surrounding JSON.
    EXPECT_THAT(out, HasSubstr("\"reporters\""));
    // Permissive check for an empty array. Some writers add whitespace/newlines.
    EXPECT_TRUE(out.find("[]") != std::string::npos ||
                out.find("[ ]") != std::string::npos);
}

TEST(JsonReporter_listReporters_874, WritesNameAndDescriptionForEachEntry_874) {
    JsonReporterHarness_874 h;
    auto reporter = h.make();

    Catch::ReporterDescription a{};
    a.name = "console";
    a.description = "Standard console reporter";

    Catch::ReporterDescription b{};
    b.name = "compact";
    b.description = "Compact, machine-friendly output";

    std::vector<Catch::ReporterDescription> descriptions{ a, b };

    ASSERT_NO_THROW(reporter.listReporters(descriptions));

    const std::string out = h.oss.str();

    // High-level, observable checks only — keys and values appear somewhere in the JSON.
    EXPECT_THAT(out, HasSubstr("\"reporters\""));

    EXPECT_THAT(out, HasSubstr("\"name\""));
    EXPECT_THAT(out, HasSubstr("\"description\""));

    EXPECT_THAT(out, HasSubstr("\"console\""));
    EXPECT_THAT(out, HasSubstr("\"Standard console reporter\""));

    EXPECT_THAT(out, HasSubstr("\"compact\""));
    EXPECT_THAT(out, HasSubstr("\"Compact, machine-friendly output\""));
}

TEST(JsonReporter_listReporters_874, EscapesSpecialCharactersInFields_874) {
    JsonReporterHarness_874 h;
    auto reporter = h.make();

    Catch::ReporterDescription d{};
    d.name = "json\"writer\n\tv1";
    d.description = "Handles quotes \" and newlines \n and tabs \t";

    std::vector<Catch::ReporterDescription> descriptions{ d };

    ASSERT_NO_THROW(reporter.listReporters(descriptions));

    const std::string out = h.oss.str();

    // We don't assert exact formatting, just that typical special characters are escaped.
    // Look for backslash-escaped quote and 'n' for newline somewhere after keys appear.
    EXPECT_THAT(out, HasSubstr("\"name\""));
    EXPECT_THAT(out, HasSubstr("\\\""));  // escaped double-quote
    EXPECT_THAT(out, HasSubstr("\\n"));   // escaped newline
    EXPECT_THAT(out, HasSubstr("\\t"));   // escaped tab
    EXPECT_THAT(out, HasSubstr("\"description\""));
}

// Notes:
// - We do not mock or access JsonReporter internals (writers, stacks, etc.).
// - We verify only observable behavior through the configured output stream.
// - We avoid asserting exact whitespace/formatting, which is an internal concern.
// - If your environment uses a slightly different ReporterConfig constructor,
//   adapt JsonReporterHarness_874::make() accordingly without changing the tests’ logic.

