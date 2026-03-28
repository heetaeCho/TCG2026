#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::TextFlow;

// ============================================================
// Column Tests
// ============================================================

TEST(ColumnTest_625, ConstructFromConstString_625) {
    std::string text = "Hello World";
    Column col(text);
    EXPECT_EQ(col.width(), 80 - 1);
}

TEST(ColumnTest_625, ConstructFromRValueString_625) {
    Column col(std::string("Hello World"));
    EXPECT_EQ(col.width(), 80 - 1);
}

TEST(ColumnTest_625, SetWidth_625) {
    Column col("Hello");
    col.width(40);
    EXPECT_EQ(col.width(), 40);
}

TEST(ColumnTest_625, DefaultWidth_625) {
    Column col("test");
    EXPECT_EQ(col.width(), 79);
}

TEST(ColumnTest_625, SetIndent_625) {
    Column col("Hello World");
    Column& ref = col.indent(4);
    // indent returns a reference to the same column (chaining)
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_625, SetInitialIndent_625) {
    Column col("Hello World");
    Column& ref = col.initialIndent(8);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_625, WidthChaining_625) {
    Column col("Hello");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50);
}

TEST(ColumnTest_625, BeginEndIterator_625) {
    Column col("Hello");
    auto it = col.begin();
    auto endIt = col.end();
    // There should be at least one line for non-empty text
    EXPECT_NE(it, endIt);
}

TEST(ColumnTest_625, EmptyString_625) {
    Column col("");
    // Even an empty string should be iterable (may produce one empty line or none)
    // Just ensure begin/end don't crash
    auto it = col.begin();
    auto endIt = col.end();
    (void)it;
    (void)endIt;
}

TEST(ColumnTest_625, StreamOutput_625) {
    Column col("Hello World");
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

TEST(ColumnTest_625, LongTextWraps_625) {
    std::string longText = "This is a very long text that should be wrapped across multiple lines when the width is set to a small value";
    Column col(longText);
    col.width(20);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++lineCount;
    }
    EXPECT_GT(lineCount, 1);
}

TEST(ColumnTest_625, WidthOfOne_625) {
    Column col("AB");
    col.width(1);
    // Should still be iterable without crashing
    std::ostringstream oss;
    oss << col;
    EXPECT_FALSE(oss.str().empty());
}

TEST(ColumnTest_625, WidthSetToLargeValue_625) {
    Column col("Short");
    col.width(1000);
    EXPECT_EQ(col.width(), 1000);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++lineCount;
    }
    EXPECT_EQ(lineCount, 1);
}

TEST(ColumnTest_625, IndentReducesAvailableWidth_625) {
    std::string text = "Hello World Test";
    Column col1(text);
    col1.width(20);

    Column col2(text);
    col2.width(20);
    col2.indent(10);

    std::ostringstream oss1, oss2;
    oss1 << col1;
    oss2 << col2;
    // With indent, the output should be different (indented lines)
    EXPECT_NE(oss1.str(), oss2.str());
}

// ============================================================
// Columns Tests
// ============================================================

TEST(ColumnsTest_625, AddColumnWithPlusEqualsOperator_625) {
    Column col1("Left column text");
    col1.width(30);
    Column col2("Right column text");
    col2.width(30);

    Columns cols;
    cols += col1;
    cols += col2;

    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST(ColumnsTest_625, ColumnPlusColumn_625) {
    Column col1("Left");
    col1.width(20);
    Column col2("Right");
    col2.width(20);

    Columns cols = col1 + col2;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Left"), std::string::npos);
    EXPECT_NE(result.find("Right"), std::string::npos);
}

TEST(ColumnsTest_625, ColumnPlusColumnRValue_625) {
    Columns cols = Column("Left") + Column("Right");
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST(ColumnsTest_625, ColumnsPlusColumn_625) {
    Column col1("First");
    col1.width(20);
    Column col2("Second");
    col2.width(20);
    Column col3("Third");
    col3.width(20);

    Columns cols = col1 + col2;
    Columns result = cols + col3;

    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ColumnsTest_625, ColumnsRValuePlusColumn_625) {
    Column col1("First");
    col1.width(20);
    Column col2("Second");
    col2.width(20);
    Column col3("Third");
    col3.width(20);

    Columns result = (col1 + col2) + Column("Third");

    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ColumnsTest_625, BeginEndIterator_625) {
    Column col1("Left");
    col1.width(20);
    Column col2("Right");
    col2.width(20);

    Columns cols = col1 + col2;
    auto it = cols.begin();
    auto endIt = cols.end();
    EXPECT_NE(it, endIt);
}

TEST(ColumnsTest_625, StreamOutputContainsBothColumns_625) {
    Column col1("AAAA");
    col1.width(20);
    Column col2("BBBB");
    col2.width(20);

    Columns cols = col1 + col2;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("AAAA"), std::string::npos);
    EXPECT_NE(result.find("BBBB"), std::string::npos);
}

TEST(ColumnsTest_625, MultipleColumnsWithDifferentLengths_625) {
    std::string shortText = "Short";
    std::string longText = "This is a much longer text that will span multiple lines in the column layout";

    Column col1(shortText);
    col1.width(20);
    Column col2(longText);
    col2.width(30);

    Columns cols = col1 + col2;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST(ColumnsTest_625, PlusEqualsReturnsSameObject_625) {
    Columns cols;
    Column col("Test");
    Columns& ref = (cols += col);
    EXPECT_EQ(&ref, &cols);
}

TEST(ColumnsTest_625, SingleColumnInColumns_625) {
    Columns cols;
    Column col("Only column");
    col.width(40);
    cols += col;

    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Only column"), std::string::npos);
}

TEST(ColumnsTest_625, EmptyColumnsText_625) {
    Column col1("");
    col1.width(20);
    Column col2("");
    col2.width(20);

    Columns cols = col1 + col2;
    std::ostringstream oss;
    oss << cols;
    // Should not crash; output may be empty or whitespace
    (void)oss.str();
}

TEST(ColumnsTest_625, ThreeColumnsAddition_625) {
    Column col1("Col1");
    col1.width(15);
    Column col2("Col2");
    col2.width(15);
    Column col3("Col3");
    col3.width(15);

    Columns cols = col1 + col2;
    cols += col3;

    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Col1"), std::string::npos);
    EXPECT_NE(result.find("Col2"), std::string::npos);
    EXPECT_NE(result.find("Col3"), std::string::npos);
}
