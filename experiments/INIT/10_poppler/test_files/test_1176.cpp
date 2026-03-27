#include <gtest/gtest.h>
#include <memory>
#include "TextOutputDev.h"

// Mock the external dependencies
class MockGfxState : public GfxState {
    // Add necessary mock methods if needed
};

// Test case for the `isSymbolic()` function
TEST_F(TextFontInfoTest_1176, IsSymbolic_True_1176) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is symbolic
    EXPECT_TRUE(fontInfo.isSymbolic());
}

TEST_F(TextFontInfoTest_1177, IsSymbolic_False_1177) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is NOT symbolic
    EXPECT_FALSE(fontInfo.isSymbolic());
}

// Test case for the `getFontName()` function
TEST_F(TextFontInfoTest_1178, GetFontName_Valid_1178) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font name is correctly fetched
    EXPECT_NE(fontInfo.getFontName(), nullptr);
}

// Test case for the `isFixedWidth()` function
TEST_F(TextFontInfoTest_1179, IsFixedWidth_True_1179) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is fixed-width
    EXPECT_TRUE(fontInfo.isFixedWidth());
}

TEST_F(TextFontInfoTest_1180, IsFixedWidth_False_1180) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is NOT fixed-width
    EXPECT_FALSE(fontInfo.isFixedWidth());
}

// Test case for the `isSerif()` function
TEST_F(TextFontInfoTest_1181, IsSerif_True_1181) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is serif
    EXPECT_TRUE(fontInfo.isSerif());
}

TEST_F(TextFontInfoTest_1182, IsSerif_False_1182) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is NOT serif
    EXPECT_FALSE(fontInfo.isSerif());
}

// Test case for the `isItalic()` function
TEST_F(TextFontInfoTest_1183, IsItalic_True_1183) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is italic
    EXPECT_TRUE(fontInfo.isItalic());
}

TEST_F(TextFontInfoTest_1184, IsItalic_False_1184) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is NOT italic
    EXPECT_FALSE(fontInfo.isItalic());
}

// Test case for the `isBold()` function
TEST_F(TextFontInfoTest_1185, IsBold_True_1185) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is bold
    EXPECT_TRUE(fontInfo.isBold());
}

TEST_F(TextFontInfoTest_1186, IsBold_False_1186) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font is NOT bold
    EXPECT_FALSE(fontInfo.isBold());
}

// Test case for the `matches()` function with a GfxState object
TEST_F(TextFontInfoTest_1187, Matches_WithGfxState_1187) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font matches with the given GfxState
    EXPECT_TRUE(fontInfo.matches(&mockState));
}

// Test case for the `matches()` function with another TextFontInfo object
TEST_F(TextFontInfoTest_1188, Matches_WithTextFontInfo_1188) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;

    // When: Construct two TextFontInfo objects
    TextFontInfo fontInfo1(&mockState);
    TextFontInfo fontInfo2(&mockState);

    // Then: Check if the fonts match
    EXPECT_TRUE(fontInfo1.matches(&fontInfo2));
}

// Test case for the `matches()` function with a Ref object
TEST_F(TextFontInfoTest_1189, Matches_WithRef_1189) {
    // Given: Create a mock GfxState object
    MockGfxState mockState;
    Ref mockRef;

    // When: Construct a TextFontInfo object
    TextFontInfo fontInfo(&mockState);

    // Then: Check if the font matches with the given Ref
    EXPECT_TRUE(fontInfo.matches(&mockRef));
}