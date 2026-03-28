#include <gtest/gtest.h>
#include "GfxFont.h"

TEST_F(GfxFontTest_1138, GetTag_1138) {
    // Test normal operation of getTag()
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    EXPECT_EQ(font.getTag(), "tag");
}

TEST_F(GfxFontTest_1138, IsSubset_1138) {
    // Test normal operation of isSubset()
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    // Assuming default is false for simplicity, adjust based on actual logic
    EXPECT_FALSE(font.isSubset());
}

TEST_F(GfxFontTest_1138, GetNameWithoutSubsetTag_1138) {
    // Test normal operation of getNameWithoutSubsetTag()
    GfxFont font("tag", Ref(1), "fontName", GfxFontType::TrueType, Ref(2));
    EXPECT_EQ(font.getNameWithoutSubsetTag(), "fontName");
}

TEST_F(GfxFontTest_1138, IsSubsetBoundary_1138) {
    // Boundary test case for isSubset (e.g., invalid/edge cases)
    GfxFont font("", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    EXPECT_FALSE(font.isSubset());
}

TEST_F(GfxFontTest_1138, ReadEmbFontFile_1138) {
    // Test the readEmbFontFile method for normal behavior
    XRef xref;
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    auto result = font.readEmbFontFile(&xref);
    EXPECT_TRUE(result.has_value());  // Assuming the function returns an optional value
}

TEST_F(GfxFontTest_1138, LocateFont_1138) {
    // Test locateFont for normal operation
    XRef xref;
    PSOutputDev ps;
    GooString substituteFontName("substituteFont");
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    auto result = font.locateFont(&xref, &ps, &substituteFontName);
    EXPECT_TRUE(result.has_value());  // Expecting optional containing font location
}

TEST_F(GfxFontTest_1138, GetFamily_1138) {
    // Test normal operation of getFamily
    GooString familyName("familyName");
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    EXPECT_EQ(*font.getFamily(), familyName);
}

TEST_F(GfxFontTest_1138, GetAscent_1138) {
    // Test normal operation of getAscent
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    EXPECT_GT(font.getAscent(), 0);  // Assuming ascent value is positive
}

TEST_F(GfxFontTest_1138, InvalidGetFamily_1138) {
    // Test boundary case: invalid family
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    EXPECT_EQ(font.getFamily(), nullptr);  // If family is not set, expect null
}

TEST_F(GfxFontTest_1138, Matches_1138) {
    // Test matches function for normal operation
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    EXPECT_TRUE(font.matches("tag"));
    EXPECT_FALSE(font.matches("nonMatchingTag"));
}

TEST_F(GfxFontTest_1138, GetNextChar_1138) {
    // Test getNextChar for boundary condition
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    const char *s = "sample";
    int len = 6;
    CharCode code;
    const Unicode *u;
    int uLen;
    double dx, dy, ox, oy;
    
    int result = font.getNextChar(s, len, &code, &u, &uLen, &dx, &dy, &ox, &oy);
    EXPECT_GE(result, 0);  // Test that getNextChar returns a valid value
}

TEST_F(GfxFontTest_1138, IsCIDFont_1138) {
    // Test isCIDFont for normal behavior
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    EXPECT_FALSE(font.isCIDFont());  // Assuming it's not CID font, adjust as per logic
}

TEST_F(GfxFontTest_1138, InvalidFontType_1138) {
    // Test for invalid or error cases (if relevant)
    XRef xref;
    Dict fontDict;
    GfxFont font("tag", Ref(1), nullptr, GfxFontType::TrueType, Ref(2));
    auto result = GfxFont::getFontType(&xref, &fontDict, nullptr);
    EXPECT_EQ(result, GfxFontType::Unknown);  // Adjust based on actual error handling
}