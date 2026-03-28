#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using Catch::TextFlow::Column;

class ColumnTest_51 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(ColumnTest_51, ConstructFromConstString_51) {
    const std::string text = "Hello World";
    Column col(text);
    EXPECT_EQ(col.width(), 79u); // default width = CATCH_CONFIG_CONSOLE_WIDTH - 1 = 80 - 1
}

TEST_F(ColumnTest_51, ConstructFromRValueString_51) {
    Column col(std::string("Hello World"));
    EXPECT_EQ(col.width(), 79u);
}

TEST_F(ColumnTest_51, ConstructFromEmptyString_51) {
    Column col("");
    EXPECT_EQ(col.width(), 79u);
}

// ==================== Width Tests ====================

TEST_F(ColumnTest_51, DefaultWidthIs79_51) {
    Column col("test");
    EXPECT_EQ(col.width(), 79u);
}

TEST_F(ColumnTest_51, SetWidthReturnsModifiedColumn_51) {
    Column col("test");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

TEST_F(ColumnTest_51, SetWidthTo1_51) {
    Column col("test");
    col.width(1);
    EXPECT_EQ(col.width(), 1u);
}

TEST_F(ColumnTest_51, SetWidthToLargeValue_51) {
    Column col("test");
    col.width(1000);
    EXPECT_EQ(col.width(), 1000u);
}

// ==================== Chaining Tests ====================

TEST_F(ColumnTest_51, WidthReturnsSelfReference_51) {
    Column col("test");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
}

TEST_F(ColumnTest_51, IndentReturnsSelfReference_51) {
    Column col("test");
    Column& ref = col.indent(5);
    EXPECT_EQ(&ref, &col);
}

TEST_F(ColumnTest_51, InitialIndentReturnsSelfReference_51) {
    Column col("test");
    Column& ref = col.initialIndent(3);
    EXPECT_EQ(&ref, &col);
}

TEST_F(ColumnTest_51, ChainingWidthIndentInitialIndent_51) {
    Column col("test");
    Column& ref = col.width(60).indent(4).initialIndent(2);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 60u);
}

// ==================== Iterator Tests ====================

TEST_F(ColumnTest_51, BeginAndEndAreEqualForEmptyString_51) {
    Column col("");
    // For an empty string, iterating should produce minimal content
    // We just verify begin/end are obtainable
    auto it = col.begin();
    auto end = col.end();
    // We can't necessarily assert they're equal for empty,
    // but we can iterate and check
    int count = 0;
    for (auto i = col.begin(); i != col.end(); ++i) {
        ++count;
    }
    // Empty string should produce at most one empty line or zero lines
    EXPECT_GE(count, 0);
    EXPECT_LE(count, 1);
}

TEST_F(ColumnTest_51, IteratorProducesContentForNonEmptyString_51) {
    Column col("Hello World");
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GE(count, 1);
}

TEST_F(ColumnTest_51, ShortStringFitsInOneLine_51) {
    Column col("Hello");
    col.width(79);
    int count = 0;
    std::string result;
    for (auto it = col.begin(); it != col.end(); ++it) {
        result += *it;
        ++count;
    }
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, "Hello");
}

TEST_F(ColumnTest_51, LongStringWrapsAcrossMultipleLines_51) {
    Column col("This is a much longer string that should definitely wrap across multiple lines when width is small");
    col.width(20);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GT(count, 1);
}

TEST_F(ColumnTest_51, EachLineRespectsWidth_51) {
    Column col("This is a test string that should be wrapped based on column width setting");
    col.width(20);
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        EXPECT_LE(line.size(), 20u);
    }
}

// ==================== Indent Tests ====================

TEST_F(ColumnTest_51, IndentAddsSpacesToSubsequentLines_51) {
    Column col("This is a long text that wraps across multiple lines for testing indent");
    col.width(30).indent(4);
    int lineNum = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        if (lineNum > 0) {
            // Subsequent lines should start with spaces
            EXPECT_GE(line.size(), 4u);
            EXPECT_EQ(line.substr(0, 4), "    ");
        }
        ++lineNum;
    }
    EXPECT_GT(lineNum, 1); // Make sure it actually wrapped
}

