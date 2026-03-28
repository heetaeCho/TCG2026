#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::TextFlow;

// ============================================================
// Tests for Column
// ============================================================

TEST(ColumnTest_623, ConstructFromConstString_623) {
    std::string text = "Hello, World!";
    Column col(text);
    EXPECT_EQ(col.width(), 80 - 1);
}

TEST(ColumnTest_623, ConstructFromRValueString_623) {
    Column col(std::string("Hello, World!"));
    EXPECT_EQ(col.width(), 80 - 1);
}

TEST(ColumnTest_623, DefaultWidth_623) {
    Column col("test");
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_623, SetWidth_623) {
    Column col("test");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST(ColumnTest_623, SetIndent_623) {
    Column col("test text");
    col.indent(4);
    // Verify it doesn't crash and column is still usable
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_623, SetInitialIndent_623) {
    Column col("test text");
    col.initialIndent(8);
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_623, ChainedModifiers_623) {
    Column col("test text");
    col.width(50).indent(4).initialIndent(8);
    EXPECT_EQ(col.width(), 50u);
}

TEST(ColumnTest_623, EmptyString_623) {
    Column col("");
    EXPECT_EQ(col.width(), 79u);
    // Should be iterable even if empty
    std::ostringstream oss;
    oss << col;
    // Empty column should produce something (possibly empty or newline)
    // We just check it doesn't crash
}

TEST(ColumnTest_623, BeginEndIterator_623) {
    Column col("Hello");
    auto it = col.begin();
    auto endIt = col.end();
    // For a short string within width, there should be at least one line
    EXPECT_NE(it, endIt);
}

TEST(ColumnTest_623, StreamOutput_623) {
    Column col("Hello, World!");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello, World!"), std::string::npos);
}

TEST(ColumnTest_623, WidthWrapsLongText_623) {
    Column col("This is a long piece of text that should be wrapped across multiple lines when the width is set to a small value");
    col.width(20);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // Output should contain newlines since text is longer than 20 chars
    EXPECT_NE(output.find('\n'), std::string::npos);
}

TEST(ColumnTest_623, IndentApplied_623) {
    Column col("Hello");
    col.indent(4);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // The output should start with spaces due to indent
    EXPECT_EQ(output.substr(0, 4), "    ");
}

TEST(ColumnTest_623, InitialIndentDiffersFromIndent_623) {
    Column col("First line then second line wrapping text that is long enough to wrap");
    col.width(30).indent(4).initialIndent(8);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // First line should have 8 spaces of indent
    EXPECT_EQ(output.substr(0, 8), "        ");
}

TEST(ColumnTest_623, VerySmallWidth_623) {
    Column col("Hello World");
    col.width(1);
    // Should not crash, even if width is very small
    std::ostringstream oss;
    oss << col;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Tests for Column operator+
// ============================================================

TEST(ColumnPlusTest_623, TwoColumnsOperatorPlus_623) {
    Column left("Left column text");
    Column right("Right column text");
    Columns cols = left + right;
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ColumnPlusTest_623, TwoColumnsContainBothTexts_623) {
    Column left("LeftText");
    Column right("RightText");
    left.width(20);
    right.width(20);
    Columns cols = left + right;
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("LeftText"), std::string::npos);
    EXPECT_NE(output.find("RightText"), std::string::npos);
}

// ============================================================
// Tests for Columns
// ============================================================

TEST(ColumnsTest_623, PlusEqualColumn_623) {
    Columns cols;
    Column col("Hello");
    cols += col;
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello"), std::string::npos);
}

TEST(ColumnsTest_623, PlusEqualMultipleColumns_623) {
    Columns cols;
    Column col1("First");
    col1.width(20);
    Column col2("Second");
    col2.width(20);
    cols += col1;
    cols += col2;
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("First"), std::string::npos);
    EXPECT_NE(output.find("Second"), std::string::npos);
}

TEST(ColumnsTest_623, ColumnsPlusColumn_623) {
    Column col1("Alpha");
    col1.width(20);
    Column col2("Beta");
    col2.width(20);
    Column col3("Gamma");
    col3.width(20);
    
    Columns cols = col1 + col2;
    Columns result = cols + col3;
    
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("Alpha"), std::string::npos);
    EXPECT_NE(output.find("Beta"), std::string::npos);
    EXPECT_NE(output.find("Gamma"), std::string::npos);
}

TEST(ColumnsTest_623, BeginEndIterator_623) {
    Column col("Hello");
    Columns cols;
    cols += col;
    
    auto it = cols.begin();
    auto endIt = cols.end();
    EXPECT_NE(it, endIt);
}

TEST(ColumnsTest_623, StreamOutputEmpty_623) {
    Columns cols;
    std::ostringstream oss;
    oss << cols;
    // An empty Columns should not crash
    // Output may be empty or minimal
}

TEST(ColumnsTest_623, PlusEqualRValueColumn_623) {
    Columns cols;
    cols += Column("Moved");
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Moved"), std::string::npos);
}

TEST(ColumnsTest_623, MultipleColumnWrapping_623) {
    Column col1("This is a long text for the first column that will need to wrap");
    col1.width(20);
    Column col2("Short");
    col2.width(20);
    
    Columns cols = col1 + col2;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    // Both texts should appear
    EXPECT_NE(output.find("Short"), std::string::npos);
    // The output should have multiple lines due to wrapping
    size_t newline_count = std::count(output.begin(), output.end(), '\n');
    EXPECT_GT(newline_count, 0u);
}

TEST(ColumnsTest_623, RValueColumnsPlusColumn_623) {
    Column col1("One");
    col1.width(20);
    Column col2("Two");
    col2.width(20);
    Column col3("Three");
    col3.width(20);
    
    // Test rvalue Columns + Column
    Columns result = (col1 + col2) + col3;
    
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("One"), std::string::npos);
    EXPECT_NE(output.find("Two"), std::string::npos);
    EXPECT_NE(output.find("Three"), std::string::npos);
}

// ============================================================
// Boundary tests
// ============================================================

TEST(ColumnBoundaryTest_623, ExactWidthText_623) {
    // Text exactly as wide as the column
    std::string text(79, 'A');
    Column col(text);
    
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find(text), std::string::npos);
}

TEST(ColumnBoundaryTest_623, TextOneCharOverWidth_623) {
    std::string text(80, 'B');
    Column col(text);
    col.width(79);
    
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // Should wrap, so there should be a newline
    EXPECT_NE(output.find('\n'), std::string::npos);
}

TEST(ColumnBoundaryTest_623, SingleCharText_623) {
    Column col("X");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("X"), std::string::npos);
}

TEST(ColumnBoundaryTest_623, WhitespaceOnlyText_623) {
    Column col("   ");
    std::ostringstream oss;
    oss << col;
    // Should not crash
}

TEST(ColumnBoundaryTest_623, NewlinesInText_623) {
    Column col("Line1\nLine2\nLine3");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("Line1"), std::string::npos);
    EXPECT_NE(output.find("Line2"), std::string::npos);
    EXPECT_NE(output.find("Line3"), std::string::npos);
}

TEST(ColumnBoundaryTest_623, LargeWidth_623) {
    Column col("Small text");
    col.width(10000);
    EXPECT_EQ(col.width(), 10000u);
    
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("Small text"), std::string::npos);
}
