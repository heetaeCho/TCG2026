#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "./TestProjects/poppler/poppler/TextOutputDev.h"

class TextFontInfoTest_1177 : public ::testing::Test {
protected:
    // Setup necessary mocks or dependencies here if required
};

TEST_F(TextFontInfoTest_1177, isItalic_ReturnsTrue_WhenFlagsSetToItalic_1177) {
    // Arrange: Create a TextFontInfo object with a font that has the italic flag set
    TextFontInfo fontInfo(nullptr);  // Assuming that we have a proper GfxState mock or object

    // Act: Check if isItalic returns true
    bool result = fontInfo.isItalic();

    // Assert: Verify the expected result
    EXPECT_TRUE(result);
}

TEST_F(TextFontInfoTest_1177, isItalic_ReturnsFalse_WhenFlagsNotSetToItalic_1177) {
    // Arrange: Create a TextFontInfo object with a font that doesn't have the italic flag set
    TextFontInfo fontInfo(nullptr);  // Assuming the GfxState doesn't have the italic flag

    // Act: Check if isItalic returns false
    bool result = fontInfo.isItalic();

    // Assert: Verify the expected result
    EXPECT_FALSE(result);
}

TEST_F(TextFontInfoTest_1177, getFontName_ReturnsCorrectFontName_1177) {
    // Arrange: Create a TextFontInfo object
    TextFontInfo fontInfo(nullptr);  // Assuming we have a valid GfxState object for the constructor

    // Act: Retrieve the font name
    const GooString* fontName = fontInfo.getFontName();

    // Assert: Check if the font name matches the expected value (assuming an example name)
    EXPECT_EQ(fontName->getCString(), "ExampleFontName");  // Replace with actual expected value
}

TEST_F(TextFontInfoTest_1177, isFixedWidth_ReturnsTrue_WhenFontIsFixedWidth_1177) {
    // Arrange: Create a TextFontInfo object for a fixed-width font
    TextFontInfo fontInfo(nullptr);  // Assuming the constructor sets the appropriate flag

    // Act: Check if isFixedWidth returns true
    bool result = fontInfo.isFixedWidth();

    // Assert: Verify the expected result
    EXPECT_TRUE(result);
}

TEST_F(TextFontInfoTest_1177, isFixedWidth_ReturnsFalse_WhenFontIsNotFixedWidth_1177) {
    // Arrange: Create a TextFontInfo object for a non-fixed-width font
    TextFontInfo fontInfo(nullptr);  // Assuming the constructor sets the appropriate flag

    // Act: Check if isFixedWidth returns false
    bool result = fontInfo.isFixedWidth();

    // Assert: Verify the expected result
    EXPECT_FALSE(result);
}

TEST_F(TextFontInfoTest_1177, matches_ReturnsTrue_WhenFontInfoMatches_1177) {
    // Arrange: Create two TextFontInfo objects that should match
    TextFontInfo fontInfo1(nullptr);  // Assuming the same GfxState
    TextFontInfo fontInfo2(nullptr);  // Same GfxState as fontInfo1

    // Act: Check if they match
    bool result = fontInfo1.matches(&fontInfo2);

    // Assert: Verify that they match
    EXPECT_TRUE(result);
}

TEST_F(TextFontInfoTest_1177, matches_ReturnsFalse_WhenFontInfoDoesNotMatch_1177) {
    // Arrange: Create two TextFontInfo objects that should not match
    TextFontInfo fontInfo1(nullptr);  // Assuming a different GfxState
    TextFontInfo fontInfo2(nullptr);  // Different GfxState

    // Act: Check if they match
    bool result = fontInfo1.matches(&fontInfo2);

    // Assert: Verify that they do not match
    EXPECT_FALSE(result);
}

TEST_F(TextFontInfoTest_1177, getAscent_ReturnsCorrectValue_1177) {
    // Arrange: Create a TextFontInfo object
    TextFontInfo fontInfo(nullptr);

    // Act: Get the ascent value
    double ascent = fontInfo.getAscent();

    // Assert: Verify the ascent value (use a placeholder expected value)
    EXPECT_DOUBLE_EQ(ascent, 12.5);  // Replace with actual expected value
}

TEST_F(TextFontInfoTest_1177, getDescent_ReturnsCorrectValue_1177) {
    // Arrange: Create a TextFontInfo object
    TextFontInfo fontInfo(nullptr);

    // Act: Get the descent value
    double descent = fontInfo.getDescent();

    // Assert: Verify the descent value (use a placeholder expected value)
    EXPECT_DOUBLE_EQ(descent, -4.5);  // Replace with actual expected value
}

TEST_F(TextFontInfoTest_1177, getWMode_ReturnsCorrectWritingMode_1177) {
    // Arrange: Create a TextFontInfo object
    TextFontInfo fontInfo(nullptr);

    // Act: Get the writing mode
    auto wMode = fontInfo.getWMode();

    // Assert: Verify the writing mode (use a placeholder expected value)
    EXPECT_EQ(wMode, GfxFont::WritingMode::Horizontal);  // Replace with actual expected value
}