TEST_F(ColumnTest_51, InitialIndentAddsSpacesToFirstLine_51) {
    Column col("This is a test text for initial indent verification");
    col.width(40).initialIndent(6);
    auto it = col.begin();
    if (it != col.end()) {
        std::string firstLine = *it;
        EXPECT_GE(firstLine.size(), 6u);
        EXPECT_EQ(firstLine.substr(0, 6), "      ");
    }
}

// ==================== Output Stream Tests ====================

TEST_F(ColumnTest_51, OutputStreamOperator_51) {
    Column col("Hello World");
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

TEST_F(ColumnTest_51, OutputStreamWithWrapping_51) {
    Column col("Short text here and more words that will cause wrapping");
    col.width(15);
    std::ostringstream oss;
    oss << col;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Should contain newlines due to wrapping
    EXPECT_NE(output.find('\n'), std::string::npos);
}

TEST_F(ColumnTest_51, OutputStreamEmptyString_51) {
    Column col("");
    std::ostringstream oss;
    oss << col;
    // Should not crash, output may be empty or a newline
    // Just verify it doesn't throw
}

// ==================== Columns (operator+) Tests ====================

TEST_F(ColumnTest_51, ColumnPlusColumnCreatesColumns_51) {
    Column col1("Left side");
    Column col2("Right side");
    auto columns = col1 + col2;
    std::ostringstream oss;
    oss << columns;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left side"), std::string::npos);
    EXPECT_NE(output.find("Right side"), std::string::npos);
}

TEST_F(ColumnTest_51, ColumnPlusColumnRValueCreatesColumns_51) {
    auto columns = Column("Left") + Column("Right");
    std::ostringstream oss;
    oss << columns;
    std::string output = oss.str();
    EXPECT_NE(output.find("Left"), std::string::npos);
    EXPECT_NE(output.find("Right"), std::string::npos);
}

// ==================== Boundary Conditions ====================

TEST_F(ColumnTest_51, SingleCharacterString_51) {
    Column col("A");
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        EXPECT_EQ(*it, "A");
        ++count;
    }
    EXPECT_EQ(count, 1);
}

TEST_F(ColumnTest_51, StringExactlyWidthLength_51) {
    std::string text(79, 'x');
    Column col(text);
    col.width(79);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 1);
}

TEST_F(ColumnTest_51, StringOneCharLongerThanWidth_51) {
    // A string of continuous chars longer than width
    // With no spaces, behavior depends on implementation
    std::string text(80, 'x');
    Column col(text);
    col.width(79);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GE(count, 1);
}

TEST_F(ColumnTest_51, ZeroIndent_51) {
    Column col("test text");
    col.indent(0);
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string line = *it;
    EXPECT_EQ(line[0], 't');
}

TEST_F(ColumnTest_51, MultipleSpacesInText_51) {
    Column col("word1  word2  word3");
    col.width(79);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GE(count, 1);
}

TEST_F(ColumnTest_51, NewlineInText_51) {
    Column col("line1\nline2\nline3");
    col.width(79);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
    }
    EXPECT_GE(count, 3);
}

TEST_F(ColumnTest_51, VeryNarrowWidth_51) {
    Column col("Hello World");
    col.width(5);
    int count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        EXPECT_LE(line.size(), 5u);
        ++count;
    }
    EXPECT_GE(count, 2);
}

TEST_F(ColumnTest_51, IndentAndInitialIndentTogether_51) {
    Column col("This text should demonstrate both initial and regular indent effects across lines");
    col.width(30).indent(4).initialIndent(8);
    int lineNum = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        if (lineNum == 0) {
            EXPECT_GE(line.size(), 8u);
            EXPECT_EQ(line.substr(0, 8), "        ");
        } else {
            EXPECT_GE(line.size(), 4u);
            EXPECT_EQ(line.substr(0, 4), "    ");
        }
        ++lineNum;
    }
}

TEST_F(ColumnTest_51, RangeBasedForLoop_51) {
    Column col("Test for range-based for loop");
    int count = 0;
    for (const auto& line : col) {
        EXPECT_FALSE(line.empty());
        ++count;
    }
    EXPECT_GE(count, 1);
}
