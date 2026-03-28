#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to test HorizontalTextLayouter which is defined in Annot.cc
// Since we're treating it as a black box, we include the necessary headers.
#include "Annot.h"

// If direct inclusion doesn't work, we may need these:
#include "GooString.h"
#include "Form.h"
#include "GfxFont.h"

#include <optional>

class HorizontalTextLayouterTest_2024 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that default-constructed layouter has zero total char count
TEST_F(HorizontalTextLayouterTest_2024, DefaultConstructorTotalCharCountIsZero_2024)
{
    HorizontalTextLayouter layouter;
    EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Test that default-constructed layouter has zero total width
TEST_F(HorizontalTextLayouterTest_2024, DefaultConstructorTotalWidthIsZero_2024)
{
    HorizontalTextLayouter layouter;
    EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
}

// Test construction with a non-null text string (empty string)
TEST_F(HorizontalTextLayouterTest_2024, EmptyTextTotalCharCountIsZero_2024)
{
    GooString text("");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Test construction with a non-null text string (empty string) - width
TEST_F(HorizontalTextLayouterTest_2024, EmptyTextTotalWidthIsZero_2024)
{
    GooString text("");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
}

// Test construction with a simple text string without font (nullptr font)
TEST_F(HorizontalTextLayouterTest_2024, SimpleTextNullFontCharCount_2024)
{
    GooString text("Hello");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    // Without a font, behavior may vary, but totalCharCount should be non-negative
    EXPECT_GE(layouter.totalCharCount(), 0);
}

// Test construction with nullptr text
TEST_F(HorizontalTextLayouterTest_2024, NullTextTotalCharCountIsZero_2024)
{
    HorizontalTextLayouter layouter(nullptr, nullptr, nullptr, std::nullopt, false);
    EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Test construction with nullptr text - total width
TEST_F(HorizontalTextLayouterTest_2024, NullTextTotalWidthIsZero_2024)
{
    HorizontalTextLayouter layouter(nullptr, nullptr, nullptr, std::nullopt, false);
    EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
}

// Test that totalWidth returns non-negative for valid text
TEST_F(HorizontalTextLayouterTest_2024, TotalWidthNonNegative_2024)
{
    GooString text("Test text");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test with available width constraint
TEST_F(HorizontalTextLayouterTest_2024, WithAvailableWidthConstraint_2024)
{
    GooString text("Hello World");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::optional<double>(100.0), false);
    EXPECT_GE(layouter.totalCharCount(), 0);
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test with noReencode = true
TEST_F(HorizontalTextLayouterTest_2024, NoReencodeTrue_2024)
{
    GooString text("Test");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, true);
    EXPECT_GE(layouter.totalCharCount(), 0);
}

// Test with zero available width
TEST_F(HorizontalTextLayouterTest_2024, ZeroAvailableWidth_2024)
{
    GooString text("Hello");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::optional<double>(0.0), false);
    EXPECT_GE(layouter.totalCharCount(), 0);
    EXPECT_GE(layouter.totalWidth(), 0.0);
}

// Test with negative available width
TEST_F(HorizontalTextLayouterTest_2024, NegativeAvailableWidth_2024)
{
    GooString text("Hello");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::optional<double>(-1.0), false);
    EXPECT_GE(layouter.totalCharCount(), 0);
}

// Test that copy constructor is deleted (compile-time check conceptually)
// This is a compile-time property, so we just verify the object is usable after move scenarios
TEST_F(HorizontalTextLayouterTest_2024, ConsistentCharCountCalls_2024)
{
    HorizontalTextLayouter layouter;
    // Multiple calls should return the same result
    int count1 = layouter.totalCharCount();
    int count2 = layouter.totalCharCount();
    EXPECT_EQ(count1, count2);
}

// Test that multiple calls to totalWidth are consistent
TEST_F(HorizontalTextLayouterTest_2024, ConsistentTotalWidthCalls_2024)
{
    HorizontalTextLayouter layouter;
    double w1 = layouter.totalWidth();
    double w2 = layouter.totalWidth();
    EXPECT_DOUBLE_EQ(w1, w2);
}

// Test with single character text
TEST_F(HorizontalTextLayouterTest_2024, SingleCharText_2024)
{
    GooString text("A");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::nullopt, false);
    EXPECT_GE(layouter.totalCharCount(), 0);
}

// Test with very large available width
TEST_F(HorizontalTextLayouterTest_2024, VeryLargeAvailableWidth_2024)
{
    GooString text("Hello World");
    HorizontalTextLayouter layouter(&text, nullptr, nullptr, std::optional<double>(1e10), false);
    EXPECT_GE(layouter.totalCharCount(), 0);
    EXPECT_GE(layouter.totalWidth(), 0.0);
}
