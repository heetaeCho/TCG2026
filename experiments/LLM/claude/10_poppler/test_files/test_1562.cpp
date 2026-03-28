#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header under test
#include "splash/SplashMath.h"

class SplashPowTest_1562 : public ::testing::Test {
protected:
    // Helper to compare floating point values with tolerance
    void expectNear(SplashCoord actual, SplashCoord expected, SplashCoord tolerance = 1e-6) {
        EXPECT_NEAR(actual, expected, tolerance);
    }
};

// Normal operation tests

TEST_F(SplashPowTest_1562, PositiveBasePositiveExponent_1562) {
    SplashCoord result = splashPow(2.0, 3.0);
    expectNear(result, 8.0);
}

TEST_F(SplashPowTest_1562, PositiveBaseIntegerExponent_1562) {
    SplashCoord result = splashPow(3.0, 2.0);
    expectNear(result, 9.0);
}

TEST_F(SplashPowTest_1562, PositiveBaseFractionalExponent_1562) {
    SplashCoord result = splashPow(4.0, 0.5);
    expectNear(result, 2.0);
}

TEST_F(SplashPowTest_1562, BaseGreaterThanOneExponentOne_1562) {
    SplashCoord result = splashPow(5.0, 1.0);
    expectNear(result, 5.0);
}

TEST_F(SplashPowTest_1562, BaseOneAnyExponent_1562) {
    SplashCoord result = splashPow(1.0, 100.0);
    expectNear(result, 1.0);
}

TEST_F(SplashPowTest_1562, BaseTenExponentThree_1562) {
    SplashCoord result = splashPow(10.0, 3.0);
    expectNear(result, 1000.0);
}

TEST_F(SplashPowTest_1562, LargeExponent_1562) {
    SplashCoord result = splashPow(2.0, 10.0);
    expectNear(result, 1024.0);
}

TEST_F(SplashPowTest_1562, FractionalBaseFractionalExponent_1562) {
    SplashCoord result = splashPow(0.25, 0.5);
    expectNear(result, 0.5);
}

// Boundary condition tests

TEST_F(SplashPowTest_1562, ExponentZero_1562) {
    SplashCoord result = splashPow(5.0, 0.0);
    expectNear(result, 1.0);
}

TEST_F(SplashPowTest_1562, BaseZeroExponentZero_1562) {
    // pow(0, 0) is typically defined as 1
    SplashCoord result = splashPow(0.0, 0.0);
    expectNear(result, 1.0);
}

TEST_F(SplashPowTest_1562, BaseZeroPositiveExponent_1562) {
    SplashCoord result = splashPow(0.0, 5.0);
    expectNear(result, 0.0);
}

TEST_F(SplashPowTest_1562, NegativeExponent_1562) {
    SplashCoord result = splashPow(2.0, -1.0);
    expectNear(result, 0.5);
}

TEST_F(SplashPowTest_1562, NegativeExponentTwo_1562) {
    SplashCoord result = splashPow(2.0, -2.0);
    expectNear(result, 0.25);
}

TEST_F(SplashPowTest_1562, NegativeBaseIntegerExponent_1562) {
    SplashCoord result = splashPow(-2.0, 3.0);
    expectNear(result, -8.0);
}

TEST_F(SplashPowTest_1562, NegativeBaseEvenExponent_1562) {
    SplashCoord result = splashPow(-2.0, 2.0);
    expectNear(result, 4.0);
}

TEST_F(SplashPowTest_1562, SmallPositiveBase_1562) {
    SplashCoord result = splashPow(0.001, 1.0);
    expectNear(result, 0.001);
}

TEST_F(SplashPowTest_1562, VerySmallExponent_1562) {
    SplashCoord result = splashPow(100.0, 0.001);
    // 100^0.001 = e^(0.001 * ln(100))
    SplashCoord expected = std::pow(100.0, 0.001);
    expectNear(result, expected, 1e-4);
}

TEST_F(SplashPowTest_1562, CubeRoot_1562) {
    SplashCoord result = splashPow(27.0, 1.0 / 3.0);
    expectNear(result, 3.0, 1e-5);
}

// Special / Exceptional cases

TEST_F(SplashPowTest_1562, NegativeBaseFractionalExponentProducesNaN_1562) {
    SplashCoord result = splashPow(-1.0, 0.5);
    EXPECT_TRUE(std::isnan(result));
}

TEST_F(SplashPowTest_1562, InfinityBase_1562) {
    SplashCoord inf = std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashPow(inf, 2.0);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0);
}

TEST_F(SplashPowTest_1562, InfinityExponent_1562) {
    SplashCoord inf = std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashPow(2.0, inf);
    EXPECT_TRUE(std::isinf(result));
}

TEST_F(SplashPowTest_1562, BaseOneInfinityExponent_1562) {
    SplashCoord inf = std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashPow(1.0, inf);
    // pow(1, inf) = 1 per IEEE
    expectNear(result, 1.0);
}

TEST_F(SplashPowTest_1562, BaseBetweenZeroAndOneInfExponent_1562) {
    SplashCoord inf = std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashPow(0.5, inf);
    expectNear(result, 0.0);
}

TEST_F(SplashPowTest_1562, BaseBetweenZeroAndOneNegInfExponent_1562) {
    SplashCoord negInf = -std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashPow(0.5, negInf);
    EXPECT_TRUE(std::isinf(result));
}

TEST_F(SplashPowTest_1562, IdentityPowOneReturnsBase_1562) {
    SplashCoord values[] = {0.1, 1.0, 2.5, 100.0, 0.0001};
    for (SplashCoord v : values) {
        SplashCoord result = splashPow(v, 1.0);
        expectNear(result, v, 1e-5);
    }
}

TEST_F(SplashPowTest_1562, SquareRootOf9_1562) {
    SplashCoord result = splashPow(9.0, 0.5);
    expectNear(result, 3.0);
}

TEST_F(SplashPowTest_1562, ConsistencyWithStdPow_1562) {
    // Verify consistency across several values
    double testCases[][2] = {
        {2.0, 3.0}, {3.5, 2.1}, {0.5, 4.0}, {10.0, 0.3}, {1.5, 7.0}
    };
    for (auto& tc : testCases) {
        SplashCoord result = splashPow(tc[0], tc[1]);
#if USE_FLOAT
        SplashCoord expected = powf((float)tc[0], (float)tc[1]);
#else
        SplashCoord expected = pow(tc[0], tc[1]);
#endif
        expectNear(result, expected, 1e-4);
    }
}
