#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

class ColumnsIteratorTest_53 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed Columns object has begin() == end()
TEST_F(ColumnsIteratorTest_53, EmptyColumnsBeginEqualsEnd_53) {
    Columns cols;
    auto beginIt = cols.begin();
    auto endIt = cols.end();
    EXPECT_TRUE(beginIt == endIt);
}

// Test that begin() != end() is false for empty columns
TEST_F(ColumnsIteratorTest_53, EmptyColumnsBeginNotEqualEndIsFalse_53) {
    Columns cols;
    auto beginIt = cols.begin();
    auto endIt = cols.end();
    EXPECT_FALSE(beginIt != endIt);
}

// Test that a single column with text produces begin() != end()
TEST_F(ColumnsIteratorTest_53, SingleColumnWithTextBeginNotEqualsEnd_53) {
    Column col = Column("Hello World");
    Columns cols = col;
    auto beginIt = cols.begin();
    auto endIt = cols.end();
    EXPECT_TRUE(beginIt != endIt);
    EXPECT_FALSE(beginIt == endIt);
}

// Test iterator equality: same iterator equals itself
TEST_F(ColumnsIteratorTest_53, IteratorEqualsSelf_53) {
    Column col = Column("Test");
    Columns cols = col;
    auto it = cols.begin();
    EXPECT_TRUE(it == it);
}

// Test that end iterators are equal
TEST_F(ColumnsIteratorTest_53, EndIteratorsAreEqual_53) {
    Column col = Column("Test");
    Columns cols = col;
    auto end1 = cols.end();
    auto end2 = cols.end();
    EXPECT_TRUE(end1 == end2);
}

// Test dereferencing the begin iterator of a single column
TEST_F(ColumnsIteratorTest_53, DereferenceBeginIteratorSingleColumn_53) {
    Column col = Column("Hello");
    Columns cols = col;
    auto it = cols.begin();
    std::string result = *it;
    EXPECT_FALSE(result.empty());
}

// Test that incrementing through all lines eventually reaches end
TEST_F(ColumnsIteratorTest_53, IncrementToEnd_53) {
    Column col = Column("Short text");
    Columns cols = col;
    auto it = cols.begin();
    auto endIt = cols.end();
    int count = 0;
    while (it != endIt) {
        ++it;
        ++count;
        // Safety guard to prevent infinite loop in test
        if (count > 1000) break;
    }
    EXPECT_TRUE(it == endIt);
    EXPECT_GT(count, 0);
}

// Test post-increment operator
TEST_F(ColumnsIteratorTest_53, PostIncrementOperator_53) {
    Column col = Column("Some text here");
    Columns cols = col;
    auto it = cols.begin();
    auto endIt = cols.end();
    if (it != endIt) {
        auto prev = it++;
        // prev should not equal the incremented iterator (unless single line that reached end)
        // At minimum, this should not crash
        SUCCEED();
    }
}

// Test multiple columns combined
TEST_F(ColumnsIteratorTest_53, MultipleColumnsCombined_53) {
    Column col1 = Column("Left column text").width(20);
    Column col2 = Column("Right column text").width(20);
    Columns cols = col1 + col2;
    auto it = cols.begin();
    auto endIt = cols.end();
    EXPECT_TRUE(it != endIt);
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

// Test iterating through multiple columns fully
TEST_F(ColumnsIteratorTest_53, IterateThroughMultipleColumns_53) {
    Column col1 = Column("Hello").width(10);
    Column col2 = Column("World").width(10);
    Columns cols = col1 + col2;
    int count = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        std::string line = *it;
        ++count;
        if (count > 1000) break;
    }
    EXPECT_GT(count, 0);
}

// Test that two different begin iterators from the same Columns are equal
TEST_F(ColumnsIteratorTest_53, TwoBeginIteratorsAreEqual_53) {
    Column col = Column("Test text");
    Columns cols = col;
    auto begin1 = cols.begin();
    auto begin2 = cols.begin();
    EXPECT_TRUE(begin1 == begin2);
}

// Test long text that wraps across multiple lines
TEST_F(ColumnsIteratorTest_53, LongTextWrapsMultipleLines_53) {
    std::string longText = "This is a very long text that should definitely wrap across multiple lines when rendered in a narrow column width.";
    Column col = Column(longText).width(20);
    Columns cols = col;
    int lineCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        ++lineCount;
        if (lineCount > 1000) break;
    }
    EXPECT_GT(lineCount, 1);
}

// Test inequality operator is consistent with equality
TEST_F(ColumnsIteratorTest_53, InequalityConsistentWithEquality_53) {
    Column col = Column("Text");
    Columns cols = col;
    auto begin = cols.begin();
    auto end = cols.end();
    EXPECT_TRUE((begin == end) != (begin != end));
}

// Test empty string column
TEST_F(ColumnsIteratorTest_53, EmptyStringColumn_53) {
    Column col = Column("");
    Columns cols = col;
    auto it = cols.begin();
    auto endIt = cols.end();
    // Empty string may or may not produce lines - just ensure no crash
    int count = 0;
    while (it != endIt) {
        std::string line = *it;
        ++it;
        ++count;
        if (count > 1000) break;
    }
    SUCCEED();
}

// Test column with newlines
TEST_F(ColumnsIteratorTest_53, ColumnWithNewlines_53) {
    Column col = Column("Line1\nLine2\nLine3");
    Columns cols = col;
    int lineCount = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        std::string line = *it;
        ++lineCount;
        if (lineCount > 1000) break;
    }
    EXPECT_GE(lineCount, 3);
}

// Test three columns combined
TEST_F(ColumnsIteratorTest_53, ThreeColumnsCombined_53) {
    Column col1 = Column("A").width(10);
    Column col2 = Column("B").width(10);
    Column col3 = Column("C").width(10);
    Columns cols = col1 + col2 + col3;
    auto it = cols.begin();
    EXPECT_TRUE(it != cols.end());
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}
