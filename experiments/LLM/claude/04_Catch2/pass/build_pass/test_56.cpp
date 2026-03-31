#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

class ColumnsTest_56 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed Columns has begin() == end() (empty iteration)
TEST_F(ColumnsTest_56, DefaultConstructedColumnsIsEmpty_56) {
    Columns cols;
    auto it = cols.begin();
    auto endIt = cols.end();
    EXPECT_EQ(it, endIt);
}

// Test that iterating over empty Columns produces no rows
TEST_F(ColumnsTest_56, EmptyColumnsProducesNoOutput_56) {
    Columns cols;
    int count = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 0);
}

// Test operator+= with a Column adds it to the Columns
TEST_F(ColumnsTest_56, OperatorPlusEqualsAddsColumn_56) {
    Column col("Hello");
    Columns cols;
    cols += std::move(col);
    // After adding a column, iteration should produce at least one row
    auto it = cols.begin();
    EXPECT_NE(it, cols.end());
}

// Test operator+ creates a new Columns from existing Columns and a Column
TEST_F(ColumnsTest_56, OperatorPlusCombinesColumnsAndColumn_56) {
    Column col1("Left");
    col1.width(20);
    Column col2("Right");
    col2.width(20);
    
    Columns cols;
    cols += std::move(col1);
    Columns result = std::move(cols) + std::move(col2);
    
    auto it = result.begin();
    EXPECT_NE(it, result.end());
}

// Test streaming Columns to ostream produces output
TEST_F(ColumnsTest_56, StreamOutputProducesNonEmptyString_56) {
    Column col("Test content");
    col.width(40);
    Columns cols;
    cols += std::move(col);
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Test content"), std::string::npos);
}

// Test streaming empty Columns produces empty or no output
TEST_F(ColumnsTest_56, StreamEmptyColumnsProducesEmptyOutput_56) {
    Columns cols;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_TRUE(output.empty());
}

// Test multiple columns side by side
TEST_F(ColumnsTest_56, MultipleColumnsSideBySide_56) {
    Column col1("Left column text");
    col1.width(20);
    Column col2("Right column text");
    col2.width(20);
    
    Columns cols;
    cols += std::move(col1);
    cols += std::move(col2);
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test that end() iterator is consistent across multiple calls
TEST_F(ColumnsTest_56, EndIteratorIsConsistent_56) {
    Columns cols;
    auto end1 = cols.end();
    auto end2 = cols.end();
    EXPECT_EQ(end1, end2);
}

// Test Column with long text that wraps
TEST_F(ColumnsTest_56, ColumnWithWrappingText_56) {
    Column col("This is a very long text that should definitely wrap across multiple lines when the width is set to a small value");
    col.width(20);
    
    Columns cols;
    cols += std::move(col);
    
    int lineCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GT(lineCount, 1);
}

// Test range-based for loop works with Columns
TEST_F(ColumnsTest_56, RangeBasedForLoopWorks_56) {
    Column col("Hello World");
    col.width(40);
    Columns cols;
    cols += std::move(col);
    
    int count = 0;
    for (const auto& line : cols) {
        (void)line;
        ++count;
    }
    EXPECT_GE(count, 1);
}

// Test operator+ with const lhs Columns and const Column
TEST_F(ColumnsTest_56, OperatorPlusConstVersion_56) {
    Column col1("A");
    col1.width(20);
    Columns cols;
    cols += std::move(col1);
    
    Column col2("B");
    col2.width(20);
    
    const Columns& constCols = cols;
    Columns result = constCols + col2;
    
    std::ostringstream oss;
    oss << result;
    EXPECT_FALSE(oss.str().empty());
}

// Test single character column
TEST_F(ColumnsTest_56, SingleCharacterColumn_56) {
    Column col("X");
    col.width(10);
    Columns cols;
    cols += std::move(col);
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("X"), std::string::npos);
}

// Test empty string column
TEST_F(ColumnsTest_56, EmptyStringColumn_56) {
    Column col("");
    col.width(20);
    Columns cols;
    cols += std::move(col);
    
    // Even an empty column may produce iteration entries
    std::ostringstream oss;
    oss << cols;
    // Should not crash
}

// Test three columns combined
TEST_F(ColumnsTest_56, ThreeColumnsCombined_56) {
    Column col1("First");
    col1.width(15);
    Column col2("Second");
    col2.width(15);
    Column col3("Third");
    col3.width(15);
    
    Columns cols;
    cols += std::move(col1);
    cols += std::move(col2);
    cols += std::move(col3);
    
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}
