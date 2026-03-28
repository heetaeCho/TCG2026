#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// Test fixture for TextWord class
class TextWordTest_1191 : public ::testing::Test {
protected:
    // Test setup code here, if necessary
    TextWord* word;

    void SetUp() override {
        // Create a mock GfxState and TextFontInfo object as needed
        const GfxState* mockState = nullptr;  // Mock or initialize GfxState
        int rotation = 0;
        double fontSize = 12.0;

        word = new TextWord(mockState, rotation, fontSize);
    }

    void TearDown() override {
        delete word;
    }
};

// Test case: Verify `getSpaceAfter()` returns the correct value
TEST_F(TextWordTest_1191, GetSpaceAfter_True) {
    // Assume spaceAfter is set to true (use constructor or setter method in actual code)
    // For now, we mock this behavior

    EXPECT_TRUE(word->getSpaceAfter());
}

// Test case: Verify `getSpaceAfter()` returns the correct value when false
TEST_F(TextWordTest_1191, GetSpaceAfter_False) {
    // Assume spaceAfter is set to false (use constructor or setter method in actual code)
    // For now, we mock this behavior

    EXPECT_FALSE(word->getSpaceAfter());
}

// Test case: Verify boundary condition where there are no characters in TextWord
TEST_F(TextWordTest_1191, GetLength_ZeroWhenNoChars) {
    EXPECT_EQ(word->getLength(), 0);
}

// Test case: Verify `getRotation()` returns the correct rotation value
TEST_F(TextWordTest_1191, GetRotation_ValidRotation) {
    int rotation = word->getRotation();
    EXPECT_EQ(rotation, 0);  // Based on the test setup, adjust if the rotation is different
}

// Test case: Verify the behavior of `getFontInfo()` with valid index
TEST_F(TextWordTest_1191, GetFontInfo_ValidIndex) {
    const TextFontInfo* fontInfo = word->getFontInfo(0);
    EXPECT_NE(fontInfo, nullptr);  // Ensure the pointer is not null (mock or provide valid data)
}

// Test case: Verify the behavior of `getFontInfo()` with an invalid index
TEST_F(TextWordTest_1191, GetFontInfo_InvalidIndex) {
    const TextFontInfo* fontInfo = word->getFontInfo(-1);  // Using an invalid index
    EXPECT_EQ(fontInfo, nullptr);  // Should return null for invalid index
}

// Test case: Verify `getLink()` correctly returns the link or null
TEST_F(TextWordTest_1191, GetLink_ValidLink) {
    const AnnotLink* link = word->getLink();
    EXPECT_EQ(link, nullptr);  // Assuming no link by default, adjust as per implementation
}

// Test case: Verify exceptional behavior when attempting to access invalid index
TEST_F(TextWordTest_1191, GetChar_ThrowsForInvalidIndex) {
    EXPECT_THROW(word->getChar(-1), std::out_of_range);  // Assuming an exception is thrown
}

// Test case: Verify `getColor()` works and returns valid RGB values
TEST_F(TextWordTest_1191, GetColor_ValidRGB) {
    double r, g, b;
    word->getColor(&r, &g, &b);
    EXPECT_GE(r, 0.0);
    EXPECT_LE(r, 1.0);
    EXPECT_GE(g, 0.0);
    EXPECT_LE(g, 1.0);
    EXPECT_GE(b, 0.0);
    EXPECT_LE(b, 1.0);
}

// Test case: Verify `getBBox()` works and returns the bounding box correctly
TEST_F(TextWordTest_1191, GetBBox_ValidBoundingBox) {
    double xMin, yMin, xMax, yMax;
    word->getBBox(&xMin, &yMin, &xMax, &yMax);
    EXPECT_GT(xMax, xMin);  // Ensure that max is greater than min
    EXPECT_GT(yMax, yMin);  // Ensure that max is greater than min
}