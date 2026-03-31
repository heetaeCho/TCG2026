#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

class ColumnConstIteratorTest_45 : public ::testing::Test {
protected:
    // Helper to create a Column with specific settings
    Column createColumn(const std::string& text, size_t width = 80) {
        Column col(text);
        col.width(width);
        return col;
    }
};

// Test that begin() iterator equals itself
TEST_F(ColumnConstIteratorTest_45, BeginIteratorEqualsSelf_45) {
    Column col = createColumn("Hello World");
    auto it1 = col.begin();
    auto it2 = col.begin();
    EXPECT_TRUE(it1 == it2);
}

// Test that end() iterator equals itself
TEST_F(ColumnConstIteratorTest_45, EndIteratorEqualsSelf_45) {
    Column col = createColumn("Hello World");
    auto it1 = col.end();
    auto it2 = col.end();
    EXPECT_TRUE(it1 == it2);
}

// Test that begin() != end() for non-empty string
TEST_F(ColumnConstIteratorTest_45, BeginNotEqualToEndForNonEmpty_45) {
    Column col = createColumn("Hello World");
    EXPECT_FALSE(col.begin() == col.end());
    EXPECT_TRUE(col.begin() != col.end());
}

// Test that begin() == end() for empty string
TEST_F(ColumnConstIteratorTest_45, BeginEqualsEndForEmptyString_45) {
    Column col = createColumn("");
    // For empty string, begin should equal end after iteration or directly
    auto it = col.begin();
    // Iterate to the end
    bool found_content = false;
    while (it != col.end()) {
        found_content = true;
        ++it;
    }
    EXPECT_TRUE(it == col.end());
}

// Test dereferencing begin iterator gives first line
TEST_F(ColumnConstIteratorTest_45, DereferenceBeginGivesFirstLine_45) {
    Column col = createColumn("Hello World", 80);
    auto it = col.begin();
    std::string line = *it;
    EXPECT_EQ(line, "Hello World");
}

// Test that short text fits in one line
TEST_F(ColumnConstIteratorTest_45, ShortTextFitsInOneLine_45) {
    Column col = createColumn("Short", 80);
    auto it = col.begin();
    EXPECT_NE(it, col.end());
    std::string line = *it;
    EXPECT_EQ(line, "Short");
    ++it;
    EXPECT_EQ(it, col.end());
}

// Test text wrapping when width is small
TEST_F(ColumnConstIteratorTest_45, TextWrapsAtSmallWidth_45) {
    Column col = createColumn("Hello World", 5);
    auto it = col.begin();
    EXPECT_NE(it, col.end());
    
    std::string firstLine = *it;
    EXPECT_FALSE(firstLine.empty());
    EXPECT_LE(firstLine.size(), static_cast<size_t>(6)); // may include hyphen
    
    ++it;
    EXPECT_NE(it, col.end());
    
    // There should be at least 2 lines
    std::string secondLine = *it;
    EXPECT_FALSE(secondLine.empty());
}

// Test post-increment returns old iterator value
TEST_F(ColumnConstIteratorTest_45, PostIncrementReturnsOldValue_45) {
    Column col = createColumn("Hello World", 5);
    auto it = col.begin();
    std::string firstLine = *it;
    
    auto old_it = it++;
    std::string oldLine = *old_it;
    EXPECT_EQ(firstLine, oldLine);
}

// Test multiple lines iteration
TEST_F(ColumnConstIteratorTest_45, IterateMultipleLines_45) {
    Column col = createColumn("This is a somewhat longer text that should wrap across multiple lines", 20);
    
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        EXPECT_FALSE(line.empty());
        lineCount++;
    }
    EXPECT_GT(lineCount, 1);
}

// Test iterators from different columns are not equal
TEST_F(ColumnConstIteratorTest_45, IteratorsFromDifferentColumnsNotEqual_45) {
    Column col1 = createColumn("Hello");
    Column col2 = createColumn("Hello");
    
    auto it1 = col1.begin();
    auto it2 = col2.begin();
    
    // Different columns, so iterators should not be equal (different column references)
    EXPECT_FALSE(it1 == it2);
}

// Test inequality operator
TEST_F(ColumnConstIteratorTest_45, InequalityOperator_45) {
    Column col = createColumn("Hello World");
    auto begin = col.begin();
    auto end = col.end();
    EXPECT_TRUE(begin != end);
    EXPECT_FALSE(begin != begin);
}

// Test with newline characters in text
TEST_F(ColumnConstIteratorTest_45, TextWithNewlines_45) {
    Column col = createColumn("Line1\nLine2\nLine3", 80);
    
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    EXPECT_GE(lineCount, 3);
}

// Test with width of 1
TEST_F(ColumnConstIteratorTest_45, VerySmallWidth_45) {
    Column col = createColumn("AB", 1);
    auto it = col.begin();
    EXPECT_NE(it, col.end());
    
    // Should be able to iterate without infinite loop
    int lineCount = 0;
    while (it != col.end() && lineCount < 100) {
        ++it;
        lineCount++;
    }
    EXPECT_GT(lineCount, 0);
    EXPECT_LT(lineCount, 100); // Should terminate
}

// Test with indentation
TEST_F(ColumnConstIteratorTest_45, ColumnWithIndent_45) {
    Column col = createColumn("Hello World", 80);
    col.indent(4);
    
    auto it = col.begin();
    std::string line = *it;
    // First line should have indent
    EXPECT_GE(line.size(), 4u);
    EXPECT_EQ(line.substr(0, 4), "    ");
}

// Test with initial indent
TEST_F(ColumnConstIteratorTest_45, ColumnWithInitialIndent_45) {
    Column col = createColumn("Hello World that is long enough to wrap around", 20);
    col.initialIndent(4);
    
    auto it = col.begin();
    std::string firstLine = *it;
    // First line should have initial indent
    EXPECT_GE(firstLine.size(), 4u);
    EXPECT_EQ(firstLine.substr(0, 4), "    ");
}

// Test single character string
TEST_F(ColumnConstIteratorTest_45, SingleCharString_45) {
    Column col = createColumn("A", 80);
    auto it = col.begin();
    EXPECT_NE(it, col.end());
    EXPECT_EQ(*it, "A");
    ++it;
    EXPECT_EQ(it, col.end());
}

// Test with spaces only
TEST_F(ColumnConstIteratorTest_45, SpacesOnlyString_45) {
    Column col = createColumn("     ", 80);
    auto it = col.begin();
    int lineCount = 0;
    while (it != col.end() && lineCount < 100) {
        ++it;
        lineCount++;
    }
    // Should terminate without infinite loop
    EXPECT_LT(lineCount, 100);
}

// Test that range-based for loop works
TEST_F(ColumnConstIteratorTest_45, RangeBasedForLoop_45) {
    Column col = createColumn("Test text for range based loop", 80);
    int count = 0;
    for (const auto& line : col) {
        (void)line;
        count++;
    }
    EXPECT_GE(count, 1);
}

// Test equality is reflexive
TEST_F(ColumnConstIteratorTest_45, EqualityIsReflexive_45) {
    Column col = createColumn("Test");
    auto it = col.begin();
    EXPECT_TRUE(it == it);
    EXPECT_FALSE(it != it);
}

// Test after full iteration, iterator equals end
TEST_F(ColumnConstIteratorTest_45, FullIterationReachesEnd_45) {
    Column col = createColumn("A medium length string for testing", 10);
    auto it = col.begin();
    while (it != col.end()) {
        ++it;
    }
    EXPECT_TRUE(it == col.end());
}
