#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashBitmap.h"

#include <vector>

#include <memory>



class SplashBitmapTest : public ::testing::Test {

protected:

    std::unique_ptr<SplashBitmap> bitmap;



    void SetUp() override {

        // Initialize a SplashBitmap object with some arbitrary values

        bitmap = std::make_unique<SplashBitmap>(10, 20, 4, (SplashColorMode)0, false, true, static_cast<const int*>(nullptr));

    }

};



TEST_F(SplashBitmapTest_1121, GetRowPad_ReturnsCorrectValue_1121) {

    // Test that getRowPad returns the correct value set during initialization

    EXPECT_EQ(bitmap->getRowPad(), 4);

}



TEST_F(SplashBitmapTest_1121, GetWidth_ReturnsNonNegativeValue_1121) {

    // Test that getWidth returns a non-negative value

    EXPECT_GE(bitmap->getWidth(), 0);

}



TEST_F(SplashBitmapTest_1121, GetHeight_ReturnsNonNegativeValue_1121) {

    // Test that getHeight returns a non-negative value

    EXPECT_GE(bitmap->getHeight(), 0);

}



TEST_F(SplashBitmapTest_1121, GetRowSize_ReturnsNonNegativeValue_1121) {

    // Test that getRowSize returns a non-negative value

    EXPECT_GE(bitmap->getRowSize(), 0);

}



TEST_F(SplashBitmapTest_1121, GetAlphaRowSize_ReturnsNonNegativeValue_1121) {

    // Test that getAlphaRowSize returns a non-negative value

    EXPECT_GE(bitmap->getAlphaRowSize(), 0);

}



TEST_F(SplashBitmapTest_1121, GetMode_ReturnsValidColorMode_1121) {

    // Assuming SplashColorMode is an enum with valid values starting from 0

    auto mode = bitmap->getMode();

    EXPECT_GE(mode, 0); // Placeholder assumption; actual range should be known

}



TEST_F(SplashBitmapTest_1121, GetDataPtr_ReturnsNonNullPointer_1121) {

    // Test that getDataPtr returns a non-null pointer

    EXPECT_NE(bitmap->getDataPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1121, GetAlphaPtr_ReturnsNonNullPointerWhenAlphaEnabled_1121) {

    // Initialize a SplashBitmap object with alpha enabled

    auto bitmapWithAlpha = std::make_unique<SplashBitmap>(10, 20, 4, (SplashColorMode)0, true, true, static_cast<const int*>(nullptr));

    

    // Test that getAlphaPtr returns a non-null pointer when alpha is enabled

    EXPECT_NE(bitmapWithAlpha->getAlphaPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1121, GetAlphaPtr_ReturnsNullPointerWhenAlphaDisabled_1121) {

    // Test that getAlphaPtr returns a null pointer when alpha is disabled

    EXPECT_EQ(bitmap->getAlphaPtr(), nullptr);

}



TEST_F(SplashBitmapTest_1121, GetSeparationList_ReturnsNonNullPointer_1121) {

    // Initialize a SplashBitmap object with separation list enabled

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepList;

    auto bitmapWithSepList = std::make_unique<SplashBitmap>(10, 20, 4, (SplashColorMode)0, false, true, &sepList);

    

    // Test that getSeparationList returns a non-null pointer when separation list is enabled

    EXPECT_NE(bitmapWithSepList->getSeparationList(), nullptr);

}



TEST_F(SplashBitmapTest_1121, GetSeparationList_ReturnsNullPointerWhenNotProvided_1121) {

    // Test that getSeparationList returns a null pointer when separation list is not provided

    EXPECT_EQ(bitmap->getSeparationList(), nullptr);

}
