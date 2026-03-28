#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using Catch::TextFlow::Column;

class ColumnTest_47 : public ::testing::Test {
protected:
    // Helper to collect all lines from a Column iterator
    std::vector<std::string> collectLines(const Column& col) {
        std::vector<std::string> lines;
        for (auto it = col.begin(); it != col.end(); ++it) {
            lines.push_back(*it);
        }
        return lines;
    }
};

// Test that default width is 79 (CATCH_CONFIG_CONSOLE_WIDTH 80 - 1)
TEST_F(ColumnTest_47, DefaultWidth_47) {
    Column col("test");
    EXPECT_EQ(col.width(), 79u);
}

// Test setting width via the width setter
TEST_F(ColumnTest_47, SetWidth_47) {
    Column col("test");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

// Test width method returns the value that was set
TEST_F(ColumnTest_47, WidthReturnsSetValue_47) {
    Column col("hello world");
    col.width(10);
    EXPECT_EQ(col.width(), 10u);
    col.width(50);
    EXPECT_EQ(col.width(), 50u);
}

// Test that width(1) is valid (minimum boundary)
TEST_F(ColumnTest_47, WidthMinimumBoundary_47) {
    Column col("a");
    col.width(1);
    EXPECT_EQ(col.width(), 1u);
}

// Test method chaining for width
TEST_F(ColumnTest_47, WidthMethodChaining_47) {
    Column col("test");
    Column& ref = col.width(20);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 20u);
}

// Test method chaining for indent
TEST_F(ColumnTest_47, IndentMethodChaining_47) {
    Column col("test");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

// Test method chaining for initialIndent
TEST_F(ColumnTest_47, InitialIndentMethodChaining_47) {
    Column col("test");
    Column& ref = col.initialIndent(4);
    EXPECT_EQ(&ref, &col);
}

// Test chaining multiple setters together
TEST_F(ColumnTest_47, ChainingMultipleSetters_47) {
    Column col("test text");
    col.width(40).indent(2).initialIndent(4);
    EXPECT_EQ(col.width(), 40u);
}

// Test construction with a const string reference
TEST_F(ColumnTest_47, ConstructFromConstString_47) {
    const std::string text = "Hello, World!";
    Column col(text);
    EXPECT_EQ(col.width(), 79u);
}

// Test construction with an rvalue string
TEST_F(ColumnTest_47, ConstructFromRvalueString_47) {
    Column col(std::string("Hello, World!"));
    EXPECT_EQ(col.width(), 79u);
}

// Test empty string column
TEST_F(ColumnTest_47, EmptyString_47) {
    Column col("");
    auto lines = collectLines(col);
    // An empty column should produce at least an empty iteration
    // (either 0 or 1 lines depending on implementation)
    EXPECT_LE(lines.size(), 1u);
}

// Test that a short string fits in one line
TEST_F(ColumnTest_47, ShortStringOneLine_47) {
    Column col("Hello");
    col.width(79);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "Hello");
}

// Test text wrapping when text exceeds width
TEST_F(ColumnTest_47, TextWrapping_47) {
    Column col("This is a longer piece of text that should be wrapped");
    col.width(20);
    auto lines = collectLines(col);
    EXPECT_GT(lines.size(), 1u);
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 20u);
    }
}

// Test that indent affects the output lines (subsequent lines should have indent)
TEST_F(ColumnTest_47, IndentAffectsLines_47) {
    Column col("This is a text that needs to wrap around to test indentation behavior");
    col.width(30).indent(4);
    auto lines = collectLines(col);
    if (lines.size() > 1) {
        // Subsequent lines should start with spaces due to indent
        for (size_t i = 1; i < lines.size(); ++i) {
            EXPECT_GE(lines[i].size(), 4u);
            EXPECT_EQ(lines[i].substr(0, 4), "    ");
        }
    }
}

// Test that initialIndent affects the first line
TEST_F(ColumnTest_47, InitialIndentAffectsFirstLine_47) {
    Column col("This is a text that needs to wrap");
    col.width(30).initialIndent(4);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // First line should be indented
    EXPECT_GE(lines[0].size(), 4u);
    EXPECT_EQ(lines[0].substr(0, 4), "    ");
}

// Test operator<< outputs to stream
TEST_F(ColumnTest_47, StreamOutputOperator_47) {
    Column col("Hello World");
    col.width(79);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

// Test operator+ combines two columns
TEST_F(ColumnTest_47, ColumnAddition_47) {
    Column col1("Left column text");
    Column col2("Right column text");
    col1.width(20);
    col2.width(20);
    auto combined = col1 + col2;
    std::ostringstream oss;
    oss << combined;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test operator+ with rvalue columns
TEST_F(ColumnTest_47, ColumnAdditionRvalue_47) {
    auto combined = Column("Left") + Column("Right");
    std::ostringstream oss;
    oss << combined;
    EXPECT_FALSE(oss.str().empty());
}

// Test begin and end iterators for a single-line text
TEST_F(ColumnTest_47, IteratorSingleLine_47) {
    Column col("Short");
    col.width(79);
    auto it = col.begin();
    auto endIt = col.end();
    EXPECT_NE(it, endIt);
    std::string first = *it;
    EXPECT_EQ(first, "Short");
    ++it;
    EXPECT_EQ(it, endIt);
}

// Test large width doesn't wrap text
TEST_F(ColumnTest_47, LargeWidthNoWrap_47) {
    std::string longText = "This is a fairly long sentence that we want to appear on a single line";
    Column col(longText);
    col.width(200);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], longText);
}

// Test very narrow width forces wrapping
TEST_F(ColumnTest_47, VeryNarrowWidth_47) {
    Column col("abcdef ghijkl");
    col.width(5);
    auto lines = collectLines(col);
    EXPECT_GT(lines.size(), 1u);
}

// Test indent with zero value (no indentation)
TEST_F(ColumnTest_47, ZeroIndent_47) {
    Column col("Hello World");
    col.width(79).indent(0);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // With no indent, the first character shouldn't be a space (assuming text doesn't start with space)
    if (!lines[0].empty()) {
        EXPECT_NE(lines[0][0], ' ');
    }
}

// Test that multiline text (with newlines) is handled
TEST_F(ColumnTest_47, MultilineText_47) {
    Column col("Line one\nLine two\nLine three");
    col.width(79);
    auto lines = collectLines(col);
    EXPECT_GE(lines.size(), 3u);
}

// Test a single character
TEST_F(ColumnTest_47, SingleCharacter_47) {
    Column col("X");
    col.width(79);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "X");
}

// Test setting width multiple times - last one wins
TEST_F(ColumnTest_47, MultipleWidthSets_47) {
    Column col("test");
    col.width(10);
    EXPECT_EQ(col.width(), 10u);
    col.width(30);
    EXPECT_EQ(col.width(), 30u);
    col.width(5);
    EXPECT_EQ(col.width(), 5u);
}
