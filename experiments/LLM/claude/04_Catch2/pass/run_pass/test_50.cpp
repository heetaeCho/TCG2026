#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using Catch::TextFlow::Column;

class ColumnTest_50 : public ::testing::Test {
protected:
};

// Test default width
TEST_F(ColumnTest_50, DefaultWidthIs79_50) {
    Column col("Hello");
    EXPECT_EQ(col.width(), 79u);
}

// Test setting custom width
TEST_F(ColumnTest_50, SetCustomWidth_50) {
    Column col("Hello");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

// Test width of 1
TEST_F(ColumnTest_50, WidthBoundaryOne_50) {
    Column col("Hello");
    col.width(1);
    EXPECT_EQ(col.width(), 1u);
}

// Test large width
TEST_F(ColumnTest_50, LargeWidth_50) {
    Column col("Hello");
    col.width(10000);
    EXPECT_EQ(col.width(), 10000u);
}

// Test width chaining (returns reference)
TEST_F(ColumnTest_50, WidthChainingReturnsReference_50) {
    Column col("Hello");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50u);
}

// Test indent chaining
TEST_F(ColumnTest_50, IndentChainingReturnsReference_50) {
    Column col("Hello");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

// Test initialIndent chaining
TEST_F(ColumnTest_50, InitialIndentChainingReturnsReference_50) {
    Column col("Hello");
    Column& ref = col.initialIndent(4);
    EXPECT_EQ(&ref, &col);
}

// Test construction with empty string
TEST_F(ColumnTest_50, ConstructWithEmptyString_50) {
    Column col("");
    EXPECT_EQ(col.width(), 79u);
}

// Test construction with rvalue string
TEST_F(ColumnTest_50, ConstructWithRvalueString_50) {
    Column col(std::string("Hello World"));
    EXPECT_EQ(col.width(), 79u);
}

// Test begin and end iterators exist (non-empty)
TEST_F(ColumnTest_50, BeginEndIteratorsNonEmpty_50) {
    Column col("Hello");
    auto it = col.begin();
    auto endIt = col.end();
    // At least one line should be produced for a non-empty string
    EXPECT_NE(it, endIt);
}

// Test begin and end for empty string
TEST_F(ColumnTest_50, BeginEndForEmptyString_50) {
    Column col("");
    auto it = col.begin();
    auto endIt = col.end();
    // Even empty string may produce at least one line or no lines
    // We just ensure no crash
    (void)it;
    (void)endIt;
}

// Test iteration produces expected content for short string
TEST_F(ColumnTest_50, IterationShortString_50) {
    Column col("Hello");
    col.width(79);
    auto it = col.begin();
    auto endIt = col.end();
    ASSERT_NE(it, endIt);
    std::string firstLine = *it;
    EXPECT_EQ(firstLine, "Hello");
    ++it;
    EXPECT_EQ(it, endIt);
}

// Test wrapping with narrow width
TEST_F(ColumnTest_50, WrappingWithNarrowWidth_50) {
    Column col("Hello World");
    col.width(5);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    EXPECT_GE(lineCount, 2);
}

// Test stream output operator
TEST_F(ColumnTest_50, StreamOutputOperator_50) {
    Column col("Hello");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello"), std::string::npos);
}

// Test indent affects output
TEST_F(ColumnTest_50, IndentAffectsOutput_50) {
    Column col("Hello");
    col.indent(4);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    // Output should start with spaces
    EXPECT_EQ(output.substr(0, 4), "    ");
}

// Test initialIndent affects first line
TEST_F(ColumnTest_50, InitialIndentAffectsFirstLine_50) {
    Column col("Hello");
    col.initialIndent(8);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_EQ(output.substr(0, 8), "        ");
}

// Test operator+ combines two columns
TEST_F(ColumnTest_50, OperatorPlusCombinesColumns_50) {
    Column col1("Left");
    col1.width(20);
    Column col2("Right");
    col2.width(20);
    auto columns = col1 + col2;
    std::ostringstream oss;
    oss << columns;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

// Test operator+ with rvalue columns
TEST_F(ColumnTest_50, OperatorPlusRvalueColumns_50) {
    auto columns = Column("Left") + Column("Right");
    std::ostringstream oss;
    oss << columns;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// Test long text wraps correctly
TEST_F(ColumnTest_50, LongTextWraps_50) {
    std::string longText = "This is a rather long piece of text that should be wrapped across multiple lines when the width is set to a reasonable value.";
    Column col(longText);
    col.width(30);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        // Each line (after trimming) should not exceed the width
        EXPECT_LE(line.size(), 30u);
        lineCount++;
    }
    EXPECT_GT(lineCount, 1);
}

// Test method chaining
TEST_F(ColumnTest_50, MethodChaining_50) {
    Column col("Hello World");
    col.width(40).indent(2).initialIndent(4);
    EXPECT_EQ(col.width(), 40u);
    std::ostringstream oss;
    oss << col;
    EXPECT_FALSE(oss.str().empty());
}

// Test multiple words fit exactly in width
TEST_F(ColumnTest_50, WordsFitExactlyInWidth_50) {
    Column col("AB CD");
    col.width(5);
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string firstLine = *it;
    EXPECT_EQ(firstLine, "AB CD");
    ++it;
    EXPECT_EQ(it, col.end());
}

// Test single very long word
TEST_F(ColumnTest_50, SingleLongWord_50) {
    std::string longWord(100, 'A');
    Column col(longWord);
    col.width(20);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    // A single 100-char word with width 20 should produce multiple lines
    EXPECT_GT(lineCount, 1);
}
