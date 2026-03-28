#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark;



// Mock for Detail::ChronometerConcept to facilitate testing of Chronometer class.

class MockChronometerConcept : public Detail::ChronometerConcept {

public:

    MOCK_METHOD(void, start, (), (override));

    MOCK_METHOD(void, stop, (), (override));

    MOCK_METHOD(double, elapsedSeconds, (), (const, override));

};



// Test fixture for Chronometer tests

class ChronometerTest_892 : public ::testing::Test {

protected:

    MockChronometerConcept mockMeter;

    Chronometer chronometer;



    ChronometerTest_892() : chronometer(mockMeter, 5) {}

};



// Test if the runs method returns the correct number of repeats.

TEST_F(ChronometerTest_892, RunsReturnsCorrectValue_892) {

    EXPECT_EQ(chronometer.runs(), 5);

}



// Test boundary condition where the number of repeats is zero.

TEST_F(ChronometerTest_892, RunsZeroRepeats_892) {

    Chronometer chronometerZero(mockMeter, 0);

    EXPECT_EQ(chronometerZero.runs(), 0);

}



// Test if measure function calls start and stop methods correctly for each run.

TEST_F(ChronometerTest_892, MeasureCallsStartAndStop_892) {

    testing::MockFunction<void()> testFun;

    EXPECT_CALL(mockMeter, start()).Times(5);

    EXPECT_CALL(mockMeter, stop()).Times(5);



    chronometer.measure([&testFun]() { testFun.Call(); });

}



// Test if measure function calls the provided function multiple times.

TEST_F(ChronometerTest_892, MeasureCallsFunctionMultipleTimes_892) {

    testing::MockFunction<void()> testFun;

    EXPECT_CALL(testFun, Call()).Times(5);



    chronometer.measure([&testFun]() { testFun.Call(); });

}



// Test if measure function can handle an empty lambda.

TEST_F(ChronometerTest_892, MeasureEmptyLambda_892) {

    auto emptyLambda = []() {};

    EXPECT_NO_THROW(chronometer.measure(emptyLambda));

}
