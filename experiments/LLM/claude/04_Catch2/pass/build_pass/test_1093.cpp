#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

// Helper function to collect all lines from a Column
std::vector<std::string> collectLines(const Column& col) {
    std::vector<std::string> lines;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lines.push_back(*it);
    }
    return lines;
}

// Helper to get the full output of a column via operator<<
std::string columnToString(const Column& col) {
    std::ostringstream oss;
    oss << col;
    return oss.str();
}

// ==================== Normal Operation Tests ====================

TEST(ColumnTest_1093, EmptyString_1093) {
    Column col("");
    auto lines = collectLines(col);
    // An empty string should produce no lines (begin == end)
    EXPECT_TRUE(lines.empty());
}

TEST(ColumnTest_1093, SingleShortWord_1093) {
    Column col("hello");
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "hello");
}

TEST(ColumnTest_1093, DefaultWidthIs79_1093) {
    Column col("test");
    EXPECT_EQ(col.width(), 79u);
}

TEST(ColumnTest_1093, SetWidth_1093) {
    Column col("test");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST(ColumnTest_1093, WidthChaining_1093) {
    Column col("test");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50u);
}

TEST(ColumnTest_1093, IndentChaining_1093) {
    Column col("test");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_1093, InitialIndentChaining_1093) {
    Column col("test");
    Column& ref = col.initialIndent(4);
    EXPECT_EQ(&ref, &col);
}

TEST(ColumnTest_1093, TextWrapsAtWidth_1093) {
    Column col("one two three four five six seven eight nine ten");
    col.width(20);
    auto lines = collectLines(col);
    ASSERT_GT(lines.size(), 1u);
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 20u);
    }
}

TEST(ColumnTest_1093, IndentApplied_1093) {
    Column col("hello world");
    col.width(40).indent(4);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    for (const auto& line : lines) {
        // Each line should start with spaces for indent
        EXPECT_EQ(line.substr(0, 4), "    ");
    }
}

TEST(ColumnTest_1093, InitialIndentApplied_1093) {
    Column col("hello world this is a longer text to wrap");
    col.width(30).indent(2).initialIndent(6);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 2u);
    // First line should have initial indent (6 spaces)
    std::string firstLine = lines[0];
    size_t firstNonSpace = firstLine.find_first_not_of(' ');
    EXPECT_EQ(firstNonSpace, 6u);
    // Second line should have regular indent (2 spaces)
    std::string secondLine = lines[1];
    size_t secondNonSpace = secondLine.find_first_not_of(' ');
    EXPECT_EQ(secondNonSpace, 2u);
}

TEST(ColumnTest_1093, LongWordHandled_1093) {
    // A word longer than the width should still be handled (possibly with hyphenation)
    Column col("superlongwordthatexceedswidth");
    col.width(10);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // All lines should respect the width
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 10u);
    }
}

TEST(ColumnTest_1093, MultipleSpacesInText_1093) {
    Column col("a  b  c");
    col.width(20);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
}

TEST(ColumnTest_1093, NewlineInText_1093) {
    Column col("line1\nline2\nline3");
    col.width(40);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 3u);
}

TEST(ColumnTest_1093, IteratorEquality_1093) {
    Column col("hello");
    auto begin = col.begin();
    auto end = col.end();
    EXPECT_NE(begin, end);
}

TEST(ColumnTest_1093, EmptyStringIteratorEquality_1093) {
    Column col("");
    auto begin = col.begin();
    auto end = col.end();
    EXPECT_EQ(begin, end);
}

TEST(ColumnTest_1093, PostIncrementIterator_1093) {
    Column col("hello world");
    col.width(5);
    auto it = col.begin();
    auto prev = it++;
    // prev should be different from it after increment (if there are multiple lines)
    // At minimum, the operation should not crash
    (void)prev;
}

TEST(ColumnTest_1093, OperatorStreamOutput_1093) {
    Column col("hello");
    col.width(40);
    std::string output = columnToString(col);
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST(ColumnTest_1093, StreamOutputMultipleLines_1093) {
    Column col("one two three four five six");
    col.width(10);
    std::string output = columnToString(col);
    // Should contain newlines
    EXPECT_NE(output.find('\n'), std::string::npos);
}

TEST(ColumnTest_1093, ExactWidthText_1093) {
    // Text that exactly fits the width
    std::string text(78, 'a'); // 79 - 1 for default width minus potential indent
    Column col(text);
    col.width(79);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 79u);
    }
}

TEST(ColumnTest_1093, OnlySpaces_1093) {
    Column col("     ");
    col.width(20);
    auto lines = collectLines(col);
    // Should handle gracefully (may produce empty or not)
    // Just ensure no crash
}

TEST(ColumnTest_1093, SingleCharacter_1093) {
    Column col("x");
    col.width(20);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "x");
}

TEST(ColumnTest_1093, MultipleNewlines_1093) {
    Column col("\n\n\n");
    col.width(20);
    auto lines = collectLines(col);
    // Each newline should produce a blank line or be handled
    ASSERT_GE(lines.size(), 1u);
}

TEST(ColumnTest_1093, TrailingNewline_1093) {
    Column col("hello\n");
    col.width(20);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // "hello" should appear somewhere
    bool found = false;
    for (const auto& line : lines) {
        if (line.find("hello") != std::string::npos) {
            found = true;
        }
    }
    EXPECT_TRUE(found);
}

