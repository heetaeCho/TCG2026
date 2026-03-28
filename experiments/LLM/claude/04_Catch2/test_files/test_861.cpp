#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"

#include <sstream>
#include <memory>

namespace {

// Concrete implementation of CumulativeReporterBase for testing
class TestCumulativeReporter : public Catch::CumulativeReporterBase {
public:
    using CumulativeReporterBase::CumulativeReporterBase;

    int testRunEndedCumulativeCallCount = 0;
    bool testRunEndedCumulativeCalled = false;

    void testRunEndedCumulative() override {
        testRunEndedCumulativeCalled = true;
        testRunEndedCumulativeCallCount++;
    }

    // Required overrides
    std::string getDescription() { return "Test reporter"; }

    // Access m_testRun for verification (it's protected)
    bool hasTestRun() const { return static_cast<bool>(m_testRun); }

    const Catch::TestRunNode* getTestRun() const {
        return m_testRun.get();
    }
};

// Helper to create a ReporterConfig
class CumulativeReporterBaseTest_861 : public ::testing::Test {
protected:
    std::stringstream stream;
    std::unique_ptr<Catch::ConfigData> configData;
    std::unique_ptr<Catch::Config> config;
    std::unique_ptr<TestCumulativeReporter> reporter;

    void SetUp() override {
        configData = std::make_unique<Catch::ConfigData>();
        config = std::make_unique<Catch::Config>(*configData);

        Catch::ReporterConfig reporterConfig(
            config.get(),
            &stream,
            Catch::ColourMode::None,
            {}
        );

        reporter = std::make_unique<TestCumulativeReporter>(CATCH_MOVE(reporterConfig));
    }
};

} // anonymous namespace

// Test that testRunEnded creates a TestRunNode and calls testRunEndedCumulative
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedCreatesTestRunNode_861) {
    Catch::TestRunInfo runInfo("test_group");
    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, false);

    EXPECT_FALSE(reporter->hasTestRun());

    reporter->testRunEnded(stats);

    EXPECT_TRUE(reporter->hasTestRun());
}

// Test that testRunEndedCumulative virtual method is called
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedCallsTestRunEndedCumulative_861) {
    Catch::TestRunInfo runInfo("test_group");
    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, false);

    EXPECT_FALSE(reporter->testRunEndedCumulativeCalled);

    reporter->testRunEnded(stats);

    EXPECT_TRUE(reporter->testRunEndedCumulativeCalled);
    EXPECT_EQ(reporter->testRunEndedCumulativeCallCount, 1);
}

// Test that the TestRunNode stores the correct stats values
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedStoresCorrectStats_861) {
    Catch::TestRunInfo runInfo("my_test_run");
    Catch::Totals totals;
    totals.assertions.passed = 10;
    totals.assertions.failed = 2;
    Catch::TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    ASSERT_TRUE(reporter->hasTestRun());
    const auto* testRun = reporter->getTestRun();
    ASSERT_NE(testRun, nullptr);
    EXPECT_EQ(testRun->value.totals.assertions.passed, 10u);
    EXPECT_EQ(testRun->value.totals.assertions.failed, 2u);
    EXPECT_FALSE(testRun->value.aborting);
}

// Test with aborting flag set to true
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedWithAbortingTrue_861) {
    Catch::TestRunInfo runInfo("aborting_run");
    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, true);

    reporter->testRunEnded(stats);

    ASSERT_TRUE(reporter->hasTestRun());
    const auto* testRun = reporter->getTestRun();
    ASSERT_NE(testRun, nullptr);
    EXPECT_TRUE(testRun->value.aborting);
}

// Test that the TestRunNode's children vector is populated (initially empty when no test cases)
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedWithNoTestCasesHasEmptyChildren_861) {
    Catch::TestRunInfo runInfo("empty_run");
    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    ASSERT_TRUE(reporter->hasTestRun());
    const auto* testRun = reporter->getTestRun();
    ASSERT_NE(testRun, nullptr);
    EXPECT_TRUE(testRun->children.empty());
}

