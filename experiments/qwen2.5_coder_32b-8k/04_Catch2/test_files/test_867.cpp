#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/catch_totals.hpp"



using namespace Catch;



class MockJsonReporter : public JsonReporter {

public:

    MOCK_METHOD(void, testRunEnded, (const TestRunStats& runStats), (override));

};



// Normal operation

TEST_F(MockJsonReporter_867, TestRunEnded_NormalOperation_867) {

    Totals totals;

    totals.assertions.total = 5;

    totals.assertions.passed = 3;

    totals.testCases.total = 2;

    totals.testCases.passed = 1;



    TestRunStats runStats(TestRunInfo(), totals, false);



    EXPECT_CALL(*this, testRunEnded(testing::_)).Times(1);

    testRunEnded(runStats);

}



// Boundary conditions

TEST_F(MockJsonReporter_867, TestRunEnded_BoundaryZeroAssertions_867) {

    Totals totals;

    totals.assertions.total = 0;

    totals.assertions.passed = 0;

    totals.testCases.total = 2;

    totals.testCases.passed = 1;



    TestRunStats runStats(TestRunInfo(), totals, false);



    EXPECT_CALL(*this, testRunEnded(testing::_)).Times(1);

    testRunEnded(runStats);

}



TEST_F(MockJsonReporter_867, TestRunEnded_BoundaryZeroTestCases_867) {

    Totals totals;

    totals.assertions.total = 5;

    totals.assertions.passed = 3;

    totals.testCases.total = 0;

    totals.testCases.passed = 0;



    TestRunStats runStats(TestRunInfo(), totals, false);



    EXPECT_CALL(*this, testRunEnded(testing::_)).Times(1);

    testRunEnded(runStats);

}



// Exceptional or error cases

TEST_F(MockJsonReporter_867, TestRunEnded_ErrorAborting_867) {

    Totals totals;

    totals.assertions.total = 5;

    totals.assertions.passed = 3;

    totals.testCases.total = 2;

    totals.testCases.passed = 1;



    TestRunStats runStats(TestRunInfo(), totals, true);



    EXPECT_CALL(*this, testRunEnded(testing::_)).Times(1);

    testRunEnded(runStats);

}
