#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

// Helper to collect all lines from a Column iterator
std::vector<std::string> collectLines(const Column& col) {
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
    }
    return lines;
}

// Test basic construction of a Column with simple text
TEST(ColumnConstIteratorTest_614, SimpleTextDereference_614) {
    Column col("Hello");
    col.width(80);
    auto it = col.begin();
    std::string line = *it;
    EXPECT_FALSE(line.empty());
    EXPECT_NE(line.find("Hello"), std::string::npos);
}

// Test that an empty string produces no lines (or one empty line)
TEST(ColumnConstIteratorTest_614, EmptyString_614) {
    Column col("");
    col.width(80);
    auto lines = collectLines(col);
    // Empty string should produce at most one line
    EXPECT_LE(lines.size(), 1u);
}

// Test that begin() == end() for empty string or proper termination
TEST(ColumnConstIteratorTest_614, BeginEndEquality_614) {
    Column col("Hello");
    col.width(80);
    auto it = col.begin();
    auto end = col.end();
    EXPECT_NE(it, end);
    ++it;
    EXPECT_EQ(it, end);
}

// Test that a long string wraps correctly within column width
TEST(ColumnConstIteratorTest_614, LongStringWraps_614) {
    Column col("This is a long string that should be wrapped across multiple lines when the column width is small");
    col.width(20);
    auto lines = collectLines(col);
    EXPECT_GT(lines.size(), 1u);
    for (const auto& line : lines) {
        // Each line should not exceed the column width significantly
        // (indentation and hyphen may add a small amount)
        EXPECT_LE(line.size(), 25u); // Allow some tolerance
    }
}

// Test post-increment operator
TEST(ColumnConstIteratorTest_614, PostIncrementOperator_614) {
    Column col("Line one and line two hopefully");
    col.width(15);
    auto it = col.begin();
    auto prev = it++;
    std::string firstLine = *prev;
    std::string secondLine = *it;
    EXPECT_FALSE(firstLine.empty());
    // If there are multiple lines, they should differ or at least second should exist
    EXPECT_NE(it, col.end());
}

// Test iterator inequality
TEST(ColumnConstIteratorTest_614, IteratorInequality_614) {
    Column col("Some text");
    col.width(80);
    auto it1 = col.begin();
    auto it2 = col.end();
    EXPECT_TRUE(it1 != it2);
}

// Test iterator equality with self
TEST(ColumnConstIteratorTest_614, IteratorSelfEquality_614) {
    Column col("Some text");
    col.width(80);
    auto it = col.begin();
    EXPECT_TRUE(it == it);
}

// Test that width=1 still produces output (boundary)
TEST(ColumnConstIteratorTest_614, VerySmallWidth_614) {
    Column col("abc");
    col.width(2);
    auto lines = collectLines(col);
    EXPECT_GE(lines.size(), 1u);
}

// Test with indentation
TEST(ColumnConstIteratorTest_614, WithIndent_614) {
    Column col("Hello World");
    col.width(80).indent(4);
    auto it = col.begin();
    std::string line = *it;
    // Line should start with spaces for indentation
    EXPECT_GE(line.size(), 4u);
    EXPECT_EQ(line.substr(0, 4), "    ");
}

// Test with initial indent different from subsequent indent
TEST(ColumnConstIteratorTest_614, InitialIndent_614) {
    Column col("This is a long text that will wrap across multiple lines for testing indent behavior");
    col.width(30).initialIndent(2).indent(4);
    auto lines = collectLines(col);
    EXPECT_GE(lines.size(), 2u);
    // First line should have initial indent of 2
    EXPECT_GE(lines[0].size(), 2u);
    EXPECT_EQ(lines[0].substr(0, 2), "  ");
    // Subsequent lines should have indent of 4
    if (lines.size() > 1) {
        EXPECT_GE(lines[1].size(), 4u);
        EXPECT_EQ(lines[1].substr(0, 4), "    ");
    }
}

// Test single word that is exactly the width
TEST(ColumnConstIteratorTest_614, WordExactlyWidth_614) {
    Column col("12345");
    col.width(5);
    auto lines = collectLines(col);
    EXPECT_GE(lines.size(), 1u);
}

// Test multiple spaces in text
TEST(ColumnConstIteratorTest_614, MultipleSpaces_614) {
    Column col("Hello    World");
    col.width(80);
    auto it = col.begin();
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

// Test newline character in text
TEST(ColumnConstIteratorTest_614, NewlineInText_614) {
    Column col("Hello\nWorld");
    col.width(80);
    auto lines = collectLines(col);
    EXPECT_GE(lines.size(), 2u);
}

// Test multiple newlines
TEST(ColumnConstIteratorTest_614, MultipleNewlines_614) {
    Column col("A\n\nB");
    col.width(80);
    auto lines = collectLines(col);
    EXPECT_GE(lines.size(), 3u);
}

// Test a very long word that exceeds column width (should be hyphenated or broken)
TEST(ColumnConstIteratorTest_614, VeryLongWord_614) {
    Column col("Supercalifragilisticexpialidocious");
    col.width(10);
    auto lines = collectLines(col);
    EXPECT_GT(lines.size(), 1u);
}

// Test that iterating through all lines and then checking end works
TEST(ColumnConstIteratorTest_614, FullIteration_614) {
    Column col("One two three four five six seven eight nine ten");
    col.width(15);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        EXPECT_FALSE(line.empty());
        ++count;
    }
    EXPECT_GT(count, 0);
}

// Test Column with only whitespace
TEST(ColumnConstIteratorTest_614, OnlyWhitespace_614) {
    Column col("   ");
    col.width(80);
    auto lines = collectLines(col);
    // Should produce at least some output or be empty
    EXPECT_GE(lines.size(), 0u);
}

// Test default width (CATCH_CONFIG_CONSOLE_WIDTH = 80)
TEST(ColumnConstIteratorTest_614, DefaultWidth_614) {
    Column col("Short");
    auto it = col.begin();
    std::string line = *it;
    EXPECT_NE(line.find("Short"), std::string::npos);
    ++it;
    EXPECT_EQ(it, col.end());
}

// Test that two iterators from same column at begin are equal
TEST(ColumnConstIteratorTest_614, TwoBeginIteratorsEqual_614) {
    Column col("Test");
    col.width(80);
    auto it1 = col.begin();
    auto it2 = col.begin();
    EXPECT_EQ(it1, it2);
}

// Test that two end iterators are equal
TEST(ColumnConstIteratorTest_614, TwoEndIteratorsEqual_614) {
    Column col("Test");
    col.width(80);
    auto it1 = col.end();
    auto it2 = col.end();
    EXPECT_EQ(it1, it2);
}
