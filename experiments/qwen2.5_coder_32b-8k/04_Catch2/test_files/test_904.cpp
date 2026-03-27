#include <gtest/gtest.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark::Detail;



// Mock class to simulate the behavior of a clock

class MockClock {

public:

    using time_point = std::chrono::steady_clock::time_point;

    using duration = std::chrono::steady_clock::duration;



    MOCK_METHOD(time_point, now, (), (const));

};



TEST_F(MockClockTest_904, MeasureOne_SingleIteration_904) {

    MockClock mockClock;

    auto start = std::chrono::steady_clock::now();

    EXPECT_CALL(mockClock, now()).WillOnce(::testing::Return(start))

                                  .WillOnce(::testing::Return(start + std::chrono::milliseconds(10)));



    auto fun = []() { return 42; };

    auto result = measure_one<MockClock>(fun, 1, std::true_type());



    EXPECT_EQ(result.duration.count(), std::chrono::milliseconds(10).count());

    EXPECT_EQ(result.result, 42);

}



TEST_F(MockClockTest_904, MeasureOne_MultipleIterations_904) {

    MockClock mockClock;

    auto start = std::chrono::steady_clock::now();

    EXPECT_CALL(mockClock, now()).WillOnce(::testing::Return(start))

                                  .WillOnce(::testing::Return(start + std::chrono::milliseconds(20)));



    auto fun = []() { return 42; };

    auto result = measure_one<MockClock>(fun, 2, std::true_type());



    EXPECT_EQ(result.duration.count(), std::chrono::milliseconds(20).count());

    EXPECT_EQ(result.result, 42);

}



TEST_F(MockClockTest_904, MeasureOne_ZeroIterations_904) {

    MockClock mockClock;

    auto start = std::chrono::steady_clock::now();

    EXPECT_CALL(mockClock, now()).WillOnce(::testing::Return(start));



    auto fun = []() { return 42; };

    auto result = measure_one<MockClock>(fun, 0, std::true_type());



    EXPECT_EQ(result.duration.count(), std::chrono::milliseconds(0).count());

    EXPECT_EQ(result.result, 42);

}



TEST_F(MockClockTest_904, MeasureOne_ExceptionHandling_904) {

    MockClock mockClock;

    auto start = std::chrono::steady_clock::now();

    EXPECT_CALL(mockClock, now()).WillOnce(::testing::Return(start))

                                  .WillOnce(::testing::Throw(std::runtime_error("Mock exception")));



    auto fun = []() { return 42; };

    EXPECT_THROW(measure_one<MockClock>(fun, 1, std::true_type()), std::runtime_error);

}
