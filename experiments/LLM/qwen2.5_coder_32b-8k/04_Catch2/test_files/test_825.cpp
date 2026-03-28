#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_helpers.cpp"

#include "catch_totals.hpp"

#include "catch_console_colour.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class MockIStream : public IStream {

public:

    MOCK_METHOD(void, write, (std::string const&), (override));

};



class MockColourImpl : public ColourImpl {

public:

    explicit MockColourImpl(MockIStream* stream) : ColourImpl(stream) {}



    MOCK_METHOD(ColourGuard, guardColour, (Colour::Code colourCode), (override));

};



class printTestRunTotalsTest_825 : public ::testing::Test {

protected:

    std::ostringstream oss;

    MockIStream mockStream;

    MockColourImpl mockColour{&mockStream};

    Totals totals;

};



TEST_F(printTestRunTotalsTest_825, NoTestsRan_825) {

    EXPECT_CALL(mockColour, guardColour(Colour::Warning))

        .WillOnce(testing::Return(ColourGuard{}));

    printTestRunTotals(oss, mockColour, totals);

    EXPECT_EQ("No tests ran\n", oss.str());

}



TEST_F(printTestRunTotalsTest_825, AllTestsPassedWithAssertions_825) {

    totals.testCases.passed = 1;

    totals.assertions.passed = 2;

    EXPECT_CALL(mockColour, guardColour(Colour::ResultSuccess))

        .WillOnce(testing::Return(ColourGuard{}));

    printTestRunTotals(oss, mockColour, totals);

    EXPECT_EQ("All tests passed (2 assertions in 1 test case)\n", oss.str());

}



TEST_F(printTestRunTotalsTest_825, SomeTestsFailed_825) {

    totals.testCases.total() = 3;

    totals.assertions.passed = 4;

    totals.testCases.failed = 1;

    totals.assertions.failed = 1;



    EXPECT_CALL(mockColour, guardColour(Colour::None))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::Success))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::ResultError))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::Skip))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::ResultExpectedFailure))

        .WillOnce(testing::Return(ColourGuard{}));



    printTestRunTotals(oss, mockColour, totals);

    std::string expectedOutput = "  | test cases\n";

    expectedOutput += "--:|----------\n";

    expectedOutput += " 3 |          \n";

    expectedOutput += " 4 |          \n";

    expectedOutput += "  | passed\n";

    expectedOutput += "--:|--------\n";

    expectedOutput += " 1 |        \n";

    expectedOutput += " 4 |        \n";

    expectedOutput += "  | failed\n";

    expectedOutput += "--:|--------\n";

    expectedOutput += " 1 |        \n";

    expectedOutput += " 1 |        \n";

    expectedOutput += "  | skipped\n";

    expectedOutput += "--:|---------\n";

    expectedOutput += " 0 |         \n";

    expectedOutput += " 0 |         \n";

    expectedOutput += "  | failed as expected\n";

    expectedOutput += "--:|------------------\n";

    expectedOutput += " 0 |                  \n";

    expectedOutput += " 0 |                  \n";



    EXPECT_EQ(expectedOutput, oss.str());

}



TEST_F(printTestRunTotalsTest_825, AllTestsSkipped_825) {

    totals.testCases.skipped = 1;

    EXPECT_CALL(mockColour, guardColour(Colour::None))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::Success))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::ResultError))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::Skip))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::ResultExpectedFailure))

        .WillOnce(testing::Return(ColourGuard{}));



    printTestRunTotals(oss, mockColour, totals);

    std::string expectedOutput = "  | test cases\n";

    expectedOutput += "--:|----------\n";

    expectedOutput += " 1 |          \n";

    expectedOutput += " 0 |          \n";

    expectedOutput += "  | passed\n";

    expectedOutput += "--:|--------\n";

    expectedOutput += " 0 |        \n";

    expectedOutput += " 0 |        \n";

    expectedOutput += "  | failed\n";

    expectedOutput += "--:|--------\n";

    expectedOutput += " 1 |        \n";

    expectedOutput += " 0 |        \n";

    expectedOutput += "  | skipped\n";

    expectedOutput += "--:|---------\n";

    expectedOutput += " 0 |         \n";

    expectedOutput += " 0 |         \n";

    expectedOutput += "  | failed as expected\n";

    expectedOutput += "--:|------------------\n";

    expectedOutput += " 0 |                  \n";

    expectedOutput += " 0 |                  \n";



    EXPECT_EQ(expectedOutput, oss.str());

}



TEST_F(printTestRunTotalsTest_825, SomeAssertionsSkipped_825) {

    totals.testCases.total() = 1;

    totals.assertions.passed = 1;

    totals.assertions.skipped = 1;



    EXPECT_CALL(mockColour, guardColour(Colour::None))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::Success))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::ResultError))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::Skip))

        .WillOnce(testing::Return(ColourGuard{}));

    EXPECT_CALL(mockColour, guardColour(Colour::ResultExpectedFailure))

        .WillOnce(testing::Return(ColourGuard{}));



    printTestRunTotals(oss, mockColour, totals);

    std::string expectedOutput = "  | test cases\n";

    expectedOutput += "--:|----------\n";

    expectedOutput += " 1 |          \n";

    expectedOutput += " 1 |          \n";

    expectedOutput += "  | passed\n";

    expectedOutput += "--:|--------\n";

    expectedOutput += " 1 |        \n";

    expectedOutput += " 1 |        \n";

    expectedOutput += "  | failed\n";

    expectedOutput += "--:|--------\n";

    expectedOutput += " 0 |        \n";

    expectedOutput += " 0 |        \n";

    expectedOutput += "  | skipped\n";

    expectedOutput += "--:|---------\n";

    expectedOutput += " 0 |         \n";

    expectedOutput += " 0 |         \n";

    expectedOutput += "  | failed as expected\n";

    expectedOutput += "--:|------------------\n";

    expectedOutput += " 0 |                  \n";

    expectedOutput += " 0 |                  \n";



    EXPECT_EQ(expectedOutput, oss.str());

}
