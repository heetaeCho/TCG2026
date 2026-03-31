#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <array>

#include "splash/SplashFont.h"
#include "splash/SplashFontFile.h"
#include "splash/SplashPath.h"
#include "splash/SplashClip.h"
#include "splash/SplashTypes.h"

// A concrete subclass to allow instantiation and testing of SplashFont
class TestSplashFont : public SplashFont {
public:
    TestSplashFont(const std::shared_ptr<SplashFontFile> &fontFileA,
                   const std::array<SplashCoord, 4> &matA,
                   const std::array<SplashCoord, 4> &textMatA,
                   bool aaA)
        : SplashFont(fontFileA, matA, textMatA, aaA) {}

    // Set bounding box for testing
    void setBBox(int xMinVal, int yMinVal, int xMaxVal, int yMaxVal) {
        xMin = xMinVal;
        yMin = yMinVal;
        xMax = xMaxVal;
        yMax = yMaxVal;
    }

    bool makeGlyph(int c, int xFrac, int yFrac, SplashGlyphBitmap *bitmap,
                   int x0, int y0, SplashClip *clip, SplashClipResult *clipRes) override {
        return false;
    }

    SplashPath *getGlyphPath(int c) override {
        return nullptr;
    }
};

class SplashFontTest_1555 : public ::testing::Test {
protected:
    void SetUp() override {
        mat = {1.0, 0.0, 0.0, 1.0};
        textMat = {1.0, 0.0, 0.0, 1.0};
    }

    std::array<SplashCoord, 4> mat;
    std::array<SplashCoord, 4> textMat;
};

// Test getBBox returns correct values for typical bounding box
TEST_F(SplashFontTest_1555, GetBBoxReturnsCorrectValues_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    font->setBBox(10, 20, 30, 40);

    int xMinA, yMinA, xMaxA, yMaxA;
    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_EQ(xMinA, 10);
    EXPECT_EQ(yMinA, 20);
    EXPECT_EQ(xMaxA, 30);
    EXPECT_EQ(yMaxA, 40);
}

// Test getBBox with zero bounding box
TEST_F(SplashFontTest_1555, GetBBoxZeroValues_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    font->setBBox(0, 0, 0, 0);

    int xMinA, yMinA, xMaxA, yMaxA;
    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_EQ(xMinA, 0);
    EXPECT_EQ(yMinA, 0);
    EXPECT_EQ(xMaxA, 0);
    EXPECT_EQ(yMaxA, 0);
}

// Test getBBox with negative values
TEST_F(SplashFontTest_1555, GetBBoxNegativeValues_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    font->setBBox(-100, -200, -10, -20);

    int xMinA, yMinA, xMaxA, yMaxA;
    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_EQ(xMinA, -100);
    EXPECT_EQ(yMinA, -200);
    EXPECT_EQ(xMaxA, -10);
    EXPECT_EQ(yMaxA, -20);
}

// Test getBBox with large values
TEST_F(SplashFontTest_1555, GetBBoxLargeValues_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    font->setBBox(INT_MIN, INT_MIN, INT_MAX, INT_MAX);

    int xMinA, yMinA, xMaxA, yMaxA;
    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_EQ(xMinA, INT_MIN);
    EXPECT_EQ(yMinA, INT_MIN);
    EXPECT_EQ(xMaxA, INT_MAX);
    EXPECT_EQ(yMaxA, INT_MAX);
}

// Test matches returns true when font file and matrices match
TEST_F(SplashFontTest_1555, MatchesReturnsTrueForSameParams_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    EXPECT_TRUE(font->matches(nullptr, mat, textMat));
}

// Test matches returns false when matrices differ
TEST_F(SplashFontTest_1555, MatchesReturnsFalseForDifferentMat_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    std::array<SplashCoord, 4> differentMat = {2.0, 0.0, 0.0, 2.0};
    EXPECT_FALSE(font->matches(nullptr, differentMat, textMat));
}

// Test matches returns false when textMat differs
TEST_F(SplashFontTest_1555, MatchesReturnsFalseForDifferentTextMat_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    std::array<SplashCoord, 4> differentTextMat = {2.0, 0.0, 0.0, 2.0};
    EXPECT_FALSE(font->matches(nullptr, mat, differentTextMat));
}

// Test getFontFile returns the font file passed in constructor
TEST_F(SplashFontTest_1555, GetFontFileReturnsCorrectFile_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    EXPECT_EQ(font->getFontFile(), nullptr);
}

// Test getGlyphPath returns nullptr for the test subclass
TEST_F(SplashFontTest_1555, GetGlyphPathReturnsNullptr_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    SplashPath *path = font->getGlyphPath(0);
    EXPECT_EQ(path, nullptr);
}

// Test getBBox after changing values
TEST_F(SplashFontTest_1555, GetBBoxAfterUpdate_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    font->setBBox(1, 2, 3, 4);

    int xMinA, yMinA, xMaxA, yMaxA;
    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);
    EXPECT_EQ(xMinA, 1);
    EXPECT_EQ(yMinA, 2);
    EXPECT_EQ(xMaxA, 3);
    EXPECT_EQ(yMaxA, 4);

    font->setBBox(100, 200, 300, 400);
    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);
    EXPECT_EQ(xMinA, 100);
    EXPECT_EQ(yMinA, 200);
    EXPECT_EQ(xMaxA, 300);
    EXPECT_EQ(yMaxA, 400);
}

// Test getBBox with mixed positive and negative
TEST_F(SplashFontTest_1555, GetBBoxMixedValues_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    font->setBBox(-50, -30, 50, 30);

    int xMinA, yMinA, xMaxA, yMaxA;
    font->getBBox(&xMinA, &yMinA, &xMaxA, &yMaxA);

    EXPECT_EQ(xMinA, -50);
    EXPECT_EQ(yMinA, -30);
    EXPECT_EQ(xMaxA, 50);
    EXPECT_EQ(yMaxA, 30);
}

// Test getGlyphAdvance default behavior
TEST_F(SplashFontTest_1555, GetGlyphAdvanceDefault_1555) {
    auto font = std::make_unique<TestSplashFont>(nullptr, mat, textMat, false);
    // Default implementation likely returns 0 or some default
    double advance = font->getGlyphAdvance(65); // 'A'
    EXPECT_GE(advance, 0.0);
}
