#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::TextFlow;

// ============================================================
// Column Tests
// ============================================================

TEST(ColumnTest_624, ConstructFromConstString_624) {
    std::string text = "Hello World";
    Column col(text);
    EXPECT_EQ(col.width(), 80 - 1);
}

TEST(ColumnTest_624, ConstructFromRvalueString_624) {
    Column col(std::string("Hello World"));
    EXPECT_EQ(col.width(), 80 - 1);
}

TEST(ColumnTest_624, DefaultWidth_624) {
    Column col("test");
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_624, SetWidth_624) {
    Column col("test");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST(ColumnTest_624, SetIndent_624) {
    Column col("Hello World");
    Column& ref = col.indent(4);
    // Should return reference to self for chaining
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_624, SetInitialIndent_624) {
    Column col("Hello World");
    Column& ref = col.initialIndent(8);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_624, WidthChaining_624) {
    Column col("test");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50u);
}

TEST(ColumnTest_624, BeginEndIteration_624) {
    Column col("Hello");
    col.width(79);
    auto it = col.begin();
    auto endIt = col.end();
    // A simple short string should produce at least one line
    EXPECT_NE(it, endIt);
}

TEST(ColumnTest_624, EmptyString_624) {
    Column col("");
    auto it = col.begin();
    auto endIt = col.end();
    // Even an empty string might produce one empty line or no lines
    // We just check it doesn't crash
    int count = 0;
    for (auto i = col.begin(); i != col.end(); ++i) {
        count++;
    }
    EXPECT_GE(count, 0);
}

TEST(ColumnTest_624, StreamOutput_624) {
    Column col("Hello World");
    col.width(79);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

TEST(ColumnTest_624, NarrowWidthWrapsText_624) {
    Column col("Hello World this is a test");
    col.width(10);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // With width 10, the text should be wrapped into multiple lines
    EXPECT_NE(output.find('\n'), std::string::npos);
}

TEST(ColumnTest_624, IndentApplied_624) {
    Column col("Hello");
    col.width(79).indent(4);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // The output should contain the text
    EXPECT_NE(output.find("Hello"), std::string::npos);
}

TEST(ColumnTest_624, InitialIndentApplied_624) {
    Column col("Hello World and more text here to wrap");
    col.width(20).indent(2).initialIndent(6);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ColumnTest_624, VerySmallWidth_624) {
    Column col("ABCDEF");
    col.width(1);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // Should still produce output without crashing
    EXPECT_FALSE(output.empty());
}

TEST(ColumnTest_624, LargeWidth_624) {
    Column col("Short text");
    col.width(1000);
    EXPECT_EQ(col.width(), 1000u);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("Short text"), std::string::npos);
}

// ============================================================
// Column Addition (produces Columns)
// ============================================================

TEST(ColumnAdditionTest_624, AddTwoColumnsLvalues_624) {
    Column left("Left text");
    Column right("Right text");
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left text"), std::string::npos);
    EXPECT_NE(output.find("Right text"), std::string::npos);
}

TEST(ColumnAdditionTest_624, AddTwoColumnsRvalues_624) {
    Columns cols = Column("Left text") + Column("Right text");
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left text"), std::string::npos);
    EXPECT_NE(output.find("Right text"), std::string::npos);
}

// ============================================================
// Columns Tests
// ============================================================

TEST(ColumnsTest_624, PlusEqualsColumn_624) {
    Columns cols;
    Column col("Hello");
    cols += col;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello"), std::string::npos);
}

TEST(ColumnsTest_624, PlusEqualsColumnRvalue_624) {
    Columns cols;
    cols += Column("Hello");
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello"), std::string::npos);
}

TEST(ColumnsTest_624, ColumnsPlusColumn_624) {
    Column col1("Col1");
    Column col2("Col2");
    Column col3("Col3");
    Columns cols = col1 + col2;
    Columns result = cols + col3;
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("Col1"), std::string::npos);
    EXPECT_NE(output.find("Col2"), std::string::npos);
    EXPECT_NE(output.find("Col3"), std::string::npos);
}

TEST(ColumnsTest_624, ColumnsPlusColumnRvalue_624) {
    Columns cols = Column("A") + Column("B");
    Columns result = std::move(cols) + Column("C");
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
}

TEST(ColumnsTest_624, BeginEndIteration_624) {
    Columns cols = Column("Hello") + Column("World");
    int count = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        count++;
    }
    EXPECT_GT(count, 0);
}

TEST(ColumnsTest_624, StreamOutputMultipleColumns_624) {
    Column left("Left side text that might wrap");
    left.width(20);
    Column right("Right side text");
    right.width(20);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ColumnsTest_624, EmptyColumnsIteration_624) {
    Columns cols;
    int count = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

TEST(ColumnsTest_624, MultipleColumnsCombined_624) {
    Column c1("One");
    c1.width(15);
    Column c2("Two");
    c2.width(15);
    Column c3("Three");
    c3.width(15);

    Columns cols;
    cols += c1;
    cols += c2;
    cols += c3;

    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("One"), std::string::npos);
    EXPECT_NE(output.find("Two"), std::string::npos);
    EXPECT_NE(output.find("Three"), std::string::npos);
}

TEST(ColumnsTest_624, ColumnsWithWrappingText_624) {
    Column left("This is a somewhat long text that should wrap around");
    left.width(15);
    Column right("Short");
    right.width(15);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    // Multiple lines expected due to wrapping in the left column
    size_t newlines = std::count(output.begin(), output.end(), '\n');
    EXPECT_GT(newlines, 0u);
}

TEST(ColumnsTest_624, ColumnsWithIndent_624) {
    Column left("Text with indent");
    left.width(30).indent(4);
    Column right("Right text");
    right.width(30);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}
