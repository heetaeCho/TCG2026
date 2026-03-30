#include <gtest/gtest.h>

#include <cmath> // For std::fabs and std::fabsf

#include "SplashMath.h"



// Define a fixture for the tests if needed, but in this case it's not necessary.



TEST(splashAbsTest_1556, PositiveValue_1556) {

    SplashCoord input = 42.0;

    EXPECT_EQ(splashAbs(input), 42.0);

}



TEST(splashAbsTest_1556, NegativeValue_1556) {

    SplashCoord input = -42.0;

    EXPECT_EQ(splashAbs(input), 42.0);

}



TEST(splashAbsTest_1556, ZeroValue_1556) {

    SplashCoord input = 0.0;

    EXPECT_EQ(splashAbs(input), 0.0);

}



TEST(splashAbsTest_1556, MaxPositive_1556) {

    SplashCoord input = std::numeric_limits<SplashCoord>::max();

    EXPECT_EQ(splashAbs(input), std::numeric_limits<SplashCoord>::max());

}



TEST(splashAbsTest_1556, MinNegative_1556) {

    SplashCoord input = std::numeric_limits<SplashCoord>::lowest();

    #if USE_FLOAT

    // For float, the absolute value of the lowest negative is the same as max positive due to representation.

    EXPECT_EQ(splashAbs(input), -std::numeric_limits<SplashCoord>::lowest());

    #else

    // For double, we can directly compare.

    EXPECT_EQ(splashAbs(input), -std::numeric_limits<SplashCoord>::lowest());

    #endif

}
