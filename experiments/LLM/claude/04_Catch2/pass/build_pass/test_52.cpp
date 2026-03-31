#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using Catch::TextFlow::Column;
using Catch::TextFlow::Columns;

class ColumnTest_52 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default width
TEST_F(ColumnTest_52, DefaultWidthIs79_52) {
    Column col("Hello");
    EXPECT_EQ(col.width(), 79u);
}

// Test setting custom width
TEST_F(ColumnTest_52, SetCustomWidth_52) {
    Column col("Hello");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

// Test width method returns reference for chaining
TEST_F(ColumnTest_52, WidthReturnsSelfForChaining_52) {
    Column col("Hello");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 50u);
}

// Test indent returns reference for chaining
TEST_F(ColumnTest_52, IndentReturnsSelfForChaining_52) {
    Column col("Hello");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

// Test initialIndent returns reference for chaining
TEST_F(ColumnTest_52, InitialIndentReturnsSelfForChaining_52) {
    Column col("Hello");
    Column& ref = col.initialIndent(4);
    EXPECT_EQ(&ref, &col);
}

// Test empty string
TEST_F(ColumnTest_52, EmptyString_52) {
    Column col("");
    std::ostringstream oss;
    oss << col;
    // An empty column should produce minimal or empty output
    std::string result = oss.str();
    // Just ensure it doesn't crash and produces something (even if just newline)
    EXPECT_TRUE(result.empty() || result == "\n");
}

// Test simple short string fits in one line
TEST_F(ColumnTest_52, ShortStringFitsOneLine_52) {
    Column col("Hello World");
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

// Test begin and end iterators
TEST_F(ColumnTest_52, BeginEndIterators_52) {
    Column col("Hello");
    auto it = col.begin();
    auto endIt = col.end();
    EXPECT_NE(it, endIt);
}

// Test iteration through lines
TEST_F(ColumnTest_52, IterationProducesLines_52) {
    Column col("Hello World");
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    EXPECT_GE(lineCount, 1);
}

// Test wrapping with narrow width
TEST_F(ColumnTest_52, NarrowWidthCausesWrapping_52) {
    Column col("Hello World");
    col.width(6);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    EXPECT_GT(lineCount, 1);
}

// Test very narrow width (width = 1)
TEST_F(ColumnTest_52, VeryNarrowWidth_52) {
    Column col("Hi");
    col.width(1);
    // Should not crash, each character or word goes on its own line
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test long text wrapping at default width
TEST_F(ColumnTest_52, LongTextWraps_52) {
    std::string longText = "This is a very long text that should definitely wrap around because it exceeds the default column width of seventy-nine characters in a single line.";
    Column col(longText);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    EXPECT_GT(lineCount, 1);
}

// Test indent affects output
TEST_F(ColumnTest_52, IndentAddsSpaces_52) {
    Column col("Hello");
    col.indent(4);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    // The output should start with spaces due to indent
    EXPECT_EQ(result.substr(0, 4), "    ");
}

// Test initialIndent different from regular indent
TEST_F(ColumnTest_52, InitialIndentOnFirstLine_52) {
    Column col("Hello World this is a test that should wrap");
    col.width(20);
    col.indent(2);
    col.initialIndent(4);
    
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string firstLine = *it;
    // First line should have 4 spaces of initial indent
    EXPECT_EQ(firstLine.substr(0, 4), "    ");
}

// Test operator<< for Column
TEST_F(ColumnTest_52, OperatorOutputStream_52) {
    Column col("Test output");
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_NE(result.find("Test"), std::string::npos);
    EXPECT_NE(result.find("output"), std::string::npos);
}

// Test operator+ for combining columns
TEST_F(ColumnTest_52, OperatorPlusCombinesColumns_52) {
    Column left("Left column text");
    Column right("Right column text");
    left.width(20);
    right.width(20);
    
    Columns combined = left + right;
    std::ostringstream oss;
    oss << combined;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test operator+ with rvalue references
TEST_F(ColumnTest_52, OperatorPlusWithRValues_52) {
    auto combined = Column("Left") + Column("Right");
    std::ostringstream oss;
    oss << combined;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test multiple words wrapping
TEST_F(ColumnTest_52, MultipleWordsWrapping_52) {
    Column col("word1 word2 word3 word4 word5");
    col.width(12);
    
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        // Each line should not exceed the width (excluding potential trailing whitespace considerations)
        lineCount++;
    }
    EXPECT_GT(lineCount, 1);
}

// Test with newlines in input
TEST_F(ColumnTest_52, InputWithNewlines_52) {
    Column col("Line1\nLine2\nLine3");
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    EXPECT_GE(lineCount, 3);
}

// Test zero indent
TEST_F(ColumnTest_52, ZeroIndent_52) {
    Column col("Hello");
    col.indent(0);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    // Should start with 'H', no indent
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], 'H');
}

// Test constructing from rvalue string
TEST_F(ColumnTest_52, ConstructFromRValueString_52) {
    std::string text = "Moved text";
    Column col(std::move(text));
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_NE(result.find("Moved"), std::string::npos);
}

// Test single character
TEST_F(ColumnTest_52, SingleCharacter_52) {
    Column col("A");
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string line = *it;
    EXPECT_NE(line.find('A'), std::string::npos);
}

// Test large width doesn't affect short text
TEST_F(ColumnTest_52, LargeWidthShortText_52) {
    Column col("Short");
    col.width(200);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    EXPECT_EQ(lineCount, 1);
}

// Test spaces only string
TEST_F(ColumnTest_52, SpacesOnlyString_52) {
    Column col("     ");
    std::ostringstream oss;
    oss << col;
    // Should not crash
    std::string result = oss.str();
    // Result may be empty or whitespace
}

// Test line content does not exceed specified width
TEST_F(ColumnTest_52, LineContentDoesNotExceedWidth_52) {
    Column col("This is a test of the emergency broadcasting system which should wrap properly");
    col.width(20);
    
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        // The visible content of each line should not exceed width
        EXPECT_LE(line.size(), 20u);
    }
}

// Test indent with wrapping
TEST_F(ColumnTest_52, IndentWithWrapping_52) {
    Column col("word1 word2 word3 word4 word5 word6");
    col.width(20);
    col.indent(4);
    
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        if (lineCount > 0) {
            // Subsequent lines should have indent
            EXPECT_EQ(line.substr(0, 4), "    ");
        }
        lineCount++;
    }
    EXPECT_GT(lineCount, 1);
}
