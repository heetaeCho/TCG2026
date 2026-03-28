#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_tap.hpp"

#include "catch_totals.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;



class TAPReporterTest_748 : public ::testing::Test {

protected:

    std::stringstream ss;

    ReporterConfig config{Detail::unique_ptr<IStream>(new OstreamRaii(ss)), ColourMode::None};

    TAPReporter reporter{CATCH_MOVE(config)};



    Totals createTotals(std::uint64_t assertionsTotal, std::uint64_t testCasesTotal) {

        Totals totals;

        totals.assertions = Counts{{assertionsTotal}};

        totals.testCases = Counts{{testCasesTotal}};

        return totals;

    }



    TestRunStats createTestRunStats(Totals totals) {

        TestRunInfo runInfo{"dummyRun"};

        bool aborting = false;

        return TestRunStats{runInfo, totals, aborting};

    }

};



TEST_F(TAPReporterTest_748, TestRunEnded_NoAssertionsNoTests_748) {

    auto testRunStats = createTestRunStats(createTotals(0, 0));

    reporter.testRunEnded(testRunStats);

    EXPECT_EQ(ss.str(), "1..0\n # Skipped: No tests ran.\n\n");

}



TEST_F(TAPReporterTest_748, TestRunEnded_SomeAssertionsNoTests_748) {

    auto testRunStats = createTestRunStats(createTotals(5, 0));

    reporter.testRunEnded(testRunStats);

    EXPECT_EQ(ss.str(), "1..5\n # Skipped: No tests ran.\n\n");

}



TEST_F(TAPReporterTest_748, TestRunEnded_NoAssertionsSomeTests_748) {

    auto testRunStats = createTestRunStats(createTotals(0, 3));

    reporter.testRunEnded(testRunStats);

    EXPECT_EQ(ss.str(), "1..0\n # Skipped: No tests ran.\n\n");

}



TEST_F(TAPReporterTest_748, TestRunEnded_SomeAssertionsSomeTests_748) {

    auto testRunStats = createTestRunStats(createTotals(5, 3));

    reporter.testRunEnded(testRunStats);

    EXPECT_EQ(ss.str(), "1..5\n\n");

}
