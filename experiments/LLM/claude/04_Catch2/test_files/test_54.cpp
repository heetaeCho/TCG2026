#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch::TextFlow;

class ColumnsIteratorTest_54 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an empty Columns object produces begin() == end()
TEST_F(ColumnsIteratorTest_54, EmptyColumnsBeginEqualsEnd_54) {
    Columns cols;
    auto begin = cols.begin();
    auto end = cols.end();
    EXPECT_FALSE(begin != end);
}

// Test that a single column with text produces begin() != end()
TEST_F(ColumnsIteratorTest_54, SingleColumnBeginNotEqualsEnd_54) {
    Column col = Column("Hello World");
    Columns cols = col;
    auto begin = cols.begin();
    auto end = cols.end();
    EXPECT_TRUE(begin != end);
}

// Test that iterating through a single column eventually reaches end
TEST_F(ColumnsIteratorTest_54, SingleColumnIterationReachesEnd_54) {
    Column col = Column("Hello World");
    Columns cols = col;
    auto it = cols.begin();
    auto end = cols.end();
    int count = 0;
    while (it != end) {
        ++it;
        ++count;
        // Safety limit to prevent infinite loop
        if (count > 1000) break;
    }
    EXPECT_FALSE(it != end);
    EXPECT_LE(count, 1000);
}

// Test that dereferencing the iterator produces a non-empty string
TEST_F(ColumnsIteratorTest_54, DereferenceProducesNonEmptyString_54) {
    Column col = Column("Hello World");
    Columns cols = col;
    auto it = cols.begin();
    auto end = cols.end();
    ASSERT_TRUE(it != end);
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

// Test that two end iterators are equal (not !=)
TEST_F(ColumnsIteratorTest_54, TwoEndIteratorsAreEqual_54) {
    Columns cols;
    auto end1 = cols.end();
    auto end2 = cols.end();
    EXPECT_FALSE(end1 != end2);
}

// Test that two begin iterators from the same Columns are equal
TEST_F(ColumnsIteratorTest_54, TwoBeginIteratorsAreEqual_54) {
    Column col = Column("Test");
    Columns cols = col;
    auto begin1 = cols.begin();
    auto begin2 = cols.begin();
    EXPECT_FALSE(begin1 != begin2);
}

// Test post-increment operator returns previous state
TEST_F(ColumnsIteratorTest_54, PostIncrementReturnsPreviousValue_54) {
    Column col = Column("Hello World this is a long text that should span multiple lines when width is small");
    col = col.width(10);
    Columns cols = col;
    auto it = cols.begin();
    auto end = cols.end();
    
    if (it != end) {
        std::string before = *it;
        auto old = it++;
        std::string oldStr = *old;
        EXPECT_EQ(before, oldStr);
    }
}

// Test multiple columns combined produce output
TEST_F(ColumnsIteratorTest_54, MultipleColumnsCombined_54) {
    Column col1 = Column("Left");
    Column col2 = Column("Right");
    col1 = col1.width(20);
    col2 = col2.width(20);
    Columns cols = col1 + col2;
    
    auto it = cols.begin();
    auto end = cols.end();
    ASSERT_TRUE(it != end);
    std::string line = *it;
    EXPECT_FALSE(line.empty());
}

// Test iterator with long text that wraps
TEST_F(ColumnsIteratorTest_54, LongTextWrapsMultipleLines_54) {
    Column col = Column("This is a very long text that should definitely wrap across multiple lines given a small width constraint");
    col = col.width(15);
    Columns cols = col;
    
    auto it = cols.begin();
    auto end = cols.end();
    int lineCount = 0;
    while (it != end) {
        ++it;
        ++lineCount;
        if (lineCount > 1000) break;
    }
    EXPECT_GT(lineCount, 1);
}

// Test that an iterator is not equal to end before full traversal
TEST_F(ColumnsIteratorTest_54, IteratorNotEqualToEndDuringTraversal_54) {
    Column col = Column("Line one\nLine two\nLine three");
    Columns cols = col;
    
    auto it = cols.begin();
    auto end = cols.end();
    
    if (it != end) {
        EXPECT_TRUE(it != end);
        ++it;
        // May or may not be at end, but we can still check the operator works
    }
}

// Test with newline characters in text
TEST_F(ColumnsIteratorTest_54, TextWithNewlines_54) {
    Column col = Column("Line1\nLine2\nLine3");
    Columns cols = col;
    
    auto it = cols.begin();
    auto end = cols.end();
    int lineCount = 0;
    while (it != end) {
        std::string line = *it;
        ++it;
        ++lineCount;
        if (lineCount > 1000) break;
    }
    EXPECT_GE(lineCount, 3);
}

// Test with empty string column
TEST_F(ColumnsIteratorTest_54, EmptyStringColumn_54) {
    Column col = Column("");
    Columns cols = col;
    
    auto it = cols.begin();
    auto end = cols.end();
    // An empty string column might produce 0 or 1 lines
    int lineCount = 0;
    while (it != end) {
        ++it;
        ++lineCount;
        if (lineCount > 1000) break;
    }
    EXPECT_LE(lineCount, 1000);
}

// Test operator!= is consistent with traversal
TEST_F(ColumnsIteratorTest_54, NotEqualConsistentWithTraversal_54) {
    Column col = Column("abc");
    Columns cols = col;
    
    auto it = cols.begin();
    auto end = cols.end();
    
    bool wasNotEqual = (it != end);
    while (it != end) {
        ++it;
    }
    bool isNowEqual = !(it != end);
    
    if (wasNotEqual) {
        EXPECT_TRUE(isNowEqual);
    }
}
