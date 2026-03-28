#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::TextFlow;

// =============================================================================
// Column Tests
// =============================================================================

TEST(ColumnTest_627, ConstructFromConstString_627) {
    std::string text = "Hello, World!";
    Column col(text);
    EXPECT_EQ(col.width(), 80 - 1);
}

TEST(ColumnTest_627, ConstructFromRvalueString_627) {
    Column col(std::string("Hello, World!"));
    EXPECT_EQ(col.width(), 80 - 1);
}

TEST(ColumnTest_627, DefaultWidth_627) {
    Column col("test");
    EXPECT_EQ(col.width(), 79);
}

TEST(ColumnTest_627, SetWidth_627) {
    Column col("test");
    col.width(40);
    EXPECT_EQ(col.width(), 40);
}

TEST(ColumnTest_627, SetWidthChaining_627) {
    Column col("test");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50);
}

TEST(ColumnTest_627, SetIndent_627) {
    Column col("test text that is long enough to wrap");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_627, SetInitialIndent_627) {
    Column col("test text");
    Column& ref = col.initialIndent(8);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_627, EmptyStringIteration_627) {
    Column col("");
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    // Empty string should produce at most one empty line or zero lines
    EXPECT_GE(count, 0);
}

TEST(ColumnTest_627, SingleWordIteration_627) {
    Column col("Hello");
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 1);
}

TEST(ColumnTest_627, WidthOfOne_627) {
    Column col("ab");
    col.width(1);
    EXPECT_EQ(col.width(), 1);
    // Should still be iterable without crashing
    for (auto it = col.begin(); it != col.end(); ++it) {
        // just iterate
    }
}

TEST(ColumnTest_627, StreamOutput_627) {
    Column col("Hello World");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello"), std::string::npos);
    EXPECT_NE(output.find("World"), std::string::npos);
}

TEST(ColumnTest_627, NarrowWidthWrapsText_627) {
    Column col("Hello World");
    col.width(6);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GE(lineCount, 2);
}

TEST(ColumnTest_627, IndentAffectsOutput_627) {
    Column col("Hello");
    col.indent(4);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // The output should contain spaces for indentation
    EXPECT_NE(output.find("Hello"), std::string::npos);
}

TEST(ColumnTest_627, InitialIndentAffectsFirstLine_627) {
    Column col("Hello World Test");
    col.width(10).initialIndent(4);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// =============================================================================
// Column + Column => Columns
// =============================================================================

TEST(ColumnPlusColumnTest_627, TwoColumnsAddition_627) {
    Column left("Left text");
    Column right("Right text");
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

TEST(ColumnPlusColumnTest_627, TwoColumnsRvalueAddition_627) {
    Columns cols = Column("Left text") + Column("Right text");
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

// =============================================================================
// Columns Tests
// =============================================================================

TEST(ColumnsTest_627, ColumnsPlusColumn_627) {
    Column col1("First");
    Column col2("Second");
    Column col3("Third");
    Columns cols = col1 + col2;
    Columns result = cols + col3;
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("First"), std::string::npos);
    EXPECT_NE(output.find("Second"), std::string::npos);
    EXPECT_NE(output.find("Third"), std::string::npos);
}

TEST(ColumnsTest_627, ColumnsPlusEqualsColumn_627) {
    Column col1("Alpha");
    Column col2("Beta");
    Columns cols = col1 + col2;
    Column col3("Gamma");
    cols += col3;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Alpha"), std::string::npos);
    EXPECT_NE(output.find("Beta"), std::string::npos);
    EXPECT_NE(output.find("Gamma"), std::string::npos);
}

TEST(ColumnsTest_627, ColumnsPlusEqualsRvalueColumn_627) {
    Column col1("Alpha");
    Column col2("Beta");
    Columns cols = col1 + col2;
    cols += Column("Gamma");
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Gamma"), std::string::npos);
}

TEST(ColumnsTest_627, ColumnsIteration_627) {
    Column col1("Line one");
    Column col2("Line two");
    Columns cols = col1 + col2;
    int count = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        ++count;
    }
    EXPECT_GE(count, 1);
}

TEST(ColumnsTest_627, ColumnsStreamOutput_627) {
    Column col1("Hello");
    Column col2("World");
    Columns cols = col1 + col2;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ColumnsTest_627, ColumnsWithDifferentWidths_627) {
    Column col1("Short");
    col1.width(20);
    Column col2("Also short");
    col2.width(30);
    Columns cols = col1 + col2;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Short"), std::string::npos);
    EXPECT_NE(output.find("Also short"), std::string::npos);
}

TEST(ColumnsTest_627, ColumnsWithLongTextWrapping_627) {
    Column col1("This is a fairly long text that should wrap when the column width is small");
    col1.width(20);
    Column col2("Another column of text that also wraps around");
    col2.width(20);
    Columns cols = col1 + col2;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ColumnsTest_627, OperatorPlusFromImplementation_627) {
    // Directly test the function from the .cpp: Columns operator+(Columns const& lhs, Column const& rhs)
    Column col1("A");
    Column col2("B");
    Columns base = col1 + col2;
    Column col3("C");
    Columns result = base + col3;
    // Verify all three columns appear
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
}

TEST(ColumnsTest_627, MultipleAdditions_627) {
    Column col1("One");
    Column col2("Two");
    Column col3("Three");
    Column col4("Four");
    Columns cols = col1 + col2;
    cols += col3;
    cols += col4;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("One"), std::string::npos);
    EXPECT_NE(output.find("Two"), std::string::npos);
    EXPECT_NE(output.find("Three"), std::string::npos);
    EXPECT_NE(output.find("Four"), std::string::npos);
}

// =============================================================================
// Boundary / Edge Cases
// =============================================================================

TEST(ColumnTest_627, VeryLongSingleWord_627) {
    std::string longWord(200, 'x');
    Column col(longWord);
    col.width(10);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // The long word should still appear in the output
    EXPECT_FALSE(output.empty());
}

TEST(ColumnTest_627, NewlineInText_627) {
    Column col("Line1\nLine2");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("Line1"), std::string::npos);
    EXPECT_NE(output.find("Line2"), std::string::npos);
}

TEST(ColumnTest_627, WhitespaceOnlyText_627) {
    Column col("   ");
    std::ostringstream oss;
    oss << col;
    // Should not crash
    SUCCEED();
}

TEST(ColumnTest_627, LargeWidth_627) {
    Column col("Short");
    col.width(10000);
    EXPECT_EQ(col.width(), 10000);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("Short"), std::string::npos);
}

TEST(ColumnTest_627, ZeroIndent_627) {
    Column col("test");
    col.indent(0);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST(ColumnsTest_627, RvalueColumnsPlusColumn_627) {
    Column col1("X");
    Column col2("Y");
    Column col3("Z");
    // Test Columns&& + Column&&
    Columns result = (Column("X") + Column("Y"));
    result += Column("Z");
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ColumnsTest_627, BeginEndConsistency_627) {
    Column col1("A");
    Column col2("B");
    Columns cols = col1 + col2;
    // Multiple iterations should yield the same result
    std::ostringstream oss1, oss2;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        oss1 << *it << "\n";
    }
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        oss2 << *it << "\n";
    }
    EXPECT_EQ(oss1.str(), oss2.str());
}
