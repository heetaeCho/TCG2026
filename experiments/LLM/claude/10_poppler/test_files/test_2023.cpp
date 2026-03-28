#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to test the HorizontalTextLayouter class based on its public interface.
// Since we're treating it as a black box and the class is defined in Annot.cc,
// we include the necessary headers.

// Forward declarations and includes needed
#include "Annot.h"
#include "GooString.h"
#include "Form.h"
#include "GfxFont.h"

#include <optional>

class HorizontalTextLayouterTest_2023 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed HorizontalTextLayouter has zero total width
TEST_F(HorizontalTextLayouterTest_2023, DefaultConstructorTotalWidthIsZero_2023) {
    HorizontalTextLayouter layouter;
    EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
}

// Test that a default-constructed HorizontalTextLayouter has zero total char count
TEST_F(HorizontalTextLayouterTest_2023, DefaultConstructorTotalCharCountIsZero_2023) {
    HorizontalTextLayouter layouter;
    EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Test that a default-constructed HorizontalTextLayouter has consumedText of 0
TEST_F(HorizontalTextLayouterTest_2023, DefaultConstructorConsumedTextIsZero_2023) {
    HorizontalTextLayouter layouter;
    EXPECT_EQ(layouter.consumedText, 0);
}

// Test construction with empty text string
TEST_F(HorizontalTextLayouterTest_2023, EmptyTextTotalWidthIsZero_2023) {
    GooString text("");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
}

// Test construction with empty text string yields zero char count
TEST_F(HorizontalTextLayouterTest_2023, EmptyTextTotalCharCountIsZero_2023) {
    GooString text("");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Test construction with nullptr text
TEST_F(HorizontalTextLayouterTest_2023, NullTextTotalWidthIsZero_2023) {
    HorizontalTextLayouter layouter(nullptr, nullptr, nullptr, std::nullopt, false);
    EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
}

// Test construction with nullptr text yields zero char count
TEST_F(HorizontalTextLayouterTest_2023, NullTextTotalCharCountIsZero_2023) {
    HorizontalTextLayouter layouter(nullptr, nullptr, nullptr, std::nullopt, false);
    EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Test that totalWidth returns non-negative value for non-empty text without font
TEST_F(HorizontalTextLayouterTest_2023, NonEmptyTextWithoutFontTotalWidthNonNegative_2023) {
    GooString text("Hello World");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test that totalCharCount returns non-negative value for non-empty text
TEST_F(HorizontalTextLayouterTest_2023, NonEmptyTextTotalCharCountNonNegative_2023) {
    GooString text("Hello World");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_GE(layouter.totalCharCount(), 0);
}

// Test with available width constraint - totalWidth should not exceed available width (if constrained)
TEST_F(HorizontalTextLayouterTest_2023, AvailableWidthConstraint_2023) {
    GooString text("Hello");
    double availWidth = 100.0;
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::make_optional(availWidth), false);
    // totalWidth should be some non-negative value
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test with zero available width
TEST_F(HorizontalTextLayouterTest_2023, ZeroAvailableWidth_2023) {
    GooString text("Hello");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::make_optional(0.0), false);
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test noReencode parameter true
TEST_F(HorizontalTextLayouterTest_2023, NoReencodeTrue_2023) {
    GooString text("Test");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, true);
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test noReencode parameter false
TEST_F(HorizontalTextLayouterTest_2023, NoReencodeFalse_2023) {
    GooString text("Test");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test that consumedText is set after construction with text
TEST_F(HorizontalTextLayouterTest_2023, ConsumedTextAfterConstruction_2023) {
    GooString text("Hello");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_GE(layouter.consumedText, 0);
}

// Test with very large available width
TEST_F(HorizontalTextLayouterTest_2023, LargeAvailableWidth_2023) {
    GooString text("Hello World");
    double largeWidth = 1e10;
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::make_optional(largeWidth), false);
    EXPECT_GE(layouter.totalWidth(), 0.0);
    EXPECT_LE(layouter.totalWidth(), largeWidth);
}

// Test with negative available width
TEST_F(HorizontalTextLayouterTest_2023, NegativeAvailableWidth_2023) {
    GooString text("Hello");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::make_optional(-1.0), false);
    // Should still handle gracefully
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test with single character text
TEST_F(HorizontalTextLayouterTest_2023, SingleCharacterText_2023) {
    GooString text("A");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_GE(layouter.totalWidth(), 0.0);
    EXPECT_GE(layouter.totalCharCount(), 0);
}
