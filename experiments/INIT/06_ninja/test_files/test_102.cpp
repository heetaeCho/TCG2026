// VisibleInputCharsIterator tests for TEST_ID 102

#include "gtest/gtest.h"
#include "elide_middle.cc"  // Contains VisibleInputCharsIterator

class VisibleInputCharsIteratorTest_102 : public ::testing::Test {};

// Boundary case: empty input should have no characters and zero positions.
TEST_F(VisibleInputCharsIteratorTest_102, EmptyInput_HasNoCharsAndZeroPositions_102) {
    std::string input;
    VisibleInputCharsIterator it(input);

    EXPECT_FALSE(it.HasChar());
    EXPECT_EQ(0u, it.InputIndex());
    EXPECT_EQ(0u, it.VisiblePosition());
    // Do not call IsVisible() or NextChar() when HasChar() is false.
}

// Normal operation: plain text without ANSI codes should be fully visible and
// input index and visible position should advance together.
TEST_F(VisibleInputCharsIteratorTest_102, PlainText_IndexesAndPositionsAdvanceTogether_102) {
    std::string input = "ABC";
    VisibleInputCharsIterator it(input);

    ASSERT_TRUE(it.HasChar());
    EXPECT_EQ(0u, it.InputIndex());
    EXPECT_EQ(0u, it.VisiblePosition());

    size_t expected_input_index = 0;
    size_t expected_visible_pos = 0;

    while (it.HasChar()) {
        EXPECT_EQ(expected_input_index, it.InputIndex());
        EXPECT_EQ(expected_visible_pos, it.VisiblePosition());
        EXPECT_TRUE(it.IsVisible()) << "All characters in plain text should be visible";

        ++expected_input_index;
        ++expected_visible_pos;
        it.NextChar();
    }

    EXPECT_EQ(input.size(), expected_input_index);
    EXPECT_EQ(input.size(), expected_visible_pos);
    EXPECT_EQ(input.size(), it.InputIndex());
    EXPECT_EQ(input.size(), it.VisiblePosition());
}

// Boundary/visibility case: input that contains only ANSI color sequences
// should have no visible characters and visible position should remain zero.
TEST_F(VisibleInputCharsIteratorTest_102, OnlyAnsiSequences_NoVisibleCharacters_102) {
    // Typical pattern: "\x1b[31m" (set red) + "\x1b[0m" (reset)
    std::string input = "\x1b[31m\x1b[0m";
    VisibleInputCharsIterator it(input);

    size_t expected_input_index = 0;
    size_t expected_visible_pos = 0;
    size_t visible_count = 0;

    while (it.HasChar()) {
        EXPECT_EQ(expected_input_index, it.InputIndex());
        EXPECT_EQ(expected_visible_pos, it.VisiblePosition());
        EXPECT_FALSE(it.IsVisible()) << "ANSI sequence bytes should not be visible";

        ++expected_input_index;
        it.NextChar();
    }

    EXPECT_EQ(input.size(), expected_input_index);
    EXPECT_EQ(input.size(), it.InputIndex());
    EXPECT_EQ(0u, expected_visible_pos);
    EXPECT_EQ(0u, it.VisiblePosition());
    EXPECT_EQ(0u, visible_count);
}

// Normal/complex case: text with ANSI color sequences should advance input index
// over all bytes, but visible position should advance only for visible characters.
TEST_F(VisibleInputCharsIteratorTest_102,
       AnsiColoredText_VisiblePositionCountsOnlyVisibleChars_102) {
    // "\x1b[31mABC\x1b[0mD"
    // Indices:
    //  0: ESC
    //  1: '['
    //  2: '3'
    //  3: '1'
    //  4: 'm'
    //  5: 'A' (visible 0)
    //  6: 'B' (visible 1)
    //  7: 'C' (visible 2)
    //  8: ESC
    //  9: '['
    // 10: '0'
    // 11: 'm'
    // 12: 'D' (visible 3)
    std::string input = "\x1b[31mABC\x1b[0mD";
    VisibleInputCharsIterator it(input);

    size_t expected_input_index = 0;
    size_t expected_visible_pos = 0;
    size_t visible_count = 0;

    while (it.HasChar()) {
        size_t idx = it.InputIndex();
        ASSERT_LT(idx, input.size());

        bool expected_visible = (idx == 5 || idx == 6 || idx == 7 || idx == 12);

        // VisiblePosition should be the current index in the visible stream,
        // which only advances when we are on a visible character.
        EXPECT_EQ(expected_visible_pos, it.VisiblePosition());
        EXPECT_EQ(expected_visible, it.IsVisible()) << "Visibility mismatch at input index " << idx;

        if (expected_visible) {
            ++expected_visible_pos;
            ++visible_count;
        }

        ++expected_input_index;
        it.NextChar();
    }

    EXPECT_EQ(input.size(), expected_input_index);
    EXPECT_EQ(input.size(), it.InputIndex());
    EXPECT_EQ(4u, expected_visible_pos);   // A, B, C, D
    EXPECT_EQ(4u, visible_count);
    EXPECT_EQ(4u, it.VisiblePosition());
}
