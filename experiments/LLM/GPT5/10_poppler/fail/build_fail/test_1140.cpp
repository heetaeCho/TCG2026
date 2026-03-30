#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"

// Mocking dependencies if needed
class XRefMock : public XRef {
    // Mocked methods here if necessary
};

// TEST_F for normal operation
TEST_F(GfxFontTest_1140, Matches_ReturnsTrueForMatchingTag_1140) {
    const char *tagA = "Helvetica";
    GfxFont font(tagA, /* idA= */ 1, /* nameA= */ std::make_optional<std::string>("Helvetica"), GfxFontType::Type1, /* embFontIDA= */ 1);
    EXPECT_TRUE(font.matches(tagA));
}

TEST_F(GfxFontTest_1141, Matches_ReturnsFalseForNonMatchingTag_1141) {
    const char *tagA = "Helvetica";
    const char *nonMatchingTag = "TimesNewRoman";
    GfxFont font(tagA, /* idA= */ 1, /* nameA= */ std::make_optional<std::string>("Helvetica"), GfxFontType::Type1, /* embFontIDA= */ 1);
    EXPECT_FALSE(font.matches(nonMatchingTag));
}

// TEST_F for boundary conditions
TEST_F(GfxFontTest_1142, GetFontMatrix_ReturnsExpectedMatrix_1142) {
    const char *tagA = "Helvetica";
    GfxFont font(tagA, /* idA= */ 1, /* nameA= */ std::make_optional<std::string>("Helvetica"), GfxFontType::Type1, /* embFontIDA= */ 1);

    std::array<double, 6> expectedMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_EQ(font.getFontMatrix(), expectedMatrix);
}

TEST_F(GfxFontTest_1143, GetFontBBox_ReturnsExpectedBBox_1143) {
    const char *tagA = "Helvetica";
    GfxFont font(tagA, /* idA= */ 1, /* nameA= */ std::make_optional<std::string>("Helvetica"), GfxFontType::Type1, /* embFontIDA= */ 1);

    std::array<double, 4> expectedBBox = {0.0, 0.0, 0.0, 0.0};
    EXPECT_EQ(font.getFontBBox(), expectedBBox);
}

// TEST_F for exceptional or error cases
TEST_F(GfxFontTest_1144, InvalidFont_ReturnsFalse_1144) {
    const char *tagA = "InvalidFont";
    GfxFont font(tagA, /* idA= */ 1, /* nameA= */ std::make_optional<std::string>("InvalidFont"), GfxFontType::Type1, /* embFontIDA= */ 1);

    EXPECT_FALSE(font.isOk());
}

// TEST_F for verifying external interactions (mocking external calls if needed)
TEST_F(GfxFontTest_1145, LocateFont_ReturnsFontLocation_1145) {
    XRefMock xref;
    PSOutputDev psOutputDev;
    GooString substituteFontName("Arial");

    const char *tagA = "Helvetica";
    GfxFont font(tagA, /* idA= */ 1, /* nameA= */ std::make_optional<std::string>("Helvetica"), GfxFontType::Type1, /* embFontIDA= */ 1);

    std::optional<GfxFontLoc> fontLoc = font.locateFont(&xref, &psOutputDev, &substituteFontName);
    EXPECT_TRUE(fontLoc.has_value());
}

// TEST_F for boundary conditions related to attributes
TEST_F(GfxFontTest_1146, GetAscent_ReturnsValidAscent_1146) {
    const char *tagA = "Helvetica";
    GfxFont font(tagA, /* idA= */ 1, /* nameA= */ std::make_optional<std::string>("Helvetica"), GfxFontType::Type1, /* embFontIDA= */ 1);

    double ascent = font.getAscent();
    EXPECT_GT(ascent, 0.0);
}

TEST_F(GfxFontTest_1147, GetDescent_ReturnsValidDescent_1147) {
    const char *tagA = "Helvetica";
    GfxFont font(tagA, /* idA= */ 1, /* nameA= */ std::make_optional<std::string>("Helvetica"), GfxFontType::Type1, /* embFontIDA= */ 1);

    double descent = font.getDescent();
    EXPECT_LT(descent, 0.0);
}