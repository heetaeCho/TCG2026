#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <vector>

#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;
using Catch::TextFlow::AnsiSkippingString;

// Helper function to collect all lines from a Column
std::vector<std::string> collectLines(const Column& col) {
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
    }
    return lines;
}

// ============================================================
// Tests for Column construction and basic properties
// ============================================================

TEST(ColumnTest_615, DefaultWidth_615) {
    Column col("Hello");
    // Default width should be CATCH_CONFIG_CONSOLE_WIDTH - 1 = 79
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_615, SetWidth_615) {
    Column col("Hello");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST(ColumnTest_615, EmptyString_615) {
    Column col("");
    auto lines = collectLines(col);
    // An empty string should produce either no lines or one empty line
    // We just verify it doesn't crash
    EXPECT_TRUE(lines.empty() || (lines.size() == 1 && lines[0].empty()));
}

TEST(ColumnTest_615, SingleWordFitsInWidth_615) {
    Column col("Hello");
    col.width(80);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "Hello");
}

TEST(ColumnTest_615, MultipleWordsFitInOneLine_615) {
    Column col("Hello World");
    col.width(80);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "Hello World");
}

// ============================================================
// Tests for word wrapping
// ============================================================

TEST(ColumnTest_615, WordWrappingAtWidth_615) {
    Column col("Hello World");
    col.width(6);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 2u);
    EXPECT_EQ(lines[0], "Hello");
    EXPECT_EQ(lines[1], "World");
}

TEST(ColumnTest_615, LongTextWrapsMultipleLines_615) {
    Column col("one two three four five six seven eight");
    col.width(10);
    auto lines = collectLines(col);
    EXPECT_GE(lines.size(), 3u);
    // Each line should not exceed the width (accounting for possible hyphenation)
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 10u);
    }
}

TEST(ColumnTest_615, ExplicitNewlinesPreserved_615) {
    Column col("Hello\nWorld");
    col.width(80);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 2u);
    EXPECT_EQ(lines[0], "Hello");
    EXPECT_EQ(lines[1], "World");
}

TEST(ColumnTest_615, MultipleNewlines_615) {
    Column col("A\n\nB");
    col.width(80);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 3u);
}

// ============================================================
// Tests for indentation
// ============================================================

TEST(ColumnTest_615, IndentApplied_615) {
    Column col("Hello");
    col.width(80).indent(4);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0].substr(0, 4), "    ");
    EXPECT_NE(lines[0].find("Hello"), std::string::npos);
}

TEST(ColumnTest_615, IndentOnWrappedLines_615) {
    Column col("Hello World Foo Bar");
    col.width(12).indent(4);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 2u);
    for (const auto& line : lines) {
        // Every line should start with 4 spaces of indent
        EXPECT_EQ(line.substr(0, 4), "    ");
    }
}

TEST(ColumnTest_615, InitialIndentDifferent_615) {
    Column col("Hello World Foo Bar");
    col.width(20).indent(4).initialIndent(8);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // First line should have initial indent of 8
    EXPECT_EQ(lines[0].substr(0, 8), "        ");
    // Subsequent lines should have indent of 4
    if (lines.size() > 1) {
        EXPECT_EQ(lines[1].substr(0, 4), "    ");
    }
}

// ============================================================
// Tests for iterator behavior
// ============================================================

TEST(ColumnIteratorTest_615, BeginEqualsEndForEmpty_615) {
    Column col("");
    // For empty string, begin should equal end
    EXPECT_TRUE(col.begin() == col.end());
}

TEST(ColumnIteratorTest_615, BeginNotEqualsEndForNonEmpty_615) {
    Column col("Hello");
    EXPECT_TRUE(col.begin() != col.end());
}

TEST(ColumnIteratorTest_615, PostIncrementReturnsOldValue_615) {
    Column col("Hello World");
    col.width(6);
    auto it = col.begin();
    std::string firstLine = *it;
    auto old = it++;
    EXPECT_EQ(*old, firstLine);
}

