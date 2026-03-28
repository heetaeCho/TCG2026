// File: tests/textflow_columns_iterator_preincrement_620.cpp

#include <gtest/gtest.h>
#include <string>

// Adjust the include path to match your project layout
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

class ColumnsIteratorTest_620 : public ::testing::Test {};

// Normal operation: pre-increment should advance iterator state so that
// dereferenced values before/after ++ differ (observable behavior).
TEST_F(ColumnsIteratorTest_620, PreIncrementAdvances_620) {
    Column left("L1\nL2");
    Column right("R1\nR2");

    // Keep formatting effects out of the way
    left.width(200).indent(0).initialIndent(0);
    right.width(200).indent(0).initialIndent(0);

    auto cols = left + right;

    Columns::iterator it(cols);
    const std::string first = *it;

    ++it; // exercise operator++()

    const std::string second = *it;

    // We do not assert specific contents (black-box), only that advancing changed the observable value.
    EXPECT_NE(first, second);
}

// Boundary condition: uneven column lengths. Pre-increment should be safe even
// when some inner iterators have already reached their ends (no throw, stable behavior).
TEST_F(ColumnsIteratorTest_620, PreIncrementHandlesUnevenColumns_620) {
    Column longer("A1\nA2\nA3");
    Column shorter("B1");

    longer.width(200).indent(0).initialIndent(0);
    shorter.width(200).indent(0).initialIndent(0);

    auto cols = longer + shorter;

    Columns::iterator it(cols);

    // 1st step should be fine
    EXPECT_NO_THROW(++it);

    // Further increments should continue to be safe even as some inner iterators finish
    EXPECT_NO_THROW(++it);
    EXPECT_NO_THROW(++it);
}

// Exceptional/edge-ish case: empty columns. Pre-increment should not crash or throw.
// We only verify no-throw semantics and iterator comparability.
TEST_F(ColumnsIteratorTest_620, PreIncrementOnEmptyColumns_620) {
    Column emptyLeft("");
    Column emptyRight("");

    emptyLeft.width(200).indent(0).initialIndent(0);
    emptyRight.width(200).indent(0).initialIndent(0);

    auto cols = emptyLeft + emptyRight;

    Columns::iterator it(cols);
    Columns::iterator it2(cols); // another iterator at same initial state

    // Initially equal (same source & position)
    EXPECT_TRUE(it == it2);

    // Pre-increment should not throw even if there is nothing to advance
    EXPECT_NO_THROW(++it);

    // After advancing one of them, they should no longer compare equal
    EXPECT_TRUE(it != it2);
}

// Iterator semantics: post-increment returns the prior state (copy) while advancing the iterator.
// This indirectly validates pre-increment behavior as well, without assuming any string formatting.
TEST_F(ColumnsIteratorTest_620, PostIncrementReturnsOldState_620) {
    Column left("X1\nX2");
    Column right("Y1\nY2");

    left.width(200).indent(0).initialIndent(0);
    right.width(200).indent(0).initialIndent(0);

    auto cols = left + right;

    Columns::iterator it(cols);

    const std::string before = *it;

    // post-increment should yield an iterator equal to the old state
    Columns::iterator old = it++;
    const std::string oldVal = *old;     // value before increment
    const std::string after  = *it;      // value after increment

    // Old snapshot matches the value prior to increment;
    // after-increment value should be observably different.
    EXPECT_EQ(before, oldVal);
    EXPECT_NE(before, after);
}
