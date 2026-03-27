#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <algorithm>

#include <vector>



using namespace Catch::Benchmark::Detail;



// Test fixture for weighted_average_quantile tests.

class WeightedAverageQuantileTest_984 : public ::testing::Test {

protected:

    std::vector<double> data;



    void SetUp() override {

        // Initialize some test data

        data = {1.0, 2.0, 3.0, 4.0, 5.0};

    }

};



// Test normal operation with a typical case.

TEST_F(WeightedAverageQuantileTest_984, NormalOperation_984) {

    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());

    EXPECT_EQ(result, 3.0);

}



// Test boundary condition with k=0.

TEST_F(WeightedAverageQuantileTest_984, BoundaryKZero_984) {

    double result = weighted_average_quantile(0, 2, data.data(), data.data() + data.size());

    EXPECT_EQ(result, 1.0);

}



// Test boundary condition with k=q.

TEST_F(WeightedAverageQuantileTest_984, BoundaryKEqualsQ_984) {

    double result = weighted_average_quantile(2, 2, data.data(), data.data() + data.size());

    EXPECT_EQ(result, 5.0);

}



// Test boundary condition with q=1.

TEST_F(WeightedAverageQuantileTest_984, BoundaryQOne_984) {

    double result = weighted_average_quantile(1, 1, data.data(), data.data() + data.size());

    EXPECT_EQ(result, 5.0);

}



// Test exceptional case with empty range.

TEST_F(WeightedAverageQuantileTest_984, ExceptionalEmptyRange_984) {

    EXPECT_THROW(weighted_average_quantile(1, 2, data.data(), data.data()), std::invalid_argument);

}



// Test exceptional case with invalid k (k > q).

TEST_F(WeightedAverageQuantileTest_984, ExceptionalKGreaterThanQ_984) {

    EXPECT_THROW(weighted_average_quantile(3, 2, data.data(), data.data() + data.size()), std::invalid_argument);

}



// Test exceptional case with invalid k (k < 0).

TEST_F(WeightedAverageQuantileTest_984, ExceptionalKNegative_984) {

    EXPECT_THROW(weighted_average_quantile(-1, 2, data.data(), data.data() + data.size()), std::invalid_argument);

}



// Test exceptional case with invalid q (q <= 0).

TEST_F(WeightedAverageQuantileTest_984, ExceptionalQNonPositive_984) {

    EXPECT_THROW(weighted_average_quantile(1, 0, data.data(), data.data() + data.size()), std::invalid_argument);

}



// Test with non-integer g.

TEST_F(WeightedAverageQuantileTest_984, NonIntegerG_984) {

    double result = weighted_average_quantile(1, 3, data.data(), data.data() + data.size());

    EXPECT_NEAR(result, 2.5, 0.0001);

}
