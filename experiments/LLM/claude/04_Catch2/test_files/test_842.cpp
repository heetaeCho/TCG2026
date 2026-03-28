#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

using namespace Catch;

namespace {

// Helper to create a minimal ReporterConfig with a given ostream
class XmlReporterTestFixture_842 : public ::testing::Test {
protected:
    std::stringstream m_stream;

    std::unique_ptr<XmlReporter> createReporter() {
        auto config = Catch::ConfigData{};
        auto catchConfig = std::make_shared<Catch::Config>(config);
        auto reporterConfig = ReporterConfig(catchConfig.get(), m_stream, Catch::ColourMode::None, {});
        auto reporter = std::make_unique<XmlReporter>(CATCH_MOVE(reporterConfig));
        m_config = catchConfig; // prevent destruction
        return reporter;
    }

    void startTestRun(XmlReporter& reporter) {
        TestRunInfo runInfo("test_run"_sr);
        reporter.testRunStarting(runInfo);
    }

    std::shared_ptr<Catch::Config> m_config;
};

} // anonymous namespace

TEST_F(XmlReporterTestFixture_842, TestRunEndedWritesOverallResults_842) {
    auto reporter = createReporter();
    startTestRun(*reporter);

    Totals totals;
    totals.assertions.passed = 10;
    totals.assertions.failed = 2;
    totals.assertions.failedButOk = 1;
    totals.assertions.skipped = 3;
    totals.testCases.passed = 5;
    totals.testCases.failed = 1;
    totals.testCases.failedButOk = 0;
    totals.testCases.skipped = 2;

    TestRunInfo runInfo("test_run"_sr);
    TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    std::string output = m_stream.str();

    // Check that OverallResults element is present with correct assertion attributes
    EXPECT_NE(output.find("OverallResults"), std::string::npos);
    EXPECT_NE(output.find("successes=\"10\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"2\""), std::string::npos);
    EXPECT_NE(output.find("expectedFailures=\"1\""), std::string::npos);
    EXPECT_NE(output.find("skips=\"3\""), std::string::npos);

    // Check that OverallResultsCases element is present with correct test case attributes
    EXPECT_NE(output.find("OverallResultsCases"), std::string::npos);
    EXPECT_NE(output.find("successes=\"5\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"1\""), std::string::npos);
}

TEST_F(XmlReporterTestFixture_842, TestRunEndedWithZeroTotals_842) {
    auto reporter = createReporter();
    startTestRun(*reporter);

    Totals totals;
    // All zeros by default

    TestRunInfo runInfo("empty_run"_sr);
    TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    std::string output = m_stream.str();

    EXPECT_NE(output.find("OverallResults"), std::string::npos);
    EXPECT_NE(output.find("OverallResultsCases"), std::string::npos);
    EXPECT_NE(output.find("successes=\"0\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"0\""), std::string::npos);
    EXPECT_NE(output.find("expectedFailures=\"0\""), std::string::npos);
    EXPECT_NE(output.find("skips=\"0\""), std::string::npos);
}

TEST_F(XmlReporterTestFixture_842, TestRunEndedWithLargeNumbers_842) {
    auto reporter = createReporter();
    startTestRun(*reporter);

    Totals totals;
    totals.assertions.passed = 1000000;
    totals.assertions.failed = 999999;
    totals.assertions.failedButOk = 500000;
    totals.assertions.skipped = 250000;
    totals.testCases.passed = 100000;
    totals.testCases.failed = 50000;
    totals.testCases.failedButOk = 25000;
    totals.testCases.skipped = 12500;

    TestRunInfo runInfo("large_run"_sr);
    TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    std::string output = m_stream.str();

    EXPECT_NE(output.find("successes=\"1000000\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"999999\""), std::string::npos);
    EXPECT_NE(output.find("expectedFailures=\"500000\""), std::string::npos);
    EXPECT_NE(output.find("skips=\"250000\""), std::string::npos);
    EXPECT_NE(output.find("successes=\"100000\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"50000\""), std::string::npos);
    EXPECT_NE(output.find("expectedFailures=\"25000\""), std::string::npos);
    EXPECT_NE(output.find("skips=\"12500\""), std::string::npos);
}

