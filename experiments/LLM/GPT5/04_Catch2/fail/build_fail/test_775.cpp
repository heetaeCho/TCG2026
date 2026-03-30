// File: tests/AutomakeReporter_test_775.cpp

#include <gtest/gtest.h>
#include <sstream>

// Catch2 headers — adjust include paths to your tree if needed
#include <catch2/reporters/catch_reporter_automake.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>

using namespace Catch;

namespace {

// A tiny IStream that wraps a provided std::ostream.
class OStringIStream final : public IStream {
public:
    explicit OStringIStream(std::ostream& os) : m_os(os) {}
    std::ostream& stream() override { return m_os; }
private:
    std::ostream& m_os;
};

// Minimal stub config: the reporter base only needs a non-null IConfig*.
// If your codebase already has a handy testing IConfig, replace this.
class DummyConfig : public IConfig {
public:
    ~DummyConfig() override = default;

    // Implement the pure virtuals with benign defaults.
    // Only a very small subset is needed by reporters during construction.
    // NOTE: If your Catch2 version requires more methods, add trivial stubs.
    bool allowThrows() const override { return true; }
    StringRef name() const override { static StringRef n = "dummy"; return n; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }
    bool skipBenchmarks() const override { return true; }
    bool benchmarkNoAnalysis() const override { return true; }
    int benchmarkSamples() const override { return 2; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 1; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
    Verbosity verbosity() const override { return Verbosity::Quiet; }
    bool includeSuccessfulResults() const override { return false; }
    bool shouldReportAllAssertions() const override { return false; }
    bool runsHiddenTests() const override { return false; }
    bool allowZeroTests() const override { return true; }
    ShowDurations::OrNot showDurations() const override { return ShowDurations::OrNot::DefaultForReporter; }
    double minDuration() const override { return -1.0; }
    TestSpec const& testSpec() const override { static TestSpec s; return s; }
    std::vector<std::string> const& getSkipExtracts() const override { static std::vector<std::string> v; return v; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    ColourMode colourMode() const override { return ColourMode::None; }
    bool labelEmptyTests() const override { return false; }
    // For completeness; some versions may need this:
    bool hasEnabledCucumberMode() const override { return false; }
};

// Helper to build a TestCaseInfo with just a name.
// If your codebase already has a factory for this, prefer that.
static TestCaseInfo makeTestCaseInfo(const std::string& name) {
    NameAndTags nat{ name, {} };
    SourceLineInfo sli{ "dummy.cpp", 1 };
    return TestCaseInfo{ StringRef{}, nat, sli };
}

// Helper to assemble TestCaseStats quickly
static TestCaseStats makeStats(const std::string& name,
                               const Totals& totals,
                               std::string out = {},
                               std::string err = {},
                               bool aborting = false) {
    // Important: TestCaseStats stores a pointer to the TestCaseInfo,
    // so the TestCaseInfo must outlive the TestCaseStats.
    // We'll keep it static per unique name for simplicity in these tests.
    // (OK for unit tests; swap to a fixture-managed store if you prefer.)
    static std::vector<std::unique_ptr<TestCaseInfo>> store;
    store.emplace_back(std::make_unique<TestCaseInfo>(makeTestCaseInfo(name)));
    return TestCaseStats{ *store.back(), totals, std::move(out), std::move(err), aborting };
}

// Build a reporter that writes into `oss`.
static std::unique_ptr<AutomakeReporter> makeReporter(std::ostringstream& oss) {
    auto cfg = std::make_unique<DummyConfig>();
    auto istream = Detail::make_unique<OStringIStream>(oss);

    // ReporterConfig usually has a constructor like:
    // ReporterConfig(IConfig const* fullConfig,
    //                Detail::unique_ptr<IStream>&& stream,
    //                ColourMode colourMode,
    //                std::map<std::string, std::string> customOptions = {})
    ReporterConfig rcfg{ cfg.get(), std::move(istream), ColourMode::None, {} };

    // We must keep DummyConfig alive; store it in a static so the pointer
    // inside ReporterBase/IEventListener remains valid for the reporter lifetime.
    static std::vector<std::unique_ptr<DummyConfig>> keepAlive;
    keepAlive.emplace_back(std::move(cfg));

    return std::make_unique<AutomakeReporter>(std::move(rcfg));
}

} // namespace

class AutomakeReporterTest_775 : public ::testing::Test {
protected:
    std::ostringstream oss;
    std::unique_ptr<AutomakeReporter> reporter;

    void SetUp() override {
        reporter = makeReporter(oss);
    }
};

// --- Tests ---

TEST_F(AutomakeReporterTest_775, PrintsSKIPWhenTestCaseTotalsIndicateSkipped_775) {
    Totals totals;
    totals.testCases.skipped = 1; // SKIP takes precedence over assertion status
    totals.assertions.passed = 0;
    totals.assertions.failed = 1; // even with failures, branch should pick SKIP

    auto stats = makeStats("case_skipped", totals);
    reporter->testCaseEnded(stats);

    EXPECT_EQ(oss.str(), ":test-result: SKIP case_skipped\n");
}

TEST_F(AutomakeReporterTest_775, PrintsPASSWhenAllAssertionsPassed_775) {
    Totals totals;
    totals.testCases.skipped = 0;
    totals.assertions.passed = 3;
    totals.assertions.failed = 0;
    totals.assertions.failedButOk = 0;

    auto stats = makeStats("case_pass", totals);
    reporter->testCaseEnded(stats);

    EXPECT_EQ(oss.str(), ":test-result: PASS case_pass\n");
}

TEST_F(AutomakeReporterTest_775, PrintsXFAILWhenAllOkButNotAllPassed_775) {
    Totals totals;
    totals.testCases.skipped = 0;
    totals.assertions.passed = 0;
    totals.assertions.failed = 0;
    totals.assertions.failedButOk = 2; // “ok” but not “allPassed” -> XFAIL

    auto stats = makeStats("case_xfail", totals);
    reporter->testCaseEnded(stats);

    EXPECT_EQ(oss.str(), ":test-result: XFAIL case_xfail\n");
}

TEST_F(AutomakeReporterTest_775, PrintsFAILOtherwise_775) {
    Totals totals;
    totals.testCases.skipped = 0;
    totals.assertions.passed = 1;
    totals.assertions.failed = 1; // not allOk -> FAIL

    auto stats = makeStats("case_fail", totals);
    reporter->testCaseEnded(stats);

    EXPECT_EQ(oss.str(), ":test-result: FAIL case_fail\n");
}

TEST_F(AutomakeReporterTest_775, PrintsExactFormatPrefixNameAndNewline_775) {
    Totals totals;
    totals.testCases.skipped = 0;
    totals.assertions.passed = 2;
    totals.assertions.failed = 0;
    totals.assertions.failedButOk = 0;

    auto stats = makeStats("이름 포함/space & unicode ✓", totals);
    reporter->testCaseEnded(stats);

    // Verify prefix, single space, test name, and single trailing '\n'
    EXPECT_TRUE(oss.str().rfind(":test-result: PASS 이름 포함/space & unicode ✓\n", 0) == 0)
        << "Unexpected output: [" << oss.str() << "]";
}

