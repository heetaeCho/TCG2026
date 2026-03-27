#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_console.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIStream : public IStream {

public:

    MOCK_METHOD(void, write, (std::string const&), (override));

};



class MockColourImpl : public ColourImpl {

public:

    MOCK_METHOD(void, useColour, (bool), (override));

    MOCK_METHOD(std::ostream&, stream, (), (const, override));

};



class ConsoleReporterTest : public ::testing::Test {

protected:

    NiceMock<MockIStream> mockStream;

    NiceMock<MockColourImpl> mockColour;

    ReporterConfig config;

    Totals totals;

    TestRunInfo runInfo;

    TestRunStats testRunStats;



    void SetUp() override {

        config.takeStream(&mockStream);

        makeColourImpl(ColourMode::None, &mockStream);

        testRunStats = TestRunStats(runInfo, totals, false);

    }



    ConsoleReporter* reporter;



    ConsoleReporterTest() : reporter(new ConsoleReporter(std::move(config))) {}



    ~ConsoleReporterTest() override {

        delete reporter;

    }

};



TEST_F(ConsoleReporterTest_773, TestRunEnded_NormalOperation_773) {

    EXPECT_CALL(mockStream, write(_)).Times(2);

    reporter->testRunEnded(testRunStats);

}



TEST_F(ConsoleReporterTest_773, TestRunEnded_ZeroTestsPassed_773) {

    Totals zeroTotals = {0, 0, 0};

    TestRunStats zeroTestRunStats(runInfo, zeroTotals, false);



    EXPECT_CALL(mockStream, write(_)).Times(2);

    reporter->testRunEnded(zeroTestRunStats);

}



TEST_F(ConsoleReporterTest_773, TestRunEnded_AllTestsPassed_773) {

    Totals allPassTotals = {10, 0, 0};

    TestRunStats allPassTestRunStats(runInfo, allPassTotals, false);



    EXPECT_CALL(mockStream, write(_)).Times(2);

    reporter->testRunEnded(allPassTestRunStats);

}



TEST_F(ConsoleReporterTest_773, TestRunEnded_AllTestsFailed_773) {

    Totals allFailTotals = {0, 10, 0};

    TestRunStats allFailTestRunStats(runInfo, allFailTotals, false);



    EXPECT_CALL(mockStream, write(_)).Times(2);

    reporter->testRunEnded(allFailTestRunStats);

}



TEST_F(ConsoleReporterTest_773, TestRunEnded_AllTestsAborted_773) {

    Totals allAbortTotals = {0, 0, 10};

    TestRunStats allAbortTestRunStats(runInfo, allAbortTotals, false);



    EXPECT_CALL(mockStream, write(_)).Times(2);

    reporter->testRunEnded(allAbortTestRunStats);

}



TEST_F(ConsoleReporterTest_773, TestRunEnded_StreamWriteFailure_773) {

    Totals normalTotals = {5, 3, 2};

    TestRunStats normalTestRunStats(runInfo, normalTotals, false);



    EXPECT_CALL(mockStream, write(_)).WillOnce(::testing::Throw(std::runtime_error("stream write error")));

    ASSERT_THROW(reporter->testRunEnded(normalTestRunStats), std::runtime_error);

}
