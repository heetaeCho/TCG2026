// File: tests/TeamCityReporter_testRunStarting_781.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the real Catch2 headers from your tree.
// Paths might differ in your repo; adjust include paths as needed.
#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/internal/catch_test_run_info.hpp"

// Minimal helper to create a TeamCityReporter that writes into an ostringstream.
// We construct it through ReporterConfig so we don't touch any private state.
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/catch_config.hpp"

namespace {

// A minimal IStream that returns an std::ostream& we own (oss).
struct OStringStreamWrapper : Catch::IStream {
    explicit OStringStreamWrapper(std::ostream& os) : m_os(os) {}
    std::ostream& stream() override { return m_os; }
private:
    std::ostream& m_os;
};

// Create a ReporterConfig that points the reporter to write into `oss`.
// This sticks to public interfaces and avoids any private state.
static Catch::ReporterConfig makeConfigWritingTo(
    std::ostream& oss,
    Catch::IConfig const* fullCfg = nullptr
) {
    // Colour mode and custom options don’t affect this test; use defaults.
    Catch::Detail::unique_ptr<Catch::IStream> wrapped{
        new OStringStreamWrapper(oss)
    };

    // ReporterConfig’s ctor is public API; use it as intended.
    // If your Catch2 version has a slightly different signature, adjust here.
    return Catch::ReporterConfig(
        fullCfg,                              // IConfig (can be nullptr)
        CATCH_MOVE(wrapped),                   // output stream
        Catch::ColourMode::None,               // disable colours
        {}                                     // no custom options
    );
}

} // namespace

// ---------- Test Fixture ----------

class TeamCityReporter_781 : public ::testing::Test {
protected:
    std::ostringstream oss;
    std::unique_ptr<Catch::TeamCityReporter> reporter;

    void SetUp() override {
        auto cfg = makeConfigWritingTo(oss, /*fullCfg*/ nullptr);
        reporter = std::unique_ptr<Catch::TeamCityReporter>(
            new Catch::TeamCityReporter(CATCH_MOVE(cfg))
        );
    }
};

// ---------- Tests ----------
//
// We only assert on observable output. We do *not* assume how `escape(..)` works,
// just that the reporter prints the proper TeamCity service message structure.

// Normal operation: a simple run name is printed in one TC message.
TEST_F(TeamCityReporter_781, TestRunStarting_PrintsTeamCitySuiteStartLine_781) {
    Catch::TestRunInfo info{ Catch::StringRef("AllTests") };

    reporter->testRunStarting(info);

    const std::string out = oss.str();
    // It should produce exactly one line ending with '\n'
    // and follow the TeamCity service message shape.
    EXPECT_FALSE(out.empty());
    EXPECT_EQ(out.back(), '\n');

    // Check prefix/suffix structure without assuming escaping internals.
    const std::string prefix = "##teamcity[testSuiteStarted name='";
    const std::string suffix = "']\n";
    ASSERT_GE(out.size(), prefix.size() + suffix.size());
    EXPECT_EQ(out.substr(0, prefix.size()), prefix);
    EXPECT_EQ(out.substr(out.size() - suffix.size()), suffix);

    // The (possibly escaped) name appears between prefix & suffix.
    const auto middle = out.substr(prefix.size(), out.size() - prefix.size() - suffix.size());
    // We cannot know exact escaping, but for a simple name it should contain "AllTests".
    EXPECT_NE(middle.find("AllTests"), std::string::npos);
}

// Boundary: empty run name prints an empty name field (escaped form may still be empty).
TEST_F(TeamCityReporter_781, TestRunStarting_EmptyName_YieldsEmptyBetweenQuotes_781) {
    Catch::TestRunInfo info{ Catch::StringRef("") };

    reporter->testRunStarting(info);

    const std::string out = oss.str();
    const std::string expectedPrefix = "##teamcity[testSuiteStarted name='";
    const std::string expectedSuffix = "']\n";

    ASSERT_GE(out.size(), expectedPrefix.size() + expectedSuffix.size());
    EXPECT_EQ(out.substr(0, expectedPrefix.size()), expectedPrefix);
    EXPECT_EQ(out.substr(out.size() - expectedSuffix.size()), expectedSuffix);

    // Extract what’s between the quotes.
    const auto between = out.substr(
        expectedPrefix.size(),
        out.size() - expectedPrefix.size() - expectedSuffix.size()
    );
    // Empty input typically stays empty after escaping.
    EXPECT_TRUE(between.empty());
}

// Special characters in name: we don’t assert the *algorithm* of escaping,
// only that the output line is well-formed and contains some representation
// of the provided name (post-escaping) between the quotes.
TEST_F(TeamCityReporter_781, TestRunStarting_NameWithSpecials_WellFormedLineAndContainsName_781) {
    // This includes characters that usually need escaping in service messages.
    const std::string rawName = "proj:core [suite] a'b|c\nd\r";
    Catch::TestRunInfo info{ Catch::StringRef(rawName) };

    reporter->testRunStarting(info);

    const std::string out = oss.str();
    const std::string prefix = "##teamcity[testSuiteStarted name='";
    const std::string suffix = "']\n";

    ASSERT_GE(out.size(), prefix.size() + suffix.size());
    EXPECT_EQ(out.substr(0, prefix.size()), prefix);
    EXPECT_EQ(out.substr(out.size() - suffix.size()), suffix);

    // Extract escaped middle; it should be non-empty even if escape altered it.
    const auto middle = out.substr(prefix.size(), out.size() - prefix.size() - suffix.size());
    EXPECT_FALSE(middle.empty());

    // As a loose observable check, ensure at least a sensible fragment from the input
    // survives in the escaped string (e.g., "proj:core" or "suite").
    // We *do not* assert the exact escaping mechanics.
    EXPECT_TRUE(
        middle.find("proj:core") != std::string::npos ||
        middle.find("suite")     != std::string::npos
    );
}

// Idempotence for single call (no extra noise): call once -> exactly one line produced.
TEST_F(TeamCityReporter_781, TestRunStarting_SingleCall_ExactlyOneLine_781) {
    Catch::TestRunInfo info{ Catch::StringRef("Once") };
    reporter->testRunStarting(info);

    const std::string out = oss.str();
    // Count '\n' occurrences; should be 1.
    size_t newlines = std::count(out.begin(), out.end(), '\n');
    EXPECT_EQ(newlines, 1u);
}

// Multiple calls: each call should append another well-formed line.
TEST_F(TeamCityReporter_781, TestRunStarting_MultipleCalls_AppendsLines_781) {
    reporter->testRunStarting(Catch::TestRunInfo{ Catch::StringRef("Run1") });
    reporter->testRunStarting(Catch::TestRunInfo{ Catch::StringRef("Run2") });

    const std::string out = oss.str();
    // Expect 2 lines ending with \n
    size_t newlines = std::count(out.begin(), out.end(), '\n');
    EXPECT_EQ(newlines, 2u);

    // Both prefixes should appear in order.
    const std::string l1 = "##teamcity[testSuiteStarted name='";
    auto first  = out.find(l1);
    auto second = out.find(l1, first == std::string::npos ? 0 : first + 1);
    EXPECT_NE(first,  std::string::npos);
    EXPECT_NE(second, std::string::npos);
    EXPECT_LT(first, second);
}
