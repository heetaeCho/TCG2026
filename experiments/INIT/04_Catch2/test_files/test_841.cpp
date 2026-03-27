// File: tests/XmlReporter_testCaseEnded_841.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 headers (paths per prompt)
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_totals.hpp"

using ::testing::_;
using ::testing::Return;

namespace {

// Minimal mock for IConfig – we only care about showDurations()
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    // All other virtuals are non-pure in the provided interface; we inherit defaults.
};

// Helper to build Totals with assertion counts
static Catch::Totals makeTotals(uint64_t passed, uint64_t failed, uint64_t failedButOk, uint64_t skipped) {
    Catch::Totals t;
    t.assertions.passed      = passed;
    t.assertions.failed      = failed;
    t.assertions.failedButOk = failedButOk;
    t.assertions.skipped     = skipped;
    return t;
}

// Lightweight helper to create TestCaseStats without relying on internal behavior.
// The method under test uses: totals, stdOut, stdErr (and ignores testInfo contents).
static Catch::TestCaseStats makeStats(const Catch::Totals& totals,
                                      const std::string& out,
                                      const std::string& err) {
    // Build a dummy TestCaseInfo that is valid but not used by testCaseEnded body.
    // Catch2's TestCaseInfo usually requires a real object; here we create a trivial one
    // through any available constructor in your codebase. If your TestCaseInfo requires
    // more fields, provide a minimal valid instance from your test helpers.
    static Catch::TestCaseInfo dummyInfo{ "dummy"_sr, Catch::SourceLineInfo{ "dummy.cpp", 1 }, {}, {} };

    return Catch::TestCaseStats{ dummyInfo, totals, std::string(out), std::string(err), false };
}

} // namespace

// ========== Tests ==========

// Verifies that <OverallResult> has success/skips attributes based on totals.
// TEST_ID: 841
TEST(XmlReporter_testCaseEnded_841, WritesSuccessAndSkipsAttributes_841) {
    using namespace Catch;

    ::testing::NiceMock<MockConfig> config;
    EXPECT_CALL(config, showDurations()).WillRepeatedly(Return(ShowDurations::Never));

    std::ostringstream oss;
    ReporterConfig rc{ &config, oss };

    XmlReporter reporter{ ReporterConfig{ &config, oss } };

    // Case A: all OK (no failures) -> success="true", skips="1"
    auto totals_ok = makeTotals(/*passed*/2, /*failed*/0, /*fbo*/0, /*skipped*/1);
    auto stats_ok  = makeStats(totals_ok, "", "");
    reporter.testCaseEnded(stats_ok);

    std::string xml = oss.str();
    EXPECT_THAT(xml, ::testing::HasSubstr("<OverallResult"));
    EXPECT_THAT(xml, ::testing::HasSubstr("success=\"true\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("skips=\"1\""));

    // Reset stream for second scenario
    oss.str("");
    oss.clear();

    // Case B: has failures -> success="false", skips="0"
    auto totals_fail = makeTotals(/*passed*/1, /*failed*/1, /*fbo*/0, /*skipped*/0);
    auto stats_fail  = makeStats(totals_fail, "", "");
    reporter.testCaseEnded(stats_fail);

    xml = oss.str();
    EXPECT_THAT(xml, ::testing::HasSubstr("<OverallResult"));
    EXPECT_THAT(xml, ::testing::HasSubstr("success=\"false\""));
    EXPECT_THAT(xml, ::testing::HasSubstr("skips=\"0\""));
}

// Verifies that durationInSeconds is written only when ShowDurations::Always.
// TEST_ID: 841
TEST(XmlReporter_testCaseEnded_841, WritesDurationOnlyWhenAlways_841) {
    using namespace Catch;

    std::ostringstream oss;

    // A) Never => no durationInSeconds attribute
    {
        ::testing::NiceMock<MockConfig> cfgNever;
        EXPECT_CALL(cfgNever, showDurations()).WillRepeatedly(Return(ShowDurations::Never));

        XmlReporter reporter{ ReporterConfig{ &cfgNever, oss } };
        auto totals = makeTotals(1, 0, 0, 0);
        reporter.testCaseEnded(makeStats(totals, "", ""));

        const std::string xml = oss.str();
        EXPECT_THAT(xml, ::testing::HasSubstr("<OverallResult"));
        EXPECT_THAT(xml, ::testing::Not(::testing::HasSubstr("durationInSeconds")));
    }

    // Clear stream
    oss.str(""); oss.clear();

    // B) Always => durationInSeconds attribute present (value unspecified)
    {
        ::testing::NiceMock<MockConfig> cfgAlways;
        EXPECT_CALL(cfgAlways, showDurations()).WillRepeatedly(Return(ShowDurations::Always));

        XmlReporter reporter{ ReporterConfig{ &cfgAlways, oss } };
        auto totals = makeTotals(1, 0, 0, 0);
        reporter.testCaseEnded(makeStats(totals, "", ""));

        const std::string xml = oss.str();
        EXPECT_THAT(xml, ::testing::HasSubstr("<OverallResult"));
        EXPECT_THAT(xml, ::testing::HasSubstr("durationInSeconds="));
    }
}

// Verifies that StdOut/StdErr elements are emitted when non-empty and trimmed.
// TEST_ID: 841
TEST(XmlReporter_testCaseEnded_841, EmitsStdOutAndStdErrWhenPresent_841) {
    using namespace Catch;

    ::testing::NiceMock<MockConfig> config;
    EXPECT_CALL(config, showDurations()).WillRepeatedly(Return(ShowDurations::Never));

    std::ostringstream oss;
    XmlReporter reporter{ ReporterConfig{ &config, oss } };

    auto totals = makeTotals(1, 0, 0, 0);

    // Include leading/trailing whitespace to verify trimming behavior
    std::string out = "  line from stdout \n";
    std::string err = "\n  line from stderr  ";
    reporter.testCaseEnded(makeStats(totals, out, err));

    const std::string xml = oss.str();
    // Presence of elements
    EXPECT_THAT(xml, ::testing::HasSubstr("<StdOut>"));
    EXPECT_THAT(xml, ::testing::HasSubstr("</StdOut>"));
    EXPECT_THAT(xml, ::testing::HasSubstr("<StdErr>"));
    EXPECT_THAT(xml, ::testing::HasSubstr("</StdErr>"));

    // Basic trimming check: the inner text should not contain the leading/trailing spaces/newlines we added.
    // (Exact whitespace/newlines around tags may differ; we only check interior text.)
    EXPECT_THAT(xml, ::testing::HasSubstr("<StdOut>line from stdout</StdOut>"));
    EXPECT_THAT(xml, ::testing::HasSubstr("<StdErr>line from stderr</StdErr>"));
}

// Verifies that StdOut/StdErr elements are NOT emitted when empty.
// TEST_ID: 841
TEST(XmlReporter_testCaseEnded_841, DoesNotEmitStdOutOrStdErrWhenEmpty_841) {
    using namespace Catch;

    ::testing::NiceMock<MockConfig> config;
    EXPECT_CALL(config, showDurations()).WillRepeatedly(Return(ShowDurations::Never));

    std::ostringstream oss;
    XmlReporter reporter{ ReporterConfig{ &config, oss } };

    auto totals = makeTotals(1, 0, 0, 0);
    reporter.testCaseEnded(makeStats(totals, /*out*/"", /*err*/""));

    const std::string xml = oss.str();
    EXPECT_THAT(xml, ::testing::Not(::testing::HasSubstr("<StdOut>")));
    EXPECT_THAT(xml, ::testing::Not(::testing::HasSubstr("<StdErr>")));
}