// Test that zero totals are stored correctly
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedWithZeroTotals_861) {
    Catch::TestRunInfo runInfo("zero_totals_run");
    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    ASSERT_TRUE(reporter->hasTestRun());
    const auto* testRun = reporter->getTestRun();
    EXPECT_EQ(testRun->value.totals.assertions.passed, 0u);
    EXPECT_EQ(testRun->value.totals.assertions.failed, 0u);
    EXPECT_EQ(testRun->value.totals.testCases.passed, 0u);
    EXPECT_EQ(testRun->value.totals.testCases.failed, 0u);
}

// Test that the run info name is preserved
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedPreservesRunInfoName_861) {
    std::string runName = "specific_test_run_name";
    Catch::TestRunInfo runInfo(runName);
    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    ASSERT_TRUE(reporter->hasTestRun());
    const auto* testRun = reporter->getTestRun();
    ASSERT_NE(testRun, nullptr);
    EXPECT_EQ(testRun->value.runInfo.name, runName);
}

// Test that calling testRunEnded twice triggers assertion failure (death test)
// This tests the assert(!m_testRun) condition
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedCalledTwiceCausesAssertion_861) {
    Catch::TestRunInfo runInfo("test_group");
    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    // Second call should trigger assert
    EXPECT_DEATH({
        reporter->testRunEnded(stats);
    }, "");
}

// Test with a complete flow: testCaseStarting, sectionStarting, etc., then testRunEnded
TEST_F(CumulativeReporterBaseTest_861, TestRunEndedAfterTestCaseFlow_861) {
    // Start a test run
    Catch::TestRunInfo runInfo("integration_run");
    reporter->testRunStarting(runInfo);

    // Create and run a test case
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "test_class", {"test_case_1", "[tag1]"}, {__FILE__, static_cast<std::size_t>(__LINE__)}
    );

    reporter->testCaseStarting(*testCaseInfo);

    Catch::SectionInfo sectionInfo("", "root_section");
    reporter->sectionStarting(sectionInfo);

    Catch::Counts assertions;
    assertions.passed = 1;
    Catch::SectionStats sectionStats(sectionInfo, assertions, 0.1, false);
    reporter->sectionEnded(sectionStats);

    Catch::Totals testCaseTotals;
    testCaseTotals.assertions.passed = 1;
    Catch::TestCaseStats testCaseStats(*testCaseInfo, testCaseTotals, "", "", false);
    reporter->testCaseEnded(testCaseStats);

    // Now end the test run
    Catch::Totals runTotals;
    runTotals.assertions.passed = 1;
    runTotals.testCases.passed = 1;
    Catch::TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    EXPECT_TRUE(reporter->hasTestRun());
    EXPECT_TRUE(reporter->testRunEndedCumulativeCalled);

    const auto* testRun = reporter->getTestRun();
    ASSERT_NE(testRun, nullptr);
    // After the flow, there should be test case children
    EXPECT_FALSE(testRun->children.empty());
}

// Test various no-op methods don't affect testRunEnded behavior
TEST_F(CumulativeReporterBaseTest_861, NoOpMethodsDontAffectTestRunEnded_861) {
    reporter->noMatchingTestCases("pattern");
    reporter->reportInvalidTestSpec("bad spec");
    reporter->fatalErrorEncountered("fatal error");
    reporter->benchmarkPreparing("bench");

    Catch::TestRunInfo runInfo("noops_run");
    Catch::Totals totals;
    totals.assertions.passed = 5;
    Catch::TestRunStats stats(runInfo, totals, false);

    reporter->testRunEnded(stats);

    EXPECT_TRUE(reporter->hasTestRun());
    EXPECT_TRUE(reporter->testRunEndedCumulativeCalled);
    EXPECT_EQ(reporter->getTestRun()->value.totals.assertions.passed, 5u);
}