TEST(ColumnIteratorTest_615, PreIncrementReturnsSelf_615) {
    Column col("Hello World");
    col.width(6);
    auto it = col.begin();
    auto& ref = ++it;
    EXPECT_EQ(&ref, &it);
}

TEST(ColumnIteratorTest_615, IterateAllLines_615) {
    Column col("a b c d e f");
    col.width(4);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GE(count, 1);
}

// ============================================================
// Tests for operator<< (stream output)
// ============================================================

TEST(ColumnTest_615, StreamOutput_615) {
    Column col("Hello World");
    col.width(80);
    std::ostringstream oss;
    oss << col;
    EXPECT_NE(oss.str().find("Hello World"), std::string::npos);
}

TEST(ColumnTest_615, StreamOutputMultipleLines_615) {
    Column col("Hello World");
    col.width(6);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello"), std::string::npos);
    EXPECT_NE(output.find("World"), std::string::npos);
    EXPECT_NE(output.find('\n'), std::string::npos);
}

// ============================================================
// Tests for very long words (hyphenation)
// ============================================================

TEST(ColumnTest_615, VeryLongWordHandled_615) {
    // A word longer than the width should be broken (possibly with hyphen)
    Column col("abcdefghijklmnopqrstuvwxyz");
    col.width(10);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // All lines should have length <= width
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 10u);
    }
}

TEST(ColumnTest_615, VeryLongWordWithIndent_615) {
    Column col("abcdefghijklmnopqrstuvwxyz");
    col.width(12).indent(4);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 12u);
    }
}

// ============================================================
// Boundary tests
// ============================================================

TEST(ColumnTest_615, WidthOfOne_615) {
    Column col("ab");
    col.width(2);
    auto lines = collectLines(col);
    // Should handle very small width
    EXPECT_GE(lines.size(), 1u);
}

TEST(ColumnTest_615, ExactFitWidth_615) {
    Column col("Hello");
    col.width(5);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
}

TEST(ColumnTest_615, MultipleSpacesBetweenWords_615) {
    Column col("Hello     World");
    col.width(80);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // The output should handle multiple spaces
}

TEST(ColumnTest_615, TrailingWhitespace_615) {
    Column col("Hello   ");
    col.width(80);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
}

TEST(ColumnTest_615, LeadingWhitespace_615) {
    Column col("   Hello");
    col.width(80);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
}

TEST(ColumnTest_615, OnlyWhitespace_615) {
    Column col("     ");
    col.width(80);
    auto lines = collectLines(col);
    // Should handle all-whitespace input gracefully
    // May produce empty or no lines
}

TEST(ColumnTest_615, OnlyNewlines_615) {
    Column col("\n\n\n");
    col.width(80);
    auto lines = collectLines(col);
    EXPECT_GE(lines.size(), 1u);
}

// ============================================================
// Tests for AnsiSkippingString
// ============================================================

TEST(AnsiSkippingStringTest_615, BasicConstruction_615) {
    AnsiSkippingString str("Hello");
    EXPECT_EQ(str.size(), 5u);
}

TEST(AnsiSkippingStringTest_615, EmptyString_615) {
    AnsiSkippingString str("");
    EXPECT_EQ(str.size(), 0u);
}

TEST(AnsiSkippingStringTest_615, BeginEndIterator_615) {
    AnsiSkippingString str("Hello");
    auto it = str.begin();
    auto end = str.end();
    EXPECT_NE(it, end);
    
    std::string result;
    for (; it != end; ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "Hello");
}

TEST(AnsiSkippingStringTest_615, AnsiEscapeSkipped_615) {
    // ANSI escape sequence: ESC[31m (red text)
    std::string text = "\033[31mHello\033[0m";
    AnsiSkippingString str(text);
    // The size should reflect visible characters only
    EXPECT_EQ(str.size(), 5u);
}

