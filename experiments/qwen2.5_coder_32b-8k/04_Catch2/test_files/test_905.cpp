#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark;

using namespace ::testing;



class ChronometerMock : public Detail::ChronometerConcept {

public:

    MOCK_METHOD(void, measureImpl, (std::function<void()>, int), (override));

};



class ChronometerTest_905 : public Test {

protected:

    std::unique_ptr<ChronometerMock> mock_impl_;

    Chronometer chronometer_;



    ChronometerTest_905()

        : mock_impl_(std::make_unique<ChronometerMock>()),

          chronometer_(*mock_impl_, 1) {}

};



TEST_F(ChronometerTest_905, MeasureFunctionCalledOnceWithDefaultRepeats_905) {

    EXPECT_CALL(*mock_impl_, measureImpl(_, 1))

        .Times(1);



    auto lambda = []() {};

    chronometer_.measure(lambda);

}



TEST_F(ChronometerTest_905, MeasureFunctionCalledMultipleTimesUntilDurationMet_905) {

    EXPECT_CALL(*mock_impl_, measureImpl(_, _))

        .WillOnce([](std::function<void()>, int){})

        .WillOnce([](std::function<void()>, int){});



    auto lambda = []() {};

    Detail::run_for_at_least(std::chrono::milliseconds(1), 1, [&chronometer = chronometer_, &lambda](){

        chronometer_.measure(lambda);

    });

}



TEST_F(ChronometerTest_905, RunsReturnsCorrectValue_905) {

    EXPECT_CALL(*mock_impl_, measureImpl(_, _))

        .WillOnce([](std::function<void()>, int){});



    auto lambda = []() {};

    chronometer_.measure(lambda);

    EXPECT_EQ(chronometer_.runs(), 1);

}
