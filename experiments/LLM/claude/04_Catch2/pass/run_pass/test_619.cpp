#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <vector>

using namespace Catch::TextFlow;

// ============================================================
// Column Tests
// ============================================================

TEST(ColumnTest_619, DefaultWidthIs79_619) {
    Column col("Hello");
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_619, SetWidth_619) {
    Column col("Hello");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST(ColumnTest_619, SetWidthChaining_619) {
    Column col("Hello");
    auto& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50u);
}

TEST(ColumnTest_619, EmptyString_619) {
    Column col("");
    auto it = col.begin();
    // An empty column might still produce one empty line or none
    // We just verify it doesn't crash and begin/end relationship holds
    size_t count = 0;
    for (auto i = col.begin(); i != col.end(); ++i) {
        count++;
        // Shouldn't loop forever
        if (count > 100) break;
    }
    EXPECT_LE(count, 100u);
}

TEST(ColumnTest_619, ShortStringFitsInOneLine_619) {
    Column col("Hello World");
    col.width(80);
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string line = *it;
    EXPECT_EQ(line, "Hello World");
    ++it;
    EXPECT_EQ(it, col.end());
}

TEST(ColumnTest_619, LongStringWraps_619) {
    Column col("This is a long string that should wrap around because the width is set very small");
    col.width(20);
    size_t lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        // Each line should not exceed the width (excluding possible indent)
        lineCount++;
        if (lineCount > 100) break; // safety
    }
    EXPECT_GT(lineCount, 1u);
    EXPECT_LE(lineCount, 100u);
}

TEST(ColumnTest_619, IteratorEquality_619) {
    Column col("Test");
    auto b1 = col.begin();
    auto b2 = col.begin();
    EXPECT_EQ(b1, b2);
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

TEST(ColumnTest_619, IteratorEndEquality_619) {
    Column col("Test");
    auto e1 = col.end();
    auto e2 = col.end();
    EXPECT_EQ(e1, e2);
}

TEST(ColumnTest_619, IteratorBeginNotEqualEnd_619) {
    Column col("Test");
    EXPECT_NE(col.begin(), col.end());
}

TEST(ColumnTest_619, PostIncrementIterator_619) {
    Column col("Hello");
    col.width(80);
    auto it = col.begin();
    auto old = it++;
    // old should have been valid
    std::string val = *old;
    EXPECT_FALSE(val.empty());
}

TEST(ColumnTest_619, IndentAddsSpaces_619) {
    Column col("Hello");
    col.width(80).indent(4);
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string line = *it;
    // The line should start with spaces due to indent
    EXPECT_GE(line.size(), 4u);
    EXPECT_EQ(line.substr(0, 4), "    ");
}

TEST(ColumnTest_619, InitialIndentDiffersFromIndent_619) {
    Column col("First line and then second line that might wrap");
    col.width(30).indent(4).initialIndent(8);
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string firstLine = *it;
    // First line should have initial indent of 8
    EXPECT_GE(firstLine.size(), 8u);
    EXPECT_EQ(firstLine.substr(0, 8), "        ");
}

TEST(ColumnTest_619, StreamOutput_619) {
    Column col("Hello World");
    col.width(80);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

TEST(ColumnTest_619, MoveConstruction_619) {
    std::string text = "Moved text";
    Column col(std::move(text));
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string line = *it;
    EXPECT_NE(line.find("Moved text"), std::string::npos);
}

TEST(ColumnTest_619, VeryNarrowWidth_619) {
    Column col("Hello");
    col.width(1);
    size_t count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        count++;
        if (count > 1000) break;
    }
    // Should produce at least as many lines as characters (each line holds ~1 char)
    EXPECT_GE(count, 1u);
    EXPECT_LE(count, 1000u);
}

// ============================================================
// Columns Tests (multiple columns side by side)
// ============================================================

TEST(ColumnsTest_619, TwoColumnsWithPlusOperator_619) {
    Column c1("Left");
    c1.width(20);
    Column c2("Right");
    c2.width(20);
    Columns cols = c1 + c2;
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    std::string row = *it;
    // Row should contain both "Left" and "Right"
    EXPECT_NE(row.find("Left"), std::string::npos);
    EXPECT_NE(row.find("Right"), std::string::npos);
}

TEST(ColumnsTest_619, TwoColumnsIteratorTraversal_619) {
    Column c1("Hello");
    c1.width(20);
    Column c2("World");
    c2.width(20);
    Columns cols = c1 + c2;
    size_t rowCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        rowCount++;
        if (rowCount > 100) break;
    }
    EXPECT_GE(rowCount, 1u);
    EXPECT_LE(rowCount, 100u);
}

