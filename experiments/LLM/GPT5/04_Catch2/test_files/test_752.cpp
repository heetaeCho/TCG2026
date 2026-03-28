// File: tests/junit_reporter_assertionEnded_752_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <vector>
#include <chrono>

// Catch2 public headers used strictly via interface:
#include "catch2/reporters/catch_reporter_junit.hpp"
#include "catch2/catch_test_macros.hpp"                 // for enums/structs used by AssertionInfo
#include "catch2/catch_version.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_timer.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_assertion_result.hpp"

using namespace Catch;
using ::testing::HasSubstr;

// ---- Minimal config stub (black-box, returns safe defaults) -----------------
class StubConfig : public IConfig {
public:
    ~StubConfig() override = default;

    // Reporter prefs used by ReporterBase construction
    ReporterPreferences reporterPreferences() const override {
        ReporterPreferences prefs;
        prefs.shouldRedirectStdOut = false;
        prefs.shouldReportAllAssertions = false;
        return prefs;
    }

    // The rest are harmless defaults; keep them trivially defined.
    bool allowThrows() const override { return true; }
    std::ostream& stream() const override { return std::cout; }
    std::string name() const override { return "stub-config"; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    TestSpec const& testSpec() const override { static TestSpec s; return s; }
    bool hasTestFilters() const override { return false; }
    bool includeSuccessfulResults() const override { return true; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoAssertions() const override { return false; }       // older/newer Catch2 may not have this; remove if not needed
    bool zeroTestsCountAsSuccess() const override { return true; }
    int abortAfter() const override { return 0; }
    bool showDurations() const override { return false; }
    double minDuration() const override { return -1.0; }
    bool debugBrokenAssert() const override { return false; }
    bool useColour() const override { return false; }
    std::uint32_t rngSeed() const override { return 0; }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool benchmarkNoAnalysis() const override { return true; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
    bool skipBenchmarks() const override { return false; }
    bool listReporters() const override { return false; }
    bool listTests() const override { return false; }
    bool listTags() const override { return false; }
    bool listTestNamesOnly() const override { return false; }
    std::string getProcessName() const override { return "proc"; }
    bool allowZeroTests() const override { return true; }
    // If your local Catch2 adds/removes IConfig methods, add trivial overrides here.
};

// ---- Small helpers to drive the reporter lifecycle as a black box ----------

static ReporterConfig MakeReporterConfig(IConfig const* cfg, std::ostream& os) {
    // Colour mode does not affect the XML. Use None.
    return ReporterConfig{ cfg, ColourMode::None, os };
}

static AssertionStats MakeAssertionStats(ResultWas::OfType resultType) {
    // Build minimal AssertionResult via public constructors.
    AssertionInfo info{
        "expr",
        SourceLineInfo{"file.cpp", 123},
        StringRef("REQUIRE"),
        ResultDisposition::Normal
    };

    AssertionResultData data;
    data.m_resultType = resultType;
    // message/expanded expression not needed for this behavior

    AssertionResult result{ info, std::move(data) };

    std::vector<MessageInfo> msgs;
    Totals totals; // unused by assertionEnded, but required by ctor

    return AssertionStats{ result, msgs, totals };
}

static void StartMinimalRun(JunitReporter& rep) {
    // Minimal, observable, black-box lifecycle
    rep.testRunStarting(TestRunInfo{"run"});
    rep.testCaseStarting(TestCaseInfo{
        "tc", // name
        "class", // className
        Tags{}, // tags
        SourceLineInfo{"t.cpp", 1}
    });
}

static void EndMinimalRun(JunitReporter& rep) {
    // Close out the case + run so reporter emits XML
    rep.testCaseEnded(TestCaseStats{
        TestCaseInfo{
            "tc", "class", Tags{}, SourceLineInfo{"t.cpp", 1}
        },
        Totals{}, // totals aren't needed for the errors attribute path we validate
        std::vector<SectionStats>{},
        false // okToFail overall
    });
    rep.testRunEndedCumulative();
}

// ---------- Tests ------------------------------------------------------------

class JunitReporterAssertionEndedTest_752 : public ::testing::Test {
protected:
    StubConfig cfg_;
    std::ostringstream os_;

    std::unique_ptr<JunitReporter> makeReporter() {
        ReporterConfig rc = MakeReporterConfig(&cfg_, os_);
        return std::unique_ptr<JunitReporter>(new JunitReporter(std::move(rc)));
    }
};

// Normal case: non-exception result should NOT increase errors
TEST_F(JunitReporterAssertionEndedTest_752, NonException_DoesNotIncreaseErrors_752) {
    auto rep = makeReporter();
    StartMinimalRun(*rep);

    auto statsOk = MakeAssertionStats(ResultWas::Ok);
    rep->assertionEnded(statsOk);

    EndMinimalRun(*rep);
    const std::string xml = os_.str();

    // Observable: JUnit report produced, and errors attribute remains 0 or absent.
    // Catch2's JUnit reporter writes errors on the <testsuite> element.
    // Accept either explicit errors="0" or absence of the attribute if no errors occurred.
    EXPECT_THAT(xml, HasSubstr("<testsuite"));
    EXPECT_TRUE(xml.find("errors=\"0\"") != std::string::npos ||
                xml.find("errors=") == std::string::npos);
}

// ThrewException should increase errors by 1
TEST_F(JunitReporterAssertionEndedTest_752, ThrewException_IncrementsErrors_752) {
    auto rep = makeReporter();
    StartMinimalRun(*rep);

    auto statsThrow = MakeAssertionStats(ResultWas::ThrewException);
    rep->assertionEnded(statsThrow);

    EndMinimalRun(*rep);
    const std::string xml = os_.str();

    EXPECT_THAT(xml, HasSubstr("<testsuite"));
    // Observable effect: errors count reflects unexpected exception(s)
    EXPECT_THAT(xml, HasSubstr("errors=\"1\""));
}

// Multiple thrown exceptions accumulate
TEST_F(JunitReporterAssertionEndedTest_752, MultipleThrownExceptions_AccumulateErrors_752) {
    auto rep = makeReporter();
    StartMinimalRun(*rep);

    rep->assertionEnded(MakeAssertionStats(ResultWas::ThrewException));
    rep->assertionEnded(MakeAssertionStats(ResultWas::ThrewException));

    EndMinimalRun(*rep);
    const std::string xml = os_.str();

    EXPECT_THAT(xml, HasSubstr("<testsuite"));
    EXPECT_THAT(xml, HasSubstr("errors=\"2\""));
}

// Sanity: even with a failing (non-throw) assertion, no error increment;
// this also exercises that the base path is executed without relying on internals.
TEST_F(JunitReporterAssertionEndedTest_752, NonThrowingFailure_DoesNotCountAsError_752) {
    auto rep = makeReporter();
    StartMinimalRun(*rep);

    rep->assertionEnded(MakeAssertionStats(ResultWas::ExpressionFailed));

    EndMinimalRun(*rep);
    const std::string xml = os_.str();

    EXPECT_THAT(xml, HasSubstr("<testsuite"));
    EXPECT_TRUE(xml.find("errors=\"0\"") != std::string::npos ||
                xml.find("errors=") == std::string::npos);
}
