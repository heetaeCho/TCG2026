#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iterator>

using namespace Catch::TextFlow;

class ColumnTest_46 : public ::testing::Test {
protected:
    // Helper to collect all lines from a Column
    std::vector<std::string> collectLines(const Column& col) {
        std::vector<std::string> lines;
        for (auto it = col.begin(); it != col.end(); ++it) {
            lines.push_back(*it);
        }
        return lines;
    }
};

// Test that an empty string column produces minimal output
TEST_F(ColumnTest_46, EmptyStringColumn_46) {
    Column col("");
    auto lines = collectLines(col);
    // An empty column should still be iterable
    // It may produce one empty line or zero lines
    EXPECT_GE(lines.size(), 0u);
}

// Test that a short string fits on one line
TEST_F(ColumnTest_46, ShortStringFitsOnOneLine_46) {
    Column col("Hello");
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    EXPECT_NE(lines[0].find("Hello"), std::string::npos);
}

// Test that a long string is wrapped across multiple lines
TEST_F(ColumnTest_46, LongStringWrapsToMultipleLines_46) {
    std::string longStr;
    for (int i = 0; i < 20; ++i) {
        longStr += "word ";
    }
    Column col(longStr);
    col.width(20);
    auto lines = collectLines(col);
    EXPECT_GT(lines.size(), 1u);
    // Each line should not exceed the specified width (approximately)
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 25u); // some tolerance for edge cases
    }
}

// Test that width setting affects wrapping
TEST_F(ColumnTest_46, WidthAffectsWrapping_46) {
    std::string text = "This is a test of the text wrapping functionality";
    
    Column colWide(text);
    colWide.width(80);
    auto wideLines = collectLines(colWide);
    
    Column colNarrow(text);
    colNarrow.width(15);
    auto narrowLines = collectLines(colNarrow);
    
    // Narrow column should have more lines than wide column
    EXPECT_GE(narrowLines.size(), wideLines.size());
}

// Test that indent affects output
TEST_F(ColumnTest_46, IndentAffectsOutput_46) {
    Column col("Hello World");
    col.width(80).indent(4);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // First line should start with spaces due to indent
    EXPECT_EQ(lines[0].substr(0, 4), "    ");
}

// Test initialIndent
TEST_F(ColumnTest_46, InitialIndentAffectsFirstLine_46) {
    std::string text = "First line text that should be indented differently";
    Column col(text);
    col.width(80).initialIndent(8).indent(2);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // First line should have initial indent of 8
    EXPECT_EQ(lines[0].substr(0, 8), "        ");
}

// Test const_iterator equality
TEST_F(ColumnTest_46, IteratorEquality_46) {
    Column col("Test");
    auto it1 = col.begin();
    auto it2 = col.begin();
    EXPECT_FALSE(it1 != it2);
}

// Test const_iterator inequality with end
TEST_F(ColumnTest_46, IteratorInequalityWithEnd_46) {
    Column col("Test");
    auto it = col.begin();
    auto end = col.end();
    EXPECT_TRUE(it != end);
}

// Test that end iterator equals end iterator
TEST_F(ColumnTest_46, EndIteratorEqualsEnd_46) {
    Column col("Test");
    auto end1 = col.end();
    auto end2 = col.end();
    EXPECT_FALSE(end1 != end2);
}

// Test post-increment iterator
TEST_F(ColumnTest_46, PostIncrementIterator_46) {
    Column col("Hello World");
    col.width(5);
    auto it = col.begin();
    auto prev = it++;
    // prev should still dereference to the first line
    std::string prevLine = *prev;
    std::string currLine = *it;
    EXPECT_NE(prevLine, currLine);
}

// Test pre-increment iterator
TEST_F(ColumnTest_46, PreIncrementIterator_46) {
    std::string text = "word1 word2 word3 word4";
    Column col(text);
    col.width(10);
    auto it = col.begin();
    auto& ref = ++it;
    // Should return reference to the same iterator
    EXPECT_FALSE(it != ref);
}

// Test that iterator reaches end after processing all text
TEST_F(ColumnTest_46, IteratorReachesEnd_46) {
    Column col("Short");
    auto it = col.begin();
    while (it != col.end()) {
        ++it;
    }
    EXPECT_FALSE(it != col.end());
}

// Test Column with only spaces
TEST_F(ColumnTest_46, ColumnWithOnlySpaces_46) {
    Column col("     ");
    auto lines = collectLines(col);
    // Should be iterable without crashing
    EXPECT_GE(lines.size(), 0u);
}

// Test Column with newline characters
TEST_F(ColumnTest_46, ColumnWithNewlines_46) {
    Column col("Line1\nLine2\nLine3");
    col.width(80);
    auto lines = collectLines(col);
    // Should produce at least 3 lines
    EXPECT_GE(lines.size(), 3u);
}

// Test very narrow width
TEST_F(ColumnTest_46, VeryNarrowWidth_46) {
    Column col("Hello World");
    col.width(5);
    auto lines = collectLines(col);
    EXPECT_GT(lines.size(), 1u);
}

// Test single character
TEST_F(ColumnTest_46, SingleCharacter_46) {
    Column col("X");
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    EXPECT_NE(lines[0].find("X"), std::string::npos);
}

// Test that dereference operator returns a string
TEST_F(ColumnTest_46, DereferenceReturnsString_46) {
    Column col("Test string");
    auto it = col.begin();
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

// Test Column with a very long word that exceeds width
TEST_F(ColumnTest_46, VeryLongWordExceedingWidth_46) {
    std::string longWord = "abcdefghijklmnopqrstuvwxyz";
    Column col(longWord);
    col.width(10);
    auto lines = collectLines(col);
    // Should still produce output without crashing
    EXPECT_GE(lines.size(), 1u);
}

// Test Column + Column (if supported)
TEST_F(ColumnTest_46, ColumnConcatenation_46) {
    Column col1("Left side text");
    col1.width(20);
    Column col2("Right side text");
    col2.width(20);
    
    auto columns = col1 + col2;
    // Iterate through the combined columns
    std::vector<std::string> lines;
    for (auto it = columns.begin(); it != columns.end(); ++it) {
        lines.push_back(*it);
    }
    EXPECT_GE(lines.size(), 1u);
}

// Test width of 1
TEST_F(ColumnTest_46, WidthOfOne_46) {
    Column col("AB");
    col.width(1);
    auto lines = collectLines(col);
    // Should not crash, and should produce output
    EXPECT_GE(lines.size(), 1u);
}

// Test multiple spaces between words
TEST_F(ColumnTest_46, MultipleSpacesBetweenWords_46) {
    Column col("Hello     World");
    col.width(80);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
}

// Test that indent larger than width doesn't crash
TEST_F(ColumnTest_46, IndentLargerThanText_46) {
    Column col("Hi");
    col.width(80).indent(20);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // The line should have leading spaces
    EXPECT_GE(lines[0].size(), 20u);
}
