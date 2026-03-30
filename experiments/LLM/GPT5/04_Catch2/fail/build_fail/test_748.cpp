// File: tests/reporter_tap_test_run_ended_748.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_tap.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_totals.hpp>

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StartsWith;
using ::testing::HasSubstr;

namespace {

// --- Minimal stream wrapper to capture reporter output -----------------
class OssIStream : public Catch::IStream {
public:
    explicit OssIStream(std::ostream& os) : os_(os) {}
    std::ostream& stream() override { return os_; }
private:
    std::ostream& os_;
};

// --- Very lightweight IConfig mock/stub --------------------------------
// Only methods needed to satisfy pure-virtual requirements should be mocked.
// If your IConfig has more pure virtuals, add MOCK_METHOD stubs returning
// reasonable defaults. Using NiceMock so unmentioned methods (if any) are fine.
class MockConfig : public Catch::IConfig {
public:
    // Provide a name for TestRunInfo, verbosity etc if your build uses them.
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(bool, warningsAsErrors, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(bool, noThrow, (), (const, override));
    MOCK_METHOD(bool, abortAfter, (std::size_t&), (const, override)); // if present in your interface
    // If your Catch2 IConfig is different, add the remaining pure virtuals here,
    // or switch to a concrete Config from your codebase.

    // Some Catch2 versions also require:
    // MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    // MOCK_METHOD(std::string const&, name, (), (const, override));
    // ...and others. Add as needed with harmless returns.
};

// Helper to build a TAPReporter that writes into an ostringstream.
struct TapHarness {
    std::ostringstream oss;
    std::unique_ptr<Catch::IStream> is;     // owned by ReporterConfig
    NiceMock<MockConfig> cfg;               // fullConfig()

    // Build a ReporterConfig consistent with ReporterBase's ctor usage.
    Catch::ReporterConfig makeConfig() {
        // Default harmless expectations for config calls used elsewhere.
        ON_CALL(cfg, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(cfg, warningsAsErrors()).WillByDefault(Return(false));
        ON_CALL(cfg, includeSuccessfulResults()).WillByDefault(Return(true));
        ON_CALL(cfg, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(cfg, allowThrows()).WillByDefault(Return(true));
        // If your interface differs, extend stubs here.

        is = std::make_unique<OssIStream>(oss);
        // ColourMode::None is usually safest for tests.
        return Catch::ReporterConfig(&cfg,
                                     std::move(is),
                                     Catch::ColourMode::None,
                                     Catch::ReporterConfig::CustomOptions{});
    }

    // Convenience to create a fully constructed TAPReporter
    std::unique_ptr<Catch::TAPReporter> makeReporter() {
        return std::make_unique<Catch::TAPReporter>(makeConfig());
    }
};

// Build TestRunStats with specified assertion and test-case totals.
// We only shape *observable* totals; we do not depend on internal counters.
inline Catch::TestRunStats makeRunStats(std::uint64_t assertionsTotal,
                                        std::uint64_t testCasesTotal) {
    Catch::Totals totals;
    // Set the totals in the simplest black-box-safe way: put everything
    // into `passed` so that Counts::total() equals our desired value.
    totals.assertions.passed = assertionsTotal;
    totals.testCases.passed  = testCasesTotal;

    Catch::TestRunInfo runInfo{ "tap-run" };
    return Catch::TestRunStats(runInfo, totals, /*aborting*/false);
}

} // namespace


// ----------------------------------- Tests -----------------------------------

class TAPReporter_testRunEnded_748 : public ::testing::Test {};

// When no tests ran, TAPReporter should append the skipped note after the plan.
TEST_F(TAPReporter_testRunEnded_748, PrintsSkippedNoteWhenNoTestsRan_748) {
    TapHarness h;
    auto rep = h.makeReporter();

    auto stats = makeRunStats(/*assertionsTotal*/ 0, /*testCasesTotal*/ 0);
    rep->testRunEnded(stats);

    const std::string out = h.oss.str();
    // Must start with "1..0"
    EXPECT_THAT(out, StartsWith("1..0"));
    // Must contain the "Skipped" annotation exactly as specified
    EXPECT_THAT(out, HasSubstr(" # Skipped: No tests ran."));
    // Must end the plan line with double newline
    EXPECT_THAT(out, HasSubstr("1..0 # Skipped: No tests ran.\n\n"));
}

// With some tests executed, only the plan should be printed (no skipped note).
TEST_F(TAPReporter_testRunEnded_748, PrintsPlanWithoutSkippedNoteWhenSomeTestsRan_748) {
    TapHarness h;
    auto rep = h.makeReporter();

    auto stats = makeRunStats(/*assertionsTotal*/ 3, /*testCasesTotal*/ 2);
    rep->testRunEnded(stats);

    const std::string out = h.oss.str();
    // Exact plan prefix
    EXPECT_THAT(out, StartsWith("1..3"));
    // Should NOT mention skipped note
    EXPECT_EQ(out.find("# Skipped: No tests ran."), std::string::npos);
    // Double newline after the plan
    EXPECT_THAT(out, HasSubstr("1..3\n\n"));
}

// Large totals are formatted as-is and still followed by a double newline.
TEST_F(TAPReporter_testRunEnded_748, PlanReflectsAssertionTotalAndEndsWithDoubleNewline_748) {
    TapHarness h;
    auto rep = h.makeReporter();

    auto stats = makeRunStats(/*assertionsTotal*/ 123, /*testCasesTotal*/ 1);
    rep->testRunEnded(stats);

    const std::string out = h.oss.str();
    EXPECT_THAT(out, StartsWith("1..123"));
    EXPECT_THAT(out, HasSubstr("\n\n"));
    EXPECT_EQ(out.find("# Skipped: No tests ran."), std::string::npos);
}
