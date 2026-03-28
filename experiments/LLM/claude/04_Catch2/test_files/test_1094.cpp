#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace Catch::TextFlow;

// ============================================================
// Column Tests
// ============================================================

TEST(ColumnTest_1094, DefaultConstruction_1094) {
    Column col("Hello World");
    // Default width should be 80 - 1 = 79
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_1094, SetWidth_1094) {
    Column col("Hello World");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST(ColumnTest_1094, SetIndent_1094) {
    Column col("Hello World");
    col.indent(4);
    // indent is set; we verify indirectly through output
    std::ostringstream oss;
    oss << col;
    // The output should have indentation
    EXPECT_FALSE(oss.str().empty());
}

TEST(ColumnTest_1094, SetInitialIndent_1094) {
    Column col("Hello World");
    col.initialIndent(8);
    std::ostringstream oss;
    oss << col;
    EXPECT_FALSE(oss.str().empty());
}

TEST(ColumnTest_1094, EmptyString_1094) {
    Column col("");
    std::ostringstream oss;
    oss << col;
    // Empty string column should produce some output (possibly just newline or empty)
    // Just ensure no crash
    SUCCEED();
}

TEST(ColumnTest_1094, StreamOutput_1094) {
    Column col("Hello");
    std::ostringstream oss;
    oss << col;
    EXPECT_NE(oss.str().find("Hello"), std::string::npos);
}

TEST(ColumnTest_1094, LongTextWrapping_1094) {
    std::string longText = "This is a very long text that should be wrapped because it exceeds the column width significantly and needs multiple lines to display properly.";
    Column col(longText);
    col.width(20);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    // The result should contain newlines since text is longer than width
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST(ColumnTest_1094, BeginEndIterators_1094) {
    Column col("Hello World");
    auto it = col.begin();
    auto end = col.end();
    // Should be able to iterate
    EXPECT_NE(it, end);
}

TEST(ColumnTest_1094, WidthOfOne_1094) {
    Column col("AB");
    col.width(1);
    std::ostringstream oss;
    oss << col;
    // Even with width 1, should not crash
    EXPECT_FALSE(oss.str().empty());
}

TEST(ColumnTest_1094, MoveConstruction_1094) {
    std::string text = "Hello World";
    Column col(std::move(text));
    EXPECT_EQ(col.width(), 79u);
    std::ostringstream oss;
    oss << col;
    EXPECT_NE(oss.str().find("Hello"), std::string::npos);
}

// ============================================================
// Column + Column => Columns Tests
// ============================================================

TEST(ColumnsTest_1094, TwoColumnAddition_1094) {
    Column left("Left column text");
    Column right("Right column text");
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Left"), std::string::npos);
    EXPECT_NE(result.find("Right"), std::string::npos);
}

TEST(ColumnsTest_1094, TwoColumnMoveAddition_1094) {
    Columns cols = Column("Left text") + Column("Right text");
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Left"), std::string::npos);
    EXPECT_NE(result.find("Right"), std::string::npos);
}

TEST(ColumnsTest_1094, ColumnsBeginEnd_1094) {
    Column left("Left");
    Column right("Right");
    Columns cols = left + right;
    auto it = cols.begin();
    auto end = cols.end();
    EXPECT_NE(it, end);
}

TEST(ColumnsTest_1094, ColumnsPlusColumn_1094) {
    Column c1("First");
    Column c2("Second");
    Column c3("Third");
    Columns cols = c1 + c2;
    Columns result = cols + c3;
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("First"), std::string::npos);
    EXPECT_NE(output.find("Second"), std::string::npos);
    EXPECT_NE(output.find("Third"), std::string::npos);
}

TEST(ColumnsTest_1094, ColumnsPlusEqualColumn_1094) {
    Column c1("First");
    Column c2("Second");
    Columns cols = c1 + c2;
    Column c3("Third");
    cols += c3;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Third"), std::string::npos);
}

TEST(ColumnsTest_1094, ColumnsPlusEqualMoveColumn_1094) {
    Column c1("First");
    Column c2("Second");
    Columns cols = c1 + c2;
    cols += Column("Third");
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Third"), std::string::npos);
}

TEST(ColumnsTest_1094, MovedColumnsPlusColumn_1094) {
    Columns cols = Column("First") + Column("Second");
    Columns result = std::move(cols) + Column("Third");
    std::ostringstream oss;
    oss << result;
    std::string output = oss.str();
    EXPECT_NE(output.find("First"), std::string::npos);
    EXPECT_NE(output.find("Third"), std::string::npos);
}

// ============================================================
// Columns::iterator Tests
// ============================================================

TEST(ColumnsIteratorTest_1094, DereferenceOperator_1094) {
    Column left("Hello");
    Column right("World");
    Columns cols = left + right;
    auto it = cols.begin();
    std::string line = *it;
    // Should contain text from both columns
    EXPECT_FALSE(line.empty());
}

TEST(ColumnsIteratorTest_1094, IncrementOperator_1094) {
    Column left("Hello");
    Column right("World");
    Columns cols = left + right;
    auto it = cols.begin();
    auto end = cols.end();
    // Pre-increment
    if (it != end) {
        ++it;
    }
    // Should not crash
    SUCCEED();
}

TEST(ColumnsIteratorTest_1094, PostIncrementOperator_1094) {
    Column left("Hello");
    Column right("World");
    Columns cols = left + right;
    auto it = cols.begin();
    auto end = cols.end();
    if (it != end) {
        auto prev = it++;
        // prev should be different from it (if there are multiple lines) or same as end
        SUCCEED();
    }
}

TEST(ColumnsIteratorTest_1094, EqualityOperator_1094) {
    Column col("Hello");
    Columns cols = col + Column("World");
    auto it1 = cols.begin();
    auto it2 = cols.begin();
    // Two begin iterators from the same Columns
    EXPECT_EQ(it1, it2);
}

TEST(ColumnsIteratorTest_1094, InequalityOperator_1094) {
    Column col("Hello");
    Columns cols = col + Column("World");
    auto begin = cols.begin();
    auto end = cols.end();
    // begin should not equal end for non-empty columns
    EXPECT_NE(begin, end);
}

TEST(ColumnsIteratorTest_1094, FullIteration_1094) {
    std::string longText = "This is some long text that will wrap across multiple lines in the column.";
    Column left(longText);
    left.width(20);
    Column right("Short");
    right.width(20);
    Columns cols = left + right;

    int lineCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        std::string line = *it;
        EXPECT_FALSE(line.empty());
        lineCount++;
        // Safety: prevent infinite loop
        if (lineCount > 100) break;
    }
    EXPECT_GT(lineCount, 0);
}

