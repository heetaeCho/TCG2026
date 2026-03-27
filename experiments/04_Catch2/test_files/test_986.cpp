#include <gtest/gtest.h>

#include "catch_amalgamated.cpp"  // Assuming the file is in the include path or correctly specified



using namespace Catch::Benchmark::Detail;



// Test fixture for mean function tests

class MeanFunctionTest_986 : public ::testing::Test {

protected:

    double values[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

};



TEST_F(MeanFunctionTest_986, CalculateMeanOfFiveNumbers_986) {

    double result = mean(values, values + 5);

    EXPECT_DOUBLE_EQ(result, 3.0);

}



TEST_F(MeanFunctionTest_986, CalculateMeanOfSingleNumber_986) {

    double singleValue[1] = {42.0};

    double result = mean(singleValue, singleValue + 1);

    EXPECT_DOUBLE_EQ(result, 42.0);

}



TEST_F(MeanFunctionTest_986, CalculateMeanOfNegativeNumbers_986) {

    double negativeValues[3] = {-1.0, -2.0, -3.0};

    double result = mean(negativeValues, negativeValues + 3);

    EXPECT_DOUBLE_EQ(result, -2.0);

}



TEST_F(MeanFunctionTest_986, CalculateMeanOfMixedNumbers_986) {

    double mixedValues[4] = {-1.0, 0.0, 1.0, 2.0};

    double result = mean(mixedValues, mixedValues + 4);

    EXPECT_DOUBLE_EQ(result, 0.5);

}



TEST_F(MeanFunctionTest_986, CalculateMeanOfZeroes_986) {

    double zeroValues[3] = {0.0, 0.0, 0.0};

    double result = mean(zeroValues, zeroValues + 3);

    EXPECT_DOUBLE_EQ(result, 0.0);

}



TEST_F(MeanFunctionTest_986, CalculateMeanWithLastPointerAtStart_986) {

    double result = mean(values, values);

    EXPECT_TRUE(std::isnan(result)); // Undefined behavior, but often returns NaN

}



TEST_F(MeanFunctionTest_986, CalculateMeanWithInvalidRange_986) {

    double result = mean(values + 1, values); // Reverse range

    EXPECT_TRUE(std::isnan(result)); // Undefined behavior, but often returns NaN

}
