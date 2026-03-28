// nextafter_tests_638.cpp
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

namespace Catch {
    // Forward declaration of the function under test
    double nextafter(double x, double y);
}

using std::numeric_limits;

class NextAfterTest_638 : public ::testing::Test {};

// Normal: moving upward toward larger y
TEST_F(NextAfterTest_638, MovesTowardLargerTarget_638) {
    double x = 1.0;
    double y = 2.0;

    double got = Catch::nextafter(x, y);

    EXPECT_GT(got, x);
    // Cross-check against the well-defined standard library behavior
    EXPECT_DOUBLE_EQ(got, std::nextafter(x, y));
}

// Normal: moving downward toward smaller y
TEST_F(NextAfterTest_638, MovesTowardSmallerTarget_638) {
    double x = 1.0;
    double y = 0.0;

    double got = Catch::nextafter(x, y);

    EXPECT_LT(got, x);
    EXPECT_DOUBLE_EQ(got, std::nextafter(x, y));
}

// Boundary: when x == y, result should be exactly y
TEST_F(NextAfterTest_638, ReturnsYWhenXEqualsY_638) {
    double x = 1.23456789;
    double y = x;

    double got = Catch::nextafter(x, y);

    EXPECT_DOUBLE_EQ(got, y);
}

// Boundary: stepping away from +0 toward positive numbers
TEST_F(NextAfterTest_638, FromZeroTowardPositive_638) {
    double x = 0.0;
    double y = 1.0;

    double got = Catch::nextafter(x, y);

    EXPECT_GT(got, 0.0);
    EXPECT_DOUBLE_EQ(got, std::nextafter(x, y)); // typically +denorm_min
}

// Boundary: stepping away from +0 toward negative numbers
TEST_F(NextAfterTest_638, FromZeroTowardNegative_638) {
    double x = 0.0;
    double y = -1.0;

    double got = Catch::nextafter(x, y);

    EXPECT_LT(got, 0.0);
    EXPECT_DOUBLE_EQ(got, std::nextafter(x, y)); // typically -denorm_min
}

// Boundary: target is +infinity (move up by one ULP)
TEST_F(NextAfterTest_638, TowardPositiveInfinity_638) {
    double x = 1.0;
    double y = numeric_limits<double>::infinity();

    double got = Catch::nextafter(x, y);

    EXPECT_GT(got, x);
    EXPECT_DOUBLE_EQ(got, std::nextafter(x, y));
}

// Boundary: source is +infinity, move toward finite (should become max finite)
TEST_F(NextAfterTest_638, FromPositiveInfinityTowardFinite_638) {
    double x = numeric_limits<double>::infinity();
    double y = 0.0;

    double got = Catch::nextafter(x, y);

    EXPECT_TRUE(std::isfinite(got));
    EXPECT_LT(got, numeric_limits<double>::infinity());
    EXPECT_DOUBLE_EQ(got, std::nextafter(x, y));
}

// Boundary: stepping from max finite toward +infinity gives +infinity
TEST_F(NextAfterTest_638, MaxFiniteTowardPositiveInfinityBecomesInf_638) {
    double x = numeric_limits<double>::max();
    double y = numeric_limits<double>::infinity();

    double got = Catch::nextafter(x, y);

    EXPECT_TRUE(std::isinf(got));
    EXPECT_GT(got, 0.0);
    EXPECT_DOUBLE_EQ(got, std::nextafter(x, y));
}

// Boundary: source is -infinity, move toward finite (should become most negative finite)
TEST_F(NextAfterTest_638, FromNegativeInfinityTowardFinite_638) {
    double x = -numeric_limits<double>::infinity();
    double y = 0.0;

    double got = Catch::nextafter(x, y);

    EXPECT_TRUE(std::isfinite(got));
    EXPECT_LT(got, 0.0);
    EXPECT_DOUBLE_EQ(got, std::nextafter(x, y));
}

// Exceptional: NaN handling — if either argument is NaN, result is NaN
TEST_F(NextAfterTest_638, NaNPropagates_638) {
    const double NaN = std::numeric_limits<double>::quiet_NaN();

    double got1 = Catch::nextafter(NaN, 1.0);
    double got2 = Catch::nextafter(1.0, NaN);
    double got3 = Catch::nextafter(NaN, NaN);

    EXPECT_TRUE(std::isnan(got1));
    EXPECT_TRUE(std::isnan(got2));
    EXPECT_TRUE(std::isnan(got3));
}
