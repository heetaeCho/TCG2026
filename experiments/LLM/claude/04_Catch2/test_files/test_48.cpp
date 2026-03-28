#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using Catch::TextFlow::Column;

class ColumnTest_48 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a Column can be constructed from a const string reference
TEST_F(ColumnTest_48, ConstructFromConstString_48) {
    std::string text = "Hello, World!";
    Column col(text);
    // Should be constructible without throwing
    EXPECT_EQ(col.width(), 79); // default width is CATCH_CONFIG_CONSOLE_WIDTH - 1 = 80 - 1 = 79
}

// Test that a Column can be constructed from an rvalue string
TEST_F(ColumnTest_48, ConstructFromRvalueString_48) {
    Column col(std::string("Hello, World!"));
    EXPECT_EQ(col.width(), 79);
}

// Test that indent returns a reference to the same Column (chaining)
TEST_F(ColumnTest_48, IndentReturnsSelf_48) {
    Column col("test");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

// Test that width setter returns a reference to the same Column (chaining)
TEST_F(ColumnTest_48, WidthSetterReturnsSelf_48) {
    Column col("test");
    Column& ref = col.width(40);
    EXPECT_EQ(&ref, &col);
}

// Test that width getter returns the set width
TEST_F(ColumnTest_48, WidthGetterReturnsSetWidth_48) {
    Column col("test");
    col.width(50);
    EXPECT_EQ(col.width(), 50);
}

// Test default width
TEST_F(ColumnTest_48, DefaultWidth_48) {
    Column col("test");
    EXPECT_EQ(col.width(), 79);
}

// Test initialIndent returns a reference to the same Column (chaining)
TEST_F(ColumnTest_48, InitialIndentReturnsSelf_48) {
    Column col("test");
    Column& ref = col.initialIndent(4);
    EXPECT_EQ(&ref, &col);
}

// Test chaining multiple setters
TEST_F(ColumnTest_48, ChainingSetters_48) {
    Column col("test");
    Column& ref = col.width(40).indent(4).initialIndent(2);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 40);
}

// Test that begin and end iterators are valid for an empty string
TEST_F(ColumnTest_48, EmptyStringIteration_48) {
    Column col("");
    auto it = col.begin();
    auto endIt = col.end();
    // An empty column should still produce at least one (empty) line or be empty
    // We just verify that iterating doesn't crash
    int count = 0;
    for (auto i = col.begin(); i != col.end(); ++i) {
        ++count;
    }
    // At least zero or more lines
    EXPECT_GE(count, 0);
}

// Test iteration over a short string that fits in one line
TEST_F(ColumnTest_48, ShortStringOneLine_48) {
    Column col("Hello");
    col.width(79);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 1);
}

// Test iteration over a long string that wraps
TEST_F(ColumnTest_48, LongStringWraps_48) {
    // Create a string longer than default width of 79
    std::string longText(200, 'a');
    Column col(longText);
    col.width(79);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GT(count, 1);
}

// Test output stream operator
TEST_F(ColumnTest_48, OutputStreamOperator_48) {
    Column col("Hello, World!");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // The output should contain the original text
    EXPECT_NE(output.find("Hello, World!"), std::string::npos);
}

// Test output with indent
TEST_F(ColumnTest_48, OutputWithIndent_48) {
    Column col("Hello");
    col.indent(4);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // The output should start with spaces for indentation
    EXPECT_EQ(output.substr(0, 4), "    ");
    EXPECT_NE(output.find("Hello"), std::string::npos);
}

// Test output with initialIndent different from indent
TEST_F(ColumnTest_48, OutputWithInitialIndent_48) {
    Column col("Hello");
    col.indent(2).initialIndent(6);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // First line should have 6 spaces of indentation
    EXPECT_EQ(output.substr(0, 6), "      ");
    EXPECT_NE(output.find("Hello"), std::string::npos);
}

// Test width of 1 (boundary condition)
TEST_F(ColumnTest_48, VerySmallWidth_48) {
    Column col("ab cd");
    col.width(1);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    // With width 1, each character or word should be on its own line
    EXPECT_GT(count, 1);
}

// Test operator+ for combining two columns
TEST_F(ColumnTest_48, CombineTwoColumns_48) {
    Column left("Left column text");
    Column right("Right column text");
    left.width(30);
    right.width(30);
    auto combined = left + right;
    std::ostringstream oss;
    oss << combined;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

// Test operator+ with rvalue columns
TEST_F(ColumnTest_48, CombineTwoRvalueColumns_48) {
    auto combined = Column("Left").width(30) + Column("Right").width(30);
    std::ostringstream oss;
    oss << combined;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

// Test indent of 0
TEST_F(ColumnTest_48, ZeroIndent_48) {
    Column col("Hello");
    col.indent(0);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // Should start with 'H' (no indentation)
    EXPECT_EQ(output[0], 'H');
}

// Test multiline text with newlines
TEST_F(ColumnTest_48, TextWithNewlines_48) {
    Column col("Line1\nLine2\nLine3");
    col.width(79);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GE(count, 3);
}

// Test that setting width to a large value works
TEST_F(ColumnTest_48, LargeWidth_48) {
    Column col("Short text");
    col.width(1000);
    EXPECT_EQ(col.width(), 1000);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 1);
}

// Test word wrapping at word boundaries
TEST_F(ColumnTest_48, WordWrapping_48) {
    Column col("The quick brown fox jumps over the lazy dog");
    col.width(20);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // Each line should not exceed width (approximately)
    std::istringstream iss(output);
    std::string line;
    while (std::getline(iss, line)) {
        EXPECT_LE(line.size(), 20u);
    }
}
