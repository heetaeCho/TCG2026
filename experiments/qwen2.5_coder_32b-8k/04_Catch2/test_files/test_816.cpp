#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_compact.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using namespace ::testing;



class MockIStream : public IStream {

public:

    MOCK_METHOD(std::ostream&, stream, (), (override));

};



class MockColourImpl : public ColourImpl {

public:

    MOCK_METHOD(void, useColour, (bool), (override));

    MOCK_METHOD(void, setColour, (ColourCode), (override));

};



class CompactReporterTest : public Test {

protected:

    NiceMock<MockIStream> mockStream;

    NiceMock<MockColourImpl> mockColour;

    ReporterConfig config{Catch::Ptr<IStream>(&mockStream), Catch::Ptr<ColourImpl>(&mockColour)};

    CompactReporter reporter{std::move(config)};



    Totals createTotals(int passed, int failed, int skipped) {

        Totals totals;

        totals.passed = passed;

        totals.failed = failed;

        totals.skipped = skipped;

        return totals;

    }



    TestRunStats createTestRunStats(const Totals& totals, bool aborting) {

        TestRunInfo runInfo{"test_run"};

        return TestRunStats{runInfo, totals, aborting};

    }

};



TEST_F(CompactReporterTest_816, TestRunEnded_PrintsTotals_816) {

    Totals totals = createTotals(5, 2, 3);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).Times(2);

    reporter.testRunEnded(stats);

}



TEST_F(CompactReporterTest_816, TestRunEnded_FlushesStream_816) {

    Totals totals = createTotals(5, 2, 3);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).WillOnce(ReturnRef(std::cout));

    reporter.testRunEnded(stats);

}



TEST_F(CompactReporterTest_816, TestRunEnded_CallsBaseClassMethod_816) {

    Totals totals = createTotals(5, 2, 3);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).Times(2);

    reporter.testRunEnded(stats);

}



TEST_F(CompactReporterTest_816, TestRunEnded_BoundaryZeroTestsPassed_816) {

    Totals totals = createTotals(0, 2, 3);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).Times(2);

    reporter.testRunEnded(stats);

}



TEST_F(CompactReporterTest_816, TestRunEnded_BoundaryZeroTestsFailed_816) {

    Totals totals = createTotals(5, 0, 3);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).Times(2);

    reporter.testRunEnded(stats);

}



TEST_F(CompactReporterTest_816, TestRunEnded_BoundaryZeroTestsSkipped_816) {

    Totals totals = createTotals(5, 2, 0);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).Times(2);

    reporter.testRunEnded(stats);

}



TEST_F(CompactReporterTest_816, TestRunEnded_BoundaryAllTestsPassed_816) {

    Totals totals = createTotals(10, 0, 0);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).Times(2);

    reporter.testRunEnded(stats);

}



TEST_F(CompactReporterTest_816, TestRunEnded_BoundaryAllTestsFailed_816) {

    Totals totals = createTotals(0, 10, 0);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).Times(2);

    reporter.testRunEnded(stats);

}



TEST_F(CompactReporterTest_816, TestRunEnded_BoundaryAllTestsSkipped_816) {

    Totals totals = createTotals(0, 0, 10);

    TestRunStats stats = createTestRunStats(totals, false);



    EXPECT_CALL(mockStream, stream()).Times(2);

    reporter.testRunEnded(stats);

}
