#include <gtest/gtest.h>

#include "SplashBitmap.h"



class SplashBitmapTest_1119 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state before each test (if needed)

        width = 10;

        height = 20;

        padding = 4;

        mode = static_cast<SplashColorMode>(0);

        alphaChannel = true;

        topDownOrder = false;



        separationListPtrVector = std::make_unique<std::vector<std::unique_ptr<GfxSeparationColorSpace>>>();

        separationListPtrInt = nullptr; // Assuming no separation list for simplicity



        splashBitmap = new SplashBitmap(width, height, padding, mode, alphaChannel, topDownOrder, separationListPtrVector.get());

    }



    void TearDown() override {

        // Clean up any resources after each test (if needed)

        delete splashBitmap;

    }



    int width;

    int height;

    int padding;

    SplashColorMode mode;

    bool alphaChannel;

    bool topDownOrder;

    std::unique_ptr<std::vector<std::unique_ptr<GfxSeparationColorSpace>>> separationListPtrVector;

    const int* separationListPtrInt;

    SplashBitmap* splashBitmap;

};



TEST_F(SplashBitmapTest_1119, GetRowSize_ReturnsCorrectValue_1119) {

    // Test that getRowSize returns the correct value based on width and padding

    EXPECT_EQ(splashBitmap->getRowSize(), width + padding);

}



TEST_F(SplashBitmapTest_1119, GetWidth_ReturnsCorrectValue_1119) {

    // Test that getWidth returns the width used during construction

    EXPECT_EQ(splashBitmap->getWidth(), width);

}



TEST_F(SplashBitmapTest_1119, GetHeight_ReturnsCorrectValue_1119) {

    // Test that getHeight returns the height used during construction

    EXPECT_EQ(splashBitmap->getHeight(), height);

}



TEST_F(SplashBitmapTest_1119, GetRowPad_ReturnsCorrectValue_1119) {

    // Test that getRowPad returns the padding used during construction

    EXPECT_EQ(splashBitmap->getRowPad(), padding);

}



TEST_F(SplashBitmapTest_1119, GetMode_ReturnsCorrectValue_1119) {

    // Test that getMode returns the color mode used during construction

    EXPECT_EQ(splashBitmap->getMode(), mode);

}



TEST_F(SplashBitmapTest_1119, GetAlphaRowSize_ReturnsCorrectValue_1119) {

    // Test that getAlphaRowSize returns the correct value based on width and padding

    EXPECT_EQ(splashBitmap->getAlphaRowSize(), width + padding);

}



TEST_F(SplashBitmapTest_1119, Copy_ReturnsNewInstanceWithSameProperties_1119) {

    // Test that copy creates a new instance with the same properties

    SplashBitmap* copiedBitmap = splashBitmap->copy(splashBitmap);



    EXPECT_EQ(copiedBitmap->getWidth(), width);

    EXPECT_EQ(copiedBitmap->getHeight(), height);

    EXPECT_EQ(copiedBitmap->getRowPad(), padding);

    EXPECT_EQ(copiedBitmap->getMode(), mode);

    EXPECT_EQ(copiedBitmap->getRowSize(), splashBitmap->getRowSize());

    EXPECT_EQ(copiedBitmap->getAlphaRowSize(), splashBitmap->getAlphaRowSize());



    delete copiedBitmap;

}



TEST_F(SplashBitmapTest_1119, GetSeparationList_ReturnsCorrectPointer_1119) {

    // Test that getSeparationList returns the correct pointer used during construction

    EXPECT_EQ(splashBitmap->getSeparationList(), separationListPtrVector.get());

}
