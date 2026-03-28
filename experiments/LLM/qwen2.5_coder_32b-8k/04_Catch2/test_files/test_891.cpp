#include <gtest/gtest.h>

#include "TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark;



class ChronometerTest_891 : public ::testing::Test {

protected:

    class MockChronometerConcept : public Detail::ChronometerConcept {

    public:

        MOCK_METHOD(void, start, (), (override));

        MOCK_METHOD(void, stop, (), (override));

        MOCK_METHOD(double, elapsedSeconds, (), (const, override));

    };



    MockChronometerConcept mockMeter;

    Chronometer chronometer;



    ChronometerTest_891() : chronometer(mockMeter, 5) {}

};



TEST_F(ChronometerTest_891, MeasureFunctionIsCalledMultipleTimes_891) {

    EXPECT_CALL(mockMeter, start()).Times(5);

    EXPECT_CALL(mockMeter, stop()).Times(5);



    auto mockFun = []() {};

    chronometer.measure(mockFun);

}



TEST_F(ChronometerTest_891, RunsReturnsCorrectCount_891) {

    EXPECT_EQ(chronometer.runs(), 5);

}
