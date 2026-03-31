#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

class ColumnsTest_55 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed Columns object has begin() == end()
TEST_F(ColumnsTest_55, DefaultConstructedColumnsIsEmpty_55) {
    Columns cols;
    auto it = cols.begin();
    auto endIt = cols.end();
    EXPECT_EQ(it, endIt);
}

// Test that begin() returns a valid iterator when columns are added
TEST_F(ColumnsTest_55, BeginReturnsValidIteratorWithColumn_55) {
    Column col("Hello World");
    col.width(40);
    Columns cols;
    cols += col;
    auto it = cols.begin();
    auto endIt = cols.end();
    EXPECT_NE(it, endIt);
}

// Test that we can iterate through a single column
TEST_F(ColumnsTest_55, SingleColumnIteration_55) {
    Column col("Hello");
    col.width(80);
    Columns cols;
    cols += col;
    int lineCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GE(lineCount, 1);
}

// Test operator+= with lvalue Column
TEST_F(ColumnsTest_55, PlusEqualsLvalueColumn_55) {
    Column col("Test text");
    col.width(40);
    Columns cols;
    cols += col;
    // Should be able to iterate
    auto it = cols.begin();
    EXPECT_NE(it, cols.end());
}

// Test operator+= with rvalue Column
TEST_F(ColumnsTest_55, PlusEqualsRvalueColumn_55) {
    Columns cols;
    cols += Column("Test text").width(40);
    auto it = cols.begin();
    EXPECT_NE(it, cols.end());
}

// Test operator+ with lvalue references
TEST_F(ColumnsTest_55, PlusOperatorLvalue_55) {
    Column col1("Left column");
    col1.width(30);
    Column col2("Right column");
    col2.width(30);
    Columns cols;
    cols += col1;
    Columns result = cols + col2;
    auto it = result.begin();
    EXPECT_NE(it, result.end());
}

// Test operator+ with rvalue references
TEST_F(ColumnsTest_55, PlusOperatorRvalue_55) {
    Column col1("Left");
    col1.width(30);
    Columns cols;
    cols += col1;
    Columns result = std::move(cols) + Column("Right").width(30);
    auto it = result.begin();
    EXPECT_NE(it, result.end());
}

// Test operator<< outputs something for non-empty columns
TEST_F(ColumnsTest_55, StreamOutputNonEmpty_55) {
    Column col("Hello World");
    col.width(80);
    Columns cols;
    cols += col;
    std::ostringstream oss;
    oss << cols;
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("Hello World"), std::string::npos);
}

// Test operator<< outputs empty (or minimal) for default columns
TEST_F(ColumnsTest_55, StreamOutputEmpty_55) {
    Columns cols;
    std::ostringstream oss;
    oss << cols;
    // Empty columns should produce empty or minimal output
    EXPECT_TRUE(oss.str().empty() || oss.str() == "\n" || oss.str().find_first_not_of(" \n\t") == std::string::npos);
}

// Test multiple columns side by side
TEST_F(ColumnsTest_55, MultipleColumnsSideBySide_55) {
    Column col1("Left side text here");
    col1.width(20);
    Column col2("Right side text here");
    col2.width(20);
    Columns cols;
    cols += col1;
    cols += col2;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test that dereferencing begin() iterator gives a non-empty string for non-empty columns
TEST_F(ColumnsTest_55, DereferenceIterator_55) {
    Column col("Some text");
    col.width(80);
    Columns cols;
    cols += col;
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

// Test long text wrapping in columns
TEST_F(ColumnsTest_55, LongTextProducesMultipleLines_55) {
    std::string longText = "This is a very long text that should wrap across multiple lines when the column width is set to a small value";
    Column col(longText);
    col.width(20);
    Columns cols;
    cols += col;
    int lineCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GT(lineCount, 1);
}

// Test iterator pre-increment
TEST_F(ColumnsTest_55, IteratorPreIncrement_55) {
    std::string longText = "Word1 Word2 Word3 Word4 Word5 Word6 Word7 Word8";
    Column col(longText);
    col.width(15);
    Columns cols;
    cols += col;
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    auto& ref = ++it;
    // Should still be a valid reference
    (void)ref;
}

// Test with empty string column
TEST_F(ColumnsTest_55, EmptyStringColumn_55) {
    Column col("");
    col.width(40);
    Columns cols;
    cols += col;
    std::ostringstream oss;
    oss << cols;
    // Should not crash; output may be empty or whitespace
}

// Test adding three columns
TEST_F(ColumnsTest_55, ThreeColumns_55) {
    Column col1("Col1");
    col1.width(20);
    Column col2("Col2");
    col2.width(20);
    Column col3("Col3");
    col3.width(20);
    Columns cols;
    cols += col1;
    cols += col2;
    cols += col3;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Col1"), std::string::npos);
    EXPECT_NE(output.find("Col2"), std::string::npos);
    EXPECT_NE(output.find("Col3"), std::string::npos);
}

// Test that column width of 1 doesn't crash
TEST_F(ColumnsTest_55, VerySmallWidth_55) {
    Column col("AB");
    col.width(2);
    Columns cols;
    cols += col;
    std::ostringstream oss;
    // Should not crash
    oss << cols;
    EXPECT_FALSE(oss.str().empty());
}

// Test copy semantics of Columns via operator+
TEST_F(ColumnsTest_55, OperatorPlusCopySemantics_55) {
    Column col1("First");
    col1.width(30);
    Column col2("Second");
    col2.width(30);
    Columns cols;
    cols += col1;
    Columns result = cols + col2;
    // Original should still work
    std::ostringstream oss1;
    oss1 << cols;
    EXPECT_NE(oss1.str().find("First"), std::string::npos);
    // Result should have both
    std::ostringstream oss2;
    oss2 << result;
    EXPECT_NE(oss2.str().find("First"), std::string::npos);
    EXPECT_NE(oss2.str().find("Second"), std::string::npos);
}
