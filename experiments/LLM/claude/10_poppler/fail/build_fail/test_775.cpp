#include <gtest/gtest.h>
#include "Annot.h"

class AnnotAppearanceBuilderTest_775 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly constructed AnnotAppearanceBuilder has addedDingbatsResource set to false
TEST_F(AnnotAppearanceBuilderTest_775, DefaultConstructor_AddedDingbatsResourceIsFalse_775)
{
    AnnotAppearanceBuilder builder;
    EXPECT_FALSE(builder.getAddedDingbatsResource());
}

// Test that buffer() returns a non-null pointer after construction
TEST_F(AnnotAppearanceBuilderTest_775, DefaultConstructor_BufferIsNotNull_775)
{
    AnnotAppearanceBuilder builder;
    const GooString *buf = builder.buffer();
    EXPECT_NE(buf, nullptr);
}

// Test that buffer() returns an empty buffer after construction
TEST_F(AnnotAppearanceBuilderTest_775, DefaultConstructor_BufferIsEmpty_775)
{
    AnnotAppearanceBuilder builder;
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_EQ(buf->getLength(), 0);
}

// Test that append adds text to the buffer
TEST_F(AnnotAppearanceBuilderTest_775, Append_AddsTextToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    builder.append("hello");
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
    std::string content(buf->c_str(), buf->getLength());
    EXPECT_EQ(content, "hello");
}

// Test that multiple appends concatenate text
TEST_F(AnnotAppearanceBuilderTest_775, Append_MultipleCalls_ConcatenatesText_775)
{
    AnnotAppearanceBuilder builder;
    builder.append("hello");
    builder.append(" world");
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    std::string content(buf->c_str(), buf->getLength());
    EXPECT_EQ(content, "hello world");
}

// Test that appending an empty string doesn't change buffer
TEST_F(AnnotAppearanceBuilderTest_775, Append_EmptyString_BufferUnchanged_775)
{
    AnnotAppearanceBuilder builder;
    builder.append("");
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_EQ(buf->getLength(), 0);
}

