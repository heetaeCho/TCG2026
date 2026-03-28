#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

using ::testing::AtLeast;
using ::testing::Mock;
using ::testing::Return;

class TextWordTest_1187 : public ::testing::Test {
protected:
    // Mock objects and setup if needed for external dependencies can go here
    const GfxState* state = nullptr; // Assuming we have a state mock or object if needed
    TextWord* textWord;
    
    void SetUp() override {
        textWord = new TextWord(state, 0, 12.0); // Assume default fontSize 12.0
    }

    void TearDown() override {
        delete textWord;
    }
};

// Test for getting the font size, normal case
TEST_F(TextWordTest_1187, GetFontSize_1187) {
    EXPECT_DOUBLE_EQ(textWord->getFontSize(), 12.0);
}

// Test for boundary condition - check very small and very large font size
TEST_F(TextWordTest_1187, GetFontSizeBoundary_1187) {
    textWord = new TextWord(state, 0, 0.1); // Very small font size
    EXPECT_DOUBLE_EQ(textWord->getFontSize(), 0.1);

    textWord = new TextWord(state, 0, 1000.0); // Very large font size
    EXPECT_DOUBLE_EQ(textWord->getFontSize(), 1000.0);
}

// Test for exceptional case - checking with uninitialized state (if applicable)
TEST_F(TextWordTest_1187, GetFontSizeWithNullState_1187) {
    textWord = new TextWord(nullptr, 0, 12.0);
    EXPECT_DOUBLE_EQ(textWord->getFontSize(), 12.0); // The fontSize should still return a valid result, even if state is null.
}

// Test for rotation retrieval
TEST_F(TextWordTest_1187, GetRotation_1187) {
    EXPECT_EQ(textWord->getRotation(), 0); // Assuming rotation is 0 by default
}

// Test for boundary conditions related to character position and length
TEST_F(TextWordTest_1187, GetCharPosAndLenBoundary_1187) {
    // Let's simulate boundary cases for character position and length
    EXPECT_EQ(textWord->getCharPos(), 0);  // default value
    EXPECT_EQ(textWord->getCharLen(), 0);  // default value

    // Here we could extend the behavior with mock objects or adjusted values depending on the state setup
}

// Test for spaceAfter and underlined property
TEST_F(TextWordTest_1187, TestSpaceAfterAndUnderlined_1187) {
    // Checking default state for spaceAfter and underlined
    EXPECT_FALSE(textWord->getSpaceAfter());
    EXPECT_FALSE(textWord->isUnderlined());
}

// Test for checking the link - assuming it could be null
TEST_F(TextWordTest_1187, GetLink_1187) {
    EXPECT_EQ(textWord->getLink(), nullptr); // Default link is null
}

// Test for verifying external interactions (if we mock any handler)
TEST_F(TextWordTest_1187, VerifyExternalInteraction_1187) {
    // If we had any external dependencies like TextSelectionVisitor, we could set expectations for them.
    // Example:
    // EXPECT_CALL(mockVisitor, VisitSelection(testing::_)).Times(AtLeast(1));
}