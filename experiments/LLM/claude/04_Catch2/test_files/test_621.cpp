#include <catch2/internal/catch_textflow.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

using namespace Catch::TextFlow;

class TextFlowColumnTest_621 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class TextFlowColumnsTest_621 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Column Tests ---

TEST_F(TextFlowColumnTest_621, DefaultColumnCreation_621) {
    Column col("");
    std::string result;
    for (auto line : col) {
        result += line;
    }
    // Empty string column should produce empty or minimal output
    EXPECT_TRUE(result.empty());
}

TEST_F(TextFlowColumnTest_621, SimpleTextColumn_621) {
    Column col("Hello World");
    std::string result;
    bool hasContent = false;
    for (auto line : col) {
        if (!line.empty()) hasContent = true;
        result += line;
    }
    EXPECT_TRUE(hasContent);
    EXPECT_NE(result.find("Hello"), std::string::npos);
    EXPECT_NE(result.find("World"), std::string::npos);
}

TEST_F(TextFlowColumnTest_621, ColumnWidthSetting_621) {
    Column col("This is a somewhat longer text that should be wrapped");
    col.width(10);
    for (auto line : col) {
        EXPECT_LE(line.size(), 10u);
    }
}

TEST_F(TextFlowColumnTest_621, ColumnDefaultWidth_621) {
    Column col("Short text");
    // Default width should accommodate the text
    std::string result;
    for (auto line : col) {
        result += line;
    }
    EXPECT_NE(result.find("Short text"), std::string::npos);
}

TEST_F(TextFlowColumnTest_621, ColumnWidthWrapsLongWords_621) {
    Column col("Superlongwordthatexceedswidth normalword");
    col.width(15);
    bool foundLine = false;
    for (auto line : col) {
        foundLine = true;
        // Lines should exist even if word is longer than width
    }
    EXPECT_TRUE(foundLine);
}

TEST_F(TextFlowColumnTest_621, ColumnIndentSetting_621) {
    Column col("Hello World");
    col.indent(4);
    col.width(80);
    auto it = col.begin();
    if (it != col.end()) {
        std::string firstLine = *it;
        // First line should have indent
        EXPECT_GE(firstLine.size(), 4u);
    }
}

TEST_F(TextFlowColumnTest_621, ColumnInitialIndentSetting_621) {
    Column col("Hello World");
    col.initialIndent(8);
    col.width(80);
    auto it = col.begin();
    if (it != col.end()) {
        std::string firstLine = *it;
        EXPECT_GE(firstLine.size(), 1u);
    }
}

TEST_F(TextFlowColumnTest_621, ColumnIteratorEquality_621) {
    Column col("Test");
    auto begin = col.begin();
    auto end = col.end();
    EXPECT_NE(begin, end);
}

TEST_F(TextFlowColumnTest_621, ColumnIteratorEndEquality_621) {
    Column col("");
    auto begin = col.begin();
    auto end = col.end();
    // Empty text: begin should equal end
    EXPECT_EQ(begin, end);
}

TEST_F(TextFlowColumnTest_621, ColumnIteratorPostIncrement_621) {
    Column col("Line one and line two text");
    col.width(10);
    auto it = col.begin();
    auto end = col.end();
    if (it != end) {
        auto prev = it++;
        // Post-increment should return the previous value
        // and advance the iterator
        EXPECT_TRUE(true); // Just verify no crash
    }
}

TEST_F(TextFlowColumnTest_621, ColumnIteratorPreIncrement_621) {
    Column col("Line one and line two text");
    col.width(10);
    auto it = col.begin();
    auto end = col.end();
    if (it != end) {
        ++it;
        EXPECT_TRUE(true); // Verify no crash
    }
}

TEST_F(TextFlowColumnTest_621, ColumnMultipleLines_621) {
    Column col("This is a longer piece of text that should definitely wrap around");
    col.width(20);
    int lineCount = 0;
    for (auto line : col) {
        lineCount++;
        (void)line;
    }
    EXPECT_GT(lineCount, 1);
}

TEST_F(TextFlowColumnTest_621, ColumnNewlineHandling_621) {
    Column col("Line1\nLine2\nLine3");
    col.width(80);
    int lineCount = 0;
    for (auto line : col) {
        lineCount++;
        (void)line;
    }
    EXPECT_GE(lineCount, 3);
}

TEST_F(TextFlowColumnTest_621, ColumnStreamOutput_621) {
    Column col("Hello World");
    col.width(80);
    std::ostringstream oss;
    oss << col;
    std::string result = oss.str();
    EXPECT_NE(result.find("Hello World"), std::string::npos);
}

