#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_stream.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig with a given ostream
class JsonReporterTestFixture : public ::testing::Test {
protected:
    std::stringstream m_stream;
    std::unique_ptr<JsonReporter> m_reporter;

    void SetUp() override {
        // We need to create a proper ReporterConfig.
        // This requires creating some infrastructure objects.
    }

    // Helper to create a reporter config pointing at our stringstream
    ReporterConfig makeConfig() {
        auto config = std::make_shared<ConfigData>();
        return ReporterConfig(config, m_stream, Catch::ColourMode::None, {});
    }

    void createReporter() {
        m_reporter = std::make_unique<JsonReporter>(makeConfig());
    }

    std::string getOutput() const {
        return m_stream.str();
    }
};

} // anonymous namespace

// Test: getDescription returns a non-empty string
TEST(JsonReporterStaticTest_867, GetDescriptionReturnsNonEmpty_867) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test: Full test run cycle - testRunStarting and testRunEnded produce valid JSON
TEST_F(JsonReporterTestFixture, TestRunStartingAndEnded_867) {
    createReporter();

    TestRunInfo runInfo("test_run");
    m_reporter->testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 1;
    totals.testCases.passed = 3;
    totals.testCases.failed = 0;

    TestRunStats runStats(runInfo, totals, false);
    m_reporter->testRunEnded(runStats);

    std::string output = getOutput();
    // The output should contain JSON with totals information
    EXPECT_NE(output.find("totals"), std::string::npos);
    EXPECT_NE(output.find("assertions"), std::string::npos);
    EXPECT_NE(output.find("test-cases"), std::string::npos);
}

// Test: testRunEnded with zero totals
TEST_F(JsonReporterTestFixture, TestRunEndedZeroTotals_867) {
    createReporter();

    TestRunInfo runInfo("empty_run");
    m_reporter->testRunStarting(runInfo);

    Totals totals;
    // All zeros by default
    TestRunStats runStats(runInfo, totals, false);
    m_reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("totals"), std::string::npos);
    EXPECT_NE(output.find("assertions"), std::string::npos);
    EXPECT_NE(output.find("test-cases"), std::string::npos);
}

// Test: testRunEnded with aborting flag set to true
TEST_F(JsonReporterTestFixture, TestRunEndedAborting_867) {
    createReporter();

    TestRunInfo runInfo("aborting_run");
    m_reporter->testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 2;
    totals.assertions.failed = 3;
    totals.testCases.passed = 1;
    totals.testCases.failed = 2;

    TestRunStats runStats(runInfo, totals, true);
    m_reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("totals"), std::string::npos);
}

// Test: Full lifecycle with test case inside test run
TEST_F(JsonReporterTestFixture, FullLifecycleWithTestCase_867) {
    createReporter();

    TestRunInfo runInfo("full_run");
    m_reporter->testRunStarting(runInfo);

    // Create a minimal test case info
    auto tcInfo = makeTestCaseInfo(
        "test_reporter",
        {"test case 1", "[tag]"},
        SourceLineInfo("file.cpp", 10)
    );

    m_reporter->testCaseStarting(*tcInfo);

    Totals totals;
    totals.assertions.passed = 1;
    totals.testCases.passed = 1;

    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    m_reporter->testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    m_reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("totals"), std::string::npos);
    EXPECT_NE(output.find("assertions"), std::string::npos);
    EXPECT_NE(output.find("test-cases"), std::string::npos);
}

// Test: testRunEnded with large totals values
TEST_F(JsonReporterTestFixture, TestRunEndedLargeTotals_867) {
    createReporter();

    TestRunInfo runInfo("large_totals_run");
    m_reporter->testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 1000000;
    totals.assertions.failed = 500000;
    totals.testCases.passed = 10000;
    totals.testCases.failed = 5000;

    TestRunStats runStats(runInfo, totals, false);
    m_reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("totals"), std::string::npos);
    // Verify the counts appear in the output
    EXPECT_NE(output.find("1000000"), std::string::npos);
    EXPECT_NE(output.find("500000"), std::string::npos);
}

// Test: Output contains passed and failed counts for assertions
TEST_F(JsonReporterTestFixture, OutputContainsAssertionCounts_867) {
    createReporter();

    TestRunInfo runInfo("assertion_counts_run");
    m_reporter->testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 42;
    totals.assertions.failed = 7;
    totals.testCases.passed = 10;
    totals.testCases.failed = 2;

    TestRunStats runStats(runInfo, totals, false);
    m_reporter->testRunEnded(runStats);

    std::string output = getOutput();
    // Should contain the assertion counts somewhere
    EXPECT_NE(output.find("42"), std::string::npos);
    EXPECT_NE(output.find("7"), std::string::npos);
}

// Test: Output contains passed and failed counts for test cases
TEST_F(JsonReporterTestFixture, OutputContainsTestCaseCounts_867) {
    createReporter();

    TestRunInfo runInfo("testcase_counts_run");
    m_reporter->testRunStarting(runInfo);

    Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 0;
    totals.testCases.passed = 99;
    totals.testCases.failed = 1;

    TestRunStats runStats(runInfo, totals, false);
    m_reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("99"), std::string::npos);
}

// Test: Multiple test runs can be serialized (reporter reuse scenario check)
TEST_F(JsonReporterTestFixture, TestRunNameAppearsInOutput_867) {
    createReporter();

    TestRunInfo runInfo("my_special_test_run");
    m_reporter->testRunStarting(runInfo);

    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    m_reporter->testRunEnded(runStats);

    std::string output = getOutput();
    // The run name should appear somewhere in the JSON output
    EXPECT_NE(output.find("my_special_test_run"), std::string::npos);
}
