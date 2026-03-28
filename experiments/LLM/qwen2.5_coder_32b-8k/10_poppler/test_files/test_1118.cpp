#include <gtest/gtest.h>

#include "SplashBitmap.h"

#include <memory>

#include <vector>



class SplashBitmapTest_1118 : public ::testing::Test {

protected:

    std::unique_ptr<SplashBitmap> bitmap;



    void SetUp() override {

        bitmap = std::make_unique<SplashBitmap>(10, 20, 4, static_cast<SplashColorMode>(1), false, true, nullptr);

    }

};



TEST_F(SplashBitmapTest_1118, GetHeight_ReturnsCorrectValue_1118) {

    EXPECT_EQ(20, bitmap->getHeight());

}



TEST_F(SplashBitmapTest_1118, GetWidth_ReturnsCorrectValue_1118) {

    EXPECT_EQ(10, bitmap->getWidth());

}



TEST_F(SplashBitmapTest_1118, GetRowSize_ReturnsCorrectValue_1118) {

    // Assuming row size is calculated as width * number of color components

    EXPECT_EQ(40, bitmap->getRowSize()); // 10 pixels * 4 bytes per pixel

}



TEST_F(SplashBitmapTest_1118, GetRowPad_ReturnsCorrectValue_1118) {

    EXPECT_EQ(4, bitmap->getRowPad());

}



TEST_F(SplashBitmapTest_1118, GetMode_ReturnsCorrectValue_1118) {

    EXPECT_EQ(static_cast<SplashColorMode>(1), bitmap->getMode());

}



TEST_F(SplashBitmapTest_1118, GetAlphaRowSize_ReturnsZeroWhenNoAlpha_1118) {

    EXPECT_EQ(0, bitmap->getAlphaRowSize());

}



TEST_F(SplashBitmapTest_1118, GetDataPtr_ReturnsNonNullPointer_1118) {

    EXPECT_NE(nullptr, bitmap->getDataPtr());

}



TEST_F(SplashBitmapTest_1118, GetAlphaPtr_ReturnsNullPointerWhenNoAlpha_1118) {

    EXPECT_EQ(nullptr, bitmap->getAlphaPtr());

}



TEST_F(SplashBitmapTest_1118, GetSeparationList_ReturnsNonNullPointer_1118) {

    EXPECT_NE(nullptr, bitmap->getSeparationList());

}



TEST_F(SplashBitmapTest_1118, BoundaryCondition_ZeroWidth_1118) {

    auto zero_width_bitmap = std::make_unique<SplashBitmap>(0, 20, 4, static_cast<SplashColorMode>(1), false, true, nullptr);

    EXPECT_EQ(0, zero_width_bitmap->getWidth());

    EXPECT_EQ(0, zero_width_bitmap->getRowSize());

}



TEST_F(SplashBitmapTest_1118, BoundaryCondition_ZeroHeight_1118) {

    auto zero_height_bitmap = std::make_unique<SplashBitmap>(10, 0, 4, static_cast<SplashColorMode>(1), false, true, nullptr);

    EXPECT_EQ(0, zero_height_bitmap->getHeight());

}



TEST_F(SplashBitmapTest_1118, BoundaryCondition_ZeroRowPad_1118) {

    auto zero_rowpad_bitmap = std::make_unique<SplashBitmap>(10, 20, 0, static_cast<SplashColorMode>(1), false, true, nullptr);

    EXPECT_EQ(0, zero_rowpad_bitmap->getRowPad());

}



TEST_F(SplashBitmapTest_1118, GetAlpha_ReturnsZeroWhenNoAlpha_1118) {

    EXPECT_EQ(0, bitmap->getAlpha(5, 5));

}
