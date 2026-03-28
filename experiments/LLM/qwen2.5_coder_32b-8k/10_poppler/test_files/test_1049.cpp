#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/splash/SplashPattern.h"



using namespace testing;



class SplashSolidColorTest_1049 : public ::testing::Test {

protected:

    void SetUp() override {

        color[0] = 0.5f;

        color[1] = 0.3f;

        color[2] = 0.8f;

        color[3] = 1.0f;



        splashColorPtr[0] = 0.0f;

        splashColorPtr[1] = 0.0f;

        splashColorPtr[2] = 0.0f;

        splashColorPtr[3] = 0.0f;



        solidColor = new SplashSolidColor(color);

    }



    void TearDown() override {

        delete solidColor;

    }



    SplashColor color;

    SplashColorPtr splashColorPtr;

    SplashSolidColor* solidColor;

};



TEST_F(SplashSolidColorTest_1049, CopyCreatesNewInstance_1049) {

    auto copiedColor = static_cast<SplashSolidColor*>(solidColor->copy());

    EXPECT_NE(copiedColor, solidColor);

    delete copiedColor;

}



TEST_F(SplashSolidColorTest_1049, GetColorSetsCorrectValues_1049) {

    bool result = solidColor->getColor(0, 0, splashColorPtr);

    EXPECT_TRUE(result);

    EXPECT_FLOAT_EQ(splashColorPtr[0], color[0]);

    EXPECT_FLOAT_EQ(splashColorPtr[1], color[1]);

    EXPECT_FLOAT_EQ(splashColorPtr[2], color[2]);

    EXPECT_FLOAT_EQ(splashColorPtr[3], color[3]);

}



TEST_F(SplashSolidColorTest_1049, TestPositionAlwaysTrue_1049) {

    bool result = solidColor->testPosition(0, 0);

    EXPECT_TRUE(result);

}



TEST_F(SplashSolidColorTest_1049, IsStaticReturnsTrue_1049) {

    bool result = solidColor->isStatic();

    EXPECT_TRUE(result);

}



TEST_F(SplashSolidColorTest_1049, IsCMYKReturnsFalseForNonCMYK_1049) {

    bool result = solidColor->isCMYK();

    EXPECT_FALSE(result); // Assuming isCMYK returns false for non-CMYK colors

}
