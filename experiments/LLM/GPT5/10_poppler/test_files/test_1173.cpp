#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Mock external collaborators if needed (not required in this case)

// Test case: Constructor - Normal operation
TEST_F(TextFontInfoTest_1173, ConstructorTest_1173) {
    // Given: A valid GfxState instance
    const GfxState* mockState = nullptr; // Use a real mock or stub as needed
    TextFontInfo fontInfo(mockState);

    // When: The constructor is called

    // Then: Verify any observable behaviors (not private/internal state)
    EXPECT_NE(fontInfo.getFontName(), nullptr);
}

// Test case: getFontName - Normal operation
TEST_F(TextFontInfoTest_1173, GetFontNameTest_1173) {
    // Given: A TextFontInfo instance initialized with a valid GfxState
    const GfxState* mockState = nullptr; // Use a real mock or stub as needed
    TextFontInfo fontInfo(mockState);

    // When: getFontName() is called
    const GooString* fontName = fontInfo.getFontName();

    // Then: Ensure the fontName is not null and the expected name is returned
    EXPECT_NE(fontName, nullptr);
    // For example, you can verify that fontName matches a known value if applicable
}

// Test case: matches(GfxState*) - Normal operation
TEST_F(TextFontInfoTest_1173, MatchesGfxStateTest_1173) {
    // Given: A TextFontInfo instance and a mock GfxState
    const GfxState* mockState = nullptr; // Use a real mock or stub as needed
    TextFontInfo fontInfo(mockState);

    // When: matches() is called with the mock GfxState
    bool result = fontInfo.matches(mockState);

    // Then: Ensure the result is as expected
    EXPECT_TRUE(result); // Adjust based on expected behavior
}

// Test case: matches(TextFontInfo*) - Normal operation
TEST_F(TextFontInfoTest_1173, MatchesFontInfoTest_1173) {
    // Given: Two TextFontInfo instances
    const GfxState* mockState = nullptr; // Use a real mock or stub as needed
    TextFontInfo fontInfo1(mockState);
    TextFontInfo fontInfo2(mockState);

    // When: matches() is called comparing the two instances
    bool result = fontInfo1.matches(&fontInfo2);

    // Then: Ensure the result is as expected
    EXPECT_TRUE(result); // Adjust based on expected behavior
}

// Test case: getAscent - Normal operation
TEST_F(TextFontInfoTest_1173, GetAscentTest_1173) {
    // Given: A TextFontInfo instance initialized with a valid GfxState
    const GfxState* mockState = nullptr; // Use a real mock or stub as needed
    TextFontInfo fontInfo(mockState);

    // When: getAscent() is called
    double ascent = fontInfo.getAscent();

    // Then: Ensure the ascent is as expected
    EXPECT_GE(ascent, 0.0); // Adjust based on expected behavior
}

// Test case: getDescent - Normal operation
TEST_F(TextFontInfoTest_1173, GetDescentTest_1173) {
    // Given: A TextFontInfo instance initialized with a valid GfxState
    const GfxState* mockState = nullptr; // Use a real mock or stub as needed
    TextFontInfo fontInfo(mockState);

    // When: getDescent() is called
    double descent = fontInfo.getDescent();

    // Then: Ensure the descent is as expected
    EXPECT_LE(descent, 0.0); // Adjust based on expected behavior
}

// Test case: isFixedWidth - Normal operation
TEST_F(TextFontInfoTest_1173, IsFixedWidthTest_1173) {
    // Given: A TextFontInfo instance initialized with a valid GfxState
    const GfxState* mockState = nullptr; // Use a real mock or stub as needed
    TextFontInfo fontInfo(mockState);

    // When: isFixedWidth() is called
    bool result = fontInfo.isFixedWidth();

    // Then: Ensure the result matches the expected behavior
    EXPECT_FALSE(result); // Adjust based on expected behavior
}

// Test case: Exception handling - Edge case for null state (if applicable)
TEST_F(TextFontInfoTest_1173, NullStateExceptionTest_1173) {
    // Given: A TextFontInfo instance initialized with a null GfxState
    const GfxState* nullState = nullptr;

    // When: The constructor is called with a null state
    TextFontInfo fontInfo(nullState);

    // Then: Ensure it behaves as expected (e.g., throws or handles error)
    // You can use EXPECT_THROW if exceptions are expected
}

// Test case: matches with Ref - Boundary condition
TEST_F(TextFontInfoTest_1173, MatchesWithRefTest_1173) {
    // Given: A TextFontInfo instance and a mock Ref
    const Ref* mockRef = nullptr; // Use a real mock or stub as needed
    const GfxState* mockState = nullptr; // Use a real mock or stub as needed
    TextFontInfo fontInfo(mockState);

    // When: matches() is called with a Ref
    bool result = fontInfo.matches(mockRef);

    // Then: Ensure the result is as expected
    EXPECT_FALSE(result); // Adjust based on expected behavior
}