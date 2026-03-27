// ColumnIterator_615_tests.cpp
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

class ColumnIteratorTest_615 : public ::testing::Test {
protected:
    // Make formatting side-effects (wrapping/indent) unlikely to interfere
    // with our observable expectations.
    static Column Prepare(std::string text) {
        Column c(std::move(text));
        // Force generous width and zero indents to keep dereferenced lines simple.
        c.width(1000).indent(0).initialIndent(0);
        return c;
    }
};

// Normal operation: single line should be produced as a single dereference.
TEST_F(ColumnIteratorTest_615, IteratesSingleLine_615) {
    auto col = Prepare("Hello world");
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string first = *it;
    EXPECT_NE(first.size(), 0u);
    EXPECT_EQ(first.rfind("Hello world", 0), 0u) << "Line should start with the original text";
    ++it;
    EXPECT_EQ(it, col.end());
}

// Normal operation: pre-increment moves from first to second logical line.
TEST_F(ColumnIteratorTest_615, PreIncrementMovesToNextLine_615) {
    auto col = Prepare("Line1\nLine2");
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string l1 = *it;

    ++it; // move to next line
    ASSERT_NE(it, col.end());
    std::string l2 = *it;

    EXPECT_EQ(l1.rfind("Line1", 0), 0u);
    EXPECT_EQ(l2.rfind("Line2", 0), 0u) << "Next line should start at 'L' (no stray newline at front)";
}

// Boundary: whitespace after a newline should not appear at the start of the next produced line.
TEST_F(ColumnIteratorTest_615, SkipsLeadingSpacesAfterNewline_615) {
    auto col = Prepare("A\n   B");
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string a = *it;
    EXPECT_EQ(a.rfind("A", 0), 0u);

    ++it;
    ASSERT_NE(it, col.end());
    std::string b = *it;

    // Validate that returned next line does not start with whitespace.
    ASSERT_FALSE(b.empty());
    EXPECT_NE(b[0], ' ') << "Iterator should skip leading spaces after newline";
    EXPECT_EQ(b.rfind("B", 0), 0u);
}

// Boundary: mixed whitespace (spaces + tabs) after newline is skipped.
TEST_F(ColumnIteratorTest_615, SkipsMixedWhitespaceAfterNewline_615) {
    auto col = Prepare("A\n \t  B");
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string a = *it;
    EXPECT_EQ(a.rfind("A", 0), 0u);

    ++it;
    ASSERT_NE(it, col.end());
    std::string b = *it;

    ASSERT_FALSE(b.empty());
    EXPECT_NE(b[0], ' ') << "Leading spaces should be skipped";
    EXPECT_NE(b[0], '\t') << "Leading tabs should be skipped";
    EXPECT_EQ(b.rfind("B", 0), 0u);
}

// Iterator law: post-increment returns the old value, while advancing the iterator.
TEST_F(ColumnIteratorTest_615, PostIncrementReturnsPrevious_615) {
    auto col = Prepare("X\nY");
    auto it = col.begin();
    ASSERT_NE(it, col.end());
    std::string before = *it;

    auto old = it++; // old should refer to the first line, it to the second
    ASSERT_NE(it, col.end());
    std::string after = *it;

    std::string oldVal = *old;
    EXPECT_EQ(oldVal.rfind("X", 0), 0u);
    EXPECT_EQ(before, oldVal) << "Post-increment result should equal the value before increment";
    EXPECT_EQ(after.rfind("Y", 0), 0u);
    EXPECT_NE(oldVal, after);
}

// Progress & termination: iterator over multiple lines advances deterministically and reaches end().
TEST_F(ColumnIteratorTest_615, IterationReachesEnd_615) {
    auto col = Prepare("L1\nL2\nL3");
    auto it = col.begin();
    size_t count = 0;

    std::vector<std::string> lines;
    for (; it != col.end(); ++it) {
        lines.push_back(*it);
        if (++count > 10) break; // safety against non-termination (should never trigger)
    }

    ASSERT_LE(count, 10u) << "Iterator must terminate";
    ASSERT_EQ(lines.size(), 3u);
    EXPECT_EQ(lines[0].rfind("L1", 0), 0u);
    EXPECT_EQ(lines[1].rfind("L2", 0), 0u);
    EXPECT_EQ(lines[2].rfind("L3", 0), 0u);
}

// Exceptional/edge case: empty input yields no lines (begin == end).
TEST_F(ColumnIteratorTest_615, EmptyInputHasNoLines_615) {
    auto col = Prepare("");
    EXPECT_EQ(col.begin(), col.end());
}
