#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::TextFlow;

// ============================================================
// Column Tests
// ============================================================

TEST(ColumnTest_628, ConstructFromConstString_628) {
    std::string text = "Hello World";
    Column col(text);
    // Default width should be 79 (80 - 1)
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_628, ConstructFromRValueString_628) {
    Column col(std::string("Hello World"));
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_628, SetWidth_628) {
    Column col("Hello");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST(ColumnTest_628, SetWidthChaining_628) {
    Column col("Hello");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50u);
}

TEST(ColumnTest_628, SetIndentChaining_628) {
    Column col("Hello");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_628, SetInitialIndentChaining_628) {
    Column col("Hello");
    Column& ref = col.initialIndent(8);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_628, IteratorBeginEnd_628) {
    Column col("Hello");
    col.width(79);
    auto it = col.begin();
    auto endIt = col.end();
    // At least one line should be produced
    EXPECT_NE(it, endIt);
}

TEST(ColumnTest_628, EmptyString_628) {
    Column col("");
    auto it = col.begin();
    auto endIt = col.end();
    // Even empty string should produce at least one iteration or zero
    // We just ensure no crash
    int count = 0;
    for (auto i = col.begin(); i != col.end(); ++i) {
        ++count;
    }
    EXPECT_GE(count, 0);
}

TEST(ColumnTest_628, StreamOutput_628) {
    Column col("Hello World");
    col.width(79);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST(ColumnTest_628, WidthWrapping_628) {
    Column col("This is a long line that should be wrapped when the width is small");
    col.width(10);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    // Result should contain newlines due to wrapping
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST(ColumnTest_628, IndentAffectsOutput_628) {
    Column col("Hello");
    col.width(79).indent(4);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    // The output should contain the word Hello
    EXPECT_NE(result.find("Hello"), std::string::npos);
}

TEST(ColumnTest_628, InitialIndentAffectsOutput_628) {
    Column col("Hello World Test");
    col.width(20).initialIndent(4).indent(2);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_NE(result.find("Hello"), std::string::npos);
}

TEST(ColumnTest_628, WidthOfOne_628) {
    // Boundary: very small width
    Column col("AB");
    col.width(1);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    // Should not crash; content should appear
    EXPECT_FALSE(result.empty());
}

TEST(ColumnTest_628, LargeWidth_628) {
    Column col("Short");
    col.width(1000);
    EXPECT_EQ(col.width(), 1000u);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_NE(result.find("Short"), std::string::npos);
}

// ============================================================
// Column operator+ Tests
// ============================================================

TEST(ColumnPlusTest_628, TwoColumnsFromLValueAdd_628) {
    Column left("Left column text");
    Column right("Right column text");
    left.width(30);
    right.width(30);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Left"), std::string::npos);
    EXPECT_NE(result.find("Right"), std::string::npos);
}

TEST(ColumnPlusTest_628, TwoColumnsFromRValueAdd_628) {
    Columns cols = Column("Left text") + Column("Right text");
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Left"), std::string::npos);
    EXPECT_NE(result.find("Right"), std::string::npos);
}

// ============================================================
// Columns Tests
// ============================================================

TEST(ColumnsTest_628, PlusEqualWithColumn_628) {
    Column col1("First");
    col1.width(30);
    Column col2("Second");
    col2.width(30);
    Columns cols = col1 + col2;

    Column col3("Third");
    col3.width(20);
    cols += col3;

    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("First"), std::string::npos);
    EXPECT_NE(result.find("Second"), std::string::npos);
    EXPECT_NE(result.find("Third"), std::string::npos);
}

TEST(ColumnsTest_628, PlusEqualWithRValueColumn_628) {
    Columns cols = Column("First") + Column("Second");
    cols += Column("Third");

    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Third"), std::string::npos);
}

TEST(ColumnsTest_628, ColumnsPlusColumn_628) {
    Columns cols = Column("A") + Column("B");
    Column col3("C");
    Columns result = cols + col3;
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
}

TEST(ColumnsTest_628, ColumnsRValuePlusColumnRValue_628) {
    // This tests the operator+(Columns&&, Column&&) which is the function
    // implemented in the .cpp file
    Columns result = (Column("X") + Column("Y")) + Column("Z");
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("X"), std::string::npos);
    EXPECT_NE(output.find("Y"), std::string::npos);
    EXPECT_NE(output.find("Z"), std::string::npos);
}

TEST(ColumnsTest_628, IteratorBeginEnd_628) {
    Columns cols = Column("Hello") + Column("World");
    auto it = cols.begin();
    auto endIt = cols.end();
    int count = 0;
    for (auto i = cols.begin(); i != cols.end(); ++i) {
        ++count;
    }
    EXPECT_GT(count, 0);
}

TEST(ColumnsTest_628, StreamOutputFormatting_628) {
    Column left("Left side content here");
    left.width(25);
    Column right("Right side content here");
    right.width(25);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST(ColumnsTest_628, EmptyColumns_628) {
    Column left("");
    Column right("");
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    // Should not crash
    std::string result = oss.str();
    // Result may or may not be empty depending on implementation
}

TEST(ColumnsTest_628, MultipleColumnsConcatenation_628) {
    // Chain multiple columns together
    Columns cols = Column("A") + Column("B");
    cols += Column("C");
    cols += Column("D");

    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("A"), std::string::npos);
    EXPECT_NE(result.find("D"), std::string::npos);
}

TEST(ColumnsTest_628, ColumnWithWrappingInMultiColumn_628) {
    Column left("This is a very long text that will wrap multiple times in a narrow column");
    left.width(15);
    Column right("Short");
    right.width(15);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Short"), std::string::npos);
}

TEST(ColumnsTest_628, ColumnWithIndentInMultiColumn_628) {
    Column left("Hello World");
    left.width(20).indent(2);
    Column right("Foo Bar");
    right.width(20).indent(3);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Hello"), std::string::npos);
    EXPECT_NE(result.find("Foo"), std::string::npos);
}

// ============================================================
// Specific test for the operator+(Columns&&, Column&&) from the .cpp file
// ============================================================

TEST(ColumnsOperatorPlusTest_628, MoveSemantics_628) {
    // Directly exercise the function: Columns operator+(Columns&& lhs, Column&& rhs)
    Columns base = Column("Base1") + Column("Base2");
    Columns result = std::move(base) + Column("Added");

    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("Base1"), std::string::npos);
    EXPECT_NE(output.find("Base2"), std::string::npos);
    EXPECT_NE(output.find("Added"), std::string::npos);
}

TEST(ColumnsOperatorPlusTest_628, ChainedMoveAdditions_628) {
    Columns result = (Column("A") + Column("B")) + Column("C");
    result = std::move(result) + Column("D");

    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
    EXPECT_NE(output.find("D"), std::string::npos);
}
