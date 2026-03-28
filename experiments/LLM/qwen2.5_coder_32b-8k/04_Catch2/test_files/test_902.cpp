#include <gtest/gtest.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark;

using namespace Catch::Benchmark::Detail;



class MeasureTest_902 : public ::testing::Test {

protected:

    struct MockFunctor {

        int operator()(int a, int b) {

            return a + b;

        }

    };

};



TEST_F(MeasureTest_902, MeasureReturnsCorrectTimingAndResult_902) {

    auto result = measure<std::chrono::high_resolution_clock>(MockFunctor(), 1, 2);

    EXPECT_EQ(result.result, 3); // The functor adds the two numbers

    EXPECT_GT(result.duration.count(), 0); // Duration should be positive

}



TEST_F(MeasureTest_902, MeasureWithZeroDuration_902) {

    auto result = measure<std::chrono::high_resolution_clock>(MockFunctor(), 0, 0);

    EXPECT_EQ(result.result, 0); // The functor adds the two numbers

    EXPECT_GE(result.duration.count(), 0); // Duration should be non-negative

}



TEST_F(MeasureTest_902, MeasureWithNegativeNumbers_902) {

    auto result = measure<std::chrono::high_resolution_clock>(MockFunctor(), -1, -2);

    EXPECT_EQ(result.result, -3); // The functor adds the two numbers

    EXPECT_GT(result.duration.count(), 0); // Duration should be positive

}



TEST_F(MeasureTest_902, MeasureWithLargeNumbers_902) {

    auto result = measure<std::chrono::high_resolution_clock>(MockFunctor(), INT_MAX, 1);

    EXPECT_EQ(result.result, (INT_MAX + 1)); // The functor adds the two numbers

    EXPECT_GT(result.duration.count(), 0); // Duration should be positive

}



TEST_F(MeasureTest_902, MeasureWithSameNumbers_902) {

    auto result = measure<std::chrono::high_resolution_clock>(MockFunctor(), 10, 10);

    EXPECT_EQ(result.result, 20); // The functor adds the two numbers

    EXPECT_GT(result.duration.count(), 0); // Duration should be positive

}



TEST_F(MeasureTest_902, MeasureWithZeroAndPositiveNumber_902) {

    auto result = measure<std::chrono::high_resolution_clock>(MockFunctor(), 0, 5);

    EXPECT_EQ(result.result, 5); // The functor adds the two numbers

    EXPECT_GT(result.duration.count(), 0); // Duration should be positive

}



TEST_F(MeasureTest_902, MeasureWithZeroAndNegativeNumber_902) {

    auto result = measure<std::chrono::high_resolution_clock>(MockFunctor(), 0, -5);

    EXPECT_EQ(result.result, -5); // The functor adds the two numbers

    EXPECT_GT(result.duration.count(), 0); // Duration should be positive

}