TEST_F(XmlReporterTestFixture_842, TestRunEndedWithAbortingTrue_842) {
    auto reporter = createReporter();
    startTestRun(*reporter);

    Totals totals;
    totals.assertions.passed = 3;
    totals.assertions.failed = 1;
    totals.testCases.passed = 2;
    totals.testCases.failed = 1;

    TestRunInfo runInfo("aborted_run"_sr);
    TestRunStats stats(runInfo, totals, true);

    reporter->testRunEnded(stats);

    std::string output = m_stream.str();

    // Even with aborting=true, the XML output should still contain the results
    EXPECT_NE(output.find("OverallResults"), std::string::npos);
    EXPECT_NE(output.find("OverallResultsCases"), std::string::npos);
    EXPECT_NE(output.find("successes=\"3\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"1\""), std::string::npos);
}

TEST_F(XmlReporterTestFixture_842, TestRunEndedOnlyFailures_842) {
    auto reporter = createReporter();
    startTestRun(*reporter);

    Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 5;
    totals.assertions.failedButOk = 0;
    totals.assertions.skipped = 0;
    totals.testCases.passed = 0;
    totals.testCases.failed = 3;
    totals.testCases.failedButOk = 0;
    totals.testCases.skipped = 0;

    TestRunInfo runInfo("failure_run"_sr);
    TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    std::string output = m_stream.str();

    // OverallResults assertions
    EXPECT_NE(output.find("OverallResults"), std::string::npos);
    // Verify the XML structure contains both elements distinctly
    size_t overallResultsPos = output.find("OverallResults");
    size_t overallResultsCasesPos = output.find("OverallResultsCases");
    EXPECT_NE(overallResultsPos, std::string::npos);
    EXPECT_NE(overallResultsCasesPos, std::string::npos);
    EXPECT_LT(overallResultsPos, overallResultsCasesPos);
}

TEST_F(XmlReporterTestFixture_842, TestRunEndedOnlySkipped_842) {
    auto reporter = createReporter();
    startTestRun(*reporter);

    Totals totals;
    totals.assertions.skipped = 10;
    totals.testCases.skipped = 5;

    TestRunInfo runInfo("skipped_run"_sr);
    TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    std::string output = m_stream.str();

    EXPECT_NE(output.find("OverallResults"), std::string::npos);
    EXPECT_NE(output.find("OverallResultsCases"), std::string::npos);
    EXPECT_NE(output.find("skips=\"10\""), std::string::npos);
    EXPECT_NE(output.find("skips=\"5\""), std::string::npos);
}

TEST_F(XmlReporterTestFixture_842, TestRunEndedOutputIsValidXmlFragment_842) {
    auto reporter = createReporter();
    startTestRun(*reporter);

    Totals totals;
    totals.assertions.passed = 1;
    totals.testCases.passed = 1;

    TestRunInfo runInfo("valid_xml_run"_sr);
    TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    std::string output = m_stream.str();

    // Verify closing tags or self-closing elements exist
    // OverallResults should be a self-closing element or have a closing tag
    bool hasSelfClosingOverallResults =
        output.find("<OverallResults ") != std::string::npos &&
        output.find("/>") != std::string::npos;
    bool hasClosingOverallResults =
        output.find("</OverallResults>") != std::string::npos;
    EXPECT_TRUE(hasSelfClosingOverallResults || hasClosingOverallResults);
}

TEST_F(XmlReporterTestFixture_842, TestRunEndedExpectedFailuresOnly_842) {
    auto reporter = createReporter();
    startTestRun(*reporter);

    Totals totals;
    totals.assertions.failedButOk = 7;
    totals.testCases.failedButOk = 3;

    TestRunInfo runInfo("expected_failures_run"_sr);
    TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    std::string output = m_stream.str();

    EXPECT_NE(output.find("expectedFailures=\"7\""), std::string::npos);
    EXPECT_NE(output.find("expectedFailures=\"3\""), std::string::npos);
}