TEST(ColumnsTest_619, TwoColumnsDifferentLengths_619) {
    Column c1("Short");
    c1.width(20);
    Column c2("This is a much longer text that will wrap across multiple lines in the second column");
    c2.width(20);
    Columns cols = c1 + c2;
    size_t rowCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        std::string row = *it;
        rowCount++;
        if (rowCount > 100) break;
    }
    // The second column wraps, so we should have multiple rows
    EXPECT_GT(rowCount, 1u);
}

TEST(ColumnsTest_619, ColumnsIteratorEquality_619) {
    Column c1("A");
    c1.width(20);
    Column c2("B");
    c2.width(20);
    Columns cols = c1 + c2;
    auto b1 = cols.begin();
    auto b2 = cols.begin();
    EXPECT_EQ(b1, b2);
    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 != b2);
}

TEST(ColumnsTest_619, ColumnsIteratorEndEquality_619) {
    Column c1("A");
    c1.width(20);
    Column c2("B");
    c2.width(20);
    Columns cols = c1 + c2;
    auto e1 = cols.end();
    auto e2 = cols.end();
    EXPECT_EQ(e1, e2);
}

TEST(ColumnsTest_619, ColumnsPostIncrement_619) {
    Column c1("Hello");
    c1.width(20);
    Column c2("World");
    c2.width(20);
    Columns cols = c1 + c2;
    auto it = cols.begin();
    auto old = it++;
    std::string row = *old;
    EXPECT_FALSE(row.empty());
}

TEST(ColumnsTest_619, ColumnsRowPaddingWhenFirstColumnExhausted_619) {
    Column c1("A");
    c1.width(10);
    Column c2("Line1 Line2 Line3");
    c2.width(10);
    Columns cols = c1 + c2;
    size_t rowCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        std::string row = *it;
        // When first column is exhausted, padding should fill its width
        // The row should still be properly formatted
        rowCount++;
        if (rowCount > 50) break;
    }
    EXPECT_GE(rowCount, 1u);
}

TEST(ColumnsTest_619, MoveColumnsOperator_619) {
    Column c1("Left");
    c1.width(20);
    Column c2("Right");
    c2.width(20);
    Columns cols = std::move(c1) + std::move(c2);
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    std::string row = *it;
    EXPECT_NE(row.find("Left"), std::string::npos);
    EXPECT_NE(row.find("Right"), std::string::npos);
}

TEST(ColumnsTest_619, ColumnsRowWidthRespected_619) {
    Column c1("AAAA");
    c1.width(10);
    Column c2("BBBB");
    c2.width(10);
    Columns cols = c1 + c2;
    auto it = cols.begin();
    ASSERT_NE(it, cols.end());
    std::string row = *it;
    // The row should be padded so that columns line up
    // First column width is 10, second is 10, so total row length ~20
    // "AAAA" takes 4 chars, then 6 spaces padding, then "BBBB"
    EXPECT_GE(row.size(), 14u); // At least 4 + 6 + 4
}

TEST(ColumnsTest_619, EmptyColumnsContent_619) {
    Column c1("");
    c1.width(10);
    Column c2("");
    c2.width(10);
    Columns cols = c1 + c2;
    size_t count = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        count++;
        if (count > 50) break;
    }
    EXPECT_LE(count, 50u);
}

TEST(ColumnTest_619, MultipleWordsWrapCorrectly_619) {
    Column col("word1 word2 word3 word4 word5");
    col.width(15);
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
        if (lines.size() > 50) break;
    }
    EXPECT_GT(lines.size(), 1u);
    for (const auto& line : lines) {
        // Each line content (before trailing spaces) should fit within width
        // Trim trailing spaces
        auto trimmed = line;
        while (!trimmed.empty() && trimmed.back() == ' ') {
            trimmed.pop_back();
        }
        EXPECT_LE(trimmed.size(), 15u);
    }
}

TEST(ColumnTest_619, SingleCharacterString_619) {
    Column col("X");
    col.width(80);
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    EXPECT_EQ(*it, "X");
    ++it;
    EXPECT_EQ(it, col.end());
}

TEST(ColumnTest_619, NewlineInString_619) {
    Column col("Line1\nLine2");
    col.width(80);
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
        if (lines.size() > 50) break;
    }
    EXPECT_GE(lines.size(), 2u);
}