// Test writeString writes to buffer
TEST_F(AnnotAppearanceBuilderTest_775, WriteString_AddsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    builder.writeString("test string");
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test writeString with empty string
TEST_F(AnnotAppearanceBuilderTest_775, WriteString_EmptyString_775)
{
    AnnotAppearanceBuilder builder;
    builder.writeString("");
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    // An empty writeString may produce parentheses or nothing depending on implementation
    // We just verify it doesn't crash
}

// Test appendf with formatted text
TEST_F(AnnotAppearanceBuilderTest_775, Appendf_FormattedText_775)
{
    AnnotAppearanceBuilder builder;
    builder.appendf("%d %d m", 10, 20);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test that lineEndingXShorten returns a value for various ending styles
TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_NoneStyle_ReturnsZero_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingNone, 10.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_SquareStyle_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingSquare, 10.0);
    // Just verify it returns some reasonable value
    EXPECT_GE(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_CircleStyle_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingCircle, 10.0);
    EXPECT_GE(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_DiamondStyle_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingDiamond, 10.0);
    EXPECT_GE(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_OpenArrowStyle_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingOpenArrow, 10.0);
    EXPECT_GE(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_ClosedArrowStyle_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingClosedArrow, 10.0);
    EXPECT_GE(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_ButtStyle_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingButt, 10.0);
    EXPECT_GE(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_SlashStyle_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingSlash, 10.0);
    EXPECT_GE(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXShorten_ZeroSize_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXShorten(annotLineEndingSquare, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test lineEndingXExtendBBox static method
TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXExtendBBox_NoneStyle_ReturnsZero_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXExtendBBox(annotLineEndingNone, 10.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXExtendBBox_SquareStyle_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXExtendBBox(annotLineEndingSquare, 10.0);
    EXPECT_GE(result, 0.0);
}

TEST_F(AnnotAppearanceBuilderTest_775, LineEndingXExtendBBox_ZeroSize_775)
{
    double result = AnnotAppearanceBuilder::lineEndingXExtendBBox(annotLineEndingSquare, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test drawCircle appends content to buffer
TEST_F(AnnotAppearanceBuilderTest_775, DrawCircle_AppendsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawCircle(50.0, 50.0, 25.0, false);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test drawCircle with fill
TEST_F(AnnotAppearanceBuilderTest_775, DrawCircle_Fill_AppendsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawCircle(50.0, 50.0, 25.0, true);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test drawCircle with zero radius
TEST_F(AnnotAppearanceBuilderTest_775, DrawCircle_ZeroRadius_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawCircle(50.0, 50.0, 0.0, false);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    // Should not crash, buffer may or may not have content
}

// Test drawEllipse appends content to buffer
TEST_F(AnnotAppearanceBuilderTest_775, DrawEllipse_AppendsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawEllipse(50.0, 50.0, 30.0, 20.0, false, true);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test drawEllipse with fill and stroke
TEST_F(AnnotAppearanceBuilderTest_775, DrawEllipse_FillAndStroke_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawEllipse(50.0, 50.0, 30.0, 20.0, true, true);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test drawCircleTopLeft appends content
TEST_F(AnnotAppearanceBuilderTest_775, DrawCircleTopLeft_AppendsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawCircleTopLeft(50.0, 50.0, 25.0);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test drawCircleBottomRight appends content
TEST_F(AnnotAppearanceBuilderTest_775, DrawCircleBottomRight_AppendsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawCircleBottomRight(50.0, 50.0, 25.0);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test that copy constructor is deleted (compile-time check - this test just verifies the class is not copyable)
TEST_F(AnnotAppearanceBuilderTest_775, IsNotCopyConstructible_775)
{
    EXPECT_FALSE(std::is_copy_constructible<AnnotAppearanceBuilder>::value);
}

// Test that copy assignment is deleted
TEST_F(AnnotAppearanceBuilderTest_775, IsNotCopyAssignable_775)
{
    EXPECT_FALSE(std::is_copy_assignable<AnnotAppearanceBuilder>::value);
}

// Test setDrawColor with a simple color (fill = false means stroke color)
TEST_F(AnnotAppearanceBuilderTest_775, SetDrawColor_Stroke_AppendsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    // Create a simple AnnotColor - assuming single-value grayscale
    AnnotColor color(1.0); // grayscale white
    builder.setDrawColor(color, false);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test setDrawColor with fill
TEST_F(AnnotAppearanceBuilderTest_775, SetDrawColor_Fill_AppendsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    AnnotColor color(0.0); // grayscale black
    builder.setDrawColor(color, true);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test setTextFont appends to buffer
TEST_F(AnnotAppearanceBuilderTest_775, SetTextFont_AppendsToBuffer_775)
{
    AnnotAppearanceBuilder builder;
    builder.setTextFont("Helvetica", 12.0);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test setTextFont with empty font name
TEST_F(AnnotAppearanceBuilderTest_775, SetTextFont_EmptyFontName_775)
{
    AnnotAppearanceBuilder builder;
    builder.setTextFont("", 12.0);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    // Should not crash
}

// Test setTextFont with zero font size
TEST_F(AnnotAppearanceBuilderTest_775, SetTextFont_ZeroFontSize_775)
{
    AnnotAppearanceBuilder builder;
    builder.setTextFont("Helvetica", 0.0);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}

// Test negative radius for drawCircle (boundary condition)
TEST_F(AnnotAppearanceBuilderTest_775, DrawCircle_NegativeRadius_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawCircle(50.0, 50.0, -10.0, false);
    // Should not crash
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
}

// Test large values for drawEllipse
TEST_F(AnnotAppearanceBuilderTest_775, DrawEllipse_LargeValues_775)
{
    AnnotAppearanceBuilder builder;
    builder.drawEllipse(1e6, 1e6, 1e5, 1e5, true, true);
    const GooString *buf = builder.buffer();
    ASSERT_NE(buf, nullptr);
    EXPECT_GT(buf->getLength(), 0);
}
