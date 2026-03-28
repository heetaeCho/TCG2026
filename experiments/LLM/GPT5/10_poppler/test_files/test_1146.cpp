#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <optional>
#include "GfxFont.h"

// Mock class for testing purposes
class MockXRef {};
class MockPSOutputDev {};
class MockGooString {};
class MockDict {};

TEST_F(GfxFontTest_1146, TestIsCIDFont_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);

    // Testing the isCIDFont() method
    EXPECT_FALSE(font.isCIDFont());
}

TEST_F(GfxFontTest_1146, TestGetNameWithoutSubsetTag_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);

    // Testing getNameWithoutSubsetTag() method with a valid GfxFont
    EXPECT_EQ(font.getNameWithoutSubsetTag(), "");
}

TEST_F(GfxFontTest_1146, TestIsSubset_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);

    // Testing isSubset() method
    EXPECT_FALSE(font.isSubset());
}

TEST_F(GfxFontTest_1146, TestGetTag_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);

    // Testing getTag() method
    EXPECT_EQ(font.getTag(), "testTag");
}

TEST_F(GfxFontTest_1146, TestGetFamily_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);

    // Testing getFamily() method (should return nullptr for this test setup)
    EXPECT_EQ(font.getFamily(), nullptr);
}

TEST_F(GfxFontTest_1146, TestGetAscent_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);

    // Testing getAscent() method
    EXPECT_EQ(font.getAscent(), 0.0);  // Assuming default value
}

TEST_F(GfxFontTest_1146, TestGetDescent_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);

    // Testing getDescent() method
    EXPECT_EQ(font.getDescent(), 0.0);  // Assuming default value
}

TEST_F(GfxFontTest_1146, TestIsBase14Font_1146) {
    std::string family = "Helvetica";
    std::string style = "Bold";

    // Testing isBase14Font with string parameters
    EXPECT_TRUE(GfxFont::isBase14Font(family, style));
}

TEST_F(GfxFontTest_1146, TestGetNextChar_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);
    const char *s = "test";
    int len = 4;
    CharCode code;
    const Unicode *u;
    int uLen;
    double dx, dy, ox, oy;

    // Test getNextChar() function
    EXPECT_EQ(font.getNextChar(s, len, &code, &u, &uLen, &dx, &dy, &ox, &oy), 0);
}

TEST_F(GfxFontTest_1146, TestGetExternalFont_1146) {
    std::string path = "path/to/font";
    bool cid = true;

    // Test getExternalFont static function
    auto result = GfxFont::getExternalFont(path, cid);
    EXPECT_TRUE(result.has_value());
}

TEST_F(GfxFontTest_1146, TestLocateFont_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);
    MockXRef *xref = nullptr;
    MockPSOutputDev *ps = nullptr;
    MockGooString *substituteFontName = nullptr;

    // Test locateFont method
    auto result = font.locateFont(xref, ps, substituteFontName);
    EXPECT_FALSE(result.has_value());
}

TEST_F(GfxFontTest_1146, TestReadEmbFontFile_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);
    MockXRef *xref = nullptr;

    // Test readEmbFontFile method
    auto result = font.readEmbFontFile(xref);
    EXPECT_FALSE(result.has_value());
}

TEST_F(GfxFontTest_1146, TestInvalidateEmbeddedFont_1146) {
    GfxFont font("testTag", 1, nullptr, GfxFontType::Type0, 2);

    // Test invalidateEmbeddedFont method
    EXPECT_TRUE(font.invalidateEmbeddedFont());
}