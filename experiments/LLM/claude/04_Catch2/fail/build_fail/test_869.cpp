#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_istream.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig with a string stream
class JsonReporterTestFixture_869 : public ::testing::Test {
protected:
    std::stringstream ss;
    std::unique_ptr<JsonReporter> reporter;

    void SetUp() override {
        // We need to create a proper ReporterConfig
        // This requires setting up the necessary infrastructure
    }

    // Helper to create a minimal TestCaseInfo
    static std::unique_ptr<TestCaseInfo> makeTestCaseInfo(const std::string& name) {
        // Create a TestCaseInfo with minimal required fields
        return std::make_unique<TestCaseInfo>(
            ""_sr,    // class name
            NameAndTags{ StringRef(name), "[test]"_sr },
            SourceLineInfo("test_file.cpp", 1)
        );
    }

    // Helper to create TestCaseStats
    static TestCaseStats makeTestCaseStats(const TestCaseInfo& tcInfo,
                                           const Totals& totals,
                                           bool aborting = false) {
        return TestCaseStats(
            tcInfo,
            totals,
            std::string(""),  // stdOut
            std::string(""),  // stdErr
            aborting
        );
    }
};

// Helper class that creates a fully functional JsonReporter for testing
class JsonReporterIntegrationTest_869 : public ::testing::Test {
protected:
    std::ostringstream oss;
    std::unique_ptr<JsonReporter> reporter;

    void SetUp() override {
        auto cfg = new Catch::ConfigData();
        cfg->defaultOutputFilename = "%stdout";
        auto config = std::make_shared<Catch::Config>(*cfg);
        delete cfg;

        // Create a reporter config using the output stream
        Catch::ReporterConfig reporterConfig(
            config.get(),
            Detail::make_unique<Catch::TextStream>(oss),
            Catch::ColourMode::None,
            std::map<std::string, std::string>{}
        );

        reporter = std::make_unique<JsonReporter>(std::move(reporterConfig));
    }
};

} // anonymous namespace

// Test that getDescription returns a non-empty string
TEST(JsonReporterStaticTest_869, GetDescriptionReturnsNonEmpty_869) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test that getDescription returns a consistent value
TEST(JsonReporterStaticTest_869, GetDescriptionIsConsistent_869) {
    std::string desc1 = JsonReporter::getDescription();
    std::string desc2 = JsonReporter::getDescription();
    EXPECT_EQ(desc1, desc2);
}

// Integration-style test: Full test run lifecycle produces valid JSON output
TEST_F(JsonReporterIntegrationTest_869, FullTestRunLifecycleProducesOutput_869) {
    if (!reporter) {
        GTEST_SKIP() << "Reporter could not be created";
    }

    // Start test run
    TestRunInfo runInfo("TestGroup"_sr);
    reporter->testRunStarting(runInfo);

    // Create a test case
    auto tcInfo = std::make_unique<TestCaseInfo>(
        ""_sr,
        NameAndTags{"TestCase1"_sr, "[tag]"_sr},
        SourceLineInfo("file.cpp", 10)
    );

    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    // Create totals
    Totals totals;
    totals.assertions.passed = 1;
    totals.assertions.failed = 0;

    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);

    // End test run
    Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test: testCaseEnded with aborting flag set to true
