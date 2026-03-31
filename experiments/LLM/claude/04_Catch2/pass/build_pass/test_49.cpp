#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using Catch::TextFlow::Column;

class ColumnTest_49 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Column can be constructed with a string
TEST_F(ColumnTest_49, ConstructWithString_49) {
    Column col("Hello, World!");
    // Should be constructible without throwing
    EXPECT_NO_THROW(Column("test string"));
}

// Test that Column can be constructed with an empty string
TEST_F(ColumnTest_49, ConstructWithEmptyString_49) {
    EXPECT_NO_THROW(Column(""));
}

// Test that default width is 79 (CATCH_CONFIG_CONSOLE_WIDTH 80 - 1)
TEST_F(ColumnTest_49, DefaultWidth_49) {
    Column col("test");
    EXPECT_EQ(col.width(), 79u);
}

// Test that width setter changes the width
TEST_F(ColumnTest_49, SetWidth_49) {
    Column col("test");
    col.width(40);
    EXPECT_EQ(col.width(), 40u);
}

// Test that width setter returns reference for chaining
TEST_F(ColumnTest_49, WidthReturnsSelfReference_49) {
    Column col("test");
    Column& ref = col.width(50);
    EXPECT_EQ(&ref, &col);
}

// Test that indent setter returns reference for chaining
TEST_F(ColumnTest_49, IndentReturnsSelfReference_49) {
    Column col("test");
    Column& ref = col.indent(4);
    EXPECT_EQ(&ref, &col);
}

// Test that initialIndent setter returns reference for chaining
TEST_F(ColumnTest_49, InitialIndentReturnsSelfReference_49) {
    Column col("test");
    Column& ref = col.initialIndent(4);
    EXPECT_EQ(&ref, &col);
}

// Test that chaining multiple setters works
TEST_F(ColumnTest_49, ChainingSetters_49) {
    Column col("test");
    Column& ref = col.width(40).indent(2).initialIndent(4);
    EXPECT_EQ(&ref, &col);
    EXPECT_EQ(col.width(), 40u);
}

// Test that begin and end iterators work for iteration
TEST_F(ColumnTest_49, BeginEndIteration_49) {
    Column col("Hello");
    col.width(79);
    int lineCount = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        lineCount++;
    }
    EXPECT_GE(lineCount, 1);
}

// Test iteration with range-based for loop (implicitly uses begin/end)
TEST_F(ColumnTest_49, RangeBasedForLoop_49) {
    Column col("Hello World");
    int lineCount = 0;
    for (const auto& line : col) {
        (void)line;
        lineCount++;
    }
    EXPECT_GE(lineCount, 1);
}

// Test that short text produces a single line
TEST_F(ColumnTest_49, ShortTextSingleLine_49) {
    Column col("Hello");
    col.width(79);
    int lineCount = 0;
    for (const auto& line : col) {
        (void)line;
        lineCount++;
    }
    EXPECT_EQ(lineCount, 1);
}

// Test that long text wraps into multiple lines
TEST_F(ColumnTest_49, LongTextWraps_49) {
    std::string longText = "This is a very long text that should be wrapped into multiple lines when the column width is set to a small value";
    Column col(longText);
    col.width(20);
    int lineCount = 0;
    for (const auto& line : col) {
        (void)line;
        lineCount++;
    }
    EXPECT_GT(lineCount, 1);
}

// Test that each wrapped line respects the width constraint
TEST_F(ColumnTest_49, WrappedLinesRespectWidth_49) {
    std::string text = "This is a test string that should wrap properly within the given width constraint for each line";
    Column col(text);
    col.width(30);
    for (const auto& line : col) {
        // Lines should not exceed the width (though they may be shorter)
        // Note: actual string length may include indent but should not exceed width
        EXPECT_LE(line.size(), 30u);
    }
}

// Test that indent adds spaces to subsequent lines
TEST_F(ColumnTest_49, IndentApplied_49) {
    std::string text = "word word word word word word word word word word";
    Column col(text);
    col.width(20).indent(4);
    int lineNum = 0;
    for (const auto& line : col) {
        if (lineNum > 0) {
            // Subsequent lines should start with spaces (indent)
            EXPECT_GE(line.size(), 4u);
            for (size_t i = 0; i < 4 && i < line.size(); ++i) {
                EXPECT_EQ(line[i], ' ');
            }
        }
        lineNum++;
    }
}

