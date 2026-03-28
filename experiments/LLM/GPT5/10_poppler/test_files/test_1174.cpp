#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"  // Include the header with the class definition

// Mock external dependencies if needed
class MockGfxState : public GfxState {
public:
    MOCK_METHOD(void, someMethod, (), (override));  // Example mock method if required
};

// Unit tests for TextFontInfo class
TEST_F(TextFontInfo_1174, IsFixedWidthReturnsTrueWhenFixedWidth_1174) {
    TextFontInfo fontInfo(mockState);  // Assuming 'mockState' is a valid GfxState object or mock
    EXPECT_TRUE(fontInfo.isFixedWidth());
}

TEST_F(TextFontInfo_1174, IsFixedWidthReturnsFalseWhenNotFixedWidth_1174) {
    TextFontInfo fontInfo(mockState);  // Assuming 'mockState' is a valid GfxState object or mock
    // Simulate behavior where isFixedWidth() should return false
    EXPECT_FALSE(fontInfo.isFixedWidth());
}

TEST_F(TextFontInfo_1174, MatchesReturnsTrueForSameGfxState_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_TRUE(fontInfo.matches(mockState));
}

TEST_F(TextFontInfo_1174, MatchesReturnsFalseForDifferentGfxState_1174) {
    TextFontInfo fontInfo(mockState);
    GfxState differentState;
    EXPECT_FALSE(fontInfo.matches(&differentState));
}

TEST_F(TextFontInfo_1174, MatchesReturnsTrueForSameFontInfo_1174) {
    TextFontInfo fontInfo(mockState);
    TextFontInfo sameFontInfo(mockState);
    EXPECT_TRUE(fontInfo.matches(&sameFontInfo));
}

TEST_F(TextFontInfo_1174, MatchesReturnsFalseForDifferentFontInfo_1174) {
    TextFontInfo fontInfo(mockState);
    TextFontInfo differentFontInfo(mockState);  // Assuming different state would lead to a mismatch
    EXPECT_FALSE(fontInfo.matches(&differentFontInfo));
}

TEST_F(TextFontInfo_1174, GetAscentReturnsCorrectValue_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_DOUBLE_EQ(fontInfo.getAscent(), 12.5);  // Adjust to an expected value
}

TEST_F(TextFontInfo_1174, GetDescentReturnsCorrectValue_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_DOUBLE_EQ(fontInfo.getDescent(), -3.5);  // Adjust to an expected value
}

TEST_F(TextFontInfo_1174, GetWModeReturnsCorrectMode_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_EQ(fontInfo.getWMode(), GfxFont::WritingMode::Horizontal);  // Adjust to an expected enum value
}

TEST_F(TextFontInfo_1174, GetFontNameReturnsCorrectFontName_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_STREQ(fontInfo.getFontName()->c_str(), "Arial");  // Assuming "Arial" is the expected font name
}

TEST_F(TextFontInfo_1174, IsSerifReturnsTrueForSerifFont_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_TRUE(fontInfo.isSerif());
}

TEST_F(TextFontInfo_1174, IsSerifReturnsFalseForNonSerifFont_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_FALSE(fontInfo.isSerif());
}

TEST_F(TextFontInfo_1174, IsSymbolicReturnsTrueForSymbolicFont_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_TRUE(fontInfo.isSymbolic());
}

TEST_F(TextFontInfo_1174, IsSymbolicReturnsFalseForNonSymbolicFont_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_FALSE(fontInfo.isSymbolic());
}

TEST_F(TextFontInfo_1174, IsItalicReturnsTrueForItalicFont_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_TRUE(fontInfo.isItalic());
}

TEST_F(TextFontInfo_1174, IsItalicReturnsFalseForNonItalicFont_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_FALSE(fontInfo.isItalic());
}

TEST_F(TextFontInfo_1174, IsBoldReturnsTrueForBoldFont_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_TRUE(fontInfo.isBold());
}

TEST_F(TextFontInfo_1174, IsBoldReturnsFalseForNonBoldFont_1174) {
    TextFontInfo fontInfo(mockState);
    EXPECT_FALSE(fontInfo.isBold());
}