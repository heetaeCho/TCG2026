#include <gtest/gtest.h>

#include "catch_outlier_classification.hpp"



using namespace Catch::Benchmark;



class OutlierClassificationTest_68 : public ::testing::Test {

protected:

    OutlierClassification outlierClassification;

};



TEST_F(OutlierClassificationTest_68, TotalReturnsZeroInitially_68) {

    EXPECT_EQ(outlierClassification.total(), 0);

}



TEST_F(OutlierClassificationTest_68, TotalSumOfAllCounts_68) {

    outlierClassification.low_severe = 1;

    outlierClassification.low_mild = 2;

    outlierClassification.high_mild = 3;

    outlierClassification.high_severe = 4;

    EXPECT_EQ(outlierClassification.total(), 10);

}



TEST_F(OutlierClassificationTest_68, TotalBoundaryConditionsWithMaxIntegers_68) {

    outlierClassification.low_severe = std::numeric_limits<int>::max();

    outlierClassification.low_mild = 0;

    outlierClassification.high_mild = 0;

    outlierClassification.high_severe = 0;

    EXPECT_EQ(outlierClassification.total(), std::numeric_limits<int>::max());

}



TEST_F(OutlierClassificationTest_68, TotalBoundaryConditionsWithNegativeValues_68) {

    outlierClassification.low_severe = -1;

    outlierClassification.low_mild = -2;

    outlierClassification.high_mild = -3;

    outlierClassification.high_severe = -4;

    EXPECT_EQ(outlierClassification.total(), -10);

}



TEST_F(OutlierClassificationTest_68, TotalBoundaryConditionsWithMixedValues_68) {

    outlierClassification.low_severe = std::numeric_limits<int>::max();

    outlierClassification.low_mild = 1;

    outlierClassification.high_mild = 2;

    outlierClassification.high_severe = std::numeric_limits<int>::min();

    EXPECT_EQ(outlierClassification.total(), std::numeric_limits<int>::max() + 3 + std::numeric_limits<int>::min());

}
