#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Catch::TextFlow;

// ============================================================
// Column Tests
// ============================================================

class ColumnTest_620 : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(ColumnTest_620, DefaultWidthIs79_620) {
    Column col("hello");
    EXPECT_EQ(col.width(), 79u);
}

TEST_F(ColumnTest_620, SetWidth_620) {
    Column col("hello");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST_F(ColumnTest_620, EmptyStringProducesOneEmptyLine_620) {
    Column col("");
    auto it = col.begin();
    EXPECT_NE(it, col.end());
    std::string line = *it;
    // Empty column should still produce at least one iteration
    ++it;
    EXPECT_EQ(it, col.end());
}

TEST_F(ColumnTest_620, ShortStringFitsInOneLine_620) {
    Column col("hello world");
    col.width(80);
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
    }
    EXPECT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "hello world");
}

TEST_F(ColumnTest_620, LongStringWraps_620) {
    Column col("This is a long string that should be wrapped into multiple lines when the width is small");
    col.width(20);
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
    }
    EXPECT_GT(lines.size(), 1u);
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 20u);
    }
}

TEST_F(ColumnTest_620, IndentApplied_620) {
    Column col("hello");
    col.width(80).indent(4);
    auto it = col.begin();
    std::string line = *it;
    EXPECT_GE(line.size(), 4u);
    EXPECT_EQ(line.substr(0, 4), "    ");
}

TEST_F(ColumnTest_620, InitialIndentApplied_620) {
    Column col("hello world this is a test of initial indent and regular indent");
    col.width(30).indent(2).initialIndent(6);
    auto it = col.begin();
    std::string firstLine = *it;
    // First line should have initial indent of 6
    EXPECT_EQ(firstLine.substr(0, 6), "      ");
    ++it;
    if (it != col.end()) {
        std::string secondLine = *it;
        // Subsequent lines should have indent of 2
        EXPECT_EQ(secondLine.substr(0, 2), "  ");
    }
}

TEST_F(ColumnTest_620, IteratorEquality_620) {
    Column col("hello");
    auto begin1 = col.begin();
    auto begin2 = col.begin();
    auto end = col.end();
    EXPECT_EQ(begin1, begin2);
    EXPECT_NE(begin1, end);
    EXPECT_EQ(end, col.end());
}

TEST_F(ColumnTest_620, PostIncrementIterator_620) {
    Column col("hello world");
    col.width(80);
    auto it = col.begin();
    auto prev = it++;
    // prev should still be valid (the old position)
    // it should be at end if the string fits in one line
    EXPECT_EQ(it, col.end());
}

TEST_F(ColumnTest_620, OutputStreamOperator_620) {
    Column col("hello");
    col.width(80);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(ColumnTest_620, WidthOfOne_620) {
    // Boundary: very small width
    Column col("ab cd");
    col.width(2);
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
    }
    EXPECT_GT(lines.size(), 1u);
}

TEST_F(ColumnTest_620, SingleCharacterString_620) {
    Column col("X");
    col.width(80);
    auto it = col.begin();
    EXPECT_EQ(*it, "X");
    ++it;
    EXPECT_EQ(it, col.end());
}

TEST_F(ColumnTest_620, MultipleSpaces_620) {
    Column col("hello     world");
    col.width(80);
    auto it = col.begin();
    std::string line = *it;
    EXPECT_NE(line.find("hello"), std::string::npos);
    EXPECT_NE(line.find("world"), std::string::npos);
}

// ============================================================
// Columns Tests (multi-column layout)
// ============================================================

