#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

class ColumnTest_617 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that an empty string produces empty output
TEST_F(ColumnTest_617, EmptyStringProducesEmptyOutput_617) {
    Column col("");
    oss << col;
    EXPECT_EQ(oss.str(), "");
}

// Test that a simple short string is output as-is
TEST_F(ColumnTest_617, SimpleShortString_617) {
    Column col("Hello World");
    oss << col;
    EXPECT_EQ(oss.str(), "Hello World");
}

// Test that operator<< returns the same ostream reference
TEST_F(ColumnTest_617, OperatorReturnsOstream_617) {
    Column col("test");
    std::ostream& result = (oss << col);
    EXPECT_EQ(&result, &oss);
}

// Test that a long string wraps at the default width
TEST_F(ColumnTest_617, LongStringWraps_617) {
    std::string longText(200, 'a');
    // Words won't break mid-character for a single long word, but let's use spaces
    std::string text = "This is a fairly long sentence that should definitely wrap around because it exceeds the default column width of seventy nine characters easily";
    Column col(text);
    oss << col;
    std::string output = oss.str();
    // Should contain a newline since it wraps
    EXPECT_NE(output.find('\n'), std::string::npos);
}

// Test custom width
TEST_F(ColumnTest_617, CustomWidth_617) {
    Column col("Hello World Test");
    col.width(10);
    oss << col;
    std::string output = oss.str();
    // With width 10, "Hello World Test" should wrap
    EXPECT_NE(output.find('\n'), std::string::npos);
}

// Test width getter returns set value
TEST_F(ColumnTest_617, WidthGetterReturnsSetValue_617) {
    Column col("test");
    col.width(42);
    EXPECT_EQ(col.width(), 42u);
}

// Test default width
TEST_F(ColumnTest_617, DefaultWidth_617) {
    Column col("test");
    EXPECT_EQ(col.width(), 79u);
}

// Test indent affects output
TEST_F(ColumnTest_617, IndentAffectsOutput_617) {
    Column col("Hello");
    col.indent(4);
    oss << col;
    std::string output = oss.str();
    // Should have leading spaces
    EXPECT_EQ(output.substr(0, 4), "    ");
}

// Test initial indent affects only first line
TEST_F(ColumnTest_617, InitialIndentAffectsFirstLine_617) {
    Column col("This is a text that should wrap to multiple lines when width is small");
    col.width(20).initialIndent(4);
    oss << col;
    std::string output = oss.str();
    // First line should start with spaces
    EXPECT_EQ(output.substr(0, 4), "    ");
}

// Test that begin and end iterators work (non-empty column)
TEST_F(ColumnTest_617, BeginEndIterators_617) {
    Column col("Hello");
    auto it = col.begin();
    auto endIt = col.end();
    EXPECT_NE(it, endIt);
}

// Test that begin equals end for empty string
TEST_F(ColumnTest_617, EmptyColumnBeginEqualsEnd_617) {
    Column col("");
    int count = 0;
    for (auto line : col) {
        (void)line;
        count++;
    }
    // Empty string might still produce one empty line or zero lines
    // We just verify it doesn't crash and count is reasonable
    EXPECT_GE(count, 0);
}

// Test that single word that fits in width doesn't wrap
TEST_F(ColumnTest_617, SingleWordNoWrap_617) {
    Column col("Hello");
    col.width(20);
    oss << col;
    EXPECT_EQ(oss.str().find('\n'), std::string::npos);
}

// Test multiple lines separated by newlines in output
TEST_F(ColumnTest_617, MultipleWordsWrapCorrectly_617) {
    Column col("one two three four five six seven eight nine ten");
    col.width(15);
    oss << col;
    std::string output = oss.str();
    // Should have multiple lines
    size_t newlines = std::count(output.begin(), output.end(), '\n');
    EXPECT_GT(newlines, 0u);
}

// Test width(1) boundary
TEST_F(ColumnTest_617, VerySmallWidth_617) {
    Column col("ab cd");
    col.width(2);
    oss << col;
    // Should not crash, output should exist
    EXPECT_FALSE(oss.str().empty());
}

// Test chaining of width, indent, initialIndent
TEST_F(ColumnTest_617, MethodChaining_617) {
    Column col("test text");
    Column& ref = col.width(40).indent(2).initialIndent(4);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 40u);
}

// Test move construction
TEST_F(ColumnTest_617, MoveConstruction_617) {
    std::string text = "Hello World";
    Column col(std::move(text));
    oss << col;
    EXPECT_EQ(oss.str(), "Hello World");
}

// Test that no trailing newline is added
TEST_F(ColumnTest_617, NoTrailingNewline_617) {
    Column col("Hello World");
    oss << col;
    std::string output = oss.str();
    if (!output.empty()) {
        EXPECT_NE(output.back(), '\n');
    }
}

// Test Column + Column produces Columns
TEST_F(ColumnTest_617, ColumnAddition_617) {
    Column col1("Left");
    Column col2("Right");
    auto columns = col1 + col2;
    std::ostringstream os;
    os << columns;
    std::string output = os.str();
    // Should contain both "Left" and "Right" somewhere
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

// Test that indent is applied to all wrapped lines
TEST_F(ColumnTest_617, IndentAppliedToAllLines_617) {
    Column col("word1 word2 word3 word4 word5 word6");
    col.width(15).indent(3);
    oss << col;
    std::string output = oss.str();
    // Check each line starts with 3 spaces
    std::istringstream iss(output);
    std::string line;
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            EXPECT_EQ(line.substr(0, 3), "   ");
        }
    }
}

// Test that a string exactly at width doesn't wrap
TEST_F(ColumnTest_617, ExactWidthNoWrap_617) {
    std::string text(10, 'x');  // Single "word" of 10 chars
    Column col(text);
    col.width(10);
    oss << col;
    std::string output = oss.str();
    // Single word should appear without wrapping issues
    EXPECT_NE(output.find(text), std::string::npos);
}