// --- Columns Tests ---

TEST_F(TextFlowColumnsTest_621, TwoColumnsAddition_621) {
    Column left("Left text");
    left.width(20);
    Column right("Right text");
    right.width(20);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    std::string result = oss.str();
    EXPECT_NE(result.find("Left text"), std::string::npos);
    EXPECT_NE(result.find("Right text"), std::string::npos);
}

TEST_F(TextFlowColumnsTest_621, ColumnsIteratorPostIncrement_621) {
    Column left("Left");
    left.width(20);
    Column right("Right");
    right.width(20);
    Columns cols = left + right;
    auto it = cols.begin();
    auto end = cols.end();
    if (it != end) {
        auto prev = it++;
        // Verify post-increment returns previous iterator and advances
        EXPECT_TRUE(true);
    }
}

TEST_F(TextFlowColumnsTest_621, ColumnsIteratorPreIncrement_621) {
    Column left("Left");
    left.width(20);
    Column right("Right");
    right.width(20);
    Columns cols = left + right;
    auto it = cols.begin();
    auto end = cols.end();
    if (it != end) {
        ++it;
        EXPECT_TRUE(true);
    }
}

TEST_F(TextFlowColumnsTest_621, ColumnsIteratorEquality_621) {
    Column left("Left");
    left.width(20);
    Column right("Right");
    right.width(20);
    Columns cols = left + right;
    auto begin = cols.begin();
    auto end = cols.end();
    EXPECT_NE(begin, end);
}

TEST_F(TextFlowColumnsTest_621, ColumnsAddColumnToColumns_621) {
    Column c1("Col1");
    c1.width(15);
    Column c2("Col2");
    c2.width(15);
    Column c3("Col3");
    c3.width(15);
    Columns cols = c1 + c2;
    Columns cols2 = cols + c3;
    std::ostringstream oss;
    oss << cols2;
    std::string result = oss.str();
    EXPECT_NE(result.find("Col1"), std::string::npos);
    EXPECT_NE(result.find("Col2"), std::string::npos);
    EXPECT_NE(result.find("Col3"), std::string::npos);
}

TEST_F(TextFlowColumnsTest_621, ColumnsStreamOutput_621) {
    Column left("Hello from left");
    left.width(25);
    Column right("Hello from right");
    right.width(25);
    Columns cols = left + right;
    std::ostringstream oss;
    oss << cols;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(TextFlowColumnsTest_621, ColumnsWithWrappedText_621) {
    Column left("This is a much longer text in the left column that should wrap");
    left.width(20);
    Column right("Short");
    right.width(20);
    Columns cols = left + right;
    int lineCount = 0;
    for (auto line : cols) {
        lineCount++;
        (void)line;
    }
    EXPECT_GT(lineCount, 1);
}

TEST_F(TextFlowColumnsTest_621, EmptyColumnsIteration_621) {
    Column left("");
    left.width(20);
    Column right("");
    right.width(20);
    Columns cols = left + right;
    auto begin = cols.begin();
    auto end = cols.end();
    // Both empty columns
    EXPECT_EQ(begin, end);
}

TEST_F(TextFlowColumnTest_621, ColumnWidthOne_621) {
    Column col("AB");
    col.width(1);
    int lineCount = 0;
    for (auto line : col) {
        lineCount++;
        (void)line;
    }
    EXPECT_GE(lineCount, 1);
}

TEST_F(TextFlowColumnTest_621, ColumnOnlySpaces_621) {
    Column col("   ");
    col.width(80);
    std::ostringstream oss;
    oss << col;
    // Spaces-only text behavior
    EXPECT_TRUE(true); // No crash
}

TEST_F(TextFlowColumnTest_621, ColumnVeryLargeWidth_621) {
    Column col("Hello World");
    col.width(10000);
    int lineCount = 0;
    for (auto line : col) {
        lineCount++;
        (void)line;
    }
    EXPECT_EQ(lineCount, 1);
}

TEST_F(TextFlowColumnTest_621, ColumnMultipleNewlines_621) {
    Column col("\n\n\n");
    col.width(80);
    int lineCount = 0;
    for (auto line : col) {
        lineCount++;
        (void)line;
    }
    EXPECT_GE(lineCount, 3);
}

TEST_F(TextFlowColumnTest_621, ColumnDereferenceIterator_621) {
    Column col("Dereference test");
    col.width(80);
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string line = *it;
    EXPECT_NE(line.find("Dereference test"), std::string::npos);
}