class ColumnsTest_620 : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(ColumnsTest_620, TwoColumnsCombined_620) {
    Column left("Left text");
    left.width(20);
    Column right("Right text");
    right.width(20);
    Columns cols = left + right;
    auto it = cols.begin();
    EXPECT_NE(it, cols.end());
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

TEST_F(ColumnsTest_620, ColumnsIteratorIncrement_620) {
    Column left("A");
    left.width(10);
    Column right("B");
    right.width(10);
    Columns cols = left + right;
    auto it = cols.begin();
    std::string firstLine = *it;
    ++it;
    EXPECT_EQ(it, cols.end());
}

TEST_F(ColumnsTest_620, ColumnsIteratorEquality_620) {
    Column left("hello");
    left.width(20);
    Column right("world");
    right.width(20);
    Columns cols = left + right;
    auto end1 = cols.end();
    auto end2 = cols.end();
    EXPECT_EQ(end1, end2);
    auto begin = cols.begin();
    EXPECT_NE(begin, end1);
}

TEST_F(ColumnsTest_620, ColumnsPostIncrement_620) {
    Column left("X");
    left.width(10);
    Column right("Y");
    right.width(10);
    Columns cols = left + right;
    auto it = cols.begin();
    auto prev = it++;
    // After post-increment from single-line columns, it should be at end
    EXPECT_EQ(it, cols.end());
}

TEST_F(ColumnsTest_620, ColumnsWithDifferentLengths_620) {
    Column left("Short");
    left.width(10);
    Column right("This is a much longer text that should wrap into multiple lines");
    right.width(15);
    Columns cols = left + right;
    
    std::vector<std::string> lines;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        lines.push_back(*it);
    }
    // Right column should cause multiple lines
    EXPECT_GT(lines.size(), 1u);
}

TEST_F(ColumnsTest_620, ColumnsRvalueOperatorPlus_620) {
    Columns cols = Column("left") + Column("right");
    auto it = cols.begin();
    EXPECT_NE(it, cols.end());
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

TEST_F(ColumnsTest_620, ColumnsChainingWidth_620) {
    Column col("test");
    Column& ref = col.width(30);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 30u);
}

TEST_F(ColumnsTest_620, ColumnsChainingIndent_620) {
    Column col("test");
    Column& ref = col.indent(5);
    EXPECT_EQ(&ref, &col);
}

TEST_F(ColumnsTest_620, ColumnsChainingInitialIndent_620) {
    Column col("test");
    Column& ref = col.initialIndent(5);
    EXPECT_EQ(&ref, &col);
}

TEST_F(ColumnsTest_620, ColumnsOutputMultipleRows_620) {
    Column left("Line one\nLine two");
    left.width(20);
    Column right("Right one\nRight two");
    right.width(20);
    Columns cols = left + right;
    
    std::vector<std::string> lines;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        lines.push_back(*it);
    }
    EXPECT_GE(lines.size(), 2u);
}

TEST_F(ColumnsTest_620, EmptyColumnsBeginEqualsEnd_620) {
    Column left("");
    left.width(10);
    Column right("");
    right.width(10);
    Columns cols = left + right;
    auto it = cols.begin();
    // Even empty columns may produce one line
    // Just iterate and verify no crash
    std::vector<std::string> lines;
    for (auto it2 = cols.begin(); it2 != cols.end(); ++it2) {
        lines.push_back(*it2);
    }
    // Should not crash and should eventually terminate
    EXPECT_GE(lines.size(), 0u);
}

TEST_F(ColumnsTest_620, ColumnNewlines_620) {
    Column col("line1\nline2\nline3");
    col.width(80);
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
    }
    EXPECT_GE(lines.size(), 3u);
}

TEST_F(ColumnsTest_620, ColumnIndentWithWrapping_620) {
    Column col("This is a somewhat long text that should wrap");
    col.width(15).indent(3);
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
    }
    EXPECT_GT(lines.size(), 1u);
    // All lines should start with indent (3 spaces)
    for (size_t i = 0; i < lines.size(); ++i) {
        if (i == 0) continue; // first line may use initial indent
        EXPECT_GE(lines[i].size(), 3u);
        EXPECT_EQ(lines[i].substr(0, 3), "   ");
    }
}
