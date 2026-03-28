#include <gtest/gtest.h>



// Assuming the function is part of a class or namespace, we'll mock it as a standalone for testing purposes.

class Splash {

public:

    static bool isImageInterpolationRequired(int srcWidth, int srcHeight, int scaledWidth, int scaledHeight, bool interpolate);

};



TEST(SplashTest_2615, InterpolateTrue_ReturnsTrue_2615) {

    EXPECT_TRUE(Splash::isImageInterpolationRequired(100, 100, 200, 200, true));

}



TEST(SplashTest_2615, ZeroSrcWidth_ReturnsTrue_2615) {

    EXPECT_TRUE(Splash::isImageInterpolationRequired(0, 100, 200, 200, false));

}



TEST(SplashTest_2615, ZeroSrcHeight_ReturnsTrue_2615) {

    EXPECT_TRUE(Splash::isImageInterpolationRequired(100, 0, 200, 200, false));

}



TEST(SplashTest_2615, ScaleFactor4OrMoreWidth_ReturnsFalse_2615) {

    EXPECT_FALSE(Splash::isImageInterpolationRequired(100, 100, 400, 99, false));

}



TEST(SplashTest_2615, ScaleFactor4OrMoreHeight_ReturnsFalse_2615) {

    EXPECT_FALSE(Splash::isImageInterpolationRequired(100, 100, 99, 400, false));

}



TEST(SplashTest_2615, ScaleFactorLessThan4_ReturnsTrue_2615) {

    EXPECT_TRUE(Splash::isImageInterpolationRequired(100, 100, 399, 399, false));

}



TEST(SplashTest_2615, NormalOperation_ReturnsTrue_2615) {

    EXPECT_TRUE(Splash::isImageInterpolationRequired(100, 100, 200, 200, false));

}