TEST(ColumnTest_1093, LeadingNewline_1093) {
    Column col("\nhello");
    col.width(20);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
}

// ==================== Boundary Condition Tests ====================

TEST(ColumnTest_1093, MinimalWidth_1093) {
    // Width must be greater than indent. With indent 0, width 2 should work.
    Column col("ab cd ef");
    col.width(3);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 3u);
    }
}

TEST(ColumnTest_1093, WidthOneMoreThanIndent_1093) {
    Column col("a b c");
    col.width(5).indent(3);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    for (const auto& line : lines) {
        EXPECT_LE(line.size(), 5u);
    }
}

TEST(ColumnTest_1093, LargeWidth_1093) {
    Column col("short text");
    col.width(1000);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "short text");
}

TEST(ColumnTest_1093, ZeroIndent_1093) {
    Column col("hello");
    col.width(20).indent(0);
    auto lines = collectLines(col);
    ASSERT_EQ(lines.size(), 1u);
    EXPECT_EQ(lines[0], "hello");
}

// ==================== Column Addition (Columns) Tests ====================

TEST(ColumnTest_1093, ColumnAddition_1093) {
    Column col1("left side text");
    col1.width(20);
    Column col2("right side text");
    col2.width(20);
    auto columns = col1 + col2;
    std::ostringstream oss;
    oss << columns;
    std::string output = oss.str();
    EXPECT_NE(output.find("left"), std::string::npos);
    EXPECT_NE(output.find("right"), std::string::npos);
}

TEST(ColumnTest_1093, MoveColumnAddition_1093) {
    auto columns = Column("left") + Column("right");
    std::ostringstream oss;
    oss << columns;
    std::string output = oss.str();
    EXPECT_NE(output.find("left"), std::string::npos);
    EXPECT_NE(output.find("right"), std::string::npos);
}

// ==================== Dereference and Iteration Tests ====================

TEST(ColumnTest_1093, DereferenceFirstLine_1093) {
    Column col("first second third");
    col.width(10);
    auto it = col.begin();
    std::string firstLine = *it;
    EXPECT_FALSE(firstLine.empty());
    EXPECT_LE(firstLine.size(), 10u);
}

TEST(ColumnTest_1093, FullIteration_1093) {
    Column col("The quick brown fox jumps over the lazy dog");
    col.width(15);
    size_t lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        EXPECT_LE(line.size(), 15u);
        EXPECT_FALSE(line.empty());
        lineCount++;
    }
    EXPECT_GT(lineCount, 1u);
}

// ==================== AnsiSkippingString Tests ====================

TEST(AnsiSkippingStringTest_1093, BasicString_1093) {
    Catch::TextFlow::AnsiSkippingString str("hello");
    EXPECT_EQ(str.size(), 5u);
}

TEST(AnsiSkippingStringTest_1093, EmptyString_1093) {
    Catch::TextFlow::AnsiSkippingString str("");
    EXPECT_EQ(str.size(), 0u);
}

TEST(AnsiSkippingStringTest_1093, BeginEndIteration_1093) {
    Catch::TextFlow::AnsiSkippingString str("abc");
    auto it = str.begin();
    auto end = str.end();
    EXPECT_NE(it, end);
    
    std::string reconstructed;
    for (auto i = str.begin(); i != str.end(); ++i) {
        reconstructed += *i;
    }
    EXPECT_EQ(reconstructed, "abc");
}

TEST(AnsiSkippingStringTest_1093, AnsiEscapeSkipped_1093) {
    // ANSI escape sequence: \033[31m (red color)
    std::string textWithAnsi = "\033[31mhello\033[0m";
    Catch::TextFlow::AnsiSkippingString str(textWithAnsi);
    // The visible size should be just "hello" = 5
    EXPECT_EQ(str.size(), 5u);
}

TEST(AnsiSkippingStringTest_1093, SubstringExtraction_1093) {
    Catch::TextFlow::AnsiSkippingString str("hello world");
    auto begin = str.begin();
    auto end = str.end();
    std::string sub = str.substring(begin, end);
    EXPECT_EQ(sub, "hello world");
}

TEST(AnsiSkippingStringTest_1093, MoveConstruction_1093) {
    std::string text = "move me";
    Catch::TextFlow::AnsiSkippingString str(std::move(text));
    EXPECT_EQ(str.size(), 7u);
}

// ==================== Column with ANSI content ====================

TEST(ColumnTest_1093, AnsiEscapesInText_1093) {
    std::string ansiText = "\033[1mBold text\033[0m and normal";
    Column col(ansiText);
    col.width(40);
    auto lines = collectLines(col);
    ASSERT_GE(lines.size(), 1u);
    // The output should contain the ANSI codes
    std::string output = columnToString(col);
    EXPECT_NE(output.find("Bold text"), std::string::npos);
}

// ==================== Iterator inequality tests ====================

TEST(ColumnTest_1093, IteratorInequalityOperator_1093) {
    Column col("hello");
    auto begin = col.begin();
    auto end = col.end();
    EXPECT_TRUE(begin != end);
    EXPECT_FALSE(begin == end);
}

TEST(ColumnTest_1093, IteratorEqualityAfterFullIteration_1093) {
    Column col("short");
    col.width(40);
    auto it = col.begin();
    ++it;
    // After iterating past the single line, should equal end
    EXPECT_EQ(it, col.end());
}
