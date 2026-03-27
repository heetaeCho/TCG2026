#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark::Detail;



class MockClock {

public:

    using duration = std::chrono::steady_clock::duration;

    using time_point = std::chrono::steady_clock::time_point;



    MOCK_CONST_METHOD0(now, time_point());

};



template <>

struct ChronometerModel<MockClock> : public ChronometerConcept {

public:

    TimePoint<MockClock> started;

    TimePoint<MockClock> finished;



    void start() override {

        started = MockClock().now();

    }



    void finish() override {

        finished = MockClock().now();

    }



    IDuration elapsed() const override {

        return std::chrono::duration_cast<IDuration>(finished - started);

    }

};



class ChronometerModelTest_888 : public ::testing::Test {

protected:

    ChronometerModel<MockClock> chronometer;

    MockClock mockClock;

};



TEST_F(ChronometerModelTest_888, StartSetsStartedTime_888) {

    EXPECT_CALL(mockClock, now()).WillOnce(testing::Return(MockClock::time_point()));

    chronometer.start();

    EXPECT_NE(chronometer.started.time_since_epoch(), MockClock::duration());

}



TEST_F(ChronometerModelTest_888, FinishSetsFinishedTime_888) {

    EXPECT_CALL(mockClock, now())

        .WillOnce(testing::Return(MockClock::time_point()))

        .WillOnce(testing::Return(MockClock::time_point() + std::chrono::seconds(1)));

    chronometer.start();

    chronometer.finish();

    EXPECT_NE(chronometer.finished.time_since_epoch(), MockClock::duration());

}



TEST_F(ChronometerModelTest_888, ElapsedCalculatesCorrectly_888) {

    auto startTime = MockClock::time_point() + std::chrono::seconds(2);

    auto endTime = startTime + std::chrono::milliseconds(500);

    EXPECT_CALL(mockClock, now())

        .WillOnce(testing::Return(startTime))

        .WillOnce(testing::Return(endTime));

    chronometer.start();

    chronometer.finish();

    EXPECT_EQ(chronometer.elapsed(), std::chrono::milliseconds(500));

}



TEST_F(ChronometerModelTest_888, ElapsedZeroBeforeFinish_888) {

    EXPECT_CALL(mockClock, now()).WillOnce(testing::Return(MockClock::time_point()));

    chronometer.start();

    EXPECT_EQ(chronometer.elapsed(), std::chrono::milliseconds(0));

}
