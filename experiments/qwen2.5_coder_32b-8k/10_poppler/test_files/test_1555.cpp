#include <gtest/gtest.h>

#include "SplashFont.h"



class SplashFontTest : public ::testing::Test {

protected:

    std::shared_ptr<SplashFontFile> fontFile;

    std::array<SplashCoord, 4> mat = {1.0, 0.0, 0.0, 1.0};

    std::array<SplashCoord, 4> textMat = {1.0, 0.0, 0.0, 1.0};

    SplashFont* font;



    void SetUp() override {

        fontFile = std::make_shared<SplashFontFile>();

        font = new SplashFont(fontFile, mat, textMat, true);

    }



    void TearDown() override {

        delete font;

    }

};



TEST_F(SplashFontTest_1555, GetBBox_ReturnsCorrectValues_1555) {

    int xMinA, yMinA, xMaxA, yMaxA;

    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_EQ(xMinA, font->xMin);

    EXPECT_EQ(yMinA, font->yMin);

    EXPECT_EQ(xMaxA, font->xMax);

    EXPECT_EQ(yMaxA, font->yMax);

}



TEST_F(SplashFontTest_1555, GetBBox_DoesNotModifyInputValues_1555) {

    int xMinA = 0, yMinA = 0, xMaxA = 0, yMaxA = 0;

    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_NE(xMinA, 0);

    EXPECT_NE(yMinA, 0);

    EXPECT_NE(xMaxA, 0);

    EXPECT_NE(yMaxA, 0);

}



TEST_F(SplashFontTest_1555, GetFontFile_ReturnsCorrectFontFile_1555) {

    std::shared_ptr<SplashFontFile> retrievedFontFile = font->getFontFile();

    EXPECT_EQ(retrievedFontFile, fontFile);

}



TEST_F(SplashFontTest_1555, Matches_ReturnsTrueForSameParameters_1555) {

    bool result = font->matches(fontFile, mat, textMat);

    EXPECT_TRUE(result);

}



TEST_F(SplashFontTest_1555, Matches_ReturnsFalseForDifferentFontFile_1555) {

    auto differentFontFile = std::make_shared<SplashFontFile>();

    bool result = font->matches(differentFontFile, mat, textMat);

    EXPECT_FALSE(result);

}



TEST_F(SplashFontTest_1555, Matches_ReturnsFalseForDifferentMatrix_1555) {

    std::array<SplashCoord, 4> differentMat = {2.0, 0.0, 0.0, 2.0};

    bool result = font->matches(fontFile, differentMat, textMat);

    EXPECT_FALSE(result);

}



TEST_F(SplashFontTest_1555, Matches_ReturnsFalseForDifferentTextMatrix_1555) {

    std::array<SplashCoord, 4> differentTextMat = {2.0, 0.0, 0.0, 2.0};

    bool result = font->matches(fontFile, mat, differentTextMat);

    EXPECT_FALSE(result);

}
