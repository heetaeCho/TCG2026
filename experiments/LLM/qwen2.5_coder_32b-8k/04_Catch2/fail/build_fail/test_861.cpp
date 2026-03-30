#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_cumulative_base.hpp"



using namespace Catch;



// Mock class to inherit from CumulativeReporterBase for testing purposes

class MockCumulativeReporter : public CumulativeReporterBase {

public:

    using CumulativeReporterBase::CumulativeReporterBase;

    MOCK_METHOD(void, testRunEndedCumulative, (), (override));

};



// Fixture class for tests

class CumulativeReporterBaseTest_861 : public ::testing::Test {

protected:

    MockCumulativeReporter reporter;

    TestRunInfo runInfo;

    Totals totals;

    bool aborting = false;



    CumulativeReporterBaseTest_861()

        : reporter(ReporterConfig{}),

          runInfo(TestRunInfo{"test suite", "description"}),

          totals{0, 0, 0, 0, 0} {}

};



// Test normal operation

TEST_F(CumulativeReporterBaseTest_861, TestRunEnded_NormalOperation_861) {

    TestRunStats testRunStats(runInfo, totals, aborting);

    EXPECT_CALL(reporter, testRunEndedCumulative());

    reporter.testRunEnded(testRunStats);

}



// Test boundary conditions: empty run info and totals

TEST_F(CumulativeReporterBaseTest_861, TestRunEnded_BoundaryConditions_EmptyRunInfoAndTotals_861) {

    TestRunStats testRunStats(TestRunInfo{}, Totals{}, false);

    EXPECT_CALL(reporter, testRunEndedCumulative());

    reporter.testRunEnded(testRunStats);

}



// Test boundary conditions: aborting flag set to true

TEST_F(CumulativeReporterBaseTest_861, TestRunEnded_BoundaryConditions_AbortingFlagTrue_861) {

    TestRunStats testRunStats(runInfo, totals, true);

    EXPECT_CALL(reporter, testRunEndedCumulative());

    reporter.testRunEnded(testRunStats);

}



// Test for multiple calls (should not assert)

TEST_F(CumulativeReporterBaseTest_861, TestRunEnded_MultipleCalls_ShouldNotAssert_861) {

    TestRunStats testRunStats(runInfo, totals, aborting);

    EXPECT_CALL(reporter, testRunEndedCumulative());

    reporter.testRunEnded(testRunStats);



    // Second call should not assert

    EXPECT_THROW({

        reporter.testRunEnded(testRunStats);

    }, std::exception);

}
