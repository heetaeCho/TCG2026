#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cfloat>

// Declaration of the function under test
namespace Catch {
    double nextafter(double x, double y);
}

class CatchNextafterTest_638 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(CatchNextafterTest_638, NextafterTowardsPositiveInfinity_638) {
    double result = Catch::nextafter(1.0, 2.0);
    EXPECT_GT(result, 1.0);
    EXPECT_EQ(result, ::nextafter(1.0, 2.0));
}

TEST_F(CatchNextafterTest_638, NextafterTowardsNegativeInfinity_638) {
    double result = Catch::nextafter(1.0, 0.0);
    EXPECT_LT(result, 1.0);
    EXPECT_EQ(result, ::nextafter(1.0, 0.0));
}

TEST_F(CatchNextafterTest_638, NextafterFromZeroTowardsPositive_638) {
    double result = Catch::nextafter(0.0, 1.0);
    EXPECT_GT(result, 0.0);
    EXPECT_EQ(result, ::nextafter(0.0, 1.0));
}

TEST_F(CatchNextafterTest_638, NextafterFromZeroTowardsNegative_638) {
    double result = Catch::nextafter(0.0, -1.0);
    EXPECT_LT(result, 0.0);
    EXPECT_EQ(result, ::nextafter(0.0, -1.0));
}

TEST_F(CatchNextafterTest_638, NextafterNegativeTowardsPositive_638) {
    double result = Catch::nextafter(-1.0, 1.0);
    EXPECT_GT(result, -1.0);
    EXPECT_EQ(result, ::nextafter(-1.0, 1.0));
}

TEST_F(CatchNextafterTest_638, NextafterNegativeTowardsMoreNegative_638) {
    double result = Catch::nextafter(-1.0, -2.0);
    EXPECT_LT(result, -1.0);
    EXPECT_EQ(result, ::nextafter(-1.0, -2.0));
}

TEST_F(CatchNextafterTest_638, NextafterSmallPositiveValues_638) {
    double result = Catch::nextafter(0.5, 1.0);
    EXPECT_GT(result, 0.5);
    EXPECT_EQ(result, ::nextafter(0.5, 1.0));
}

// Boundary condition tests

TEST_F(CatchNextafterTest_638, NextafterSameValues_638) {
    double result = Catch::nextafter(1.0, 1.0);
    EXPECT_EQ(result, 1.0);
    EXPECT_EQ(result, ::nextafter(1.0, 1.0));
}

TEST_F(CatchNextafterTest_638, NextafterZeroTowardsZero_638) {
    double result = Catch::nextafter(0.0, 0.0);
    EXPECT_EQ(result, 0.0);
    EXPECT_EQ(result, ::nextafter(0.0, 0.0));
}

TEST_F(CatchNextafterTest_638, NextafterMaxDoubleTowardsInfinity_638) {
    double result = Catch::nextafter(std::numeric_limits<double>::max(), 
                                      std::numeric_limits<double>::infinity());
    EXPECT_EQ(result, ::nextafter(std::numeric_limits<double>::max(), 
                                   std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(std::isinf(result));
}

TEST_F(CatchNextafterTest_638, NextafterMinPositiveTowardsZero_638) {
    double smallest = std::numeric_limits<double>::denorm_min();
    double result = Catch::nextafter(smallest, 0.0);
    EXPECT_EQ(result, ::nextafter(smallest, 0.0));
    EXPECT_EQ(result, 0.0);
}

TEST_F(CatchNextafterTest_638, NextafterInfinityTowardsZero_638) {
    double result = Catch::nextafter(std::numeric_limits<double>::infinity(), 0.0);
    EXPECT_EQ(result, ::nextafter(std::numeric_limits<double>::infinity(), 0.0));
    EXPECT_LT(result, std::numeric_limits<double>::infinity());
}

TEST_F(CatchNextafterTest_638, NextafterNegativeInfinityTowardsZero_638) {
    double result = Catch::nextafter(-std::numeric_limits<double>::infinity(), 0.0);
    EXPECT_EQ(result, ::nextafter(-std::numeric_limits<double>::infinity(), 0.0));
    EXPECT_GT(result, -std::numeric_limits<double>::infinity());
}

TEST_F(CatchNextafterTest_638, NextafterNegativeMaxTowardsNegativeInfinity_638) {
    double result = Catch::nextafter(-std::numeric_limits<double>::max(), 
                                      -std::numeric_limits<double>::infinity());
    EXPECT_EQ(result, ::nextafter(-std::numeric_limits<double>::max(), 
                                   -std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(std::isinf(result));
}

// NaN tests

TEST_F(CatchNextafterTest_638, NextafterWithNaNAsFirst_638) {
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    double result = Catch::nextafter(nan_val, 1.0);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(CatchNextafterTest_638, NextafterWithNaNAsSecond_638) {
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    double result = Catch::nextafter(1.0, nan_val);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(CatchNextafterTest_638, NextafterBothNaN_638) {
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    double result = Catch::nextafter(nan_val, nan_val);
    EXPECT_TRUE(std::isnan(result));
}

// Consistency with standard nextafter

TEST_F(CatchNextafterTest_638, ConsistencyWithStdNextafter_638) {
    // Test a variety of values to ensure consistency
    double test_pairs[][2] = {
        {0.0, 1.0},
        {1.0, 0.0},
        {-1.0, 0.0},
        {0.0, -1.0},
        {100.0, 200.0},
        {-100.0, -200.0},
        {DBL_MIN, 0.0},
        {DBL_MIN, 1.0},
        {1e-300, 1e-301},
        {1e300, 1e301},
    };
    
    for (const auto& pair : test_pairs) {
        double catch_result = Catch::nextafter(pair[0], pair[1]);
        double std_result = ::nextafter(pair[0], pair[1]);
        EXPECT_EQ(catch_result, std_result) 
            << "Mismatch for nextafter(" << pair[0] << ", " << pair[1] << ")";
    }
}

TEST_F(CatchNextafterTest_638, NextafterPositiveNegativeZero_638) {
    // +0.0 towards -0.0 and vice versa
    double result1 = Catch::nextafter(+0.0, -0.0);
    EXPECT_EQ(result1, ::nextafter(+0.0, -0.0));
    
    double result2 = Catch::nextafter(-0.0, +0.0);
    EXPECT_EQ(result2, ::nextafter(-0.0, +0.0));
}

TEST_F(CatchNextafterTest_638, NextafterDenormalizedRange_638) {
    double denorm = std::numeric_limits<double>::denorm_min();
    double result = Catch::nextafter(denorm, 1.0);
    EXPECT_GT(result, denorm);
    EXPECT_EQ(result, ::nextafter(denorm, 1.0));
}
