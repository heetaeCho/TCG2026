#include <catch2/internal/catch_textflow.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

using namespace Catch::TextFlow;

class TextFlowColumnTest_616 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a Column can be created with default settings
TEST_F(TextFlowColumnTest_616, DefaultColumnCreation_616) {
    Column col("Hello World");
    EXPECT_NO_THROW({
        auto it = col.begin();
        auto end = col.end();
    });
}

// Test that iterating over a simple single-line string yields the string
TEST_F(TextFlowColumnTest_616, SingleLineIteration_616) {
    Column col("Hello");
    col.width(80);
    auto it = col.begin();
    auto end = col.end();
    ASSERT_NE(it, end);
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

// Test that an empty string column works
TEST_F(TextFlowColumnTest_616, EmptyStringColumn_616) {
    Column col("");
    col.width(80);
    // Even empty string should be iterable
    auto it = col.begin();
    auto end = col.end();
    // Implementation may or may not produce lines for empty string
    // Just ensure no crash
    EXPECT_NO_THROW({
        while (it != end) {
            std::string line = *it;
            ++it;
        }
    });
}

// Test that post-increment returns previous iterator value
TEST_F(TextFlowColumnTest_616, PostIncrementReturnsPrevious_616) {
    Column col("Hello World this is a long line that should wrap");
    col.width(10);
    auto it = col.begin();
    auto end = col.end();
    
    if (it != end) {
        std::string firstLine = *it;
        auto prev = it++;
        std::string prevLine = *prev;
        EXPECT_EQ(firstLine, prevLine);
    }
}

// Test that post-increment advances the iterator
TEST_F(TextFlowColumnTest_616, PostIncrementAdvancesIterator_616) {
    Column col("Hello World this is a test");
    col.width(10);
    auto it = col.begin();
    auto end = col.end();
    
    if (it != end) {
        std::string firstLine = *it;
        it++;
        if (it != end) {
            std::string secondLine = *it;
            // After post-increment, should be on next line (which should differ if wrapping)
            // We can at least confirm we got a non-empty string
            EXPECT_FALSE(secondLine.empty());
        }
    }
}

// Test that pre-increment and post-increment reach the same end
TEST_F(TextFlowColumnTest_616, PreAndPostIncrementReachSameEnd_616) {
    std::string text = "Short text to wrap around in a column display";
    
    Column col1(text);
    col1.width(15);
    Column col2(text);
    col2.width(15);
    
    int countPre = 0;
    for (auto it = col1.begin(); it != col1.end(); ++it) {
        countPre++;
    }
    
    int countPost = 0;
    for (auto it = col2.begin(); it != col2.end(); it++) {
        countPost++;
    }
    
    EXPECT_EQ(countPre, countPost);
}

// Test that setting a narrow width causes wrapping (more lines)
TEST_F(TextFlowColumnTest_616, NarrowWidthCausesWrapping_616) {
    std::string text = "This is a reasonably long sentence for testing";
    
    Column wideCol(text);
    wideCol.width(200);
    
    Column narrowCol(text);
    narrowCol.width(10);
    
    int wideCount = 0;
    for (auto it = wideCol.begin(); it != wideCol.end(); ++it) {
        wideCount++;
    }
    
    int narrowCount = 0;
    for (auto it = narrowCol.begin(); it != narrowCol.end(); ++it) {
        narrowCount++;
    }
    
    EXPECT_GE(narrowCount, wideCount);
}

// Test Column width setting and chaining
TEST_F(TextFlowColumnTest_616, ColumnWidthChaining_616) {
    Column col("test");
    EXPECT_NO_THROW({
        col.width(40);
    });
}

// Test iterator equality
TEST_F(TextFlowColumnTest_616, IteratorEquality_616) {
    Column col("Hello");
    col.width(80);
    auto it1 = col.begin();
    auto it2 = col.begin();
    EXPECT_EQ(it1, it2);
}

// Test that end iterators are equal
TEST_F(TextFlowColumnTest_616, EndIteratorEquality_616) {
    Column col("Hello");
    col.width(80);
    auto end1 = col.end();
    auto end2 = col.end();
    EXPECT_EQ(end1, end2);
}

// Test streaming a column to ostream
TEST_F(TextFlowColumnTest_616, ColumnStreamOutput_616) {
    Column col("Hello World");
    col.width(80);
    std::ostringstream oss;
    EXPECT_NO_THROW({
        oss << col;
    });
    EXPECT_FALSE(oss.str().empty());
}

// Test that lines respect column width
TEST_F(TextFlowColumnTest_616, LinesRespectWidth_616) {
    const size_t width = 20;
    Column col("This is a fairly long string that should be wrapped according to the width");
    col.width(width);
    
    for (auto it = col.begin(); it != col.end(); ++it) {
        std::string line = *it;
        // Each line should not exceed the specified width
        EXPECT_LE(line.size(), width);
    }
}

// Test with a single very long word
TEST_F(TextFlowColumnTest_616, SingleLongWord_616) {
    Column col("Supercalifragilisticexpialidocious");
    col.width(10);
    
    int count = 0;
    EXPECT_NO_THROW({
        for (auto it = col.begin(); it != col.end(); ++it) {
            count++;
            // Prevent infinite loop in test
            if (count > 100) break;
        }
    });
    EXPECT_GT(count, 0);
}

// Test indent
TEST_F(TextFlowColumnTest_616, ColumnIndent_616) {
    Column col("Hello World");
    col.width(80);
    EXPECT_NO_THROW({
        col.indent(4);
    });
    
    auto it = col.begin();
    if (it != col.end()) {
        std::string line = *it;
        // Indented line should start with spaces
        EXPECT_GE(line.size(), 4u);
    }
}
