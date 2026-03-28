#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

// Test that streaming an empty Columns object produces no output
TEST(ColumnsTest_622, EmptyColumnsProducesNoOutput_622) {
    Columns cols;
    std::ostringstream os;
    os << cols;
    EXPECT_EQ(os.str(), "");
}

// Test that streaming a Columns with a single column produces output without trailing newline
TEST(ColumnsTest_622, SingleColumnOutput_622) {
    Column col("Hello");
    Columns cols = Columns() + col;
    std::ostringstream os;
    os << cols;
    std::string result = os.str();
    // Should contain "Hello" and no leading newline
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Hello"), std::string::npos);
    // First character should not be a newline
    if (!result.empty()) {
        EXPECT_NE(result[0], '\n');
    }
}

// Test that operator<< returns the same ostream reference
TEST(ColumnsTest_622, OperatorReturnsOstream_622) {
    Columns cols;
    std::ostringstream os;
    std::ostream& ref = (os << cols);
    EXPECT_EQ(&ref, &os);
}

// Test that multiple lines are separated by newlines
TEST(ColumnsTest_622, MultipleLinesAreSeparatedByNewlines_622) {
    // Create a column with text long enough to wrap into multiple lines
    Column col("This is a fairly long piece of text that should wrap across multiple lines when the column width is narrow enough");
    col.width(20);
    Columns cols = Columns() + col;
    std::ostringstream os;
    os << cols;
    std::string result = os.str();
    // The result should contain at least one newline since text wraps
    EXPECT_NE(result.find('\n'), std::string::npos);
}

// Test that the first line does not have a leading newline
TEST(ColumnsTest_622, FirstLineNoLeadingNewline_622) {
    Column col("Test text");
    Columns cols = Columns() + col;
    std::ostringstream os;
    os << cols;
    std::string result = os.str();
    if (!result.empty()) {
        EXPECT_NE(result[0], '\n');
    }
}

// Test operator+= with Column rvalue
TEST(ColumnsTest_622, PlusEqualsWithColumn_622) {
    Columns cols;
    Column col("Added column");
    cols += col;
    std::ostringstream os;
    os << cols;
    std::string result = os.str();
    EXPECT_NE(result.find("Added column"), std::string::npos);
}

// Test operator+ creates combined columns
TEST(ColumnsTest_622, OperatorPlusCombinesColumns_622) {
    Column col1("Left");
    col1.width(20);
    Column col2("Right");
    col2.width(20);
    Columns cols = Columns() + col1 + col2;
    std::ostringstream os;
    os << cols;
    std::string result = os.str();
    // Both "Left" and "Right" should appear in the output
    EXPECT_NE(result.find("Left"), std::string::npos);
    EXPECT_NE(result.find("Right"), std::string::npos);
}

// Test that begin() and end() allow iteration
TEST(ColumnsTest_622, BeginEndIteration_622) {
    Column col("Iterate me");
    Columns cols = Columns() + col;
    int lineCount = 0;
    for (auto line : cols) {
        lineCount++;
        EXPECT_FALSE(line.empty());
    }
    EXPECT_GT(lineCount, 0);
}

// Test with multiple columns side by side, each with wrapping text
TEST(ColumnsTest_622, MultipleColumnsWithWrapping_622) {
    Column col1("AAAA BBBB CCCC DDDD EEEE");
    col1.width(10);
    Column col2("1111 2222 3333 4444 5555");
    col2.width(10);
    Columns cols = Columns() + col1 + col2;
    std::ostringstream os;
    os << cols;
    std::string result = os.str();
    // Should have multiple lines
    size_t newlineCount = std::count(result.begin(), result.end(), '\n');
    EXPECT_GT(newlineCount, 0u);
}

// Test streaming columns to an already-populated stream
TEST(ColumnsTest_622, StreamToPopulatedOstream_622) {
    Column col("World");
    Columns cols = Columns() + col;
    std::ostringstream os;
    os << "Hello ";
    os << cols;
    std::string result = os.str();
    EXPECT_EQ(result.substr(0, 6), "Hello ");
    EXPECT_NE(result.find("World"), std::string::npos);
}

// Test chaining operator<< calls
TEST(ColumnsTest_622, ChainingStreamOperator_622) {
    Column col("Chain");
    Columns cols = Columns() + col;
    std::ostringstream os;
    os << cols << " end";
    std::string result = os.str();
    EXPECT_NE(result.find("Chain"), std::string::npos);
    EXPECT_NE(result.find(" end"), std::string::npos);
}

// Test that a single short line has no newline in output
TEST(ColumnsTest_622, SingleShortLineNoNewline_622) {
    Column col("Hi");
    col.width(80);
    Columns cols = Columns() + col;
    std::ostringstream os;
    os << cols;
    std::string result = os.str();
    // "Hi" fits in 80 chars, so should be a single line with no newline
    EXPECT_EQ(result.find('\n'), std::string::npos);
}