TEST_F(JsonReporterIntegrationTest_869, TestCaseEndedWithAborting_869) {
    if (!reporter) {
        GTEST_SKIP() << "Reporter could not be created";
    }

    TestRunInfo runInfo("TestGroup"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = std::make_unique<TestCaseInfo>(
        ""_sr,
        NameAndTags{"AbortingTest"_sr, "[tag]"_sr},
        SourceLineInfo("file.cpp", 20)
    );

    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 1;

    TestCaseStats tcStats(*tcInfo, totals, "", "", true);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);

    Totals runTotals;
    runTotals.assertions.failed = 1;
    runTotals.testCases.failed = 1;
    TestRunStats runStats(runInfo, runTotals, true);
    reporter->testRunEnded(runStats);

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test: testCaseEnded with zero assertions
TEST_F(JsonReporterIntegrationTest_869, TestCaseEndedWithZeroAssertions_869) {
    if (!reporter) {
        GTEST_SKIP() << "Reporter could not be created";
    }

    TestRunInfo runInfo("TestGroup"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = std::make_unique<TestCaseInfo>(
        ""_sr,
        NameAndTags{"EmptyTest"_sr, "[tag]"_sr},
        SourceLineInfo("file.cpp", 30)
    );

    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    Totals totals;
    // Zero assertions

    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);

    Totals runTotals;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // The output should contain "totals" and "assertions"
    EXPECT_NE(output.find("totals"), std::string::npos);
    EXPECT_NE(output.find("assertions"), std::string::npos);
}

// Test: Multiple test cases in sequence
TEST_F(JsonReporterIntegrationTest_869, MultipleTestCasesInSequence_869) {
    if (!reporter) {
        GTEST_SKIP() << "Reporter could not be created";
    }

    TestRunInfo runInfo("TestGroup"_sr);
    reporter->testRunStarting(runInfo);

    // First test case
    auto tcInfo1 = std::make_unique<TestCaseInfo>(
        ""_sr,
        NameAndTags{"Test1"_sr, "[tag1]"_sr},
        SourceLineInfo("file.cpp", 10)
    );

    reporter->testCaseStarting(*tcInfo1);
    reporter->testCasePartialStarting(*tcInfo1, 0);

    Totals totals1;
    totals1.assertions.passed = 3;

    TestCaseStats tcStats1(*tcInfo1, totals1, "", "", false);
    reporter->testCasePartialEnded(tcStats1, 0);
    reporter->testCaseEnded(tcStats1);

    // Second test case
    auto tcInfo2 = std::make_unique<TestCaseInfo>(
        ""_sr,
        NameAndTags{"Test2"_sr, "[tag2]"_sr},
        SourceLineInfo("file.cpp", 20)
    );

    reporter->testCaseStarting(*tcInfo2);
    reporter->testCasePartialStarting(*tcInfo2, 0);

    Totals totals2;
    totals2.assertions.passed = 2;
    totals2.assertions.failed = 1;

    TestCaseStats tcStats2(*tcInfo2, totals2, "", "", false);
    reporter->testCasePartialEnded(tcStats2, 0);
    reporter->testCaseEnded(tcStats2);

    Totals runTotals;
    runTotals.assertions.passed = 5;
    runTotals.assertions.failed = 1;
    runTotals.testCases.passed = 1;
    runTotals.testCases.failed = 1;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test: testCaseEnded with stdout and stderr output
TEST_F(JsonReporterIntegrationTest_869, TestCaseEndedWithStdOutAndStdErr_869) {
    if (!reporter) {
        GTEST_SKIP() << "Reporter could not be created";
    }

    TestRunInfo runInfo("TestGroup"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = std::make_unique<TestCaseInfo>(
        ""_sr,
        NameAndTags{"OutputTest"_sr, "[tag]"_sr},
        SourceLineInfo("file.cpp", 40)
    );

    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    Totals totals;
    totals.assertions.passed = 1;

    std::string stdOut = "Hello stdout";
    std::string stdErr = "Hello stderr";
    TestCaseStats tcStats(*tcInfo, totals, std::move(stdOut), std::move(stdErr), false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);

    Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test: Output contains JSON-like structure with totals
TEST_F(JsonReporterIntegrationTest_869, OutputContainsTotalsSection_869) {
    if (!reporter) {
        GTEST_SKIP() << "Reporter could not be created";
    }

    TestRunInfo runInfo("TestGroup"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = std::make_unique<TestCaseInfo>(
        ""_sr,
        NameAndTags{"TotalsTest"_sr, "[tag]"_sr},
        SourceLineInfo("file.cpp", 50)
    );

    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 2;
    totals.assertions.failedButOk = 1;

    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);

    Totals runTotals = totals;
    runTotals.testCases.passed = 0;
    runTotals.testCases.failed = 1;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    std::string output = oss.str();
    // Verify key JSON elements are present
    EXPECT_NE(output.find("totals"), std::string::npos);
    EXPECT_NE(output.find("assertions"), std::string::npos);
}

// Test: Test case with sections
TEST_F(JsonReporterIntegrationTest_869, TestCaseWithSections_869) {
    if (!reporter) {
        GTEST_SKIP() << "Reporter could not be created";
    }

    TestRunInfo runInfo("TestGroup"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = std::make_unique<TestCaseInfo>(
        ""_sr,
        NameAndTags{"SectionTest"_sr, "[tag]"_sr},
        SourceLineInfo("file.cpp", 60)
    );

    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 61), "Section1"_sr);
    reporter->sectionStarting(sectionInfo);

    Counts sectionAssertions;
    sectionAssertions.passed = 2;
    SectionStats sectionStats(sectionInfo, {sectionAssertions, {}}, 0.5, false);
    reporter->sectionEnded(sectionStats);

    Totals totals;
    totals.assertions.passed = 2;

    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter->testCasePartialEnded(tcStats, 0);
    reporter->testCaseEnded(tcStats);

    Totals runTotals;
    runTotals.assertions.passed = 2;
    runTotals.testCases.passed = 1;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}
