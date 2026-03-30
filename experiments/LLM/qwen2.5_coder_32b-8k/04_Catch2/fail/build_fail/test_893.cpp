#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark;

using namespace Catch::Benchmark::Detail;



// Mock class for ChronometerConcept

class MockChronometerConcept : public ChronometerConcept {

public:

    MOCK_METHOD(void, start, (), (override));

    MOCK_METHOD(void, stop, (), (override));

    MOCK_METHOD(double, elapsedSeconds, (), (const, override));

};



TEST(BenchmarkFunctionTest_893, CallWithCallableFunction_893) {

    MockChronometerConcept mockMeter;

    Chronometer meter(mockMeter, 1);

    int callCount = 0;

    auto testFun = [&callCount](Chronometer& m) { ++callCount; };

    BenchmarkFunction<decltype(testFun)>::model model(testFun);



    EXPECT_CALL(mockMeter, start()).Times(1);

    EXPECT_CALL(mockMeter, stop()).Times(1);



    model.call(meter);



    EXPECT_EQ(callCount, 1);

}



TEST(BenchmarkFunctionTest_893, CallWithNonCallableFunction_893) {

    MockChronometerConcept mockMeter;

    Chronometer meter(mockMeter, 1);

    int callCount = 0;

    auto testFun = [&callCount](int x) { ++callCount; };

    BenchmarkFunction<decltype(testFun)>::model model(testFun);



    EXPECT_CALL(mockMeter, start()).Times(0);

    EXPECT_CALL(mockMeter, stop()).Times(0);



    model.call(meter);



    EXPECT_EQ(callCount, 0);

}



TEST(BenchmarkFunctionTest_893, CallMultipleRuns_893) {

    MockChronometerConcept mockMeter;

    Chronometer meter(mockMeter, 5); // Setting repeats to 5

    int callCount = 0;

    auto testFun = [&callCount](Chronometer& m) { ++callCount; };

    BenchmarkFunction<decltype(testFun)>::model model(testFun);



    EXPECT_CALL(mockMeter, start()).Times(5);

    EXPECT_CALL(mockMeter, stop()).Times(5);



    model.call(meter);



    EXPECT_EQ(callCount, 1); // The function should be called only once regardless of repeats

}



TEST(BenchmarkFunctionTest_893, MeasureWithCallableFunction_893) {

    MockChronometerConcept mockMeter;

    Chronometer meter(mockMeter, 1);

    int callCount = 0;

    auto testFun = [&callCount](Chronometer& m) { ++callCount; };



    EXPECT_CALL(mockMeter, start()).Times(1);

    EXPECT_CALL(mockMeter, stop()).Times(1);



    meter.measure(testFun);



    EXPECT_EQ(callCount, 1);

}



TEST(BenchmarkFunctionTest_893, MeasureWithNonCallableFunction_893) {

    MockChronometerConcept mockMeter;

    Chronometer meter(mockMeter, 1);

    int callCount = 0;

    auto testFun = [&callCount](int x) { ++callCount; };



    EXPECT_CALL(mockMeter, start()).Times(0);

    EXPECT_CALL(mockMeter, stop()).Times(0);



    meter.measure(testFun);



    EXPECT_EQ(callCount, 0);

}
