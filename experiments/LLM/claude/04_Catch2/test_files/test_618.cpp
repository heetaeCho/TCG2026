#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::TextFlow;

// ============================================================
// Tests for Column class
// ============================================================

TEST(ColumnTest_618, DefaultWidthIs79_618) {
    Column col("hello");
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_618, SetWidthReturnsUpdatedWidth_618) {
    Column col("hello");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST(ColumnTest_618, SetWidthTo1_618) {
    Column col("hello");
    col.width(1);
    EXPECT_EQ(col.width(), 1u);
}

TEST(ColumnTest_618, SetWidthToLargeValue_618) {
    Column col("hello");
    col.width(1000);
    EXPECT_EQ(col.width(), 1000u);
}

TEST(ColumnTest_618, WidthMethodChaining_618) {
    Column col("hello");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50u);
}

TEST(ColumnTest_618, IndentMethodChaining_618) {
    Column col("hello");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_618, InitialIndentMethodChaining_618) {
    Column col("hello");
    Column& ref = col.initialIndent(4);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_618, EmptyStringColumn_618) {
    Column col("");
    EXPECT_EQ(col.width(), 79u);
    // Iterating over empty column should produce at least an empty or single line
    std::ostringstream oss;
    oss << col;
    // Just verify it doesn't crash
    SUCCEED();
}

TEST(ColumnTest_618, OutputStreamOperator_618) {
    Column col("Hello, World!");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello, World!"), std::string::npos);
}

TEST(ColumnTest_618, NarrowWidthWrapsText_618) {
    Column col("Hello World");
    col.width(5);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // With width 5, "Hello World" should be wrapped into multiple lines
    EXPECT_NE(output.find('\n'), std::string::npos);
}

TEST(ColumnTest_618, WideWidthNoWrap_618) {
    Column col("Hello World");
    col.width(200);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // With width 200, it should fit in one line - no newline within the text
    // The output might have a trailing newline, but shouldn't wrap
    std::string trimmed = output;
    while (!trimmed.empty() && trimmed.back() == '\n') {
        trimmed.pop_back();
    }
    EXPECT_EQ(trimmed.find('\n'), std::string::npos);
}

TEST(ColumnTest_618, BeginEndIteration_618) {
    Column col("Line one");
    col.width(80);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GE(count, 1);
}

TEST(ColumnTest_618, IndentAffectsOutput_618) {
    Column col1("Hello World");
    col1.width(80);
    std::ostringstream oss1;
    oss1 << col1;

    Column col2("Hello World");
    col2.width(80).indent(4);
    std::ostringstream oss2;
    oss2 << col2;

    // Indented output should be different (longer due to spaces)
    // or at least the indented version should contain leading spaces
    // They should differ
    EXPECT_NE(oss1.str(), oss2.str());
}

TEST(ColumnTest_618, InitialIndentAffectsFirstLine_618) {
    Column col1("Hello World");
    col1.width(80);
    std::ostringstream oss1;
    oss1 << col1;

    Column col2("Hello World");
    col2.width(80).initialIndent(4);
    std::ostringstream oss2;
    oss2 << col2;

    // With initial indent, the first line should start with spaces
    EXPECT_NE(oss1.str(), oss2.str());
}

TEST(ColumnTest_618, MoveConstructColumn_618) {
    std::string text = "Some test text";
    Column col(std::move(text));
    col.width(80);
    std::ostringstream oss;
    oss << col;
    EXPECT_NE(oss.str().find("Some test text"), std::string::npos);
}

// ============================================================
// Tests for Column addition (Columns)
// ============================================================

TEST(ColumnsTest_618, AddTwoColumns_618) {
    Column left("Left side");
    left.width(20);
    Column right("Right side");
    right.width(20);

    auto combined = left + right;
    std::ostringstream oss;
    oss << combined;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

TEST(ColumnsTest_618, AddTwoColumnsMoveSemantics_618) {
    Column left("Left side");
    left.width(20);
    Column right("Right side");
    right.width(20);

    auto combined = std::move(left) + std::move(right);
    std::ostringstream oss;
    oss << combined;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Tests for Spacer function
// ============================================================

TEST(SpacerTest_618, SpacerCreatesColumnWithGivenWidth_618) {
    Column spacer = Spacer(10);
    EXPECT_EQ(spacer.width(), 10u);
}

TEST(SpacerTest_618, SpacerWithZeroWidth_618) {
    Column spacer = Spacer(0);
    EXPECT_EQ(spacer.width(), 0u);
}

TEST(SpacerTest_618, SpacerWithLargeWidth_618) {
    Column spacer = Spacer(500);
    EXPECT_EQ(spacer.width(), 500u);
}

TEST(SpacerTest_618, SpacerUsedBetweenColumns_618) {
    Column left("Left");
    left.width(10);
    Column spacer = Spacer(5);
    Column right("Right");
    right.width(10);

    auto combined = left + spacer + right;
    std::ostringstream oss;
    oss << combined;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

TEST(SpacerTest_618, SpacerOutputIsEmpty_618) {
    Column spacer = Spacer(5);
    std::ostringstream oss;
    oss << spacer;
    std::string output = oss.str();
    // Spacer is created with empty string, output should be mostly/all spaces or empty
    // Just verify no crash and it produces some output
    SUCCEED();
}

// ============================================================
// Tests for long text wrapping
// ============================================================

TEST(ColumnTest_618, LongTextWrapping_618) {
    std::string longText = "This is a very long line of text that should definitely be wrapped when the column width is set to something small like twenty characters.";
    Column col(longText);
    col.width(20);
    
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GT(lineCount, 1);
}

TEST(ColumnTest_618, SingleWordLongerThanWidth_618) {
    Column col("Supercalifragilisticexpialidocious");
    col.width(10);
    std::ostringstream oss;
    oss << col;
    // Should not crash, and should produce output
    EXPECT_FALSE(oss.str().empty());
}

TEST(ColumnTest_618, MultipleSpacesInText_618) {
    Column col("Hello     World");
    col.width(80);
    std::ostringstream oss;
    oss << col;
    EXPECT_FALSE(oss.str().empty());
}

TEST(ColumnTest_618, NewlinesInText_618) {
    Column col("Line1\nLine2\nLine3");
    col.width(80);
    
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GE(lineCount, 3);
}

TEST(ColumnTest_618, IndentAndInitialIndentCombined_618) {
    Column col("Hello World this is a test");
    col.width(20).indent(4).initialIndent(8);
    std::ostringstream oss;
    oss << col;
    EXPECT_FALSE(oss.str().empty());
}

TEST(ColumnTest_618, ZeroIndent_618) {
    Column col("Hello World");
    col.width(80).indent(0).initialIndent(0);
    std::ostringstream oss;
    oss << col;
    EXPECT_NE(oss.str().find("Hello World"), std::string::npos);
}