TEST(ColumnsIteratorTest_1094, EmptyColumns_1094) {
    Column left("");
    Column right("");
    Columns cols = left + right;
    auto begin = cols.begin();
    auto end = cols.end();
    // Even with empty strings, iterator behavior should be defined
    // Just ensure no crash
    int count = 0;
    for (auto it = begin; it != end; ++it) {
        count++;
        if (count > 100) break;
    }
    SUCCEED();
}

// ============================================================
// Column width and indent interaction Tests
// ============================================================

TEST(ColumnFormattingTest_1094, IndentAffectsOutput_1094) {
    Column col1("Hello World");
    col1.width(40);

    Column col2("Hello World");
    col2.width(40);
    col2.indent(4);

    std::ostringstream oss1, oss2;
    oss1 << col1;
    oss2 << col2;

    // Indented column should have more leading spaces
    EXPECT_NE(oss1.str(), oss2.str());
}

TEST(ColumnFormattingTest_1094, InitialIndentDiffersFromIndent_1094) {
    Column col1("Hello World this is a longer text to force wrapping on multiple lines");
    col1.width(30);
    col1.indent(2);

    Column col2("Hello World this is a longer text to force wrapping on multiple lines");
    col2.width(30);
    col2.indent(2);
    col2.initialIndent(6);

    std::ostringstream oss1, oss2;
    oss1 << col1;
    oss2 << col2;

    // Different initial indent should produce different output
    EXPECT_NE(oss1.str(), oss2.str());
}

TEST(ColumnFormattingTest_1094, NarrowWidthCausesWrapping_1094) {
    Column col("Hello World");
    col.width(5);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    // Should have newlines due to wrapping
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST(ColumnsTest_1094, StreamOutputConsistency_1094) {
    Column left("Left");
    left.width(20);
    Column right("Right");
    right.width(20);
    Columns cols = left + right;

    std::ostringstream oss1, oss2;
    oss1 << cols;
    oss2 << cols;
    // Same output both times
    EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(ColumnsTest_1094, ThreeColumns_1094) {
    Column c1("First column");
    c1.width(20);
    Column c2("Second column");
    c2.width(20);
    Column c3("Third column");
    c3.width(20);

    Columns cols = c1 + c2;
    cols += c3;

    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("First"), std::string::npos);
    EXPECT_NE(result.find("Second"), std::string::npos);
    EXPECT_NE(result.find("Third"), std::string::npos);
}

TEST(ColumnTest_1094, ChainedWidthAndIndent_1094) {
    Column col("Test text");
    col.width(40).indent(4).initialIndent(8);
    EXPECT_EQ(col.width(), 40u);
    std::ostringstream oss;
    oss << col;
    EXPECT_FALSE(oss.str().empty());
}

TEST(ColumnsIteratorTest_1094, SingleColumnIteration_1094) {
    // Create a Columns with just one column by adding two
    Column c1("Line one text here");
    c1.width(10);
    Column c2("Another");
    c2.width(10);
    Columns cols = c1 + c2;

    std::vector<std::string> lines;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        lines.push_back(*it);
        if (lines.size() > 50) break;
    }
    EXPECT_GT(lines.size(), 0u);
}

TEST(ColumnsIteratorTest_1094, IteratorEndEquality_1094) {
    Column c1("A");
    Column c2("B");
    Columns cols = c1 + c2;
    auto end1 = cols.end();
    auto end2 = cols.end();
    EXPECT_EQ(end1, end2);
}
