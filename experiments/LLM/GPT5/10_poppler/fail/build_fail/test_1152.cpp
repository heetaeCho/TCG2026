#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <optional>
#include "GfxFont.h"

class GfxFontTest_1152 : public ::testing::Test {
protected:
    std::unique_ptr<GfxFont> font;

    void SetUp() override {
        // Setup the font object here if needed
        font = std::make_unique<GfxFont>("tagA", 1, "Arial", GfxFontType::Type1, Ref(1));
    }
};

TEST_F(GfxFontTest_1152, IsSerifTrue_1152) {
    // Test for a serif font
    EXPECT_TRUE(font->isSerif());
}

TEST_F(GfxFontTest_1152, IsSerifFalse_1152) {
    // Test for a non-serif font
    EXPECT_FALSE(font->isSerif());
}

TEST_F(GfxFontTest_1152, GetFamily_1152) {
    // Test getting the font family
    EXPECT_EQ(font->getFamily()->c_str(), "Arial");
}

TEST_F(GfxFontTest_1152, IsFixedWidthTrue_1152) {
    // Test if the font is fixed width
    EXPECT_TRUE(font->isFixedWidth());
}

TEST_F(GfxFontTest_1152, IsFixedWidthFalse_1152) {
    // Test if the font is not fixed width
    EXPECT_FALSE(font->isFixedWidth());
}

TEST_F(GfxFontTest_1152, GetFontMatrix_1152) {
    // Test getting the font matrix
    const auto& matrix = font->getFontMatrix();
    EXPECT_EQ(matrix.size(), 6);
}

TEST_F(GfxFontTest_1152, GetFontBBox_1152) {
    // Test getting the font bounding box
    const auto& bbox = font->getFontBBox();
    EXPECT_EQ(bbox.size(), 4);
}

TEST_F(GfxFontTest_1152, GetAscent_1152) {
    // Test getting the ascent value
    EXPECT_GT(font->getAscent(), 0);
}

TEST_F(GfxFontTest_1152, GetDescent_1152) {
    // Test getting the descent value
    EXPECT_LT(font->getDescent(), 0);
}

TEST_F(GfxFontTest_1152, IsSymbolicTrue_1152) {
    // Test for symbolic font
    EXPECT_TRUE(font->isSymbolic());
}

TEST_F(GfxFontTest_1152, IsSymbolicFalse_1152) {
    // Test for non-symbolic font
    EXPECT_FALSE(font->isSymbolic());
}

TEST_F(GfxFontTest_1152, GetEncodingName_1152) {
    // Test getting the font encoding name
    EXPECT_EQ(font->getEncodingName(), "WinAnsiEncoding");
}

TEST_F(GfxFontTest_1152, GetTag_1152) {
    // Test getting the font tag
    EXPECT_EQ(font->getTag(), "tagA");
}

TEST_F(GfxFontTest_1152, GetID_1152) {
    // Test getting the font ID
    const Ref* id = font->getID();
    EXPECT_NE(id, nullptr);
}

TEST_F(GfxFontTest_1152, MatchesTrue_1152) {
    // Test matching the tag with the correct value
    EXPECT_TRUE(font->matches("tagA"));
}

TEST_F(GfxFontTest_1152, MatchesFalse_1152) {
    // Test non-matching tag
    EXPECT_FALSE(font->matches("tagB"));
}

TEST_F(GfxFontTest_1152, IsOkTrue_1152) {
    // Test the 'isOk' method when the font is valid
    EXPECT_TRUE(font->isOk());
}

TEST_F(GfxFontTest_1152, IsOkFalse_1152) {
    // Test the 'isOk' method when the font is invalid
    font = nullptr;
    EXPECT_FALSE(font->isOk());
}

TEST_F(GfxFontTest_1152, GetNextChar_1152) {
    // Test getting the next character
    const char* s = "test";
    int len = 4;
    CharCode code;
    const Unicode* u;
    int uLen;
    double dx, dy, ox, oy;

    int result = font->getNextChar(s, len, &code, &u, &uLen, &dx, &dy, &ox, &oy);
    EXPECT_EQ(result, 0);  // Assuming 0 is a valid return code
}