// Test initialIndent affects the first line
TEST_F(ColumnTest_49, InitialIndentApplied_49) {
    std::string text = "word word word word word word word word word word";
    Column col(text);
    col.width(30).initialIndent(6);
    auto it = col.begin();
    if (it != col.end()) {
        std::string firstLine = *it;
        EXPECT_GE(firstLine.size(), 6u);
        for (size_t i = 0; i < 6 && i < firstLine.size(); ++i) {
            EXPECT_EQ(firstLine[i], ' ');
        }
    }
}

// Test that ostream operator<< works
TEST_F(ColumnTest_49, StreamOperator_49) {
    Column col("Hello World");
    col.width(79);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

// Test empty string column produces output (at least empty or one line)
TEST_F(ColumnTest_49, EmptyStringColumn_49) {
    Column col("");
    std::ostringstream oss;
    oss << col;
    // Empty column should produce some output (possibly empty or newline)
    // Just ensure it doesn't crash
    SUCCEED();
}

// Test operator+ combining two columns
TEST_F(ColumnTest_49, ColumnAddition_49) {
    Column left("Left column text");
    Column right("Right column text");
    left.width(30);
    right.width(30);
    auto columns = left + right;
    std::ostringstream oss;
    oss << columns;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test setting width to 1 (boundary condition)
TEST_F(ColumnTest_49, MinimalWidth_49) {
    Column col("ab cd ef");
    col.width(1);
    // Should not crash, and should produce output
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << col);
}

// Test setting width to very large value
TEST_F(ColumnTest_49, VeryLargeWidth_49) {
    Column col("Hello World");
    col.width(10000);
    EXPECT_EQ(col.width(), 10000u);
    int lineCount = 0;
    for (const auto& line : col) {
        (void)line;
        lineCount++;
    }
    EXPECT_EQ(lineCount, 1);
}

// Test setting indent to 0
TEST_F(ColumnTest_49, ZeroIndent_49) {
    Column col("Hello World");
    col.indent(0);
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << col);
}

// Test setting initialIndent to 0
TEST_F(ColumnTest_49, ZeroInitialIndent_49) {
    Column col("Hello World");
    col.initialIndent(0);
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << col);
}

// Test move construction of Column
TEST_F(ColumnTest_49, MoveConstruction_49) {
    std::string text = "movable text";
    Column col(std::move(text));
    std::ostringstream oss;
    oss << col;
    EXPECT_NE(oss.str().find("movable text"), std::string::npos);
}

// Test that multiple words wrapping preserves content
TEST_F(ColumnTest_49, ContentPreservedAfterWrapping_49) {
    std::string text = "alpha beta gamma delta";
    Column col(text);
    col.width(15);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_NE(result.find("alpha"), std::string::npos);
    EXPECT_NE(result.find("beta"), std::string::npos);
    EXPECT_NE(result.find("gamma"), std::string::npos);
    EXPECT_NE(result.find("delta"), std::string::npos);
}

// Test operator+ with rvalue columns
TEST_F(ColumnTest_49, ColumnAdditionRvalue_49) {
    auto columns = Column("Left").width(30) + Column("Right").width(30);
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << columns);
}

// Test that setting width after other settings works
TEST_F(ColumnTest_49, SetWidthAfterOtherSettings_49) {
    Column col("test text here");
    col.indent(2).initialIndent(4).width(25);
    EXPECT_EQ(col.width(), 25u);
}

// Test with text containing newlines
TEST_F(ColumnTest_49, TextWithNewlines_49) {
    Column col("line one\nline two\nline three");
    col.width(79);
    int lineCount = 0;
    for (const auto& line : col) {
        (void)line;
        lineCount++;
    }
    // Should have at least 3 lines due to embedded newlines
    EXPECT_GE(lineCount, 3);
}

// Test with a single very long word that exceeds width
TEST_F(ColumnTest_49, SingleLongWord_49) {
    std::string longWord(100, 'x');
    Column col(longWord);
    col.width(20);
    // Should not crash
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << col);
    EXPECT_FALSE(oss.str().empty());
}