TEST(AnsiSkippingStringTest_615, SubstringExtraction_615) {
    AnsiSkippingString str("Hello World");
    auto begin = str.begin();
    auto end = str.end();
    std::string sub = str.substring(begin, end);
    EXPECT_EQ(sub, "Hello World");
}

TEST(AnsiSkippingStringTest_615, MoveConstruction_615) {
    std::string text = "Hello";
    AnsiSkippingString str(std::move(text));
    EXPECT_EQ(str.size(), 5u);
}

// ============================================================
// Tests for AnsiSkippingString::const_iterator
// ============================================================

TEST(AnsiSkippingStringIteratorTest_615, Dereference_615) {
    AnsiSkippingString str("A");
    auto it = str.begin();
    EXPECT_EQ(*it, 'A');
}

TEST(AnsiSkippingStringIteratorTest_615, Increment_615) {
    AnsiSkippingString str("AB");
    auto it = str.begin();
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
    ++it;
    EXPECT_EQ(it, str.end());
}

TEST(AnsiSkippingStringIteratorTest_615, PostIncrement_615) {
    AnsiSkippingString str("AB");
    auto it = str.begin();
    auto old = it++;
    EXPECT_EQ(*old, 'A');
    EXPECT_EQ(*it, 'B');
}

TEST(AnsiSkippingStringIteratorTest_615, Decrement_615) {
    AnsiSkippingString str("AB");
    auto it = str.begin();
    ++it; // now at 'B'
    --it; // back at 'A'
    EXPECT_EQ(*it, 'A');
}

TEST(AnsiSkippingStringIteratorTest_615, PostDecrement_615) {
    AnsiSkippingString str("AB");
    auto it = str.begin();
    ++it;
    auto old = it--;
    EXPECT_EQ(*old, 'B');
    EXPECT_EQ(*it, 'A');
}

TEST(AnsiSkippingStringIteratorTest_615, Equality_615) {
    AnsiSkippingString str("A");
    auto a = str.begin();
    auto b = str.begin();
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(AnsiSkippingStringIteratorTest_615, LessEqual_615) {
    AnsiSkippingString str("AB");
    auto a = str.begin();
    auto b = str.begin();
    ++b;
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= a);
}

TEST(AnsiSkippingStringIteratorTest_615, OneBefore_615) {
    AnsiSkippingString str("AB");
    auto it = str.begin();
    ++it; // at 'B'
    auto prev = it.oneBefore();
    EXPECT_EQ(*prev, 'A');
}

TEST(AnsiSkippingStringIteratorTest_615, SkipsAnsiSequences_615) {
    // ESC[31m is a color code
    std::string text = "\033[31mA\033[0m";
    AnsiSkippingString str(text);
    auto it = str.begin();
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(it, str.end());
}

// ============================================================
// Tests for Column + Column (Columns)
// ============================================================

TEST(ColumnsTest_615, TwoColumnsCanBeAdded_615) {
    Column left("Hello");
    left.width(20);
    Column right("World");
    right.width(20);
    auto cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello"), std::string::npos);
    EXPECT_NE(output.find("World"), std::string::npos);
}

// ============================================================
// Tests for chaining
// ============================================================

TEST(ColumnTest_615, ChainingWidthIndentInitialIndent_615) {
    Column col("Test text that is relatively long for wrapping purposes");
    col.width(20).indent(2).initialIndent(4);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // First line starts with 4 spaces
    EXPECT_EQ(lines[0].substr(0, 4), "    ");
    if (lines.size() > 1) {
        // Subsequent lines start with 2 spaces
        EXPECT_EQ(lines[1].substr(0, 2), "  ");
    }
}

TEST(ColumnTest_615, WidthReturnsByRef_615) {
    Column col("test");
    Column& ref = col.width(40);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_615, IndentReturnsByRef_615) {
    Column col("test");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_615, InitialIndentReturnsByRef_615) {
    Column col("test");
    Column& ref = col.initialIndent(4);
    EXPECT_EQ(&ref, &col);
}
