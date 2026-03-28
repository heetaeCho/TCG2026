#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::TextFlow;

// Test that operator+= with rvalue Column adds a column to Columns
TEST(ColumnsOperatorPlusEqual_626, AddsRvalueColumnToColumns_626) {
    Column col1("Hello");
    Column col2("World");
    
    Columns cols;
    cols += std::move(col1);
    cols += std::move(col2);
    
    // Verify by iterating - if we have content from both columns, the operator worked
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Hello"), std::string::npos);
    EXPECT_NE(result.find("World"), std::string::npos);
}

// Test that operator+= returns a reference to lhs (chaining)
TEST(ColumnsOperatorPlusEqual_626, ReturnsSelfReference_626) {
    Columns cols;
    Column col("Test");
    
    Columns& ref = (cols += std::move(col));
    EXPECT_EQ(&ref, &cols);
}

// Test adding a single column via operator+=
TEST(ColumnsOperatorPlusEqual_626, SingleColumn_626) {
    Columns cols;
    Column col("Single column text");
    cols += std::move(col);
    
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Single column text"), std::string::npos);
}

// Test adding an empty string column
TEST(ColumnsOperatorPlusEqual_626, EmptyColumn_626) {
    Columns cols;
    Column col("");
    cols += std::move(col);
    
    // Should not crash; output may be empty or whitespace
    std::ostringstream oss;
    oss << cols;
    // Just verify no crash occurred
    SUCCEED();
}

// Test chaining multiple operator+= calls
TEST(ColumnsOperatorPlusEqual_626, ChainingMultipleAdds_626) {
    Columns cols;
    cols += Column("First");
    cols += Column("Second");
    cols += Column("Third");
    
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("First"), std::string::npos);
    EXPECT_NE(result.find("Second"), std::string::npos);
    EXPECT_NE(result.find("Third"), std::string::npos);
}

// Test Column construction and basic output
TEST(ColumnBasic_626, ConstructAndOutput_626) {
    Column col("Hello World");
    std::ostringstream oss;
    oss << col;
    EXPECT_NE(oss.str().find("Hello World"), std::string::npos);
}

// Test Column width setter and getter
TEST(ColumnBasic_626, WidthSetterGetter_626) {
    Column col("Test");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

// Test Column + Column produces Columns
TEST(ColumnOperatorPlus_626, TwoColumnsProduceColumns_626) {
    Column col1("Left");
    Column col2("Right");
    
    Columns result = col1 + col2;
    
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

// Test Columns + Column produces combined Columns
TEST(ColumnsOperatorPlus_626, ColumnsAddColumn_626) {
    Column col1("A");
    Column col2("B");
    Column col3("C");
    
    Columns cols = col1 + col2;
    Columns result = std::move(cols) + std::move(col3);
    
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
}

// Test Column with long text wraps within width
TEST(ColumnBasic_626, LongTextWrapsWithinWidth_626) {
    Column col("This is a relatively long piece of text that should be wrapped at the specified column width boundary");
    col.width(20);
    
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    
    // Each line should not exceed the width (approximately)
    std::istringstream iss(output);
    std::string line;
    while (std::getline(iss, line)) {
        // Lines should generally respect the width constraint
        // (allowing some tolerance for word boundaries)
        EXPECT_LE(line.size(), 25u); // small tolerance
    }
}

// Test Column indent
TEST(ColumnBasic_626, IndentApplied_626) {
    Column col("Indented text");
    col.indent(4);
    
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // The output should have leading spaces
    EXPECT_EQ(output.substr(0, 4), "    ");
}

// Test Column initialIndent
TEST(ColumnBasic_626, InitialIndentApplied_626) {
    Column col("Initial indent text that is long enough to wrap onto a second line for testing");
    col.width(30);
    col.initialIndent(6);
    col.indent(2);
    
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // First line should start with 6 spaces
    EXPECT_EQ(output.substr(0, 6), "      ");
}

// Test Column iterators are valid
TEST(ColumnBasic_626, IteratorsWork_626) {
    Column col("Line of text");
    
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GE(lineCount, 1);
}

// Test Columns iterators are valid
TEST(ColumnsBasic_626, IteratorsWork_626) {
    Column col1("Left");
    Column col2("Right");
    Columns cols = col1 + col2;
    
    int lineCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GE(lineCount, 1);
}

// Test operator+= with column having custom width
TEST(ColumnsOperatorPlusEqual_626, ColumnWithCustomWidth_626) {
    Columns cols;
    Column col("Narrow");
    col.width(10);
    cols += std::move(col);
    
    std::ostringstream oss;
    oss << cols;
    EXPECT_NE(oss.str().find("Narrow"), std::string::npos);
}

// Test move semantics - Column rvalue via operator+ 
TEST(ColumnOperatorPlus_626, RvalueColumns_626) {
    Columns result = Column("Left") + Column("Right");
    
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

// Test default width
TEST(ColumnBasic_626, DefaultWidth_626) {
    Column col("Test");
    EXPECT_EQ(col.width(), 79u); // 80 - 1 as per header
}

// Test width of 1 (boundary)
TEST(ColumnBasic_626, MinimalWidth_626) {
    Column col("ab");
    col.width(1);
    
    std::ostringstream oss;
    oss << col;
    // Should not crash with very small width
    SUCCEED();
}
