#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



class SplashOutputDevTest_1112 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any needed state or objects here

        splash_output_dev = new SplashOutputDev(SplashColorModeRGB8, 4, nullptr, true, splashThinLineDefault, false);

    }



    void TearDown() override {

        // Clean up and release resources here

        delete splash_output_dev;

    }



    SplashOutputDev* splash_output_dev;

};



TEST_F(SplashOutputDevTest_1112, GetCurrentFont_NormalOperation_1112) {

    // Test the normal operation of getCurrentFont()

    // Since we don't have control over setting a font, we can only check if it returns nullptr or not

    EXPECT_EQ(splash_output_dev->getCurrentFont(), nullptr);

}



TEST_F(SplashOutputDevTest_1112, GetCurrentFont_AfterUpdateFont_1112) {

    // Mock or simulate an updateFont call and then check the getCurrentFont()

    // Since we cannot directly set a font, this test assumes that after an updateFont call, getCurrentFont() returns a valid pointer

    GfxState* state = nullptr; // Placeholder for actual GfxState object

    splash_output_dev->updateFont(state);

    EXPECT_NE(splash_output_dev->getCurrentFont(), nullptr);

}



TEST_F(SplashOutputDevTest_1112, GetCurrentFont_ExceptionalCase_1112) {

    // Test the exceptional case where getCurrentFont() might return nullptr after some operations

    // Since we cannot control internal state changes leading to this condition, this test is hypothetical

    // Assuming there's an operation that might reset the font pointer

    GfxState* state = nullptr; // Placeholder for actual GfxState object

    splash_output_dev->updateFont(state);

    // Perform some operations that might lead to resetting the font pointer

    splash_output_dev->endPage();

    EXPECT_EQ(splash_output_dev->getCurrentFont(), nullptr);

}



TEST_F(SplashOutputDevTest_1112, GetVectorAntialias_NormalOperation_1112) {

    // Test the normal operation of getVectorAntialias()

    bool vector_antialias = splash_output_dev->getVectorAntialias();

    EXPECT_EQ(vector_antialias, false); // Default value is assumed to be false

}



TEST_F(SplashOutputDevTest_1112, SetAndGetVectorAntialias_NormalOperation_1112) {

    // Test setting and getting vector antialias

    splash_output_dev->setVectorAntialias(true);

    bool vector_antialias = splash_output_dev->getVectorAntialias();

    EXPECT_EQ(vector_antialias, true);



    splash_output_dev->setVectorAntialias(false);

    vector_antialias = splash_output_dev->getVectorAntialias();

    EXPECT_EQ(vector_antialias, false);

}



TEST_F(SplashOutputDevTest_1112, GetFontAntialias_NormalOperation_1112) {

    // Test the normal operation of getFontAntialias()

    bool font_antialias = splash_output_dev->getFontAntialias();

    EXPECT_EQ(font_antialias, true); // Default value is assumed to be true

}



TEST_F(SplashOutputDevTest_1112, SetAndGetFontAntialias_NormalOperation_1112) {

    // Test setting and getting font antialias

    splash_output_dev->setFontAntialias(false);

    bool font_antialias = splash_output_dev->getFontAntialias();

    EXPECT_EQ(font_antialias, false);



    splash_output_dev->setFontAntialias(true);

    font_antialias = splash_output_dev->getFontAntialias();

    EXPECT_EQ(font_antialias, true);

}



TEST_F(SplashOutputDevTest_1112, SetEnableFreeType_NormalOperation_1112) {

    // Test setting enableFreeType

    splash_output_dev->setEnableFreeType(false);

    splash_output_dev->setEnableFreeType(true);

}
